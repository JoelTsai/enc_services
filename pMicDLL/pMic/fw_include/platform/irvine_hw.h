#ifndef _IRVINE_HW_H_
#define _IRVINE_HW_H_

/*******************************************************************************
 *
 * Filename    : irvine_hw.h
 * Description : 
 * Created on  : 11/23/2004
 * CVS Version : 
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/

#define PROM_BUZZER_PHYSICAL_ADDRESS        0xFE850000  
#define PROM_NVRAM_PHYSICAL_ADDRESS         0xFE840000
#define PROM_NVRAM_SIZE                     (32 * 1024)

/* Defines of offsets usied in Sonoma HW. */
#define    NVRAM_BOOT                   0x0000    /* NVRAM Boot area */
#define    NVRAM_CPARAM                 0x0800    /* Ctrl Parameter */
#define    NVRAM_SCSIEMUL               0x0C00    /* SCSI Emulation */
#define    NVRAM_EVNTLOG                0x6780    /* Event Log */
#define    NVRAM_ISCSI_PARAM            0x7780    /* iSCSI Parameters */
#define    NVRAM_PD_PARAM               0x7F80    /* PD Device settings */

#define    NVRAM_WTTBL                  0x1800    /* Write Transaction Table */
#define    NVRAM_WHTBL                  0x0C00    /* Write Hole Table */
#define    NVRAM_DMAPTBL                0x11800   /* Drive Map Table */

/* Defines for sizes of areas used in Sonoma HW */
#define    NVRAM_BOOT_SIZE              0x0800
#define    NVRAM_CPARAM_SIZE            0x0400
#define    NVRAM_SCSIEMUL_SIZE          0x0000
#define    NVRAM_EVNTLOG_SIZE           0x1000
#define    NVRAM_ISCSI_PARAM_SIZE       0x0800
#define    NVRAM_PD_SETTINGS_SIZE       0x0080

#define    NVRAM_WTTBL_SIZE             0x4000
#define    NVRAM_WHTBL_SIZE             0x5B80
#define    NVRAM_DMAPTBL_SIZE           0x2000

#define PROM_BP_ID_PHYSICAL_ADDRESS        0xFE8D0000

#define DEFAULT_HM_START_ADDR              0xA8000000
#define DEFAULT_HM_SIZE                    128

#define PROM_MEMORY_INFO_FROM_KERNEL       0
#define PROM_TOTAL_SYSTEM_MEMORY_SIZE      (256 * 1024 * 1024)
#define PROM_OS_ASSIGNED_MEMORY_SIZE       (128 * 1024 * 1024)   

#define PROM_PASSWORD_JUMPER_SUPPORTED     0

#endif /* _IRVINE_HW_H_ */


