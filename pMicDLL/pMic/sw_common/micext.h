/*******************************************************************************
 * Filename    : micext.h
 * Description : promise MIC Extension header file
 *               It provides the extened definitions to the MIC.
 * Created on  : 03/09/03
 * CVS Version : $Id: micext.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2004
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_MICEXT_H__
#define __PI_MICEXT_H__

/* --- standard C lib header files ------------------------------------------ */
#include "pibasic.h"
#include "mic.h"

/* --- internal header files ------------------------------------------------ */

/* --- constants & data structures ------------------------------------------ */
#define INVALID_CTRL_ID 0xFFFFFFFF
#define INVALID_PORT_ID 0xFFFFFFFF
#define INVALID_TARGET_ID 0xFFFFFFFF
#define INVALID_ARRAY_ID 0xFFFFFFFF
#define INVALID_PHYDRV_ID 0xFFFFFFFF
#define INVALID_LOGDRV_ID 0xFFFFFFFF
#define INVALID_ENCL_ID 0xFFFFFFFF
#define INVALID_SLOT_ID 0xFFFFFFFF
#define INVALID_SEQUENCE_NUMBER 0xFFFFFFFF
#define INVALID_FSH_HANDLE 0xFFFFFFFF
#define INVALID_RAID_LEVEL 0xFFFF
#define INVALID_STRIPE_SIZE 0xFFFFFFFF
#define INVALID_BATTERY_ID 0xFFFF
#ifdef WINDOWS
    #define INVALID_CAPACITY 0xFFFFFFFFFFFFFFFFi64
#else
    #define INVALID_CAPACITY 0xFFFFFFFFFFFFFFFFLL
#endif
#define INVALID_INITIATOR_INDEX 0xFFFF

/* device flag */
#define DEVICE_STATE_MASK       0xFF000000
#define DEVICE_COND_MASK        0x00FF0000
#define DEVICE_OPERATION_MASK   0x0000FF00
#define DEVICE_CONFIG_MASK      0x000000FF

/* physical drive flag */
#define PHYDRV_STATE_MASK           DEVICE_STATE_MASK
#define PHYDRV_STATE_FLAG(u32Flag)  (u32Flag & PHYDRV_STATE_MASK)
#define PHYDRV_STATE_ONLINE         0x01000000
#define PHYDRV_STATE_MISSING        0x02000000
#define PHYDRV_STATE_REBUILD        0x08000000

#define PHYDRV_COND_MASK            DEVICE_COND_MASK
#define PHYDRV_COND_FLAG(u32Flag)   (u32Flag & PHYDRV_COND_MASK)
#define PHYDRV_COND_PFA             0x00020000
#define PHYDRV_COND_FORCED          0x00040000
#define PHYDRV_COND_TEMP            0x00080000
#define PHYDRV_COND_TEMPSPARE       0x00100000
#define PHYDRV_COND_PRESENT         0x00200000
#define PHYDRV_COND_ACCESSIBLE      0x00400000

/* Physical drive operation flags shares the same value space with the logical drive operation flags */
/* Physical drive and logical drive operation flags must be consistent and have no conflict */
#define PHYDRV_OPERATION_MASK           DEVICE_OPERATION_MASK
#define PHYDRV_OPERATION_FLAG(u32Flag)  (u32Flag & PHYDRV_OPERATION_MASK)
#define PHYDRV_OPERATION_INITIALIZING   0x00000400
#define PHYDRV_OPERATION_MP             0x00000500
#define PHYDRV_OPERATION_SYNCHRONIZING  0x00000600
#define PHYDRV_OPERATION_TRANSITION     0x00000700
#define PHYDRV_OPERATION_MIGRATION      0x00000800
#define PHYDRV_OPERATION_PDM            0x00000900

#define PHYDRV_CONFIG_MASK              DEVICE_CONFIG_MASK
#define PHYDRV_CONFIG_FLAG(u32Flag)     (u32Flag & PHYDRV_CONFIG_MASK)
#define PHYDRV_CONFIG_UNCONFIGURED      0x00000000
#define PHYDRV_CONFIG_CONFIGURED        0x00000001
#define PHYDRV_CONFIG_GLOBALSPARE       0x00000002
#define PHYDRV_CONFIG_DEDICATEDSPARE    0x00000004
#define PHYDRV_CONFIG_STALE             0x00000008
#define PHYDRV_CONFIG_PASSTHRU          0x00000010

/* logical drive flag */
#define LOGDRV_STATE_MASK           DEVICE_STATE_MASK
#define LOGDRV_STATE_FLAG(u32Flag)  (u32Flag & LOGDRV_STATE_MASK)
#define LOGDRV_STATE_ONLINE         0x01000000
#define LOGDRV_STATE_CRITICAL       0x02000000
#define LOGDRV_STATE_DEGRADED       0x04000000

#define LOGDRV_COND_MASK            DEVICE_COND_MASK
#define LOGDRV_COND_FLAG(u32Flag)   (u32Flag & LOGDRV_COND_MASK)
#define LOGDRV_COND_INITIALIZED     0x00010000
#define LOGDRV_COND_PFA             0x00020000
#define LOGDRV_COND_SYNCHRONIZED    0x00040000
#define LOGDRV_MIGRATION_NVWM_MISSING   0x00080000
#define LOGDRV_COND_TRANSPORT_READY 0x00100000
#define LOGDRV_COND_SYNC_FORCED     0x00200000

/* Logical drive operation flags shares the same value space with the physical drive operation flags */
/* Physical drive and logical drive operation flags must be consistent and have no conflict */
#define LOGDRV_OPERATION_MASK           DEVICE_OPERATION_MASK
#define LOGDRV_OPERATION_FLAG(u32Flag)  (u32Flag & LOGDRV_OPERATION_MASK)
#define LOGDRV_OPERATION_IDEL           0x00000000
#define LOGDRV_OPERATION_REBUILDING     0x00000100
#define LOGDRV_OPERATION_INITIALIZING   0x00000400
#define LOGDRV_OPERATION_REDCHECKING    0x00000500
#define LOGDRV_OPERATION_SYNCHRONIZING  0x00000600
#define LOGDRV_OPERATION_MIGRATING      0x00000800

#define LOGDRV_CONFIG_MASK          DEVICE_CONFIG_MASK
#define LOGDRV_CONFIG_FLAG(u32Flag) (u32Flag & LOGDRV_CONFIG_MASK)
#define LOGDRV_CONFIG_CONFIGURED    0x00000001

/* logical drive attributes */
#define LOGDRV_ATTRIB_WRITE_THRU    0x0
#define LOGDRV_ATTRIB_WRITE_BACK    0x00000001
#define LOGDRV_ATTRIB_READ_CACHE    0x0
#define LOGDRV_ATTRIB_READ_AHEAD    0x00000002
#define LOGDRV_ATTRIB_NOCACHE       0x00000004
#define LOGDRV_ATTRIB_LA_ENABLE     0x00000008
#define LOGDRV_ATTRIB_CURRENT_WRITE_THRU    0x0
#define LOGDRV_ATTRIB_CURRENT_WRITE_BACK    0x00000010
#define LOGDRV_ATTRIB_ALUA_ENABLE   0x00000020

/* disk array attributes */
#define ARRAY_ATTRIB_DATA_ARRAY   0x00000001
#define ARRAY_ATTRIB_DSPARE_ARRAY 0x00000002
#define ARRAY_ATTRIB_GSPARE_ARRAY 0x00000003

/* disk array flags */
#define ARRAY_FLAG_RO_MASK           0x0000FFFF
#define ARRAY_FLAG_RW_MASK           0xFFFF0000

/* disk array flags - read only */
#define ARRAY_FLAG_UPDATE_PENDING               0x00000001
#define ARRAY_FLAG_UPDATE_IN_PROGRESS           0x00000002
#define ARRAY_FLAG_LASTUPDATE_FAILED            0x00000004
#define ARRAY_FLAG_PRESENT                      0x00000010
#define ARRAY_FLAG_DRIVES_MISSING_FROM_ARRAY    0x00000020
#define ARRAY_FLAG_ARRAY_INCOMPLETE             0x00000040
#define ARRAY_FLAG_MIGRATION_RUNNING            0x00000080
#define ARRAY_FLAG_TRANSITION_RUNNING           0x00000100
#define ARRAY_FLAG_PDM_RUNNING                  0x00000200
#define ARRAY_FLAG_SPARE_CHECK_RUNNING          0x00000400
#define ARRAY_FLAG_MIG_NV_WM_MISSING            0x00000800
#define ARRAY_FLAG_TRANSPORT_READY              0x00001000

/* disk array flags - r/w */
#define ARRAY_FLAG_MP_ENABLE         0x00010000
#define ARRAY_FLAG_TEMP_SPARE        0x00020000
#define ARRAY_FLAG_PDM_ENABLE        0x00040000

/* TBD */
#define SECTOR_SIZE 512

/* TBD */
#define RAID0     0x0000
#define RAID1     0x0001
#define RAID3     0x0003
#define RAID5     0x0005
    /*raid6*/
#define RAID6     0x0006
#define RAID60    0x0060            
#define JBOD      0x000A
#define JBOD_MDD  0x000B
#define RAID10    0x0010
#define RAID50    0x0050
#define RAID51    0x0051
#define RAID55    0x0055
#define RAID01    0x005F
#define RAID30    0x0030
/* the following two raid levels are for s/w use only */
#define RAID_ALL   0xFFFF
#define RAID_UNKNOWN     0xFFFFFFFF

/* statistics type */
#define STATS_TYPE_ALL     0
#define STATS_TYPE_CTRL    1
#define STATS_TYPE_PHYDRV  2
#define STATS_TYPE_LOGDRV  3
#define STATS_TYPE_INVALID 0xFF

/* performance statistics type */
#define PERF_STATS_TYPE_ALL     0
#define PERF_STATS_TYPE_LOGDRV  1
#define PERF_STATS_TYPE_PHYDRV  2
#define PERF_STATS_TYPE_PORT    3
#define PERF_STATS_TYPE_INVALID 0xFF

#define BGA_RATE_HIGH   75
#define BGA_RATE_MEDIUM 50
#define BGA_RATE_LOW    25

/* MIC error descriptions */

#define MICS_ASC_START 0x80
#define MICS_ASC_MCP            ((MIC_MCP_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_LOCKMGR        ((MIC_LOCKMGR_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_CTRL_CONFIG    ((MIC_CTLR_CONFIG_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_MDD_FRONTEND   ((MIC_MDD_FRONTEND_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_MEDIA_PATROL   ((MIC_MEDIA_PATROL_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_INIT           ((MIC_LD_INIT_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_EVENTMGR       ((MIC_EVENTMGR_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_REBUILD        ((MIC_REBUILD_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_BKSYNC         ((MIC_BKSYNC_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_WATERMARK      ((MIC_WATERMARK_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_SCSIENU        ((MIC_SCSIEMU_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_REDCHECK       ((MIC_REDUNDANCY_CHK_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_PASSTHRU       ((MIC_PASSTHRU_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_ISCSI_MGT      ((MIC_ISCSI_MGT_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_ENCL_MGT       ((MIC_ENCLOSURE_MGT_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_RW_PROC        ((MIC_RWPROCESS_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_BUZZER         ((MIC_BUZZER_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_STATS          ((MIC_STATS_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_SPARE_CHECK    ((MIC_SPARECHECK_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_SPIN_DRV       ((MIC_SPIN_DRV_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_BBM            ((MIC_BBM_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_FC             ((MIC_FC_MGT_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_PSCSI          ((MIC_PSCSI_MGT_ID >> 8) + MICS_ASC_START)
#define MICS_ASC_FW_UPDATE      ((MIC_FW_UPDATE_ID >> 8) + MICS_ASC_START)

/* enclosure */
#define MIC_ENCL_TEMP_WARNING_MIN   25
#define MIC_ENCL_TEMP_WARNING_MAX   45
#define MIC_CTRL_TEMP_WARNING_MIN   35
#define MIC_CTRL_TEMP_WARNING_MAX   63

#define MIC_ENCL_TEMP_CRITICAL_MIN  30
#define MIC_ENCL_TEMP_CRITICAL_MAX  51
#define MIC_CTRL_TEMP_CRITICAL_MIN  40
#define MIC_CTRL_TEMP_CRITICAL_MAX  68

/* Mx10x */
#define MIC_CTRL_MX10X_TEMP_CRITICAL_MAX 68
#define MIC_CTRL_MX10X_TEMP_CRITICAL_MIN 48
#define MIC_CTRL_MX10X_TEMP_WARNING_MAX  63
#define MIC_CTRL_MX10X_TEMP_WARNING_MIN  40
#define MIC_ENCL_MX10X_TEMP_CRITICAL_MAX 51
#define MIC_ENCL_MX10X_TEMP_CRITICAL_MIN 43
#define MIC_ENCL_MX10X_TEMP_WARNING_MAX  45
#define MIC_ENCL_MX10X_TEMP_WARNING_MIN  35

/* JClass */
#define MIC_CTRL_J300S_TEMP_CRITICAL_MAX 71
#define MIC_CTRL_J300S_TEMP_CRITICAL_MIN 62
#define MIC_CTRL_J300S_TEMP_WARNING_MAX  61
#define MIC_CTRL_J300S_TEMP_WARNING_MIN  10
#define MIC_ENCL_J300S_TEMP_CRITICAL_MAX 61
#define MIC_ENCL_J300S_TEMP_CRITICAL_MIN 52
#define MIC_ENCL_J300S_TEMP_WARNING_MAX  51
#define MIC_ENCL_J300S_TEMP_WARNING_MIN  10

/* EClass */
#define MIC_CTRL_E310X_TEMP_CRITICAL_MAX 85
#define MIC_CTRL_E310X_TEMP_CRITICAL_MIN 76
#define MIC_CTRL_E310X_TEMP_WARNING_MAX  75
#define MIC_CTRL_E310X_TEMP_WARNING_MIN  10
#define MIC_ENCL_E310X_TEMP_CRITICAL_MAX 61
#define MIC_ENCL_E310X_TEMP_CRITICAL_MIN 52
#define MIC_ENCL_E310X_TEMP_WARNING_MAX  51
#define MIC_ENCL_E310X_TEMP_WARNING_MIN  10

/* Cx20x */
#define MIC_CTRL_VR1000_TEMP_CRITICAL_MAX 63
#define MIC_CTRL_VR1000_TEMP_CRITICAL_MIN 48
#define MIC_CTRL_VR1000_TEMP_WARNING_MAX  53
#define MIC_CTRL_VR1000_TEMP_WARNING_MIN  40
#define MIC_ENCL_VR1000_TEMP_CRITICAL_MAX 0
#define MIC_ENCL_VR1000_TEMP_CRITICAL_MIN 0
#define MIC_ENCL_VR1000_TEMP_WARNING_MAX  0
#define MIC_ENCL_VR1000_TEMP_WARNING_MIN  0

/* Cx20x jbod */
#define MIC_CTRL_VJ1000_TEMP_CRITICAL_MAX 63
#define MIC_CTRL_VJ1000_TEMP_CRITICAL_MIN 54
#define MIC_CTRL_VJ1000_TEMP_WARNING_MAX  53
#define MIC_CTRL_VJ1000_TEMP_WARNING_MIN  10
#define MIC_ENCL_VJ1000_TEMP_CRITICAL_MAX 0
#define MIC_ENCL_VJ1000_TEMP_CRITICAL_MIN 0
#define MIC_ENCL_VJ1000_TEMP_WARNING_MAX  0
#define MIC_ENCL_VJ1000_TEMP_WARNING_MIN  0

/*iscsi node maxburstlen*/
#define BURST_LENGTH_MAX 16777215
#define BURST_LENGTH_MIN 65536
#define BURST_LENGTH_GAP 512

/* --- functional routines ------------------------------------------------- */

#endif /* __PI_MICEXT_H__ */

/*******************************************************************************
 * Change Log
 *
 * $Log: micext.h,v $
 * Revision 1.39.6.11  2009/10/26 02:14:13  xinw
 * add LOGDRV_COND_SYNC_FORCED define
 *
 * Revision 1.39.6.10  2009/10/16 09:12:48  xinw
 * add performace monitor support
 *
 * Revision 1.39.6.9  2009/07/07 05:24:59  xinw
 * add raid3 support
 *
 * Revision 1.39.6.8  2009/05/26 07:41:11  xinw
 * change Maxburstlength to 16mb -1
 *
 * Revision 1.39.6.7  2009/05/15 03:07:10  xinw
 * change BURST_LENGTH_MAX to 16MB
 *
 * Revision 1.39.6.6  2009/05/05 10:01:53  xinw
 * change Firsrburstlength and Maxburstlength to 64kb
 *
 * Revision 1.39.6.5  2009/04/16 11:49:03  xinw
 * change iscsi Maxburstlen from 128K to 256K
 *
 * Revision 1.39.6.4  2009/01/06 08:09:07  xinw
 * modify cclass jbod temperature range
 *
 * Revision 1.39.6.3  2009/01/06 07:28:43  xinw
 * add class jbod temperature range
 *
 * Revision 1.39.6.2  2008/11/03 06:31:31  xinw
 * modify cx20s temp range
 *
 * Revision 1.39.6.1  2008/09/27 01:37:27  xinw
 * add cx20s temp range
 *
 * Revision 1.39  2008/05/16 05:54:33  michaell
 * add PHYDRV_CONFIG_PASSTHRU
 *
 * Revision 1.38  2007/12/12 06:21:45  danielz
 * remove flag ARRAY_FLAG_MP_RUNNING
 *
 * Revision 1.37  2007/10/23 10:29:47  danielz
 * support ALUA
 *
 * Revision 1.36  2007/05/09 09:55:20  xinw
 * modify maxburstlen value
 *
 * Revision 1.35  2007/04/05 03:36:36  JudithLi
 * 13548/ Mx10i: Please change the minimum value of the "MaxBurstLen" in CLU
 *
 * Revision 1.34  2007/02/09 03:00:29  danielz
 * current write policy of LD
 *
 * Revision 1.33  2006/11/28 08:23:49  danielz
 * FW update module
 *
 * Revision 1.32  2006/10/27 02:00:18  danielz
 * the PHYDRV_STATE_MISSING should be 0x02000000, not 0x04000000
 *
 * Revision 1.31  2006/10/12 03:51:53  danielz
 * Add enclosure temperature range for Mx10x
 *
 * Revision 1.30  2006/06/23 23:12:37  debinc
 * update temperature threshold
 *
 * Revision 1.29  2006/06/21 18:49:05  debinc
 * support eclass enclosure
 *
 * Revision 1.28  2006/05/31 19:21:05  debinc
 * factory defaults encl
 *
 * Revision 1.27  2006/03/14 23:48:46  debinc
 * lun affinity support
 *
 * Revision 1.26  2006/03/03 02:24:19  debinc
 * support RAID60
 *
 * Revision 1.25  2005/11/23 19:28:22  debinc
 * *** empty log message ***
 *
 * Revision 1.24  2005/08/31 05:08:49  weny
 * add new ASCs
 *
 * Revision 1.23  2005/08/18 09:22:52  xinw
 * added macro
 *
 * Revision 1.22  2005/08/17 09:10:41  binx
 * bug fix 7020 6809 5241
 *
 * Revision 1.21  2005/08/17 07:47:56  xinw
 * change the macro
 *
 * Revision 1.20  2005/03/18 07:33:28  weny
 * add temp threshold range definitions
 *
 * Revision 1.19  2004/10/28 05:00:31  weny
 * add INVALID_BATTERY_ID
 *
 * Revision 1.18  2004/10/19 22:12:02  weny
 * LD status of Transport Ready
 *
 * Revision 1.17  2004/10/19 04:34:17  weny
 * Online Array Removal support
 *
 * Revision 1.16  2004/10/11 19:45:33  weny
 * use u32 for stripe size in migration
 *
 * Revision 1.15  2004/10/05 19:39:57  debinc
 * remove subsys and enclosure stats
 *
 * Revision 1.14  2004/09/14 04:45:02  weny
 * Using the same naming scheme for LD Operation Status
 *
 * Revision 1.13  2004/08/31 06:50:45  weny
 * add flags for missing nvram watermark
 *
 * Revision 1.12  2004/08/26 04:02:30  weny
 * added new ASCs
 *
 * Revision 1.11  2004/08/18 23:37:40  weny
 * add ASC defintions
 *
 * Revision 1.10  2004/07/28 01:39:29  weny
 * remove the coercion macro defs, which are not in mic.h
 *
 * Revision 1.9  2004/07/22 04:03:00  weny
 * stale drive handling
 *
 * Revision 1.8  2004/07/20 04:23:40  weny
 * add some new constant definitions
 *
 * Revision 1.7  2004/07/08 23:09:44  weny
 * merge with Napa I2 API
 *
 * Revision 1.6  2004/07/07 01:19:15  weny
 * correct compiling error on Windows about i64 constants
 *
 * Revision 1.5  2004/07/06 23:18:49  weny
 * clean compiling warnings
 *
 * Revision 1.4  2004/04/27 17:45:35  weny
 * Sync with the fw mdd.h about LD/PD operation flag
 *
 * Revision 1.3  2004/04/07 02:24:15  zhengj
 * added LOGDRV_OPERATION_SYNCHRONIZING
 *
 * Revision 1.2  2004/03/26 22:43:05  zhengj
 * pd flag value update
 *
 * Revision 1.1  2004/03/24 03:24:12  weny
 * I2 API porting
 *
 ******************************************************************************/
