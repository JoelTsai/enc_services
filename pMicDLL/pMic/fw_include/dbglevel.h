/***************************************************************
 *
 * Filename    : dbglevel.h
 * Description : Contains defines for Debug Level Control
 * Created on  : 16th Jan 2004
 * CVS Version : $Id: dbglevel.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ****************************************************************/
#ifndef DBGLEVEL_H
#define DBGLEVEL_H

/* Sev Level */
//#define SEV_LEVEL_DEBUG   1      - Disabled temporarly
#define SEV_LEVEL_INFO    2
#define SEV_LEVEL_WARNING 3
#define SEV_LEVEL_ERROR   4
#define SEV_LEVEL_FATAL   5
#define SEV_LEVEL_SILENT  6

#define MAX_SEV_LEVEL     6  


/* Module ID */
#define MAX_FW_MODULES      64

#define MAIN_MID    0x0000000000000001ULL   /* Main */
#define MS_MID      0x0000000000000002ULL   /* Main Scheduler */
#define HCP_MID     0x0000000000000004ULL   /* Host Command Processor */
#define RMM_MID     0x0000000000000008ULL   /* Raid Memory Module */

#define MGT_MID     0x0000000000000010ULL   /* Management API Library */
#define MIGRAT_MID  0x0000000000000020ULL   /* Migration */
#define BEM_MID     0x0000000000000040ULL   /* Back End Manager */
#define DISC_MID    0x0000000000000080ULL   /* Discovery */

#define PT_MID      0x0000000000000100ULL   /* Pass Through Command */
#define LDI_MID     0x0000000000000200ULL   /* Logical drive initialization */
#define PDNEG_MID   0x0000000000000400ULL   /* Drive parameter negotiation */ 
#define COER_MID    0x0000000000000800ULL   /* Coercion */

#define ENC_MID     0x0000000000001000ULL   /* Enclosure */
#define I2C_MID     0x0000000000002000ULL   /* I2C */
#define DDF_MID     0x0000000000004000ULL   /* DDF  */
#define RWP_MID     0x0000000000008000ULL   /* Read/Write Processor */

#define WBM_MID     0x0000000000010000ULL   /* Write Back Manager */
#define CM_MID      0x0000000000020000ULL   /* Cacke Manager */
#define XM_MID      0x0000000000040000ULL   /* XOR Manager */
#define LM_MID      0x0000000000080000ULL   /* Lock Manager */

#define BEML_MID    0x0000000000100000ULL   /* General Marvell debugging msgs. */
#define BEELVT_MID  0x0000000000200000ULL   /* Elevator sorting (sata) */
#define BEBBM_MID   0x0000000000400000ULL   /* Bad Block Management (sata) */
#define BEEIJ_MID   0x0000000000800000ULL   /* Error InIection (sata) */

#define BEMSG_MID   0x0000000001000000ULL   /* General Backend Module */
#define RCM_MID     0x0000000002000000ULL   /* RCM */  
#define ISCSIM_MID  0x0000000004000000ULL   /* ISCSI Management */  
#define ISNSC_MID   0x0000000008000000ULL   /* ISNS Client */

#define ISPM_MID    0x0000000010000000ULL   /* ISP Management */
#define ISP_MID     0x0000000020000000ULL   /* ISP Core Driver */
#define IFD_MID     0x0000000040000000ULL   /* ISCSI Filter Driver*/
#define RBLD_MID    0x0000000080000000ULL   /* Rebuild */

#define BGSYNC_MID  0x0000000100000000ULL   /* Background synchronization */
#define REDCHK_MID  0x0000000200000000ULL   /* Redundancy Check */
#define MEDPAT_MID  0x0000000400000000ULL   /* Media Patrol */
#define SCSIEM_MID  0x0000000800000000ULL   /* Scsi Emulation */

#define WTRMRK_MID  0x0000001000000000ULL   /* Water Mark Manager */ 
#define EVT_MID     0x0000002000000000ULL   /* Event Logging */
#define BUZZ_MID    0x0000004000000000ULL   /* Buzzer */
#define KFS_MID     0x0000008000000000ULL   /* Kernel File System */

#define BGINTR_MID  0x0000010000000000ULL   /* Bbackground Task Interface module */
#define BGERR_MID   0x0000020000000000ULL   /* Background Task Error Recovery Handler module */
#define CTL_MID     0x0000040000000000ULL   /* Background Task Error Recovery Handler module */
#define STATS_MID   0x0000080000000000ULL   /* Statistics Monitoring */
#define SMART_MID   0x0000100000000000ULL   /* SMART Monitoring (raid core) */
#define BBMRC_MID   0x0000200000000000ULL   /* Bad Block Manager (raid core) */

#define FMU_MID     0x0000400000000000ULL   /* FMU driver */
#define SAS_MID     0x0000800000000000ULL   /* SAS Topology related*/

#define ALL_MID     0xFFFFFFFFFFFFFFFFULL

/* Module Index */
#define MAIN_MOD_INDX           0
#define MS_MOD_INDX             1
#define HCP_MOD_INDX            2
#define RMM_MOD_INDX            3

#define MGT_MOD_INDX            4
#define MIGRAT_MOD_INDX         5
#define BEM_MOD_INDX            6
#define DISC_MOD_INDX           7

#define PT_MOD_INDX             8
#define LDI_MOD_INDX            9
#define PDNEG_MOD_INDX         10
#define COER_MOD_INDX          11

#define ENC_MOD_INDX           12
#define I2C_MOD_INDX           13
#define DDF_MOD_INDX           14
#define RWP_MOD_INDX           15      

#define WBM_MOD_INDX           16
#define CM_MOD_INDX            17
#define XM_MOD_INDX            18
#define LM_MOD_INDX            19

#define BEML_MOD_INDX          20 
#define BEELVT_MOD_INDX        21
#define BEBBM_MOD_INDX         22
#define BEEIJ_MOD_INDX         23

#define BEMSG_MOD_INDX         24
#define RCM_MOD_INDX           25
#define ISCSIM_MOD_INDX        26
#define ISNSC_MOD_INDX         27

#define ISPM_MOD_INDX          28
#define ISP_MOD_INDX           29
#define IFD_MOD_INDX           30
#define RBLD_MOD_INDX          31

#define BGSYNC_MOD_INDX        32
#define REDCHK_MOD_INDX        33
#define MEDPAT_MOD_INDX        34
#define SCSIEM_MOD_INDX        35

#define WTRMRK_MOD_INDX        36
#define EVT_MOD_INDX           37
#define BUZZ_MOD_INDX          38
#define KFS_MOD_INDX           39

#define BGINTR_MOD_INDX        40 
#define BGERR_MOD_INDX         41
#define CTL_MOD_INDX           42
#define STATS_MOD_INDX         43
#define SMART_MOD_INDX         44
#define BBMRC_MOD_INDX         45
#define FMU_MOD_INDX           46
#define SAS_MOD_INDX           47


/* Macro Start */
#define PROM_CONV_TO_STR(s)      #s
#define PROM_CONV_TO_LVLID(x)    PROM_TO_NOS(SEV_LEVEL_##x)
#define PROM_CONV_TO_NOS(x)      PROM_TO_NOS(x##_MID)
#define PROM_CONV_TO_MODINDX(x)  PROM_TO_NOS(x##_MOD_INDX)
#define PROM_TO_NOS(x)           x


#define PRO_PRINT(Mod,SevLvl,fmt,args...)                                               (\
{                                                                                       \
    if ((PROM_CONV_TO_NOS(Mod) & gModuleDebugFlag) &&                                   \
        ((PROM_CONV_TO_LVLID(SevLvl) >= gGlobalSevLevel) ||                             \
         (PROM_CONV_TO_LVLID(SevLvl) >= gModuleSevLevel[PROM_CONV_TO_MODINDX(Mod)])))   \
    {                                                                                   \
        printk(KERN_ALERT "%-7s: %-6s - "fmt, PROM_CONV_TO_STR(SevLvl), PROM_CONV_TO_STR(Mod), ##args);\
    }                                                                                   \
})


/* Externs defined */
extern u64 gModuleDebugFlag;
extern u16 gGlobalSevLevel;
extern u16 gModuleSevLevel[64];

#endif //DBGLEVEL_H
/***************************************************************
 * Change Log
 *
 * $Log: dbglevel.h,v $
 * Revision 1.3.2.4  2006/05/12 09:33:11  haipao.fan
 * Support topology mic command (virtual enclosure).
 *
 * Revision 1.3.2.3  2005/09/13 05:40:57  haipao.fan
 * Merged SAS code (with Intel ISC813XX back-end driver).
 *
 * Revision 1.3.2.2  2005/03/09 02:20:40  manojm
 * Print when boot from flash when appropriate debug level is set
 *
 * Revision 1.3.2.1  2005/03/08 21:58:12  manojm
 * Print when boot from flash when appropriate debug level is set
 *
 * Revision 1.3  2004/10/29 23:54:17  randallc
 * added mic support for obtaining the bbm defect list from the backend driver
 *
 * Revision 1.2  2004/08/27 16:58:34  randallc
 * added smart polling for pds
 *
 * Revision 1.1.1.1  2004/05/11 00:22:39  randallc
 * Temporary IslaVista Timesys Port
 *
 * Revision 1.10  2004/04/06 18:47:02  randallc
 * added '(' and ')' to PRO_PRINT macros.  Causing issues when using if
 * statement without curly braces.
 *
 * Revision 1.9  2004/03/08 22:50:21  randallc
 * Added support for statistics monitoring.  Support for only retriving values
 * from fw via mic commands is there, however, valid values are not currently
 * returned.  Done so software can continue development.
 *
 * Revision 1.8  2004/02/17 18:51:35  manojm
 * Add CTL Debug Module ID
 *
 * Revision 1.7  2004/02/02 18:56:28  manojm
 * Added Module ID for BGT
 *
 * Revision 1.6  2004/01/27 21:42:44  manojm
 * Changed #define MGTAPI to MGT
 *
 * Revision 1.5  2004/01/21 19:57:09  manojm
 * Some more Debug Log Module ID added
 *
 * Revision 1.4  2004/01/21 19:01:55  manojm
 * Several Debug Log Module ID added
 *
 * Revision 1.3  2004/01/21 01:13:02  manojm
 * Added ModuleID for Backend/FrontEnd and RCM module
 *
 * Revision 1.2  2004/01/20 16:55:53  manojm
 * Disabled DEBUG level temporarly
 *
 * Revision 1.1  2004/01/20 01:11:25  manojm
 * Debug Logging level code
 *
 *
 ****************************************************************/






