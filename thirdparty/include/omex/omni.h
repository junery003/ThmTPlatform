/* #### */
#if !defined( __OMNI_H )
#define __OMNI_H 
#define __OMNI_LOADED 1

#if defined(_AIX43)
#include <sys/inttypes.h>
#endif /* _AIX43 */

#if !defined( __OMNI_CODES_LOADED )
#define OMNI_DU_DATALOST    -208002 /* info from sender possibly lost */
#define OMNI_DU_LINKLOST    -208004 /* link to OMdu server lost */
#define OMNI_DU_SENDERLOST  -208006 /* sender service lost */
#define OMNI_DU_SENDERRESTARTED -208008 /* sender service restarted */
#endif

/* 
 * Bandwidth limit status codes 
 */
#define OMNI_BWLIMIT_EXCEEDED -3001 /* Bandwidth limit exceeded */
#define OMNI_BWUSAGE_HIGH     -3002 /* Bandwidth usage over conf percent */
#define OMNI_BWUSAGE_NORMAL    3003 /* Bandwidth usage back to normal */

/* ------------------------------------ *
 * FS#1065-External API Events          *
 * ------------------------------------ */
#define OMNI_NE_RTR_UNCERTAIN   -4001   /* RTR connection status between NG - BE (TR) uncertain */
#define OMNI_NE_RTR_NORMAL       4001   /* RTR connection status between NG - BE (TR) normal */
#define OMNI_NE_OMDU_UNCERTAIN  -4002   /* OMdu connection status between NG - BE uncertain (no broadcasts from BE) */
#define OMNI_NE_OMDU_NORMAL      4002   /* OMdu connection status between NG - BE normal (broadcasts from BE) */
#define OMNI_NE_ORDERS_INACTIVATED  -4003   /* Orders inactivated on backend */
#define OMNI_NE_LOGOUT_IMMINENT  4004   /* A logout event for user is about to be received (due to nighbatch etc) */


#define SEV_WARNING     0   /* Severity warning in log message */
                    /* O%%iLogMessage.Severity value */
#define SEV_SUCCESS     1   /* Severity success in log message */
                    /* O%%iLogMessage.Severity value */
#define SEV_ERROR       2   /* Severity error in log message */
                    /* O%%iLogMessage.Severity value */
#define SEV_INFORMATION     3   /* Severity info. in log message */
                    /* O%%iLogMessage.Severity value */
#define SEV_FATAL       4   /* Severity fatal in log message */
                    /* O%%iLogMessage.Severity value */

#define ENT_TRANSACTION_SYSTEM  0   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_NETWORK     1   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_SECURITY        2   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_OPERATING_SYSTEM    3   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_TRACE       4   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_TABLES      5   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_TRANSACTION     6   /* Log message entity */
                    /* O%%iLogMessage.Entity value */
#define ENT_OMDU        7   /* Messages from OMdu component */ 

#define USER_NAME_LENGTH    32  /* Login msg username field length */
#define USER_PASSWORD_LENGTH    32  /* Login msg password field length */

#define OLD_ENCRYPTION_METHOD   0   /* DEPRECATED! Password method = 0: Password */
                                    /* is stored in the CDB as encrypted.        */
#define NEW_ENCRYPTION_METHOD   2   /* Password method = 2: Password is stored   */
                                    /* in the CDB as hashed values. */

/*
    known omniapi get info information types
*/
#define OMNI_INFTYP_USERCODE            1   /* pick up the usercode */
#define OMNI_INFTYP_FACTYP_E0           2   /* retrieve the 1st ext. facility # */
#define OMNI_INFTYP_FACTYP_I0           3   /* retrieve the 1st int. facility # */
#define OMNI_INFTYP_OMEXVERSION         4   /* retrieve backend omex version string */
#define OMNI_INFTYP_BANDWIDTH           5   /* retrieve bandwidth limitation info */
#define OMNI_INFTYP_OMEXEXCHNAME        6   /* retrieve omex_exchange name */
#define OMNI_INFTYP_OMEXEXCHCODE        7   /* retrieve omex_exchange code */
#define OMNI_INFTYP_COMPRESSION         9   /* retrieve compression state */
#define OMNI_INFTYP_ENCRYPTION          10  /* retrieve encryption state */
#define OMNI_INFTYP_PWD_EXPIRATION      11  /* retrieve number of days before password expiration */
#define OMNI_INFTYP_TIME_UTC            12  /* retrieve OMex system date/time in UTC time */
#define OMNI_INFTYP_TIME_LOCAL          13  /* retrieve OMex system date/time in local time */
#define OMNI_INFTYP_TXTIMEOUT           14  /* Retrieve transaction timeout for API */
#define OMNI_INFTYP_CONCURRENT_BDX      15  /* Check if OAPI/Gateway supports concurrent BDX */
#define OMNI_INFTYP_PARALLEL_SESSIONS   16  /* Check for support for parallel sessions */      /* enh#2786 */
#define OMNI_INFTYP_SESSION_NAME        17  /* Used for setting or retrieving sessions name */ /* enh#2786 */
#define OMNI_INFTYP_DELAY_INFO          18  /* Retrieve delayed txn info, in us */

typedef float           real32;
typedef double          real64;

#if !defined( __INTS_LOADED )

#if !defined(_AIX43)            /* int8 already defined in /usr/include/sys/inttypes.h in AIX 4.3 */
typedef char            int8;
typedef short           int16;
typedef int         int32;
#endif /* _AIX43 */

typedef unsigned char       uint8;
typedef unsigned short      uint16;
#if defined( _MSDOS )
typedef long            int32;
typedef unsigned long       uint32;
#else
typedef unsigned int        uint32;
#endif

#include "oal_align_packed.h"

#if !defined(_AIX43)   /* INT64 et al is already defined on AIX 4.3 */
typedef struct
  {
#if defined( __hpux ) || defined( sun )	|| defined( _AIX ) || \
    defined( __nonstopux ) || defined( __VOS__ ) || defined( __TANDEM )
    int32   l0; /* big endian op. systems */
    uint32  l1;
#else
    uint32  l0; /* little endian op. systems */
    int32   l1;
#endif
  } int64;

#endif /* _AIX43 */

typedef struct
  {
    uint32  l0;
    uint32  l1;
  } uint64;

#endif  /* __INTS_LOADED */

typedef char        omni_username[USER_NAME_LENGTH];
typedef char        omni_password[USER_PASSWORD_LENGTH];

typedef struct
  {
    uint8 country_id_s[2];
    uint8 ex_customer_s[5];
    uint8 user_id_s[5];
  } omni_usercode;

typedef struct
  {
    uint32 status_u;
    uint16 msglen_n;
    /* int8 message_s[]; - start of the message text */
  } omni_netwrksts;

typedef struct
  {
    int8 central_module_c;
    int8 server_type_c;
    uint16 broadcast_number_n;
    omni_netwrksts network_status_x;
  } omni_broadcast;

/* -------------------------------------------------------------------- *
 * FS#1065- External API Events                                         *
 * Following structs are extenstions to omni_broadcast/omni_netwrksts   *
 * The reason for not modifying the struct's above is that we have to   *
 * be backward compatible.                                              *
 * The struct's were added primarerly for BN4 Network event but will be *
 * used for newer Network Events added in the future.                   *
 * They could be used for older Network Events such as BN1 and BN2 but  *
 * then the client programmer needs to interpret the BN{1|2|3} as       *
 * omn_network_event_t instead of omni_broadcast                        *
 * -------------------------------------------------------------------- */
typedef struct
  {
    int32           status_i;   /* can be negative ! */
    uint16          msglen_n;   /* 0 - 65535         */
    int16           filler_n;   /* let's be aligned  */
    int32           reason_i;   /* can be negative 2!*/
    /* int8 message_s[]; - contains the message text */
  } network_event_t;

/* instead of including omex.h for broadcast_type_t *
 * we just keep the fields here                     */
typedef struct
  {
    int8                central_module_c;
    int8                server_type_c;
    uint16              broadcast_number_n;
    network_event_t     network_event;
  } omn_network_event_t;


#include "oal_align_reset.h"

#endif /* __OMNI_H */

