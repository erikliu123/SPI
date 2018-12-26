// #include "if_mrf.h"
// #include "wf_events.h"
// unsigned mrf_read_byte(unsigned regno)
// {
//     struct wifi_port *w = &wifi_port[0];
//     char reply;

//     spi_select(&w->spiio);
//     spi_transfer(&w->spiio, regno | MRF24_READ_MODE, 1);
//     reply = spi_transfer(&w->spiio, 0xff, 0);//TODO
//     spi_deselect(&w->spiio);
//     //PRINTDBG("-- read %s -> %02x\n", reg_name(regno), reply);
//     return reply;
// }

// /*
//  * Write 8-bit register.
//  */
// void mrf_write_byte(unsigned regno, unsigned value)
// {
//     struct wifi_port *w = &wifi_port[0];

//     //PRINTDBG("-- write %s = %02x\n", reg_name(regno), value);
//     spi_select(&w->spiio);
//     spi_transfer(&w->spiio, regno,1);
//     spi_transfer(&w->spiio, value,1);
//     spi_deselect(&w->spiio);
// }

// /*
//  * Read 16-bit register.
//  * Return register value.
//  */
// unsigned mrf_read(unsigned regno)
// {
//     struct wifi_port *w = &wifi_port[0];
//     char reply[3];

//     spi_select(&w->spiio);
//     reply[0] = spi_transfer(&w->spiio, regno | MRF24_READ_MODE,1);
//     reply[1] = spi_transfer(&w->spiio, 0xff,0);
//     reply[2] = spi_transfer(&w->spiio, 0xff,0);
//     spi_deselect(&w->spiio);
//     //PRINTDBG("-- read %s -> %04x\n", reg_name(regno), (reply[1] << 8) | reply[2]);
//     return (reply[1] << 8) | reply[2];
// }

// /*
//  * Write 16-bit register.
//  */
// void mrf_write(unsigned regno, unsigned value)
// {
//     struct wifi_port *w = &wifi_port[0];

//    // PRINTDBG("-- write %s = %04x\n", reg_name(regno), value);
//     spi_select(&w->spiio);
//     spi_transfer(&w->spiio, regno,1);
//     spi_transfer(&w->spiio, value >> 8,1);
//     spi_transfer(&w->spiio, value & 0xff,1);
//     spi_deselect(&w->spiio);
// }

// /*
//  * Read a block of data from a register.
//  */
// void mrf_read_array(unsigned regno, char *data, unsigned nbytes)
// {
//     struct wifi_port *w = &wifi_port[0];

//     //PRINTDBG("-- read %u bytes from %s: ", nbytes, reg_name(regno));
//     spi_select(&w->spiio);
//     spi_transfer(&w->spiio, regno | MRF24_READ_MODE,1);
//     while (nbytes-- > 0) {
//         *data++ = spi_transfer(&w->spiio, 0xff,0);
//         //PRINTDBG("%02x", data[-1]);
//         if (nbytes > 0) ;
//             //PRINTDBG("-");
//     }
    
//     //PRINTDBG("\n");
//     spi_deselect(&w->spiio);
// }

// /*
//  * Write a data block to specified register.
//  */
// void mrf_write_array(unsigned regno, const char *data, unsigned nbytes)
// {
//     struct wifi_port *w = &wifi_port[0];

//     //PRINTDBG("-- write %u bytes to %s: ", nbytes, reg_name(regno));
//     spi_select(&w->spiio);
//     spi_transfer(&w->spiio, regno,1);
//     while (nbytes-- > 0) {
//         //PRINTDBG("%02x", *data);
//         if (nbytes > 0)
//             //PRINTDBG("-");
//         spi_transfer(&w->spiio, *data++,1);
//     }
//    // PRINTDBG("\n");
//     spi_deselect(&w->spiio);
// }

// /*
//  * Write to analog register via bitbang.
//  */
// static void mrf_write_analog(unsigned bank, unsigned address, unsigned value)
// {
//     unsigned reset, mask;

//     /* Create register address byte. */
//     address <<= 2;

//     /* Enable the on-chip SPI and select the desired bank (0-3). */
//     reset = RESET_ANA_SPI_EN | (bank << 6);
//     mrf_write(MRF24_REG_RESET, reset);

//     /* Bit-bang the address byte, MS bit to LS bit. */
//     for (mask = 0x80; mask; mask >>= 1) {
//         if (address & mask)
//             reset |= RESET_ANA_SPI_DOUT;
//         else
//             reset &= ~RESET_ANA_SPI_DOUT;

//         mrf_write(MRF24_REG_RESET, reset);
//         mrf_write(MRF24_REG_RESET, reset | RESET_ANA_SPI_CLK);
//     }

//     /* Bit bang data from MS bit to LS bit. */
//     for (mask = 0x8000; mask; mask >>= 1) {
//         if (value & mask)
//             reset |= RESET_ANA_SPI_DOUT;
//         else
//             reset &= ~RESET_ANA_SPI_DOUT;

//         mrf_write(MRF24_REG_RESET, reset);
//         mrf_write(MRF24_REG_RESET, reset | RESET_ANA_SPI_CLK);
//     }

//     /* Disable the on-chip SPI. */
//     reset &= ~RESET_ANA_SPI_EN;
//     mrf_write(MRF24_REG_RESET, reset);
// }

// /*-------------------------------------------------------------
//  * Return the current value of the 1ms timer.
//  */
// unsigned mrf_timer_read()
// {
//    /* unsigned count = mfc0_Count();

//     count /= CPU_KHZ / 2;*/
//     return 0;
// }

// int mrf_timer_elapsed(unsigned start_time)
// {
//    /* int elapsed = mrf_timer_read() - start_time;

//     if (elapsed < 0)
//         elapsed += 0xffffffffU / (CPU_KHZ / 2);*/

//     return 0;
// }

// /*-------------------------------------------------------------
//  * Configure host processor external interrupt.
//  * This line is asserted low by MRF24WG.
//  * Config parameter WF_INT defines the interrupt pin to use:
//  * one of INT1, INT2, INT3 or INT4.
//  */
// void mrf_intr_init()
// {
//     struct wifi_port *w = &wifi_port[0];

//     return ;
// }

// /*-------------------------------------------------------------
//  * Called by Universal Driver to inform application of MRF24WG events.
//  *
//  * Various events are reported to the application via this function callback.
//  * The application should take appropriate action based on the event.
//  */
// void mrf_event(event_t event_type, void *event_data)
// {
//     struct wifi_port *w = &wifi_port[0];

//     switch (event_type) {
//     case WF_EVENT_CONNECTION_SUCCESSFUL:
//         //printf("--- %s: connection successful\n", __func__);
//         w->is_connected = 1;
//         break;

//     case WF_EVENT_CONNECTION_FAILED:
//        /* printf("--- %s: connection failed, code=0x%x\n",
//             __func__, (unsigned) event_data);*/
//         w->is_connected = 0;
//         break;

//     case WF_EVENT_CONNECTION_TEMPORARILY_LOST:
//         /*printf("--- %s: connection temporarily lost, code=0x%x\n",
//             __func__, (unsigned) event_data);*/
//         w->is_connected = 0;
//         break;

//     case WF_EVENT_CONNECTION_PERMANENTLY_LOST:
//         /*printf("--- %s: connection lost, code=0x%x\n",
//             __func__, (unsigned) event_data);*/
//         w->is_connected = 0;
//         break;

//     case WF_EVENT_CONNECTION_REESTABLISHED:
//         /*printf("--- %s: connection reestablished, code=0x%x\n",
//             __func__, (unsigned) event_data);*/
//         w->is_connected = 1;
//         break;

//     case WF_EVENT_SCAN_RESULTS_READY:
//         //printf("--- %s: scan results ready, count=%u\n", __func__, (unsigned) event_data);
//         w->is_scan_ready = (unsigned) event_data;
//         break;

//     case WF_WPS_EVENT_KEY_CALCULATION_REQUEST:
//         //printf("--- %s: key calculation request\n", __func__);
//         //bcopy(event_data, &w->key_info, sizeof(w->key_info));
// #if 0
//         // Create the binary key.
//         // This is too cpu-consuming to run with interrupts disabled.
//         //TODO: reschedule to handle it in the watchdog routine.
//         char key[32];
//         mrf_passphrase_to_key(w->key_info.pass, w->key_info.ssid,
//             w->key_info.ssid_len, key);

//         // Send it to MRF24WG.
//         mrf_set_psk(key);
// #endif
//         break;

//     case WF_EVENT_MRF24WG_MODULE_ASSERT:
//         //printf("--- %s: assert info=%04x\n", __func__, (unsigned) event_data);
//         break;
//     }
// }

// void mrf_powersave_activate(int enable)
// {
//     unsigned scratch1;

//     if (enable) {
//         /*
//          * Activate PS-Poll mode on MRF24W.
//          */
//         //dbgprintf("Enable PS\n");
//         mrf_write(MRF24_REG_PSPOLL, PSPOLL_LP_ENABLE);
//     } else {
//         /*
//          * Deactivate PS-Poll mode on MRF24W.
//          * Take it out of low-power mode and wake it up.
//          */
//         //dbgprintf("Disable PS\n");
//         mrf_write(MRF24_REG_PSPOLL, 0);

//         /* Poll the response bit that indicates when the MRF24W
//          * has come out of low power mode. */
//         do {
//             mrf_write(MRF24_REG_ADDR, MRF24_INDEX_SCRATCHPAD1);
//             scratch1 = mrf_read(MRF24_REG_DATA);
//         } while (scratch1 & PSPOLL_LP_ENABLE);
//     }
// }


// /*
//  * Get the device out of power save mode before any message transmission.
//  * Set flag to reactivate power save mode later.
//  */
// void mrf_awake()
// {
//     struct wifi_port *w = &wifi_port[0];

//     if (w->is_powersave_active) {   /* if the application has enabled PS mode */
//         mrf_powersave_activate(0);  /* wake up MRF24WG */
//         w->is_powersave_active = 0;
//         w->need_powersave = 1;      /* set flag to put PS mode back later */
//     }
// }
// void udelay(int a){
//     int i=0;
//     if(a < 0) return ;
//     for(; i<a ;++i) ;
// }
// /*
//  * Setup output on interface.
//  * Get another datagram to send off of the interface queue,
//  * and map it to the interface before starting the output.
//  * called only at splimp or interrupt level.
//  */
// static void mrf_start(struct ifnet *ifp)
// {
//     //TODO
// }

// /*
//  * Initialization of interface; set up initialization block
//  * and transmit/receive descriptor rings.
//  */
// static void mrf_init(int unit)
// {
//     //TODO
// }

// /*
//  * Reset of interface.
//  */
// static void mrf_reset(int unit)
// {
//     //TODO
// }

// /*
//  * Process an ioctl request.
//  */
// /*
// static int mrf_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
// {
//     //TODO
//     return 0;
// }
// */

// /*
//  * Timeout routine.
//  */
// static void mrf_watchdog(int unit)
// {
//     //TODO
// }

// /*
//  * Scan the band for networksTimeout routine.
//  */
// void wifi_scan()
// {
//     struct wifi_port *w = &wifi_port[0];

//     mrf_scan_start(w->cpid);
// }


// /*
//  * Detect the presence of MRF24G controller at given SPI port.
//  * Return -1 on error.
//  */
// static int mrf_detect(struct wifi_port *w)
// {
//     int mask2, v;

//     /* Setup direction of signal pins. */
//     // gpio_set(w->pin_irq);
//     // gpio_set_input(w->pin_irq);         /* /Int input */

//     // gpio_clr(w->pin_reset);
//     // gpio_set_output(w->pin_reset);      /* /Reset output low (active) */

//     // gpio_set(w->pin_hibernate);
//     // gpio_set_output(w->pin_hibernate);  /* Hibernate output high (active) */

//     // /* Take chip out of hibernate and out of reset. */
//     // udelay(2000);
//     // gpio_clr(w->pin_hibernate);         /* Hibernate signal low (inactive) */
//     // udelay(300000);
//     // gpio_set(w->pin_reset);             /* /Reset signal high (inactive) */
//     // udelay(5000);

//     /* Shuttle MRF24WG workaround (benign to production MRF24WG) */
//     mrf_write_analog(2, ANALOG_REG_PLL0, 0x8021);
//     mrf_write_analog(2, ANALOG_REG_PLL0, 0x6021);

//     /* Production MRF24WG workaround (benign to shuttle MRF24WG) */
//     mrf_write_analog(1, ANALOG_REG_OSC0, 0x6b80);
//     mrf_write_analog(1, ANALOG_REG_BIAS, 0xc000);

//     /* Check whether we really have MRF24G chip attached. */
//     mask2 = mrf_read(MRF24_REG_MASK2);
//     mrf_write(MRF24_REG_MASK2, 0xaa55);
//     v = mrf_read(MRF24_REG_MASK2);
//     if (v != 0xaa55)
//         goto failed;
//     mrf_write(MRF24_REG_MASK2, 0x55aa);
//     v = mrf_read(MRF24_REG_MASK2);
//     if (v != 0x55aa)
//         goto failed;
//     mrf_write(MRF24_REG_MASK2, mask2);

//     /* MRF24G controller detected */
//     return 0;

// failed:
//     // gpio_set_input(w->pin_reset);
//     // gpio_set_input(w->pin_hibernate);
//     return -1;
// }
