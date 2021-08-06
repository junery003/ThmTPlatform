#if !defined(__OMNIAPI_H)
#define __OMNIAPI_H
/*
    OMNIAPI.H - Definitions for the OMnet Application Programming Interface

*/

/*
    Platform-specific definitions
*/

/*
    On Windows NT, VMS, VMS/TCP, HP-UX, AIX, Sun Solaris and Sun SunOS,
    simply compile
*/

/*
    osf on ALPHA is 64-bit architecture.
    Passing zero to a pointer argument when no function
    prototype is visible results in the use of 4-yte zero insted
    of 6-byte zero. =L results in 8-byte zero.
*/
#if defined( __osf__ )
#define W_NULL (void*)0L
#define NULL 0L
#else
#define W_NULL (void*)0
#endif

#define om_malloc malloc
#define om_free free
#define om_strlen strlen
#define om_memcpy memcpy
#define om_sprintf sprintf

#ifndef TRUE
#define TRUE (1 == 1)
#endif
#ifndef FALSE
#define FALSE (0 == 1)
#endif

#include "om_inttypes.h"

#define omniapi_read_event(et,rb,rl,em) \
    omniapi_read_event_ext(et,rb,rl,em,(int32)0)

/*
    Important!

    The following two literals must not be greater than 64000 to
    be supported by the OMnet backbone.
*/
#define MAX_REQUEST_SIZE        ((int32) 64000)/* request buffer size */
#define MAX_RESPONSE_SIZE       ((int32) 64000)/* response buffer size */

#define USE_GLOBAL_SOCKET       ((int16  *)-1)
#define UNINITIALIZED_HANDLE    ((int16)-1)

#define SRC_DEFAULT             ((uint8) 16)    /* the default source for */
                                                /* PUT_MGMT calls */
#define READEV_OPTMSK_MANY      1               /* option for many events */
                                                /* from a _READ_EVENT call */
#define READEV_OPTMSK_SINGLE 0                  /* Option for one event */

#define ZLIB_BUFFERSIZE_OAPI 1024 * 128  /* Z-lib Buffer size allocation */

#define PUTQUAD(y,x) swapint64_t(&y, &x)
#define PUTQUAD_OLD(y,x) y = swapint64(x)
#define PUTLONG(y,x) y = swapint32 (x)
#define PUTSHORT(y,x) y = swapint16 (x)
#define PUTBYTE(y,x) y = (x)
#define PUTORDERID(y,x) y = swaporderid(x)


#include "oal_align_packed.h"

/*
    OMNIAPI type definitions
*/
typedef struct
{                               /* OMnet transaction message */
    uint32      length_u;       /* Number of bytes after USRCOD_X */
} omni_message;

typedef struct
{                               /* OMnet logging message */
    uint32      length_u;       /* Number of bytes after RESRVD */
    uint8       resrvd_s[116];  /* Reserved by OM for OMnet use */
} omni_log_message;

/* Deprecated. Use omni_login_t instead. */
typedef struct
{                               /* OMnet login message */
    uint32          type_u;     /* routing id (always 0 at login) */
    omni_username   user_s;     /* user idenfication */
    omni_password   pass_s;     /* password */
    uint8_t         filler_32_s[32];/* Field is not used any more. */
                                    /* See OMnet Application Programmer�s Interface Manual */
    int8            node_s[129];/* node name or number */
    int8            sock_s[21]; /* socket name or number */
    int8            idnt_s[18]; /* program identification */
} omni_login_message;

#define LOGIN_NORMAL    0
#define LOGIN_FORCED    1

/* Struct used between API Client Appl and OMnet API library */
/* when setting logging in. */
typedef struct
{                                           /* OMnet login data structure */
    omni_username   user_s;                 /* user idenfication */
    omni_password   pass_s;                 /* password */
    char            gateway_node_s[128];    /* gateway node name or ip-number */
    uint32_t        port_u;                 /* gateway port number */
    char            appl_ident_s[32];       /* program identification */
    uint8_t         forced_u;               /* LOGIN_NORMAL=normal login, */
                                            /* LOGIN_FORCED=forced login */
    char            filler_3_s[3];          /* filler */
} omni_login_t;

/* Struct used when requiesting OMNI_INFTYP_OMEXEXCHCODE */
typedef struct
{
    uint32_t        num_u;      /* Unsigned 32 bit numerical value  */
} omni_unsigned_num_t;

/* Struct used when requiesting OMNI_INFTYP_PWD_EXPIRATION, */
/* OMNI_INFTYP_COMPRESSION and OMNI_INFTYP_ENCRYPTION */
typedef struct
{
    int32_t         num_i;      /* Signed 32 bit numerical value  */
} omni_signed_num_t;


/* Struct used between API Client Appl and OMnet API library */
/* when setting a new password */
typedef struct
{                                   /* Set password message */
    omni_password   pass_s;         /* Current password */
    omni_password   new_pass_s;     /* The new password */
} omni_set_password_t;


/* Struct used when requiesting OMNI_INFTYP_BANDWIDTH */
typedef struct
{
    uint32        inbound;      /* Inbound in byte/s of limit       */
    uint32        outbound_qr;  /* Outbound qry in byte/s           */
    uint32        outbound_bdx; /* Outbound bdx in byte/s           */
} omni_bw_item_t;


/* Struct used when requiesting OMNI_INFTYP_BANDWIDTH */
typedef struct
{
    uint32         interval;    /* Interval T in seconds            */
    int32          inbound_lim; /* Inbound limit in byte/s          */
    int32          outbound_lim;/* Outbound limit in byte/s         */
    omni_bw_item_t last;        /* Last T seconds in byte/s         */
    omni_bw_item_t average;     /* Average Bandwidth util in byte/s      */
    omni_bw_item_t peak;        /* Peak Bandwidth util. in byte/s   */
    uint32         tot_ses_len; /* Total session length in seconds  */
} omni_bw_info_t;


/*
    Information object used for subscriptions
*/
typedef struct
{
    uint16 infsrc_n;            /* information source */
    uint16 inftyp_n;            /* information type   */
    struct
    {
        char central_module_c;
        char server_type_c;
        unsigned short transaction_number_n;
    } brdcst_x;                 /* broadcast type, like 'B' 'I' 9 */
    union                       /* attribute based on info type   */
    {
        struct
        {
            uint32 no_use_u;    /* currently always set to one    */
        } general_x;            /* general: inftyp == 1           */
        struct
        {
            uint16 commodity_n; /* OMex commodity code */
            uint8 exp_year_c;   /* expiration year [binary 96 for 1996] */
            uint8 exp_month_c;  /* expiration month [binary 1 for Jan]  */
        } derivative_x;         /* derivative: inftyp == 2 */
        struct
        {
            uint32 commodity_u; /* OMex commodity code     */
        } underlying_x;         /* underlying: inftyp == 3 */
        struct
        {
            uint16 no_use_n;        /* currently always set to one */
            uint16 member_info_n;   /* member information, 0: all member broadcast */
                                    /*                     1: only user broadcast */
        } dedicated_x;              /* dedicated: inftyp == 4 */
        struct
        {
            uint32 dissemination_u; /* OMex dissemination group */
        } dissemination_x;          /* dissemination: inftyp == 5 */
        struct
        {
            uint16 underlying_n; /* OMex inderlying id         */
            uint8  market_c;     /* OMex market code           */
            uint8  group_c;      /* OMex instrument group code */
               
        } instrumentclass_x;     /* Instrument Class: inftyp == 7 */
        struct
	{
	    uint16 member_info_n;/* OMex member information    */
            uint8  market_c;     /* OMex market code           */
            uint8  group_c;      /* OMex instrument group code */
               
        } instrument_dedicated_x;/* Instrument Dedicated: inftyp == 8 */
    } attrib_x;                     /* info type dependent attributes */
} infobj_t;

typedef struct                  /* authorised info object return from omniapi */
{                               /* read event ext with the SHOW_SUBSCR flag */
    infobj_t infobj_x;          /* information object */
    uint32 force_u;             /* force flag: 1: already subscr for by gwy */
                                /*             0: not subscribed for by gwy */
} auth_infobj_t;

typedef struct                  /* returned when new subscription is added to the CDB through the API */
{                               /* broadcast type is BN2 */
    int8 central_module_c;
    int8 server_type_c;
    uint16 broadcast_number_n;
    auth_infobj_t auth_infobj_x;
} new_subscr_t;

typedef struct                  /* information object description for */
{                               /* omniapi set event */
    infobj_t infobj_x;          /* information object */
    uint32 handle_u;            /* subscription handle */
    int32 status_i;             /* subscription status */
} subscr_item_t;

typedef struct                  /* event received from omniapi read event ext */
{                               /* if subscriptions are used */
    uint32 handle_u;            /* subscription handle causing the event */
    uint16 evelen_n;            /* length of the event */
                                /* event forthcoming: subscribed_event_t *foo; found at ( foo + 1 ) */
} subscribed_event_t;

/*
    returned structure when asking for known subscriptions
    (omniapi_read_event_ext with the OMNI_EVTTYP_SHOW_SUBSCR option)
*/
typedef struct
{
    uint32 objects_u;           /* number of information objects forthcoming */
    auth_infobj_t assobj_x[1];  /* first assigned info object in the list */
} show_subscr_list_t;

typedef struct
{
    int32 buflen_i;             /* len of the set event buffer (buflen incl) */
    subscr_item_t subitm_x[1];  /* first subscription item */
} set_event_list_t;


/* Struct used when requiesting OMNI_INFTYP_TIME_... */
typedef struct 
{ 
 	int32_t tm_sec;     /* seconds after the minute - [0,59] */
 	int32_t tm_min;     /* minutes after the hour - [0,59] */
 	int32_t tm_hour;    /* hours since midnight - [0,23] */
 	int32_t tm_mday;    /* day of the month - [1,31] */
 	int32_t tm_mon;     /* months since January - [0,11] */
 	int32_t tm_year;    /* years since 1900 */
 	int32_t tm_wday;    /* days since Sunday - [0,6] */
 	int32_t tm_yday;    /* days since January 1 - [0,365] */
 	int32_t tm_isdst;   /* daylight savings time flag */ 
} omni_tm_t; 


/* Struct used when requiesting OMNI_INFTYP_TIME_... */
typedef struct 
{
 	char system_datetime_s[28]; /* For example "Thu Sep 16 13:35:22 2004" */
 	omni_tm_t system_datetime;
} omni_time_info_t;

#include "oal_align_reset.h"

/*
    Callable Routines:
    Facility types 0-15 are reserved.
    Source values in the range 0-31 are reserved.
*/

#ifdef __cplusplus
extern "C"
{
#endif
    /* Function below is using one single global session handle. */
    /* These functions are deprecated. */
    int32 omniapi_tx (
        int32  *,               /* transaction status, by ref */
        uint32,                 /* facility type, by value */
        omni_message  **,       /* tx buffers, pointer vector by ref */
        uint32     *,           /* transaction ID, by ref */
        uint32     *);          /* order ID, by ref */

    int32 omniapi_query (
        int32  *,               /* transaction status, by ref */
        uint32,                 /* facility type, by value */
        omni_message  *,        /* send buffer, by ref */
        int8,                   /* return buffer flag, by value */
        int8 *,                 /* receive buffer, by ref */
        uint32  *,              /* receive buf length, by ref */
        uint32  *,              /* transaction ID, by ref */
        uint32  *);             /* order ID, by ref */

    int32 omniapi_set_event (
        uint32,                 /* event type, by value */
        int8  *);               /* reserved by OM */

    int32 omniapi_clear_event (
        uint32,                 /* event type, by value */
        int8  *);               /* reserved by OM */

    int32 omniapi_read_event_ext (
        uint32,                 /* event type, by value */
        int8 *,                 /* receive buffer, by reference */
        uint32  *,              /* receive length, by reference */
        int32  *,               /* event mask, by reference */
        int32);                 /* option mask, by value */

    int32 omniapi_put_mgmt (
        uint8,                  /* message entity, by value */
        uint8,                  /* message severity, by value */
        uint16,                 /* entity type, by value */
        uint8,                  /* message source, by value */
        omni_log_message  *);   /* log message, by reference */

    int32 omniapi_get_message (
        int32,                  /* message code, by value */
        int8  *,                /* message string, by reference */
        uint32  *,              /* messge length, by reference */
        int32);                 /* simple message string, bool by val */


    int32 omniapi_get_info (
        int32  *,               /* reason, by reference */
        uint32,                 /* information type, by value */
        uint32  *,              /* buffer length, by reference */
        void  *);               /* information buffer, by reference */
    /* Function above is using one single global session handle. */
    /* These functions are deprecated. */

    void omniapi_cvt_string (
        int8,                   /* TRUE=TO, FALSE=FROM ISO format */
        uint8  *);              /* string to be converted */

    void omniapi_cvt_int (
        void*,                  /* integer to be converted to/from */
                                /* little-endian, by reference */
        int16);                 /* size (in bytes) of integer */

    void swapint64_t (void *outVal, void *inVal);
    uint64 swapint64 (uint64 intval);
    uint32 swapint32 (uint32 intval);
    uint16 swapint16 (uint16 intval);

    uint64 swaporderid( uint64 orderid);

    struct tm* omniapi_convert_timestruct(omni_tm_t* omni_tm_p, struct tm* tm_p);  

#define omniapi_session_handle  void*   /* to ease the readability in code */

    int32 omniapi_tx_ex (
        omniapi_session_handle, /* Handle to session */
        int32 *,                /* transaction status, by ref */
        uint32,                 /* facility type, by value */
        omni_message **,        /* tx buffers, pointer vector by ref */
        uint32    *,            /* transaction ID, by ref */
        uint32    *);           /* order ID, by ref */

  int32 omniapi_tx_response_ex (
	omniapi_session_handle, /* Handle to session */
	int32 *,                /* transaction status, by ref */
	uint32,                 /* facility type, by value */
	omni_message *,         /* send buffer, by ref */
	int8,                   /* return buffer flag, by value */
	int8 *,                 /* receive buffer, by ref */
	uint32 *,               /* receive buf length, by ref */
	uint32 *,               /* transaction ID, by ref */
	uint32 *);              /* order ID, by ref */

    int32 omniapi_query_ex (
        omniapi_session_handle, /* Handle to session */
        int32 *,                /* transaction status, by ref */
        uint32,                 /* facility type, by value */
        omni_message *,         /* send buffer, by ref */
        int8,                   /* return buffer flag, by value */
        int8 *,                 /* receive buffer, by ref */
        uint32 *,               /* receive buf length, by ref */
        uint32 *,               /* transaction ID, by ref */
        uint32 *);              /* order ID, by ref */

    int32 omniapi_set_event_ex (
        omniapi_session_handle, /* Handle to session */
        uint32,                 /* event type, by value */
        int8 *);                /* reserved by OM */

    int32 omniapi_clear_event_ex (
        omniapi_session_handle, /* Handle to session */
        uint32,                 /* event type, by value */
        int8 *);                /* reserved by OM */

    int32 omniapi_read_event_ext_ex (
        omniapi_session_handle, /* Handle to session */
        uint32,                 /* event type, by value */
        int8 *,                 /* receive buffer, by reference */
        uint32 *,               /* receive length, by reference */
        int32 *,                /* event mask, by reference */
        int32);                 /* option mask, by value */

    int32 omniapi_put_mgmt_ex (
        omniapi_session_handle, /* Handle to session */
        uint8,                  /* message entity, by value */
        uint8,                  /* message severity, by value */
        uint16,                 /* entity type, by value */
        uint8,                  /* message source, by value */
        omni_log_message *);    /* log message, by reference */

    int32 omniapi_get_message_ex (
        omniapi_session_handle, /* Handle to session */
        int32,                  /* message code, by value */
        int8 *,                 /* message string, by reference */
        uint32 *,               /* messge length, by reference */
        int32);                 /* simple message string, bool by val */

    int32 omniapi_get_info_ex (
        omniapi_session_handle, /* Handle to session */
        int32 *,                /* reason, by reference */
        uint32,                 /* information type, by value */
        uint32 *,               /* buffer length, by reference */
        void *);                /* information buffer, by reference */

    omniapi_session_handle omniapi_create_session(void);

    void omniapi_close_session(
        omniapi_session_handle);/* Handle to session */

    int32 omniapi_set_option_ex (
        omniapi_session_handle, /* Handle to session */
        int32,                  /* option type  (OMNIAPI_OPT_nn)   */
        int32 );                /* option value (OMNIAPI_OPVAL_nn) */

    int32 omniapi_set_info_ex (
        omniapi_session_handle, /* Handle to session */
        int32 opt_type,         /* option type */
        void *opt_value );      /* option value */    

    int32 omniapi_set_option_default (
        int32,                  /* option type  (OMNIAPI_OPT_nn)   */
        int32 );                /* option value (OMNIAPI_OPVAL_nn) */

    int32_t omniapi_login_ex (
        omniapi_session_handle, /* Handle to session */
        int32_t *,              /* transaction status, by ref */
        omni_login_t *);        /* pointer to data struct */

    int32_t omniapi_logout_ex (
        omniapi_session_handle, /* Handle to session */
        int32_t *);             /* transaction status, by ref */

    int32_t omniapi_set_newpwd_ex (
        omniapi_session_handle, /* Handle to session */
        int32_t *,              /* transaction status, by ref */
        omni_set_password_t *); /* pointer to data struct */


    int32 omniapi_read_event_block (
        omniapi_session_handle, /* Handle to session */
        uint32,                 /* Event Type */
        int8*,                  /* Receive buffer */
        uint32*,                /* Receive buffer length */
        uint32,                 /* Wait Timeout */
        uint32                  /* Wait type */
        );

#ifdef __cplusplus
}
#endif

/*
    Option Types (omniapi_set_option_ex / omniapi_set_option_default )
    ------------------------------------------------------------------
    OMNIAPI_OPT_COMPRESS  - compress session data
    OMNIAPI_OPT_ENCRYPT   - encrypt session data
*/
#define OMNIAPI_OPT_COMPRESS            1
#define OMNIAPI_OPT_ENCRYPT             2
#define OMNIAPI_OPT_CONCURRENT_BDX      3
#define OMNIAPI_OPT_SES_NAME            4

/*
    Option Values (omniapi_set_option_ex / omniapi_set_option_default )
    -------------------------------------------------------------------
    OMNIAPI_OPVAL_ANY     - use gateway default value
    OMNIAPI_OPVAL_ENABLE  - enable option
    OMNIAPI_OPVAL_DISABLE - disable option
*/
#define OMNIAPI_OPVAL_ANY       1
#define OMNIAPI_OPVAL_ENABLE    2
#define OMNIAPI_OPVAL_DISABLE   3


/*
    Wait Types (omniapi_read_event_block) )
    -------------------------------------------------------------------
    OMNIAPI_BDXBUFFER_ATLEAST_ONE     - Wait till one broadcast is received
*/

#define OMNIAPI_BDXBUFFER_ATLEAST_ONE       1

/*
    Error Codes
*/

/*
    Module OAPI
*/

#define OMNIAPI_TX_IN_PROGRESS       5      /* TX is in progress */
#define OMNIAPI_ALLEVTS              4      /* All events collected */
#define OMNIAPI_OVERFLOW             3      /* Event message buffer overflow */
#define OMNIAPI_ALR_CLR              2      /* Event type already cleared */
#define OMNIAPI_ALR_SET              1      /* Event type already set */
#define OMNIAPI_NORMAL               0      /* Normal completion */
#define OMNIAPI_FAILURE             -1      /* Failure completion */
#define OMNIAPI_NOT_READY           -2      /* OAPI not ready */
#define OMNIAPI_FACID_NOT_VALID     -3      /* Facility Id not in range */
#define OMNIAPI_INVALID_TABLE       -4      /* Invalid table type */
#define OMNIAPI_NOT_LOGGED_IN       -5      /* OAPI not logged in */
#define OMNIAPI_RESERVED_6          -6
#define OMNIAPI_RESERVED_7          -7
#define OMNIAPI_RESERVED_8          -8
#define OMNIAPI_NOT_INITIALIZED     -9      /* OAPI not initialized */
#define OMNIAPI_NO_INFO_RCVD        -10     /* No network information received */
#define OMNIAPI_NOBACKEND           -11     /* Backend connection failed */
#define OMNIAPI_TX_ABORTED          -12     /* Transaction aborted */
#define OMNIAPI_TRUNCATED           -13     /* Data truncated */
#define OMNIAPI_CNV_NO_RANGE        -14     /* Table conversion range error */
#define OMNIAPI_CNV_NOT_SORTED      -15     /* Table conversion sort error */
#define OMNIAPI_CNV_OFFS_ERROR      -16     /* Table conversion offset error */
#define OMNIAPI_NO_SUCH_ID          -17     /* Invalid transaction type */
#define OMNIAPI_VER_FIELD_ERROR     -18     /* Transaction verification error */
#define OMNIAPI_VER_INT_ERROR       -19     /* Message verific. internal error */
#define OMNIAPI_VER_TABLE_ERROR     -20     /* Table verification error */
#define OMNIAPI_TX_TIMEOUT          -21     /* Transaction timeout */
#define OMNIAPI_TX_DECLFAIL         -22     /* Transaction server/requester declaration failure */
#define OMNIAPI_TX_FAILURE          -23     /* Transaction failure */
#define OMNIAPI_DYNMEM              -24     /* Error obtaining dynamic memory */
#define OMNIAPI_INVARG              -25     /* Invalid argument */
#define OMNIAPI_NOT_FOUND           -26     /* Requested data not found */
#define OMNIAPI_ITV_ERROR           -27     /* Information table verification error */
#define OMNIAPI_NO_USR_OR_PASSW     -28     /* Username and/or Password missing */
#define OMNIAPI_NO_NET_PATH         -29     /* Net Path data missing */
#define OMNIAPI_INVEVT              -30     /* Invalid event type */
#define OMNIAPI_RESERVED_31         -31
#define OMNIAPI_INVTXTYPE           -32     /* Invalid transaction type */
#define OMNIAPI_RESERVED_33         -33
#define OMNIAPI_RESERVED_34         -34
#define OMNIAPI_FATAL               -35     /* Fatal OAPI error */
#define OMNIAPI_NOORDERID           -36     /* No order id */
#define OMNIAPI_RESERVED_37         -37
#define OMNIAPI_RESERVED_38         -38
#define OMNIAPI_NOTAUTH             -39     /* Subscription not authorized, or failed   */
#define OMNIAPI_PASSW_EXPIRED       -40     /* The password has expired */
#define OMNIAPI_INVALID_PASSW       -41     /* Password is not valid. */
#define OMNIAPI_GATEWAY_FULL        -42     /* No more users allowed on the gateway */
#define OMNIAPI_ENDIAN_ERROR        -50     /* Endian error, bytewap failed */

#define OMNIAPI_RESERVED_51         -51
#define OMNIAPI_RESERVED_52         -52

/* Network errors introduced in OSRV_V085  */

#define OMNIAPI_NETERR_LINK         -53     /* Link failure between Client and Gateway */
#define OMNIAPI_NETERR_TIMEOUT      -54     /* Timed out while doing network I/O, connection lost */

/* Concurrent connection status and error codes */

#define OMNIAPI_CONCUR_ERROR        -55     /* Error in concurrent connection */
#define OMNIAPI_CONCUR_DISABLE      -56     /* Concurrent connection disabled */
#define OMNIAPI_ERROPTCONC	    -57     /* Concurrent connection not supported */


/*
    module OMNIAPI
*/
#define OMNIAPI_MAX_STATUS           2100   /* Highest status code (for the moment) */

#define OMNIAPI_RECONNECT            2000   /* successful reconnection */
#define OMNIAPI_SUCCESS              0      /* normal OMNIAPI completion */
#define OMNIAPI_PROBLEM             -2000   /* error in OMNIAPI internal call */
#define OMNIAPI_INTFAILURE          -2001   /* internal OMNIAPI error */
#define OMNIAPI_BADNARGS            -2003   /* bad number of arguments */
#define OMNIAPI_BADARGVAL           -2004   /* bad argument value */
#define OMNIAPI_NONETWORK           -2005   /* no network is present for IPC */
#define OMNIAPI_OSBADCONFIG         -2006   /* O/S incorrectly configured */
#define OMNIAPI_OAPI                -2007   /* problem in the internal OM API */
#define OMNIAPI_NOTCONNECTED        -2008   /* invalid operation before LOGIN */
#define OMNIAPI_NOGWYSRV            -2009   /* no gateway service defined */
#define OMNIAPI_BADHOSTNAME         -2010   /* host name could not be translated */
#define OMNIAPI_ERRSOCKET           -2011   /* socket could not be allocated */
#define OMNIAPI_ERRCONNECT          -2012   /* system error occured on 'connect' */
#define OMNIAPI_ERRBIND             -2013   /* system error occured on 'bind' */
#define OMNIAPI_NOSESSION           -2014   /* session is aborted */
#define OMNIAPI_ERRSEND             -2015   /* error on send() */
#define OMNIAPI_ERRMEM              -2016   /* error on malloc() */
#define OMNIAPI_APIOLD              -2017   /* OMNIAPI too old for the gateway */
#define OMNIAPI_RESERVED_2018       -2018
#define OMNIAPI_SESINUSE            -2019   /* gateway API session already in use */

#define OMNIAPI_ERROPTCMPZ          -2020   /* compression option rejected */
#define OMNIAPI_ERROPTENCRYPT       -2021   /* encryption option rejected */
#define OMNIAPI_ERR_SECURE          -2022   /* Failed to establish secure ses*/
#define OMNIAPI_LOGIN_DISABLED      -2023   /* Login disabled by OSABE */
#define OMNIAPI_INVALID_LOGIN_ATTEMPT -2024 /* Invalid login attempt */
#define OMNIAPI_OMNBE_BUSY          -2025   /* Please wait - OMnet backend is busy */
#define OMNIAPI_LOGIN_FAILED        -2026   /* Communications/database problems */
#define OMNIAPI_PWD_CHANGE_REQ       2027   /* Password has expired. Restricted access until password is changed. */
#define OMNIAPI_PWD_IMPEND_EXP       2028   /* Login succeeded, but password expiration is impending. */
#define OMNIAPI_INVALID_CHRS        -2029   /* Characters 0x01 to 0x19, '%' and '\' are not allowed in passwords. */
#define OMNIAPI_NO_NULL_TERMINATION -2030   /* String has to be null-terminated. */
#define OMNIAPI_WRONG_TX_SIZE       -2031   /* The provided buffer size is not correct. */
#define OMNIAPI_CALL_NOT_SUPPORTED  -2032   /* The call that was done is not supported by the exchange. */
#define OMNIAPI_INVALID_LOGIN_LOCKED    -2033  /* Login denied. User account is locked.     */
#define OMNIAPI_INVALID_LOGIN_SUSPENDED -2034  /* Login denied. User account is suspended.  */
#define OMNIAPI_RELOGIN_NOT_ALLOWED -2035   /* Login denied. Relogin is not allowed. */
#define OMNIAPI_NOT_APPLICABLE      -2036   /* The requested information is not applicable. */
#define OMNIAPI_INVALID_LOGIN_INACTIVE  -2037  /* Login denied. User account is inactivated. */
#define OMNIAPI_INVALID_BEF_CHG_PWD -2038   /* Invalid request before password is changed. */

#define OMNIAPI_RESERVED_2039       -2039
#define OMNIAPI_RESERVED_2040       -2040
#define OMNIAPI_RESERVED_2041       -2041
#define OMNIAPI_RESERVED_2042       -2042

#define OMNIAPI_PART_NOT_FOUND      -2043   /* Backend partition not found */
#define OMNIAPI_PART_NOT_REACHABLE  -2044   /* Backend partition not reachable */

#define OMNIAPI_CONCUR_EXISTS       -2045   /* Concurrent connection already exists for the session */
#define OMNIAPI_INVALID_IDENT       -2046   /* Invalid Session/Concurrent identifier  */

#define OMNIAPI_SESSIONS_EXCEEDED   -2047   /* Login Denied. Session limit reached, no more sessions allowed for this user */
#define OMNIAPI_INVALID_INSTANCE    -2048   /* Login Denied. Parallel sessions not allowed from different instances */

#define OMNIAPI_MIN_STATUS          -2100   /* Lowest status code */

#endif /* __OMNIAPI_H */
