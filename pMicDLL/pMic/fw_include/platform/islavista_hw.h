#ifndef _ISLAVISTA_HW_H_
#define _ISLAVISTA_HW_H_

/*******************************************************************************
 *
 * Filename    : islavista_hw.h
 * Description : 
 * Created on  : 11/23/2004
 * CVS Version : 
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/
#include <asm/arch-forestlake/forestlake-irqs.h>
#include <asm/arch-forestlake/forestlake.h>

#define PROM_BUZZER_PHYSICAL_ADDRESS        0x4E700000
#define PROM_NVRAM_PHYSICAL_ADDRESS         0x4E600000
#define PROM_NVRAM_SIZE                     ((128 * 1024) - 0x0F)

/* Defines of Offsets in NVRAM. */
#define    NVRAM_BOOT                   0x0000    /* NVRAM Boot area */
#define    NVRAM_CPARAM                 0x0800    /* Controller Parameter */
#define    NVRAM_SCSIEMUL               0x0C00    /* SCSI Emulation */
#define    NVRAM_WTTBL                  0x1000    /* Write Transaction Table */
#define    NVRAM_WHTBL                  0x5000    /* Write Hole Table */
#define    NVRAM_DMAPTBL                0x11000   /* Drive Map Table */
#define    NVRAM_CRASH_DUMP             0x15000   /* Crash Dump */
#define    NVRAM_RES1                   0x15400   /* Reserved */
#define    NVRAM_PD_PARAM               0x15700   /* PD Device settings */
#define    NVRAM_MIGR_WM                0x15800   /* Migration watermark */
#define    NVRAM_ISCSI_PARAM            0x17800   /* iSCSI Parameters */
#define    NVRAM_EVNTLOG                0x18000   /* Event Log */

/* Defines for sizes of areas used in IslaVista HW */
#define    NVRAM_BOOT_SIZE              0x0800
#define    NVRAM_CPARAM_SIZE            0x0400
#define    NVRAM_SCSIEMUL_SIZE          0x0400
#define    NVRAM_EVNTLOG_SIZE           0x8000
#define    NVRAM_ISCSI_PARAM_SIZE       0x0800
#define    NVRAM_PD_SETTINGS_SIZE       0x0100
#define    NVRAM_MIGRATION_SIZE         0x2000
#define    NVRAM_CRASH_DUMP_SIZE        0x0400
#define    NVRAM_RES1_SIZE              0x0300
#define    NVRAM_WTTBL_SIZE             0x4000
#define    NVRAM_WHTBL_SIZE             0xC000
#define    NVRAM_DMAPTBL_SIZE           0x4000



#define PROM_CPLD_BASE_ADDR                 0x4E700000
#define PROM_BP_ID_PHYSICAL_ADDRESS         0x4E700002

#define DEFAULT_HM_START_ADDR               0x08000000
#define DEFAULT_HM_SIZE                     128

#define PROM_MEMORY_INFO_FROM_KERNEL        1
#define PROM_TOTAL_SYSTEM_MEMORY_SIZE       0
#define PROM_OS_ASSIGNED_MEMORY_SIZE        0

#define PROM_PASSWORD_JUMPER_SUPPORTED      1

#endif /* _ISLAVISTA_HW_H_ */















