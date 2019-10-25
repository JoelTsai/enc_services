/**
*  ::: RAID Driver Init Header :::
*
*  Contains
*   - FrontEnd driver Registration Information
*   - BackEnd driver Registration Information
*
* IMPORTANT: Structures are 32-bit aligned
**/

#ifndef __MAIN_H
#define __MAIN_H

#include "platform.h"
#include "product.h"

#ifdef CX20Y
#include "kfs.h"
#endif

#ifdef SMP_DISCOVERY
#include "backendmgr.h"   // auxDevice_t
#endif

struct FrontEndCmdResp;
struct FD_INFO_DESC;
struct BkEndInputStruct;

#define IN
#define OUT
#define INOUT


/* Data type used for global values for raid core */
typedef struct RaidCore
{
    spinlock_t              rc_SpinLock;

    /* used for asyn notification for user app (i2) */
    struct fasync_struct    *rc_AsyncQ;
} RaidCore_t;

typedef struct DriverInfo
{
    u8  di_DriverType;          /* Types: Unknown (set after unload), iSCSI, SATA */
    u8  di_DriverMajorNumber;
    u8  di_DriverMinorNumber;
    u8  di_DriverBuildNumber;
    u32 di_Reserved[3];
}DriverInfo_t;

/* Possible values for di_DriverType */
#define FE_USE_VIRT_MEM     0x80

#define SATA_DRIVER         0x01
#define ISCSI_DRIVER        0x02
#define SCSI_DRIVER         0x03
#define SAS_DRIVER          0x04
#define FC_DRIVER           0x05
#define FMU_DRIVER          0x06
#define INTEL_SAS_DRIVER    0x07
#define STM_DRIVER          0x09    /*QUENNEL CCLASS*/
#define SW_ISCSI_DRIVER     (FE_USE_VIRT_MEM | ISCSI_DRIVER)
#ifdef CX20Y_NAS
#define KERNEL_BLOCK_DRIVER 0x08
#define KER_BLOCK_FE_DRIVER (FE_USE_VIRT_MEM | KERNEL_BLOCK_DRIVER)
#endif
#define SCSI_HOST_DRIVER    0x0A
#define SCSI_HOST_DRIVER_V  (FE_USE_VIRT_MEM | SCSI_HOST_DRIVER)
#define SCSI_HOST_DRIVER_P  SCSI_HOST_DRIVER

typedef struct FrontEndDriverInfo
{
    struct DriverInfo   fedi_DriverInfo;

    u16 fedi_VendorId;
    u16 fedi_DeviceId;
    u16 fedi_SubSystemVendorId;
    u16 fedi_SubSystemDeviceId;

    u8 (*fedi_DMAQueueProcess) (struct FrontEndCmdResp *);
    u8 (*fedi_StatusQueueProcess) (struct FrontEndCmdResp *);
    u8 (*fedi_ReleaseFrontEndResource) (struct FrontEndCmdResp *);
    u8 (*fedi_ManagementInterface) (void *pCDB, void *pBuffer,
										void (*CallBackFn)(void *),
											void *CallBackData,
												u32 *CallBackSts);
    u8 (*fedi_DriverControlInterface) (void *pBuffer);
    u8 (*fedi_abortcmdwithfe) (struct FrontEndCmdResp *);
    u8 (*fedi_cleanupfewaitlist) (struct FrontEndCmdResp *);
    void (*fedi_notify_event_to_fe) (u32 EventID, u32 DeviceID, void *buffer);
#define FE_EVT_LUN_ADDED							0x1001
#define FE_EVT_LUN_REMOVED							0x1002
#ifdef CX20Y_NAS
#define FE_EVT_LUN_GONE_ONLINE						0x1003
#define FE_EVT_LUN_GONE_OFFLINE						0x1004
#define FE_EVT_LUN_DONE_OCE  						0x1005
#endif
	void (*fedi_poll_fe_isr) (void);
#if defined (PROM_FE_SAS) /*QUENNEL CCLASS*/
    void (*fedi_enable_fe)(void);
#endif

} FrontEndDriverInfo_t;

typedef struct ISCSIModuleInitParameters_
{
    void **imip_ChapHead;
    void **imip_ChapTargetHead;
    void *ChapListLock;
    void *imip_nvSettings;
    void *imip_nvNwkSettings;

}ISCSIModuleInit_t;



typedef struct ISCSIDriverInfo
{
    struct FrontEndDriverInfo  idi_FrontEndDriverInfo;

    u8 idi_MacAdress[8];
    u8 idi_IpAddress[4];
    u8 idi_IpNetMask[4];
    u8 idi_PortNumber;

    ISCSIModuleInit_t idi_ModuleParams;
	void *bd_list_head;
}ISCSIDriverInfo_t;

typedef struct MaxCTLSupport
{
    u16 mcs_VendorId;
    u16 mcs_DeviceId;
    u16 mcs_SubSystemVendorId;
    u16 mcs_SubSystemDeviceId;
    u8 mcs_MaxSupportedChannels;/* Max Channels supported by the Controller */
    u8 mcs_MaxSupportedTarget;  /* Max Target supported by the Controller */
    u8 mcs_MaxSupportedLun;     /* Max Lun supported by the Controller */
    u8 mcs_Reserved [5];
}MaxCTLSupport_t;


typedef struct FMUDriverInfo
{
    FrontEndDriverInfo_t fdi_driverinfo;

}FmuDriverInfo_t;

typedef struct FCDriverInfo
{
    FrontEndDriverInfo_t fdi_driverinfo;
    u32                  fdi_PortNumber;

}FCDriverInfo_t;

typedef struct SRB
{
    u8 temp; /*Place Holder */
}SRB_t;

#define MAX_BACKEND_CONTROLLERS     64
typedef struct SATADriverInfo
{
    struct DriverInfo        sdi_DriverInfo;
    u8                       sdi_NoOfControllers;                /* Number of controllers present */
    u8                       sdi_Reserved[3];
    struct MaxCTLSupport     sdi_CTL_List [MAX_BACKEND_CONTROLLERS]; /* Refer to this struct in SATA Section*/
    u32 (*fnsdi_SATA_Command_Process) (struct BkEndInputStruct *);
    u32 (*fnsdi_SATA_Management_Process) (struct BkEndInputStruct *);
#ifdef PERF_STAT
    void (*fnsdi_SATA_Print_Queue_Depths) (void);
#endif //PERF_STAT
    void (*poll_isr)(void);
    s32 (*fnsdi_SATA_Registration_Completed) (void);
}SATADriverInfo_t;

typedef struct SASDriverInfo
{
    struct DriverInfo   sdi_DriverInfo;
    u32 (*fnsdi_SAS_Command_Process) (struct BkEndInputStruct *);
    u32 (*fnsdi_SAS_Management_Process) (struct BkEndInputStruct *);
#ifdef PERF_STAT
    void (*fnsdi_SAS_Print_Queue_Depths) (void);
#endif //PERF_STAT
    u32 (*fnsdi_SAS_Validate_Target)(int target);
#ifdef SMP_DISCOVERY
    u32 (*fnsdi_SASScanAuxDevices)(u16 controllerId, u16 FlatId, auxDevice_t *pAuxDev);
#endif
    s32 (*fnsdi_SAS_Registration_Completed) (void);
} SASDriverInfo_t;

typedef union DrvRes
{
    struct DriverInfo        Driver_Info;
    struct FrontEndDriverInfo   FED_Info;
    struct ISCSIDriverInfo   ISCSI_Info;
    struct FCDriverInfo   FC_Info;	// [ABC] V4
    struct SATADriverInfo    SATA_Info;
    struct SASDriverInfo    SAS_Info;
}DrvRes_t;

typedef struct DriverResource
{
    u8              dr_InitState;   /* Maintains the state if a Discovery was done or not.
                                This will be mainly used during HotPlug of enclosure*/
    u8              dr_Reserved[3];
    union DrvRes    dr_DriverRes;
}DriverResource_t;

/* Possible value of dr_InitState */
#define UNKNOWN_STATE       0
#define REGISTERED_STATE    1
#define DISCOVERED_STATE    2

#define MAX_FRONTEND_DRIVERS    8
#define MAX_BACKEND_DRIVERS     8

typedef struct InterfaceModule
{
    u8                      im_NoOfFrontendDriver;
    u8                      im_NoOfBackendDriver;
    u8                      im_Reserved[2];
    struct DriverResource   im_FrontendDriverRes [MAX_FRONTEND_DRIVERS];
    struct DriverResource   im_BackendDriverRes [MAX_BACKEND_DRIVERS];
}InterfaceModule_t;

/* Other defines */
#define MAX_POSSIBLE_DRIVER_HANDLE  0x17
#define FRONTEND_DRIVER_HANDLE_MASK 0x10

/* Possible return values */
#define MAIN_SUCCESS                0x00
#define MAIN_FAILED                 0x01
#define MAIN_TRUE                   0x01
#define MAIN_FALSE                  0x00
#define MAIN_INVALID_HANDLE         0xFF

/* InitAllStages states */
#define IAS_SAS_DISCOVERY  0x200
#define IAS_CTL_INITPART2  0x201
#define IAS_DDF_PROCESS    0x202
#define IAS_PD_NEG         0x203
#define IAS_RW_PROCESS     0x204
#define IAS_WM_PROCESS     0x205
#define IAS_LMM_PROCESS    0x206
#define IAS_INIT_COMPLETE  0x207
#define IAS_RESTORE_LED    0x208

/* Externs */
extern u8 RegisterResource (IN DrvRes_t *DrvResource);
extern u8 DeRegisterResource (IN u8 Handle);
extern RaidCore_t gRaidCore;
extern u8 StartFixedMacAddress[8];
extern u8 StartFixedIPAddress[4];
extern u8 StartFixedSubNetMask[4];
#ifdef RLINUX
extern spinlock_t promise_grl;
#endif

extern size_t prom_printk(const char *fmt, ...);
extern int FindFrontEndDriverResourceByType (IN int type, OUT DrvRes_t **DrvRes);
extern int CWWN;
#ifndef TIMESYS
extern void wakeup_mainsched(void);
#endif

#define RAID_DEBUG_INPUT_BACKDOOR    1   /* 1: On, 0: Off */

#define BEM_DEBUG_IOFLOW    1 /* 1: Enable, 0: Disable */

#ifdef CX20Y
#define IVDUMP_PRINT_BUFFER_SIZE (256 * 1024)
extern u8 gIvdumpBuff[IVDUMP_PRINT_BUFFER_SIZE];
extern u8 *gIvdumpBuffOutPtr;
extern s32 gIvdumpFileDesc;
extern u8 gIvdump_timeout;
#define IVDUMP_PRINT_BUFFER_IS_FULL (gIvdumpBuffOutPtr == gIvdumpBuff + sizeof(gIvdumpBuff))
#define IVDUMP_PRINT_BUFFER_FREE_SPACE (gIvdumpBuff + sizeof(gIvdumpBuff) - gIvdumpBuffOutPtr)
#define IVDUMP_PRINT_BUFFER_USED_SPACE (gIvdumpBuffOutPtr - gIvdumpBuff)
#define IVDUMP_PRINT_TRUNCATED_WARNING "IVDUMP WARNING: the content listed above might be truncated\n"
#endif

#define IVDUMP_FILE "/tmp/ivdump_msg"
#ifdef CX20Y
#define IVDUMP_PRINT(FMT, ARGS... ) do { \
    if (gIvdump_timeout == 0) \
    { \
        printk(FMT, ##ARGS); \
        memset(gIvdumpBuff, 0, sizeof(gIvdumpBuff)); \
        if (gIvdumpFileDesc > 0) \
        { \
            sprintf(gIvdumpBuff, FMT, ##ARGS); \
            kfsWrite(gIvdumpFileDesc, (const void *)gIvdumpBuff, (u32)strlen(gIvdumpBuff)); \
        } \
    } \
    else \
    { \
        *gIvdumpBuffOutPtr = '\0'; \
        snprintf((void *)gIvdumpBuffOutPtr, IVDUMP_PRINT_BUFFER_FREE_SPACE, FMT, ##ARGS); \
        gIvdumpBuffOutPtr += strlen((void *)gIvdumpBuffOutPtr); \
    } \
} while (0)

#define IVDUMP_PRINT_RESET (gIvdumpBuffOutPtr = gIvdumpBuff)

#define IVDUMP_PRINT_FLUSH do { \
    extern int prom_getrtctime(struct prom_time*); \
    prom_time_t tm; \
    char time_line[26] = "time: "; \
    char *time = time_line + 6; \
    if (gIvdump_timeout > 0 && gIvdumpFileDesc > 0) \
    { \
        *gIvdumpBuffOutPtr ++ = '\n'; \
        kfsWrite(gIvdumpFileDesc, (void *)gIvdumpBuff, IVDUMP_PRINT_BUFFER_USED_SPACE); \
        if (IVDUMP_PRINT_BUFFER_IS_FULL) \
        { \
            kfsWrite(gIvdumpFileDesc, IVDUMP_PRINT_TRUNCATED_WARNING, strlen(IVDUMP_PRINT_TRUNCATED_WARNING)); \
            printk(IVDUMP_PRINT_TRUNCATED_WARNING); \
        } \
        else \
            printk("IVDUMP INFO: number of bytes used is %d\n", IVDUMP_PRINT_BUFFER_USED_SPACE); \
    } \
    IVDUMP_PRINT_RESET; \
    prom_getrtctime(&tm); \
    BIN_TO_ASCIIBCD(tm.month, time, 0, 20, ':'); \
    BIN_TO_ASCIIBCD(tm.date, time, 3, 20, ':'); \
    BIN_TO_ASCIIBCD(tm.year, time, 6, 20, ':'); \
    BIN_TO_ASCIIBCD(tm.hrs, time, 9, 20, ':'); \
    BIN_TO_ASCIIBCD(tm.mins, time, 12, 20, ':'); \
    BIN_TO_ASCIIBCD(tm.sec, time, 15, 20, '#'); \
    time[18] = '\n'; \
    time[19] = '\0'; \
    kfsWrite(gIvdumpFileDesc, time_line, sizeof(time_line) - 1); \
} while (0)

#define IVDUMP_PRINT_LOCK(lock, flags) do { \
    if (gIvdump_timeout > 0) \
    { \
        if (lock != NULL) \
            down_interruptible(lock); \
        local_irq_save(flags); \
    } \
} while (0)

#define IVDUMP_PRINT_UNLOCK(lock, flags) do { \
    if (gIvdump_timeout > 0) \
    { \
        local_irq_restore(flags); \
        if (lock != NULL) \
            up(lock); \
    } \
} while (0)

#define IVDUMP_PRINT_BEGIN(lock, flags) do { \
    IVDUMP_PRINT_RESET; \
    IVDUMP_PRINT_LOCK(lock, flags); \
} while (0)

#define IVDUMP_PRINT_END(lock, flags) do { \
    IVDUMP_PRINT_UNLOCK(lock, flags); \
    IVDUMP_PRINT_FLUSH; \
} while (0)
#else
#define IVDUMP_PRINT(FMT, ARGS... ) printk(FMT, ##ARGS)
#endif



#endif /* __MAIN_H */
