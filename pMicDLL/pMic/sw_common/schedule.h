/*******************************************************************************
 * Filename    : schedule.h
 * Description : schedule header file
 *               It provides the constant definitions, data structures and
 *               related functional routines.
 * Created on  : 06/19/03
 * CVS Version : $Id: schedule.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_SCHEDULE_H__
#define __PI_SCHEDULE_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- constant definitions & data structures ------------------------------ */

typedef struct
{
	u8 sdp_u8Interval; /* in days */
    u8 sdp_u8Reserved[3]; /* reserved for alignment */
} schedule_daily_pattern_t;

typedef struct
{
	u8 swp_u8Interval; /* in weeks */
	u8 swp_u8DayMask; /* a bitmap. Sunday:0x1, Monday:0x02, Tuesday:0x04, ... */
    u8 swp_u8Reserved[2]; /* reserved for alignment */
} schedule_weekly_pattern_t;

#define MONTHLY_DAY_PATTERN_DAY		0
#define MONTHLY_DAY_PATTERN_ORDINAL	1

#define ORDINAL_FIRST   0
#define ORDINAL_SECOND  1
#define ORDINAL_THIRD   2
#define ORDINAL_FOURTH  3
#define ORDINAL_LAST    4

typedef struct
{
	u16 smp_u16MonthMask; /* a bitmap. Jan: 0x01, Feb: 0x02, Mar: 0x04, … */
	u8 smp_u8DayPattern; /* day of month, or some specific day of week */
	u8 sm_u8Reserved; /* reserved for alignment */
    union
    {
        u8 smp_u8DayOfMonth;
        struct
        {
            u8 smp_u8Ordinal;   /* FIRST, SECOND, THIRD, FOURTH or LAST */
            u8 smp_u8DayOfWeek; /* Sunday: 0, Monday: 1, Tuesday: 2, ... */
            u8 smp_u8Reserved2[2]; /* reserved for alignment */
        } smp_sWeekDayOfMonth;
    } smp_uMonthlyRecurrentPattern;
} schedule_monthly_pattern_t;

#define SCHEDULE_RECURRENCY_DAILY   1
#define SCHEDULE_RECURRENCY_WEEKLY  2
#define SCHEDULE_RECURRENCY_MONTHLY 3

#define SCHEDULE_RANGE_END_NONE     1
#define SCHEDULE_RANGE_END_COUNT    2
#define SCHEDULE_RANGE_END_DATE     3

typedef struct
{
    /* enabled/disable */
    boolean_t s_bEnabled;
    /* recurrency. the recurrent type: ONCE, DAILY, MONTHLY or YEARLY */
    u8 s_u8Recurrency;
    
    /* 
     * start time of each of the occurrences. the number of minutes from 0:00 AM 
     * of the day 
     */
    u16 s_u16StartTime; 
    /* 
     * duration. the number of minutes from the start time, which indicates 
     * the duration of one occurence. 0 (zero) indicates that the shedule
     * is open-ended 
     */
    u32 s_u32Duration; 

     /* recurrent pattern. depending on the recurrency, the pattern is different */
    union
    {
        schedule_daily_pattern_t s_sdpDailyPattern;
        schedule_weekly_pattern_t s_swpWeeklyPattern;
        schedule_monthly_pattern_t s_smpMonthlyPattern;
    } s_uRecurrentPattern;
    
    /* range of Recurrence */
    u8 s_u8RangeEndType;
    u8 s_u8RecurrenceCount; /* valid only when RangeEndType is SCHEDULE_RANGE_END_COUNT */
    u8 s_u8Reserved[2];
    
	/* start day of range of occurrence */
    u8 s_u8DayStart;    /* day of month, range from 1 ~ 31 */
    u8 s_u8MonthStart;  /* range from 0 ~ 11 */
    u16 s_u16YearStart; /* the year since 1900 */
	/* 
     * valid only when RangeEndType is SCHEUDLE_RANGE_END_DATE
     */
    u8 s_u8DayEnd;      /* day of month, range from 1 ~ 31 */
    u8 s_u8MonthEnd;    /* range from 0 ~ 11 */
    u16 s_u16YearEnd;   /* the year since 1900 */
} schedule_t;

/* --- functional routines ------------------------------------------------- */

/***************************************************************************
* Function Name: schd_isScheduleDue 
* Description: check whether the schedule is currently due. A schedule is due,
*       when it is now within the duration of one recurrent period.
* Parameters: pSchedule, the pointer to the schedule.
* Return: TRUE: the schedule is due; FALSE: the schedule is not due. 
* Remarks: none.  
****************************************************************************/
/*boolean_t schd_isScheduleDue(schedule_t * pSchedule);*/

#endif /*__PI_SCHEDULE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: schedule.h,v $
 * Revision 1.3  2003/07/19 02:43:03  weny
 * cover the range of recurrence end in # times
 *
 * Revision 1.2  2003/07/01 03:32:27  wenyis
 * Ordinal constants are changed for the sequence of GUI
 *
 * Revision 1.1  2003/06/28 05:41:52  weny
 * add for bga scheduler
 *
 ******************************************************************************/
