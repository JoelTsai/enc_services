/*******************************************************************************
 * Filename    : bgaschd.h
 * Description : bga schedule header file
 *               It provides the constant definitions, data structures and
 *               related functional routines.
 * Created on  : 06/19/03
 * CVS Version : $Id: bgaschd.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_BGASCHEDULE_H__
#define __PI_BGASCHEDULE_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "schedule.h"
#include "i2limit.h"
#include "errorlog.h"
/* --- constant definitions & data structures ------------------------------ */

#define BGAS_TYPE_MP    0
#define BGAS_TYPE_RC    1
#define BGAS_TYPE_BRC   2
#define BGAS_TYPE_SC    3
#define BGAS_TYPE_PS_ON    4
#define BGAS_TYPE_PS_OFF   5
#define BGAS_TYPE_NTP   7
#define BGAS_TYPE_ALL   0xFF

typedef struct
{
	u8 bs_u8BgaType; /* BGAS_TYPE_MP or BGAS_TYPE_RC */
	u8 bs_u8SeqNum; /* MP and RC schedule have their own independent sequence numbers */
	u8 bs_u8Reserved[6]; /* reserved for alignment */ 
	schedule_t bs_sSchedule;
} bga_schedule_t;

typedef struct
{
    bga_schedule_t mps_bsSchedule;
} mp_schedule_t;

typedef struct
{
    bga_schedule_t rcs_bsSchedule;
	boolean_t rcs_bFix; /* to fix or not to fix */  
	boolean_t rcs_bPause;   /* to pause or not to pause on error */
	u16 rcs_u16NumberOfDevices; /* max is MAX_LOGICAL_DRIVES. If it 0, it means all logical drives */
	u16 rcs_u16DeviceIds[2];
} rc_schedule_t;

typedef struct
{
    bga_schedule_t brcs_bsSchedule;
} brc_schedule_t;
 
typedef struct
{
    bga_schedule_t ss_bsSchedule;
} sc_schedule_t; 

 typedef struct
{
    bga_schedule_t pss_bsSchedule;
} ps_schedule_t;

typedef struct
{
    bga_schedule_t ntps_bsSchedule;
} ntp_schedule_t;

#define BGAS_OPSTATUS_NEW       0 /* the schedule is newly added/updated */
#define BGAS_OPSTATUS_PENDING   1 /* the bga schedule is pending for execution */
#define BGAS_OPSTATUS_RUNNING   2 /* the schedule is currently running */
#define SCHD_SEQNUM_AUTO  0xFF  /* auto seq num */ 
#define RC_SCHEDULE_SIZE(numOfDev) \
(((numOfDev) <= 2)?\
(sizeof(rc_schedule_t)):\
(sizeof(rc_schedule_t) + (((numOfDev)-2) * sizeof(u16))))
    
typedef struct
{
#ifndef EMBEDDED
    u8 bs_u8WWN[32];
#endif
	u8 bs_u8CurrentMPSchedules; /* READ ONLY */
	u8 bs_u8CurrentRCSchedules; /* READ ONLY */
    u8 bs_u8CurrentBRCSchedules; /* READ ONLY */
    u8 bs_u8CurrentSCSchedules; /* READ ONLY */
    u8 bs_u8CurrentPSOnSchedules; /* READ ONLY */
    u8 bs_u8CurrentPSOffSchedules; /* READ ONLY */
    u8 bs_u8CurrentNTPSchedules; /* READ ONLY */
	u8 bs_u8MaxMPScheudles; /* READ ONLY */
	u8 bs_u8MaxRCSchedules; /* READ ONLY */
    u8 bs_u8MaxBRCSchedules; /* READ ONLY */
    u8 bs_u8MaxSCSchedules; /* READ ONLY */
    u8 bs_u8MaxPSSchedules; /* READ ONLY */
    u8 bs_u8MaxNTPSchedules; /* READ ONLY */
	u8 bs_u8NumberOfMPSchedules;  /* number of MP schedules in the bs_bsSchedules */
	u8 bs_u8NumberOfRCSchedules;  /* number of RC schedules in the bs_bsSchedules */
    u8 bs_u8NumberOfBRCSchedules;  /* number of BRC schedules in the bs_bsSchedules */
    u8 bs_u8NumberOfSCSchedules;  /* number of SC schedules in the bs_bsSchedules */
    u8 bs_u8NumberOfPSOnSchedules;  /* number of SC schedules in the bs_bsSchedules */
    u8 bs_u8NumberOfPSOffSchedules;  /* number of SC schedules in the bs_bsSchedules */
    u8 bs_u8NumberOfNTPSchedules;  /* number of NTP schedules in the bs_bsSchedules */
    u8 bs_u8Reserved[4]; /* reserved for alignment */
	bga_schedule_t bs_bsSchedules[1]; /*number of MP schedules followed by number of RC schedules*/
} bga_schedules_t;

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: bgaschd_locateNextSchedule 
* Description: locate the next schedule in the buffer after the pointer
*       specified by the index
* Parameters:    
*   	[in] pBuf, the buffer of the schedules
*       [in] u32Size, the size of the buffer
*       [in] u32Index, the index, specifying the pointer
*       [out] pbs, the schedule to be returned 
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: none.     
****************************************************************************/
u32 bgaschd_locateNextSchedule(bga_schedules_t * pBuf, u32 u32Size, u32 u32Index, 
    bga_schedule_t ** ppbs);

#endif /*__PI_BGASCHEDULE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: bgaschd.h,v $
 * Revision 1.13.42.2  2009/11/20 09:22:10  xinw
 * add ntp support
 *
 * Revision 1.13.42.1  2008/12/02 06:54:11  xinw
 * add power schedule support
 *
 * Revision 1.13  2006/08/22 10:19:54  fieldsy
 * InBand BGA Support
 *
 * Revision 1.12  2004/07/06 23:10:38  weny
 * remove unnecessary includes from API header files
 *
 * Revision 1.11  2004/06/28 23:42:24  debinc
 * 8 bytes aligned
 *
 * Revision 1.10  2004/06/12 00:58:39  debinc
 * move bga setting save/restore data structure out of API code
 *
 * Revision 1.9  2004/06/11 23:19:28  debinc
 * seperate code from I2
 *
 * Revision 1.8  2004/04/29 21:33:47  debinc
 * fix in-band build error
 *
 * Revision 1.7  2004/04/29 01:03:43  debinc
 * separate bga scheduler to a standalone daemon
 *
 * Revision 1.6  2004/03/26 00:12:16  debinc
 * Add support for bga spare check
 *
 * Revision 1.5  2004/03/24 03:26:13  weny
 * I2 API porting
 *
 * Revision 1.4  2004/03/11 00:03:07  debinc
 * Add battery conditioning support
 *
 * Revision 1.3  2003/09/19 00:45:29  debinc
 * Add data structure
 *
 * Revision 1.2  2003/09/17 01:47:21  debinc
 * New data strcuture needed to save/restore to flash
 *
 * Revision 1.1  2003/06/28 05:41:52  weny
 * add for bga scheduler
 *
 ******************************************************************************/
