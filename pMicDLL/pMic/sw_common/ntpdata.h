/*******************************************************************************
 * Filename    : ntpdata.h
 * Description : ntp data header file
 *               Shared ntp information data strcture
 * Created on  : 01/19/09
 *
 * (C) Copyright Promise Technology Inc., 2009
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __NTPDATA_H__
#define __NTPDATA_H__

#include "pibasic.h"

/* --- constants & data structures ------------------------------------------ */


#define NTP_CONF_FILE_NAME "ntp.conf"
#define NTP_CONF_BACKUP_FILE_NAME "/etc/ntp.conf"
#define MAX_TIME_SERVER_COUNT 3
#define MAX_TIME_SERVER_NAME_LENGTH 64

typedef struct
{
    u8 nw_u8Month; //Jan 0, Feb 1
    u8 nw_u8WeekOfMonth; //FIRST 0, SECOND 1, THIRD 2, FOURTH 3 or LAST 4
    u8 nw_u8DayOfWeek; //Sunday: 0, Monday: 1, Tuesday: 2, ...
    u8 nw_u8Reserved; //reserved for alignment
} dst_WeekDayOfMonth_t;

#endif /* __NTPDATA_H__ */



