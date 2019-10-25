/*******************************************************************************
 * Filename    : evtlogdata.h
 * Description : event logger data header file
 *               * Shared event logger related data strcture
 * Created on  : 07/19/06
 * CVS Version : $Id: evtlogdata.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2006
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __EVTLOGDATA_H__
#define __EVTLOGDATA_H__

#include "pibasic.h"

#define EVTLOG_FILTER_TYPE_SEV_CLASS 1
#define EVTLOG_FILTER_TYPE_EVT_ID 2

#define EVTLOG_LOCATION_NONE                    0x0
#define EVTLOG_LOCATION_SYSTEM_LOGGER           0x1
#define EVTLOG_LOCATION_FILE                    0x2
#define EVTLOG_LOCATION_CONSOLE                 0x4
#define EVTLOG_LOCATION_REMOTE                  0x8

#define EVTLOG_SEVERITY_NONE                    0xFF
#define EVTLOG_SEVERITY_MIN                     0x2
#define EVTLOG_SEVERITY_MAX                     0x7

#define EVTLOG_SEVERITY_UNKNOWN                 0x0
#define EVTLOG_SEVERITY_OTHER                   0x1
#define EVTLOG_SEVERITY_INFO                    0x2
#define EVTLOG_SEVERITY_WARNING                 0x3
#define EVTLOG_SEVERITY_MINOR                   0x4
#define EVTLOG_SEVERITY_MAJOR                   0x5
#define EVTLOG_SEVERITY_CRITICAL                0x6
#define EVTLOG_SEVERITY_FATAL                   0x7

#define EVTLOG_MAX_SOURCE_NAME_LENGTH           32
#define EVTLOG_MAX_DEVICES                      20

#define EVTLOG_DEFAULT_SOURCE_NAME          "Promise Event Logger" 

typedef struct
{
    u8 edc_u8WWN[20];
    u8 edc_u8SourceName[EVTLOG_MAX_SOURCE_NAME_LENGTH];
    u32 edc_u8LogLocation;
    u8 edc_u8FileName[MAX_PATH_LENGTH + 1];
    u64 edc_u64MaxFileSize;
    u32 edc_u32SyncInterval;
    u8 edc_u8FilterLevel;
    u8 edc_u8PollingInterval; /* At least 17 seconds */
    u8 edc_u8SyncTime;
    u8 edc_u8Reserved1[1];
    u8 edc_u8Reserved2[64];
} evtlog_device_config_t;

typedef struct
{
    u8 ec_u8NumOfConfig;
    u8 ec_u8Reserved1[3];
    u32 ec_u32LocationMask;
    u8 es_u8Reserved2[32];
    evtlog_device_config_t ec_edcDefault;
    evtlog_device_config_t ec_edcConfigs[EVTLOG_MAX_DEVICES];
} evtlog_config_t;

#endif /* __EVTLOGDATA_H__ */

/*******************************************************************************
 * Change Log
 *
 * $Log: evtlogdata.h,v $
 * Revision 1.3  2007/04/25 06:30:35  theoz
 * EventLog improvement:
 * 1. Add 2 configuration item ¡°syncInterval¡± and ¡°syncTime¡± in
 *    evtlogsetting_NEC.xml .
 * 2. Change the first 2 bits of Windows event id as the event severity.
 *
 * Revision 1.2  2007/01/10 02:48:49  danielz
 * default source name
 *
 * Revision 1.1  2006/08/21 10:43:40  danielz
 * event logger header files
 *
 ******************************************************************************/



