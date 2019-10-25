#ifndef _UPSTYPES_H
#define _UPSTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef EMBEDDED
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <pthread.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "pibasic.h"
#include "i2types.h"
#include "errcode.h"
#include "errorlog.h"
#include "conffile.h"
#include "dtdecode.h"
#include "events.h"
#include "mic.h"
#include "fwinterf.h"

#define MAXSTRING 256
#define MAX_UPS_NUMBER 2
#define UPSNAMELEN  100
#define SHMPATH "/var/run/upsd.pid"
#ifndef u_char
typedef u8 u_char;
#endif
#ifndef int32_t
typedef s32 int32_t;
#endif
#ifndef uint32_t
typedef u32 uint32_t;
#endif

enum { 
   CI_UPSMODEL = 0,                /* Model number */
   CI_STATUS,                      /* status function */
   CI_LQUAL,                       /* line quality status */
   CI_VLINE,                       /* line voltage */
   CI_VOUT,                        /* Output voltage */
   CI_VBATT,                       /* Battery voltage */
   CI_LOAD,                        /* UPS Load */
   CI_Discharging,                 /* Discharging */
   CI_Overload,
   CI_NeedReplacement,             /* NeedReplacement */
   CI_BATTLEV,                      /* RemainingCapacity */
   CI_RUNTIM,                      /* Est. Runtime left */
   CI_BatteryPresent,               /* BatteryPresent */
   CI_ACPresent,                   /* ACPresent */
   CI_ITEMP,                       /* Internal UPS temperature */
   CI_IDEN,                        /* UPS Identification (name) */
   CI_MANDAT,                      /* Manufacture date */
   CI_SERNO,                       /* serial number */
   CI_NOMBATTV,                    /* Nominal battery voltage */
   CI_HUMID,                       /* UPS Humidity percentage */
   CI_REVNO,                       /* Firmware revision */
   CI_NOMOUTV,                     /* Nominal output voltage */
   CI_Manufacturer,             
   CI_LAST                         /* MUST BE LAST */
};

#define CI_MAXCI         (CI_LAST-1)    /* maximum UPS commands we handle */

#define UPS_DETECTION_AUTO 0
#define UPS_DETECTION_ENABLE 1
#define UPS_DETECTION_DISABLE 2

#define UPS_ACTION_NONE 0
#define UPS_ACTION_SHUTDOWN 1
#define UPS_ACTION_CTRLCACHE 2
#define UPS_ACTION_LDCACHE 3
/* The order of these UpsModes is important!! */
typedef enum {
   UNKNOWN_UPS,
   USB_UPS,             /* USB UPS driver       */
   SNMP_UPS,            /* SNMP UPS driver      */
   RS232_UPS,           /* RS232 UPS driver     */
} UpsMode;

typedef struct internalgeninfo {
   char name[MAXSTRING];           /* JHNC: name mustn't contain whitespace */
   char long_name[MAXSTRING];
   int type;
} INTERNALGENINFO;                 /* for assigning into upsinfo */

/* bit values for APC UPS Status Byte (ups->Status) */
#define UPS_battlow       0x01
#define UPS_replacebatt   0x02
#define UPS_overload      0x04
#define UPS_online        0x08
#define UPS_onbatt        0x10

typedef struct upsinfo {

    u8 id;
    boolean_t present;
    u8 status;                     /* UPS status (Bitmapped) */
    boolean_t opened;

    char operational_status[32];

   /* DATA */
   //char release[20];

   //int fd;                         /* UPS device node file descriptor */

   INTERNALGENINFO mode;           /* UPSTYPE directive */

   /* Items reported by smart UPS */
   /* Volatile items -- i.e. they change with the state of the UPS */
   double BattChg;                 /* remaining UPS charge % */
   double UPSLoad;                 /* battery load percentage */ //ups0_LoadingRatio
   double UPSTemp;                 /* UPS internal temperature */ //ups0_temperature
   double TimeLeft;                /* Est. time UPS can run on batt. */ //ups0_BackupCap
   double humidity;                /* Humidity */ //not being used now

   /* Items reported by smart UPS */
   /* Static items that normally do not change during UPS operation */
   int NomOutputVoltage;           /* Nominal voltage when on batteries */ //usd_UPSVoltage
   double nombattv;                /* Nominal batt. voltage -- not actual */ //ups0_BtyVoltage
   char birth[20];                 /* manufacture date */ //ups0_FactoryDate
   char serial[32];                /* serial number */ //ups0_Serial
   char firmrev[20];               /* firmware revision */ //ups0_FWVersion
   char upsmodel[20];              /* ups model number */ //ups0_Model
   char upsname[UPSNAMELEN];       /* UPS internal name */ //not being used now

   /* Items specified from config file */
   int polltime;                   /* Time interval to poll the UPS */
   char device[MAXSTRING];         /* device name in use */

   void *driver_internal_data;     /* Driver private data */
    
   error_handler_t * pehErrorHandler;
} UPSINFO;

typedef struct
{
    u8 detection_mode; /*auto=0/enable=1/disable=2*/
    u8 num_of_ups;
    boolean_t network_configured;
    u8 current_driver;
    boolean_t daemon_mode;
    boolean_t terminate;
    u8 cache_flag;                          /* current cache policy flag */
    u8 action_mode;                         /*none=0/shutdown=1/ld_cache=2/ctrl_cache=3*/
    boolean_t need_policy;                  /* whether cache policy calculation needed */
    boolean_t is_master;                    /* indicate current controller role */
    u8 reserved[2];
    int poll_time;
    time_t last_cache_disable_time;         /* time stamp of last disable cache action */
    pthread_t event_poll_thread;
    /* Threashold settings */
    int temp_threshold;                     /* temperature threashold */
    int remaining_time_threshold;           /* remaining capacity last time threashold (in minute) */
    int loading_ratio_threashold;           /* battery loading percentage threshold */
    device_id_t device_id;
    session_id_t session_id;
    error_handler_t * pehErrorHandler;
    feature_bits_t fbFeatureBits;
    UPSINFO ups[MAX_UPS_NUMBER];
}upsd;

typedef struct 
{
    UPSINFO * info[MAX_UPS_NUMBER];
    
    /* Threashold settings */
    int tempthreshold;                    /* temperature threashold */
    int remainingtimethreshold;           /* remaining capacity last time threashold */
    int loadingratiothreshold;            /* battery load percentage */
}ups_policy_param_in_t;

typedef struct
{
    /* info for ups 0 */
    /* SW to check starting this field, info in this field is clear on every entry */
    u32 ups0_eventhappen;    /* event id is same as the event id defined in mic.h */
                             /* info is bitwised and the bit definition is offset of the event id */
    /* info for ups 1 */
    /* SW to check starting this field, info in this field is clear on every entry */
    u32 ups1_eventhappen;    /* event id is same as the event id defined in mic.h */
                             /* info is bitwised and the bit definition is offset of the event id */
    u8  PDCachePolicyflag;   /* disk cache policy event, bitwised */
                               /* BIT0 -- has triggered PD write back to enable */
                               /* BIT1 -- has triggered PD write back to disable */
    u8  LDCachePolicyflag;
                               /* BIT0 -- has triggered LD to write back */
                               /* BIT1 -- has triggered LD to write through */
}ups_policy_param_out_t;


#ifdef __cplusplus
}
#endif

#endif   /* _STRUCT_H */

/*******************************************************************************
 * Change Log
 *
 * $Log: upstypes.h,v $
 * Revision 1.1.4.4  2009/05/19 03:50:11  xinw
 * add new ups function
 *
 * Revision 1.1.4.3  2009/04/21 05:57:35  xinw
 * add action choise item
 *
 * Revision 1.1.4.2  2009/03/23 12:24:20  xinw
 * add support ups
 *
 ******************************************************************************/
