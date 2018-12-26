/*
 * MRF24WG Universal Driver RAW
 *
 * This module contains definitions for RAW window access
 */
#ifndef __WF_RAW_H
#define __WF_RAW_H

#define NUM_RAW_WINDOWS         6   /* Total number of raw windows */

/*
 * Usage of RAW Windows
 */
#define RAW_ID_RECEIVE          0   /* Network data receive */
#define RAW_ID_TRANSMIT         1   /* Network data transmit */
#define RAW_ID_MGMT_RX          2   /* Receive of management messages */
#define RAW_ID_MGMT_TX          3   /* Transmit of management messages */
#define RAW_ID_SCRATCH          4   /* Not used */
#define RAW_ID_UNUSED           5   /* Not used */

/*
 * Source/Destination objects for mrf_raw_move()
 */
#define RAW_MAC                 0x00    /* MRF24W MAC as command processor */
#define RAW_MGMT_POOL           0x10    /* For management packets */
#define RAW_DATA_POOL           0x20    /* For network packets */
#define RAW_SCRATCH_POOL        0x30    /* Scratch object, not used */
#define RAW_STACK_MEM           0x40    /* Single level stack to save state of RAW, not used */
#define RAW_COPY                0x70    /* RAW to RAW copy, not used */
typedef  char u_int8_t;
void     mrf_raw_init(void);
unsigned mrf_raw_move(unsigned raw_id, unsigned raw_obj, int raw_is_destination, unsigned size);
void     mrf_raw_seek(unsigned raw_id, unsigned index);
void     mrf_raw_read(unsigned raw_id, char *dest, unsigned nbytes);
void     mrf_raw_write(unsigned raw_id, const char *src, unsigned nbytes);
void     mrf_raw_pread(unsigned raw_id, char *dest, unsigned nbytes, unsigned offset);
void     mrf_raw_pwrite(unsigned raw_id, const char *src, unsigned nbytes, unsigned offset);

/*
 * RAW message type definitions.
 */

/* Tx Message Types */
#define WF_TYPE_DATA_REQUEST        1   /* Network packet */
#define WF_TYPE_MGMT_REQUEST        2   /* Management message */

/* Rx Message Types */
#define WF_TYPE_DATA_TX_CONFIRM     1   /* Data packet transmitted */
#define WF_TYPE_MGMT_CONFIRM        2   /* Mgmt message transmitted */
#define WF_TYPE_DATA_RX_INDICATE    3   /* Data packet received */
#define WF_TYPE_MGMT_INDICATE       4   /* Mgmt message received */

/* Tx/Rx Data Message Subtypes */
#define WF_SUBTYPE_STD_DATA         1   /* Generic data */
#define WF_SUBTYPE_NULL_DATA        2
                                 /* 3 - reserved value */
#define WF_SUBTYPE_UNTAMPERED_DATA  4

#endif /* __WF_RAW_H */

//copy from WF_MGMT_MSG_H
/*
 * Management Message Request/Response Subtypes
 */

#define WF_MAX_TX_MGMT_MSG_SIZE         128
enum {
    /* Misc subtypes */
    WF_SUBTYPE_SCAN                             = 1,
    WF_SUBTYPE_JOIN                             = 2,
    WF_SUBTYPE_AUTH                             = 3,
    WF_SUBTYPE_ASSOC                            = 4,
    WF_SUBTYPE_DISCONNECT                       = 5,
    WF_SUBTYPE_DISASOCC                         = 6,
    WF_SUBTYPE_SET_POWER_MODE                   = 7,
    WF_SUBTYPE_SET_PM_KEY                       = 8,
    WF_SUBTYPE_SET_WEP_MAP                      = 9,
    WF_SUBTYPE_SET_WEP_KEY                      = 10,
    WF_SUBTYPE_SET_TEMP_KEY                     = 11,
    WF_SUBTYPE_CALC_PSK_KEY                     = 12,
    WF_SUBTYPE_SET_WEP_KEY_ID                   = 13,
    WF_SUBTYPE_CONFIG_KEY_SPACE                 = 14,
    WF_SUBTYPE_SET_PARAM                        = 15,
    WF_SUBTYPE_GET_PARAM                        = 16,
    WF_SUBTYPE_ADHOC_CONNECT                    = 17,
    WF_SUBTYPE_ADHOC_START                      = 18,

    /* Connection Profile Message Subtypes */
    WF_SUBTYPE_CP_CREATE_PROFILE                = 21,
    WF_SUBTYPE_CP_DELETE_PROFILE                = 22,
    WF_SUBTYPE_CP_GET_ID_LIST                   = 23,
    WF_SUBTYPE_CP_SET_ELEMENT                   = 24,
    WF_SUBTYPE_CP_GET_ELEMENT                   = 25,

    /* Connection Algorithm Message Subtypes */
    WF_SUBTYPE_CA_SET_ELEMENT                   = 26,
    WF_SUBTYPE_CA_GET_ELEMENT                   = 27,

    /* Connnection Manager Message Subtypes */
    WF_SUBTYPE_CM_CONNECT                       = 28,
    WF_SUBTYPE_CM_DISCONNECT                    = 29,
    WF_SUBTYPE_CM_GET_CONNECTION_STATUS         = 30,

    WF_SUBTYPE_SCAN_START                       = 31,
    WF_SUBTYPE_SCAN_GET_RESULTS                 = 32,

    WF_SUBTYPE_CM_INFO                          = 33,

    WF_SUBTYPE_SCAN_FOR_IE                      = 34,  /* not yet supported */
    WF_SUBTYPE_SCAN_IE_GET_RESULTS              = 35,  /* not yet supported */

    WF_SUBTYPE_CM_GET_CONNECTION_STATISTICS     = 36,  /* not yet supported so moved here for now */
    WF_SUBTYPE_NUM_REQUESTS
};


