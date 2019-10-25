/*******************************************************************************
 *
 * Filename    : sclass_hw.h
 * Description : 
 * Created on  : 02/01/2006
 * CVS Version : 
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _SCLASS_HW_H_
#define _SCLASS_HW_H_

#include <asm/arch/irqs.h>

#define PROM_NVRAM_PHYSICAL_ADDRESS           0xC0F00000
#define PROM_NVRAM_SIZE                       (64 * 1024)

/* Defines of Offsets in NVRAM. */
#define    NVRAM_BOOT                       0x0000    /* NVRAM Boot area */
#define    NVRAM_CPARAM                     0x0800    /* Controller Parameter */
#define    NVRAM_SCSIEMUL                   0x0C00    /* SCSI Emulation */
#define    NVRAM_WTTBL                      0x1000    /* Write Transaction Table */
#define    NVRAM_WHTBL                      0x5000    /* Write Hole Table */
#define    NVRAM_CRASH_DUMP                 0xA000   /* Crash Dump */
#define    NVRAM_RES1                       0xA400   /* Reserved */
#define    NVRAM_PD_PARAM                   0xA700   /* PD Device settings */
#define    NVRAM_MIGR_WM                    0xA800   /* Migration watermark */
#define    NVRAM_ISCSI_PARAM                0xC800   /* iSCSI Parameters */
#define    NVRAM_EVNTLOG                    0xD000   /* Event Log */
#define    NVRAM_DMAPTBL                    0x0000   /* Drive Map Table */

/* Defines for sizes of areas used in IslaVista HW */
#define    NVRAM_BOOT_SIZE                  0x0800
#define    NVRAM_CPARAM_SIZE                0x0400
#define    NVRAM_SCSIEMUL_SIZE              0x0400
#define    NVRAM_EVNTLOG_SIZE               0x3000
#define    NVRAM_ISCSI_PARAM_SIZE           0x0800 
#define    NVRAM_PD_SETTINGS_SIZE           0x0100
#define    NVRAM_MIGRATION_SIZE             0x2000
#define    NVRAM_CRASH_DUMP_SIZE            0x0400
#define    NVRAM_RES1_SIZE                  0x0300
#define    NVRAM_WTTBL_SIZE                 0x4000 
#define    NVRAM_WHTBL_SIZE                 0x5000
#define    NVRAM_DMAPTBL_SIZE               0x0000


#define PROM_CPLD_BASE_ADDR                   0xC0F40000
#define PROM_BUZZER_PHYSICAL_ADDRESS          0xC0F40001
#define PROM_BP_ID_PHYSICAL_ADDRESS           0xC0F40002
#define PROM_RESET_CONFIG_PHYSICAL_ADDRESS    0xC0F40003
#define PROM_RESET_CAUSE_PHYSICAL_ADDRESS     0xC0F40004
#define PROM_CONTROLLER_ID_PHYSICAL_ADDRESS   0xC0F4000F

#define DEFAULT_HM_START_ADDR              0x08000000
#define DEFAULT_HM_SIZE                    64

#define PROM_MEMORY_INFO_FROM_KERNEL       1
#define PROM_TOTAL_SYSTEM_MEMORY_SIZE      (128 * 1024 * 1024)
#define PROM_OS_ASSIGNED_MEMORY_SIZE       (64 * 1024 * 1024)   

#define PROM_PASSWORD_JUMPER_SUPPORTED     0


struct sclass_enclosure_struct
{
	u8 NumOfFans;
	u8 NumOfPsus;
	u8 NumOfHDSlots;
	u8 DoorLockSts;
	u8 NumOfTempSensors;
	u8 NumOfAudibleAlarms;
	u8 NumOfBytesToFollow_Conf;
	u8 NumOfVoltageSensors;
	u8 NumOfBatteries;

};


#endif /* _SCLASS_HW_H_ */

