/*******************************************************************************
 *
 * Filename    : cx20y_hw.h
 * Description : 
 * Created on  : 2008/5/13
 * CVS Version : 
 *
 * (C) Copyright Promise Technology Inc., 2002-2008
 * All Rights Reserved
 *
 ******************************************************************************/
#ifndef _CX20Y_HW_H_
#define _CX20Y_HW_H_

/* SunriseLake IOP */
#include <asm/arch/iop1340-irqs.h>

extern u8   IV_WatchDogInit (void);
extern u8   IV_WatchDogDisable (void);

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
#define MCU_DECCR                           (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x181C)
#define DECCR_ECC_ENABLE                    BIT03   /* ECC Enabled: 1: Enable, 0: Disable */
#define DECCR_ONE_BIT_CORR                  BIT02   /* Single Bit Error Correction Enable */
#define DECCR_MULT_BIT_ERR                  BIT01   /* Multi-Bit Error Reporting Enable */
#define DECCR_ONE_BIT_ERR                   BIT00   /* Single Bit Error Reporting Enable */

#define MCU_DELOG0                          (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1820)
#define MCU_DELOG1                          (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1824)
#define DELOG_UP_ADDR                       BIT3128 /* Upper ECC Address */
#define DELOG_RW_TYPE                       BIT12   /* 0: Read error, 1: Write error */
#define DELOG_ERR_TYPE                      BIT08   /* 0: One bit, 1: Multi-bit */
#define DELOG_SYNDROME                      BIT0700

#define MCU_DEAR0                           (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1828)

#define MCU_DEAR1                           (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x182C)
#define DEAR_ERR_ADDR                       BIT3102 /* Error Address */

#define MCU_DECTST                          (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1840)
#define DECTST_ECC_MASK                     BIT0700

#define MCU_DMCISR                          (volatile u32 *)(PMMR_VIRT_MEM_BASE + 0x1860)
#define DMCISR_ECC_ERR_MASK                 BIT0200
#define DMCISR_ECC_ERR_N                    BIT02
#define DMCISR_ECC_ERR_1                    BIT01
#define DMCISR_ECC_ERR_0                    BIT00

// Address
#define PROM_NAND_FLASH_BASE_ADDRESS        0xF2000000
#define PROM_RTC_BASE_ADDRESS               0xF2400000
#define PROM_CPLD_BASE_ADDR                 0xFC600000
#define PROM_BUZZER_PHYSICAL_ADDRESS        0xF2800000
#if 0  // check for Cx20y HW ESD
#define PROM_BP_ID_PHYSICAL_ADDRESS           0xC0F40002
#define PROM_RESET_CONFIG_PHYSICAL_ADDRESS    0xC0F40003
#define PROM_RESET_CAUSE_PHYSICAL_ADDRESS     0xC0F40004
#define PROM_CONTROLLER_ID_PHYSICAL_ADDRESS   0xC0F4000F
#endif

// Virtual Address
#define PROM_NAND_FLASH_VIRTUAL_ADDRESS 0xFC000000
#if defined(EV_BOARD) && defined(CX20Y)
#define PROM_NVRAM_VIRTUAL_ADDRESS      0xFC070000
#define PROM_RTC_VIRTUAL_ADDRESS        0xFC400000
#define PROM_CPLD_VIRTUAL_ADDRESS       0xFC020000
#define PROM_BUZZER_VIRTUAL_ASSRESS     0xFC060000
#else
#define PROM_NVRAM_VIRTUAL_ADDRESS      0xFC200000
#define PROM_RTC_VIRTUAL_ADDRESS        0xFC400000
#define PROM_CPLD_VIRTUAL_ADDRESS       0xFC600000
#define PROM_BUZZER_VIRTUAL_ASSRESS     0xFC800000
#endif

#if defined(EV_BOARD)
#define PROM_NVRAM_SIZE                 (128 * 1024)
#define PROM_NVRAM_PHYSICAL_ADDRESS     0xF2200000
#else
// 128 KB NVRAM, no deduct 0x0F of RTC and WDT but leave to EVENT LOG module to handle
#define PROM_NVRAM_SIZE                 128 * 1024
#define PROM_NVRAM_PHYSICAL_ADDRESS     0xF2200000 /* ToDo: Check CX20Y HW ESD */
#endif


#define     NVRAM_BOOT                  0x0000    /* NVRAM Boot area */
#define     NVRAM_CPARAM                0x0800    /* Ctrl Parameter */
#define     NVRAM_SCSIEMUL_32           0x0C00     
#define     NVRAM_WTTBL_32              0x1000
#define     NVRAM_WHTBL_32              0x3800    /* Write Hole Table */
#define     NVRAM_DMAPTBL_32            0x6000    /* No Used */
#define     NVRAM_CRASH_DUMP_32         0x6000    /* Crash Dump */
//#define     NVRAM_RES1                  0x6400    /* Reserved, no reserve for EV board 32MB nvram */
#define     NVRAM_PD_PARAM_32           0x6400    /* PD Device settings */
#define     NVRAM_MIGR_WM_32            0x6500    /* Migration Water Mark */
#define     NVRAM_PCI_PARAM_32          0x7500    /* PCI OEM info */
#define     NVRAM_ISCSI_PARAM_32        0x7600    /* BIOS SEP */
#define     NVRAM_EVNTLOG_32            0x7A00    /* Event Log */
#define     NVRAM_END_32                0x8000

/* Defines of Offsets in NVRAM. */
#define     NVRAM_SCSIEMUL_128          0x0C00    /* SCSI Emulation */
#define     NVRAM_WTTBL_128             0x1000    /* Write Transaction Table */
#define     NVRAM_WHTBL_128             0x5000    /* Write Hole Table */
#define     NVRAM_HA                    0x11000   /* High Avalibility info */
#define     NVRAM_DMAPTBL_128           0x11400   /* Drive Map Table */
#define     NVRAM_CRASH_DUMP_128        0x15000   /* Crash Dump */
#define     NVRAM_PCI_PARAM_128         0x15400   /* PCI OEM info */
#define     NVRAM_ENC                   0x156C0   /* Enclosure Service, currently not use */
#define     NVRAM_UPS                   0x156F0   /* UPS Manager */
#define     NVRAM_PD_PARAM_128          0x15700   /* PD Device settings */
#define     NVRAM_MIGR_WM_128           0x15800   /* Migration watermark */
#define     NVRAM_ISCSI_PARAM_128       0x17800   /* iSCSI Parameters */
#define     NVRAM_RES2                  0x19000   /* Currently for Redboot Dual image protection */
#define     NVRAM_EVNTLOG_128           0x1A000   /* Event Log */
#define     NVRAM_END_128               0x20000


#define     NVRAM_EVNTLOG_SIZE_32       0x0600
#define     NVRAM_EVNTLOG_SIZE_128      0x6000

#ifdef EV_BOARD
#define IV_NVRAM_CD_ADDRESS             nvRamHD+NVRAM_CRASH_DUMP_128
#else
#define IV_NVRAM_CD_ADDRESS             nvRamHD+NVRAM_CRASH_DUMP_128
#endif
#define IV_NVRAM_CD_SIZE                0x400

/* These are yet to be defined properly for cx20y */
#define IV_RESET_CFG                    0xEC700006
/* end quote */

/* IV_RESET_CAUSE is 7byte offset within the CPLD */
#define IV_RESET_CAUSE_OFF              (0x4)
#define IV_RESET_CAUSE                  (PROM_CPLD_VIRTUAL_ADDRESS + IV_RESET_CAUSE_OFF)


#define IV_RTC_REGBASE                  PROM_RTC_VIRTUAL_ADDRESS
#define IV_RTC_REGOFF(x, y)                {                        \
    volatile u8* reg = (volatile u8*)CPLD_BASE_REG;                 \
    if ((*(reg + 0x07) & 0x40) && (*(reg + 0x0f) & 0x0f))           \
        y = (volatile u8 *)(IV_RTC_REGBASE + 0x7fff0 + (x));        \
    else                                                            \
        y = (volatile u8 *)(IV_RTC_REGBASE + (x));                  \
}

#define IV_WATCHDOG_FLAGS(x)               IV_RTC_REGOFF(0, x)
#define IV_WATCHDOG_REG(x)                 IV_RTC_REGOFF(7, x)
#define IV_WATCHDOG_CONTROL(x)             IV_RTC_REGOFF(8, x)

#if defined(CX20Y)
#define WatchDogInit                    IV_WatchDogInit
#define WatchDogDisable                 IV_WatchDogDisable
#else
#define WatchDogInit
#define WatchDogDisable
#endif

#define CPLD_BASE_REG                   PROM_CPLD_VIRTUAL_ADDRESS
#define CPLD_EXPENDER_OFF               (0x2)
#define CPLD_RESET_OFF                  (0x3)
#define CPLD_INTR_OFF                   (0x4)
#define CPLD_CTRL_ID_OFF                (0xf)


#if 0
#define CPLD_WDOG_ENABLE_INTR(x)        {                               \
        volatile u8* reg = (volatile u8*)CPLD_BASE_REG + CPLD_INTR_OFF; \
        if (x) {                                                        \
            *reg |= (0x80);                                              \
        } else {                                                        \
            *reg &= ~(0x80);                                             \
        }                                                               \
    }
#endif

#define CPLD_WDOG_ENABLE_INTR(x)

#define CPLD_WDOG_ENABLE_RESET(x)       {                               \
        volatile u8* reg = (volatile u8*)CPLD_BASE_REG + CPLD_RESET_OFF;\
        if (x) {                                                        \
            *reg |= (0x04);                                              \
        } else {                                                        \
            *reg &= ~(0x04);                                             \
        }                                                               \
    }


#define     DEFAULT_HM_START_ADDR       0x04000000
#define     DEFAULT_HM_SIZE             128

#define PROM_MEMORY_INFO_FROM_KERNEL       1
#define PROM_TOTAL_SYSTEM_MEMORY_SIZE      (256 * 1024 * 1024)
#define PROM_OS_ASSIGNED_MEMORY_SIZE       (128 * 1024 * 1024)   

#define PROM_PASSWORD_JUMPER_SUPPORTED     1

#define PROM_MEMORY_TYPE    PROM_MEMORY_TYPE_DDR2


#endif /* _CX20Y_HW_H_ */

