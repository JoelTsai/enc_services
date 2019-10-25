/*******************************************************************************
 * Filename    : swsetting.h
 * Description : sw xml setting header file
 * Created on  : 06/08/04
 * CVS Version : $Id: swsetting.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/
 
#ifndef __SWSETTING_H__
#define __SWSETTING_H__

#include "pibasic.h"
#include "bgaschd.h"
#include "swmgt.h"
#if defined(EMBEDDED)
#include "emaildata.h"
#include "userdata.h"
#else //  ! defined(EMBEDDED)
#include "evtlogdata.h"

#undef SWSETTINGAPI
#undef SWSETTINGCALL
#ifdef WINDOWS
    #include "windows.h"
    #if defined(PROMISE_SWSETTING_DLL)
        #define SWSETTINGAPI  __declspec(dllexport)
        #define SWSETTINGCALL
    #else
        #define SWSETTINGAPI
        #define SWSETTINGCALL __cdecl
    #endif
#else
	#define SWSETTINGAPI
	#define SWSETTINGCALL
#endif

#endif // end defined(EMBEDDED)

/* --- internal header files ----------------------------------------------- */

#if defined(EMBEDDED)

typedef struct
{
    email_config_t es_ecConfig;
    u8 es_u8Version[8];
    u8 es_u8Reserved2[64];
} email_setting_t;

typedef struct
{
    boolean_t ud_bOutsideDB;
    boolean_t ud_bPwdEncrpted;
    u8 ud_u8MaxUser;
    u8 ud_u8Reserved[4];
    u64 ud_u64LastUpdateTime;
    u8 ud_u8EncrptionKey[40];
    user_list_t ud_tUserList;
    u8 ud_u8Version[8];
} user_db_t;
#endif // ! defined(EMBEDDED)

//following two structures are for save bga setting to flash
typedef struct
{
    bga_schedule_t rcs_bsSchedule;
    boolean_t rcs_bFix; /* to fix or not to fix */
    boolean_t rcs_bPause;   /* to pause or not to pause on error */
    u16 rcs_u16NumberOfDevices; /* max is MAX_LOGICAL_DRIVES. If it 0, it means all logical drives */
    u16 rcs_u16DeviceIds[MAX_LOGICAL_DRIVES];
} rc_schedule_setting_t;

#define MAX_NUM_RC_SCHD 4
typedef struct
{
#ifndef EMBEDDED
    u8 bss_u8WWN[32];
#endif
    u8 bss_u8MaxMPScheudles; /* READ ONLY */
    u8 bss_u8MaxRCSchedules; /* READ ONLY */
    u8 bss_u8MaxBRCSchedules; /* READ ONLY */
    u8 bss_u8MaxSCSchedules; /* READ ONLY */
    u8 bss_u8MaxPSOnSchedules; /* READ ONLY */
    u8 bss_u8MaxPSOffSchedules; /* READ ONLY */
    u8 bss_u8MaxNTPSchedules; /* READ ONLY */
    u8 bss_u8NumberOfMPSchedules;  /* number of MP schedules in the bs_bsSchedules */
    u8 bss_u8NumberOfRCSchedules;  /* number of RC schedules in the bs_bsSchedules */
    u8 bss_u8NumberOfBRCSchedules;  /* number of BRC schedules in the bs_bsSchedules */
    u8 bss_u8NumberOfSCSchedules;  /* number of SC schedules in the bs_bsSchedules */
    u8 bss_u8NumberOfPSOnSchedules;  /* number of PS schedules in the bs_bsSchedules */
    u8 bss_u8NumberOfPSOffSchedules;  /* number of PS schedules in the bs_bsSchedules */
    u8 bss_u8NumberOfNTPSchedules;  /* number of NTP schedules in the bs_bsSchedules */
    mp_schedule_t  bss_msMPSchedules;
    brc_schedule_t  bss_bsBRCSchedules;
    sc_schedule_t  bss_ssSCSchedules;
    rc_schedule_setting_t  bss_baRCSchedules[MAX_NUM_RC_SCHD];
    ps_schedule_t  bss_pssPSOnSchedules;
    ps_schedule_t  bss_pssPSOffSchedules;
    ntp_schedule_t  bss_nsNTPSchedules;
    u8 bss_u8Version[8];
} bga_schedules_setting_t;

u32 readSwmgt(const char * pstrSwmgtXmlFileName, swmgt_setting_t * pud);
u32 writeSwmgt(const char * pstrSwmgtXmlFileName, u8 * pDaemonName, u8 daemonStartupType);
#ifdef EMBEDDED

u32 readEmailSetting(email_setting_t * pes);
u32 writeEmailSetting(email_setting_t *pes);

u32 writeUserdb(user_db_t *pud);
u32 createUserdb(user_db_t * pud, boolean_t *bFirstTime);
u32 readUserdb(user_db_t * pud, char * pFile);
#endif

u32 writeBGASchdSetting(bga_schedules_setting_t *pbss);
u32 readBGASchdSetting(bga_schedules_setting_t * pbss);

#ifndef EMBEDDED
typedef struct
{
    evtlog_config_t es_ecConfig;
    u8 es_u8Version[8];
    u8 es_u8Reserved2[64];
} evtlog_setting_t;

SWSETTINGAPI u32 SWSETTINGCALL readEvtlogSetting(evtlog_setting_t * pes);
SWSETTINGAPI u32 SWSETTINGCALL writeEvtlogSetting(evtlog_setting_t * pes);
#endif


#endif /* __SWSETTING_H__ */
/*******************************************************************************
 * Change Log
 *
 * $Log: swsetting.h,v $
 * Revision 1.11.42.2  2009/11/20 09:22:11  xinw
 * add ntp support
 *
 * Revision 1.11.42.1  2008/12/02 06:53:15  xinw
 * add power schedule support
 *
 * Revision 1.11  2006/10/23 10:02:16  michaell
 * swmgt linux in-band support
 *
 * Revision 1.10  2006/09/11 02:07:19  weny
 * enable swmgt routines to take swmgt xml file path as parameter
 *
 * Revision 1.9  2006/08/22 10:18:22  fieldsy
 * InBand Support
 *
 * Revision 1.8  2006/08/22 06:15:42  fieldsy
 * InBand BGA support
 *
 * Revision 1.7  2006/08/21 10:37:37  danielz
 * Add evtlog setting
 *
 * Revision 1.6  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.5  2004/08/06 21:38:58  debinc
 * create email_setting_t
 *
 * Revision 1.4  2004/08/05 19:02:21  debinc
 * version stamp setting file
 *
 * Revision 1.3  2004/06/15 01:22:27  debinc
 * MAX RC is 4
 *
 * Revision 1.2  2004/06/12 00:59:14  debinc
 * move setting save/restore data structure out of API code
 *
 * Revision 1.1  2004/06/10 00:02:33  debinc
 * replace tinyXML with libxml2
 *
 *******************************************************************************/



