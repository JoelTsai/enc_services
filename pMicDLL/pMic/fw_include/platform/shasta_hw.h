#ifndef _SHASTA_HW_H_
#define _SHASTA_HW_H_

/*******************************************************************************
 *
 * Filename    : shasta.h
 * Description : 
 * Created on  : 11/23/2004
 * CVS Version : 
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/

#include <asm/arch/irqs.h>
/*#include <asm-arm/arch-iop3xx/iop321-irqs.h> \ #define IRQ_IOP321_I2C_0 IOP321_IRQ(11)
                                                      #define IRQ_IOP321_I2C_1 IOP321_IRQ(12) */

#define PROM_BUZZER_PHYSICAL_ADDRESS        0xCE860000
#define PROM_NVRAM_PHYSICAL_ADDRESS         0xCE800000
#define PROM_NVRAM_SIZE                     (32 * 1024)

/* Defines of Offsets in NVRAM. */
#define     NVRAM_BOOT                  0x0000    /* NVRAM Boot area */
#define     NVRAM_CPARAM                0x0800    /* Ctrl Parameter */
#define     NVRAM_EVNTLOG               0x0C00    /* Event Log */
#define     NVRAM_WHTBL                 0x1C00    /* Write Hole Table */
#define     NVRAM_MIGR_WM               0x5B80    /* Migration Water Mark */
#define     NVRAM_CRASH_DUMP            0x7B80    /* Crash Dump logging in NVRAM */ 
#define     NVRAM_PD_PARAM              0x7F80    /* PD Device settings */

/* Defines for sizes of areas used in Shasta HW */
#define     NVRAM_BOOT_SIZE             0x0800
#define     NVRAM_CPARAM_SIZE           0x0400
#define     NVRAM_EVNTLOG_SIZE          0x1000
#define     NVRAM_WHTBL_SIZE            0x3F80
#define     NVRAM_MIGRATION_SIZE        0x2000
#define     NVRAM_CRASH_DUMP_SIZE       0x0400
#define     NVRAM_PD_SETTINGS_SIZE      0x0080

/* Dummy defines */
#define     NVRAM_WTTBL                 0x0       
#define     NVRAM_DMAPTBL               0x0       
#define     NVRAM_ISCSI_PARAM           0x0       
#define     NVRAM_SCSIEMUL              0x0       


#define PROM_BP_ID_PHYSICAL_ADDRESS        0x0 /* not used in raid_core for HBA */

#define DEFAULT_HM_START_ADDR              0x04000000
#define DEFAULT_HM_SIZE                    64

#define PROM_MEMORY_INFO_FROM_KERNEL       0
#define PROM_TOTAL_SYSTEM_MEMORY_SIZE      (128 * 1024 * 1024)
#define PROM_OS_ASSIGNED_MEMORY_SIZE       (64 * 1024 * 1024)   

#define PROM_PASSWORD_JUMPER_SUPPORTED     0

#endif /* _SHASTA_HW_H_ */







