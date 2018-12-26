#include "wf_raw.h"
//#include "spi.h"
#include "uart.h"
#include "if_mrf.h"
#include "wf_registers.h"
#include "wf_events.h"
/*
#include "spiio.h"
#include "wf_reg.h"
#include "fpga.h"
#include "wf_events.h"
*/
static void set_power_mode(int disable, int wake, int use_dtim)
{
    char hdr[6];

    hdr[0] = WF_TYPE_MGMT_REQUEST;
    hdr[1] = WF_SUBTYPE_SET_POWER_MODE;
    hdr[2] = disable;
    hdr[3] = wake;
    hdr[4] = use_dtim;
    hdr[5] = 0;

    mrf_mgmt_send(hdr, sizeof(hdr), 0, 0, 1);
}
void mrf_mgmt_send(char *header, unsigned header_len,
                   char *data, unsigned data_len,
                   int free_response)
{
    unsigned start_time, elapsed_time, buf_avail, nbytes;
    unsigned intr, intr2, assert_info;
    char reply[4];

    mrf_awake();
#if 0
    printf("--- %s: send %u+%u bytes: %02x", __func__, header_len, data_len, header[0]);
    int i;
    for (i=1; i<header_len; ++i)
        printf("-%02x", header[i]);
    for (i=0; i<data_len; ++i)
        printf("-%02x", data[i]);
    printf("\n");
#endif
    start_time = mrf_timer_read();
    for (;;) {
        /*
         * Allocate a Mgmt Tx buffer.
         */
        /* get total bytes available for MGMT tx memory pool */
        buf_avail = mrf_read(MRF24_REG_WFIFO_BCNT1) & FIFO_BCNT_MASK;

        /* if enough bytes available to allocate */
        if (buf_avail >= WF_MAX_TX_MGMT_MSG_SIZE) {
            /* allocate and create the new Mgmt Tx buffer */
            nbytes = mrf_raw_move(RAW_ID_MGMT_TX, RAW_MGMT_POOL, 1, WF_MAX_TX_MGMT_MSG_SIZE);
            if (nbytes > 0)
                break;
            uart_print(" cannot allocate %u bytes of %u free\n\r");
            /*printf("--- %s: cannot allocate %u bytes of %u free\n",
                __func__, WF_MAX_TX_MGMT_MSG_SIZE, buf_avail); */
            
        }
        /* Don't poll too fast, give the chip some time for internal tasks */
        udelay(10);
    }

    /* write out management header */
    mrf_raw_write(RAW_ID_MGMT_TX, header, header_len);

    /* write out data (if any) */
    if (data_len > 0) {
        mrf_raw_write(RAW_ID_MGMT_TX, data, data_len);
    }
    /* signal MRF24W that mgmt message is ready to be processed */
    mrf_raw_move(RAW_ID_MGMT_TX, RAW_MAC, 0, header_len + data_len);
    for (;;) {
        intr = mrf_read_byte(MRF24_REG_INTR);

        // if received a level 2 interrupt
        if (intr & INTR_INT2) {
            intr2 = mrf_read(MRF24_REG_INTR2);
            if (intr2 & INTR2_MAILBOX) {
                /* MRF24WG has hit an assert condition.
                 * Module number in upper 8 bits,
                 * assert information in lower 20 bits. */
                assert_info = (mrf_read(MRF24_REG_MAILBOX0_HI) << 16) |
                              mrf_read(MRF24_REG_MAILBOX0_LO);
                mrf_event(WF_EVENT_MRF24WG_MODULE_ASSERT, (void*) assert_info);
            }

            /* clear this interrupt */
            mrf_write(MRF24_REG_INTR2,
                INTR2_RAW2 | INTR2_RAW3 | INTR2_RAW4 | INTR2_RAW5);
            mrf_write_byte(MRF24_REG_INTR, INTR_INT2);
        }
        if (intr & INTR_FIFO1) {
            /* got a FIFO 1 Threshold interrupt (Management Fifo).  Mgmt Rx msg ready to proces. */
            /* clear this interrupt */
            mrf_write_byte(MRF24_REG_INTR, INTR_FIFO1);

            // signal that a mgmt msg, either confirm or indicate, has been received
            // and needs to be processed
            if (mrf_mgmt_receive_confirm())
                break;
        }

        udelay(10);
    }
    /* If the caller wants to delete the response immediately
     * (doesn't need any data from it). */
    if (free_response) {
        /* Read and verify result before freeing up buffer to ensure
         * our message send was successful. */
        mrf_raw_pread(RAW_ID_MGMT_RX, reply, sizeof(reply), 0);

        if (reply[2] != MGMT_RESP_SUCCESS) {
            uart_print(" mgmt response failed, result=\n\r");
            uart_print(my_itoa(reply[2]));
            uart_print("\n\r");
            //("--- %s: mgmt response failed, result=%u\n", __func__, reply[2]);
        }
        else if (reply[1] != header[1]) {
            uart_print("invalid mgmt response subtype=%u, expected=\n\r");
            uart_print(my_itoa(reply[1]));
            uart_print("\n\r");
           /* printf("--- %s: invalid mgmt response subtype=%u, expected=%u\n",
                __func__, reply[1], header[1]);*/
        }

        /* free mgmt buffer */
        mrf_raw_move(RAW_ID_MGMT_RX, RAW_MGMT_POOL, 0, 0);
    }
}
