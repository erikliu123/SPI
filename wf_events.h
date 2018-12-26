/*
 * MRF24WG event definitions
 *
 * This module contains defines used to define WiFi events
 */
#ifndef __WF_EVENTS_H
#define __WF_EVENTS_H

enum {
    UD_SUCCESS = 0,

    // this block of error codes are returned from the MRF24WG in the result field
    // of a managment response message and should not be changed.
    MGMT_RESP_SUCCESS                                              = 1,
    MGMT_RESP_ERROR_INVALID_SUBTYPE                                = 2,
    MGMT_RESP_ERROR_OPERATION_CANCELLED                            = 3,
    MGMT_RESP_ERROR_FRAME_END_OF_LINE_OCCURRED                     = 4,
    MGMT_RESP_ERROR_FRAME_RETRY_LIMIT_EXCEEDED                     = 5,
    MGMT_RESP_ERROR_EXPECTED_BSS_VALUE_NOT_IN_FRAME                = 6,
    MGMT_RESP_ERROR_FRAME_SIZE_EXCEEDS_BUFFER_SIZE                 = 7,
    MGMT_RESP_ERROR_FRAME_ENCRYPT_FAILED                           = 8,
    MGMT_RESP_ERROR_INVALID_PARAM                                  = 9,
    MGMT_RESP_ERROR_AUTH_REQ_ISSUED_WHILE_IN_AUTH_STATE            = 10,
    MGMT_RESP_ERROR_ASSOC_REQ_ISSUED_WHILE_IN_ASSOC_STATE          = 11,
    MGMT_RESP_ERROR_INSUFFICIENT_RESOURCES                         = 12,
    MGMT_RESP_ERROR_TIMEOUT_OCCURRED                               = 13,
    MGMT_RESP_ERROR_BAD_EXCHANGE_ENCOUNTERED_IN_FRAME_RECEPTION    = 14,
    MGMT_RESP_ERROR_AUTH_REQUEST_REFUSED                           = 15,
    MGMT_RESP_ERROR_ASSOCIATION_REQUEST_REFUSED                    = 16,
    MGMT_RESP_ERROR_PRIOR_MGMT_REQUEST_IN_PROGRESS                 = 17,
    MGMT_RESP_ERROR_NOT_IN_JOINED_STATE                            = 18,
    MGMT_RESP_ERROR_NOT_IN_ASSOCIATED_STATE                        = 19,
    MGMT_RESP_ERROR_NOT_IN_AUTHENTICATED_STATE                     = 20,
    MGMT_RESP_ERROR_SUPPLICANT_FAILED                              = 21,
    MGMT_RESP_ERROR_UNSUPPORTED_FEATURE                            = 22,
    MGMT_RESP_ERROR_REQUEST_OUT_OF_SYNC                            = 23,
    MGMT_RESP_ERROR_CP_INVALID_ELEMENT_TYPE                        = 24,
    MGMT_RESP_ERROR_CP_INVALID_PROFILE_ID                          = 25,
    MGMT_RESP_ERROR_CP_INVALID_DATA_LENGTH                         = 26,
    MGMT_RESP_ERROR_CP_INVALID_SSID_LENGTH                         = 27,
    MGMT_RESP_ERROR_CP_INVALID_SECURITY_TYPE                       = 28,
    MGMT_RESP_ERROR_CP_INVALID_SECURITY_KEY_LENGTH                 = 29,
    MGMT_RESP_ERROR_CP_INVALID_WEP_KEY_ID                          = 30,
    MGMT_RESP_ERROR_CP_INVALID_NETWORK_TYPE                        = 31,
    MGMT_RESP_ERROR_CP_INVALID_ADHOC_MODE                          = 32,
    MGMT_RESP_ERROR_CP_INVALID_SCAN_TYPE                           = 33,
    MGMT_RESP_ERROR_CP_INVALID_CP_LIST                             = 34,
    MGMT_RESP_ERROR_CP_INVALID_CHANNEL_LIST_LENGTH                 = 35,
    MGMT_RESP_ERROR_NOT_CONNECTED                                  = 36,
    MGMT_RESP_ERROR_ALREADY_CONNECTING                             = 37,
    MGMT_RESP_ERROR_DISCONNECT_FAILED                              = 38,
    MGMT_RESP_ERROR_NO_STORED_BSS_DESCRIPTOR                       = 39,
    MGMT_RESP_ERROR_INVALID_MAX_POWER                              = 40,
    MGMT_RESP_ERROR_CONNECTION_TERMINATED                          = 41,
    MGMT_RESP_ERROR_HOST_SCAN_NOT_ALLOWED                          = 42,
    MGMT_RESP_ERROR_INVALID_WPS_PIN                                = 44,
    // end of mgmt response error code block

    UD_ERROR_SSID_BUFFER_EMPTY               = 101,     // SSID length > 0, but SSID string is empty
    UD_ERROR_SSID_NOT_DEFINED                = 103,     // An SSID is required for this connection mode
    UD_ERROR_SSID_TOO_LONG                   = 104,     // SSID cannot be longer than 32 characters
    UD_ERROR_NO_CHANNEL_LIST_DEFINED         = 105,     // p_channelList parameter is not valid
    UD_ERROR_INVALID_CHANNEL_0               = 106,     // cannot have a channel number of 0
    UD_ERROR_EXCEEDED_MAX_CHANNELS           = 107,     // Cannot have more than 14 channels in channel list
    UD_INVALID_CHANNEL_NUMBER                = 108,     // Channel list has an invalid channel number
    UD_ERROR_CHANNEL_OUT_OF_RANGE            = 109,     // Channel number too large for selected domain
    UD_ERROR_ALL_DOMAIN_CHANNELS_REQUIRED    = 110,     // when using WPS, the channel list must contain all legal channels in domain
    UD_INVALID_NETWORK_TYPE                  = 111,     // Invalid network type
    UD_ERROR_INVALID_SECURITY_TYPE           = 112,     // Invalid security type
    UD_ERROR_WEP_40_KEY_INVALID_LENGTH       = 113,     // WEP-40 key must be 4 5-byte keys, or 20 bytes
    UD_ERROR_WEP_104_KEY_INVALID_LENGTH      = 114,     // WEP-104 key must be 4 13-byte keys, or 52 bytes
    UD_ERROR_INVALID_WEP_KEY_INDEX           = 115,     // WEP key index must be between and 0 and 3
    UD_ERROR_INVALID_CONFIG                  = 117,     // A previous error event occurred that prevents a connection
    UD_ERROR_INVALID_WPA_KEY_LENGTH          = 118,     // WPA/WPA2 binary key length is invalid (must be 32 bytes)
    UD_ERROR_INVALID_WPA_PASSPHRASE_LENGTH   = 119,     // WPA/WPA2 ASCII passphrase must be between 8 and 63 characters
    UD_ERROR_INVALID_WPA_PASSPHRASE_CHARACTERS = 120,   // Passphrase characters must be printable
    UD_ERROR_WPS_PIN_LENGTH_INVALID          = 121,     // WPS PIN must be 7 digits + checksum, or a total of 8 digits
    UD_ERROR_INVALID_WPS_PIN                 = 122,     // WPS pin does not have a valid checksum in the 8th digit
    UD_ERROR_SSID_DEFINED                    = 123,     // For instrastructure mode using WPS push-button, SSID must be empty
                                                        //  string with length of 0
    UD_ERROR_INVALID_WEP_SECURITY            = 124,     // AdHoc only supports open or WEP security
    UD_ERROR_INVALID_ADHOC_RETRY_COUNT       = 125,     // using WF_RETRY_FOREVER, not recommended for AdHoc networks
    UD_ERROR_INVALID_P2P_SSID                = 126,     // When network type is WF_NETWORK_TYPE_P2P, SSID must be "DIRECT-"
    UD_ERROR_INVALID_P2P_CHANNEL_LIST        = 127,     // When network type is WF_NETWORK_TYPE_P2P, channel list must be 1,6,11
    UD_ERROR_INVALID_DEAUTH_PARAM            = 128,     // UdSetReconnectMode(), deauthAction param invalid
    UD_ERROR_INVALID_BEACON_TIMEOUT_PARAM    = 129,     // UdSetReconnectMode(), beaconTimeoutAction param invalid
    UD_ERROR_INVALID_RECONNECT_MODE          = 130,     // UdSetReconnectMode(), can't have retry count of 0 and attempt to reconnect
    UD_ERROR_ONLY_VALID_WHEN_NOT_CONNECTED   = 132,     // Can only perform this action when not connected
    UD_ERROR_INVALID_WEP_SECURITY_TYPE       = 133,     // t_wepContext has an invalid WEP security type
    UD_ERROR_INVALID_WEP_KEY_TYPE            = 134,     // t_wepContext has an invalid key type
    UD_ERROR_INVALID_SCAN_TYPE               = 136,     // mrf_conn_set_scan(), scan_type parameter is invalid
    UD_ERROR_INVALID_HIDDEN_SSID             = 137,     // SetAdhocContext(), hiddenSsid param must be true or false
    UD_ERROR_INVALID_ADHOC_MODE              = 138,     // SetAdhocContext(), mode param invalid
    UD_ERROR_INVALID_TX_MODE                 = 139,     // WF_TxModeSet(), invalid mode param
    UD_ERROR_INVALID_RTS_THRESHOLD           = 140,     // WF_SetRtsTheshold(), invalid rtsThreshold param
    UD_ERROR_INVALID_MULTICAST_FILTER_ID     = 144,     // t_swMulticastConfig(), or WF_SwMulticastFilterSet(); invalid Multicast filter ID paramter
    UD_ERROR_INVALID_GET_PASS_PHRASE         = 146,     // WF_SetSecurityWps(), getPassphrase param must be true or false
    UD_ERROR_NULL_PASS_PHRASE_INFO           = 148,     // WF_SetSecurityWps(), illegal null pointer for p_wpsPassPhraseInfo param
    UD_ERROR_NOT_WPS_SECURITY                = 150,     // WF_GetWpsCredentials(), invalid to call this if not using WPS security
};
//==============================================================================
//                                  DEFINES/CONSTANTS
//==============================================================================
#define WF_MAC_ADDRESS_LENGTH               6       // MAC addresses are always 6 bytes
#define WF_BSSID_LENGTH                     6       // BSSID is always 6 bytes
#define WF_MAX_SSID_LENGTH                  32      // does not include string terminator
#define WF_MAX_PASSPHRASE_LENGTH            64      // must include string terminator
#define WF_MAX_CHANNEL_LIST_LENGTH          14      // max channel list (for Japan) is 1-14
#define WF_WPS_PIN_LENGTH                   8       // 7 digits + checksum byte
#define WF_WPA_KEY_LENGTH                   32      // WPA binary key always 32 bytes
#define WF_WEP40_KEY_LENGTH                 20      // 4 keys of 5 bytes each
#define WF_WEP104_KEY_LENGTH                52      // 4 keys of 13 bytes each
#define WF_MAX_WEP_KEY_LENGTH               WF_WEP104_KEY_LENGTH
#define WF_NO_EVENT_DATA                    0xffffffffU
#define WF_MAX_NUM_RATES                    8

//CPY FROM wf_universal_driver.h
//==============================================================================
// DEFAULTS - After a reset, the MRF24WG has the following default settings.  These
//            can also be used in various API calls.
//==============================================================================
// see t_scanContext
#define WF_DEFAULT_SCAN_TYPE                WF_ACTIVE_SCAN
#define WF_DEFAULT_SCAN_COUNT               1
#define WF_DEFAULT_SCAN_MIN_CHANNEL_TIME    200     // ms
#define WF_DEFAULT_SCAN_MAX_CHANNEL_TIME    400     // ms
#define WF_DEFAULT_SCAN_PROBE_DELAY         20      // us

// see mrf_conn_set_adhoc()
#define WF_DEFAULT_ADHOC_HIDDEN_SSID        0
#define WF_DEFAULT_ADHOC_BEACON_PERIOD      100     // ms
#define WF_DEFAULT_ADHOC_MODE               WF_ADHOC_CONNECT_THEN_START

// see mrf_powersave_enable()
#define WF_DEFAULT_PS_LISTEN_INTERVAL       1       // 100ms multiplier, e.g. 1 * 100ms = 100ms
#define WF_DEFAULT_PS_DTIM_INTERVAL         2       // number of beacon periods
#define WF_DEFAULT_PS_DTIM_ENABLED          true    // DTIM wake-up enabled (normally the case)

// see t_txmode
#define WF_DEFAULT_TX_MODE                  WF_TXMODE_G_RATES   // full 802.11 g rates

// see mrf_conn_set_rssi()
#define WF_DEFAULT_RSSI                     255     // connect to highest RSSI found

// see mrf_set_rts_threshold()
#define WF_DEFAULT_RTS_THRESHOLD            2347

// see mrf_profile_set_wep()
#define WF_DEFAULT_WEP_KEY_INDEX            0
#define WF_DEFAULT_WEP_KEY_TYPE             WF_SECURITY_WEP_OPENKEY

//===================
// End DEFAULTS block
//===================

// See mrf_set_regional_domain()
enum {
    WF_DOMAIN_FCC           = 0,        // Available Channels: 1 - 11
    WF_DOMAIN_ETSI          = 2,        // Available Channels: 1 - 13
    WF_DOMAIN_JAPAN         = 7,        // Available Channels: 1 - 14
    WF_DOMAIN_OTHER         = 7,        // Available Channels: 1 - 14
};

// WiFi security modes
enum {
    WF_SECURITY_OPEN                         = 0,
    WF_SECURITY_WEP_40                       = 1,
    WF_SECURITY_WEP_104                      = 2,
    WF_SECURITY_WPA_WITH_KEY                 = 3,
    WF_SECURITY_WPA_WITH_PASS_PHRASE         = 4,
    WF_SECURITY_WPA2_WITH_KEY                = 5,
    WF_SECURITY_WPA2_WITH_PASS_PHRASE        = 6,
    WF_SECURITY_WPA_AUTO_WITH_KEY            = 7,
    WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE    = 8,
    WF_SECURITY_WPS_PUSH_BUTTON              = 9,
    WF_SECURITY_WPS_PIN                      = 10,

    WF_MAX_SECURITY_TYPE                     = 10,
};

// mrf_conn_set_scan()
enum {
    WF_SCAN_ACTIVE          = 1,
    WF_SCAN_PASSIVE         = 2,
};

// see mrf_profile_set_network_type()
enum {
    WF_MIN_NETWORK_TYPE            = 1,

    WF_NETWORK_TYPE_INFRASTRUCTURE = 1,
    WF_NETWORK_TYPE_ADHOC          = 2,
    WF_NETWORK_TYPE_P2P            = 3,

    WF_MAX_NETWORK_TYPE            = 3,
};

// see mrf_profile_set_wep()
enum {
    WF_SECURITY_WEP_SHAREDKEY = 0,
    WF_SECURITY_WEP_OPENKEY   = 1,
};

// see mrf_conn_set_adhoc()
enum {
    WF_ADHOC_CONNECT_THEN_START = 0,
    WF_ADHOC_CONNECT_ONLY       = 1,
    WF_ADHOC_START_ONLY         = 2,
};

// See mrf_set_tx_mode()
enum {
    WF_TXMODE_G_RATES       = 0,
    WF_TXMODE_B_RATES       = 1,
    WF_TXMODE_LEGACY_RATES  = 2,
};

// see mrf_conn_get_state()
enum {
    WF_CSTATE_NOT_CONNECTED               = 1,
    WF_CSTATE_CONNECTION_IN_PROGRESS      = 2,
    WF_CSTATE_CONNECTED_INFRASTRUCTURE    = 3,
    WF_CSTATE_CONNECTED_ADHOC             = 4,
    WF_CSTATE_RECONNECTION_IN_PROGRESS    = 5,
    WF_CSTATE_CONNECTION_PERMANENTLY_LOST = 6,
};

// Multicast Filter IDs 多播过滤器
enum {
    WF_MULTICAST_FILTER_1   = 4,
    WF_MULTICAST_FILTER_2   = 5,
};

// see mrf_profile_get_wps_credentials()
enum {
    WF_WPS_AUTH_OPEN        = 0x01,
    WF_WPS_AUTH_WPA_PSK     = 0x02,
    WF_WPS_AUTH_SHARED      = 0x04,
    WF_WPS_AUTH_WPA         = 0x08,
    WF_WPS_AUTH_WPA2        = 0x10,
    WF_WPS_AUTH_WPA2_PSK    = 0x20,
};

// see mrf_profile_get_wps_credentials()
enum {
    WF_WPS_ENC_NONE         = 0x01,
    WF_WPS_ENC_WEP          = 0x02,
    WF_WPS_ENC_TKIP         = 0x04,
    WF_WPS_ENC_AES          = 0x08,
};

// Event Types - see mrf_event()
typedef enum {
    // Connection events
    WF_EVENT_CONNECTION_SUCCESSFUL          = 1,
    WF_EVENT_CONNECTION_FAILED              = 2,
    WF_EVENT_CONNECTION_TEMPORARILY_LOST    = 3,
    WF_EVENT_CONNECTION_PERMANENTLY_LOST    = 4,
    WF_EVENT_CONNECTION_REESTABLISHED       = 5,

    // WiFi scan event
    WF_EVENT_SCAN_RESULTS_READY             = 6,

    // WPS WPA-PSK key calculation needed
    WF_WPS_EVENT_KEY_CALCULATION_REQUEST    = 8,

    // Error events
    WF_EVENT_MRF24WG_MODULE_ASSERT          = 52,
} event_t;
#endif /* __WF_EVENTS_H */
