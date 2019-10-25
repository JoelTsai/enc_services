#ifndef _YOSEMITE_HW_H_
#define _YOSEMITE_HW_H_

/*******************************************************************************
 *
 * Filename    : yosemite.h
 * Description :
 * Created on  : 6/08/2005
 * CVS Version :
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/

/* SunriseLake IOP */
#include <asm/arch/iop1340-irqs.h>

/* IRQ */
#define IRQ_MCU_ERR         IRQ_IOP1340_MCU_ERR

/* PMMR virtual memory base address */
#define PMMR_VIRT_MEM_BASE  IOP1340_PMMR_VIRT_MEM_BASE

/* common constants */
#define BIT00   0x00000001
#define BIT01   0x00000002
#define BIT02   0x00000004
#define BIT03   0x00000008
#define BIT04   0x00000010
#define BIT05   0x00000020
#define BIT06   0x00000040
#define BIT07   0x00000080

#define BIT08   0x00000100
#define BIT09   0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000

#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000

#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

#define BIT0200 0x00000007
#define BIT0700 0x000000FF
#define BIT3128 0xF0000000
#define BIT3102 0xFFFFFFFC
#define BIT3100 0xFFFFFFFF

/* Registers of Memory Control Unit */
#define MCU_DECCR   (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x181C)
#define DECCR_ECC_ENABLE    BIT03   /* ECC Enabled: 1: Enable, 0: Disable */
#define DECCR_ONE_BIT_CORR  BIT02   /* Single Bit Error Correction Enable */
#define DECCR_MULT_BIT_ERR  BIT01   /* Multi-Bit Error Reporting Enable */
#define DECCR_ONE_BIT_ERR   BIT00   /* Single Bit Error Reporting Enable */

#define MCU_DELOG0  (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1820)
#define MCU_DELOG1  (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1824)
#define DELOG_UP_ADDR       BIT3128 /* Upper ECC Address */
#define DELOG_RW_TYPE       BIT12   /* 0: Read error, 1: Write error */
#define DELOG_ERR_TYPE      BIT08   /* 0: One bit, 1: Multi-bit */
#define DELOG_SYNDROME      BIT0700

#define MCU_DEAR0   (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1828)

#define MCU_DEAR1   (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x182C)
#define DEAR_ERR_ADDR       BIT3102 /* Error Address */

#define MCU_DECTST  (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1840)
#define DECTST_ECC_MASK     BIT0700

#define MCU_DMCISR  (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1860)
#define DMCISR_ECC_ERR_MASK BIT0200
#define DMCISR_ECC_ERR_N    BIT02
#define DMCISR_ECC_ERR_1    BIT01
#define DMCISR_ECC_ERR_0    BIT00

// Address
#define PROM_BUZZER_PHYSICAL_ADDRESS        0xF2020000
#define PROM_NVRAM_PHYSICAL_ADDRESS         0xF2000000
#define PROM_CPLD_GREEN_LED_ADDRESS         0xF2060000
#define PROM_CPLD_RED_LED_ADDRESS           0xF20A0000

/*add for agg_active_led*/
#define PROM_AGGLED_ON_PHYSICAL_ADDRESS     0xF20C0000
#define PROM_AGGLED_OFF_PHYSICAL_ADDRESS    0xF2040000

// 32 KB NVRAM
#define PROM_NVRAM_SIZE                     (32 * 1024)

/* Defines of Offsets in NVRAM. */
#define     NVRAM_BOOT                  0x0000    /* NVRAM Boot area */
#define     NVRAM_CPARAM                0x0800    /* Ctrl Parameter */
#define     NVRAM_SCSIEMUL_32           0x0000
#define     NVRAM_WTTBL_32              0x0000
#define     NVRAM_EVNTLOG_32            0x0C00    /* Event Log */
#define     NVRAM_WHTBL_32              0x1C00    /* Write Hole Table */
#define     NVRAM_DMAPTBL_32            0x0000
#define     NVRAM_MIGR_WM_32            0x5B80    /* Migration Water Mark */
#define     NVRAM_ISCSI_PARAM_32        0x7B00    /* BIOS SEP */
#define     NVRAM_CRASH_DUMP_32         0x7B80    /* Crash Dump */
#define     NVRAM_PD_PARAM_32           0x7F80    /* PD Device settings */
#define     NVRAM_END_32                0x8000

/* Defines for sizes of areas */
#define     NVRAM_BOOT_SIZE             0x0800
#define     NVRAM_CPARAM_SIZE           0x0400
#define     NVRAM_EVNTLOG_SIZE_32       0x1000
#define     NVRAM_WHTBL_SIZE            0x3F80
#define     NVRAM_MIGRATION_SIZE        0x1F80
#define     NVRAM_ISCSI_PARAM_SIZE      0x0080
#define     NVRAM_CRASH_DUMP_SIZE       0x0400
#define     NVRAM_PD_SETTINGS_SIZE      0x0080

// 128 KB NVRAM
//#define PROM_NVRAM_SIZE                     ((128 * 1024) - 0x0F)

/* Defines of Offsets in NVRAM. */
//#define    NVRAM_BOOT                   0x0000    /* NVRAM Boot area */
//#define    NVRAM_CPARAM                 0x0800    /* Controller Parameter */
#define    NVRAM_SCSIEMUL_128           0x0C00    /* SCSI Emulation */
#define    NVRAM_WTTBL_128              0x1000    /* Write Transaction Table */
#define    NVRAM_WHTBL_128              0x5000    /* Write Hole Table */
#define    NVRAM_HA                     0x11000   /* High Avalibility info */
#define    NVRAM_DMAPTBL_128            0x11400   /* Drive Map Table */
#define    NVRAM_CRASH_DUMP_128         0x15000   /* Crash Dump */
#define    NVRAM_RES1                   0x15400   /* Reserved */
#define    NVRAM_ENC                    0x156C0   /* Enclosure Service, currently not use */
#define    NVRAM_UPS                    0x156F0   /* UPS Manager */
#define    NVRAM_PD_PARAM_128           0x15700   /* PD Device settings */
#define    NVRAM_MIGR_WM_128            0x15800   /* Migration watermark */
#define    NVRAM_ISCSI_PARAM_128        0x17800   /* iSCSI Parameters */
#define    NVRAM_EVNTLOG_128            0x18000   /* Event Log */
#define    NVRAM_END_128                0x20000

/* Defines for sizes of areas used in Yosemite HW */
#if 0 // For human reference only
#define    NVRAM_BOOT_SIZE             0x0800
#define    NVRAM_CPARAM_SIZE           0x0400
#define    NVRAM_SCSIEMUL_SIZE         0x0400
#define    NVRAM_WTTBL_SIZE            0x4000
#define    NVRAM_WHTBL_SIZE            0xC000
#define    NVRAM_HA_SIZE               0x0400
#define    NVRAM_DMAPTBL_SIZE          0x3C00
#define    NVRAM_CRASH_DUMP_SIZE       0x0400
#define    NVRAM_RES1_SIZE             0x02C0             //0x0300
#define    NVRAM_ENC_SIZE              0x0030
#define    NVRAM_UPS_SIZE              0x0010
#define    NVRAM_PD_SETTINGS_SIZE      0x0100
#define    NVRAM_MIGRATION_SIZE        0x2000
#define    NVRAM_ISCSI_PARAM_SIZE      0x0800
#endif
#define    NVRAM_EVNTLOG_SIZE_128      0x8000


#define PROM_BP_ID_PHYSICAL_ADDRESS        0x0  /* not used in raid_core for HBA */

#define DEFAULT_HM_START_ADDR              0x04000000
#define DEFAULT_HM_SIZE                    192

#define PROM_MEMORY_INFO_FROM_KERNEL       1
#define PROM_TOTAL_SYSTEM_MEMORY_SIZE      (256 * 1024 * 1024)
#define PROM_OS_ASSIGNED_MEMORY_SIZE       (64 * 1024 * 1024)

/* record internal backplane connect phy*/
    #define SAS_INTERNAL_PHYSTART          0
    #define SAS_INTERNAL_PHYCOUNT          4 /*8454 internal phy list: phy 0,1,2,3*/

#define PROM_PASSWORD_JUMPER_SUPPORTED     0

#define PROM_MEMORY_TYPE    PROM_MEMORY_TYPE_DDR2

#endif /* _YOSEMITE_HW_H_ */

