/*******************************************************************************
 * Filename    : mic.h
 * Description : Management Interface Command definitions
 * Created on  : 12/08/02
 * CVS Version : $Id: mic.h 1332 2012-07-30 03:14:21Z bob.cho $
 *
 * (C) Copyright Promise Technology Inc., 2002
 * All Rights Reserved
 ******************************************************************************/

#ifndef __MIC_H
#define __MIC_H

//adamadam
#if defined(_SWRAID_V4_)
#include "common.h"
#endif

#define VESSAPP
#define LUNCOPY
#define PACKED __attribute__ ((packed))

/******************* User Space definition - Start ****************************/

#define PMIC_EXECUTE_USRCMD     0x105a0001  /* cmd val for use w/ ioctl() */

#define PMIC_MAX_SENSE_SIZE     64
#define PMIC_MAX_PMIC_SIZE      32
#define PMIC_MAX_DATA_XFER_SIZE 65536

#define RO  /* Read-Only */
#define RW  /* Read-Write */

//adamadam
#if defined(WINDOWS) || defined(_WINDRIVER)
//#pragma pack (show)
//#pragma pack (push, mic_pack, 1)
#pragma pack(push, 1) //rock test
//#pragma pack (show)
#endif

/* IOCTL defintion */
typedef struct ptiIOCTLCmd
{
    u8  *pic_pDataBuf;                      /* AP - Pointer to Data Buffer       */
    u32  pic_DataBufLen;                    /* AP - Length of pic_Databuf        */
    u32  pic_SenseBufLen;                   /* FW - Valid Sense Buffer length    */
    u8   pic_MicBuf[PMIC_MAX_PMIC_SIZE];    /* AP - Contains MIC                 */
    u8   pic_SenseBuf[PMIC_MAX_SENSE_SIZE]; /* FW - Contains Sense Information   */
    u32  pic_DataDirection;                 /* AP - Flow of Data direction       */
    u8   pic_Status;                        /* FW - Status for Command Execution */
} PACKED  ptiIOCTLCmd_t;

/* Valid values for pic_DataDirection */
#define PMIC_DATA_UNKNOWN           0   /* reserved, should not be used */
#define PMIC_DATA_IN                1   /* data is being sent to firmware */
#define PMIC_DATA_OUT               2   /* data is being sent to userspace */
#define PMIC_DATA_NONE              3   /* no data transfer */

/* Valid statuses for pic_Status */
#define PMIC_GOOD                   0x00
#define PMIC_CHECK_CONDITION        0x02

/* Valid ASCQ values for CHECK_CONFITION */
#define MICS_RESERVED                       0xFF

#define MICS_SUCCESS                        0x00
#define MICS_INVALID_CMD_SCSI_OP_CODE       0x01
#define MICS_INVALID_CMD_MIC_SIGNATURE      0x02
#define MICS_INVALID_CMD_MIC_OP_CODE        0x03
#define MICS_INVALID_CMD_CONFIG_LOCK        0x04
#define MICS_INVALID_CMD_UNIQUE_CMD_ID      0x05
#define MICS_INVALID_CMD_LOGIN_KEY          0x06
#define MICS_INVALID_CMD_TRANSFER_LENGTH    0x07
#define MICS_INVALID_CMD_TRANSFER_OFFSET    0x08
#define MICS_INVALID_CMD_AT_OFFSET          0x09 /*The Command Offset will be in Sense Specifc Info.*/
#define MICS_INVALID_CMD_START_DEVICE_ID    0x0A
#define MICS_INVALID_CMD_DEVICE_COUNT       0x0B
#define MICS_INVALID_CMD_ARRAY_ID           0x0C
#define MICS_INVALID_CMD_PHYSICAL_DRIVE_ID  0x0D
#define MICS_INVALID_CMD_LOGICAL_DRIVE_ID   0x0E
#define MICS_INVALID_CMD_HOT_SPARE_ID       0x0F
#define MICS_INVALID_CMD_SEQUENCE_NO        0x10
#define MICS_INVALID_CMD_MIC_PAGE_CODE      0x11
#define MICS_INVALID_TOTAL_DATA_SIZE        0x12
#define MICS_INVALID_DATA_BUFFER_SIZE       0x13
#define MICS_INVALID_DATA_AT_OFFSET         0x14 /*The Data Offset will be in Sense Specifc Info.*/
#define MICS_INVALID_ARRAY_ID               0x15
#define MICS_INVALID_PHYSICAL_DRIVE_ID      0x16
#define MICS_INVALID_LOGICAL_DRIVE_ID       0x17
#define MICS_INVALID_HOT_SPARE_ID           0x18
#define MICS_CMD_EXECUTION_NOT_AUTHORIZED   0x19
#define MICS_MEMORY_ALLOCATION_FAILED       0x1A
#define MICS_INTERNAL_ERROR                 0x1B /*Internal Error Code will be in Sense Specifc Info.*/
#define MICS_UCID_CL_USED_INCORRECTLY       0x1C
#define MICS_INVALID_CONFIG_LOCK            0x1D
#define MICS_INVALID_UCID_OR_CONFIG_LOCK    0x1E
#define MICS_INVALID_DATA                   0x1F
#define MICS_MDD_ACCESS_FAILED              0x20
#define MICS_INVALID_CMD                    0x21
#define MICS_MIGRATION_ACTIVE_IN_ARRAY      0x22
#define MICS_PD_UNCONFIGURED                0x23
#define MICS_CFG_UPDATE_BLOCKED             0x24
#define MICS_INVALID_PD_SEQUENCE_NO         0x25
#define MICS_ACTIVE_SESSIONS_PRESENT        0x26
#define MICS_DRIVES_MISSING_IN_ARRAY        0x28
#define MICS_CMD_REJECTED_SS_SHUTDOWN       0x29
#define MICS_NVRAM_ACCESS_FAILED            0x2A
#define MICS_FLASH_ACCESS_FAILED            0x2B
#define MICS_WM_ACCESS_FAILED               0x2C
#define MICS_PEER_UPDATE_FAILED             0x2D
#define MICS_FW_UNABLE_TO_GET_RESOURCE_LOCK 0x2E
#define MICS_UNSUPPORTED_CMD_FOR_DRIVE_TYPE 0x2F
#define MICS_UNABLE_TO_COMM_TO_PARTNER_CTRL 0x30
#define MICS_CMD_REJECTED_MAINTENANCE_MODE  0x31
#define MICS_CMD_REJECTED_CLIQUE_NOT_REDUNDANT  0x32
#define MICS_SUBSYSTEM_NOT_READY            0x33
#define MICS_INVALID_PORT                   0x34
#define MICS_SAS_FE_INVALID_CSS             0x35
#define MICS_CONFIG_UPDATE_ON_DISK_FAILED   0x36
#define MICS_SUBSYS_NOT_ACTIVE_ACTIVE       0x37
#define MICS_PD_HARDWARE_ERROR              0x38
#define MICS_FAILOVER_IN_PROGRESS           0x39
#define MICS_STSVC_ACTIVE                   0x40
#define MICS_REQ_ARRAY_INCOMPLETE           0x41

#define MICS_GENERAL_ERROR_RESERVED_END     0x4F
#define MICS_MODULE_SPECIFIC_ERROR_START    0x50
#define MICS_PTATACMD_FAILED (MICS_MODULE_SPECIFIC_ERROR_START + 0)

#define MICS_MODULE_SPECIFIC_ERROR_END      0xFE

/* MIC error code for SMART diagnostic */
#define MICS_SMART_NOT_ENABLED              (MICS_MODULE_SPECIFIC_ERROR_START + 0x01)
#define MICS_SMART_NO_AVAILABLE_PD          (MICS_MODULE_SPECIFIC_ERROR_START + 0x02)
#define MICS_SMART_ALREADY_STARTED          (MICS_MODULE_SPECIFIC_ERROR_START + 0x03)
#define MICS_SMART_NOT_STARTED              (MICS_MODULE_SPECIFIC_ERROR_START + 0x04)

/* MIC error code for firmware update module */
#define MICS_FWUPD_TIMEOUT                  (MICS_MODULE_SPECIFIC_ERROR_START + 0x05)
#define MICS_FWUPD_ALREADY_INITALIZED       (MICS_MODULE_SPECIFIC_ERROR_START + 0x06)
#define MICS_FWUPD_NOT_INITIALIZED          (MICS_MODULE_SPECIFIC_ERROR_START + 0x07)
#define MICS_FWUPD_IMAGE_NOT_TRANSFERRED    (MICS_MODULE_SPECIFIC_ERROR_START + 0x08)
#define MICS_FWUPD_INVALID_IMAGE            (MICS_MODULE_SPECIFIC_ERROR_START + 0x09)
#define MICS_FWUPD_FLASH_IN_PROGRESS        (MICS_MODULE_SPECIFIC_ERROR_START + 0x0A)
#define MICS_FWUPD_TRANSFER_OUT_OF_ORDER    (MICS_MODULE_SPECIFIC_ERROR_START + 0x0B)
#define MICS_FWUPD_TRANSFER_OVERFLOW        (MICS_MODULE_SPECIFIC_ERROR_START + 0x0C)
#define MICS_FWUPD_TRANSFERRED              (MICS_MODULE_SPECIFIC_ERROR_START + 0x0D)

#define MICS_MODULE_SPECIFIC_ERROR_END      0xFE

/******************* User Space definition - End ****************************/


/********** Management Command Interface (MIC) definitions - Start **********/

typedef struct ExtendedMicCmd
{
    u8 emc_ExtendedCmd[16];
}ExtendedMicCmd_t;

/* General structure for Standard MIC Command */
typedef struct MicCmd
{
    u8                  mc_ScsiOpCode;
    u8                  mc_MicSignature;
    u16                 mc_MicOpCode;

    union
    {
        u8              mc_ConfigLock;
        u8              mc_UniqueCmdId;
    }PACKED u;

    u8                  mc_LoginKey;
    u8                  mc_CmdSpecific0;
    u8                  mc_CmdSpecific1;
    u8                  mc_CmdSpecific2;
    u8                  mc_CmdSpecific3;
    u16                 mc_TransferLength;
    u16                 mc_TransferOffset;
    u8                  mc_CmdSpecific4;
    u8                  mc_Control;
    ExtendedMicCmd_t    mc_ExtendedCmd;     /* For InBand, copy this to dbh_ExtendedCmd */
                                            /* of DataBufferHeader_t and send only      */
                                            /* 16 Byte as Command                       */
} PACKED MicCmd_t;

//} MicCmd_t;

/* Valid values for mc_ScsiOpCode */
#define PMIC_MGT_CMD                0xD8
#define PMIC_SINBAND_MGT_CMD        0xD9 /* for secure InBand Command */

/* Valid values for mc_MicSignature */
#define PMIC_SIGNATURE              0xBA

/* Possible values for mc_Control */
#define OC_1        0x00
#define OC_512      0x40
#define OC_1024     0x80
#define OC_4096     0xC0

#define OC_MASK     0xC0
#define OC_GETOFFSETCONTROL(x)  ((x) >> 6)

typedef struct Control
{
    u8 c_Control:6;
    u8 c_OffsetControl:2;
} PACKED Control_t;
//} Control_t;
/*
 * Data Buffer Header structure for OutOfBand and
 * InBand Non-Pass Through Commands
 */
typedef struct DataBufferHeader
{
    u8  dbh_ExtendedCmd[16];
    u8  dbh_LoginKey[16];
    u32 dbh_TotalDataSize;
    u32 dbh_NextTransferOffset;
    u8  dbh_Reserved[24];
} PACKED DataBufferHeader_t;

/*
 * Sense Buffer structure
 *
 */
typedef struct micRequestSense
{
    u8 rs_ResponseCode;
    u8 rs_Obselete;
    u8 rs_SenseKey;
    u8 rs_Information[4];
    u8 rs_AdditionalSenseLength;
    u8 rs_CmdSpecificInfo[4];
    u8 rs_ASC;                  /* 0x80 + ModuleID */
    u8 rs_ASCQ;
    u8 rs_FRUCode;
    u8 rs_SenseKeySpecific;
    u8 rs_SenseKeySpecificData[2];
    u8 rs_AdditionalSenseInfo[PMIC_MAX_SENSE_SIZE - 18];
} PACKED micRequestSense_t;

/*
 * Since each command will be handled by a specific module, the command will
 * be encoded with a module ID
 */
#ifndef LUNCOPY
#define MIC_NUM_MODULES             32
#else
#define MIC_NUM_MODULES             34
#endif

#define MIC_MCP_ID                  0x0100  /* Management Command Processor */
#define MIC_LOCKMGR_ID              0x0200  /* MIC Lock Manager */
#define MIC_CTLR_CONFIG_ID          0x0300  /* Ctlr related funcs Manager */
#define MIC_MDD_FRONTEND_ID         0x0400  /* aka Configuration Manager */
#define MIC_MEDIA_PATROL_ID         0x0500  /* Media Patrol Manager */
#define MIC_LD_INIT_ID              0x0600  /* Logical Drive Init Manager */
#define MIC_EVENTMGR_ID             0x0700  /* Event Manager */
#define MIC_REBUILD_ID              0x0800  /* Rebuild Manager */
#define MIC_BKSYNC_ID               0x0900  /* BkSync Manager */
#define MIC_WATERMARK_ID            0x0A00  /* Watermark Manager */
#define MIC_SCSIEMU_ID              0x0B00  /* SCSI Emulation Manager */
#define MIC_REDUNDANCY_CHK_ID       0x0C00  /* Redundancy check Manager */
#define MIC_PASSTHRU_ID             0x0D00  /* PASSTHRU commands Manager*/
#define MIC_ISCSI_MGT_ID            0x0E00  /* iSCSI Configuration Manager */
#define MIC_ENCLOSURE_MGT_ID        0x0F00  /* Enclosure related management commands */
#define MIC_RWPROCESS_ID            0x1000  /* R/W Process Related Management Commands. */
#define MIC_BUZZER_ID               0x1100  /* Buzzer Related Management Cmds */
#define MIC_STATS_ID                0x1200  /* Statistics monitoring manager */
#define MIC_SPARECHECK_ID           0x1300  /* Periodical spare check      */
#define MIC_SPIN_DRV_ID             0x1400  /* Spin Drives - unused PDs    */
#define MIC_BBM_ID                  0x1500  /* Bad block management */
#define MIC_FC_MGT_ID               0x1600  /* FC Configuration Manager */
#define MIC_PSCSI_MGT_ID            0x1700  /* SCSI Front End driver */
#define MIC_SAS_MGT_ID              0x1800  /* SAS topology related */
#define MIC_MDD_SMART_ID            0x1900  /* SMART PD Operation */
#define MIC_INTERNAL_MGT_ID         0x1A00  /* Internal related */
#define MIC_FE_SAS_MGT_ID           0x1B00  /* Front End SAS MIC */
#define MIC_GENERIC_FE_MGT_ID       0x1C00  /* Generic Front End MIC */
#define MIC_FW_UPDATE_ID            0x1D00  /* Yosemite Firmware Update */
#define MIC_CBAY_FE_MGT_ID          0x1E00 /* Cbay specific frontend MICs */
#define MIC_SXP_ZONING_MGT_ID       0x1F00 /* SXP Zoning Management MICs */
#define MIC_LCD_MGT_ID              0x2000 /* LCD management commands */
#ifdef LUNCOPY
#define MIC_STORAGESERVICES_ID      0x2200 /* STORAGE SERVICES, LDCOPY, SNAPSHOT etc*/
#endif

/* General SubOpCodes:
 * 0xF0 -to- 0xFF -> Used for Sub Command Types
 * 0x80 -to- 0xEF -> Used for Extended 32 byte command
 * 0x00 -to- 0x7F -> Used for 16 byte command
 */
#define MIC_SUBOPCODE_EXTCMD_START  0x80
#define MIC_SUBOPCODE_EXTCMD_END    0xEF
/* for pass thru commands only */
#define MIC_SUBOPCODE_PTWRITE       (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 0
#define MIC_SUBOPCODE_PTREAD        (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 1
#define MIC_SUBOPCODE_PTNODATA      (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 2
#define MIC_SUBOPCODE_PT_PD_RESET   (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 3
#define MIC_SUBOPCODE_PT_JBOD_WRITE     (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 4
#define MIC_SUBOPCODE_PT_JBOD_READ      (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 5
#define MIC_SUBOPCODE_PT_JBOD_NODATA    (MIC_PASSTHRU_ID | MIC_SUBOPCODE_EXTCMD_START) + 6
#define MIC_SUBOPCODE_READ_EXECUTE      (MIC_PASSTHRU_ID | MIC_READ_EXECUTE_CMD)
#define MIC_SUBOPCODE_WRITE_EXECUTE     (MIC_PASSTHRU_ID | MIC_WRITE_EXECUTE_CMD)
#define MIC_SUBOPCODE_RELEASE_RESOURCE  (MIC_PASSTHRU_ID | MIC_RELEASE_RESOURCE)
#define MIC_SUBOPCODE_JBOD_READ_EXECUTE      (MIC_PASSTHRU_ID | MIC_JBOD_READ_EXECUTE_CMD)
#define MIC_SUBOPCODE_JBOD_WRITE_EXECUTE     (MIC_PASSTHRU_ID | MIC_JBOD_WRITE_EXECUTE_CMD)

/* commands for pass thru end*/
#define MIC_TEST_MODULE             0xFF
#define MIC_READ_EXECUTE_CMD        0xFE
#define MIC_WRITE_EXECUTE_CMD       0xFD
#define MIC_RELEASE_RESOURCE        0xFC
#define MIC_COMMAND_INFO            0xFB
#define MIC_JBOD_READ_EXECUTE_CMD   0xFA
#define MIC_JBOD_WRITE_EXECUTE_CMD  0xF9

/* Promise Management Interface Command Opcodes - Start */

#define PMIC_CONTROLLER_GET_INFO            (0x0001 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_GET_SETTINGS        (0x0002 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_SET_SETTINGS        (0x0003 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_READ_EXECUTE        (MIC_READ_EXECUTE_CMD | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_RELEASE_RESOURCE    (MIC_RELEASE_RESOURCE | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_WRITE_EXECUTE       (MIC_WRITE_EXECUTE_CMD | MIC_CTLR_CONFIG_ID)
#define PMIC_SUBSYSTEM_GET_INFO             (0x0004 | MIC_CTLR_CONFIG_ID)
#define PMIC_SUBSYSTEM_GET_SETTINGS         (0x0005 | MIC_CTLR_CONFIG_ID)
#define PMIC_SUBSYSTEM_SET_SETTINGS         (0x0006 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_GET_TIME            (0x0007 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_SET_TIME            (0x0008 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_GET_NVRAM_DUMP      (0x0009 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_CLEAR_NVRAM_DUMP    (0x000A | MIC_CTLR_CONFIG_ID)
#define PMIC_SUBSYSTEM_REBOOT               (0x000B | MIC_CTLR_CONFIG_ID)
#define PMIC_SUBSYSTEM_SHUTDOWN             (0x000C | MIC_CTLR_CONFIG_ID)
#define PMIC_HBA_SHUTDOWN                   (0x000D | MIC_CTLR_CONFIG_ID)
#define PMIC_PASSWORD_JUMPER_GET_STATUS     (0x000E | MIC_CTLR_CONFIG_ID)
#define PMIC_PASSWORD_JUMPER_CLEAR_STATUS   (0x000F | MIC_CTLR_CONFIG_ID)
#define PMIC_HBA_RESUME                     (0x0010 | MIC_CTLR_CONFIG_ID)
#define PMIC_POWER_SCHEDULE_SET_SETTINGS     (0x0011 | MIC_CTLR_CONFIG_ID)
#define PMIC_POWER_SCHEDULE_GET_SETTINGS     (0x0012 | MIC_CTLR_CONFIG_ID)
#define PMIC_SUBSYSTEM_POWEROFF              (0x0013 | MIC_CTLR_CONFIG_ID)


#define PMIC_CONTROLLER_ENTER_MAINTENANCE_MODE (0x0050 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_EXIT_MAINTENANCE_MODE (0x0051 | MIC_CTLR_CONFIG_ID)
#define PMIC_CLIQUE_GET_INFORMATION         (0x0052 | MIC_CTLR_CONFIG_ID)
#define PMIC_CLIQUE_GET_SETTINGS            (0x0053 | MIC_CTLR_CONFIG_ID)
#define PMIC_CLIQUE_SET_SETTINGS            (0x0054 | MIC_CTLR_CONFIG_ID)
#define PMIC_GET_FLASH_IMAGE_VERSION_INFO   (0x0060 | MIC_CTLR_CONFIG_ID)

#if defined(VESSAPP) || defined(_WINDRIVER) /* EXTAPI */
/* controller extend apis */
#define PMIC_CONTROLLER_EXT_API_GET         (0x0080 | MIC_CTLR_CONFIG_ID)
#define PMIC_CONTROLLER_EXT_API_SET         (0x0081 | MIC_CTLR_CONFIG_ID)
#endif


#define PMIC_GET_UINQUE_CMD_ID              (0x0005 | MIC_MCP_ID)
#define PMIC_RELEASE_UINQUE_CMD_ID          (0x0006 | MIC_MCP_ID)
#define PMIC_GET_CONFIG_LOCK                (0x0007 | MIC_MCP_ID)
#define PMIC_RELEASE_CONFIG_LOCK            (0x0008 | MIC_MCP_ID)
#define PMIC_MODIFY_CL_UCID_TIMEOUT         (0x0009 | MIC_MCP_ID)
#define PMIC_FORCE_RELEASE_CONFIG_LOCK      (0x000A | MIC_MCP_ID)
#define PMIC_VERIFY_CL_UCID                 (0x000B | MIC_MCP_ID)

#define PMIC_ARRAY_CREATE_CONFIGURATION      (0x0000 | MIC_MDD_FRONTEND_ID)
#define PMIC_ARRAY_DELETE_CONFIGURATION      (0x0001 | MIC_MDD_FRONTEND_ID)
#define PMIC_ARRAY_GET_CONFIGURATION         (0x0002 | MIC_MDD_FRONTEND_ID)
#define PMIC_LOGICAL_DRIVE_ADD              (0x0003 | MIC_MDD_FRONTEND_ID)
#define PMIC_LOGICAL_DRIVE_DELETE           (0x0004 | MIC_MDD_FRONTEND_ID)

#define PMIC_ARRAY_GET_INFORMATION           (0x0005 | MIC_MDD_FRONTEND_ID)
#define PMIC_ARRAY_GET_SETTINGS              (0x0006 | MIC_MDD_FRONTEND_ID)
#define PMIC_ARRAY_SET_SETTINGS              (0x0007 | MIC_MDD_FRONTEND_ID)

#define PMIC_PHYSICAL_DRIVE_GET_INFORMATION (0x0008 | MIC_MDD_FRONTEND_ID)
#define PMIC_PHYSICAL_DRIVE_GET_SETTINGS    (0x0009 | MIC_MDD_FRONTEND_ID)
#define PMIC_PHYSICAL_DRIVE_SET_SETTINGS    (0x000A | MIC_MDD_FRONTEND_ID)

#define PMIC_LOGICAL_DRIVE_GET_INFORMATION  (0x000B | MIC_MDD_FRONTEND_ID)
#define PMIC_LOGICAL_DRIVE_GET_SETTINGS     (0x000C | MIC_MDD_FRONTEND_ID)
#define PMIC_LOGICAL_DRIVE_SET_SETTINGS     (0x000D | MIC_MDD_FRONTEND_ID)

#define PMIC_GET_MISSING_PHYSICAL_DRIVES    (0x000E | MIC_MDD_FRONTEND_ID)
#define PMIC_PROCESS_INCOMPLETE_ARRAY       (0x000F | MIC_MDD_FRONTEND_ID)
#define PMIC_MIGRATE_ARRAY                  (0x0010 | MIC_MDD_FRONTEND_ID)
#define PMIC_MIGRATE_GETPROGRESS            (0x0011 | MIC_MDD_FRONTEND_ID)
#define PMIC_GET_TRANSITION_PD_INFO         (0x0012 | MIC_MDD_FRONTEND_ID)
#define PMIC_MIGRATE_CLEAR_STALE_NVWM       (0x0013 | MIC_MDD_FRONTEND_ID)
#define PMIC_SET_ARRAY_TRANSPORT_READY      (0x0014 | MIC_MDD_FRONTEND_ID)
#define PMIC_UNSET_ARRAY_TRANSPORT_READY    (0x0015 | MIC_MDD_FRONTEND_ID)
#define PMIC_SET_PDS_ONLINE_FOR_ARRAY       (0x0016 | MIC_MDD_FRONTEND_ID)

#define PMIC_MDD_READ_EXECUTE               (MIC_READ_EXECUTE_CMD | MIC_MDD_FRONTEND_ID)
#define PMIC_MDD_RELEASE_RESOURCE           (MIC_RELEASE_RESOURCE | MIC_MDD_FRONTEND_ID)
#define PMIC_MDD_WRITE_EXECUTE              (MIC_WRITE_EXECUTE_CMD | MIC_MDD_FRONTEND_ID)
#define PMIC_MDD_COMMAND_INFO               (MIC_COMMAND_INFO | MIC_MDD_FRONTEND_ID)

#define PMIC_SMART_SUBMIT_OP                (0x0001 | MIC_MDD_SMART_ID)
#define PMIC_SMART_GET_DIAG_STATUS          (0x0002 | MIC_MDD_SMART_ID)

#define PMIC_OBTAINLOCKKEY                  (0x0001 | MIC_LOCKMGR_ID)
#define PMIC_RELEASELOCKKEY                 (0x0002 | MIC_LOCKMGR_ID)

/* R/W Process General SubOpcode. */
#define PMIC_GET_ERR_TABLE              (0x0001 | MIC_RWPROCESS_ID)
#define PMIC_CLEAR_ERR_TABLE            (0x0002 | MIC_RWPROCESS_ID)

/* Background Task General SubOpCodes */
#define PMIC_SUBOPCODE_START            0x0001
#define PMIC_SUBOPCODE_STOP             0x0002
#define PMIC_SUBOPCODE_PAUSE            0x0003
#define PMIC_SUBOPCODE_RESUME           0x0004
#define PMIC_SUBOPCODE_GET_PROGRESS     0x0005
#define PMIC_SUBOPCODE_QUICK_INIT       0x0006

/* Media Patrol*/
#define PMIC_MEDIAPATROL_START              (PMIC_SUBOPCODE_START | MIC_MEDIA_PATROL_ID)
#define PMIC_MEDIAPATROL_STOP               (PMIC_SUBOPCODE_STOP | MIC_MEDIA_PATROL_ID)
#define PMIC_MEDIAPATROL_PAUSE              (PMIC_SUBOPCODE_PAUSE | MIC_MEDIA_PATROL_ID)
#define PMIC_MEDIAPATROL_RESUME             (PMIC_SUBOPCODE_RESUME | MIC_MEDIA_PATROL_ID)
#define PMIC_MEDIAPATROL_GETPROGRESS        (PMIC_SUBOPCODE_GET_PROGRESS | MIC_MEDIA_PATROL_ID)

/* Logical Drive Initialization*/
#define PMIC_LDI_START                      (PMIC_SUBOPCODE_START | MIC_LD_INIT_ID)
#define PMIC_LDI_STOP                       (PMIC_SUBOPCODE_STOP | MIC_LD_INIT_ID)
#define PMIC_LDI_PAUSE                      (PMIC_SUBOPCODE_PAUSE | MIC_LD_INIT_ID)
#define PMIC_LDI_RESUME                     (PMIC_SUBOPCODE_RESUME | MIC_LD_INIT_ID)
#define PMIC_LDI_GETPROGRESS                (PMIC_SUBOPCODE_GET_PROGRESS | MIC_LD_INIT_ID)
#define PMIC_LDI_QUICK_INIT                 (PMIC_SUBOPCODE_QUICK_INIT | MIC_LD_INIT_ID)

/* Rebuild */
#define PMIC_REBUILD_START                  (PMIC_SUBOPCODE_START | MIC_REBUILD_ID)
#define PMIC_REBUILD_STOP                   (PMIC_SUBOPCODE_STOP | MIC_REBUILD_ID)
#define PMIC_REBUILD_PAUSE                  (PMIC_SUBOPCODE_PAUSE | MIC_REBUILD_ID)
#define PMIC_REBUILD_RESUME                 (PMIC_SUBOPCODE_RESUME | MIC_REBUILD_ID)
#define PMIC_REBUILD_GETPROGRESS            (PMIC_SUBOPCODE_GET_PROGRESS | MIC_REBUILD_ID)
#define PMIC_REBUILD_TEST                   (MIC_TEST_MODULE | MIC_REBUILD_ID)

/* Background Synchronization */
#define PMIC_BKSYNC_STOP                    (PMIC_SUBOPCODE_STOP | MIC_BKSYNC_ID)
#define PMIC_BKSYNC_GETPROGRESS             (PMIC_SUBOPCODE_GET_PROGRESS | MIC_BKSYNC_ID)
#define PMIC_BKSYNC_TEST                    (MIC_TEST_MODULE | MIC_BKSYNC_ID)

/* SCSI_Emulation & LUN Masking & Mapping Module */
#define PMIC_LMM_GET_INITIATOR_LIST         (0x0000 | MIC_SCSIEMU_ID )
#define PMIC_LMM_ADD_INITIATOR              (0x0001 | MIC_SCSIEMU_ID )
#define PMIC_LMM_DELETE_INITIATOR           (0x0002 | MIC_SCSIEMU_ID )
#define PMIC_LMM_GET_LMMTABLE               (0x0003 | MIC_SCSIEMU_ID )
#define PMIC_LMM_ADD_LMMENTRY               (0x0004 | MIC_SCSIEMU_ID )
#define PMIC_LMM_SET_LMMENTRY               (0x0005 | MIC_SCSIEMU_ID )
#define PMIC_LMM_DELETE_LMMENTRY            (0x0006 | MIC_SCSIEMU_ID )
#define PMIC_LMM_GET_LMMTABLE_PSCSI         (0x0007 | MIC_SCSIEMU_ID )
#define PMIC_LMM_ADD_LMMENTRY_PSCSI         (0x0008 | MIC_SCSIEMU_ID )
#define PMIC_LMM_SET_LMMENTRY_PSCSI         (0x0009 | MIC_SCSIEMU_ID )
#define PMIC_LMM_DELETE_LMMENTRY_PSCSI      (0x000A | MIC_SCSIEMU_ID )

/* Redundancy check commands */
#define PMIC_RCK_START                  (PMIC_SUBOPCODE_START | MIC_REDUNDANCY_CHK_ID)
#define PMIC_RCK_STOP                   (PMIC_SUBOPCODE_STOP | MIC_REDUNDANCY_CHK_ID)
#define PMIC_RCK_PAUSE                  (PMIC_SUBOPCODE_PAUSE | MIC_REDUNDANCY_CHK_ID)
#define PMIC_RCK_RESUME                 (PMIC_SUBOPCODE_RESUME | MIC_REDUNDANCY_CHK_ID)
#define PMIC_RCK_GETPROGRESS            (PMIC_SUBOPCODE_GET_PROGRESS | MIC_REDUNDANCY_CHK_ID)
#define PMIC_RCK_TEST                   (MIC_TEST_MODULE | MIC_REDUNDANCY_CHK_ID)

#ifdef LUNCOPY
/* Logical Drive copy*/
#define PMIC_CREATE_ASSOCIATION         (0x01 | MIC_STORAGESERVICES_ID)
#define PMIC_DELETE_ASSOCIATION         (0x02 | MIC_STORAGESERVICES_ID)
#define PMIC_START_COPY                 (0x03 | MIC_STORAGESERVICES_ID)
#define PMIC_STOP_COPY                  (0x04 | MIC_STORAGESERVICES_ID)
#define PMIC_GET_COPY_PROGRESS          (0x05 | MIC_STORAGESERVICES_ID)
#define PMIC_GET_ASSOCIATION_INFO       (0x06 | MIC_STORAGESERVICES_ID)
#define PMIC_PAUSE_COPY                 (0x07 | MIC_STORAGESERVICES_ID)
#define PMIC_RESUME_COPY                (0x08 | MIC_STORAGESERVICES_ID)
#endif

/* ISCSI Management Related Commands */
#define PMIC_ISCSI_GET_INFORMATION          MIC_ISCSI_MGT_ID | 0x0001
#define PMIC_ISCSI_GET_PARAMETERS           MIC_ISCSI_MGT_ID | 0x0002
#define PMIC_ISCSI_SET_PARAMETERS           MIC_ISCSI_MGT_ID | 0x0003
#define PMIC_ISCSI_PING                     MIC_ISCSI_MGT_ID | 0x0004
#define PMIC_ISCSI_ADD_CHAP_RECORD          MIC_ISCSI_MGT_ID | 0x0005
#define PMIC_ISCSI_DEL_CHAP_RECORD          MIC_ISCSI_MGT_ID | 0x0006
#define PMIC_ISCSI_SET_CHAP_RECORD          MIC_ISCSI_MGT_ID | 0x0007
#define PMIC_ISCSI_GET_CHAP_RECORD          MIC_ISCSI_MGT_ID | 0x0008
#define PMIC_ISCSI_GET_NODE_LIST            MIC_ISCSI_MGT_ID | 0x0009
#define PMIC_ISCSI_RESET_NODE               MIC_ISCSI_MGT_ID | 0x000a
#define PMIC_ISCSI_RESET_PORT               MIC_ISCSI_MGT_ID | 0x000b
#define PMIC_ISCSI_RESET_SESS               MIC_ISCSI_MGT_ID | 0x000c
#define PMIC_ISCSI_ADD_PARAMETERS           MIC_ISCSI_MGT_ID | 0x0010
#define PMIC_ISCSI_DEL_PARAMETERS           MIC_ISCSI_MGT_ID | 0x0011
#define PMIC_ISCSI_NAS_GET_INFO             MIC_ISCSI_MGT_ID | 0x0012
#define PMIC_ISCSI_NAS_GET_SETTING          MIC_ISCSI_MGT_ID | 0x0013
#define PMIC_ISCSI_NAS_SET_SETTING          MIC_ISCSI_MGT_ID | 0x0014


/* Front End SAS MIC Definitions. */
#define PMIC_SAS_FE_GET_INFORMATION         (MIC_FE_SAS_MGT_ID | 0x0001)
#define PMIC_SAS_FE_GET_PARAMETERS          (MIC_FE_SAS_MGT_ID | 0x0002)
#define PMIC_SAS_FE_SET_PARAMETERS          (MIC_FE_SAS_MGT_ID | 0x0003)
#define PMIC_SAS_FE_GET_INITIATOR_LIST      (MIC_FE_SAS_MGT_ID | 0x0004)
#define PMIC_SAS_FE_GET_PHY_STATS           (MIC_FE_SAS_MGT_ID | 0x0005)


/* Generic Front End MIC Commands */
#define PMIC_FECMN_CLEAR_STATS              (MIC_GENERIC_FE_MGT_ID | 0x0001)
#define PMIC_SAS_FE_CLEAR_STATS             (MIC_GENERIC_FE_MGT_ID | 0x0001)
#define PMIC_FC_CLEAR_STATS                 (MIC_GENERIC_FE_MGT_ID | 0x0001)

/* Clearbay Front End MICs */
#define PMIC_GET_LMM_KEY                    (MIC_CBAY_FE_MGT_ID | 0x0001)
#define PMIC_SET_LMM_KEY                    (MIC_CBAY_FE_MGT_ID | 0x0002)
#define PMIC_GET_SLOT_WWN_MAPPING           (MIC_CBAY_FE_MGT_ID | 0x0003)

/* SAS Zoning Expander MICs */
#define PMIC_ZONING_GET_GROUP_MEMBERSHIP_TABLE (MIC_SXP_ZONING_MGT_ID | 0x0001)
#define PMIC_ZONING_GET_GROUP_PERMISSION_TABLE (MIC_SXP_ZONING_MGT_ID | 0x0002)
#define PMIC_ZONING_SET_GROUP_PERMISSION_TABLE (MIC_SXP_ZONING_MGT_ID | 0x0003)


/* Events */
#define PMIC_EVENT_CLEAR_LOG                (0x0001 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_DISABLE_LOGGING          (0x0002 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_ENABLE_LOGGING           (0x0003 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_GET                      (0x0004 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_GET_EVENTINFO            (0x0005 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_GET_SETTINGS             (0x0007 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_RESET_EVENTINFO          (0x0008 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_SET_EVENTINFO            (0x0009 | MIC_EVENTMGR_ID)
#define PMIC_EVENT_SET_SETTINGS             (0x000b | MIC_EVENTMGR_ID)
#define PMIC_EVENT_GET_STATS                (0x000c | MIC_EVENTMGR_ID)

/* 05/03/06 DC - Add Wait Event */
#define PMIC_EVENT_WAIT                     (0x000d | MIC_EVENTMGR_ID)
#define PMIC_EVENT_POST_SW_EVENT            (0x000e | MIC_EVENTMGR_ID)

/* Buzzer */
#define PMIC_BUZZER_TURN_ON                 (0x0000 | MIC_BUZZER_ID)
#define PMIC_BUZZER_TURN_OFF                (0x0001 | MIC_BUZZER_ID)
#ifdef DURATION_SUPPORTED
#define PMIC_BUZZER_SET_DURATION            (0x0002 | MIC_BUZZER_ID)
#define PMIC_BUZZER_GET_DURATION            (0x0003 | MIC_BUZZER_ID)
#endif
#define PMIC_BUZZER_GET_STATUS              (0x0004 | MIC_BUZZER_ID)

/* Statistics monitoring */
#define PMIC_STATS_RESET                    (0x0000 | MIC_STATS_ID)
#define PMIC_STATS_GET_CONTROLLER           (0x0003 | MIC_STATS_ID)
#define PMIC_STATS_GET_LOGICAL_DRIVE        (0x0004 | MIC_STATS_ID)
#define PMIC_STATS_GET_PHYSICAL_DRIVE       (0x0005 | MIC_STATS_ID)
#define PMIC_STATS_GET_PHYSICAL_DRIVE_EXT   (0x0006 | MIC_STATS_ID)   /* Get Phy Driver Statistic Extension Cmd */
#define PMIC_STATS_MONITOR_START            (0x0007 | MIC_STATS_ID)
#define PMIC_STATS_GET_STATISTICS           (0x0008 | MIC_STATS_ID)
#define PMIC_STATS_GET_STATISTICS_EXT       (0x0009 | MIC_STATS_ID)

/* Spare check */
#define PMIC_SPARECHECK_START               (PMIC_SUBOPCODE_START | MIC_SPARECHECK_ID)
#define PMIC_SPARECHECK_GET_STATUS          (PMIC_SUBOPCODE_GET_PROGRESS | MIC_SPARECHECK_ID)

/* Spin PD */
#define PMIC_SPIN_UP_DOWN_CHANGE_STATE      (PMIC_SUBOPCODE_START | MIC_SPIN_DRV_ID )
#define PMIC_SPIN_UP_DOWN_GET_STATUS        (PMIC_SUBOPCODE_GET_PROGRESS | MIC_SPIN_DRV_ID)

/* BBM */
#define PMIC_BBM_GET_DEFECT_LIST            (0x0000 | MIC_BBM_ID)
#define PMIC_BBM_CLEAR_DEFECT_LIST          (0x0001 | MIC_BBM_ID)

/* FC */        //[ABC] FC V4
#define PMIC_FC_GET_INFORMATION             MIC_FC_MGT_ID | 0x0001
#define PMIC_FC_GET_PARAMETERS              MIC_FC_MGT_ID | 0x0002
#define PMIC_FC_SET_PARAMETERS              MIC_FC_MGT_ID | 0x0003
#define PMIC_FC_GET_LOGGEDIN_DEVICE         MIC_FC_MGT_ID | 0x0004
#define PMIC_FC_GET_INITIATOR_LIST          MIC_FC_MGT_ID | 0x0005
#define PMIC_FC_GET_SYMBOLIC_NAME           MIC_FC_MGT_ID | 0x0006
#define PMIC_FC_SET_SYMBOLIC_NAME           MIC_FC_MGT_ID | 0x0007

/* SAS topology commans */
#define PMIC_GET_SAS_TOPOLOGY_INFO                      MIC_SAS_MGT_ID | 0x01
#define PMIC_SMP_GET_SAS_REPORT_GENERAL_DISCOVER_INFO   MIC_SAS_MGT_ID | 0x02
#define PMIC_GET_PHY_ERR_LOG                            MIC_SAS_MGT_ID | 0x03
#define PMIC_PHY_CONTROL                                MIC_SAS_MGT_ID | 0x04
#define PMIC_GET_PHY_ERR_LOG_FOR_C2C                    MIC_SAS_MGT_ID | 0x05
#define PMIC_PHY_CONTROL_C2C                            MIC_SAS_MGT_ID | 0x06

/* error codes for SAS mgt commands */
#define PMIC_SMP_RESPONSE_FN_UNKNOWN                 (MICS_MODULE_SPECIFIC_ERROR_START + 0x01)
#define PMIC_SMP_RESPONSE_FN_FAILED                  (MICS_MODULE_SPECIFIC_ERROR_START + 0x02)
#define PMIC_SMP_RESPONSE_INVALID_FRAME_LENGTH       (MICS_MODULE_SPECIFIC_ERROR_START + 0x03)
#define PMIC_SMP_RESPONSE_NO_PHY                     (MICS_MODULE_SPECIFIC_ERROR_START + 0x10)
#define PMIC_SMP_RESPONSE_NO_INDEX                   (MICS_MODULE_SPECIFIC_ERROR_START + 0x11)
#define PMIC_SMP_RESPONSE_NOT_SATA_PHY               (MICS_MODULE_SPECIFIC_ERROR_START + 0x12)
#define PMIC_SMP_RESPONSE_UNKNOWN_PHY_OP             (MICS_MODULE_SPECIFIC_ERROR_START + 0x13)

/* Generic front end commands */
#define PMIC_GENERIC_FE_CLEAR_STATS         (MIC_GENERIC_FE_MGT_ID | 0x0001)
#define PMIC_SAS_FE_CLEAR_STATS             (MIC_GENERIC_FE_MGT_ID | 0x0001)
#define PMIC_FC_CLEAR_STATS                 (MIC_GENERIC_FE_MGT_ID | 0x0001)

/* Firmware update commands */
#define PMIC_FWUPD_EXECUTE         (MIC_FW_UPDATE_ID | 0x0001)
#define PMIC_FWUPD_TRANSFER_IMG    (MIC_FW_UPDATE_ID | 0x0002)
#define PMIC_FWUPD_GET_STATUS      (MIC_FW_UPDATE_ID | 0x0003)

/* Promise Management Interface Command Opcodes - End */

/* error code for Stats Manager commands */
#define MICS_STATS_MONITOR_NOT_STARTED               (MICS_MODULE_SPECIFIC_ERROR_START + 0x01)

/* Command specific structures - Start */

/******************************************************************/
/* Image Version Support: PMIC_GET_FLASH_IMAGE_VERSION_INFO Begin */
/******************************************************************/
typedef struct micGetFlashImageVersionInfoCmd
{
    u8      gvi_ScsiOpCode;
    u8      gvi_MicSignature;
    u16     gvi_MicOpCode;
    u8      gvi_UniqueCmdId;
    u8      gvi_LoginKey;

    /* to specific slot0 or slot 1 controller,
    slot0 = 0x0, slot1 = 0x1, both = 0xff */
    u8      gvi_ControllerID;

    u8      gvi_Reserved0;
    u16     gvi_Reserved1;
    u16     gvi_TransferLength;
    u16     gvi_TransferOffset;

    /* to specific which Enclosure Info to get,
    first enclosure starts from 0 to 0xfe,
    and 0xff to get all system */
    u8      gvi_EnclosureID;

    Control_t   gvi_Control;
} PACKED micGetFlashImageVersionInfoCmd_t;

/*
*****
*/

typedef struct micImageVersionNumber
{
    /* must manually 8 byte align */
    u8      ivn_MajorVersionNo;
    u8      ivn_MinorVersionNo;
    u16     ivn_OEMCode;
    u8      ivn_BuildNo;
    u8      ivn_Reserved[11];
} PACKED micImageVersionNumber_t;

/*
*****
*/

typedef struct micImageDate
{
    /* must manually 8 byte align */
    u8      id_Month;
    u8      id_Day;
    u16     id_Year;
    u8      id_Hour;
    u8      id_Minute;
    u8      id_Second;
    u8      id_Reserved;
} PACKED micImageDate_t;

/*
*****
*/

#define IMAGE_CONDITION_FLASH       0x0
#define IMAGE_CONDITION_RUNNING     0x1

#define VERSION_INFO_ENTRY_STRUCT_REVZERO   0x0 /* initial structure rev # for micFlashImageVersionInfoEntry */

typedef struct micFlashImageVersionInfoEntry    // 64 byte structure
{
    u8  fivie_StructVersion;
    u8  fivie_EnclIndex;
    u8  fivie_CtrlIndex;
    u8  fivie_ImageType;
    u8  fivie_ImageCondition;   /* either CONDITION_FLASH or CONDITION_RUNNING */
    u8  fivie_Reserved[11];

    micImageVersionNumber_t     fivie_VersionNumber;
    micImageDate_t              fivie_BuildDate;
    micImageDate_t              fivie_FlashDate;

    u8  fivie_Reserved2[16];
} PACKED micFlashImageVersionInfoEntry_t;

/*
*****
*/

#define FLASH_IMG_VERSION_INFO_STRUCT_REVZERO   0x0 /* initial structure rev #  for  micFlashImageVersionInfo */

typedef struct micFlashImageVersionInfo
{
    u8      fivi_StructVersion;         /* struct ver is 0x0 for now */
    u8      fivi_Reserved;
    u16     fivi_NumberOfImageInfoEntries;
    u8      fivi_Reserved2[60];         // Reserved for future

    // The runtime info first, and then the flash/partition image info
    // All image is always the first one to be returned
    micFlashImageVersionInfoEntry_t     fivi_ImageEntry[1];
} PACKED micFlashImageVersionInfo_t;
/****************************************************************/
/* Image Version Support: PMIC_GET_FLASH_IMAGE_VERSION_INFO End */
/****************************************************************/

/* PMIC_SUBSYSTEM_GET_INFO */

typedef struct micSubsystemGetInfoCmd
{
    u8          gci_ScsiOpCode;
    u8          gci_MicSignature;
    u16         gci_MicOpCode;
    u8          gci_UniqueCmdId;
    u8          gci_LoginKey;
    u16         gci_Reserved0;
    u16         gci_Reserved1;
    u16         gci_TransferLength;
    u16         gci_TransferOffset;
    u8          gci_Reserved2;
    Control_t   gci_Control;
} PACKED micSubsystemGetInfoCmd_t;

typedef struct micSubsystemInfo
{
    u8      ssi_CustName[24];
    u8      ssi_CustModel[16];
    u8      ssi_MftPartNo[16];
    u8      ssi_MftSerialNo[16];
    u8      ssi_MftRev[8];
    u8      ssi_CustPartNo[16];
    u8      ssi_CustSerialNo[16];
    u8      ssi_CustRev[8];
    u8      ssi_WWN[8];
    u8      ssi_Reserved0[16];
    u8      ssi_MftName[48];
    u8      ssi_MftModel[48];
    u8      ssi_MftMonth;
    u8      ssi_MftDate;
    u16     ssi_MftYear;
    u8      ssi_Reserved1[5];
    u8      ssi_UserName[48];
    u8      ssi_MaxRAIDSSSupported;
    u8      ssi_MaxJOBExpSSSupported;
    u8      ssi_MaxCtlSupported;
    u8      ssi_InterConnectType;
    u8      ssi_Reserved2[61];
    u8      ssi_RAIDSSPresent;
    u8      ssi_JOBExpSSPresent;
    u8      ssi_NumberOfCtlPresent;
    u8      ssi_Reserved3[147];
} PACKED micSubsystemInfo_t;

/* Possible bit map value for ssi_InterConnectType */

#define ICT_NOT_DEFINED    0
#define ICT_SAS            1
//#define ICT_             2
//#define ICT_             4


/* PMIC_SUBSYSTEM_GET_SETTINGS */
/* PMIC_SUBSYSTEM_SET_SETTINGS */

typedef struct micSubsysGetSetSettingsCmd
{
    u8          sgss_ScsiOpCode;
    u8          sgss_MicSignature;
    u16         sgss_MicOpCode;
    u8          sgss_UniqueCmdId;
    u8          sgss_LoginKey;
    u16         sgss_Reserved0;
    u16         sgss_Reserved1;
    u16         sgss_TransferLength;
    u16         sgss_TransferOffset;
    u8          sgss_Reserved2;
    Control_t   sgss_Control;
} PACKED micSubsysGetSetSettingsCmd_t;
//} micSubsysGetSetSettingsCmd_t;

typedef struct micSubsystemSettings
{
    u8      ss_UserName[48];
    u8      ss_Reserved[208];
} PACKED micSubsystemSettings_t;

/* PMIC_CONTROLLER_GET_INFO */

#define MICS_FW_LUN_AFFINITY_DISABLED           MICS_MODULE_SPECIFIC_ERROR_START + 1
#define MICS_FW_CONTROLLER_NOT_PRESENT          MICS_MODULE_SPECIFIC_ERROR_START + 2
#define MICS_FW_SUBSYS_ACTIVE_STANDBY           MICS_MODULE_SPECIFIC_ERROR_START + 3
#define MICS_FW_SUBSYS_CRITICAL                 MICS_MODULE_SPECIFIC_ERROR_START + 4
#define MICS_FW_SUBSYS_SINGLE_CONTROLLER        MICS_MODULE_SPECIFIC_ERROR_START + 5

typedef struct micCtlGetInfoCmd
{
    u8          gci_ScsiOpCode;
    u8          gci_MicSignature;
    u16         gci_MicOpCode;
    u8          gci_UniqueCmdId;
    u8          gci_LoginKey;
    u16         gci_ControllerID;
    u8          gci_CodePage;
    u8          gci_Reserved;
    u16         gci_TransferLength;
    u16         gci_TransferOffset;
    u8          gci_ControllerCount;
    Control_t   gci_Control;
} PACKED micCtlGetInfoCmd_t;
//} micCtlGetInfoCmd_t;

/* Possible values for gci_CodePage*/
#define CTRL_PAGE_ALL               0xFF
#define CTRL_PAGE_RAID              0x00
#define CTRL_PAGE_FW_SW             0x01
#define CTRL_PAGE_HW_GENERIC        0x02
#define CTRL_PAGE_HW_OTHER          0x03
#define CTRL_PAGE_ISCSI_NETWORK     0x04
#define CTRL_PAGE_ETHER_NETWORK     0x05
#define CTRL_PAGE_HBA               0x06
#define CTRL_PAGE_MAINTENANCE_ETHER 0x07

#define COERCION_METHOD_GB_TRUNCATION    0      /* truncate to 1GB boundary */
#define COERCION_METHOD_10GB_TRUNCATION  1      /* truncate to 10GB boundary */
#define COERCION_METHOD_GROUP_ROUNDING   2      /* truncate the size based on certain capacity range */
#define COERCION_METHOD_OEM_TABLE        3     /* truncate according table, OEMs can custamize the table in flash file "/islavista/conf/fw/OEMCoercionTable.conf"*/
#define COERCION_METHOD_TEST             4     /* truncate to requested GB bytes */

/* Possible values for cs_SparePowerLevels and ci_SparePowerLevels */
#define HDD_POWER_SAVING_LEVEL_0 0 /* Disabled */
#define HDD_POWER_SAVING_LEVEL_1 1 /* Park R/W Heads */
#define HDD_POWER_SAVING_LEVEL_2 2 /* Park R/W Heads, Lower Rotation Speed */
#define HDD_POWER_SAVING_LEVEL_3 3 /* Park R/W Heads, Lower Rotation Speed, Spin-Down HDD */

/* Possible values for cs_HddSpinDownType and ci_HddSpinDownType */
#define HDD_SPIN_DOWN_TYPE_1 1 /* All drives */
#define HDD_SPIN_DOWN_TYPE_2 2 /* Spare drives and unconfigured drives only */

#define CS_PORT_PWRCTRL_NONE  0
#define CS_PORT_PWRCTRL_WOS   1

#if defined(VESSAPP) || defined(_WINDRIVER) /* PDCRITEMP */
#define CS_PD_CRI_TEMP_THRESHOLD_MIN        58
/*
** This is changed to avoid PD OTP shutdown.
**
#define CS_PD_CRI_TEMP_THRESHOLD_DEFAULT    58
#define CS_PD_CRI_TEMP_THRESHOLD_MAX        60
*/
#define CS_PD_CRI_TEMP_THRESHOLD_DEFAULT    65
#define CS_PD_CRI_TEMP_THRESHOLD_MAX        65

#define CS_PD_TEMP_THRESHOLD_MIN            50
#define CS_PD_TEMP_THRESHOLD_DEFAULT        55
#define CS_PD_TEMP_THRESHOLD_MAX            55
#else
#define CS_PD_TEMP_THRESHOLD_MIN            50
#define CS_PD_TEMP_THRESHOLD_DEFAULT        55
#define CS_PD_TEMP_THRESHOLD_MAX            60
#endif

typedef struct micControllerInfoPage0
{
    u16     ci_PageCode;
    u16     ci_PageLength;
    u16     ci_DeviceID;
    u8      ci_Reserved0[2];
    u8      ci_CustName[24];
    u8      ci_CustModel[16];
    u8      ci_MftPartNo[16];
    u8      ci_MftSerialNo[16];
    u8      ci_MftRev[8];
    u8      ci_CustPartNo[16];
    u8      ci_CustSerialNo[16];
    u8      ci_CustRev[8];
    u8      ci_WWN[8];
    u32     ci_CustCode;    /*for OEM NEC*/
    u8      ci_Reserved1[12];
    u8      ci_MftName[48];
    u8      ci_MftModel[48];
    u8      ci_MftMonth;
    u8      ci_MftDate;
    u16     ci_MftYear;
    u8      ci_Reserved2[4];
    u8      ci_UserName[48];
    u16     ci_ProductID;
    u8      ci_FrontEndInterfaceType;
    u8      ci_BackEndInterfaceType;
    u32     ci_Uptime;
    u64     ci_Uptime64;
    u8      ci_SCSIProtocolSupported;
    u8      ci_LastResetCause;
    u16     ci_MaxCmdSupported;
    u8      ci_MaxLogLBABitsSupported;
    u8      ci_RaidState;
    u8      ci_RescueMode;
    u8      ci_MaxSectorSizeCodeSupported;
    u32     ci_PreferedCacheLineSize;
    u32     ci_CurrentCacheLineSize;
    u32     ci_TotalNoOfCacheLines;
    u32     ci_NoOfCacheLinesInUse;
    u32     ci_NoOfDirtyCacheLines;
    u8      ci_Reserved4[36];
    u64     ci_MDDVersion;
    u32     ci_MaxMDDSizeReserved;
    u32     ci_MaxMDDSizeUsed;
    u8      ci_Reserved6[36];
    u16     ci_MaxDiskArraySupported;   /*if NEC = 4 , for yosemite 256*/
    u16     ci_DiskArrayPresent;
    u8      ci_Reserved7[36];
    u16     ci_MaxLogicalDriveSupported; /*if NEC = 32*/
    u16     ci_LogicalDrivePresent;
    u16     ci_LogicalDriveOnline;
    u16     ci_LogicalDriveOffline;
    u16     ci_LogicalDriveCritical;
    u8      ci_Reserved8[33];
    u8      ci_MaxEnclosureIDSupported;
    u16     ci_MaxPhysicalDriveIDSupported;
    u16     ci_MaxPhysicalDriveSupported;
    u16     ci_PhysicalDrivePresent;
    u16     ci_PhysicalDriveOnline;
    u16     ci_PhysicalDriveOffline;
    u16     ci_PhysicalDrivewithPFA;
    u16     ci_PhysicalDriveElementInArray;
    u16     ci_PhysicalDriveNotConfigured;
    u16     ci_PhysicalDriveMissing;
    u16     ci_PhysicalDriveRegen;
    u8      ci_Reserved9[28];
    u16     ci_MaxGlobalSparesSupported;
    u16     ci_GlobalSparesPresent;
    u16     ci_MaxDedicatedSparesSupported;
    u16     ci_DedicatedSparesPresent;
    u16     ci_MaxTempGlobalSparesSupported;
    u16     ci_TempGlobalSparesPresent;
    u16     ci_TempGlobalSparesUsed;
    u16     ci_MaxTempDedicatedSparesSupported;
    u16     ci_TempDedicatedSparesPresent;
    u16     ci_TempDedicatedSparesUsed;
    u8      ci_Reserved10[36];
    u16     ci_NoOfRebuilds;
    u16     ci_NoOfBkSync;
    u16     ci_NoOfMediaPatrol;
    u16     ci_NoOfRedCheck;
    u16     ci_NoOfLDInit;
    u16     ci_NoOfMigration;
    u16     ci_NoOfPDM;
    u16     ci_NoOfTransition;
    u16     ci_NoOfSpareCheck;
    u8      ci_Reserved11[28];
    u8      ci_RebuildRate;
    u8      ci_BkSyncRate;
    u8      ci_MediaPatrolRate;
    u8      ci_RedCheckRate;
    u8      ci_LDInitRate;
    u8      ci_MigrationRate;
    u8      ci_PDMRate;
    u8      ci_TransitionRate;
    u8      ci_Reserved11a[6];
    u32     ci_ReassignedBlockThreshold;
    u32     ci_ErrorBlockThreshold;
    u8      ci_Reserved12[22];
    u8      ci_AutoRebuildEnable;
    u8      ci_MediaPatrolEnable;
    u32     ci_MediaPatrolStartTime;
    u32     ci_MediaPatrolStopTime;
    u8      ci_SpinUpDownEnable;
    u8      ci_MediaPatrolPDCapacity;      /* 0 - Full Capacity, 1 - Configurable size */
#if defined(VESSAPP) || defined(_WINDRIVER)/* PDCRITEMP */
    u8      ci_Reserved13[29];       
    u8      ci_PDCriTempThreshold;
#else
    u8      ci_Reserved13[30];
#endif
    u32     ci_SmartPollInterval;           /* In seconds */
    u8      ci_SmartLogEnable;              /* 0 = disable, 1 = enable */
    u8      ci_Reserved14;
    u8      ci_PDTempThreshold;
    u8      ci_EnclosurePollInterval;
    u8      ci_TempThresholdWarning;
    u8      ci_TempThresholdCritical;
    u8      ci_CtrlTempThresholdWarning;
    u8      ci_CtrlTempThresholdCritical;
    u8      ci_NumOfDrivesToSpin;
    u8      ci_TimeBetweenSpinUp;
    u8      ci_CoercionEnable;
    u8      ci_CoercionMethod;
    u8      ci_ElevatorSortingEnable;
    u8      ci_BuzzerEnable;
    u8      ci_LUNMasking;
    u8      ci_MigrationWMStorage;
    u8      ci_WriteThruMode;
    u8      ci_OrphanMigNvramWMPresent;
    u8      ci_WriteBackCacheFlushInterval;
    u8      ci_CoercionDriveSize;  /* in GBs for testing only */
    u8      ci_LUNAffinityEnable;
    u8      ci_AdaptiveWriteBackCacheEnable;
    u8      ci_LmmKey;
    u8      ci_ALUAEnable;
    u8      ci_SyncCacheEnable;
    u8      ci_PseudoDeviceType;
    u8      ci_ForcedReadAheadEnable;    /* 0 = Disable 1 = Enable */
    u8      ci_CommonWWNNEnable;
    u8      ci_LcdModuleEnable;          /* 0 = Disable 1 = Enable */
    u8      ci_DisableDriveCmdCombining; /* 0 = combing enabled, 1 = combing disabled*/
    u8      ci_SparePowerLevels;
    u8      ci_HddSpinDownType;
    u16     ci_SpareIdleTime;         /* Park head : 0, 1~1440, unit: min */ //
    u16     ci_SpareStandbyTime;     /* LowerRotationSpeed : 0, 1~1440, unit: min */ //
    u16     ci_SpareStoppedTime;      /* Spin down : 0, 10~1440, unit: min */ //
    u16     ci_MaxRetryForFullStripe;  /* retry one time is 20ms in C-class */
    u8      ci_Reserved15[20];
    u8      ci_Reserved16[37];
    u8      ci_MaxDriveForParityRaid;
    u16     ci_MaxDriveInDiskArray;     /*if NEC = 4*/
    u8      ci_MaxAxleInLogicalDrive; /* For RAID50/51 and RAID60 */
    u8      ci_Reserved17a[3];
    /*
     * Bit      31   30 29 28 27 26 25 24 23 22 21 20     19     18     17     16 
     * Support                                    RAID60 RAID55 RAID51 RAID50 RAID10 
     * Bit      15   14 13 12 11 10 9  8  7  6  5  4      3      2      1      0 
     * Support  JBOD                              RAID6  RAID5  RAID1E RAID1  RAID0
     */
    u32     ci_RaidLevelSupportFlag;
    u32     ci_FirmwareFeaturesSuported1;
#define FB_SUP_UPS         0x00000001           /* Feature Support for UPS */
#define FB_SUP_LUNCLONE    0x00000002           /* Feature Support for LUNCLONE */
    u32     ci_FirmwareFeaturesSuported2;
    u32     ci_FirmwareFeaturesSuported3;
    u32     ci_FirmwareFeaturesSuported4;
    u8      ci_Reserved17[18];
    u8      ci_HASupported;
    u8      ci_ReadinessStatus;
    u8      ci_IsMaster;
    u8      ci_Reserved18[33];
    u16     ci_NoOfLogicalDriveReserved;
    u8      ci_Reserved19[36];
    u8      ci_DebugLevel;
    u8      ci_PortPowerCtrl;
    u8      ci_NCQDisable;
#if defined(VESSAPP) || defined(_WINDRIVER)
    u8      ci_OTPEnable; /* PDOTP, also affect controller temperature */
    u8      ci_Reserved20[68];
#else
    u8      ci_Reserved20[69];
#endif
} PACKED micControllerInfoPage0_t;

/*
 * Promise Interface Feature Bits for ci_RaidLevelSupportFlag. These values
 * are defined as mask bits so that it's easy to check the supported RAID
 * levels; or we can use them to construct the RAID levels that this system
 * is supporting.
 */
#define PI_FB_RAID_0     0x00000001
#define PI_FB_RAID_1     0x00000002
#define PI_FB_RAID_1E    0x00000004
#define PI_FB_RAID_5     0x00000008
#define PI_FB_RAID_6     0x00000010
#ifdef __RAID3__
#define PI_FB_RAID_3     0x00000020
#endif
#define PI_FB_RAID_JBOD  0x00008000
#define PI_FB_RAID_10    0x00010000
#define PI_FB_RAID_50    0x00020000
#define PI_FB_RAID_51    0x00040000
#define PI_FB_RAID_55    0x00080000
#define PI_FB_RAID_60    0x00100000
#ifdef __RAID30__
#define PI_FB_RAID_30    0x00200000
#endif

/* Possible values for ci_RaidState */
#define CTL_STATUS_UNKNOWN      0
#define CTL_STATUS_OK           1
#define CTL_STATUS_CRITICAL     2
#define CTL_STATUS_OFFLINE      3
#define CTL_STATUS_DEGRADED     4

/* Possible values for ci_DebugLevel &
   cs_DebugLevel */
#define DBG_MSG_LEVEL_DEBUG   1
#define DBG_MSG_LEVEL_INFO    2
#define DBG_MSG_LEVEL_WARNING 3
#define DBG_MSG_LEVEL_ERROR   4
#define DBG_MSG_LEVEL_FATAL   5
#define DBG_MSG_LEVEL_SILENT  6

/* Possible values for ci_ReadinessStatus */
/*       - Same as mci_ReadinessStatus    */

/* Possible values for ci_PreferedCacheLineSize &
   ci_CurrentCacheLineSize */
#define CACHE_LINE_8K       8
#define CACHE_LINE_64K      64

/* Possible values for ci_ProductID */
#define PT_M_SERIES_SUBSYSTEM         0x0100
#define PT_E_SERIES_SUBSYSTEM         0x0200
#define PT_J_SERIES_SUBSYSTEM         0x0300
#define PT_SUPERTRAK_SERIES_HBA       0x4000
#define PT_VR1000_SERIES_SUBSYSTEM    0x0400
#define PT_VJ1000_SERIES_SUBSYSTEM    0x0500
#define PT_Ex30_SERIES_SUBSYSTEM      0x0600
#define PT_VESS2000_SERIES_SUBSYSTEM  0x0700
/* Only for VessApp product used */
#define PT_VA1000_SERIES_SUBSYSTEM  PT_VR1000_SERIES_SUBSYSTEM
#define PT_VA2000_SERIES_SUBSYSTEM  PT_VESS2000_SERIES_SUBSYSTEM

/* J Series Product Line */
#define PL_J_VIRTUAL            0x0   // for virtual ctrl and BP, a HBA define
#define PL_J300                 0x1
#define PL_J310_J610            0x2   // J310 and J610 use same id
#define PL_TRACY                0x20  // tracy controller

/* J Series Product ID */
#define CTRL_J300       PL_J300 | PT_J_SERIES_SUBSYSTEM
#define CTRL_J610       PL_J310_J610 | PT_J_SERIES_SUBSYSTEM  /* J610 and J310 are the same */
#define CTRL_TRACY      PL_TRACY | PT_J_SERIES_SUBSYSTEM

/* M & E Series Product Line */
#define PL_500I                 0x0001
#define PL_300I                 0x0002
#define PL_200I                 0x0003
#define PL_500F                 0x0004
#define PL_300F                 0x0005
#define PL_200F                 0x0006
#define PL_500P                 0x0007
#define PL_300P                 0x0008
#define PL_200P                 0x000A

#define PL_510I                 0x0011
#define PL_310I                 0x0012
#define PL_210I                 0x0013
#define PL_510F                 0x0014
#define PL_310F                 0x0015
#define PL_210F                 0x0016
#define PL_510P                 0x0017
#define PL_310P                 0x0018
#define PL_210P                 0x001A
#define PL_510S                 0x001B
#define PL_310S                 0x001C
#define PL_210S                 0x001D

#define PL_610I                 0x001E
#define PL_610F                 0x001F
#define PL_610P                 0x0020
#define PL_610S                 0x0021

/* Product line for Clear Bay */
#define PL_CBAY          0x00E0

/* Product line for C-class */
/* 8Bays SAS 3.5" */
#define PL_1320S                0x0001
#define PL_1420S                0x0002
#define PL_1720S                0x0003
#define PL_1820S                0x0004

/* 12Bays SAS 3.5" */
#define PL_1730S                0x0005
#define PL_1830S                0x0006

/* 16bays SAS 3.5" */
#define PL_1740S                0x0007
#define PL_1840S                0x0008

/* 8Bays iSCSI 3.5" */
#define PL_1320I                0x0009
#define PL_1420I                0x000A
#define PL_1720I                0x000B
#define PL_1820I                0x000C

/* 12Bays iSCSI 3.5" */
#define PL_1730I                0x000D
#define PL_1830I                0x000E

/* 16bays iSCSI 3.5" */
#define PL_1740I                0x000F
#define PL_1840I                0x0010

/* 12bays JBOD 3.5" */
#define PL_1730                 0x0011
#define PL_1830                 0x0012

/* 16bays JBOD 3.5" */
#define PL_1740                 0x0013
#define PL_1840                 0x0014

/* 24bays JBOD 3.5" */
#define PL_1760                 0x0015
#define PL_1860                 0x0016

/* 4Bays iSCSI 3.5" */
#define PL_1710I                0x0017

/* 2U12bays SAS & iSCSI 3.5" Swappable FAN model */
#define PL_1731S                0x0018
#define PL_1831S                0x0019
#define PL_1731I                0x001A
#define PL_1831I                0x001B


/* M Series Product ID*/
#define CTRL_M500I     PL_500I | PT_M_SERIES_SUBSYSTEM
#define CTRL_M300I     PL_300I | PT_M_SERIES_SUBSYSTEM
#define CTRL_M200I     PL_200I | PT_M_SERIES_SUBSYSTEM

#define CTRL_M500F     PL_500F | PT_M_SERIES_SUBSYSTEM
#define CTRL_M300F     PL_300F | PT_M_SERIES_SUBSYSTEM
#define CTRL_M200F     PL_200F | PT_M_SERIES_SUBSYSTEM

#define CTRL_M500P     PL_500P | PT_M_SERIES_SUBSYSTEM
#define CTRL_M300P     PL_300P | PT_M_SERIES_SUBSYSTEM
#define CTRL_M200P     PL_200P | PT_M_SERIES_SUBSYSTEM

/* E Series Product ID */
#define CTRL_E500I     PL_500I | PT_E_SERIES_SUBSYSTEM
#define CTRL_E300I     PL_300I | PT_E_SERIES_SUBSYSTEM
#define CTRL_E200I     PL_200I | PT_E_SERIES_SUBSYSTEM

#define CTRL_E500F     PL_500F | PT_E_SERIES_SUBSYSTEM
#define CTRL_E300F     PL_300F | PT_E_SERIES_SUBSYSTEM
#define CTRL_E200F     PL_200F | PT_E_SERIES_SUBSYSTEM

#define CTRL_E500P     PL_500P | PT_E_SERIES_SUBSYSTEM
#define CTRL_E300P     PL_300P | PT_E_SERIES_SUBSYSTEM
#define CTRL_E200P     PL_200P | PT_E_SERIES_SUBSYSTEM

/* Mx10x Series Product ID */
#define CTRL_M610I     PL_610I | PT_M_SERIES_SUBSYSTEM
#define CTRL_M510I     PL_510I | PT_M_SERIES_SUBSYSTEM
#define CTRL_M310I     PL_310I | PT_M_SERIES_SUBSYSTEM
#define CTRL_M210I     PL_210I | PT_M_SERIES_SUBSYSTEM

#define CTRL_M510F     PL_510F | PT_M_SERIES_SUBSYSTEM
#define CTRL_M310F     PL_310F | PT_M_SERIES_SUBSYSTEM
#define CTRL_M210F     PL_210F | PT_M_SERIES_SUBSYSTEM

#define CTRL_M610P     PL_610P | PT_M_SERIES_SUBSYSTEM
#define CTRL_M510P     PL_510P | PT_M_SERIES_SUBSYSTEM
#define CTRL_M310P     PL_310P | PT_M_SERIES_SUBSYSTEM
#define CTRL_M210P     PL_210P | PT_M_SERIES_SUBSYSTEM

#define CTRL_M510S     PL_510S | PT_M_SERIES_SUBSYSTEM
#define CTRL_M310S     PL_310S | PT_M_SERIES_SUBSYSTEM
#define CTRL_M210S     PL_210S | PT_M_SERIES_SUBSYSTEM

/* E Series Product ID */
#define CTRL_E310F     PL_310F | PT_E_SERIES_SUBSYSTEM

#define CTRL_E310S     PL_310S | PT_E_SERIES_SUBSYSTEM
#define CTRL_E310I     PL_310I | PT_E_SERIES_SUBSYSTEM

#define CTRL_E610F     PL_610F | PT_E_SERIES_SUBSYSTEM
#define CTRL_E610S     PL_610S | PT_E_SERIES_SUBSYSTEM
#define CTRL_E610I     PL_610I | PT_E_SERIES_SUBSYSTEM

/* ClearBay Product ID */
#define CTRL_CBAY      PL_CBAY | PT_E_SERIES_SUBSYSTEM

/* VessRAID Series Product ID*/
#define CTRL_VR1320S            PL_1320S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1420S            PL_1420S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1720S            PL_1720S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1820S            PL_1820S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1730S            PL_1730S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1731S            PL_1731S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1830S            PL_1830S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1831S            PL_1831S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1740S            PL_1740S | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1840S            PL_1840S | PT_VR1000_SERIES_SUBSYSTEM

#define CTRL_VR1320I            PL_1320I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1420I            PL_1420I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1710I            PL_1710I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1720I            PL_1720I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1820I            PL_1820I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1730I            PL_1730I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1731I            PL_1731I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1830I            PL_1830I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1831I            PL_1831I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1740I            PL_1740I | PT_VR1000_SERIES_SUBSYSTEM
#define CTRL_VR1840I            PL_1840I | PT_VR1000_SERIES_SUBSYSTEM

/* VessJBOD Series Product ID*/
#define CTRL_VJ1730             PL_1730 | PT_VJ1000_SERIES_SUBSYSTEM
#define CTRL_VJ1740             PL_1740 | PT_VJ1000_SERIES_SUBSYSTEM
#define CTRL_VJ1760             PL_1760 | PT_VJ1000_SERIES_SUBSYSTEM
#define CTRL_VJ1830             PL_1830 | PT_VJ1000_SERIES_SUBSYSTEM
#define CTRL_VJ1840             PL_1840 | PT_VJ1000_SERIES_SUBSYSTEM
#define CTRL_VJ1860             PL_1860 | PT_VJ1000_SERIES_SUBSYSTEM




/* SuperTrak Series Product Line */
#define PL_EX8300               0x0000
#define PL_EX16300              0x0001

#define PL_EX8350               0x0008
#define PL_EX16350              0x0009

#define PL_EX865x               0x0020
#define PL_EX4650               0x0021
#define PL_EX8650               0x0022
#define PL_EX8654               0x0023
#define PL_EX8650EL             0x0024
#define PL_EX4650EL             0x0025
#define PL_EX8650M              0x0026
#define PL_EX8658               0x0027
#define PL_EX8650A              0x0028
#define PL_EX4650A              0x0029
#define PL_EX16650              0x002A
#define PL_EX16654              0x002B
#define PL_EX28654              0x002C


/* SuperTrak Series Product ID */
#define CTRL_EX8300    PL_EX8300  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX16300   PL_EX16300 | PT_SUPERTRAK_SERIES_HBA

#define CTRL_EX8350    PL_EX8350  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX16350   PL_EX16350 | PT_SUPERTRAK_SERIES_HBA


#define CTRL_EX865x    PL_EX865x   | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX4650    PL_EX4650   | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX8650    PL_EX8650   | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX8654    PL_EX8654   | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX8650EL  PL_EX8650EL | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX4650EL  PL_EX4650EL | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX8650M   PL_EX8650M  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX8658    PL_EX8658   | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX8650A   PL_EX8650A  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX4650A   PL_EX4650A  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX16650   PL_EX16650  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX16654   PL_EX16654  | PT_SUPERTRAK_SERIES_HBA
#define CTRL_EX28654   PL_EX28654  | PT_SUPERTRAK_SERIES_HBA


/* VessApp Series Product ID */
#define PL_NONE        0x01
#define PL_AEB         0x02  /* Analog Encoder Board */
#define PL_DAB         0x03  /* Display Accelerator Board */
#define PL_AEB_DAB     0x04  /* Include AEB & DAB */

#define CTRL_NSR500    PL_NONE    | PT_VA1000_SERIES_SUBSYSTEM
#define CTRL_NSR510    PL_AEB     | PT_VA1000_SERIES_SUBSYSTEM
#define CTRL_NSR520    PL_DAB     | PT_VA1000_SERIES_SUBSYSTEM
#define CTRL_NSR550    PL_AEB_DAB | PT_VA1000_SERIES_SUBSYSTEM

/* VA2000+
   VessApp 2nd generation Product ID 
   VessApp V840	  3U16 Sandy/Ivy Bridge, Redundant PSU, Single Controller	
   VessApp V740	  3U16 Sandy/Ivy Bridge, Single PSU, Single Controller	
   VessApp V750	  2U6 Sandy/Ivy Bridge, Single PSU, Single Controller	
   VessApp V850   2U6 Sandy/Ivy Bridge, Redundant PSU, Single Controller	
   VessApp V810	  1U4 Sandy/Ivy Bridge, Redundant PSU, Single Controller	
   VessApp V840n  3U16 Sandy/Ivy Bridge, Redundant PSU, Single Controller, NAS	
   VessApp C310	  4 Bay CedaView, Single PSU, Single Ctrl	
   VessApp C350	  6 Bay CedaView, Single PSU, Single Ctrl	
   VessApp C810	  1U4 CedaView, Redundant PSU, Single Ctrl	
*/
   
/* VessApp 2nd generation product line */
#define PL_V840        0x01 
#define PL_V740        0x02 
#define PL_V750        0x03 
#define PL_V850        0x04  
#define PL_V810        0x05  
#define PL_V840I       0x06  /* iSCSI Product for surveillance */
#define PL_V840N       0x07  /* NAS + ISCSI combined */

#define PL_C310        0x10  
#define PL_C350        0x11  
#define PL_C810        0x12  

#define CTRL_V840      ( PL_V840   | PT_VA2000_SERIES_SUBSYSTEM )
#define CTRL_V740      ( PL_V740   | PT_VA2000_SERIES_SUBSYSTEM )
#define CTRL_V850      ( PL_V850   | PT_VA2000_SERIES_SUBSYSTEM )
#define CTRL_V750      ( PL_V750   | PT_VA2000_SERIES_SUBSYSTEM )
#define CTRL_V810      ( PL_V810   | PT_VA2000_SERIES_SUBSYSTEM )
#define CTRL_V840I     ( PL_V840I  | PT_VA2000_SERIES_SUBSYSTEM )
#define CTRL_V840N     ( PL_V840N  | PT_VA2000_SERIES_SUBSYSTEM )


/* End VessApp 2nd generation Product ID */ 
   

/* Possible values for ci_FrontEndInterfaceType */
#define FEIT_UNKNOWN        0
#define FEIT_ISCSI          1
#define FEIT_FC             2
#define FEIT_SCSI           3
#define FEIT_PCI            4
#define FEIT_PCIE           4
#define FEIT_SAS            5
#define FEIT_FC_ISCSI       6
#define FEIT_SCSI_HOST      FEIT_SAS

/* Possible value for ci_BackEndInterfaceType */
#define BEIT_UNKNOWN        0
#define BEIT_SATA           1
//#define BEIT_ISCSI_DRIVER 2 no back end reserved
#define BEIT_SCSI           3
#define BEIT_SAS            4
#define BEIT_FC             5
//#define BEIT_FMU_DRIVER           6  reserved

/* These fields marked with _DO_NOT_USE are marked so because of a size
 * difference.  However, because a product is already release, we CANNOT remove
 * this fields.  These fields MUST remain filled with zeros AT ALL TIMES!
 */
typedef struct micControllerInfoPage1
{
    u16     ci1_PageCode;
    u16     ci1_PageLength;
    u16     ci1_DeviceID;
    u8      ci1_PriBootLoaderMajorNo;
    u8      ci1_PriBootLoaderMinorNo;
    u8      ci1_PriBootLoaderBuildNo;
    u8      ci1_PriBootLoaderBuildMonth;
    u8      ci1_PriBootLoaderBuildDate;
    u8      ci1_PriBootLoaderOEMCode_DO_NOT_USE; /* see above comment */
    u16     ci1_PriBootLoaderBuildYear;
    u8      ci1_PriFWMajorNo;
    u8      ci1_PriFWMinorNo;
    u8      ci1_PriFWBuildNo;
    u8      ci1_PriFWBuildMonth;
    u8      ci1_PriFWBuildDate;
    u8      ci1_PriFWOEMCode_DO_NOT_USE; /* see above comment */
    u16     ci1_PriFWBuildYear;
    u8      ci1_PriSWMajorNo;
    u8      ci1_PriSWMinorNo;
    u8      ci1_PriSWBuildNo;
    u8      ci1_PriSWBuildMonth;
    u8      ci1_PriSWBuildDate;
    u8      ci1_PriSWOEMCode_DO_NOT_USE; /* see above comment */
    u16     ci1_PriSWBuildYear;

   /* Single image version */
    u8      ci1_SingleImageMajorNo;
    u8      ci1_SingleImageMinorNo;
    u8      ci1_SingleImageBuildNo;
    u8      ci1_SingleImageBuildMonth;
    u8      ci1_SingleImageBuildDate;
    u8      ci1_SingleImageReserved; /* see above comment */
    u16     ci1_SingleImageBuildYear;

    /* BIOS version */
    u8      ci1_BIOSMajorNo;
    u8      ci1_BIOSMinorNo;
    u8      ci1_BIOSBuildNo;
    u8      ci1_BIOSBuildMonth;
    u8      ci1_BIOSBuildDate;
    u8      ci1_BIOSReserved; /* see above comment */
    u16     ci1_BIOSBuildYear;

#if defined(VESSAPP) || defined(_WINDRIVER) /* CDVER */
    /* installation cd version */
    u8      ci1_ICDMajorNo;
    u8      ci1_ICDMinorNo;
    u8      ci1_ICDBuildNo;
    u8      ci1_ICDBuildMonth;
    u8      ci1_ICDBuildDate;
    u8      ci1_ICDReserved; /* see above comment */
    u16     ci1_ICDBuildYear;

    u8      ci1_Reserved0[2];
#else
    u8      ci1_Reserved0[10];
#endif

    /* see comment directly above structure */
    u32     ci1_PriBootLoaderOemCode;
    u32     ci1_PriFWOemCode;
    u32     ci1_PriSWOemCode;
    u32     ci1_SingleImageOemCode;
    u32     ci1_BIOSOemCode;

#if defined(VESSAPP) || defined(_WINDRIVER) /* CDVER */
    u32     ci1_ICDOemCode;

    u8      ci1_Reserved1[64];
#else
    u8      ci1_Reserved1[68];
#endif
} PACKED micControllerInfoPage1_t;

typedef struct micControllerInfoPage2
{
    u16     ci2_PageCode;
    u16     ci2_PageLength;
    u16     ci2_DeviceID;
    u8      ci2_MaxCPUSupported;
    u8      ci2_NoOfCPUPresent;
    u8      ci2_NoOfCPUFailed;
    u8      ci2_Reserved0[7];
    u8      ci2_CPU1VendorName[24];
    u8      ci2_CPU1Revision[8];
    u16     ci2_CPU1PCIVendorId;
    u16     ci2_CPU1PCIDeviceId;
    u16     ci2_CPU1PCISubsysVendorId;
    u16     ci2_CPU1PCISubsysDeviceId;
    u16     ci2_CPU1BusWidth;
    u16     ci2_CPU1Speed;
    u8      ci2_Reserved1[36];
    u8      ci2_CPU2VendorName[24];
    u8      ci2_CPU2Revision[8];
    u16     ci2_CPU2PCIVendorId;
    u16     ci2_CPU2PCIDeviceId;
    u16     ci2_CPU2PCISubsysVendorId;
    u16     ci2_CPU2PCISubsysDeviceId;
    u16     ci2_CPU2BusWidth;
    u16     ci2_CPU2Speed;
    u8      ci2_Reserved2[36];
    u8      ci2_SystemCtlVendorName[24];
    u8      ci2_SystemCtlRevision[8];
    u16     ci2_SystemCtlPCIVendorId;
    u16     ci2_SystemCtlPCIDeviceId;
    u16     ci2_SystemCtlPCISubsysVendorId;
    u16     ci2_SystemCtlPCISubsysDeviceId;
    u8      ci2_Reserved3[36];
    u8      ci2_MemoryType;
    u8      ci2_MemoryBusWidth;
    u16     ci2_MemorySpeed;
    u8      ci2_MemoryECCType;
    u8      ci2_Reserved4[3];
    u32     ci2_MemorySize;
    u8      ci2_CachePartOfSysMemory;
    u8      ci2_CacheType;
    u8      ci2_CacheBusWidth;
    u8      ci2_CacheECCType;
    u16     ci2_CacheSpeed;
    u8      ci2_Reserved4a[2];
    u32     ci2_CacheSize;
    u8      ci2_Reserved5[5];
    u8      ci2_FlashType;
    u8      ci2_Reserved5a[2];
    u32     ci2_FlashSize;
    u32     ci2_MaxFlashWriteAllowed;
    u32     ci2_NoOfFlashWriteDone;
    u8      ci2_Reserved6[5];
    u8      ci2_NVRAMType;
    u8      ci2_Reserved6a[2];
    u32     ci2_NVRAMSize;
    u32     ci2_MaxNVRAMWriteAllowed;
    u32     ci2_NoOfNVRAMWriteDone;
    u8      ci2_Reserved7[84];
} PACKED micControllerInfoPage2_t;

/* Possible values for ci2_NVRAMType */
#define NVRAM_TYPE_UNKNOWN 0
#define NVRAM_TYPE_FRAM    1
#define NVRAM_TYPE_SRAM    2

/* Possible values for ci2_MemoryType */
#define PROM_MEMORY_TYPE_UNKNOWN 0
#define PROM_MEMORY_TYPE_DDR    1
#define PROM_MEMORY_TYPE_DDR2    2
#define PROM_MEMORY_TYPE_DDR3      3

typedef struct micControllerInfoPage3
{
    u16     ci3_PageCode;
    u16     ci3_PageLength;
    u16     ci3_DeviceID;
    u8      ci3_Reserved1[2];
    u8      ci3_MaxComPortSupported;
    u8      ci3_NoOfComPortPresent;
    u8      ci3_NoOfComPortFailed;
    u8      ci3_Reserved;
    u32     ci3_Com1MaxBaudSupported;
    u32     ci3_Com1CurrentBaud;
    u8      ci3_Com1Usage;
    u8      ci3_Com1Enabled;
    u8      ci3_Com1Reserved[18];
    u32     ci3_Com2MaxBaudSupported;
    u32     ci3_Com2CurrentBaud;
    u8      ci3_Com2Usage;
    u8      ci3_Com2Enabled;
    u8      ci3_Com2Reserved[18];
    u32     ci3_Com3MaxBaudSupported;
    u32     ci3_Com3CurrentBaud;
    u8      ci3_Com3Usage;
    u8      ci3_Com3Enabled;
    u8      ci3_Com3Reserved[18];
    u8      ci3_Reserved2[3];
    u8      ci3_NoOfTimerPresent;
    u32     ci3_Timer1Resolution;
    u32     ci3_Timer1Range;
    u8      ci3_Timer1Reserved[16];
    u32     ci3_Timer2Resolution;
    u32     ci3_Timer2Range;
    u8      ci3_Timer2Reserved[16];
    u8      ci3_Reserved3[2];
    u8      ci3_NoOfWatchdogTimerPresent;
    u8      ci3_WatchdogTimerEnabled;
    u32     ci3_WatchdogTimerCount;
    u8      ci3_RTCInfo[16];
    u8      ci3_Reserved4[92];
} PACKED micControllerInfoPage3_t;


#define MIC_FEATURE_IS_SUPPORTED            0x01
#define MIC_FEATURE_NOT_SUPPORTED           0x00

#define MIC_FEATURE_IS_ENABLED              0x01
#define MIC_FEATURE_IS_DISABLED             0x00


/* Size: 144 */
/* default values are only for port 0 - for other ports all values will be 0 */
typedef struct micNetworkPortInfoSettings
{
    u16     npis_PortId;                            /* dflt: 0 */
    u8      npis_PortControl;                       /* dflt: 0 */
#define PORT_INFO_MODIFIED          0x01
    u8      npis_Reserved0;

    u8      npis_PortEnableDisableSupported;        /* dflt: 1 */
    u8      npis_PortEnabled;                       /* dflt: 1 */
    u8      npis_PortStatus;                        /* dflt: 0 */
#define PORT_STATUS_LINK_UP                     0x1 /* Bit 0..6 */
#define PORT_STATUS_LINK_DOWN                   0x2 /* Bit 0..6 */
#define PORT_STATUS_LINK_NOT_PRESENT            0x3 /* Bit 0..6 */
#define PORT_STATUS_BIT7_ACTIVE                 0x0 /* Bit 7 of npis_PortStatus */
#define PORT_STATUS_BIT7_STANDBY                0x1 /* Bit 7 of npis_PortStatus */

    u8      npis_SecondaryMacSupported;             /* dflt: 0 */

    u8      npis_PrimaryMACAddress[8];              /* dflt: all 0 */
    u8      npis_SecondaryMACAddress[8];            /* dflt: all 0 */

    u8      npis_DHCPSupported;                     /* dflt: 1 */
    u8      npis_DHCPEnabled;                       /* dflt: 0 */
    u8      npis_IPAddressType;                     /* dflt: PORT_MIC_IP_ADDRESS_TYPE_V4 */


#define PORT_MIC_IP_ADDRESS_TYPE_V4             0x4
#define PORT_MIC_IP_ADDRESS_TYPE_V6             0x6

    u8      npis_SecondaryIPAddressSupported;       /* dflt: 0 */

    u8      npis_PrimaryIPAddress[16];              /* dflt: [0] = 10
                                                             [1] = 0
                                                             [2] = 0
                                                             [3] = 2
                                                    */
    u8      npis_PrimarySubnetMask[16];             /* dflt: [0] = 255
                                                             [1] = 0
                                                             [2] = 0
                                                             [3] = 0
                                                    */

    u8      npis_SecondaryIPAddress[16];            /* dflt: 0 */
    u8      npis_SecondarySubnetMask[16];           /* dflt: 0 */

    /* the DSN fields do not apply for Ethernet for now. */
    u8      npis_PrimaryDNSServerIPAddress[16];     /* dflt: all 0 */
    u8      npis_SecondaryDNSServerIPAddress[16];   /* dflt: all 0 */

    u8      npis_DefaultGatewayIPAddress[16];       /* dflt: all 0 */

    u8      npis_DNSLearningThroughDHCPIsSupported; /* dflt: all 0 */
    u8      npis_DNSLearningThroughDHCP;            /* dflt: all 0 */

    u8      npis_WOL_Status;                        /* dflt: 0x00 */

#define PORT_MIC_WOL_MAGIC_PACKET_WAKE_ENABLE       0x01
#define PORT_MIC_WOL_MAGIC_PACKET_SLEEP_ENABLE      0x02

#define PORT_MIC_WOL_MAGIC_PACKET_ENABLE            0x80
#define PORT_MIC_WOL_MAGIC_PACKET_DISABLE           0x00

    u8      npis_Reserved1;                         /* For 8-byte alignment */
} PACKED micNetworkPortInfoSettings_t;

#define ETHERNET_PORT_USAGE_MANAGEMENT  0
#define ETHERNET_PORT_USAGE_INTERCOMM   1

typedef struct micEthernetPortNetworkInfo
{
    micNetworkPortInfoSettings_t    epni_NetworkPortInfo;
    /* vendor info */
    u8      epni_VendorName[24];
    u8      epni_Revision[8];
    u16     epni_PCIVendorId;
    u16     epni_PCIDeviceId;
    u16     epni_PCISubsysVendorId;
    u16     epni_PCISubsysDeviceId;
    u8      epni_Reserved[38];
    /* ethernet specific info */
    u16     epni_MaxSupportedSpeed;
    u8      epni_Usage;  /* management or inter-ctrl communication */
    u8      epni_Reserved1[2];
    } PACKED micEthernetPortNetworkInfo_t;

typedef struct miciSCSIPortNetworkInfo
{
    micNetworkPortInfoSettings_t    ipni_NetworkPortInfo;
    /* vendor info */
    u16     ipni_PCIVendorID;
    u16     ipni_PCIDeviceID;

    u16     ipni_PCISubSystemVendorID;
    u16     ipni_PCISubSystemDeviceID;

    u32     ipni_Version;
    u32     ipni_FirmwareVersion;

    /* iscsi specific info */
    u8      ipni_FrontEndProtocol;
    u8      ipni_LinkType;

#define     LINK_TYPE_COPPER        0x01
#define     LINK_TYPE_OPTICAL       0x02
    u16     ipni_TCPPortNumber;

    u32     ipni_MaxSupportedSpeed;  /* In Mbps */

    u32     ipni_CurrentSpeed; /* In Mbps */

    /* Jumbo Frame
     */
    u8    ipni_JumboFrameEnabled;    /* Jumbo Frame Enable Status */
#define IPNI_JUMBO_FRAME_DISABLE                0x00
#define IPNI_JUMBO_FRAME_ENABLE                 0x01

    u8    ipni_Reserved1[3];         /* padding/8 byte alignment */
} PACKED miciSCSIPortNetworkInfo_t;


typedef struct micISCSIPortNetworkSettings
{
    micNetworkPortInfoSettings_t ipns_PortSettings;
    u16  ipns_TcpPortNumber;

    /* Jumbo Frame
     */
    u8    ipns_JumboFrameEnabled;  /* Jumbo Frame Enable Status */
#define IPNS_JUMBO_FRAME_DISABLE              0x00
#define IPNS_JUMBO_FRAME_ENABLE               0x01
    u8    ipns_Reserved;           /* padding */
    u32   ipns_MaxTxUnit;          /* Maximum Transfer Unit */
}PACKED micISCSIPortNetworkSettings_t;

typedef struct micEthernetPortNetworkSettings
{
    micNetworkPortInfoSettings_t    epns_NetworkPortSettings;
} PACKED micEthernetPortNetworkSettings_t;


typedef struct micControllerInfoPage4
{
    u16     ci4_PageCode;
    u16     ci4_PageLength;

    u16     ci4_DeviceID;   /* ctrl id */
    u16     ci4_Reserved;

    u8      ci4_MaxPortsSupported;
    u8      ci4_NumOfPortsPresent;
    u8      ci4_NumOfPortsFailed;
    u8      ci4_Reserved1[1];

    u8      ci4_Reserved2[12]; /* For 8-byte alignment */

    /* length of ci4_PortInfo can be variable depending on the ci4_NumOfPortsPresent */
    miciSCSIPortNetworkInfo_t   ci4_PortInfo[1];
} PACKED micControllerInfoPage4_t;

typedef struct micControllerInfoPage5
{
    u16     ci5_PageCode;
    u16     ci5_PageLength;

    u16     ci5_DeviceID;   /* ctrl id */
    u16     ci5_Reserved;

    u8      ci5_MaxPortsSupported;
    u8      ci5_NumOfPortsPresent;
    u8      ci5_NumOfPortsFailed;
    u8      ci5_Reserved1[1];

    u8      ci5_Reserved2[8];

    /* length of ci5_PortInfo can be variable depending on the ci5_NumOfPortsPresent */
    micEthernetPortNetworkInfo_t   ci5_PortInfo[1];
} PACKED micControllerInfoPage5_t;

/* micControllerInfoPage6 is specific to HBA products */
typedef struct micControllerInfoPage6
{
    u16     ci6_PageCode;
    u16     ci6_PageLength;
    u16     ci6_DeviceID;
    u16     ci6_ProductID;
    u8      ci6_CustName[24];
    u8      ci6_CustModel[16];
    u8      ci6_MftPartNo[16];
    u8      ci6_MftSerialNo[16];
    u8      ci6_MftRev[8];
    u8      ci6_CustPartNo[16];
    u8      ci6_CustSerialNo[16];
    u8      ci6_CustRev[8];
    u8      ci6_MftName[48];
    u8      ci6_MftModel[48];
    u8      ci6_MftMonth;
    u8      ci6_MftDate;
    u16     ci6_MftYear;
    u8      ci6_RebuildRate;
    u8      ci6_BkSyncRate;
    u8      ci6_MediaPatrolRate;
    u8      ci6_OnlineExpRate;
    u8      ci6_LDInitRate;
    u8      ci6_MigrationRate;
    u8      ci6_AutoRebuildEnable;
    u8      ci6_MediaPatrolEnable;
    u8      ci6_SmartLogEnable;
    u8      ci6_SmartPollInterval;
    u8      ci6_SmartLogLevel;
    u8      ci6_EnclosurePollInterval;
    u8      ci6_MemoryType;
    u8      ci6_MemoryECCType;
    u16     ci6_MemorySpeed;
    u32     ci6_MemorySize;
    u16     ci6_MaxLogicalDriveSupported;
    u16     ci6_LogicalDrivePresent;
    u16     ci6_LogicalDriveOnline;
    u16     ci6_LogicalDriveOffline;
    u16     ci6_LogicalDriveCritical;
    u16     ci6_MaxPhysicalDriveSupported;
    u16     ci6_PhysicalDrivePresent;
    u16     ci6_PhysicalDriveOnline;
    u16     ci6_PhysicalDriveOffline;
    u16     ci6_PhysicalDriveNotConfigured;
    u16     ci6_MaxChannelsSupported;//[cz]add
    u16     ci6_MaxGlobalSparesSupported;
    u16     ci6_GlobalSparesPresent;
    u16     ci6_MaxDedicatedSparesSupported;
    u16     ci6_DedicatedSparesPresent;
    u16     ci6_NoOfRebuilds;
    u16     ci6_NoOfBkSync;
    u16     ci6_NoOfMediaPatrol;
    u16     ci6_NoOfLDInit;
    u16     ci6_NoOfMigration;
    u8      ci6_AliasName[48];
}PACKED micControllerInfoPage6_t;

typedef struct micControllerInfoPage7
{
    u16     ci7_PageCode;
    u16     ci7_PageLength;

    u16     ci7_DeviceID;   /* ctrl id */
    u16     ci7_Reserved;

    u8      ci7_MaxPortsSupported;
    u8      ci7_NumOfPortsPresent;
    u8      ci7_NumOfPortsFailed;
    u8      ci7_Reserved1[1];

    u8      ci7_Reserved2[8];

    /* length of ci7_PortInfo can be variable depending on the ci7_NumOfPortsPresent */
    micEthernetPortNetworkInfo_t   ci7_PortInfo[1];
} PACKED micControllerInfoPage7_t;

/* PMIC_CONTROLLER_GET_SETTINGS */
/* PMIC_CONTROLLER_SET_SETTINGS */

typedef struct micCtlGetSetSettingsCmd
{
    u8          gscs_ScsiOpCode;
    u8          gscs_MicSignature;
    u16         gscs_MicOpCode;
    u8          gscs_UniqueCmdId;
    u8          gscs_LoginKey;
    u16         gscs_ControllerID;
    u8          gscs_CodePage;
    u8          gscs_Reserved;
    u16         gscs_TransferLength;
    u16         gscs_TransferOffset;
    u8          gscs_ControllerCount;
    Control_t   gscs_Control;
} PACKED micCtlGetSetSettingsCmd_t;
//} micCtlGetSetSettingsCmd_t;

/*
 * For PMIC_CONTROLLER_SET_SETTINGS gci_ConfigLock is used
 * instead of gci_LoginKey
 */
#define gci_ConfigLock  gci_LoginKey
#define MAX_CONTROLLER_USERNAME_BYTES    48

typedef struct micCtrlSettingsPage0
{
    u16     cs_PageCode;
    u16     cs_PageLength;
    u16     cs_DeviceID;
    u8      cs_UserName[MAX_CONTROLLER_USERNAME_BYTES];
    u8      cs_Reserved0[38];
    u32     cs_PreferedCacheLineSize;   /* default: 64KB              */
    u8      cs_Reserved1[36];
    u8      cs_RebuildRate;             /* default: High               */
    u8      cs_BkSyncRate;              /* default: low                */
    u8      cs_MediaPatrolRate;         /* default: Low                */
    u8      cs_RedCheckRate;            /* default: Medium             */
    u8      cs_LDInitRate;              /* default: Medium             */
    u8      cs_MigrationRate;           /* default: High               */
    u8      cs_PDMRate;                 /* default: High               */
    u8      cs_TransitionRate;          /* default: Medium             */
    u8      cs_Reserved1a[2];
    u8      cs_RescueMode;
    u8      cs_AutoRebuildToDeadDiskEnable;
    u32     cs_ReassignedBlockThreshold;/* default: 1                  */
    u32     cs_ErrorBlockThreshold;     /* default: 50                 */
    u8      cs_Reserved2[26];
    u8      cs_AutoRebuildEnable;       /*     default: Enabled            */
    u8      cs_MediaPatrolEnable;       /*     default: Enable             */
    u32     cs_MediaPatrolStartTime;    /*     default: n/a                */
    u32     cs_MediaPatrolStopTime;     /*     default:n/a                 */
    u8      cs_SpinUpDownEnable;        /*     default:disabled            */
    u8      cs_MediaPatrolPDCapacity;   /*  Default - 0 Entire PD capacity */
#if defined(VESSAPP) || defined(_WINDRIVER)
    u8      cs_Reserved3[21];     
    u8      cs_PDCriTempThreshold;
#else
    u8      cs_Reserved3[22];
#endif
    u32     cs_SmartPollInterval;
    u8      cs_SmartLogEnable;
    u8      cs_Reserved4;
    u8      cs_PDTempThreshold;
    u8      cs_EnclosurePollInterval;     /*     default:15 seconds                */
    u8      cs_TempThresholdWarning;      /*     default:45 degrees celcius        */
    u8      cs_TempThresholdCritical;     /*     default:50 degrees celcius        */
    u8      cs_CtrlTempThresholdCritical; /*     default:50 degrees celcius        */
    u8      cs_CtrlTempThresholdWarning;  /*     default:55 degrees celcius        */
    u8      cs_NumOfDrivesToSpin;         /*     currently not used                */
    u8      cs_TimeBetweenSpinUp;         /*     currently not used                */
    u8      cs_CoercionEnable;            /*     default: Enabled                  */
    u8      cs_CoercionMethod;            /*     default: Aligned to GB boundry(0) */
    u8      cs_ElevatorSortingEnable;     /*     default: Enabled                  */
    u8      cs_BuzzerEnable;              /*     default: Enabled                  */
    u8      cs_LUNMasking;                /*     default: Disabled             */
    u8      cs_MigrationWMStorage;
    u8      cs_WriteBackCacheFlushInterval; /*   default: 3 sec */
    u8      cs_CoercionDriveSize;  /* default 3 gb for testing only */
    u8      cs_LUNAffinityEnable;
    u8      cs_AdaptiveWriteBackCacheEnable;  /* default is disabled*/
    u8      cs_LmmKey;/* def: (cbay:SLOTBASED  rest:LMMKEY_WWNBASED) */
    u8      cs_ALUAEnable;
    u8      cs_SyncCacheEnable;
    u8      cs_PseudoDeviceType;
    u8      cs_ForcedReadAheadEnable; /* 0 = Disable 1 = Enable */
    u8      cs_CommonWWNNEnable;
    u8      cs_LcdModuleEnable;     /* 0 = Disable 1 = Enable */
    u8      cs_DisableDriveCmdCombining; /* 0 = combing enabled, 1 = combing disabled*/
    u8      cs_SparePowerLevels; //Diann - Original is  cs_HddPowerSavingLevels
    u8      cs_HddSpinDownType;
    u16     cs_SpareIdleTime;               /* Park head : 0, 1~1440, unit : min */
    u16     cs_SpareStandbyTime;          /* LowerRotationSpeed : 0, 1~1440, unit : min */
    u16     cs_SpareStoppedTime;            /* Spin down : 0, 10~1440, unit : min */
    u16     cs_MaxRetryForFullStripe;       /* retry one time is 20ms in C-class  */
    u8      cs_PortPowerCtrl;
    u8      cs_Reserved4a; /* cs_NCQDisable, used for VessRaid */
#if defined(VESSAPP)
    u8      cs_OTPEnable; /* PDOTP, also affect controller temp */
#else
    u8      cs_Reserved5;
#endif
    u8      cs_DebugLevel;
    u8      cs_Reserved6[126];
} PACKED micCtrlSettingsPage0_t;

typedef struct micCtrlSettingsPage3
{
    u16     cs3_PageCode;
    u16     cs3_PageLength;
    u16     cs3_DeviceID;
    u8      cs3_Reserved[2];
    u32     cs3_Com1CurrentBaud;
    u8      cs3_Com1Enabled;
    u8      cs3_Com1Reserved[15];
    u32     cs3_Com2CurrentBaud;
    u8      cs3_Com2Enabled;
    u8      cs3_Com2Reserved[15];
    u32     cs3_Com3CurrentBaud;
    u8      cs3_Com3Enabled;
    u8      cs3_Com3Reserved[18];
    u8      cs3_WatchdogTimerEnabled;
    u32     cs3_WatchdogTimerCount;
    u8      cs3_Reserved1[16];
    u8      cs3_RTCInfo[16];
    u8      cs3_Reserved2[156];
} PACKED micCtrlSettingsPage3_t;

typedef struct micCtrlSettingsPage4
{
    u16     cs4_PageCode;
    u16     cs4_PageLength;

    u16     cs4_DeviceID;
    u16     cs4_NumPorts;

    /* the length of cs4_PortSettings can be variable */
    micISCSIPortNetworkSettings_t   cs4_PortSettings[1];
}PACKED  micCtrlSettingsPage4_t;

typedef struct micCtrlSettingsPage5
{
    u16     cs5_PageCode;
    u16     cs5_PageLength;

    u16     cs5_DeviceID;
    u16     cs5_Reserved0;

    /* the length of cs5_PortSettings can be variable */
    micEthernetPortNetworkSettings_t    cs5_PortSettings[1];
} PACKED  micCtrlSettingsPage5_t;

/* micCtrlSettingsPage6 is specific to HBA products */
typedef struct micCtrlSettingsPage6
{
    u16     cs6_PageCode;
    u16     cs6_PageLength;
    u16     cs6_DeviceID;
    u8      cs6_RebuildRate;
    u8      cs6_BkSyncRate;
    u8      cs6_MediaPatrolRate;
    u8      cs6_RedCheckRate;
    u8      cs6_LDInitRate;
    u8      cs6_MigrationRate;
    u8      cs6_AutoRebuildEnable;
    u8      cs6_MediaPatrolEnable;
    u8      cs6_SmartPollInterval;
    u8      cs6_SmartLogEnable;
    u8      cs6_EnclosurePollInterval;
    u8      cs6_BuzzerEnable;
    u8      cs6_Reserved[6];
 } PACKED micCtrlSettingsPage6_t;

typedef struct micCtrlSettingsPage7
{
    u16     cs7_PageCode;
    u16     cs7_PageLength;

    u16     cs7_DeviceID;
    u16     cs7_Reserved0;

    /* the length of cs7_PortSettings can be variable */
    micEthernetPortNetworkSettings_t    cs7_PortSettings[1];
} PACKED micCtrlSettingsPage7_t;

typedef struct micPowerScheduleGetSetCmd
{
    u8          ps_ScsiOpCode;
    u8          ps_MicSignature;
    u16         ps_MicOpCode;
    u8          ps_UniqueCmdId;
    u8          ps_LoginKey;
    u16         ps_ControllerID;
    u16         ps_Reserved0;
    u16         ps_TransferLength;
    u16         ps_TransferOffset;
    u8          ps_Reserved1;
    Control_t   ps_Control;
}PACKED micPowerScheduleGetSetSettingsCmd_t;

typedef struct micPowerScheduleSetting
{
    u8      ps_Status;
#define MIC_POWER_SCHEDULE_DAILY                      0x01
#define MIC_POWER_SCHEDULE_WEEKLY                   0x02
#define MIC_POWER_SCHEDULE_MONTHLY                 0x04
#define MIC_POWER_SCHEDULE_SPECIFIC_DATE       0x08
#define MIC_POWER_SCHEDULE_DISABLE                  0x00
    u8      ps_Reserved0[3];

    /* Specific date or the first regular date in UTC format */
    u64 ps_UTC_PowerOnTime;
} PACKED micPowerScheduleSetting_t;

#if defined(VESSAPP) || defined(_WINDRIVER) /* EXTAPI */

/* extend api properties */
#define CEA_PROP_OEM_MODEL_SIGNATURE      0x01
#define CEA_PROP_OEM_SERIAL_NO            0x02
#define CEA_PROP_WWN                      0x03
#define CEA_PROP_VPD_MB                   0x04
#define CEA_PROP_VPD_BP                   0x05
#define CEA_PROP_VPD_PSU                  0x06


typedef struct micCtrlExtApiGetSetCmd
{
    u8          cea_ScsiOpCode;
    u8          cea_MicSignature;
    u16         cea_MicOpCode;
    u8          cea_UniqueCmdId;
    u8          cea_LoginKey;
    u8          cea_Property;
    u8          cea_Reserved0 [3];
    u16         cea_TransferLength;
    u16         cea_TransferOffset;
    u8          cea_Reserved1;
    Control_t   cea_Control;

} PACKED micCtrlExtApiGetSetCmd_t;

/*
** API: OEM Model Signature
*/
typedef struct micApiOemModelSig
{
    u16     oms_ModelSig;
    u8      oms_Reserved [6];

} PACKED micApiOemModelSig_t;

/*
** API: OEM Serial No
*/
typedef struct micApiOemSn
{
    u8      os_SerialNo [8];
    u8      os_Reserved [8];

} PACKED micApiOemSn_t;

/*
** API: Controller WWN
*/
typedef struct micApiCtrlWWN
{
    u8      api_CtrlWWN [8];

} PACKED micApiCtrlWWN_t;

/*
** API: Backplane/controller VPD
*/
typedef struct micApiVPD
{
    u8   api_VPD [256];

} PACKED micApiVPD_t;

#endif

/* PMIC_ARRAY_CREATE_CONFIGURATION  */
/* PMIC_ARRAY_DELETE_CONFIGURATION  */
/* PMIC_ARRAY_GET_CONFIGURATION     */
/* PMIC_LOGICAL_DRIVE_ADD          */
/* PMIC_LOGICAL_DRIVE_DELETE       */

#define MAX_LD_NAME_BYTES   32
#define MAX_ARRAY_NAME_BYTES     32

typedef struct micArrayCreateConfigCmd
{
    u8          cac_ScsiOpCode;
    u8          cac_MicSignature;
    u16         cac_MicOpCode;
    u8          cac_ConfigLock;
    u8          cac_LoginKey;
    u32         cac_Reserved0;
    u16         cac_TransferLength;
    u16         cac_TransferOffset;
    u8          cac_Reserved1;
    Control_t   cac_Control;
} PACKED micArrayCreateConfigCmd_t;
//} micArrayCreateConfigCmd_t;

typedef struct micArrayGetConfigCmd
{
    u8          gac_ScsiOpCode;
    u8          gac_MicSignature;
    u16         gac_MicOpCode;
    u8          gac_UniqueCmdId;
    u8          gac_LoginKey;
    u16         gac_StartArrayID;
    u16         gac_Reserved0;
    u16         gac_TransferLength;
    u16         gac_TransferOffset;
    u8          gac_ArrayCount;
    Control_t   gac_Control;
} PACKED micArrayGetConfigCmd_t;
//} micArrayGetConfigCmd_t;

typedef struct micArrayDeleteConfigCmd
{
    u8          dac_ScsiOpCode;
    u8          dac_MicSignature;
    u16         dac_MicOpCode;
    u8          dac_ConfigLock;
    u8          dac_LoginKey;
    u16         dac_StartArrayID;
    u16         dac_Reserved0;
    u16         dac_TransferLength;
    u16         dac_Reserved1;
    u8          dac_ArrayCount;
    Control_t   dac_Control;
} PACKED micArrayDeleteConfigCmd_t;
//} micArrayDeleteConfigCmd_t;

/* Possible ASCQ values for Disk Array related Commands */
#define MICS_ARRAY_CREATE_ARRAY_FULL        MICS_GENERAL_ERROR_RESERVED_END + 1
#define MICS_ARRAY_CREATE_LD_FULL           MICS_GENERAL_ERROR_RESERVED_END + 2
#define MICS_ARRAY_CREATE_ASSOC_ARRAY_FULL  MICS_GENERAL_ERROR_RESERVED_END + 3
#define MICS_ARRAY_UPDATE_FAILED            MICS_GENERAL_ERROR_RESERVED_END + 4
#define MICS_ARRAY_ATTRIBUTES_INVALID       MICS_GENERAL_ERROR_RESERVED_END + 5
#define MICS_ARRAY_SPARE_ACTION_INVALID     MICS_GENERAL_ERROR_RESERVED_END + 6
#define MICS_ARRAY_ASSOC_ARRAY_ID_INVALID   MICS_GENERAL_ERROR_RESERVED_END + 7

#define MICS_NO_MISSING_DRIVES_FOUND        MICS_GENERAL_ERROR_RESERVED_END + 8

#define MICS_ARRAY_INCOMPLETE               MICS_GENERAL_ERROR_RESERVED_END + 9
#define MICS_INVALID_ARRAY_PD_COUNT         MICS_GENERAL_ERROR_RESERVED_END + 10
#define MICS_INVALID_ARRAY_FLAGS            MICS_GENERAL_ERROR_RESERVED_END + 11
#define MICS_INVALID_PD_SIZE                MICS_GENERAL_ERROR_RESERVED_END + 12
#define MICS_INVALID_LD_PD_COUNT            MICS_GENERAL_ERROR_RESERVED_END + 13
#define MICS_INVALID_LD_AXLE_COUNT          MICS_GENERAL_ERROR_RESERVED_END + 14
#define MICS_INVALID_LD_RAID_LEVEL          MICS_GENERAL_ERROR_RESERVED_END + 15
#define MICS_INVALID_LD_STRIPE_SIZE         MICS_GENERAL_ERROR_RESERVED_END + 16
#define MICS_INVALID_LD_FLAGS               MICS_GENERAL_ERROR_RESERVED_END + 17
#define MICS_INVALID_LD_ATTRIBS             MICS_GENERAL_ERROR_RESERVED_END + 18
#define MICS_INVALID_LD_AXLE_SPINDLE_COUNT  MICS_GENERAL_ERROR_RESERVED_END + 19
#define MICS_INVALID_LD_AXLE_NUM            MICS_GENERAL_ERROR_RESERVED_END + 20
#define MICS_INVALID_LD_PD_FLATID           MICS_GENERAL_ERROR_RESERVED_END + 21
#define MICS_INVALID_LD_PD_COMPSIZE         MICS_GENERAL_ERROR_RESERVED_END + 22
#define MICS_INVALID_LD_PD_STARTBLOCK       MICS_GENERAL_ERROR_RESERVED_END + 23
#define MICS_INVALID_DSPARE_FOR_ARRAY       MICS_GENERAL_ERROR_RESERVED_END + 24
#define MICS_INVALID_LD_SIZE                MICS_GENERAL_ERROR_RESERVED_END + 25
#define MICS_MIGRATION_FAILED_TO_START      MICS_GENERAL_ERROR_RESERVED_END + 26
#define MICS_INVALID_SECTOR_SIZE            MICS_GENERAL_ERROR_RESERVED_END + 27
#define MICS_INVALID_PD_CONFIG_CHANGE       MICS_GENERAL_ERROR_RESERVED_END + 28
#define MICS_ADDING_STALE_PD_TO_ARRAY       MICS_GENERAL_ERROR_RESERVED_END + 29
#define MICS_PD_SETTINGS_INVALID_SETTING    MICS_GENERAL_ERROR_RESERVED_END + 30
#define MICS_PD_SETTINGS_INVALID_DRVTYPE    MICS_GENERAL_ERROR_RESERVED_END + 31
#define MICS_PD_SETTINGS_IN_PROGRESS        MICS_GENERAL_ERROR_RESERVED_END + 32
#define MICS_LD_USES_DEAD_PD                MICS_GENERAL_ERROR_RESERVED_END + 33
#define MICS_MIG_WM_IN_NVRAM                MICS_GENERAL_ERROR_RESERVED_END + 34
#define MICS_ARRAY_PDM_RUNNING              MICS_GENERAL_ERROR_RESERVED_END + 35
#define MICS_ARRAY_TRANSPORT_READY          MICS_GENERAL_ERROR_RESERVED_END + 36
#define MICS_ARRAY_CRITICAL                 MICS_GENERAL_ERROR_RESERVED_END + 37
#define MICS_ARRAY_TRANSITION_RUNNING       MICS_GENERAL_ERROR_RESERVED_END + 38
#define MICS_DRIVES_REMOVED_FROM_ARRAY      MICS_GENERAL_ERROR_RESERVED_END + 39
#define MICS_ARRAY_NOT_TRANSPORT_READY      MICS_GENERAL_ERROR_RESERVED_END + 40
#define MICS_ARRAY_NO_DEAD_DRIVES_PRESENT   MICS_GENERAL_ERROR_RESERVED_END + 41
#define MICS_NAS_LD_IN_ARRAY                MICS_GENERAL_ERROR_RESERVED_END + 42

typedef struct micLogicalDriveAddCmd
{
    u8          ald_ScsiOpCode;
    u8          ald_MicSignature;
    u16         ald_MicOpCode;
    u8          ald_ConfigLock;
    u8          ald_LoginKey;
    u16         ald_LDCount;
    u16         ald_ArrayID;
    u16         ald_TransferLength;
    u16         ald_TransferOffset;
    u8          ald_Reserved0;
    Control_t   ald_Control;
} PACKED micLogicalDriveAddCmd_t;
//} micLogicalDriveAddCmd_t;

typedef struct micLogicalDriveDeleteCmd
{
    u8          dld_ScsiOpCode;
    u8          dld_MicSignature;
    u16         dld_MicOpCode;
    u8          dld_ConfigLock;
    u8          dld_LoginKey;
    u16         dld_StartLDID;
    u16         dld_ArrayID;
    u16         dld_TransferLength;
    u16         dld_LDCount;
    u8          dld_Reserved1;
    Control_t   dld_Control;
} PACKED micLogicalDriveDeleteCmd_t;
//} micLogicalDriveDeleteCmd_t;

typedef struct micArrayConfigurationDef
{
    IN OUT u8  acd_ArrayName[MAX_ARRAY_NAME_BYTES];
    IN OUT u16 acd_ArrayID;
    IN OUT u16 acd_NoOfLogicalDrives;
    IN OUT u16 acd_NoOfPhysicalDrives;
    IN OUT u16 acd_Reserved1;
    IN OUT u8  acd_ArrayAttributes;      /* Defines if MP is enabled etc */
           u8  acd_Reserved2[3];
    IN OUT u32 acd_ArrayFlags;           /* Defines the type of the Array, like
                                           Global spare, dedicated spare etc., */
    IN OUT u32 acd_NoOfArraysAssociated; /* For a Spare Array, lists the Array
                                           WWNs of the Data Array to which this
                                           spare drive is assigned to. For Data
                                           Array, lists the Spare Array WWNs
                                           which are assigned to the Data Array
                                         */

    OUT u8 acd_UserSetPowerMode;         //user set level, application should ignore this.
    OUT u8 acd_CurrentPowerMode;         // current  level
    OUT u8 acd_PowerManagementIgnored;   //power management would be disabled if this field is set to PRO_TRUE

    u8 acd_Reserved3[61];
    IN OUT u32 acd_AssociatedArrayInformationBegin[1];

} PACKED micArrayConfigurationDef_t;


typedef struct micComponentDeviceDef
{
    IN OUT u16 cdd_SequenceNo;
           u16 cdd_Reserved1;
    IN OUT u64 cdd_StartBlock;
    IN OUT u64 cdd_ComponentSizeinBlocks;
    IN OUT u16 cdd_DeviceFlatId;
           u16 cdd_Reserved2;
    IN OUT u32 cdd_PDUniqueID;
    IN OUT u32 cdd_PDFlags;
    u32 cdd_Reserved3[4];

} PACKED micComponentDeviceDef_t;

#define LD_MAX_AXLES                16

/* It must be noted that for a Hybrid RAID 50 and 51, the Max PDs per
 * Axle would be only 16.
 * For all other RAID Levels, wherever applicable, the Max PDs per Axle would be
 * 256
 */

typedef struct micLDAxleDefinition
{
    IN OUT u16 lad_AxleNum;
    IN OUT u16 lad_NumPDInAxle;
#ifdef CX20Y_NAS
    // Set LDEVFLAG_DEVICE_NAS_USED in ldi_Flags to indicate that the LD is used for NAS (or otherwise for ISCSI).
#endif
    IN OUT u32 lad_AxleFlags;
    IN OUT u32 lad_Reserved1[4];
    IN OUT micComponentDeviceDef_t lad_AxlePDDefinition[1];

} PACKED micLDAxleDefinition_t;

typedef struct micLogicalDriveDef
{
    IN OUT u16      ldd_ArrayID;
           u16      ldd_Reserved1;
    IN OUT u16      ldd_LDFlatID;
           u16      ldd_Reserved2;
    OUT    u32      ldd_LDUniqueID;
    IN OUT u8       ldd_RaidLevel;
           u8       ldd_SectorSizeCode;
       u8       ldd_RaidAlgoSelect;
#define RAID_ALGO_LEFT_SYMMETRIC          0x1
#define RAID_ALGO_RIGHT_SYMMETRIC         0x2
#define RAID_ALGO_LEFT_ASYMMETRIC         0x3
#define RAID_ALGO_RIGHT_ASYMMETRIC        0x4
#ifdef __RAID3__
#define RAID_ALGO_NONROTATING_PARITY0       0x5
#define RAID_ALGO_NONROTATING_PARITYN       0x6
#endif

           u8       ldd_ParityPace;  // for RAID6

    IN OUT u8       ldd_LDName[MAX_LD_NAME_BYTES];
    IN OUT u32      ldd_StripeSizeInBlocks;
    IN OUT u64      ldd_LDSizeInBlocks;
#ifdef CX20Y_NAS
    // Set LDEVFLAG_DEVICE_NAS_USED in ldd_LDFlags to indicate that the LD is used for NAS (or otherwise for ISCSI).
#endif
    IN OUT u32      ldd_LDFlags;
    IN OUT u32      ldd_LDAttributes;
    IN OUT u16      ldd_LDNoOfAxles;
           u8       ldd_NumofParityDrives;
           u8       ldd_CodecScheme;

#define RAID6_CODEC_PQ      0x1
#define RAID6_CODEC_RS      0x2
#define RAID6_CODEC_VANDMON 0x3

    IN OUT u16      ldd_NoOfUsedPD;
           u16      ldd_PreferredOwnerControllerId;
           u8       ldd_Wwn[8];
           u32      ldd_Reserved7[13];
    IN OUT micLDAxleDefinition_t LDAxleDefinition[1];
} PACKED micLogicalDriveDef_t;

#define   MAX_MODEL_NO       40
#define   MAX_SERIAL_NO      24
#define   MAX_FIRMWARE_REV   8

typedef struct micPhysicalDeviceDef
{
    u16 pdd_PDFlatId;
    u16 pdd_DriveType;
    u8 pdd_MediaType;
    u8 pdd_Reserved1[3];
    u32 pdd_Reserved2;

    u32 pdd_PDUniqueID;
    u32 pdd_SequenceNo;
    u16 pdd_ArrayID;
    u16 pdd_Reserved4;
    u32 pdd_PDFlags;
    u64 pdd_PDSize;
    u64 pdd_PDConfigurableSize;

    u8 pdd_SerialNumber[MAX_SERIAL_NO]; // MAX_SERIAL_NO = 24
    u32 pdd_Reserved[2];
} PACKED micPhysicalDeviceDef_t;

/*
 * Data structure for  PMIC_CREATE_ARRAY_CONFIGURATION  &
 * PMIC_DELETE_ARRAY_CONFIGURATION  will be as follows
 *
 *      -------------------
 *      | micUPCD_t (1)   |
 *      -------------------
 *      | micUPD_t (1..n) |
 *      -------------------
 *      | micUVD_t (0..n) |
 *      -------------------
 */

/* PMIC_ARRAY_GET_INFORMATION */

typedef struct micArrayGetInfoCmd
{
    u8          agi_ScsiOpCode;
    u8          agi_MicSignature;
    u16         agi_MicOpCode;
    u8          agi_UniqueCmdId;
    u8          agi_LoginKey;
    u16         agi_ArrayId;
    u16         agi_Reserved;
    u16         agi_TransferLength;
    u16         agi_TransferOffset;
    u8          agi_ArrayCount;
    Control_t   agi_Control;
} PACKED micArrayGetInfoCmd_t;
//} micArrayGetInfoCmd_t;

/* This is an 8-byte aligned structure : size 184
   if you are planning to edit this, please ensure
   8-byte alignment for In-band tools to work */

    typedef struct micArrayInfo
{
    u16     ai_ArrayId;
    u16     ai_Reserved1;
    u8      ai_ArrayName[32];
    u8      ai_WWN[8];
    u16     ai_NoOfPD;
    u16     ai_NoOfLD;
    u32     ai_Flags;
    u32     ai_Attribs;
    u16     ai_NoOfAssociatedArrays;
    u16     ai_NoOfPassiveProcesses;
    u16     ai_NoOfLdi;
    u16     ai_NoOfBkSync;
    u16     ai_NoOfSyncCheck;
    u16     ai_NoOfRebuild;
    u16     ai_NoOfOCE;
    u16     ai_NoOfRLM;
    u16     ai_NoOfMP;
    u16     ai_Reserved2;
    u16     ai_Reserved3[7];
    u16     ai_NoOfOfflinePD;
    u16     ai_NoOfOfflineLD;
    u16     ai_NoOfCriticalLD;
    u64     ai_Reserved4; /* Used for Array Write/Read Counts. Support will be
    decided
                           after discussions */
    u64     ai_Reserved5; /* Write Count */
    u64     ai_Reserved6; /* Error Count */

    u8      ai_UserSetPowerMode;
    u8      ai_CurrenPowerMode;
    u16     ai_ArrayIdleTime;
    u16     ai_ArrayStandbyTime;
    u16     ai_ArrayStoppedTime;
    u8      ai_PowerManagementIgnored;
    u8      ai_Reserved7[3];
    u32     ai_Reserved[13];
} PACKED micArrayInfo_t;

/* PMIC_ARRAY_GET_SETTINGS */
/* PMIC_ARRAY_SET_SETTINGS */

typedef struct micArrayGetSetSettingsCmd
{
    u8          pogss_ScsiOpCode;
    u8          pogss_MicSignature;
    u16         pogss_MicOpCode;
    u8          pogss_UniqueCmdId;
    u8          pogss_LoginKey;
    u16         pogss_ArrayId;
    u16         pogss_Reserved;
    u16         pogss_TransferLength;
    u16         pogss_TransferOffset;
    u8          pogss_ArrayCount;
    Control_t   pogss_Control;
} PACKED micArrayGetSetSettingsCmd_t;
//} micArrayGetSetSettingsCmd_t;

/*
 * For PMIC_ARRAY_SET_SETTINGS pogsp_ConfigLock is used
 * instead of pogsp_LoginKey
 */
#define pogsp_ConfigLock  pogsp_LoginKey
/* This is an 8-byte aligned structure : size 56
   if you are planning to edit this, please ensure 8-byte alignment for In-band
   tools to work */

typedef struct micArraySettings
{
    u16     as_ArrayId;
    u16     as_Reserved0;
    u32     as_Flags;
    u32     as_Attribs;
    u8      as_ArrayName[32];
    u16     as_SpareAction;

#define SPARE_ACTION_NONE               0x0
#define SPARE_ACTION_ASSOC_SPARE        0x1
#define SPARE_ACTION_DISASSOC_SPARE     0x2

    u16     as_NumberOfAssocArraysInList;
    u8      as_ArrayPowerLevels;
    u8      as_IgnorePowerManagement; /* default PRO_FALSE */
    u16     as_ArrayIdleTime;
    u16     as_ArrayStandbyTime;
    u16     as_ArrayStoppedTime;

    u32     as_Reserved1[13];
    u16     as_AssocArrayList[2];
} PACKED micArraySettings_t;




typedef struct micProcessIncompleteArray
{
    u8          pia_ScsiOpCode;
    u8          pia_MicSignature;
    u16         pia_MicOpCode;
    u8          pia_UniqueCmdId;
    u8          pia_LoginKey;
    u16         pia_ArrayId;
    u8          pia_ActionType;

#define MIC_ACCEPT_INCOMPLETE_ARRAY                 0x01
#define MIC_PROCESS_MDD_FOR_INCOMPLETE_ARRAY        0x02
#define MIC_PROCESS_MDD_FOR_CTLR                    0x03
#define MIC_ACCEPT_MISSING_NVRAM_MIG_WM             0x04

    u8          pia_Reserved1;
    u16         pia_TransferLength;
    u16         pia_TransferOffset;
    u8          pia_Reserved2;
    Control_t   pia_Control;
}PACKED micProcessIncompleteArrayCmd_t;

typedef struct micSetArrayTransportReady
{
    u8        msat_ScsiOpCode;
    u8        msat_MicSignature;
    u16       msat_MicOpCode;
    u8        msat_UniqueCmdId;
    u8        msat_LoginKey;
    u16       msat_ArrayId;
    u16       msat_Reserved;
    u16       msat_TransferLength;
    u16       msat_TransferOffset;
    u8        msat_ControllerID;
    Control_t msat_Control;
} PACKED micSetArrayTransportReady_t;

typedef struct micUnsetArrayTransportReady
{
    u8        musat_ScsiOpCode;
    u8        musat_MicSignature;
    u16       musat_MicOpCode;
    u8        musat_UniqueCmdId;
    u8        musat_LoginKey;
    u16       musat_ArrayId;
    u16       musat_Reserved;
    u16       musat_TransferLength;
    u16       musat_TransferOffset;
    u8        musat_ControllerID;
    Control_t musat_Control;
} PACKED micUnsetArrayTransportReady_t;

typedef struct micSetPDsOnlineForArray
{
    u8        mspoa_ScsiOpCode;
    u8        mspoa_MicSignature;
    u16       mspoa_MicOpCode;
    u8        mspoa_UniqueCmdId;
    u8        mspoa_LoginKey;
    u16       mspoa_ArrayId;
    u16       mspoa_Reserved;
    u16       mspoa_TransferLength;
    u16       mspoa_TransferOffset;
    u8        mspoa_ControllerID;
    Control_t mspoa_Control;
} PACKED micSetPDsOnlineForArray_t;

/*
 * PMIC_PHYSICAL_DRIVE_GET_INFORMATION
 *   micPDInfoPage0 - Raid Specific
 *   micPDInfoPage1 - SATA Specific
 */

typedef struct micPDGetInfoCmd
{
    u8        pgi_ScsiOpCode;
    u8        pgi_MicSignature;
    u16       pgi_MicOpCode;
    u8        pgi_UniqueCmdId;
    u8        pgi_LoginKey;
    u16       pgi_PDFlatId;
    u8        pgi_CodePage;
    u8        pgi_Reserved;
    u16       pgi_TransferLength;
    u16       pgi_TransferOffset;
    u8        pgi_PDCount;
    Control_t pgi_Control;
} PACKED micPDGetInfoCmd_t;
//} micPDGetInfoCmd_t;

#define PD_PAGE_RAID 0
#define PD_PAGE_SATA 1
#define PD_PAGE_HBA  2
#define PD_PAGE_SAS  3    // SAS page of physical drive information  // allen SAS
#define PD_PAGE_ALL  0xFF

#if 0 /* following were moved above the definition of micPhysicalDeviceDef_t */
#define MAX_MODEL_NO     40
#define MAX_SERIAL_NO    24
#define MAX_FIRMWARE_REV 8
#endif

#define MIC_SCSI_DIRECT_ACCESS              0x00
#define MIC_SCSI_SEQUENTIAL_ACCESS          0x01
#define MIC_SCSI_PRINTER                    0x02
#define MIC_SCSI_PROCESSOR                  0x03
#define MIC_SCSI_WRITE_ONCE                 0x04
#define MIC_SCSI_CD_DVD                     0x05
#define MIC_SCSI_SCANNER                    0x06
#define MIC_SCSI_OPTICAL_MEMORY             0x07
#define MIC_SCSI_MEDIUM_CHANGER             0x08
#define MIC_SCSI_COMMUNICATION              0x09
#define MIC_SCSI_OBSOLETE_0x0A              0x0A
#define MIC_SCSI_OBSOLETE_0x0B              0x0B
#define MIC_SCSI_STORAGE_ARRAY_CONTROLLER   0x0C
#define MIC_SCSI_SES                        0x0D
#define MIC_SCSI_SIMPLIFIED_DIRECT_ACCESS   0x0E
#define MIC_SCSI_OPTICAL_CARD_READER_WRITER 0x0F
#define MIC_SCSI_BRIDGE_CONTROLLER_COMMANDS 0x10
#define MIC_SCSI_OBJECT_BASED_STORAGE       0x11
#define MIC_SCSI_AUTOMATION_DRIVE_INTERFACE 0x12
#define MIC_SCSI_SECURITY_MANAGER           0x13
#define MIC_SCSI_WELL_KNOWN_LOGICAL_UNIT    0x1E
#define MIC_SCSI_UNKNOWN                    0x1F

/* Possible value for pdi_MediaType */
#define MT_MAGNETIC 0
#define MT_OPTICAL  1
#define MT_MEMORY   2

/* Possible values for pdi_PowerSavingMode */
#define PD_IN_NORMAL_MODE       0  /* HDD in full power mode   */
#define PD_IN_PARK_HEAD_MODE    1  /* HDD in park head mode    */
#define PD_IN_LOW_ROTATION_MODE 2  /* HDD in low rotation mode */
#define PD_IN_SPIN_DOWN_MODE    3  /* HDD in spin down mode    */

typedef struct micPDInfoPage0
{
    u16 pdi_PageCode;
    u16 pdi_PageLength;
    u16 pdi_FlatId;
    u16 pdi_ArrayId;
    u32 pdi_UniqueId;
    u8  pdi_Reserved0;
    u8  pdi_Controller;
    u16 pdi_Channel;
    u16 pdi_Target;
    u16 pdi_Lun;
    u16 pdi_EnclosureId;
    u16 pdi_SlotId;
    u16 pdi_SequenceNo;
    u16 pdi_MddSequenceNo;
    u8  pdi_Reserved5[4];
    u64 pdi_PhysicalSize;
    u64 pdi_LastUnconfiguredFragement;
    u64 pdi_ConfigurableSize;
    u64 pdi_UsedSize;
    u64 pdi_StartBlock;
    u16 pdi_BlockSize;
    u16 pdi_BlockSizeHigh;
    u32 pdi_Cylinders;      /* not implented yet. currently values are zeros*/
    u16 pdi_Heads;          /* not implented yet. currently values are zeros*/
    u16 pdi_Sectors;        /* not implented yet. currently values are zeros*/
    u32 pdi_Flags;
    u8  pdi_PDSpinStatus;   /* PD Spin status */
    u8  pdi_DriveSpeed;     /* interpret this based on drive type, for sata GB, for SCSI 160 or 320 etc*/
    u8  pdi_ScsiPeripheralDeviceType;
    u8  pdi_Reserved2[10];
    u8  pdi_MediaType;          /* Magnetic, Optical, Memory etc */
    u16 pdi_DriveType;          /* SATA, SCSI etc */
    u8  pdi_DriveModelNo[MAX_MODEL_NO];
    u8  pdi_DriveSerialNo[MAX_SERIAL_NO];
    u8  pdi_DriveFirmwareVer[MAX_FIRMWARE_REV];
    u16 pdi_ProtocolMajorVer;   /* 0xffff does not report */
    u16 pdi_ProtocolMinorVer;   /* 0xffff does not report */
    u8  pdi_PdVisibleToControllerID; /* if 0xFF all controllers can see the PD, otherwise the controller id */
    u8  pdi_DriveTemperature;   /* in degree Celsius 0x FF means NA */
    u8  pdi_ReferenceDriveTemperature; /*in degree Celsius 0x FF means NA*/
    u8  pdi_PowerSavingMode;    /* PD in which power saving level */
    u8  pdi_Reserved3[7];
    u8  pdi_IsDirectAttached;
    u64 pdi_ReadCount;
    u64 pdi_WriteCount;
    u64 pdi_ErrorCount;
    u8  pdi_DriveAlias[32];
    u32 pdi_PhysicalSectorSize;
    u16 pdi_LowestAlignedLBA;
    u8  pdi_Reserved4[10];
} PACKED micPDInfoPage0_t;

typedef struct micPDInfoPage1
{
    u16     pdi1_PageCode;
    u16     pdi1_PageLength;
    u16     pdi1_FlatId;
    u8      pdi1_MaxSecotsSupportedForRWMultiple;
    u8      pdi1_CurrentSectorsForRWMultiple; // 8 byte

    u8      pdi1_MultiwordDMaSupport;
    u8      pdi1_MultipleDmaMode; /* if this is 0, multi mode dma is not selected */
    u8      pdi1_PioModeSupport;
    u8      pdi1_NOPcommandSupport;  //12 bytes

    u8      pdi1_NOPCmdEnable;
    u8      pdi1_ReadBufferSupport;
    u8      pdi1_ReadBufferCmdEnable;
    u8      pdi1_WriteBufferSupport; //16 bytes

    u8      pdi1_WriteBufferCmdEnable;
    u8      pdi1_HPASupport;
    u8      pdi1_HPAFeatureSetEnable;           /* host protected area*/
    u8      pdi1_DeviceResetSupport; //20

    u8      pdi1_DeviceResetCmdEnable;
    u8      pdi1_ServiceInterruptSupport;
    u8      pdi1_ServiceInterruptStateEnabled;
    u8      pdi1_ReleaseInterruptSupport; //24

    u8      pdi1_ReleaseInterruptEnabled;
    u8      pdi1_RLASupport;
    u8      pdi1_RLASupportEnable;              /* read look ahead*/
    u8      pdi1_WriteCacheSupport; //28

    u8      pdi1_WriteCachedEnable;
    u8      pdi1_MandatoryPMSupport;
    u8      pdi1_PMFeatureSetEnabled;
    u8      pdi1_RMFeatureSetSupport; //32

    u8      pdi1_RMFeatureSetEnable;            /* removable media*/
    u8      pdi1_SecurityModeSupport;
    u8      pdi1_SecurityModeFeatureSetEnable;
    u8      pdi1_SMARTFeatureSetSupport; //36

    u8      pdi1_FieldReservedForSMARTFeatureSetEnable;
    u8      pdi1_SMARTSelfTestSupport;
    u8      pdi1_SMARTErrorLoggingSupport;
    u8      pdi1_AAFeatureSetSupport; //40

    u8      pdi1_AAFeatureSetEnable;            /* automatic acoustic*/
    u8      pdi1_SMSecurityExtCmdSupport;
    u8      pdi1_SMSecurityExtCmdSetEnable;     /* set max */
    u8      pdi1_PUISByFeatureSetSupport;  //44

    u8      pdi1_PUISByFeatureSetEnable;        /* power up in stand by */
    u8      pdi1_RMSNFeatureSetSupport;
    u8      pdi1_RMNFeatureSetEnable;           /* removable media notification */
    u8      pdi1_APMFeatureSetSupport; //48

    u8      pdi1_APMFeatureSetEnable;           /* advanced power management */
    u8      pdi1_CFAFeatureSetSupport;
    u8      pdi1_CFAFeatureSetEnable;
    u8      pdi1_MCPTCmdSupport; //52

    u8      pdi1_MCPTCmdSetEnable;              /* media card pass through */
    u8      pdi1_UltraDmaModeSupport;
    u8      pdi1_UltraDmaMode;                  /* if this is 0, ultra dma mode is not selcted */
    u8      pdi1_RWDmaQueuedCmdSupport; //56

    u8      pdi1_QueueDepth;
    u8      pdi1_EnableCmdQueuing;               /* current state of queuing on drives enabled/disbaled*/
    u8      pdi1_FlushCacheExtSupport;
    u8      pdi1_MandatoryFlashCacheSupport; //60

    u8      pdi1_DCOFeatureSetSupport;          /* device configuration overlay*/
    u8      pdi1_Bit48FeatureSetSupport;
    u8      pdi1_SFNeededToSpinUpafterPOS;      /* set features command*/
    u8      pdi1_DownLoadMicrocodeCmdSupport; //64

    u8      pdi1_GPLoggingFeatureSetSupport;    /* general purpose*/
    u8      pdi1_StreamingFeatureSetSupport;
    u8      pdi1_MSNValid;                    /* media serial number*/
    u8      pdi1_Reserved; //68

    u8      pdi1_Reserved1[60]; /* to align on 128 bytes boundary */
} PACKED micPDInfoPage1_t;

/* micPDInfoPage2 is specific to HBA products */
typedef struct micPDInfoPage2
{
    u16     pdi2_PageCode;
    u16     pdi2_PageLength;
    u16     pdi2_FlatId;
    u16     pdi2_ArrayId;
    u8      pdi2_Controller;
    u8      pdi2_SecurityModeSupport;
    u16     pdi2_Channel;
    u16     pdi2_Target;
    u16     pdi2_EnclosureId;
    u16     pdi2_SlotId;
    u16     pdi2_SequenceNo;
    u8      pdi2_WriteCacheSupport;
    u8      pdi2_WriteCachedEnable;
    u8      pdi2_SMARTFeatureSetSupport;
    u8      pdi2_SMARTFeatureSetEnable;
    u64     pdi2_PhysicalSize;
    u64     pdi2_UsedSize;
    u64     pdi2_StartBlock;
    u16     pdi2_BlockSize;
    u16     pdi2_DriveType; /* SATA, SCSI etc */
    u32     pdi2_Cylinders;
    u16     pdi2_Heads;
    u16     pdi2_Sectors;
    u32     pdi2_Flags;
    u8      pdi2_DriveModelNo[MAX_MODEL_NO];
    u8      pdi2_DriveSerialNo[MAX_SERIAL_NO];
    u8      pdi2_DriveFirmwareVer[MAX_FIRMWARE_REV];
    u64     pdi2_ReadCount;
    u64     pdi2_WriteCount;
    u64     pdi2_ErrorCount;
    u8      pdi2_MultiwordDMaSupport;
    u8      pdi2_MultipleDmaMode; /* if this is 0, multi mode dma is not selected */
    u8      pdi2_PioModeSupport;
    u8      pdi2_UltraDmaModeSupport;
    u8      pdi2_UltraDmaMode;      /* if this is 0, ultra dma mode is not selcted */
    u8      pdi2_Reserved[3];
} PACKED micPDInfoPage2_t;

typedef struct micPDInfoPage3     // size: 128 bytes
{
    u16     pdi3_PageCode;                      // page code: PD_PAGE_SAS
    u16     pdi3_PageLength;                    // page length
    u16     pdi3_FlatId;                        // flat id of the drive (Physical Drive ID)
    u16     pdi3_Reserved1;                     // reserved for 2 bytes

    u64     pdi3_WWN;                           // world wide name
    u64     pdi3_SasAddress1;                   // SAS address of the drive of 1st Path
    u64     pdi3_SasAddress2;                   // SAS address of the drive of 2nd Path

    u8      pdi3_NumOfPorts;                    // number of SAS ports
    u8      pdi3_PhySpeedNegotiated1;           // speed negotiated for port 1
    u8      pdi3_MaxPhySpeedProgrammed1;        // max programmed speed for port 1
    u8      pdi3_MinPhySpeedProgrammed1;        // min programmed speed for port 1

    u8      pdi3_MaxHwPhySpeed1;                // max hardware speed for port 1
    u8      pdi3_MinHwPhySpeed1;                // min hardware speed for port 1
    u8      pdi3_PhySpeedNegotiated2;           // speed negotiated for port 2
    u8      pdi3_MaxPhySpeedProgrammed2;        // max programmed speed for port 2

    u8      pdi3_MinPhySpeedProgrammed2;        // min programmed speed for port 2
    u8      pdi3_MaxHwPhySpeed2;                // max hardware speed for port 2
    u8      pdi3_MinHwPhySpeed2;                // min hardware speed for port 2
    u8      pdi3_MultiPath;                     // multi-path

    u16     pdi3_BusInactiveLimit;              // timeout of bus inactive limit
    u16     pdi3_ConnectTimeLimit;              // connect time limit
    u16     pdi3_MaxBurstSize;                  // max burst size
    u16     pdi3_FirstBurstSize;                // first brust size

    u8      pdi3_Reserved2;                     // reserved for 1 byte
    u8      pdi3_ReadCacheEnable;               // read cache
    u8      pdi3_WriteCacheEnable;              // write cache
    u8      pdi3_ReadLookAheadCacheEnable;      // RLA cache

    u8      pdi3_ReadCacheSupport;              // read cache support
    u8      pdi3_WriteCacheSupport;             // write cache support
    u8      pdi3_RwRetentionPriority;           // read/write retention priority
    u8      pdi3_ReadLookAheadCacheSupport;     // read  cache support

    u16     pdi3_DisablePrefetchTransferLength; // disable prefetch transfer length
    u16     pdi3_MinPrefetch;                   // minimum prefetch
    u16     pdi3_MaxPrefetch;                   // maximum prefetch
    u16     pdi3_MaxPrefetchCeiling;            // maxmum prefetch ceiling

    u16     pdi3_CacheSegmentSize;              // cache segment size
    u8      pdi3_NumberofCacheSegment;          // number of cache segment
    u8      pdi3_Reserved3;                     // reserved for 1 byte

    u8      pdi3_NonCacheSegmentSize [3];       // non-cache segment size
    u8      pdi3_CmdQueuingSupport;             // drive supports command queuing
    u8      pdi3_CmdQueuingEnable;              // currently enabled or disabled
    u8      pdi3_Reserved4 [51];                // reserved for 51 bytes
} PACKED micPDInfoPage3_t;

typedef struct micGetMissingPDInfoCmd
{
    u8          gmpi_ScsiOpCode;
    u8          gmpi_MicSignature;
    u16         gmpi_MicOpCode;
    u8          gmpi_UniqueCmdId;
    u8          gmpi_LoginKey;
    u32         gmpi_Reserved1;
    u16         gmpi_TransferLength;
    u16         gmpi_TransferOffset;
    u8          gmpi_Count;
    Control_t   gmpi_Control;
} PACKED micGetMissingPDInfoCmd_t;

typedef struct micMissingPDInfo
{
    u16 mpi_NoOFMissingDrivesDetected;
    u16 mpi_NoOfMissingDrivesReturned;
    u32 mpi_Reserved1;

    micPDInfoPage0_t PDInfo[1];

} PACKED micMissingPDInfo_t;

/*
 * PMIC_PHYSICAL_DRIVE_GET_SETTINGS
 * PMIC_PHYSICAL_DRIVE_SET_SETTINGS
 *   micPDSETTINGPage0 - Raid Specific
 *   micPDSETTINGPage1 - SATA Specific
 */

typedef struct micPDGetSetSettingsCmd
{
    u8          pgss_ScsiOpCode;
    u8          pgss_MicSignature;
    u16         pgss_MicOpCode;
    u8          pgss_UniqueCmdId;
    u8          pgss_LoginKey;
    u16         pgss_FlatId;
    u8          pgss_PageCode;
    u8          pgss_Reserved;
    u16         pgss_TransferLength;
    u16         pgss_TransferOffset;
    u8          pgss_PDCount;
    Control_t   pgss_Control;
} PACKED micPDGetSetSettingsCmd_t;
//} micPDGetSetSettingsCmd_t;

/*
 * For PMIC_PHYSICAL_DRIVE_SET_SETTINGS pgsp_ConfigLock is used
 * instead of pgsp_LoginKey
 */
#define pgss_ConfigLock  pgss_LoginKey

typedef struct micPDSettingsPage0Internal
{
    u16     pdsp_FlatId;
    u16     pdsp_Reserved;
    u8      pdsp_Reserved1[4];
    u32     pdsp_Blocksize;
    u32     pdsp_Flags;
    u8      pdsp_PDAlias[32];
    u8      pdsp_Reserved2[32]; /* Pad for 8-byte Alignment and future use */

} PACKED micPDSetPage0Internal_t;


typedef struct micPDSettingsPage0
{
    u16     pds_PageCode;
    u16     pds_PageLength;
    u32     pds_Reserved1;

    micPDSetPage0Internal_t pds_PDSettings[1];

} PACKED micPDSettingsPage0_t;

typedef struct micPDSettingsPage1Internal
{
    u16     pds1_FlatId;                            /* this will be 0xFFFF to indicate this is controller based */
    u8      pds1_WriteCachedEnable;                 /* default:   enabled*/
    u8      pds1_RLASupportEnable;                  /* read look ahead default: enabled*/
    u16     pds1_NumOfSectorsPerMultipleModeCmds;   /* default *: default:16 sectors*/
    u8      pds1_TransferMode;                      /* mulitDMA and Ultra DMA default:UDMA5 */
    u8      pds1_PioMode;                           /* default: PIO_Mode 4 */
/*    u8      pds1_HPAFeatureSetEnable;             host protected area */
/*    u8      pds1_SecurityModeFeatureSetEnable; may be not now( thru set passwd cmd) */
    u8      pds1_ReservedForSMARTFeatureSetEnable;             /* default : enabled */
    u8      pds1_AAFeatureSetEnable;                /* automatic acoustic default: disabled*/
    u8      pds1_AALevel;                           /* default :n/a */
/*    u8      pds1_SMSecurityExtCmdSetEnable;        set max passwd*/
/* spin up may need to control this   u8      pds1_PUISByFeatureSetEnable;     power up in stand by */
    u8      pds1_APMFeatureSetEnable;               /* advanced power management default:disabled*/
    u8      pds1_APMLevel;                          /* default n/a*/
    u8      pds1_IsThisDeafultSettings;             /* default TRUE*/
    u8      pds1_EnableCmdQueuing;                   /* default FALSE */
    u8      pds1_SpeedNegotiated;                    /* default highest */
    u8      pds1_TemperaturePollingInterval;        /* in seconds, default:30 secs, 0= no polling*/
    u8      pds1_Reserved[12];
    u8      pds1_Signature[2];
    u8      pds1_CheckSum;
} PACKED micPDSettingsPage1Internal_t;

typedef struct micPDSettingsPage1
{
    u16     pds1_PageCode;
    u16     pds1_PageLength;
    u8      pds1_DrvType;
    u8      pds1_Reserved[3];
    micPDSettingsPage1Internal_t pds1_PDSettings[1]; // this should be a union of diffrebe drv types
} PACKED micPDSettingsPage1_t;

/* PD settings page 1 values */
#define PD_SETTINGS_ENABLE_WRITECACHE           PRO_TRUE
#define PD_SETTINGS_DISABLE_WRITECACHE          PRO_FALSE
#define PD_SETTINGS_ENABLE_RLA                  PRO_TRUE
#define PD_SETTINGS_DISABLE_RLA                 PRO_FALSE
#define PD_SETTINGS_ENABLE_READ_CACHE           PRO_TRUE
#define PD_SETTINGS_DISABLE_READ_CACHE          PRO_FALSE
#define PD_SETTINGS_ENABLE_RLA                  PRO_TRUE
#define PD_SETTINGS_DISABLE_RLA                 PRO_FALSE
#define PD_SETTINGS_PIO_MODE_DEFAULT            0x00
#define PD_SETTINGS_PIO_MODE_0                  0x08
#define PD_SETTINGS_PIO_MODE_1                  0x09
#define PD_SETTINGS_PIO_MODE_2                  0x0a
#define PD_SETTINGS_PIO_MODE_3                  0x0b
#define PD_SETTINGS_PIO_MODE_4                  0x0c
#define PD_SETTINGS_TRANSFERMODE_UMA_0          0x40
#define PD_SETTINGS_TRANSFERMODE_UMA_1          0x41
#define PD_SETTINGS_TRANSFERMODE_UMA_2          0x42
#define PD_SETTINGS_TRANSFERMODE_UMA_3          0x43
#define PD_SETTINGS_TRANSFERMODE_UMA_4          0x44
#define PD_SETTINGS_TRANSFERMODE_UMA_5          0x45
#define PD_SETTINGS_TRANSFERMODE_MULTI_DMA_0    0x20
#define PD_SETTINGS_TRANSFERMODE_MULTI_DMA_1    0x21
#define PD_SETTINGS_TRANSFERMODE_MULTI_DMA_2    0x22

#define PD_SETTINGS_AA_LEVEL_MIN_EMANATION      0x80
#define PD_SETTINGS_AA_LEVEL_MAX_PERFORMANCE    0xFE
#define PD_SETTINGS_AA_LEVEL_INTERMEDIATE_LOWER 0x81
#define PD_SETTINGS_AA_LEVEL_INTERMEDIATE_UPPER 0xFD
#define PD_SETTINGS_APM_LEVEL_MAX_PERFORMANCE   0xFE
#define PD_SETTINGS_APM_LEVEL_MAX_NO_STNDBY     0xFD
#define PD_SETTINGS_APM_LEVEL_MIN_NO_STNDBY     0x80
#define PD_SETTINGS_APM_LEVEL_MAX_WITH_STNDBY   0x7F
#define PD_SETTINGS_APM_LEVEL_MIN_WITH_STNDBY   0x01
#define PD_SETTINGS_ENABLE_RW_CMD_QUEING        PRO_TRUE
#define PD_SETTINGS_DISABLE_RW_CMD_QUEING       PRO_FALSE

#define PD_SPEED_SATA_UNKNOWN         0
#define PD_SPEED_AUTO_NEGOTIATION     0
#define PD_SPEED_SATA_1P5G            1
#define PD_SPEED_SATA_3G              2
#define PD_SPEED_SATA_6G              3

/* Allowed values for above structure/
1.pds1_NumOfSectorsPerMultipleModeCmds = this could be any value,
less than 0xFF, should be supported by drive if thi is more than
allowed value command will not be sent to drive.
2.Transfer mode = DMA_MODE | DMA_LEVEL or PIO_MODE possible vals are define below
    for ex, UDMA_MODE | UDMA_LEVEL2 etc.
3.PioMode : could be one of the 4 modes
3.RLASupportEnabe =1 to enable 0 to disable read look ahead
4.SMARTFeatureSet = 0 ; disable smart 1 enable smart
5.AAFeature SetEnable = 1, then specify AA_level. If 0 ignore AA_level
6.Same as AA, for APM too
7.WriteCacheEnable = 0; disable, 1 enable
*/

/* micPDSettingsPage2 is specific to HBA products */
typedef struct micPDSettingsPage2
{
    u16     pds2_PageCode;
    u16     pds2_PageLength;
    u16     pds2_FlatId;
    u16     pds2_ArrayId;
    u8      pds2_WriteCachedEnable;
    u8      pds2_SMARTFeatureSetEnable;
    u8      pds2_Reserved[6];
} PACKED micPDSettingsPage2_t;

typedef struct micPDSettingsPage3Internal    // size: 64 bytes
{
    u16    pds3_FlatId;            // this will be 0xFFFF to indicate this is controller based
    u16    pds3_Reserved1;         // reserved for 2 bytes
    u8     pds3_WriteCachedEnable; // default: enabled
    u8     pds3_ReadCacheEnable;   // read cache default: enabled default=TRUE
    u8     pds3_RLAEnable;         // READ ahead default=TRUE
    u8     pds3_Reserved2;         // reserved for 2 bytes

    u16    pds3_BusInactiveLimit;  // in 100 micro seconds scale, 0 = no limit defaullt = 0
    u16    pds3_ConnectTimeLimit;  // in 100 micro seconds scale, 0 = no limit default = 0
    u16    pds3_MaxBurstSize;      // in terms of 512 bytes, 1 = 512 bytes 2= 1024 bytes etc 0=no limit default = 0
    u16    pds3_FirstBurstSize;    // in terms of 512 bytes, 1 = 512 bytes 2= 1024 bytes etc..0=no limit default =0

    u8     pds3_CmdQueuing;        // command queuing  default = TRUE
    u8     pds3_RestorePDFactoryDefaults;  // TRUE OR FALSE , if TRUE all other parameters are ignored, default = FALSE
    u8     pds3_SpeedNegotiated;           // Defualthighest possible
    u8     pds3_TemperaturePollingInterval; /* in seconds, default:30 secs, o=no polling*/
    u8     pds3_Reserved3 [40];            // reserved for 43 bytes
    u8     pds3_Reserved4;
    u8     pds3_Signature[2];      // signature
    u8     pds3_CheckSum;          // check sum

} PACKED micPDSettingsPage3Internal_t;

/* PAge 0 info for SAS define for software, Firmware does not use them*/
/* defines for scsi firmware major version*/
#define NO_STD   0x0
#define SPC      0x03
#define SPC2     0x04
#define SPC3     0x05
/* everything else is either obselete or reserved*/


typedef struct micPDSettingsPage3 // size: 8 + 64 bytes
{
    u16     pds3_PageCode;         // page code
    u16     pds3_PageLength;       // page length
    u32     pds3_Reserved1;        // reserved for 4 bytes
    micPDSettingsPage3Internal_t pds3_PDSettings[1];
} PACKED micPDSettingsPage3_t;


/* PMIC_LOGICAL_DRIVE_GET_INFORMATION */

typedef struct micLDGetInfoCmd
{
    u8          lgi_ScsiOpCode;
    u8          lgi_MicSignature;
    u16         lgi_MicOpCode;
    u8          lgi_UniqueCmdId;
    u8          lgi_LoginKey;
    u16         lgi_LDFlatId;
    u16         lgi_LDCount;
    u16         lgi_TransferLength;
    u16         lgi_TransferOffset;
    u8          lgi_Reserved;
    Control_t   lgi_Control;
} PACKED micLDGetInfoCmd_t;
//} micLDGetInfoCmd_t;

typedef struct micLogicalDriveInfo
{
    u16     ldi_FlatId;
    u8      ldi_RaidLevel;
    u8      ldi_Reserved1;
#ifdef CX20Y_NAS
    // Set LDEVFLAG_DEVICE_NAS_USED in ldi_Flags to indicate that the LD is used for NAS (or otherwise for ISCSI).
#endif
    u32     ldi_Flags;
    u32     ldi_Attributes;
    u64     ldi_Size;
    u64     ldi_RawSize;
    u64     ldi_StartBlock;
    u16     ldi_NoOfAxles;
    u16     ldi_NoOfUsedPD;
    u32     ldi_IsConfigured;
    u32     ldi_StripeSize;
    u16     ldi_ArrayId;
    u8      ldi_SectorSizeCode;
    #define LDEVFLAG_DEVICE_DEGRADE   0x04
    u8      ldi_RaidAlgoSelect;
    u8      ldi_LDName[MAX_LD_NAME_BYTES];
    u8      ldi_SerialNo[20];
    u8      ldi_WWN[8];
    u64     ldi_ReadCount;
    u64     ldi_WriteCount;
    u64     ldi_ErrorCount;

    u8      ldi_ParityPace;
    u8      ldi_NumofParityDrives;
    u8      ldi_CodecScheme;
    u8      ldi_Reserved2;

    u16     ldi_PreferredOwnerControllerId;
#ifndef LUNCOPY
    u16     ldi_Reserved4;
    u32     ldi_Reserved3[14];
#else
    u8      ldi_ALUAAccessState[4];
    u16     ldi_reserved;
    u32     ldi_AssociationState;
    u32     ldi_storagesevicesOperation;
    u8      ldi_LDAccessControl; // readonly, write only and not visible to host
#define LD_ACCESS_DEFAULT              0x00     // full access both read writebale
#define LD_ACCESS_NOTREADABLE          0x01
#define LD_ACCESS_NOTWRITEABLE         0x02
#define LD_ACCESS_NOTREADWRITEABLE     0x03
#define LD_ACCESS_NOTVISIBLETOHOST     0x04     // HOST can not see the LUN  values could go up to 0x07
    u8      ldi_Reserved3[3];
    u32     ldi_Reserved4[10];
#endif

} PACKED micLogicalDriveInfo_t;


/* PMIC_LOGICAL_DRIVE_GET_SETTINGS */
/* PMIC_LOGICAL_DRIVE_SET_SETTINGS */

typedef struct micLDGetSetSettingsCmd
{
    u8          ldgss_ScsiOpCode;
    u8          ldgss_MicSignature;
    u16         ldgss_MicOpCode;
    u8          ldgss_UniqueCmdId;
    u8          ldgss_LoginKey;
    u16         ldgss_LDFlatId;
    u16         ldgss_Reserved;
    u16         ldgss_TransferLength;
    u16         ldgss_TransferOffset;
    u8          ldgss_LDCount;
    Control_t   ldgss_Control;
} PACKED micLDGetSetSettingsCmd_t;
//} micLDGetSetSettingsCmd_t;

/*
 * For PMIC_LOGICAL_DRIVE_SET_SETTINGS ldgsp_ConfigLock is used
 * instead of ldgsp_LoginKey
 */
#define ldgss_ConfigLock  ldgss_LoginKey

typedef struct micLogicalDriveSettings
{
    u16     lds_LDFlatId;
    u16     lds_ArrayID;
    u32     lds_Attribs;
    u32     lds_Devflags;
    u32     lds_Stripesizeinblks;
    u8      lds_LDName[MAX_LD_NAME_BYTES];
    u16     lds_PreferredOwnerControllerId;
    u16     lds_reserved1;
    u32     lds_Reserved2[15];
} PACKED micLogicalDriveSettings_t;

/* Background Data structures */

#define BGT_MODULES_COMMON_ERROR_START      MICS_MODULE_SPECIFIC_ERROR_START
#define BGT_MODULE_SPECIFIC_ERROR_START     (BGT_MODULES_COMMON_ERROR_START + 0x20)

/* possible ASCQ returned by BackGround Tasks */
#define BGT_NOT_ACTIVE                      (BGT_MODULES_COMMON_ERROR_START + 0x01)
#define BGT_ALREADY_RUNNING                 (BGT_MODULES_COMMON_ERROR_START + 0x02)
#define BGT_IO_PENDING_ON_LD                (BGT_MODULES_COMMON_ERROR_START + 0x03)
#define BGT_REBUILD_OR_MIGRATION_RUNNING    (BGT_MODULES_COMMON_ERROR_START + 0x04)
#define BGT_WM_UPDATE_FAILED                (BGT_MODULES_COMMON_ERROR_START + 0x05)
#define BGT_LD_OFFLINE                      (BGT_MODULES_COMMON_ERROR_START + 0x06)
#define BGT_LDI_ACTIVE                      (BGT_MODULES_COMMON_ERROR_START + 0x07)
#define BGT_CMD_ALREADY_PENDING             (BGT_MODULES_COMMON_ERROR_START + 0x08)
#define BGT_PAUSED_RESUME_REQUIRED          (BGT_MODULES_COMMON_ERROR_START + 0x09)
#define BGT_LD_NOT_ONLINE                   (BGT_MODULES_COMMON_ERROR_START + 0x0A)
#define BGT_LAST_USER_ERROR_CODE               (BGT_MODULES_COMMON_ERROR_START + 0x0B)

//Internally used error code
#define BGT_RQST_ERROR_INVALID_CONTROLLER                   ( BGT_LAST_USER_ERROR_CODE + 0x01)
#define BGT_C2C_INVALID_INDEX                                            ( BGT_LAST_USER_ERROR_CODE + 0x02)
#define BGT_NO_CACHE_ALLOCATED                                        ( BGT_LAST_USER_ERROR_CODE + 0x03 )
#define BGT_PARTIAL_CL_ALLOCATED                                      ( BGT_LAST_USER_ERROR_CODE + 0x04 )


/* PMIC_MEDIAPATROL_START       */
/* PMIC_MEDIAPATROL_STOP        */
/* PMIC_MEDIAPATROL_PAUSE       */
/* PMIC_MEDIAPATROL_RESUME     */
/* PMIC_MEDIAPATROL_GETPROGRESS */

/* For START, STOP, PAUSE, RESUME & GET Progress .... uses the same command
format No parameters are required, only the MIC Opcode will be different    */

typedef struct micMediaPatrolAllCmd
{
    u8          mpa_ScsiOpCode;
    u8          mpa_MicSignature;
    u16         mpa_MicOpCode;
    u8          mpa_UniqueCmdId;
    u8          mpa_LoginKey;
    u32         mpa_Reserved0;
    u16         mpa_TransferLength;
    u16         mpa_Reserved1;
    u8          mpa_Reserved2;
    Control_t   mpa_Control;
} PACKED micMediaPatrolAllCmd_t;

typedef struct micMediaPatrolPDInfo
{
    u32 mppi_PDUniqueID;                /*  Physical device unique ID   */
    u16 mppi_PDFlatId;                  /*  Physical device Flat ID */
    u16 mppi_Reserved;                  /*  Reserved    */
} PACKED micMediaPatrolPDInfo_t;

/*
    NUMBER_CONFIGURED_PD_IN_CONTROLLER ?will be sum of mppd_CompletedPDCount
    and mppd_QueuedPDCount.
*/

#define NUMBER_CONFIGURED_PD_IN_CONTROLLER     1
typedef struct micMediaPatrolProgress
{
    u8  mppd_OverallPercentage;         /* Overall MP perentage complete */
    u8  mppd_State;                     /*  Current MP state    */
    u16 mppd_PDFlatId;                  /*  Flat ID of the MP Active PD */
    u32 mppd_PDUniqueID;                /*  MP Active PD Unique ID  */
    u8  mppd_ProgressinPercentage;      /*  % Progress in PD    */
    u8  mppd_Reserved[3];               /*  Reserved    */
    u32 mppd_CompletedPDCount;          /*  MP Completed PD count   */
    u32 mppd_QueuedPDCount;             /*  MP Queued PD count  */
    micMediaPatrolPDInfo_t mppd_PDDetails[NUMBER_CONFIGURED_PD_IN_CONTROLLER];
                                        /*  MP Info of each PD  */
} PACKED micMediaPatrolProgress_t;

typedef struct micHBAMediaPatrolPDInfo
{
    u64 mppi_wWatermark;        /* patrol watermark */
    u16 mppi_PDFlatId;          /*  Physical device Flat ID */
    u16 mppi_hFlags;            /* see above BGA_STATE_xxx */
    u16 mppi_hCount;            /* loop count */
    u16 mppi_hErrorCount;       /* error detected during media patrol */
    u16 mppi_hPercentage;       /* Runtime percentage, internal usage */
    u8  mppi_Reserved1[6];
} PACKED micHBAMediaPatrolPDInfo_t;

#define MAX_CONFIGURED_PHYDRVS_PER_CONTROLLER 16 /* HBA specific - ? */
typedef struct micHBAMediaPatrolProgress
{
    u32 mppd_CompletedPDCount;          /*  MP Completed PD count   */
    u32 mppd_RunningPDCount;            /*  MP Running PD count  */
    u8  mppd_Reserved[4];               /*  Reserved    */
    micHBAMediaPatrolPDInfo_t mppd_PDDetails[MAX_CONFIGURED_PHYDRVS_PER_CONTROLLER];
                                        /*  MP Info of each PD  */
} PACKED micHBAMediaPatrolProgress_t;


#define MP_NOT_ENABLED_IN_CONTROLLER    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x01 )
#define MP_NOT_ENABLED_IN_ANY_ARRAY    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x02 )
#define MP_CANNOT_START_NO_ARRAY_PRESENT   ( BGT_MODULE_SPECIFIC_ERROR_START + 0x03 )

/* PMIC_LDI_START        */
/* PMIC_LDI_QUICK_INIT   */
/* PMIC_LDI_STOP         */
/* PMIC_LDI_PAUSE        */
/* PMIC_LDI_RESUME       */
/* PMIC_LDI_GETPROGRESS  */

typedef struct micLdiCmd
{
    u8          ldi_ScsiOpCode;         /* vendor specific */
    u8          ldi_MicSignature;
    u16         ldi_MicOpCode;          /* like PMIC_LDI_START STOP etc*/
    u8          ldi_UniqueCmdId;        /* for IB cmd */
    u8          ldi_LoginKey;           /* for IB cmd */
    u16         ldi_LDFlatId;           /* logical drive Id for init or 0xFFFFFFFF for all active LDs*/
    u16         ldi_Reserved1;
    u16         ldi_TransferLength;     /* for IB 16 + pattern length if any only for quick init and start*/
    u16         ldi_Reserved2;          /* */
    u8          ldi_Reserved3;          /* */
    Control_t   ldi_Control;
} PACKED micLdiCmd_t;

typedef struct micLdiQuickStartCmd
{
    u8          ldi_ScsiOpCode;         /* vendor specific */
    u8          ldi_MicSignature;
    u16         ldi_MicOpCode;          /* like PMIC_LDI_QUICK_INIT STOP etc*/
    u8          ldi_UniqueCmdId;        /* for IB cmd */
    u8          ldi_LoginKey;           /* for IB cmd */
    u16         ldi_LDFlatId;           /* logical drive Id for init or 0xFFFFFFFF for all active LDs*/
    u16         ldi_QuickInitSizeInMB;  /* this value will be multiplied by (1024*1024) and align next stripe */
    u16         ldi_TransferLength;     /* for IB 16 + pattern length if any only for quick init and start*/
    u16         ldi_Reserved1;          /* */
    u8          ldi_Reserved2;          /* */
    Control_t   ldi_Control;
} PACKED micLdiQuickStartCmd_t;

#define PMIC_SECTOR_SIZE    512

typedef struct micLdiPattern
{
    u8  ldip_Pattern[PMIC_SECTOR_SIZE];   /* maximum is sector. could be less than that too( Ldi TranferLength-16)*/
} PACKED micLdiData_t;

/* possible state code that can be returned for Progress Data*/

/* how to send how many of these structures willl folllow*/
typedef struct micLdiProgress
{
    u32 ldi_LDUID;
    u16 ldi_LdFlatId;
    u8  ldi_LdiState;
    u8  ldi_ProgressinPercentage;
} PACKED micLdiProgress_t;

/* PMIC_REBUILD_START       */
/* PMIC_REBUILD_STOP        */
/* PMIC_REBUILD_PAUSE       */
/* PMIC_REBUILD_RESUME     */
/* PMIC_REBUILD_GETPROGRESS */
typedef struct micRebuildStartCmd
{
    u8          rbs_ScsiOpCode;
    u8          rbs_MicSignature;
    u16         rbs_MicOpCode;
    u8          rbs_UniqueCmdId;
    u8          rbs_LoginKey;
    u16         rbs_ArrayID;                 /* Array to rebuild */
    u16         rbs_PDSequenceNoInArray;     /* Dead drive sequence number in Disk Array */
    u16         rbs_TransferLength;
    u16         rbs_PDFlatId;               /* PD ID of new drive to rebuild */
    u8          rbs_OpType;              /* Type of operation Command*/
    Control_t   rbs_Control;
} PACKED micRebuildStartCmd_t;

/* For STOP, PAUSE, RESUME & Get Progress .... use the same command format
requires same parameters, only the MIC Opcode will change   */
typedef struct micRebuildOtherCmd
{
    u8          rbo_ScsiOpCode;
    u8          rbo_MicSignature;
    u16         rbo_MicOpCode;
    u8          rbo_UniqueCmdId;
    u8          rbo_LoginKey;
    u16         rbo_ArrayID;                 /* Array to rebuild */
    u16         rbo_PDSequenceNoInArray;     /* drive sequence number in Array */
    u16         rbo_TransferLength;
    u16         rbo_Reserved1;
    u8          rbo_OpType;              /* Type of operation Command*/
    Control_t   rbo_Control;
} PACKED micRebuildOtherCmd_t;

/* Definition of all possible types */
#define RBD_ACTION_RBD                 0x0
#define RBD_ACTION_TRANSITION          0x1
#define RBD_ACTION_PDM                 0x2
#define RBD_ACTION_INVALID             0xFF /* shall be used only in Get progress command to get the Status of all Types */

/* Return data for "Get Progress" command, the following structure will be
    returned for requested Disk Array / all the Disk Array whose rebuild
    is active in the controller */
typedef struct micRebuildProgress
{
    u8  rbpd_State;                     /*  Current state of the device */
    u8  rbpd_LD_ProgressinPercentage;   /*  % Progress in LD    */
    u8  rbpd_PD_ProgressinPercentage;   /*  % Progress in PD    */
    u8  rbpd_Type;                         /*  0 - Rebuild / 1 - Transition */
    u32 rbpd_PDUniqueID;                /*  Physical device unique ID   */
    u32 rbpd_LDUniqueID;                /*  Logical device Unique ID    */
    u16 rbpd_LDFlatId;                  /*  Logical device Flat ID  */
    u16 rbpd_PDFlatId;                  /*  Physical device Flat ID */
    u16 rbpd_SeqNumber;                 /* Rebuilding PD sequence Numeber   */
    u16 rbpd_ArrayID;                   /* Rebuild ArrayID  */
    u8  rbpd_Padding[4];                /* padding is added for In-Band path */
} PACKED micRebuildProgress_t;

#define RBD_SPARE_DRIVE_NOT_AVAILABLE           ( BGT_MODULE_SPECIFIC_ERROR_START + 0x01 )
#define RBD_LOGICAL_DRIVE_IN_ARRAY              ( BGT_MODULE_SPECIFIC_ERROR_START + 0x02 )
#define RBD_REDUNDANT_LOGICAL_DRIVE_IN_ARRAY    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x03 )
#define RBD_NO_CRITICAL_LOGICAL_DRIVE_IN_ARRAY  ( BGT_MODULE_SPECIFIC_ERROR_START + 0x04 )
#define RBD_PD_NOT_PRESENT                      ( BGT_MODULE_SPECIFIC_ERROR_START + 0x05 )
#define RBD_INVALID_SEQUENCE_NO                 ( BGT_MODULE_SPECIFIC_ERROR_START + 0x06 )
#define RBD_INVALID_DEAD_DRIVEID                ( BGT_MODULE_SPECIFIC_ERROR_START + 0x07 )
#define RBD_USER_STOPPED                         ( BGT_MODULE_SPECIFIC_ERROR_START + 0x08 )
#define RBD_INVALID_NEW_PDID                    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x09 )
#define RBD_PDM_NOT_ENABLED_IN_ARRAY            ( BGT_MODULE_SPECIFIC_ERROR_START + 0x0A )
#define RBD_PD_PFA_CONDITION_SET                ( BGT_MODULE_SPECIFIC_ERROR_START + 0x0B )
#define RBD_REQUESTED_OPERATION_TYPE_ERROR      ( BGT_MODULE_SPECIFIC_ERROR_START + 0x0C )
#define RBD_INVALID_PDSIZE                      ( BGT_MODULE_SPECIFIC_ERROR_START + 0x0D )
#define RBD_START_REQUESTED_ON_STALE_PD         ( BGT_MODULE_SPECIFIC_ERROR_START + 0x0E )
#define RBD_START_REQUESTED_ON_CONFIGURED_PD    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x0F )
#define RBD_DESTINATION_PD_IS_ALREADY_IN_USE    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x10 ) /* Destination Pd is already is use  for either PDM - Transition */
#define RBD_ARRAY_SET_FOR_TRANSPORTING          ( BGT_MODULE_SPECIFIC_ERROR_START + 0x11 ) /* Request operation can be accepted, since the array is marked for transportion */
#define RBD_ARRAY_INCOMPLETE                    ( BGT_MODULE_SPECIFIC_ERROR_START + 0x12 ) /* Request can not be accepted, Since the array is not complete */
#define RBD_REQUESTED_OPERATION_TYPE_ERROR_SRC_NOT_REVERTIBLE_SPARE ( BGT_MODULE_SPECIFIC_ERROR_START + 0x13 ) /* Error Return when start transition is requested for a non revertible spare as source dirve */
#define RBD_REQUESTED_OPERATION_TYPE_ERROR_SRC_PD_DEAD ( BGT_MODULE_SPECIFIC_ERROR_START + 0x14 ) /* Error Return when start PDM / transition is requested with dead src drive, only rebuild is possible at this suitation */
#define RBD_CONFIG_PD_INVALID_ARRAY_ID          ( BGT_MODULE_SPECIFIC_ERROR_START + 0x15 )          /* Configured PD array ID is incorrect */
#define RBD_DESTINATION_DSPARE_PD_NOT_DEDICATED_FOR_THIS_ARRAY          ( BGT_MODULE_SPECIFIC_ERROR_START + 0x16 )          /* The destination drive specified for rebuild / Transition / PDM is dedicated spare, but the destination drive is not dedicated for the source array */
#define RBD_SOURCE_PD_IS_ONLINE                 ( BGT_MODULE_SPECIFIC_ERROR_START + 0x17 ) /* Rebuild source Pd is online, rebuild cann't be started on an online data member */
#define RBD_NO_LD_PRESENT                       ( BGT_MODULE_SPECIFIC_ERROR_START + 0x18 )
#define RBD_ARRAY_DELETE_IN_PROGRESS            ( BGT_MODULE_SPECIFIC_ERROR_START + 0x19 )
#define RBD_RQST_ERROR_INVALID_CONTROLLER       ( BGT_MODULE_SPECIFIC_ERROR_START + 0x1A ) /* Request is received in slave controller cannot be processed */
#define RBD_ERROR_CODES_END                     (RBD_RQST_ERROR_INVALID_CONTROLLER + 1)

/* PMIC_RCK_START        */
/* PMIC_RCK_STOP         */
/* PMIC_RCK_PAUSE        */
/* PMIC_RCK_RESUME       */
/* PMIC_RCK_GETPROGRESS  */

typedef struct micRckCmd
{
    u8          rck_ScsiOpCode;         /* vendor specific */
    u8          rck_MicSignature;
    u16         rck_MicOpCode;          /* like PMIC_RCK_START STOP etc*/
    u8          rck_UniqueCmdId;
    u8          rck_LoginKey;           /* for IB cmd */
    u16         rck_LDFlatId;           /* logical drive Id for init or 0xFFFFFFFF for all active LDs*/
    u16         rck_Reserved1;
    u16         rck_TransferLength;     /* for IB 16 + pattern length if any only for quick init and start*/
    u16         rck_Reserved2;          /* */
    u8          rck_Policy;             /* Auto Fix / No Fix / stop or pause on first error, when RC concounters an error  */
    Control_t   rck_Control;
} PACKED micRckCmd_t;

/* Return data for "Get Progress" command, the following structure will be
    returned for the requested Logical drive / all the Logical drives whose
    RC is active */

typedef struct micRCProgressData
{
    u32 rcpd_LDUniqueID;                /*  Logical device UID  */
    u16 rcpd_LDFlatId;                  /*  Logical device Flat ID  */
    u8  rcpd_State;                     /*  Current state of the device */
    u8  rcpd_LD_ProgressinPercentage;   /*  % Progress in LD    */
} PACKED micRCProgressData_t;

#define RCK_LD_NOT_SYNCHRONIZED     ( BGT_MODULE_SPECIFIC_ERROR_START + 0x01 )
#define RCK_INVALID_RAID_LEVEL      ( BGT_MODULE_SPECIFIC_ERROR_START + 0x02 )

/* Lower nibble is used for policy Auto Fix / No Fix */
#define MIC_RCK_POLICY_AUTO_FIX     0x00
#define MIC_RCK_POLICY_NO_FIX       0x01

/* Higher nibble used for Action of RC on 1ST Inconsistent block    */
#define MIC_RCK_CONTINUE_1ST_ERROR  0x00
#define MIC_RCK_PASUE_1ST_ERROR     0x10

#define MIC_RCK_AUTOFIX_CONTINUE    0x00
#define MIC_RCK_NOFIX_CONTINUE      0x01
#define MIC_RCK_AUTOFIX_PAUSE       0x10
#define MIC_RCK_NOFIX_PAUSE         0x11

/* PMIC_BGSYNC_STOP        */
/* PMIC_BGSYNC_GETPROGRESS */

/* will use the same command format as LDI  ......*/
typedef struct micBKSyncAllCmd
{
    u8          bsa_ScsiOpCode;
    u8          bsa_MicSignature;
    u16         bsa_MicOpCode;
    u8          bsa_UniqueCmdId;
    u8          bsa_LoginKey;
    u16         bsa_LDFlatId;
    u16         bsa_Reserved0;
    u16         bsa_TransferLength;
    u16         bsa_Reserved1;
    u8          bsa_Reserved2;
    Control_t   bsa_Control;
} PACKED micBKSyncAllCmd_t;

/* Return data for "Get Progress" command, the following structure will be
    returned for the requested Logical drive / all the Logical drives whose
    Background synchronization is active */

typedef struct micBKSyncProgressData
{
    u32 bspd_LDUniqueID;                /*  Logical device UID  */
    u16 bspd_LDFlatId;                  /*  Logical device Flat ID  */
    u8  bspd_State;                     /*  Current state of the device */
    u8  bspd_LD_ProgressinPercentage;   /*  % Progress in LD    */
} PACKED micBKSyncProgressData_t;

/* possible states that can be returned in ProgressDataInfo for Back ground tasks*/
#define BGA_STATE_NONE              0x00     /* no BGA */
#define BGA_STATE_RUNNING           0x01     /* BGA is running on this array */
#define BGA_STATE_ABORTED           0x02  /* BGA was aborted - HBA specific */
#define BGA_STATE_PAUSED            0x03     /* BGA was paused by user */
#define BGA_STATE_AUTOPAUSED        0x04  /* BGA was pased by the RAID engine - HBA specific */

/* 0x05 ~ 0x0F reserved */

#define BGA_STATE_QUEUED            0x10  /* BGA is queued - IslaVista specific */
#define BGA_STATE_QUEUED_PAUSED     0x11  /* Queued RBD is paused - IslaVista specific */
#define BGA_STATE_YIELDED           0x12  /* BGA yielded to another higher priority BGA - IslaVista specific */
#define BGA_STATE_COMPLETED         0x13  /* MP is complete on this PD - IslaVista specific */

/* Event Logging Command and structure Definitions */

/* Event manager errors */
#define MICS_EVTMGR_GENERAL_ERROR           0x51
#define MICS_EVTMGR_ERR_NOT_INITIALIZED     0x52
#define MICS_EVTMGR_ERR_INVALID_SEQ_NO      0x53
#define MICS_EVTMGR_INVALID_LOGGING_AREA    0x54
#define MICS_EVTMGR_ERR_SAVING_SETTINGS     0x55
#define MICS_EVTMGR_ERR_WRITING_FLASH_DATA  0x56
/* End Event manager errors */

typedef struct micEventClearLogCmd
{
    u8        ecl_ScsiOpCode;
    u8        ecl_MicSignature;
    u16       ecl_MicOpCode;        /* 0x0701 */
    u8        ecl_UniqueCmdId;
    u8        ecl_LoginKey;
    u8        ecl_Ram:1;
    u8        ecl_Mdd:1;
    u8        ecl_Nvram:1;
    u8        ecl_Reserved0:5;
    u8        ecl_Reserved1[8];
    Control_t ecl_Control;
} PACKED micEventClearLogCmd_t;

typedef struct micEventDisableLoggingCmd
{
    u8        edl_ScsiOpCode;
    u8        edl_MicSignature;     /* 0x0702 */
    u16       edl_MicOpCode;
    u8        edl_UniqueCmdId;
    u8        edl_LoginKey;
    u8        edl_Reserved[9];
    Control_t edl_Control;
} PACKED micEventDisableLoggingCmd_t;

typedef struct micEventEnableLoggingCmd
{
    u8        eel_ScsiOpCode;
    u8        eel_MicSignature;
    u16       eel_MicOpCode;        /* 0x0703 */
    u8        eel_UniqueCmdId;
    u8        eel_LoginKey;
    u8        eel_Reserved[9];
    Control_t eel_Control;
} PACKED micEventEnableLoggingCmd_t;

typedef struct micEventGetStatsCmd
{
    u8        egsc_ScsiOpCode;
    u8        egsc_MicSignature;
    u16       egsc_MicOpCode;       /* 0x070c */
    u8        egsc_UniqueCmdId;
    u8        egsc_LoginKey;
    u32       egsc_Reserved0;
    u16       egsc_TransferLength;
    u16       egsc_TransferOffset;
    u8        egsc_Reserved1;
    Control_t egsc_Control;
} PACKED micEventGetStatsCmd_t;


/** 05/22/06 DC - Add Wait Event **/
typedef struct micEventWaitCmd
{
    u8        ewc_ScsiOpCode;
    u8        ewc_MicSignature;
    u16       ewc_MicOpCode;        /* 0x070d */
    u8        ewc_UniqueCmdId;
    u8        ewc_LoginKey;
    u8        ewc_Reserved0[9];
    Control_t ewc_Control;

} PACKED micEventWaitCmd_t;
/** 05/22/06 DC - Add Wait Event **/

typedef struct micEventGetCmd
{
    u8        eg_ScsiOpCode;
    u8        eg_MicSignature;
    u16       eg_MicOpCode;         /* 0x0704 */
    u8        eg_UniqueCmdId;
    u8        eg_LoginKey;
    u16       eg_SequenceNumber;
    u16       eg_EventCount;
    u16       eg_TransferLength;
    u16       eg_TransferOffset;
    u8        eg_Ram:1;
    u8        eg_Mdd:1;
    u8        eg_Nvram:1;
    u8        eg_Padding:5;
    Control_t eg_Control;
} PACKED micEventGetCmd_t;

typedef struct micEventGetEventInfoCmd
{
    u8        egei_ScsiOpCode;
    u8        egei_MicSignature;
    u16       egei_MicOpCode;       /* 0x0705 */
    u8        egei_UniqueCmdId;
    u8        egei_LoginKey;
    u32       egei_EventId;         /* EventId_t Strucuture */
    u16       egei_TransferLength;
    u16       egei_TransferOffset;
    u8        egei_Count;
    Control_t egei_Control;
} PACKED micEventGetEventInfoCmd_t;

typedef struct micEventGetSettingsCmd
{
    u8        egs_ScsiOpCode;
    u8        egs_MicSignature;
    u16       egs_MicOpCode;        /* 0x0707 */
    u8        egs_UniqueCmdId;
    u8        egs_LoginKey;
    u8        egs_Reserved0[4];
    u16       egs_TransferLength;
    u16       egs_TransferOffset;
    u8        egs_Reserved1;
    Control_t egs_Control;
} PACKED micEventGetSettingsCmd_t;

typedef struct micEventResetEventInfoCmd
{
    u8        erei_ScsiOpCode;
    u8        erei_MicSignature;
    u16       erei_MicOpCode;       /* 0x0708 */
    u8        erei_UniqueCmdId;
    u8        erei_LoginKey;
    u8        erei_Reserved0[4];
    u16       erei_TransferLength;
    u16       erei_TransferOffset;
    u8        erei_Reserved1;
    Control_t erei_Control;
} PACKED micEventResetEventInfoCmd_t;

typedef struct micEventSetEventInfoCmd
{
    u8        esei_ScsiOpCode;
    u8        esei_MicSignature;
    u16       esei_MicOpCode;       /* 0x0709 */
    u8        esei_UniqueCmdId;
    u8        esei_LoginKey;
    u16       esei_Count;
    u8        esei_Reserved0[2];
    u16       esei_TransferLength;
    u16       esei_TransferOffset;
    u8        esei_Reserved1;
    Control_t esei_Control;
} PACKED micEventSetEventInfoCmd_t;

typedef struct micEventSetSettingsCmd
{
    u8        ess_ScsiOpCode;
    u8        ess_MicSignature;
    u16       ess_MicOpCode;        /* 0x070b */
    u8        ess_UniqueCmdId;
    u8        ess_LoginKey;
    u8        ess_Reserved0[4];
    u16       ess_TransferLength;
    u16       ess_TransferOffset;
    u8        ess_Reserved1;
    Control_t ess_Control;
} PACKED micEventSetSettingsCmd_t;

typedef union
{
    u32 ei_DWord;

    struct /* Little Endian */
    {
        u16 ei_EventCode;
        u16 ei_ClassId;
    } PACKED  ei_EventId;
} PACKED EventId_t;

#define EVT_NUM_EVENTS_IN_BUFFER            1024
#define EVT_NUM_EVENTS_IN_MDD               16376

/* TODO: Change this once NVRAM size is changed */
//#define EVT_NUM_EVENTS_IN_NVRAM             63

#define EVT_EVENT_BUFFER_SIZE               ((EVT_NUM_EVENTS_IN_BUFFER *\
                                            sizeof (Event_t)) + sizeof (u16))
#define EVT_SEQNO_PTR                       (EVT_NUM_EVENTS_IN_BUFFER *\
                                            sizeof (Event_t))
#define EVT_MAX_EVENT_SPECIFIC_INFO_SIZE    32


#define EVT_LOCATION_CURRENT_MAX            0x4
#define EVT_LOCATION_RAM                    0x1
#define EVT_LOCATION_MDD                    0x2
#define EVT_LOCATION_BUZZER                 0x3
#define EVT_LOCATION_NVRAM                  0x4

#define EVT_MAX_SPEC_DATA_BYTES             32

typedef struct Event
{
    u32         evt_Timestamp;
    u8          evt_EnclosureId;
    u8          evt_ControllerId;
    u16         evt_DeviceId;
    u32         evt_VendorEventId;
    EventId_t   evt_EventId;
    u8          evt_EventInfo[EVT_MAX_SPEC_DATA_BYTES];
    u8          evt_Severity;
    u8          evt_Reserved0;
    u16         evt_SequenceNumber;
    u8          evt_Reserved1[12];
} PACKED Event_t;

typedef struct EventLogSettings
{
    u32 els_MaxRamEvents;       /* read only */
    u32 els_MaxMddEvents;       /* read only */
    u32 els_MaxNvramEvents;     /* read only */
    u8  els_LoggingEnabledRam;
    u8  els_LoggingEnabledMdd;
    u8  els_LoggingEnabledNvram;
    u8  els_Padding[3];
} PACKED EventLogSettings_t;

typedef struct LogLocations
{
    union
    {
        u8 Byte;
        struct
        {
            u8 ll_Ram:1;
            u8 ll_Mdd:1;
            u8 ll_Nvram:1;
            u8 ll_Buzzer:1;
            u8 ll_DefaultRam:1;
            u8 ll_DefaultMdd:1;
            u8 ll_DefaultNvram:1;
            u8 ll_DefaultBuzzer:1;
            u8 ll_BuzzerOnOff:1;
            u8 ll_BuzzerType:3;
        } PACKED Bits;
    } PACKED;
} PACKED LogLocations_t;

typedef struct EventInfo
{
    u32 ei_VendorEventId;
    u8  ei_DefaultSeverity;
    u8  ei_Severity;
} PACKED EventInfo_t;

typedef struct micEventLogLocation
{
    LogLocations_t ell_LogLocations;
    u8             ell_ClassId;
} PACKED micEventLogLocation_t;

typedef struct micEventInfo
{
    u32            ei_VendorEventId;
    EventId_t      ei_EventId;
    u8             ei_DefaultSeverity;
    u8             ei_Severity;
    LogLocations_t ei_LogLocations;
    u8             ei_Reserved0[5];
} PACKED micEventInfo_t;

typedef struct EventLocStats
{
    u32       elst_RamOldestSeqNo;
    u32       elst_RamLastSeqNo;
    u32       elst_RamNumValidEvents;
    u32       elst_RamLastUpdate;
    u8        elst_Reserved0[48];

    u32       elst_NvramOldestSeqNo;
    u32       elst_NvramLastSeqNo;
    u32       elst_NvramNumValidEvents;
    u32       elst_NvramLastUpdate;
    u8        elst_Reserved1[48];

    u32       elst_MddOldestSeqNo;
    u32       elst_MddLastSeqNo;
    u32       elst_MddNumValidEvents;
    u32       elst_MddLastUpdate;
    u8        elst_Reserved2[48];
} PACKED EventLocStats_t;

/* End Event Logging Command and structure Definitions */

/* Buzzer command & structure defs */

/* Buzzer errors */
#define MICS_BUZZER_IS_DISABLED             0x51
/* End Buzzer errors */

/* PMIC_BUZZER_TURN_ON */
typedef struct micBuzzerTurnOnCmd
{
    u8        bton_ScsiOpCode;
    u8        bton_MicSignature;
    u16       bton_MicOpCode;        /* 0x1100 */
    u8        bton_UniqueCmdId;
    u8        bton_LoginKey;
    u8        bton_ControllerId;
    u8        bton_Reserved0[8];
    Control_t bton_Control;
} PACKED micBuzzerTurnOnCmd_t;

/* PMIC_BUZZER_TURN_OFF */
typedef struct micBuzzerTurnOffCmd
{
    u8        btoff_ScsiOpCode;
    u8        btoff_MicSignature;
    u16       btoff_MicOpCode;        /* 0x1101 */
    u8        btoff_UniqueCmdId;
    u8        btoff_LoginKey;
    u8        btoff_ControllerId;
    u8        btoff_Reserved0[8];
    Control_t btoff_Control;
} PACKED micBuzzerTurnOffCmd_t;

#ifdef DURATION_SUPPORTED
/* PMIC_BUZZER_SET_DURATION */
typedef struct micBuzzerSetDurationCmd
{
    u8        bsd_ScsiOpCode;
    u8        bsd_MicSignature;
    u16       bsd_MicOpCode;        /* 0x1104 */
    u8        bsd_UniqueCmdId;
    u8        bsd_LoginKey;
    u8        bsd_ControllerId;
    u32       bsd_Duration;         /* in seconds */
    u8        bsd_Reserved0[4];
    Control_t bsd_Control;
} PACKED micBuzzerSetDurationCmd_t;

/* PMIC_BUZZER_GET_DURATION */
typedef struct micBuzzerGetDurationCmd
{
    u8        bgd_ScsiOpCode;
    u8        bgd_MicSignature;
    u16       bgd_MicOpCode;        /* 0x1105 */
    u8        bgd_UniqueCmdId;
    u8        bgd_LoginKey;
    u8        bgd_ControllerId;
    u8        bgd_Reserved0[8];
    Control_t bgd_Control;
} PACKED micBuzzerGetDurationCmd_t;
#endif

/* PMIC_BUZZER_GET_STATUS */
typedef struct micBuzzerGetStatusCmd
{
    u8        bgs_ScsiOpCode;
    u8        bgs_MicSignature;
    u16       bgs_MicOpCode;        /* 0x1106 */
    u8        bgs_UniqueCmdId;
    u8        bgs_LoginKey;
    u8        bgs_ControllerId;
    u8        bgs_Reserved0[3];
    u16       bgs_TransferLength;
    u16       bgs_TransferOffset;
    u8        bgs_Reserved1;
    Control_t bgs_Control;
} PACKED micBuzzerGetStatusCmd_t;

typedef struct BuzzerStatus
{
    u8        bs_Sounding;
    u8        bs_Reserved[7];
} PACKED micBuzzerStatus_t;

/* End Buzzer command & structure defs */

/* Statistics monitoring command & structure defs */
/* PMIC_STATS_RESET */
typedef struct micStatsReset
{
    u8        sr_ScsiOpCode;
    u8        sr_MicSignature;
    u16       sr_MicOpCode;        /* 0x1200 */
    u8        sr_UniqueCmdId;
    u8        sr_LoginKey;
    u8        sr_ObjectId;
    u8        sr_Reserved0[6];
    u8        sr_ObjectCount;
    Control_t sr_Control;
} PACKED micStatsReset_t;

/* PMIC_STATS_GET_CONTROLLER */
typedef struct micStatsGetController
{
    u8        sgc_ScsiOpCode;
    u8        sgc_MicSignature;
    u16       sgc_MicOpCode;        /* 0x1203 */
    u8        sgc_UniqueCmdId;
    u8        sgc_LoginKey;
    u8        sgc_ControllerId;
    u8        sgc_Reserved0[3];
    u16       sgc_TransferLength;
    u16       sgc_TransferOffset;
    u8        sgc_ControllerCount;
    Control_t sgc_Control;
} PACKED micStatsGetController_t;

/* PMIC_STATS_GET_LOGICAL_DRIVE */
typedef struct micStatsGetLogicalDrive
{
    u8        sgld_ScsiOpCode;
    u8        sgld_MicSignature;
    u16       sgld_MicOpCode;        /* 0x1204 */
    u8        sgld_UniqueCmdId;
    u8        sgld_LoginKey;
    u16       sgld_LogicalDriveId;
    u16       sgld_LogicalDriveCount;
    u16       sgld_TransferLength;
    u16       sgld_TransferOffset;
    u8        sgld_Reserved0;
    Control_t sgld_Control;
} PACKED micStatsGetLogicalDrive_t;

/* PMIC_STATS_GET_PHYSICAL_DRIVE */
typedef struct micStatsGetPhysicalDrive
{
    u8        sgpd_ScsiOpCode;
    u8        sgpd_MicSignature;
    u16       sgpd_MicOpCode;        /* 0x1205 */
    u8        sgpd_UniqueCmdId;
    u8        sgpd_LoginKey;
    u16       sgpd_PhysicalDriveId;
    u16       sgpd_PhysicalDriveCount;
    u16       sgpd_TransferLength;
    u16       sgpd_TransferOffset;
    u8        sgpd_Reserved0;
    Control_t sgpd_Control;
} PACKED micStatsGetPhysicalDrive_t;

/* PMIC_STATS_MONITOR_START */
typedef struct micStatsMonitorStart
{
    u8        sms_ScsiOpCode;
    u8        sms_MicSignature;
    u16       sms_MicOpCode;
    u8        sms_UniqueCmdId;
    u8        sms_LoginKey;
    u16       sms_Reserved0;
    u16       sms_Reserved1;
    u16       sms_TransferLength;
    u16       sms_TransferOffset;
    u8        sms_Reserved2;
    Control_t sms_Control;
} PACKED micStatsMonitorStart_t;

typedef struct micStatsInfo
{
    u16       si_NoOfLDs;
    u16       si_NoOfPDs;
    u8        si_NoOfPorts;
    u8        si_Reserved0[3];
} PACKED micStatsInfo_t;  /* 8 bytes */

typedef struct micStatsLD
{
    u8        sld_LDId;
    u8        sld_CacheUsage;     /*% cache usage*/
    u8        sld_DirtyCache;     /*% dirty cache */
    u8        sld_Reserved0[15];  /*reserved for future usage */
    u16       sld_MaxLatency;     /*in ms */
    u16       sld_MinLatency;     /*in ms */
    u16       sld_AverLatency;    /*in ms */
    u64       sld_IOReq;          /*number of IOs */
    u64       sld_BandWidth;      /*in bytes/second */
} PACKED micStatsLD_t; /* 40 bytes */

typedef struct micStatsPD
{
    u8        spd_PDId;
    u8        spd_Reserved0[9];   /*reserved for future usage */
    u16       spd_MaxLatency;    /*in ms */
    u16       spd_MinLatency;    /*in ms */
    u16       spd_AverLatency;    /*in ms */
    u64       spd_IOReq;          /*number of IOs */
    u64       spd_BandWidth;      /*in bytes/second */
} PACKED micStatsPD_t; /* 32 bytes */

typedef struct micStatsPort
{
    u8        spt_PortId;
    u8        spt_Reserved0[9];   /*reserved for future usage */
    u16       spt_MaxLatency;     /*in ms */
    u16       spt_MinLatency;     /*in ms */
    u16       spt_AverLatency;    /*in ms */
    u64       spt_IOReq;          /*number of IOs */
    u64       spt_BandWidth;      /*in bytes/second */
} PACKED micStatsPort_t;

typedef struct micStatsLDExt
{
    u8        sld_LDId;
    u8        sld_CacheUsage;        /*% cache usage */
    u8        sld_DirtyCache;        /*% dirty cache */
    u8        sld_WriteCache;        /*% write cache */
    u32       sld_Reserved0;         /* reserved */
    u32       sld_Reserved1;         /* reserved */
    u16       sld_MaxReadLatency;    /* maximum read latency in ms */
    u16       sld_MaxWriteLatency;   /* maximum write latency in ms */
    u16       sld_MinReadLatency;    /* minimum read latency in ms */
    u16       sld_MinWriteLatency;   /* minimum write latency in ms */
    u16       sld_AverReadLatency;   /* average read latency in ms */
    u16       sld_AverWriteLatency;  /* average write latency in ms */
    u64       sld_ReadReqs;          /* number of read requests */
    u64       sld_WriteReqs;         /* number of write requests */
    u64       sld_ReadBandWidth;     /* read bandwidth in bytes/second */
    u64       sld_WriteBandWidth;    /* write bandwidth in bytes/seconds */
    u64       sld_Reserved2;         /* reserved */
} PACKED micStatsLDExt_t; /* 64 bytes */

typedef struct micStatsPDExt
{
    u8        spd_PDId;
    u8        spd_Reserved0;         /*reserved for future usage */
    u16       spd_Reserved1;         /*reserved for future usage */
    u16       spd_MaxReadLatency;    /* maximum read latency in ms */
    u16       spd_MaxWriteLatency;   /* maximum write latency in ms */
    u16       spd_MinReadLatency;    /* minimum read latency in ms */
    u16       spd_MinWriteLatency;   /* minimum write latency in ms */
    u16       spd_AverReadLatency;   /* average read latency in ms */
    u16       spd_AverWriteLatency;  /* average write latency in ms */
    u64       spd_ReadReqs;          /* number of read requests */
    u64       spd_WriteReqs;         /* number of write requests */
    u64       spd_ReadBandWidth;     /* read bandwidth in bytes/second */
    u64       spd_WriteBandWidth;    /* write bandwidth in bytes/second */
    u64       spd_Reserved2;         /* reserved for future usage */
} PACKED micStatsPDExt_t; /* 56 bytes */

typedef struct micStatsPortExt
{
    u8        spt_PortId;
    u8        spt_Reserved0;          /* reserved for future usage */
    u16       spt_Reserved1;          /* reserved for future usage */
    u16       spt_MaxReadLatency;     /* maximum read latency in ms */
    u16       spt_MaxWriteLatency;    /* maximum write latency in ms */
    u16       spt_MinReadLatency;     /* minimum read latency in ms */
    u16       spt_MinWriteLatency;    /* minimum write latency in ms */
    u16       spt_AverReadLatency;    /* average read latency in ms */
    u16       spt_AverWriteLatency;   /* average write latency in ms */
    u64       spt_ReadReqs;           /* number of read requests */
    u64       spt_WriteReqs;          /* number of write requests */
    u64       spt_ReadBandWidth;      /* read bandwidth in bytes/second */
    u64       spt_WriteBandWidth;     /* write bandwidth in bytes/second */
    u64       spt_Reserved2;          /* reserved for future usage */
} PACKED micStatsPortExt_t; /* 56 byte */

/* PMIC_STATS_GET_STATISTICS & PMIC_STATS_GET_STATISTICS_EXT */
typedef struct micStatsGetPerformanceMonitoringData
{
    u8        sgpmd_ScsiOpCode;
    u8        sgpmd_MicSignature;
    u16       sgpmd_MicOpCode;
    u8        sgpmd_UniqueCmdId;
    u8        sgpmd_LoginKey;
    u16       sgpmd_Reserved0;
    u16       sgpmd_Reserved1;
    u16       sgpmd_TransferLength;
    u16       sgpmd_TransferOffset;
    u8        sgpmd_Reserved2;
    Control_t sgpmd_Control;
} PACKED micStatsGetPerformanceMonitoringData_t;

typedef struct StatsController
{
    u8        scntr_ControllerId;
    u8        scntr_Reserved0[7];
    u64       scntr_BlocksTransferred;
    u64       scntr_ReadBlocksTransferred;
    u64       scntr_WriteBlocksTransferred;
    u32       scntr_Errors;
    u32       scntr_ReadErrors;
    u32       scntr_WriteErrors;
    u32       scntr_NonRWErrors;
    u64       scntr_IOReq;
    u64       scntr_ReadIOReq;
    u64       scntr_WriteIOReq;
    u64       scntr_NonRWReq;
    u32       scntr_Reserved1;
    u32       scntr_Reserved2;
    u64       scntr_statsStartTime;
    u64       scntr_statsCollectionTime;
} PACKED StatsController_t;

typedef struct micStatsController
{
    u16               mscntr_Count;
    u8                mscntr_Reserved[6];
    StatsController_t mscntr_Stats[1];
} PACKED micStatsController_t;

typedef struct StatsLogicalDrive
{
    u8        sld_LogicalDriveId;
    u8        sld_Reserved0[7];
    u64       sld_BlocksTransferred;
    u64       sld_ReadBlocksTransferred;
    u64       sld_WriteBlocksTransferred;
    u32       sld_Errors;
    u32       sld_ReadErrors;
    u32       sld_WriteErrors;
    u32       sld_NonRWErrors;
    u64       sld_IOReq;
    u64       sld_ReadIOReq;
    u64       sld_WriteIOReq;
    u64       sld_NonRWReq;
    u64       sld_statsStartTime;
    u64       sld_statsCollectionTime;
} PACKED StatsLogicalDrive_t;

typedef struct micStatsLogicalDrive
{
    u16                 msld_Count;
    u8                  msld_Reserved[6];
    StatsLogicalDrive_t msld_Stats[1];
} PACKED micStatsLogicalDrive_t;

typedef struct StatsPhysicalDrive
{
    u8        spd_PhysicalDriveId;
    u8        spd_Reserved0[3];
#define TARGET_MAX_PATH   (2)
    u16       spd_PathAvgResponseTime[TARGET_MAX_PATH]; /* millisecs */
    u64       spd_BlocksTransferred;
    u64       spd_ReadBlocksTransferred;
    u64       spd_WriteBlocksTransferred;
    u32       spd_Errors;
    u32       spd_ReadErrors;
    u32       spd_WriteErrors;
    u32       spd_NonRWErrors;
    u64       spd_IOReq;
    u64       spd_ReadIOReq;
    u64       spd_WriteIOReq;
    u64       spd_NonRWReq;
    u64       spd_statsStartTime;
    u64       spd_statsCollectionTime;
} PACKED StatsPhysicalDrive_t;

typedef struct micStatsPhysicalDrive
{
    u16                  mspd_Count;
    u8                   mspd_Reserved[6];
    StatsPhysicalDrive_t mspd_Stats[1];
} PACKED micStatsPhysicalDrive_t;

typedef struct micStatsPhysicalDriveExt
{
    u16       spd_PhysicalDriveId;
    u8        spd_Reserved0[6];
    u64       spd_BlocksTransferred;
    u64       spd_ReadBlocksTransferred;
    u64       spd_WriteBlocksTransferred;
    u32       spd_Errors;
    u32       spd_ReadErrors;
    u32       spd_WriteErrors;
    u32       spd_NonRWErrors;
    u64       spd_IOReq;
    u64       spd_ReadIOReq;
    u64       spd_WriteIOReq;
    u64       spd_NonRWReq;
    u64       spd_statsStartTime;
    u64       spd_statsCollectionTime; // 96 bytes at this point

    // the following are extended PD stats
    u32       spd_PathAvgResponseTime[TARGET_MAX_PATH];
    u32       spd_PathMaxResponseTime[TARGET_MAX_PATH];
    u8        spd_Reserved1[144];       // 256 bytes at this point
} PACKED micStatsPhysicalDriveExt_t;

typedef struct micStatsPhysicalDriveHeaderExt
{
    u16       mspd_Count;
    u16       mspd_StatsEntryLength;    // if this is 0 or 96, SW uses StatsPhysicalDrive_t
                                        // to interpret mspd_Stats, if it is 256, SW uses
                                        // micStatsPhysicalDriveExt_t to interpret mspd_Stats.
    u8        mspd_Reserved[4];
} PACKED micStatsPhysicalDriveHeaderExt_t;


/* End Statistics monitoring command & structure defs */

/* Command specific structures - End */

/* pass through command structure definition*/
typedef struct AtaCmdBlock
{
    u8  acb_FeaturesPrev;
    u8  acb_FeaturesCur;
    u8  acb_SectorCountPrev;
    u8  acb_SectorCountCur;
    u8  acb_LbaLowPrev;
    u8  acb_LbaLowCur;
    u8  acb_LbaMidPrev;
    u8  acb_LbaMidCur;
    u8  acb_LbaHighPrev;
    u8  acb_LbaHighCur;
    u8  acb_DeviceRegister;
    u8  acb_CommandCode;     /* All na registers for a given command code must be zero*/
} PACKED micACB_t;

/*actual pass through command structure that comes embedd in the data area or the extended command area*/
typedef struct MicPassThroughData
{
    micACB_t            ptd_AtaCmd;                 /* 13 bytes*/
    u32                 ptd_ReadWriteDataLength;    /* in bytes maximum of 64 k bytes to read or write*/
} PACKED micPTD_t;

/* be it a split command or full command */
typedef struct MicPassThruCmd
{
    u8                  pt_ScsiOpCode;      /* can indicate secure or unsecure scsi opcode*/
    u8                  pt_MicSignature;
    u16                 pt_MicOpCode;       /* class code for passthrough*/
    union
    {
        u8              pt_ConfigLock;        /* UniqueCmdId is very much needed for passthru read(which becomes bidirectional) command*/
        u8              pt_UniqueCmdId;
    }PACKED u;
    u8                  pt_LoginKey;
    u8                  pt_Controller;       /* controller number */
    u8                  pt_Channel;          /* channel Number */
    u16                 pt_TargetId;         /* Target number need mechanism for flat ID if flatId,ignore other 2 fields*/
    u16                 pt_TransferLength;   /* size of Data + buffer header, Data area actually contains the PT Cmd this actually gives the transfer size for partial commands*/
    u16                 pt_TransferOffset;
    u8                  pt_ReservedArea1;       /* upper 4 buts define retry value, 4 bits define time out value in seconds*/
    u8                  pt_Control;
    micPTD_t            pt_extCmdArea;          /* contains actual passthrough command, not data*/
                                             /* For InBand, copy this to dbh_ExtendedCmd */
                                             /* of DataBufferHeader_t and send only      */
                                             /* 16 Byte as Command                       */
} PACKED micPTCmd_t;


typedef struct MicPassThroughDataForSas
{
   u8 CDB[16];
}micPTDSAS_t;

/* be it a split command or full command */
typedef struct MicPassThruCmdForSAS
{
    u8                  pt_ScsiOpCode;      /* can indicate secure or unsecure scsi opcode*/
    u8                  pt_MicSignature;
    u16                 pt_MicOpCode;       /* class code for passthrough*/
    union
    {
        u8              pt_ConfigLock;        /* UniqueCmdId is very much needed for passthru read(which becomes bidirectional) command*/
        u8              pt_UniqueCmdId;
    }PACKED u;
    u8                  pt_LoginKey;
    u16                 pt_DataLengthLsb;       /* Pure data length for read/write commands since cdbs can be byte orblock based LSB field is belowafter couple of fileds*/
    u16                 pt_TargetId;         /* this flat ID of SAS/SATA drive,ignore other 2 fields( controller and channel*/
    u16                 pt_TransferLength;   /* size of Data + buffer header, Data area actually contains the PT Cmd
                                                this actually gives the transfer size for partial commands*/
    u16                 pt_TransferOffset;
    u8                  pt_DataLengthMsb;      /* Pure data length for read/write commands since cdbs can be byte orblock based*/
    u8                  pt_Control;
    micPTDSAS_t         pt_extCmdArea;          /* contains actual passthrough SCSIcommand, not data*/
                                             /* For InBand, copy this to dbh_ExtendedCmd */
                                             /* of DataBufferHeader_t and send only      */
                                             /* 16 Byte as Command                       */
} PACKED micPTCmdSas_t;

#define MICS_CHAP_INVALID_FLAGS           (MICS_MODULE_SPECIFIC_ERROR_START + 1)
#define MICS_LOCAL_CHAP_PRESENT           (MICS_MODULE_SPECIFIC_ERROR_START + 2)
#define MICS_CHAP_RECORD_NOT_FOUND        (MICS_MODULE_SPECIFIC_ERROR_START + 3)
#define MICS_CHAP_COMMAND_ERROR           (MICS_MODULE_SPECIFIC_ERROR_START + 4)
#define MICS_PING_FAILED                  (MICS_MODULE_SPECIFIC_ERROR_START + 5)
#define MICS_GROUP_TAG_MATCH              (MICS_MODULE_SPECIFIC_ERROR_START + 6)
#define MICS_INVALID_MAX_CONNECTIONS      (MICS_MODULE_SPECIFIC_ERROR_START + 7)
#define MICS_INVALID_FLAGS                (MICS_MODULE_SPECIFIC_ERROR_START + 8)
#define MICS_INVALID_MAX_BURST_LENGTH     (MICS_MODULE_SPECIFIC_ERROR_START + 9)
#define MICS_UNSUP_ERR_RECOV_LVL         (MICS_MODULE_SPECIFIC_ERROR_START + 10)
#define MICS_INVALID_FIRST_BURST_LENGTH  (MICS_MODULE_SPECIFIC_ERROR_START + 11)
#define MICS_INVALID_MAX_R2T             (MICS_MODULE_SPECIFIC_ERROR_START + 12)
#define MICS_INVALID_TIME2WAIT           (MICS_MODULE_SPECIFIC_ERROR_START + 13)
#define MICS_INVALID_TIME2RETAIN         (MICS_MODULE_SPECIFIC_ERROR_START + 14)
#define MICS_NO_RESOURCE_FOR_FIRST_BURST_LENGTH     (MICS_MODULE_SPECIFIC_ERROR_START + 15)
#define MICS_PEER_CHAP_NAME_ALREADY_PRESENT         (MICS_MODULE_SPECIFIC_ERROR_START + 16)
#define MICS_NO_CONNECTION                          (MICS_MODULE_SPECIFIC_ERROR_START + 17)
#define MICS_CONNECTION_FAILED                      (MICS_MODULE_SPECIFIC_ERROR_START + 18)
#define MICS_FE_CONTROLLER_FAILED_TO_RESPOND        (MICS_MODULE_SPECIFIC_ERROR_START + 19)
#define MICS_FE_CONTROLLER_NOT_READY                (MICS_MODULE_SPECIFIC_ERROR_START + 20)
#define MICS_FE_CONTROLLER_BUSY                     (MICS_MODULE_SPECIFIC_ERROR_START + 21)

/* LinkLayer service errors */
#define MICS_LLS_INVALID_MEMBER_PORT        (MICS_MODULE_SPECIFIC_ERROR_START + 30)
#define MICS_LLS_IP_ALREADY_EXIST           (MICS_MODULE_SPECIFIC_ERROR_START + 31)
#define MICS_LLS_OPERATION_NOT_PERMITTED    (MICS_MODULE_SPECIFIC_ERROR_START + 32)

#define MICS_LLS_VLAN_IF_ALREADY_EXIST      (MICS_MODULE_SPECIFIC_ERROR_START + 38)
#define MICS_LLS_VLAN_IF_DOESNOT_EXIST      (MICS_MODULE_SPECIFIC_ERROR_START + 39)
#define MICS_LLS_VLAN_IF_MAX_EXCEED         (MICS_MODULE_SPECIFIC_ERROR_START + 40)
#define MICS_LLS_VLAN_INVALID_TAG           (MICS_MODULE_SPECIFIC_ERROR_START + 41)
#define MICS_LLS_VLAN_TAG_FOR_PORT_EXIST    (MICS_MODULE_SPECIFIC_ERROR_START + 42)
#define MICS_LLS_VLAN_INTERFACE_BUSY        (MICS_MODULE_SPECIFIC_ERROR_START + 43)
#define MICS_LLS_VLAN_MTU_MORE_THAN_PORT    (MICS_MODULE_SPECIFIC_ERROR_START + 44)
#define MICS_LLS_VLAN_SET_IP_FAILED         (MICS_MODULE_SPECIFIC_ERROR_START + 45)
#define MICS_LLS_VLAN_SUBNET_ALREADY_EXIST  (MICS_MODULE_SPECIFIC_ERROR_START + 46)

#define MICS_LLS_TRUNK_INVALID_INDEX        (MICS_MODULE_SPECIFIC_ERROR_START + 52)
#define MICS_LLS_TRUNK_IF_MAX_EXCEED        (MICS_MODULE_SPECIFIC_ERROR_START + 53)
#define MICS_LLS_TRUNK_IF_ALREADY_EXIST     (MICS_MODULE_SPECIFIC_ERROR_START + 54)
#define MICS_LLS_TRUNK_IF_DOESNOT_EXIST     (MICS_MODULE_SPECIFIC_ERROR_START + 55)
#define MICS_LLS_TRUNK_MEMBER_NOT_EXIST     (MICS_MODULE_SPECIFIC_ERROR_START + 56)
#define MICS_LLS_TRUNK_MEMBER_CANNOT_ADD    (MICS_MODULE_SPECIFIC_ERROR_START + 57)
#define MICS_LLS_TRUNK_MEMBER_CANNOT_DEL    (MICS_MODULE_SPECIFIC_ERROR_START + 58)
#define MICS_LLS_TRUNK_MAX_MEMBER_EXCEED    (MICS_MODULE_SPECIFIC_ERROR_START + 59)
#define MICS_LLS_TRUNK_CANNOT_DEL           (MICS_MODULE_SPECIFIC_ERROR_START + 60)
#define MICS_LLS_TRUNK_MEMBER_CONFIG_LOCK   (MICS_MODULE_SPECIFIC_ERROR_START + 61)

#define MICS_ISCSI_MICROCODE_UPDATING       (MICS_MODULE_SPECIFIC_ERROR_START + 72)
/* End LinkLayer service errors */

#define MIC_ISCSI_NODE_PARAMETER_PAGE           0x01
#define MIC_ISCSI_TCPIP_ADVANCED_OPTION_PAGE    0x02
#define MIC_ISCSI_GIGE_OPTION_PAGE              0x03
#define MIC_ISCSI_CHAP_CONFIGURATION_PAGE       0x04
#define MIC_ISCSI_SLP_CONFIGURATION_PAGE        0x05
#define MIC_ISCSI_ISNS_CONFIGURATION_PAGE       0x06
#define MIC_ISCSI_CHIP_SPECIFIC_INFO_PAGE       0x07
#define MIC_ISCSI_DRIVER_DEBUG_INFO_PAGE        0x08
#define MIC_ISCSI_PORT_STATISTICS_PAGE          0x09
#define MIC_ISCSI_SESSION_STATS_PAGE            0x0A
#define MIC_ISCSI_SESSION_PARAMETERS_PAGE       0x0B
#define MIC_ISCSI_TARGET_PORT_PARAMETERS_PAGE   0x0C
#define MIC_ISCSI_TARGET_LOGIN_LOGOUT_STATS_PAGE    0x0D
#define MIC_ISCSI_NODE_STATISTICS_PAGE              0x0E
#define MIC_ISCSI_EXTENDED_NODE_PARAMS_PAGE         0x0F
#define MIC_ISCSI_PORTAL_PARAM_PAGE                 0x10
#define MIC_ISCSI_LLS_VLAN_PAGE                     0x11
#define MIC_ISCSI_LLS_LINK_AGGR_PAGE                0x12
#define MIC_ISCSI_ISNAP_MICROCODE_UPDATE_PAGE       0x13
#define MIC_ISCSI_NODE_DEFAULT_PARAMETER_PAGE       0x14
#define MIC_ISCSI_ACCESS_ALL_PORTS                  0xFF
#define MIC_ISCSI_ACCESS_ALL_NODES                  0xFF
#define MIC_ISCSI_ACCESS_ALL_SESSIONS               0xFF
#define MIC_ISCSI_ACCESS_ALL_VLANS                  0xFF
#define MIC_ISCSI_ACCESS_ALL_LINK_AGGS              0xFF
#define MIC_ISCSI_ACCESS_ALL_PAGES                  0xFF

typedef struct micISCSIGetParamsInfoCmd
{
    u8  igpc_ScsiOpCode;
    u8  igpc_MicSignature;
    u16 igpc_MicOpCode;
    u8  igpc_UniqueCmdId;
    u8  igpc_LoginKey;
    u8  igpc_PortID;
    u8  igpc_PageCode;
    u8  igpc_SessionID;
    u8  igpc_Reserved2;
    u16 igpc_TransferLength;
    u16 igpc_TransferOffset;
    u8  igpc_Reserved3;
    Control_t igspc_Control;

} PACKED micISCSIGetParamsInfoCmd_t;


typedef struct micISCSISetParamsCmd
{
    u8  ispc_ScsiOpCode;
    u8  ispc_MicSignature;
    u16 ispc_MicOpCode;
    u8  ispc_UniqueCmdId;
    u8  ispc_LoginKey;
    u8  ispc_PortID;
/* PortID is valid for only a few pages.
 * for Node Parameter Page NodeID
 */
    u8  ispc_PageCode;
    u16 isspc_SessionIndex;
    u16 isspc_TransferLength;
    u16 isspc_TransferOffset;
    u8  ispc_Reserved1;
    Control_t ispc_Control;

} PACKED micISCSISetParamsCmd_t;


typedef struct micISCSIAddParamCmd
{
    u8        iapc_ScsiOpCode;
    u8        iapc_MicSignature;
    u16       iapc_MicOpCode;
    u8        iapc_ConfigLock;
    u8        iapc_LoginKey;
    u8        iapc_Reserved0;
    u8        iapc_PageCode;
    u16       iapc_Index; /*General purpose ID. Uses are based on page code */
    u16       iapc_TransferLength;
    u16       iapc_TransferOffset;
    u8        iapc_Reserved1;
    Control_t iapc_Control;
} PACKED micISCSIAddParamCmd_t;


typedef struct micISCSIDelParamCmd
{
    u8        idpc_ScsiOpCode;
    u8        idpc_MicSignature;
    u16       idpc_MicOpCode;
    u8        idpc_ConfigLock;
    u8        idpc_LoginKey;
    u8        idpc_Reserved0;
    u8        idpc_PageCode;
    u16       idpc_Index; /*General purpose ID. Uses are based on page code */
    u8        idpc_Reserved1[5];
    Control_t idpc_Control;
} PACKED micISCSIDelParamCmd_t;


typedef struct micISCSIReset
{
    u8  ispc_ScsiOpCode;
    u8  ispc_MicSignature;
    u16 ispc_MicOpCode;
    u8  ispc_UniqueCmdId;
    u8  ispc_LoginKey;
    u8  ispc_PortID;
/* PortID is valid for only a few pages.
 * for Node Parameter Page NodeID
 */
    u8  ispc_PageCode;
    u16 isspc_SessionIndex;
    u16 isspc_TransferLength;
    u16 isspc_TransferOffset;
    u8  ispc_Reserved1;
    Control_t ispc_Control;

} PACKED micISCSIResetCmd_t;


typedef struct micISCSINASGetSetCmd
{
    u8  ings_ScsiOpCode;
    u8  ings_MicSignature;
    u16 ings_MicOpCode;
    u8  ings_UniqueCmdId;
    u8  ings_LoginKey;
    u8  ings_Reserved0;
    u8  ings_PageCode;
    u8  ings_Reserved1;
    u8  ings_Reserved2;
    u16 ings_TransferLength;
    u16 ings_TransferOffset;
    u8  ings_Reserved3;
    Control_t ings_Control;

} PACKED micISCSINASGetSetCmd_t;


#define MIC_ISCSI_OPTION_IMMEDIATE_DATA             0x00000001
                                                        /* Default : Enabled */

#define MIC_ISCSI_OPTION_INITIAL_R2T                0x00000002
                                                        /* Default : Enabled */

#define MIC_ISCSI_OPTION_HEADER_DIGEST              0x00000004
                                                        /* Default : Disabled */
#define MIC_ISCSI_OPTION_DATA_DIGEST                0x00000008
                                                        /* Default : Disabled */
#define MIC_ISCSI_OPTION_UNI_CHAP_AUTH              0x00000010
                                                        /* Default : Disabled */
#define MIC_ISCSI_OPTION_ACCESS_CTRL                0x00000020
                                                        /* Default : Disabled */

/* The Following Two Flags are Read-Only and Cannot be set */

#define MIC_ISCSI_OPTION_DATA_PDU_INORDER           0x00000040
                                                        /* Default : Enabled */
#define MIC_ISCSI_OPTION_DATA_SEQ_INORDER           0x00000080
                                                        /* Default : Enabled */
#define MIC_ISCSI_OPTION_BIDI_CHAP_AUTH             0x00000100
                                                        /* Default : Enabled */
#define MIC_ISCSI_OPTION_NOP_IN_ACTIVE              0x00000200

#define MIC_ISCSI_NODE_FLAG_NODE_UP_DOWN            0x00000001 /* If the bit is
                                                                  set, node is
                                                                  Up */
/* For Set Parameter Command, the read-only fields are don't-care */
/* Size : 336 */
typedef struct NodeParameterData
{

    u16 npd_ISCSINodeID;
    u16 npd_Reserved1;
    u32 npd_NodeFlag; /* Read-Only */
    u8  npd_ISCSINodeName[256];
    u8  npd_ISCSINodeAlias[32]; /* UTF-8 Encoded String */
    u32 npd_ISCSINodeOptionFlags;
    u32 npd_ISCSINodeMaxOutstandingR2T;
                                     /* Default : 1
                                        Range : 1 - 65535 */

    u32 npd_ISCSINodeFirstBurstLength;
                                     /* Default : 65536
                                        Range : 512 - 16777215 (16 MB) */
    u32 npd_ISCSINodeMaxBurstLength;
                                     /* Default : 262114 (256 KB)
                                        Range  : 512 - 16777215 (16 MB) */

    u32 npd_ISCSINodeMaxConnections;
                                     /* Default : 1
                                        Range : 1 to 65535 */
    u32 npd_ISCSINodeDefaultTimeToWait;
                                     /* Default : 2
                                        Range : 0 to 3600 */

    u32 npd_ISCSINodeDefaultTimeToRetain;
                                     /* Default : 20
                                        Range : 0 to 3600 */

    u32 npd_ISCSINodeErrorRecoveryLevel;
                                     /* Default : 0
                                        Range : 0 to 2 */


    u32 npd_Reserved2; /* For 8-byte aligment */

} PACKED NodeParameterData_t;


/* This Structure Covers the Parameters and Information command */

/* Parameters: Some of the Settings will take effect only in the next power
 * cycle
 * Information: Current Running Settings in the Controller
 */

typedef struct micISCSINodeParameterInfoPage
{
    u16 inpp_PageCode; /* MIC_ISCSI_NODE_PARAMETER_PAGE */
    u16 inpp_PageLength;

    u16 inpp_MaxNodes;
    u16 inpp_NodesPresent;

    u16 inpp_NodesFailed;
    u16 inpp_Reserved1;

    u32 inpp_Reserved2; /* For 8-byte aligment */

    NodeParameterData_t inpp_NodeParameter[1];

} PACKED micISCSINodeParameterInfoPage_t;


typedef struct ExtendedNodeParameterData
{
    u16 npd_ISCSINodeID;
    u16 npd_Reserved1;
    u32 npd_NodeFlag; /* Read-Only */
    u8  npd_ISCSINodeName[256];
    u8  npd_ISCSINodeAlias[32]; /* UTF-8 Encoded String */
    u32 npd_ISCSINodeOptionFlags;
    u32 npd_ISCSINodeMaxOutstandingR2T;
                                     /* Default : 1
                                        Range : 1 - 65535 */

    u32 npd_ISCSINodeFirstBurstLength;
                                     /* Default : 65536
                                        Range : 512 - 16777215 (16 MB) */
    u32 npd_ISCSINodeMaxBurstLength;
                                     /* Default : 262114 (256 KB)
                                        Range  : 512 - 16777215 (16 MB) */

    u32 npd_ISCSINodeMaxConnections;
                                     /* Default : 1
                                        Range : 1 to 65535 */
    u32 npd_ISCSINodeDefaultTimeToWait;
                                     /* Default : 2
                                        Range : 0 to 3600 */

    u32 npd_ISCSINodeDefaultTimeToRetain;
                                     /* Default : 20
                                        Range : 0 to 3600 */

    u32 npd_ISCSINodeErrorRecoveryLevel;
                                     /* Default : 0
                                        Range : 0 to 2 */


    u32 npd_Reserved2[2]; /* For 8-byte aligment */

    u32 enpd_MaxAllowedFirstBurstLength;
    u32 enpd_MaxAllowedMaxBurstLength; /* Currently Not Used */
    u32 enpd_MaxAllowedDefaultTimeToWait; /* Currently Not Used */
    u32 enpd_MaxAlloaedDefaultTimeToRetain; /* Currently Not Used */
    u32 enpd_MaxAllowedMaxOutstandingR2T;   /* Currently Not Used */


    u32 enpd_Reserved2[17]; /* Pad for 8-byte Alignment and Future Use  */

} PACKED ExtendedNodeParameterData_t;

#ifndef EXTENDED_PAGE_IMPLEMENTED_BY_FW
#define enpd_MaxAllowedFirstBurstLength     enpd_Reserved2
#define enpd_MaxAllowedMaxBurstLength       enpd_Reserved2
#define enpd_MaxAllowedDefaultTimeToWait       enpd_Reserved2
#define enpd_MaxAlloaedDefaultTimeToRetain       enpd_Reserved2
#define enpd_MaxAllowedMaxOutstandingR2T       enpd_Reserved2
#endif

typedef struct micISCSIExtendedNodeParameterInfoPage
{
    u16 ienpp_PageCode; /* MIC_ISCSI_EXTENDED_NODE_PARAMS_PAGE */
    u16 ienpp_PageLength;

    u16 ienpp_MaxNodes;
    u16 ienpp_NodesPresent;

    u16 ienpp_NodesFailed;
    u16 ienpp_Reserved1;

    u32 ienpp_Reserved2; /* For 8-byte aligment */

    ExtendedNodeParameterData_t ienpp_ExtNodeParameter[1];

} PACKED micISCSIExtendedNodeParameterInfoPage_t;


/* Size: 32 */

typedef struct TargetPortData
{

        u16 tpd_PortID;
        u16 tpd_Reserved1;

        u32 tpd_Reserved2;
    RO  u32 tpd_MaxReceiveDataSegmentLength; /* Bytes */


    RO  u8 tpd_PrimaryHeaderDigestMethod;
    RO  u8 tpd_PrimaryDataDigestMethod;

    RO  u8 tpd_SecondaryHeaderDigestMethod;
    RO  u8 tpd_SecondaryDataDigestMethod;

#define DIGEST_METHOD_NONE                  0x00
#define DIGEST_METHOD_CRC32                 0x01

    RW  u32 tpd_TargetPortalOptionFlags;

#define TGT_PORT_MARKER_ENABLE              0x00000001

    RO  u32 tpd_NoOfActiveSessions;

    RW  u32 tpd_TargetPortalGroupTag;
    RW  u32 tpd_ISCSIReceiveMarker;    /* Not Used */

} PACKED TargetPortData_t;



typedef struct micTargetPortInfo
{
    RO  u16 mtpi_PageCode;
    RO  u16 mtpi_PageLength;

    RO  u16 mtpi_NumPorts;
        u16 mtpi_Reserved;

    TargetPortData_t mtpi_PortInfo[1];


} PACKED micTargetPortInfo_t;


typedef struct micTargetPortSettingsData
{

    RW  u16 mtpsd_ISCSIReceiveMarker;
        u16 mtpsd_PortID;

    RW  u32 mtpsd_TargetPortalOptionFlags;
    RW  u32 mtpsd_TargetPortalGroupTag; /* Default: Port Number */
        u32 mtpsd_MaxReceiveDataSegmentLength;  /*Default: 512 * 1024 Bytes*/

} PACKED TargetPortSettings_t;


typedef struct micTargetPortSettings
{
    RW  u16 mtps_PageCode;
    RW  u16 mtps_PageLength;

    RW  u16 mtps_NumPorts;
        u16 mtps_IsPageSupported;

        TargetPortSettings_t mtps_PortSettings[1];


} PACKED micTargetPortSettings_t;


typedef struct micISCSIPortalInfoData_s
{
    u32 mipid_PortalId;

    u8  mipid_PortalIfType;
#define ISCSI_PORTAL_TYPE_UNKNOWN   0x00
#define ISCSI_PORTAL_TYPE_PHY       0x01
#define ISCSI_PORTAL_TYPE_VLAN      0x02
#define ISCSI_PORTAL_TYPE_TRUNK     0x03

    u16 mipid_InterfaceId;
    u8  mipid_Reserved1;

    u8  mipid_InterfaceName[16];

    u8  mipid_IPAddr[16];
    u32 mipid_TcpPort;

    u32 mipid_Reserved2[5];
} PACKED micISCSIPortalInfoData_t;


typedef struct micISCSIPortalInfo_s
{
    u16 mipi_PageCode;
    u16 mipi_PageLength;

    u16 mipi_ControllerID; /* For Multiple Controller Use */
    u16 mipi_NumPortals;

    u32 mipi_Reserved[4];

    micISCSIPortalInfoData_t mipi_Portals[1];
} PACKED micISCSIPortalInfo_t;


/* All the elements in the following are Read-Only */

/* For the Following Structure all fields are RO */

/* Size 448 */

typedef struct micISCSISessionData
{
    u32 misd_SessionIndex;
    u32 misd_SessionState;

#define SESS_STATE_NO_ACTIVE_CONNECTIONS        0x00000001
#define SESS_STATE_DEV_LOGIN_IN_PROGRESS        0x00000002
#define SESS_STATE_CONNECTED_NO_SESS_ACTIVE     0x00000003
#define SESS_STATE_SESS_ACTIVE                  0x00000004
#define SESS_STATE_SESS_CLOSE_IN_PROGESS        0x00000005
#define SESS_STATE_SESSION_FAILED               0x00000006
#define SESS_STATE_LOGIN_IN_PROGESS             0x00000007
#define SESS_STATE_REQUEST_LOGOUT               0x00000008


    u32 misd_SessionOptions;
#define DEVICE_IS_INITIATOR                 0x00000001
#define DEVICE_IS_TARGET                    0x00000002
#define DEVICE_ACCESS_CONTROL_ENABLE        0x00000004

    u16 misd_PortID;
    u16 misd_Reserved1;


    u8  misd_DeviceIP[16];

    u8  misd_DeviceISCSIName[256];
    u8  misd_DeviceISCSIAlias[32];

    u32 misd_TargetPortalGroup;
    u32 misd_ISCSIInitiatorSourcePort;

    u32 misd_ISCSIOptions; /* Refer to MIC_ISCSI_OPTION_... */


    u8  misd_InitatorSessionID[6];
    u8  misd_Reserved3[2];
    u32 misd_TargetSessionHandle;

    u32 misd_ExecutionThrottle;
    u32 misd_ExecutionCount;

    u32 misd_MaxReceiveDataSegmentLength;
    u32 misd_ReceiveMarkerInterval; /* Not Supported */
    u32 misd_SendMarkerInterval; /* Not Supported */

    u32 misd_FirstBurstLength; /* Bytes */
    u32 misd_MaxBurstLength; /* Bytes */

    u32 misd_DefaultTimeToWait; /* Seconds */
    u32 misd_DefaultTimeToRetain; /* Seconds */

    u32 misd_MaxOutstandingR2T;

    u32 misd_Reserved2[16];

} PACKED micISCSISessionData_t;


typedef struct micISCSISessionInfo
{
    RO  u16 misi_PageCode;
    RO  u16 misi_PageLength;

    RO  u16 misi_NumberOfPorts;
        u16 misi_NumberOfSessions;

        micISCSISessionData_t misi_SessionInfo[1];


} PACKED micISCSISessionInfo_t;

/* Session Parameters is not used currently */
typedef struct SessionParamters
{
    RW  u32 sp_SessionIndex;
    RW  u32 sp_SessionOptions;
    RW  u32 sp_ExecutionThrottle;
        u16 so_PortID;
        u16 sp_Reserved1; /* Padding for 8-byte alignment */

} PACKED SessParams_t;

typedef struct micISCSISessionSettings
{
    RW  u16 miss_PageCode;
    RW  u16 miss_PageLength;
    RW  u32 miss_NumberOfSessions;

    RW  SessParams_t SessionParams[1];

} PACKED miciSCSISessionSettings_t;


/* For the Following Structure All fields are RO or RW based on which command
   the structure is used: For Get Info Commands, the fields are RO and SET
   commands the fields are Write-able*/

/* Size : 32 */ /* Not used Currently */
typedef struct micISCSITcpIpAdvOptions
{

    u16 mita_PortID;

    u8 mita_NagleSupportFlag;
    u8 mita_NagleEnable;

    u8 mita_TimeStampSupportFlag;
    u8 mita_TimeStampEnable;

    u8 mita_PathMTUSupportFlag;
    u8 mita_PathMTUEnable;

    u8 mita_TCPSAckSupportFlag;
    u8 mita_TCPSAckSupportEnable;

    u8 mita_TCPWndSclSupporFlag;
    u8 mita_TCPWndSclEnable;

    u8 mita_FragmentationSupportFlag;
    u8 mita_FragmentationEnable;

    u8 mita_PauseFrameSupportFlag;
    u8 mita_PauseFrameEnable;

    u8 mita_ArpRedirectSupportFlag;
    u8 mita_ArpRedirectEnable;

    u8 mita_TCPTTLSupportFlag;
    u8 mita_TCPTTL;

    u8 mita_TCPMaxSegSizeSupportFlag;
    u8 mita_TCPMaxSegSize; /* Bytes */

    u8 mita_TCPKeepAliveSupportFlag;
    u8 mita_TCPKeepAlive; /* Seconds */

    u8 mita_TCPTransmitTimeStampSupport;
    u8 mita_TCPTransmitTimeStamp;

    u8 mita_TCPReceiveTimeStampSupport;
    u8 mita_TCPReceiveTimeStamp;



    u32 mita_Reserved1;


} PACKED micISCSITcpIpAdvOptions_t;


typedef struct micTcpIpAdvOptionsInfo
{
    RO  u16 mtao_PageLength;
    RO  u16 mtao_PageCode;

    RO  u16 mtao_NumPorts;
    RO  u16 mtao_Reserved1;

    RO  micISCSITcpIpAdvOptions_t mtao_TcpIpOptionsInfo[1];

} PACKED micTcpIpAdvOptionsInfo_t;



typedef struct micTcpIpAdvSettings
{
    RW  u16 mtia_PageLength;
    RW  u16 mtia_PageCode;

    RW  u16 mtia_NumPorts;
    RW  u16 mtia_Reserved1;

    RW  micISCSITcpIpAdvOptions_t mtia_TcpIpOptionsSettings[1];

} PACKED micTcpIpAdvSettings_t;


typedef struct micSLPConfigPage
{

    RW  u32 msc_SLPFlags; /* Default : 0x00000000 */

#define SLP_FLAGS_USE_DA                                0x00000001
#define SLP_FLAGS_ENABLE_SA                             0x00000002
#define SLP_FLAGS_GET_DA_THRU_DHCP                      0x00000004
#define SLP_FLAGS_ENABLE_SLP                            0x00000008

    RW  u8  msc_IPAddrType; /* Refer to Port Mic IP Address Types */
        u8  msc_Reserved1;
        u16 msc_PortID;

    RW  u8  msc_DAIPAddress[16];


}  PACKED micSLPConfigPage_t;

/* Size : 32 */
typedef struct micSLPInfoSettings
{
    RW  u16 msi_PageCode;
    RW  u16 msi_PageLength;
        u16 msi_NumPorts;
        u16 msi_Reserved;
        micSLPConfigPage_t msi_SlpData[1];
}  PACKED micSLPInfoSettings_t;


typedef struct micISNSConfigData
{
    u16 micd_PortID;
    u16 micd_ISNSSrvrPort; /* Default: 3205 */
    u32 micd_ISNSControl; /* Default : 0x00000000 */
#define     MIC_ISNS_ENABLE                     0x00000001
#define     MIC_ISNS_USE_DHCP_FOR_ISNS_IP       0x00000002
#define     MIC_ISNS_ENABLE_ESI                 0x00000004

    u8 micd_ISNSSrvIP[16];

    u8 micd_ISNSSrvFQDN[256];
    u8 micd_Reserved2[32];

}  PACKED micISNSConfigData_t;


typedef struct micISNSInfoSettings
{
    u16 mis_PageCode;
    u16 mis_PageLength;

    u16 mis_NumPorts;
    u16 mis_Reserved1;

    micISNSConfigData_t mis_Config[1];

}  PACKED micISNSInfoSettings_t;


typedef struct micGetNodeList
{
    u8  mgnl_ScsiOpCode;
    u8  mgnl_MicSignature;
    u16 mgnl_MicOpCode;
    u8  mgnl_UniqueCmdId;
    u8  mgnl_LoginKey;
    u16  mgnl_PortID;
    u16 mgnl_Reserved1;
    u16 mgnl_TransferLength;
    u16 mgnl_TranferOffet;
    u8  mgnl_NodeType;

#define MIC_ISCSI_NODE_TYPE_INITIATOR           0x01
#define MIC_ISCSI_NODE_TYPE_TARGET              0x02

    Control_t mgnl_Control;

}PACKED micGetNodeListCmd_t;


typedef struct micNodeData
{
    u8 mnd_NodeName[256];
    u8 mnd_NodeAlias[32];
    u32 mnd_NumPorts;
    u8 mnd_NodeType;
    u8 mnd_Reserved1[3];
    u8 mnd_PortIP[1][16]; /* Variable, based on num ports */

}  PACKED micNodeData_t;

typedef struct micNodeInfo
{
    u32 mni_NumNodes;
    micNodeData_t mni_NodeData[1];

}  PACKED micNodeInfo_t;



typedef struct micAddChapRecordCmd
{
    u8  acrc_ScsiOpCode;
    u8  acrc_MicSignature;
    u16 acrc_MicOpCode;
    u8  acrc_UniqueCmdId;
    u8  acrc_LoginKey;
    u8  acrc_Reserved;
    u8  acrc_NodeID;
    u16 acrc_Reserved1;
    u16 acrc_TransferLength;
    u16 acrc_TranferOffet;
    u8  acrc_Reserved2[1];
    Control_t acrc_Control;

} PACKED micAddChapRecordCmd_t;



#define MIC_CHAP_COUNT_ALL              0xFF

typedef struct micDelChapRecordCmd
{
    u8  dcrc_ScsiOpCode;
    u8  dcrc_MicSignature;
    u16 dcrc_MicOpCode;
    u8  dcrc_UniqueCmdId;
    u8  dcrc_LoginKey;
    u8  dcrc_Reserved;
    u8  dcrc_NodeID;
    u16 dcrc_ChapIndex;
    u16 dcrc_TransferLength;
    u16 dcrc_TranferOffset;
    u8  dcrc_ChapCount;
    Control_t dcrc_Control;

} PACKED micDelChapRecordCmd_t;



typedef struct micSetChapRecordCmd
{
    u8  scrc_ScsiOpCode;
    u8  scrc_MicSignature;
    u16 scrc_MicOpCode;
    u8  scrc_UniqueCmdId;
    u8  scrc_LoginKey;
    u8  scrc_Reserved;
    u8  scrc_NodeID;
    u16 scrc_Reserved1;
    u16 scrc_TransferLength;
    u16 scrc_TransferOffset;
    u8  scrc_ChapCount;
    Control_t scrc_Control;

} PACKED micSetChapRecordCmd_t;


typedef struct micGetChapRecordCmd
{
    u8  gcrc_ScsiOpCode;
    u8  gcrc_MicSignature;
    u16 gcrc_MicOpCode;
    u8  gcrc_UniqueCmdId;
    u8  gcrc_LoginKey;
    u8  gcrc_Reserved;
    u8  gcrc_NodeID;
    u16 gcrc_ChapIndex;
    u16 gcrc_TransferLength;
    u16 gcrc_TransferOffset;
    u8 gcrc_ChapCount;

    Control_t gcrc_Control;

} PACKED micGetChapRecordCmd_t;


/* Size : 368 */

typedef struct CHAPRecord
{
    RW  u16 cr_ChapTblIndex;
        u16 cr_Reserved1;

    RW  u32 cr_ChapSecretLen;
    RW  u8  cr_ChapName[256];
    RW  u8  cr_ChapSecret[100];

    RW  u32 cr_ChapFlags;

#define CHAP_FLAGS_NAME_IS_LOCAL    0x00000000
#define CHAP_FLAGS_NAME_IS_PEER     0x00000001

}  PACKED micCHAPRecord_t;

typedef struct micCHAPConfigurationData
{
    RW  u32 ccd_NumberOfRecords;
        u32 ccd_Reserved[3];

    RW  micCHAPRecord_t ccd_ChapRecord[1];

}  PACKED micChapConfigData_t;




/* Please note this is not a ping using ISCSI PDUs: This is using ICMP through
   ISCSI Ports */

typedef struct micISCSIPortPingCmd
{
    u8  mipp_ScsiOpCode;
    u8  mipp_MicSignature;
    u16 mipp_MicOpCode;
    u8  mipp_UniqueCmdId;
    u8  mipp_LoginKey;
    u8  mipp_Reserved1;
    u8  mipp_PortID;
    u16 mipp_Reserved2;
    u16 mipp_TransferLength;
    u8  mipp_Reserved3[3];
    Control_t mipp_Control;

} PACKED micISCSIPortPingCmd_t;

/* Size is 520: 8-byte aligned */

typedef struct ISCSIPingControlData
{
    RW  u8 ipcd_DestIdentifier;
#define PING_DEST_ID_IP         0x1
#define PING_DEST_ID_DNS        0x2

    u8 ipcd_Reserved[2];

    u8 ipcd_IPAddrType;

    union ip_dns
    {
        RW  u8 ipcd_IPAddress[16];
        RW  u8 ipcd_DomainName[256];
    }ipcd_IPDNS_u;

    RW  u32 ipcd_NumPackets;
    RW  u8  ipcd_Reserved1[256];

}  PACKED micISCSIPingControlData_t;

/* Size : 288 */
typedef struct _MIC_ISCSI_PORT_STATISTICS_
{

    u16 mips_PortID;
    u16 mips_Reserved8;
    u32 mips_Reserved9;
    u64 mips_mactxframecnt;
    /* MAC Transmited Byte Count */
    u64 mips_mactxbytecnt;
    /* MAC Received Frame Count */
    u64 mips_macrxframecnt;
    /* MAC Received Byte Count */
    u64 mips_macrxbytecnt;
    /* MAC CRC Error Count */
    u64 mips_maccrcerrcnt;
    /* MAC Encoding Error Count */
    u64 mips_macencodingerrcnt;

    /* IP related Statistics */

    /* IP Transmitted Packet Count */
    u64 mips_iptxpktcnt;
    /* IP Transmitted Byte Count */
    u64 mips_iptxbytecnt;
    /* IP Transmitted Fragment Count */
    u64 mips_iptxfragcnt;
    /* IP Received Packet Count */
    u64 mips_iprxpktcnt;
    /* IP Received Byte Count */
    u64 mips_iprxbytecnt;
    /* IP Received Fragment Count */
    u64 mips_iprxfragcnt;
    /* IP Received Datagram Reassembly Count */
    u64 mips_ipdgramreasscnt;

    u64 mips_Reserved1;
    /* IP Received Packet Error Count */
    u64  mips_iprxpkterrcnt;

    /* IP Datagram Reassembly Time-out Count */
    u8 mips_ipdgramreasstmocnt;

    /* IP fragement received out-of-order count */
    u8 mips_ipfragrxooocnt;

    /* IP fragement received Overlap count */
    u8 mips_ipfragrxoverlapcnt;
    u8 mips_Reserved2[5];

    /* TCP Related Statistics */

    /* TCP Transmitted Segment Count */
    u64 mips_tcptxsegcnt;
    /* TCP Transmitted Byte Count */
    u64 mips_tcptxbytecnt;
    /* TCP Received Segment Count */
    u64 mips_tcprxsegcnt;
    /* TCP Received Byte Count */
    u64 mips_tcprxbytecnt;

    /* TCP Retransmit Timer Expire Count */
    u8 mips_tcpretrantmrexpcnt;
    /* TCP Persist Timer Expire Count */
    u8 mips_tcpprsttmrexpcnt;
    u8 mips_Reserved3[6];

    /* TCP Received Pure Ack Count */
    u16 mips_tcprxpureackcnt;
    /* TCP Received Duplicate Ack Count */
    u16 mips_tcprxdupackcnt;
    u8 mips_Reserved4[4];

    /* TCP Transmitted Pure Ack Count */
    u16 mips_tcptxpureackcnt;
    /* TCP Transmitted Duplicate Ack Count */
    u16 mips_txdupackcnt;
    u8 mips_Reserved5[4];

    /* TCP Received Segment Out-Of-Order Count */
    u16 mips_tcprxsegooocnt;
    /* TCP Received Segment Error Count */
    u16 mips_tcprxsegerrcnt;
    u8 mips_Reserved6[4];

    /* TCP Received Window Update Count */
    u8 mips_tcprxwndupdcnt;
    /* TCP Received Window Probe Count */
    u8 mips_tcprxwndprbcnt;
    u8 mips_Reserved7[6];

    /* ISCSI Related Statistics */

    /* ISCSI Transmitted PDU Count */
    u64 mips_iscsitxpducnt;
    /* ISCSI Transmitted Data Bytes Count */
    u64 mips_iscsitxdatabytescnt;
    /* ISCSI Received PDU Count */
    u64 mips_iscsirxpducnt;
    /* ISCSI Received Data Bytes Count */
    u64 mips_iscsirxdatabytescnt;
    /* ISCSI I/O Comp Bytes Count */
    u64 mips_iscsiiocompcnt;

    /* ISCSI Unexpected I/O received count */
    u64 mips_unexpiorxcnt;
    /* ISCSI Format Error Count */
    u64 mips_formaterrcnt;
    /* ISCSI Header Digest Error Count */
    u64 mips_hdrdgsterrcnt;
    /* ISCSI Data Digest Error Count */
    u64 mips_datadgsterrcnt;
    /* ISCSI Sequence  Error Count */
    u64 mips_seqerrcnt;


} PACKED micISCSIPortStats_t;

typedef struct _MICS_ISCSI_PORT_STAT_PAGE_
{
    u16 mipsp_PageCode;
    u16 mipsp_PageLength;

    u16 mipsp_NumPorts;
    u16 mipsp_DeviceID; /* For Dual Controller Use */
    micISCSIPortStats_t mipsp_Stats[1];

} PACKED micISCSIPortStatsPage_t;


/* iSCSI Statistics of Silverback Frontend driver
 */

/* size = 584 */
typedef struct micISCSIPortStatsSBData_s
{
    u16 mipsd_PortID;
    u8  mipsd_Reserved0[6];

    /* L2 statistics
     */
    /* number of frames successfully transmitted */
    u64 mipsd_macframetxcnt;
    /* number of frames successfully received */
    u64 mipsd_macframerxcnt;
    /* number of frames with CRC errors */
    u64 mipsd_macframecheckseqerrcnt;
    /* number of frames with alignment errors */
    u64 mipsd_macalignmenterrcnt;
    /* number of octets successfully transmitted */
    u64 mipsd_macocttxcnt;
    /* number of octets successfully received */
    u64 mipsd_macoctrxcnt;
    /* number of frames dropped due to mac errors */
    u64 mipsd_macframelostrcverrcnt;
    /* number of frames received with frame length unequal to mac length */
    u64 mipsd_maclenerrcnt;
    /* number of frames received exceeding maxFrameSize */
    u64 mipsd_macframetoolongerrcnt;
    /* number of invalid symbol events on the carrier */
    u64 mipsd_macsymbolerrcnt;
    /* number of pause frames transmitted */
    u64 mipsd_macpausectrlframetxcnt;
    /* number of pause frames received */
    u64 mipsd_macpausectrlframerxcnt;
    /* total number of bytes received */
    u64 mipsd_macstatsoctcnt;
    /* number of frames dropped due to lack of resources */
    u64 mipsd_macstatsdropeventcnt;
    /* total number of frames received - good and bad */
    u64 mipsd_macstatspkttotalcnt;
    /* number of frames received less than 64 bytes w/good FCS */
    u64 mipsd_macstatsundersizepktcnt;
    /* number of frames received greater than 1518 bytes w/good FCS */
    u64 mipsd_macstatsoversizepktcnt;
    /* number of frames received less than 64 bytes w/bad FCS */
    u64 mipsd_macstatsundersizepkterrcnt;
    /* number of frames received greater than 1518 bytes w/bad FCS */
    u64 mipsd_macstatsoversizepkterrcnt;
    /* number of frames received w/length of 64 bytes */
    u64 mipsd_macstatspkt64octcnt;
    /* number of frames received w/length >= 65 and <= 127 bytes */
    u64 mipsd_macstatspkt65to127octcnt;
    /* number of frames received w/length >= 128 and <= 255 bytes */
    u64 mipsd_macstatspkt128to255Octcnt;
    /* number of frames received w/length >= 256 and <= 511 bytes */
    u64 mipsd_macstatspkt256to511Octcnt;
    /* number of frames received w/length >= 512 and <= 1023 bytes */
    u64 mipsd_macstatpkt512to1023Octcnt;
    /* number of frames received w/length >= 1024 and <= 1518 bytes */
    u64 mipsd_macstatspkt1024toMaxSizeoctcnt;
    /* number of frames received with vlan tag */
    u64 mipsd_macrxvlantaggedframecnt;
    /* number of frames received to unicast addr */
    u64 mipsd_macrxunicastaddrcnt;
    /* number of frames received to multicast addr */
    u64 mipsd_macmulticastframerxcnt;
    /* number of frames received to broadcast addr */
    u64 mipsd_macbroadcastframerxcnt;
    /* number of jumbograms received */
    u64 mipsd_macrxjumboframecnt;
    /* number of frames transmitted w/length of 64 bytes */
    u64 mipsd_mactxpkt64octcnt;
    /* number of frames transmitted w/length >= 65 and <= 127 bytes */
    u64 mipsd_mactxpkt65to127octcnt;
    /* number of frames transmitted w/length >= 128 and <= 255 bytes */
    u64 mipsd_mactxpkt128to255octcnt;
    /* number of frames transmitted w/length >= 256 and <= 511 bytes */
    u64 mipsd_mactxpkt256to511octcnt;
    /* number of frames transmitted w/length >= 512 and <= 1023 bytes */
    u64 mipsd_mactxpkt512to1023octcnt;
    /* number of frames transmitted w/length >= 1024 and <= 1518 bytes */
    u64 mipsd_mactxpkt1024tomaxsizeoctcnt;
    /* number of frames transmitted to unicast addr*/
    u64 mipsd_mactxunicastaddrcnt;
    /* number of frames transmitted to broadcast addr*/
    u64 mipsd_macmulticastframetxcnt;
    /* number of frames transmitted to multicast addr*/
    u64 mipsd_macbroadcastframetxcnt;
    /* number of jumbograms transmitted */
    u64 mipsd_mactxjumboframes;
    /* number of octets transmitted per second */
    u32 mipsd_macocttxperseccnt;
    /* number of octets received per second */
    u32 mipsd_macoctrxperseccnt;

    u32 mipsd_Reserved1[4];


    /* L3-L4 statistics
     */
    /* number of frames received on the interface */
    u64 mipsd_ifpacketcnt;
    /* total number of ip packets received */
    u64 mipsd_ippackettotalcnt;
    /* number of datagrams delivered to upper layer */
    u64 mipsd_ipdatadelivercnt;
    /* total number of tcp packets received */
    u64 mipsd_tcppacketrcvtotalcnt;
    /* total number of udp packets received */
    u64 mipsd_udppackettotalcnt;
    /* number of frames received as multicasts */
    u64 mipsd_ifmulticastrcvframecnt;
    /* number of frames received as broadcasts */
    u64 mipsd_ifbroadcastrcvframecnt;
    /* total number of bytes received */
    u64 mipsd_iftotalbytecnt;
    /* number of frames dropped due to lack of resources */
    u64 mipsd_ipdropframeerrcnt;
    /* number of frames received with input errors */
    u64 mipsd_ifrcverrcnt;
    /* number of frames destined for unsupported protocol */
    u64 mipsd_ifnoprotocolerrcnt;
    /* number of packets too small to contain ip packet */
    u64 mipsd_ippackettoosmallerrcnt;
    /* number of packets with ip version other than 4 or 6 */
    u64 mipsd_ippacketvererrcnt;
    /* number of packets with invalid ip header length */
    u64 mipsd_ippackethdrlenerrcnt;
    /* number of packets with inconsistent ip header and data lengths */
    u64 mipsd_ippackethdrdatalenerrcnt;
    /* number of ip fragments received */
    u64 mipsd_ippacketfragmentrcvcnt;
    /* number of packets with bad checksum */
    u64 mipsd_ippacketchecksumerrcnt;
    /* number of packets with invalid data length */
    u64 mipsd_ippackettooshorterrcnt;
    /* number of packets with unknown or unsupported protocol */
    u64 mipsd_ippacketprotocolerrcnt;
    /* number of packets with unreachable destination */
    u64 mipsd_ippacketforwarderrcnt;
    /* number of tcp packets received that are too short */
    u64 mipsd_tcppacketrcvtooshorterrcnt;
    /* number of packets with invalid tcp header length */
    u64 mipsd_tcppacketrcvhdrlenerrcnt;
    /* number of tcp packets with checksum errors */
    u64 mipsd_tcppacketrcvchecksumerrcnt;
    /* number of udp packets with packet shorter than header */
    u64 mipsd_udppackethdrlenerrcnt;
    /* number of udp packets with data length larger than packet */
    u64 mipsd_udppacketdatalenerrcnt;
    /* number of udp packets with checksum errors */
    u64 mipsd_udppacketchecksumerrcnt;
    /* number of frames with other errors (vlan/ieee802.3/icmp/igmp) */
    u64 mipsd_othererrcnt;

    u32 mipsd_Reserved2[4];

} PACKED micISCSIPortStatsSBData_t;

/* size = 24 + 584 */
typedef struct micISCSIPortStatsSB_s
{
    u16 mipss_PageCode;
    u16 mipss_PageLength;

    u16 mipss_ControllerID; /* For Multiple Controller Use */
    u16 mipss_NumPorts;

    u32 mipss_Reserved[4];

    micISCSIPortStatsSBData_t mipss_Stats[1];
} PACKED micISCSIPortStatsSB_t;


/* size = 64 */
typedef struct micISCSINodeSessStatsData_s
{
    /* Node ID */
    u32 minssd_nodeID;
    /* Session ID */
    u32 minssd_sessionID;

    /* Received command PDU count */
    u32 minssd_rxcmdpducnt;
    /* Transmitted responce PDU count */
    u32 minssd_txrsppducnt;

    /* Received data octet count */
    u64 minssd_rxdataoctcnt;
    /* Transmitted data octet count */
    u64 minssd_txdataoctcnt;

    /* Header digest error count */
    u32 minssd_hdrdgsterrcnt;
    /* Data digest error count */
    u32 minssd_datadgsterrcnt;
    /* Connection timeout error count */
    u32 minssd_conntmoerrcnt;
    /* Format error count */
    u32 minssd_formatErrors;

    u32 minssd_reserved1[4];
} PACKED micISCSINodeSessStatsData_t;


/* size = 24 + 64 */
typedef struct micISCSISessNodeSessStats_s
{
    u16 minss_PageCode;
    u16 minss_PageLength;

    u16 minss_ControllerID; /* For Multiple Controller Use */
    /* Number of Node or Session */
    u16 minss_NumOfStats;

    u32 minss_Reserved[4];

    micISCSINodeSessStatsData_t minss_Stats[1];
} PACKED micISCSINodeSessStats_t;


/* Size : 216 */
typedef struct _MICS_ISCSI_SESS_STATISTICS_
{
    u16 misst_PortID;
    u16 misst_DeviceIndex;
    u32 misst_Reserved1;
    /* Session Received Command PDU Count */
    u32 misst_rxcmdpducnt;
     /* Session Transmitted Response PDU Count */
    u32 misst_txrsppducnt;

    /* Session Transmitted Data Octet Count */
    u64 misst_txdataoctcnt;
    /* Session Received Data Octet Count */
    u64 misst_rxdataoctcnt;


    /* Session Header Digest Error Count */
    u32 misst_sesshdrdgsterrcnt;
    /* Session Data Digest Error Count */
    u32 misst_sessdatadgsterrcnt;
    /* Session Connection Time-out Error Count */
    u32 misst_conntmoerrcnt;
    /* Session Frame Error Count */
    u32 misst_framerrcnt;


    /* Session Transmitted Nop-In PDU Count */
    u32 misst_txnopinpducnt;
    /* Session Transmitted ISCSI Response PDU Count */
    u32 misst_txiscsirsppducnt;
    /* Session Transmitted Task Management Response PDU Count */
    u32 misst_txscsitskmgmtrsppdu;
    /* Session Transmitted Login Response PDU Count */
    u32 misst_txloginrsppducnt;
    /* Session Transmitted Text Response PDU Count */
    u32 misst_txtxtresppducnt;
    /* Session Transmitted SCSI Data Read PDU Count */
    u32 misst_txscsidatardpducnt;
    /* Session Transmitted Logout Response PDU Count */
    u32 misst_txlogoutrsppducnt;
    /* Session Transmitted R2T PDU Count */
    u32 misst_txr2tpducnt;
    /* Session Transmitted Async PDU Count */
    u32 misst_txasyncpducnt;
    /* Session Transmitted Reject PDU Count */
    u32 misst_txrejpducnt;

    /* Session Received Nop-out PDU Count */
    u32 misst_rxnopoutpducnt;
    /* Session Received SCSI Command PDU Count */
    u32 misst_rxscsicmdpducnt;
    /* Session Received Task Management Command PDU Count */
    u32 misst_rxtaskmgmtcmdpducnt;
    /* Session Received Login Command PDU Count */
    u32 misst_rxlogincmdpducnt;
    /* Session Received Text Command PDU Count */
    u32 misst_rxtxtcmdpducnt;
    /* Session Received SCSI Data Write PDU Count */
    u32 misst_rxscsidatawrtpducnt;
    /* Session Received Logout Command PDU Count */
    u32 misst_rxlogoutcmdpducnt;
    /* Session Received SNACK Request PDU Count */
    u32 misst_rxsnackreqpducnt;

    /* Session Transmitted Status Authenticated Count */
    u32 misst_txstsauthcnt;
    /* Session Transmitted Status Move Temp Count */
    u32 misst_txstsmovtempcnt;
    /* Session Transmitted Status Move Perm Count */
    u32 misst_txstsmovpermcnt;
    /* Session Transmitted Status Proxy Count */
    u32 misst_txstsproxycnt;
    /* Session Transmitted Status Authentication Failed Count */
    u32 misst_txstsauthfailcnt;
    /* Session Transmitted Status Forbidden Count */
    u32 misst_txstsforbdncnt;
    /* Session Transmitted Status Not Found Count */
    u32 misst_txstsnotfndcnt;
    /* Session Transmitted Status Remove Count */
    u32 misst_txstsrmvcnt;
    /* Session Transmitted Status Conflict Count */
    u32 misst_txstsconflictcnt;
    /* Session Transmitted Status Target Error Count */
    u32 misst_txststgterrcnt;
    /* Session Transmitted Status Unavailable Count */
    u32 misst_txstsunavailcnt;
    /* Session Transmitted Status Bad Version Count */
    u32 misst_txstsbadvercnt;
    /* Session Transmitted Reject Format Count */
    u32 misst_txrejfmtcnt;
    /* Session Transmitted Reject Header Digest Count */
    u32 misst_txrejhdrdgstcnt;
    /* Session Transmitted Reject Data Digest Count */
    u32 misst_txrejdatadgstcnt;
    /* Session Transmitted Reject Data Snack Count */
    u32 misst_txrejdatasnackcnt;
    /* Session Transmitted Reject Restart Count */
    u32 misst_txrejrestrtcnt;
    /* Session Transmitted Reject Full Feature Count */
    u32 misst_txrejfullfeaturecnt;
    /* Session Transmitted Logout Session Close Count */
    u32 misst_txlosessclosecnt;
    /* Session Transmitted Logout Connection Recovery Count */
    u32 misst_txlocxnrcvrycnt;
    /* Session Transmitted Logout Target Request Count */
    u32 misst_txlotgtreqcnt;
    /* Session Transmitted Async Target Reset Count */
    u32 misst_txasynctgtrstcnt;
    /* Session Transmitted Async Logout Request Count */
    u32 misst_txasyncloreqcnt;
    /* Session Transmitted Async Connection Drop Request Count */
    u32 misst_txasynccxndropcnt;


} PACKED micISCSISessStats_t;

typedef struct _MICS_ISCSI_SESS_STAT_PAGE_
{
    u16 missp_PageCode;
    u16 missp_PageLength;

    u16 missp_NumSessions;
    u16 missp_DeviceID; /* For Dual Controller Use */

    micISCSISessStats_t missp_Stats[1];

} PACKED micISCSISessStatsPage_t;


typedef struct micISCSIiSNAPMicrocodeUpdate
{
    u16 miifu_PageCode;
    u16 miifu_PageLength;

    u16 miifu_ControllerID; /* For Multiple Controller Use */
    u16 miifu_Reserved1;

    u8  miifu_MicrocodeMajorVer;   /* iSNAP FW Major version */
    u8  miifu_MicrocodeMinorVer;   /* iSNAP FW Minor version */
    u16 miifu_MicrocodeBuildVer;   /* iSNAP FW Build version */

    u16 miifu_NumberOfSessions;

    u8  miifu_UpdateOptions;    /* Default: 0 No Option */
    u8  miifu_CleanSessionFlag; /* Default: 0 keep session */

#define ISCSI_LOGIN_REJECT      0x01
#define ISCSI_CONFIG_LOCK       0x02

#define ISCSI_KEEP_SESSION      0x00
#define ISCSI_CLEAN_SESSION     0x01

    u16  miifu_Reserved2[4];
} PACKED micISCSIiSNAPMicrocodeUpdate_t;


#define MIC_NAS_GET_DEVICE_NODE_PAGE    0x01

typedef struct micISCSINASGetDevNodeData
{
    u8  ingdnd_block_name[8]; /* Ex: rca,rcb,rcz,rcaa1*/ /*8 bytes per block device name*/
    u32 ingdnd_BlockIDInfo;   /* Ex: 2,3,5,7 (Corresponding LUN ID)*/
}PACKED micISCSINASGetDevNodeData_t;


typedef struct micISCSINASGetDevNodeHeader
{
    u32 ingdn_num_ld; /* Number LD (Number of device nodes)*/
    micISCSINASGetDevNodeData_t ingdn_DiskInfo[1];
}PACKED micISCSINASGetDevNodeHeader_t;



/************************************************************/
/************************************************************/
/* MIC_LCD_MGT_ID */
/************************************************************/
#define PMIC_LCD_DETECTION             (0x01 | MIC_LCD_MGT_ID)
#define PMIC_LCD_CONFIGURATION         (0x02 | MIC_LCD_MGT_ID)
#define PMIC_LCD_DISPLAY_SCREEN        (0x03 | MIC_LCD_MGT_ID)
#define PMIC_LCD_GET_USER_INPUT_BUTTON (0x04 | MIC_LCD_MGT_ID)

/************************************************************/
/* PMIC_LCD_DETECTION */
/************************************************************/
typedef struct micLcdDetectionCmd
{
    u8          lcdd_ScsiOpCode;
    u8          lcdd_MicSignature;
    u16         lcdd_MicOpCode;
    u8          lcdd_UniqueCmdId;
    u8          lcdd_LoginKey;
    u32         lcdd_Reserved0;
    u16         lcdd_TransferLength;
    u16         lcdd_TransferOffset;
    u8          lcdd_ControllerID;
    Control_t   lcdd_Control;
} PACKED micLcdDetectionCmd_t;

/* Return data structure */
typedef struct micLcdDetectionStatus
{
    u8 ds_ControllerID;  /* Future expandable, always 0 currently */
    u8 ds_PresentStatus; /* LCD Panel Present Status */
    u8 ds_InitStatus;    /* LCD Panel Initialization Status */
    u8 ds_NoOfLines;     /* LCD Panel Display Lines */
    u8 ds_DisplayWidth;  /* LCD Panel Display Width */
    u8 ds_DisplayFlag;
    u8 ds_Reserved[10];  /* Future expansion */
} PACKED micLcdDetectionStatus_t;

/* Bit 0 for Read, LCD panel just display read item */
/* Bit 1 for Write, LCD panel will display write item */
/* Bit 2 for Disable, LCD panel will display "LCD is Disable" only. */
#define LCD_DISPLAY_FLAG_NOT_SUPPORT 0x00
#define LCD_DISPLAY_FLAG_READ        0x01
#define LCD_DISPLAY_FLAG_READ_WRITE  0x03
#define LCD_DISPLAY_FLAG_DISABLE     0x04

/* Possible values for ds_PresentStatus */
#define LCD_PANEL_NOT_PRESENT        0x00
#define LCD_PANEL_PRESENT            0x01

/* Possible values for ds_InitStatus */
#define LCD_PANEL_NOT_INITIALIZED    0x00
#define LCD_PANEL_INITIALIZED        0x01

/************************************************************/
/* PMIC_LCD_CONFIGURATION */
/************************************************************/
typedef struct micLcdConfigurationCmd
{
    u8          lcdc_ScsiOpCode;
    u8          lcdc_MicSignature;
    u16         lcdc_MicOpCode;
    u8          lcdc_UniqueCmdId;
    u8          lcdc_LoginKey;
    u32         lcdc_Reserved0;
    u16         lcdc_TransferLength;
    u16         lcdc_TransferOffset;
    u8          lcdc_ControllerID;
    Control_t   lcdc_Control;
} PACKED micLcdConfigurationCmd_t;

typedef struct micLcdConfigureParameter
{
    u8  cp_ConfigureParameterId;  /* Configuration Parameter ID */
    u8  cp_Reserved1[3];          /* Padding */
    u32 cp_ConfigureParameterVal; /* Parameter Value */
    u8  cp_Reserved2[8];          /* Future expansion */
} PACKED micLcdConfigureParameter_t;

/* Current possible values for cp_ConfigureParameterId */
/* Bit 0 for resetting LCD Panel */
#define LCD_CONFIGURE_PARAMETER_RESET_PANEL          0x01
/* Bit 1 for decreasing LCD Panel brightness */
#define LCD_CONFIGURE_PARAMETER_DECREASE_BRIGHTNESS  0x02
#define LCD_CONFIGURE_PARAMETER_SET_DISPLAY_FLAG     0x04

/************************************************************/
/* PMIC_LCD_DISPLAY_SCREEN */
/************************************************************/
typedef struct micLcdScreenDisplayCmd
{
    u8          sd_ScsiOpCode;
    u8          sd_MicSignature;
    u16         sd_MicOpCode;
    u8          sd_UniqueCmdId;
    u8          sd_LoginKey;
    u32         sd_Reserved0;
    u16         sd_TransferLength;
    u16         sd_TransferOffset;
    u8          sd_ControllerID;
    Control_t   sd_Control;
} PACKED micLcdDisplayScreenCmd_t;

typedef struct micLcdCharType
{
    u16 ct_Character;          /* Unicode Character*/
    u16 ct_CharacterAttribute; /* Character Properties */
    u8  ct_Reserved[4];        /* Reserved and padding */
} PACKED micLcdCharType_t;

/* Current possible values for ct_CharacterAttribute */
/* Bit 0 for special pattern */
#define LCD_DISPLAY_SPECIAL_PATTERN     0x01

/* Current possible values for ct_Character if bit 0 for ct_CharacterAttribute is set to 1 */
#define LCD_DISPLAY_UP_ARROW            0x10
#define LCD_DISPLAY_UP_DOWN_ARROW       0x11
#define LCD_DISPLAY_DOWN_ARROW          0x12
#define LCD_DISPLAY_CIRCLE_SYMBOL       0x23
#define LCD_DISPLAY_RIGHT_ARROW         0x32

typedef struct micLcdDisplayContents
{
    u8  dc_DisplayLen;       /* Length of the displayed string */
    u8  dc_CursorPosition;   /* Cursor Display Position if Cursor enable*/
    u16 dc_DisplayAttribute; /* Display Properties */
    u8  dc_Reserved[4];      /* Reserved and padding */
    micLcdCharType_t dc_DisplayContents[1]; /* Contents of the displayed  string*/
} PACKED micLcdDisplayContents_t;

/* Current possible values for dc_DisplayAttribute */
/* Bit 0 and Bit 1 for displayed Line number */
#define LCD_DISPLAY_ATTRIBUTE_LINE1            0x01
#define LCD_DISPLAY_ATTRIBUTE_LINE2            0x02
/* Bit 2 and Bit 3 for Cursor setting */
#define LCD_DISPLAY_ATTRIBUTE_CURSOR_ENABLE    0x04
#define LCD_DISPLAY_ATTRIBUTE_CURSOR_BLINK     0x08

/************************************************************/
/* PMIC_LCD_GET_USER_INPUT_BUTTON */
/************************************************************/
typedef struct micLcdGetUserInputButtonCmd
{
    u8          guib_ScsiOpCode;
    u8          guib_MicSignature;
    u16         guib_MicOpCode;
    u8          guib_UniqueCmdId;
    u8          guib_LoginKey;
    u32         guib_Reserved0;
    u16         guib_TransferLength;
    u16         guib_TransferOffset;
    u8          guib_ControllerID;
    Control_t   guib_Control;
} PACKED micLcdGetUserInputButtonCmd_t;

/* Return data structure */
typedef struct micLcdUserInputButton
{
    u8 uib_ControllerID;   /* Future expandable, always 0 currently */
    u8 uib_Button;         /* User Input button */
    u8 uib_SettingUpdated;
    u8 uib_Reserved[5];    /* Future expansion */
} PACKED micLcdUserInputButton_t;

/* Current possible values for uib_Button */
#define LCD_IOPORT_BUTTON1        0x01
#define LCD_IOPORT_BUTTON2        0x02
#define LCD_IOPORT_BUTTON3        0x03
#define LCD_IOPORT_BUTTON4        0x04
/************************************************************/


/* iSCSI Link Layer Services
 */

typedef struct micVLANInfoSettingsData
{
    /* User defined index
     */
    u32   mvisd_Index;          /* Min:0-Max:31 */
#define ISCSI_VLAN_IF_INVALID_ID       0xFFFFFFFF
    u32   mvisd_Reserved0;    /* Reserved and 8-byte align */

    u8    mvisd_Name[16];       /* VLAN Name */

    /* VLAN config-info
     */
    u32   mvisd_VlanTag;        /* VLAN ID. dflt:2 / Min:2 / Max:4095 */
    u32   mvisd_Priority;       /* dflt:0 / Min:0 / Max:7 */

    u32   mvisd_InterfaceId;    /* Interface ID - dflt:0*/
    u32   mvisd_InterfaceType;  /* Interface Type - dflt:1*/
#define ISCSI_VLAN_IF_NONE             0
#define ISCSI_VLAN_IF_TYPE_PHY         1
#define ISCSI_VLAN_IF_TYPE_TRUNK       2

    /* Portal associated to the VLAN
     */
    u8    mvisd_IpAddr[16];     /* Ip Address */
    u8    mvisd_SubnetMask[16]; /* NetMask */
    u8    mvisd_GatewayIP[16];  /* GateWay Ip */
    u32   mvisd_TcpPortNumber;  /* TCP Port for iSCSI Portal dflt:3260*/
    u32   mvisd_MaxTxUnit;      /* dflt:1500 / Min:1500 / MAX: 9000*/

    u32   mvisd_Reserved1[6];    /* Reserved and 8-byte align */
} PACKED micVLANInfoSettingsData_t;


typedef struct micVLANInfoSettings
{
    u16   mvis_PageCode;      /* MIC_ISCSI_LLS_VLAN_PAGE */
    u16   mvis_PageLength;

    u16   mvis_ControllerID;
    u8    mvis_Reserved0[2];  /* padding */

    u16   mvis_VlanCount;     /* dflt:0 */
    u16   mvis_MaxVlans;
#define ISCSI_VLAN_MAX_COUNT           32

    u32   mvis_Reserved[5];   /* Reserved and 8-byte align */

    micVLANInfoSettingsData_t   mvis_VlanData[1]; /* Data buffer */
} PACKED micVLANInfoSettings_t;


typedef struct micLinkAggrInfoSettingsData
{
    u32   mlaisd_TrunkID;        /* User defined index. Min:1-Max:32 */
    u32   mlaisd_MasterPort;     /* Master physical port dflt:0 */
    u32   mlaisd_SlavePortList;  /* Bitmap for Max 32 phy Ports - dflt:0 */

    u32   mlaisd_Reserved[5];    /* Reserved and 8-byte align */
} PACKED micLinkAggrInfoSettingsData_t;


typedef struct micLinkAggrInfoSettings
{
    u16   mlais_PageCode;        /* MIC_ISCSI_LLS_LINK_AGGR_PAGE */
    u16   mlais_PageLength;

    u16   mlais_ControllerID;
    u8    mlais_Reserved0[2];    /* padding */

    u16   mlais_LagCount;        /* dflt:0 */
    u16   mlais_MaxLags;
#define ISCSI_LINK_AGGR_MAX_COUNT      32

    u32   mlais_Reserved[5];     /* Reserved and 8-byte align */

    micLinkAggrInfoSettingsData_t   mlais_LinkAggrData[1];  /* buffer */
} PACKED micLinkAggrInfoSettings_t;


typedef struct micLinkLayerServiceReadCmd
{
    u8        llsrc_ScsiOpCode;
    u8        llsrc_MicSignature;
    u16       llsrc_MicOpCode;
    u8        llsrc_UniqueCmdId;
    u8        llsrc_LoginKey;
    u8        llsrc_IfID;         /*ISCSI Link Layer Servce Interface ID*/
    u8        llsrc_PageCode;
    u16       llsrc_Reserved1;
    u16       llsrc_TransferLength;
    u16       llsrc_TransferOffset;
    u8        llsrc_Reserved2;
    Control_t llsrc_Control;
}PACKED micLLSReadCmd_t;


typedef struct micLinkLayerServiceWriteCmd
{
    u8        llswc_ScsiOpCode;
    u8        llswc_MicSignature;
    u16       llswc_MicOpCode;
    u8        llswc_ConfigLock;
    u8        llswc_LoginKey;
    u8        llswc_IfID;       /*ISCSI Link Layer Servce Interface ID*/
    u8        llswc_PageCode;
    u16       llswc_Reserved1;
    u16       llswc_TransferLength;
    u16       llswc_TransferOffset;
    u8        llswc_Reserved2;
    Control_t llswc_Control;
} PACKED micLLSWriteCmd_t;
#define PMIC_GET_ENCLOSURE_INFORMATION       (0x00 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_ENCLOSURE_STATUS            (0x01 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_LOCATE_ENCLOSURE_HARD_DISK      (0x02 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_ENCLOSURE_SETTINGS          (0x03 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SET_ENCLOSURE_SETTINGS          (0x04 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_ENC_DO_BATTERY_RECONDITIONING   (0x05 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_FRU_INFORMATION             (0x06 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_BATTERY_INFO                (0x07 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SET_FAN_SPEED                   (0x08 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_LOCATE_STOP                     (0x0C |MIC_ENCLOSURE_MGT_ID)
#define PMIC_LOCATE_ARRAY_IN_ENCLOSURE       (0x0D |MIC_ENCLOSURE_MGT_ID)
#define PMIC_LOCATE_LOGDRV_IN_ENCLOSURE      (0x0E |MIC_ENCLOSURE_MGT_ID)
#define PMIC_LOCATE_ENCLOSURE                (0x0F |MIC_ENCLOSURE_MGT_ID)
#define PMIC_LOCATE_FRU                      (0x10 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SIMUALTE_ENC_FAULT              (0x11 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_CLEAR_DDF_ON_PD                 (0x12 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_CONTROL_FRU_LED                 (0x13 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_CONTROL_DISK_FRU_LED            (0x14 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_DISCHARGE_BATTERY               (0x15 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_CHARGE_BATTERY                  (0x16 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_BATTERY_CAPACITY            (0x17 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SHUTDOWN_BATTERY                (0x18 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_RESERVED_FOR_ENC_CMD_START      (0x09 |MIC_ENCLOSURE_MGT_ID)

#define PMIC_GET_TERMINAL_SENSE_SIGNAL       (0x20 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SET_TERMINAL_SENSE_SIGNAL       (0x21 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_TERMINAL_ALARM_SIGNAL       (0x22 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SET_TERMINAL_ALARM_SIGNAL       (0x23 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_UART_MODE                   (0x24 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SET_UART_MODE                   (0x25 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_ENC_COMPONENT               (0x26 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_SET_ENC_COMPONENT               (0x27 |MIC_ENCLOSURE_MGT_ID)
#if defined(VESSAPP) || defined(WINTEST)
#define PMIC_GET_FRU_LED                     (0x28 |MIC_ENCLOSURE_MGT_ID)
#define PMIC_GET_DISK_LED                    (0x29 |MIC_ENCLOSURE_MGT_ID)
#endif

#define PMIC_RESERVED_FOR_ENC_CMD_END        (0xFF |MIC_ENCLOSURE_MGT_ID)


/* Error Status from Enclosure management */
#define PMIC_SEP_STS_NOT_PRESENT            (MICS_MODULE_SPECIFIC_ERROR_START + 0x01)
#define PMIC_SEP_STS_MALFUNCTIONING         (MICS_MODULE_SPECIFIC_ERROR_START + 0x02)
#define PMIC_SEP_STS_ALLOC_MEMORY_FAILED    (MICS_MODULE_SPECIFIC_ERROR_START + 0x03)
#define PMIC_SEP_STS_RETURNED_ERROR         (MICS_MODULE_SPECIFIC_ERROR_START + 0x04)
#define PMIC_SEP_STS_UNKNOWN_CMD            (MICS_MODULE_SPECIFIC_ERROR_START + 0x05)
#define PMIC_INVALID_PARAMETER              (MICS_MODULE_SPECIFIC_ERROR_START + 0x06)
#define PMIC_SEP_STS_CMD_NOT_SUPPORTED     (MICS_MODULE_SPECIFIC_ERROR_START + 0x07)

typedef struct MicEnclosureGenericCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Controller;       /* controller number */
    u8                  enc_Channel;          /* channel Number or enc_TimeInMinutes for locate PD*/
    u16                 enc_TargetId;         /* Target number need mechanism for flat ID if flatId,ignore other 2 fields*/
    u16                 enc_TransferLength;   /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_TransferOffset;    /* Note Transfer offset should be here */
    u8                  enc_EnclosureId;
    u8                  enc_Control;
}  PACKED micEncCmd_t;// __attribute__ ((packed));


typedef struct micEnclosureGetSetSettings
{
   u8  mgss_TempThresholdWarning;
   u8  mgss_TempThresholdCritical;
   u8  mgss_EnclosureFrequency;  //monitoring period in seconds
   u8  mgss_NumOfDrivesToSpin;
   u8  mgss_TimeBetweenSpinUp;
   u8  mgss_CtrlTempThresholdWarning;
   u8  mgss_CtrlTempThresholdCritical;
   u16 mgss_Reserved;
}PACKED MGSS_t;

typedef struct MicEnclosureSetCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Controller;       /* controller number */
    u8                  enc_Channel;          /* channel Number */
    u16                 enc_TargetId;         /* Target number need mechanism for flat ID if flatId,ignore other 2 fields*/
    u16                 enc_TransferLength;   /* size of Data + buffer header, */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
}  PACKED micEncSetCmd_t;// __attribute__ ((packed));

#define FRU_TYPE_MB                 0    /* mother board, posiible numbers only 0,1*/
#define FRU_TYPE_SEP                1
#define FRU_TYPE_BBU                2
#define FRU_TYPE_FAN                3
#define FRU_TYPE_PSU                4
#define FRU_TYPE_BP                 5
#define FRU_TYPE_DAUGHTERCARD       6

typedef struct MicEnclolsureGetSetFRUCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_FruType;       /* FRU TYPE number */
    u8                  enc_FruNum;          /* FRU  Number */
    u16                 enc_Reserved;         /* */
    u16                 enc_TransferLength;   /* size of Data  */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
}  PACKED micEncGSFRUCmd_t;// __attribute__ ((packed));

#define ENC_FAN_SPEED_FULL                      4
#define ENC_FAN_SPEED_HALF                      2
#define ENC_FAN_SPEED_OFF                       0

typedef struct MicEnclosureSetFanSpeedCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Reserved1;       /* controller number */
    u8                  enc_FanId;          /* channel Number */
    u8                  enc_FanSpeed;         /* Full, half permitted*/
    u8                  enc_Reserved2;
    u16                 enc_TransferLength;   /* size of Data + buffer header, */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
}  PACKED micEncSetFSCmd_t;// __attribute__ ((packed));

/************************************************************/
/* PMIC_GET_ENCLOSURE_SETTINGS, PMIC_SET_ENCLOSURE_SETTINGS */
/************************************************************/
/* Element Type (base on standard SES element define) */
#define ENC_ELEMENT_TEMPERATURE_THRESHOLD   0x4     /* Temperature threshold for both Critical and Warning */
#define ENC_ELEMENT_ALL                     0xFF    /* All Element (vendor specific definition) */

#if defined(CX20Y) || defined(VESSAPP) || defined(WINTEST)/* COOLER_MODE */
#define ENC_ELEMENT_GLOBAL              0xFE /* Enclosure global settings */
/*
** enclosure global element is vendor defined, used for promise defined
** enclosure settings. this global element cannot be set if software specified
** ENC_ELEMENT_ALL, software needs to fill following fields:
**
**      mesh_ElementType    = ENC_ELEMENT_GLOBAL
**      mesh_ElementCnt     = 1
**      mesh_SettingByteCnt = 0
**      mesh_CoolerMode     = 0 (or 1)
**      mesh_reserved [3]
**      (total 8 bytes)
*/
#endif

typedef struct MicEnclosureGetSetSettingCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_ElementType;        /* Element Type to get or to set */
    u8                  enc_Reserved1;
    u16                 enc_Reserved2;
    u16                 enc_TransferLength;     /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_Reserved3;
    u8                  enc_EnclosureId ;       /* Enclosure Flat Id */
    u8                  enc_Control;
}  PACKED micEncGSSettingCmd_t;// __attribute__ ((packed));

typedef struct MicEnclosureLocateArrayCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Controller;       /* controller number */
    u8                  enc_TimeInMinutes;          /* channel Number */
    u16                 enc_ArrayId;         /* Array flat id*/
    u16                 enc_TransferLength;   /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_TransferOffset;    /* Note Transfer offset should be here */
    u8                  enc_EnclosureId ;   /* array flat Id */
    u8                  enc_Control;
}  PACKED micLocateArrayCmd_t;// __attribute__ ((packed));

typedef struct MicEnclosureLocateLogDrvCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Controller;       /* controller number */
    u8                  enc_TimeInMinutes;          /* channel Number */
    u16                 enc_LDId;             /* Logical Drive  flat id*/
    u16                 enc_TransferLength;   /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_TransferOffset;    /* Note Transfer offset should be here */
    u8                  enc_EnclosureId ;   /* array flat Id */
    u8                  enc_Control;
}  PACKED micLocateLDCmd_t;// __attribute__ ((packed));


typedef struct MicEnclosureLocateFru
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_FruType;       /* controller number */
    u8                  enc_TimeInMinutes;          /* channel Number */
    u16                 enc_FruId;             /* Logical Drive  flat id*/
    u16                 enc_TransferLength;   /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_TransferOffset;    /* Note Transfer offset should be here */
    u8                  enc_EnclosureId ;   /* array flat Id */
    u8                  enc_Control;
}  PACKED micLocateEnclosureFRUCmd_t;// __attribute__ ((packed));



/* mic enclosure respone commands */

/*****************************************************************/
/* Cmd: PMIC_GET_ENCLOSURE_SETTINGS, PMIC_SET_ENCLOSURE_SETTINGS */
/*****************************************************************/
/* Element Type (base on standard SES element define) */
#define ENC_ELEMENT_TEMP_SENSOR         0x04 /* Temperature threshold for both Critical and Warning */
#define ENC_ELEMENT_ALL                 0xFF /* All Element (vendor specific definition) */

typedef struct micEncTemperatureThreshold
{
    u8  mett_Warning;
    u8  mett_Critical;
} PACKED METT_t;

typedef struct micEncGetSetSettingResponseHeader
{
    /* header */
    u8  mesh_ElementType;
    u8  mesh_ElementCnt;
    u16 mesh_SettingByteCnt;    /* total element page length not including the 8byte header */
                                /* the byte cnt only for the current element not the following element */

#if defined(CX20Y) || defined(VESSAPP) || defined(WINTEST) /* COOLER_MODE */
    /* VessRAID only, used for cooler mode enable/disable */
    u8  mesh_CoolerMode;
    u8  mesh_reserved[3];
#else
    u8  mesh_reserved[4];
#endif

    union {
        METT_t  TempThreshold;
    } PACKED setting;
}  PACKED MESH_t;   /* Mic Enclosure Setting Header */

/* Subsystem */
#define ENC_TYPE_SONOMA           0x0
#define ENC_TYPE_ISLAVISTA        0x1
#define ENC_TYPE_2U12BAY          0x2
#define ENC_TYPE_2U8BAY           0x3
#define ENC_TYPE_J300S            0x4       /* J300S BP with 3 bit id: 110b */
#define ENC_TYPE_MX10X_2U12BAY    0x5
#define ENC_TYPE_MX10X_2U8BAY     0x6
#define ENC_TYPE_E3X0_2U12BAY     0x7       /* Eclass BP with 4 bit id: 0111b */
#define ENC_TYPE_E3X0_3U16BAY     0x8       /* Eclass BP with 4 bit id: 1000b */
#define ENC_TYPE_MX10X_3U16BAY    0x9
#define ENC_TYPE_MX10X_3U16BAY_G2 0xA       /* Generation 2 backplane of MX10X */
#define ENC_TYPE_CX20Y_1U4BAY     0xB
#define ENC_TYPE_CX20Y_2U8BAY_TOWER         ENC_TYPE_2U8BAY
#define ENC_TYPE_CX20Y_2U8BAY               ENC_TYPE_MX10X_2U8BAY
#define ENC_TYPE_CX20Y_2U12BAY              ENC_TYPE_MX10X_2U12BAY
#define ENC_TYPE_CX20Y_3U16BAY              ENC_TYPE_MX10X_3U16BAY_G2
#define ENC_TYPE_CX20Y_4U24BAY              ENC_TYPE_MX10X_3U16BAY

/* single psu */
#define ENC_TYPE_VR1000Y_1U4BAY_S           (0x00 | ENC_TYPE_CX20Y_1U4BAY)
#define ENC_TYPE_VR1000Y_2U8BAY_TOWER_S     (0x00 | ENC_TYPE_2U8BAY)
#define ENC_TYPE_VR1000Y_2U8BAY_S           (0x00 | ENC_TYPE_MX10X_2U8BAY)
#define ENC_TYPE_VR1000Y_2U12BAY_S          (0x00 | ENC_TYPE_MX10X_2U12BAY)
#define ENC_TYPE_VR1000Y_3U16BAY_S          (0x00 | ENC_TYPE_MX10X_3U16BAY_G2)
#define ENC_TYPE_VR1000Y_4U24BAY_S          (0x00 | ENC_TYPE_MX10X_3U16BAY)

/* redundant psu */
#define ENC_TYPE_VR1000Y_2U8BAY_TOWER_R     (0x10 | ENC_TYPE_2U8BAY)
#define ENC_TYPE_VR1000Y_2U8BAY_R           (0x10 | ENC_TYPE_MX10X_2U8BAY)
#define ENC_TYPE_VR1000Y_2U12BAY_R          (0x10 | ENC_TYPE_MX10X_2U12BAY)
#define ENC_TYPE_VR1000Y_3U16BAY_R          (0x10 | ENC_TYPE_MX10X_3U16BAY_G2)
#define ENC_TYPE_VR1000Y_4U24BAY_R          (0x10 | ENC_TYPE_MX10X_3U16BAY)

/* redundant_green psu */
#define ENC_TYPE_VR1000Y_2U8BAY_TOWER_R_G   (0x20 | ENC_TYPE_2U8BAY)
#define ENC_TYPE_VR1000Y_2U8BAY_R_G         (0x20 | ENC_TYPE_MX10X_2U8BAY)
#define ENC_TYPE_VR1000Y_2U12BAY_R_G        (0x20 | ENC_TYPE_MX10X_2U12BAY)
#define ENC_TYPE_VR1000Y_3U16BAY_R_G        (0x20 | ENC_TYPE_MX10X_3U16BAY_G2)
#define ENC_TYPE_VR1000Y_4U24BAY_R_G        (0x20 | ENC_TYPE_MX10X_3U16BAY)

/* SmartStor */
#define ENC_TYPE_SMARTSTOR_1U2BAY_TOWER     0x40 /* NS2700 */
#define ENC_TYPE_SMARTSTOR_1U4BAY_TOWER     0x41 /* NS4700 */
#define ENC_TYPE_SMARTSTOR_2U6BAY_TOWER     0x42 /* NS6700 */
#define ENC_TYPE_SMARTSTOR_2U8BAY_TOWER     0x43 /* NS8700 */
#define ENC_TYPE_SMARTSTOR_1U4BAY           0x44 /* for SmartStor rackmount product */
#define ENC_TYPE_SMARTSTOR_1U4BAY_IM        0x45 /* for SmartStor rackmount product (Imation) */

/* VessApp */
/*split a id bench for VESS series*/
#define ENC_TYPE_VESS_2U6BAY  0x50 
#define ENC_TYPE_VESS_2U12BAY 0x51 
#define ENC_TYPE_VESS_3U16BAY 0x52
#define ENC_TYPE_VESS_4U24BAY 0x53 


/* HBA */
#define ENC_TYPE_3RD_PARTY        0x7F
#define ENC_TYPE_SUPERSWAP_4100   0x80
#define ENC_TYPE_SUPERSWAP_4600   0x81
#define ENC_TYPE_SUPERSWAP_1600   0x82    /*for SS1600*/

/* Mask off now, plan to be removed
**************************************
#define ENC_TYPE_SHASTA_8300      0x90
#define ENC_TYPE_SHASTA_8350      0x98
#define ENC_TYPE_YOSEMITE_8400    0xA0
#define ENC_TYPE_YOSEMITE_8404    0xA1
#define ENC_TYPE_YOSEMITE_8408    0xA2
#define ENC_TYPE_YOSEMITE_8450    0xA8
#define ENC_TYPE_YOSEMITE_8454    0xA9
#define ENC_TYPE_YOSEMITE_8458    0xAA

#define ENC_TYPE_YOSEMITE_865x    0xB0
#define ENC_TYPE_YOSEMITE_4650    0xB1
#define ENC_TYPE_YOSEMITE_8650    0xB2
#define ENC_TYPE_YOSEMITE_8654    0xB3
#define ENC_TYPE_YOSEMITE_8650EL  0xB4
#define ENC_TYPE_YOSEMITE_4650EL  0xB5
#define ENC_TYPE_YOSEMITE_8650M   0xB6
*/

#define ENC_TYPE_YOSEMITE_VIRTUAL 0xC0

#define ENC_TYPE_NEC_AMI_918      0xE0
#define ENC_TYPE_ACER_SAS_BP      0xE1  /*for ACER SAS BP*/
#define ENC_TYPE_GW_1U_SGPIO      0xE2
#define ENC_TYPE_GW_2U_SES        0xE3


typedef struct micPromiseEncVSData
{
    u8 mpvs_NumOfVoltageSensors;
    u8 mpvs_NumOfBatteries;
    u8 mpvs_SepFwVerSion[4]; /*x.xx format in ASCII */
    u8 mpvs_EnclosureType;  // see above  for macros
    u8 mpvs_EncId;          // enclosure id for current data
    u8 mpvs_NumOfMB;        // max number of controllers for this enc
    u8 mpvs_NumOfSep;       // max num of SEP
    u8 mpvs_NumOfCUs;
    u8 mpvs_FRUCapability;  // bit0:Controller, bit1:Enc, bit2:PSU, bit3:CU (1:support locate, 0: not support)
    u8 mpvs_reserved1[4];   // CBAY already used this

    // below is the extend structure area.
    u8 mpvs_StructRev;      // structure revision #, current is 0
    u8 mpvs_reserved2[3];   // for future use
    u16 mpvs_CtrlType;      // 16 bits Controller Type
    u16 mpvs_FrontEndInterfaceType;        // 16 bits Front End Type
    u8 mpvs_PSUType;        // For PSU type use
    u8 mpvs_reserved3[39];  // reserved to a total of 64 byte structure
}PACKED MPVS_t;

typedef struct micEncInfoResponse
{
    u8 mei_NumOfFans;
    u8 mei_NumOfPsus;
    u8 mei_NumOfHDSlots;
    u8 mei_DoorLockSts;
    u8 mei_NumOfTempSensors;
    u8 mei_NumOfAudibleAlarms;
    u8 mei_ThermostatInfo;
    u8 mei_NumOfBytesToFollow; // this byte will be 64 bytes after the extension
    MPVS_t mei_VendorUniqueData;
}PACKED MEI_t;

#if 0
typedef struct micEnclosureStsResponse
{
    u8 *mes_FanSts;
    u8 *mes_PsuSts;
    u8 *mes_SlotIds;
    u8 mes_DoorLockSts; //mandatory
    u8 mes_SpeakerSts;  //mandatory
    u8 *mes_ThermalSensorSts;
    u8 mes_TempFlags1;  // mandatory single bytes
    u8 mes_TempFlags2; // mandatory single bytes
    u8 *mes_VoltageSensor;
    u8 *mes_FanSpeed; /*in RPM (1350 *1000)/(fanspeed * 4) = 337500/fanspeed */
    u8  mes_TemperatureThresholdWarning;
    u8  mes_TemperatureThresholdCritical;
    u8 mes_PollingInterval;
    u8 mes_ControllerTemperature;
    u8 mes_CtrlTempWarning;
    u8 mes_CtrlCriticalTemp;
}  PACKED MES_t;

#endif
/* define for mbi_BatteryType */
#define BATTERY_TYPE_UNKNOWN    0xff    /* board/battery mismatch or unidentified type */
#define BATTERY_TYPE_TWO_CELL   0x2     /* 2 cell */
#define BATTERY_TYPE_FOUR_CELL  0x4     /* 4 cell */
/*for BBU PlusII - 1 cell 1100mAh*/
#define BATTERY_TYPE_BBU_PLUSII_ONE_CELL   0x11     /* 1 cell : 1100mAh*/

typedef struct micBatteryInfoResponse
{
   u16  mbi_SerialNum;
   u16  mbi_MfgDate;
   u8   mbi_MfgName[12];
   u8   mbi_DeviceName[8];
   u8   mbi_DeviceChemistry[6];
   u16  mbi_SpfcnInfo;
   u16  mbi_TempThreshholdDischarge;
   u16  mbi_TempthresholdCharge;
   u16  mbi_BatteryTemperature; //current temperature of the cell
   u16  mbi_CycleCount;
   u16  mbi_RemainingCapacity; // % of full capacity
   u16  mbi_BatteryVoltage;  //in mV
   u16  mbi_BatteryCurrent; //in mA
   u8   mbi_BatteryState;   // one of the below defines

   u8   mbi_BatteryCellType;
//   u8   mbi_reserved;

}PACKED MBI_t;

#define BATTERY_CHARGING                0x00
#define BATTERY_DISCHARGING             0x01
#define BATTERY_FULLY_CHARGED           0x02
#define BATTERY_MALFUNCTION             0x03
#define BATTERY_RECONDITION             0x04
#define BATTERY_SHUTDOWN                0x05

#if defined(VESSAPP) || defined(_WINDRIVER)
#define OEM_MODEL_SIG_DISK_LOCK         0x0000
#define OEM_MODEL_SIG_DISK_LESS         0x0001

/*
** other model signature should be defined as:
** #define OEM_MODEL_SIG_XXXX           0x0002
** #define OEM_MODEL_SIG_YYYY           0x0004
** #define OEM_MODEL_SIG_ZZZZ           0x0008
** etc.
*/

typedef struct _mfru_modelsig
{
    u16  disklock:1;            /* disk lock/unlock */
#define MODSIG_DISK_LOCK        0x0
#define MODSIG_DISK_UNLOCK      0x1

    u16  frontend:2;            /* front-end type */
#define MODSIG_FED_SCSI         0x0
#define MODSIG_FED_ISCSI        0x1
#define MODSIG_FED_NAS          0x2

    u16  os_type:1;             /* os type */
#define MODSIG_OS_LINUX         0x0
#define MODSIG_OS_WINDOWS       0x1

    u16  nsr_capacity:4;        /* nsr capacity limitation */
#define MODSIG_CAP_0TB          0x0
#define MODSIG_CAP_1TB          0x1
#define MODSIG_CAP_2TB          0x2
#define MODSIG_CAP_4TB          0x3
#define MODSIG_CAP_8TB          0x4
#define MODSIG_CAP_12TB         0x5
#define MODSIG_CAP_ANY          0xf  /* non-nsr product has no limitation */

    u16  product_id:4;          /* additional product id */
#define MODSIG_APID_NSR_NONE    0x1  /* nsr-500: none */
#define MODSIG_APID_NSR_AEB     0x2  /* nsr-510: analog encoder board */
#define MODSIG_APID_NSR_DAB     0x3  /* nsr-520: display accelerator board */
#define MODSIG_APID_NSR_AEB_DAB 0x4  /* nsr-550: both of AEB & DAB */
/*
**      MODSIG_APID_XXX         0x5    future additional product id (5~f)
*/

    u16  reserved:4;            /* reserved */
}
  PACKED MFRU_ModelSig_t;
#endif

/* this strcuture is still evolving and is tightly tied to Promise VPD structur efinition . However the maximum size can be only 255 bytes */
typedef struct micEnclosureFruInfo
{
/* Generic info */
  u8  mfru_Signature[2];
  u16 mfru_GenericCheckSum;
  u8  mfru_BoardId;
#if defined(VESSAPP) || defined(_WINDRIVER)
  u8  mfru_Reserved;
  u16 mfru_OEMModelSignature; /* see MFRU_ModelSig_t for detail */
#else
  u8  mfru_Reserved [3];
#endif
  u8  mfru_OEMName[16];
  u8  mfru_OEMModel[16];
  u8  mfru_MfgPartNo[16];
  u8  mfru_MfgSerialNo[16];
  u8  mfru_MfgRev[8];
  u8  mfru_MfgMonth;
  u8  mfru_MfgDate;
  u8  mfru_MfgYear;
  u8  mfru_Reserved1;
  u8  mfru_ProductBarcodeSerialNo[12];
#if defined(VESSAPP) || defined(_WINDRIVER)
  u8  mfru_OEMSerialNo [8];
  u8  mfru_Reserved_11 [8];
  u8  mfru_PSUType;
  u8  mfru_Reserved_12 [7];
#else
  u8  mfru_Reserved_11 [16];
  u8  mfru_PSUType;
  u8  mfru_Reserved_12 [7];
#endif
  u8  mfru_WWN[8];
/* Product specific info */
  u8  mfru_Reserved2;
  u8  mfru_Block1MACCount;
  u8  mfru_Block1MACAddress[6];
  u8  mfru_Reserved3;
  u8  mfru_Block2MACCount;
  u8  mfru_Block2MACAddress[6];
  u8  mfru_Reserved4;
  u8  mfru_Block3MACCount;
  u8  mfru_Block3MACAddress[6];
  u8  mfru_IPAddress[4];
  u8  mfru_Mask[4];
#if defined(VESSAPP) || defined(_WINDRIVER)
  u8  mfru_Reserved5[94];
#else
  u8  mfru_SwappableFan;
  u8  mfru_Reserved5[93];
#endif
  u16 mfru_PSCheckSum;
}  PACKED MFRU_t;


#define ENCLOSURE_SIMTYPE_FAULT     0x01
#define ENCLOSURE_SIMTYPE_TIMEOUT   0x02
#define ENCLOSURE_SIMTYPE_NORMAL    0x03

typedef struct MicEnclosureSimulateFaultCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Controller;       /* controller number */
    u8                  enc_Channel;          /* channel Number */
    u16                 enc_SimType;         /* Target number need mechanism for flat ID if flatId,ignore other 2 fields*/
    u16                 enc_TransferLength;   /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_TransferOffset;    /* Note Transfer offset should be here */
    u8                  enc_EnclosureId;
    u8                  enc_Control;
}  PACKED micEncSimFltCmd_t;// __attribute__ ((packed));


typedef struct MicEnclosureFRULedControl
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* should be PMIC_CONTROL_FRU_LED*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_FruNum;       /* use Macros define below */
    u8                  enc_FruLedState;             /* one of colors mentioned below*/
    u16                  enc_TargetId;
    u16                 enc_TransferLength;   /* Note TL shouldbe here,size of Data + buffer header, */
    u16                 enc_TransferOffset;    /* Note Transfer offset should be here */
    u8                  enc_EnclosureId;   /* array flat Id */
    u8                  enc_Control;
}  PACKED micEncFruLedCtrl_t;

#define ENC_FRU_NUM_PSU1            0
#define ENC_FRU_NUM_PSU2            7
#define ENC_FRU_NUM_FB1FAN1         2
#define ENC_FRU_NUM_FB1FAN2         3
#define ENC_FRU_NUM_FB2FAN1         5
#define ENC_FRU_NUM_FB2FAN2         6
#define ENC_FRU_NUM_BATTERY1        1
#define ENC_FRU_NUM_BATTERY2        4
#define ENC_FRU_NUM_SEP1            8
#define ENC_FRU_NUM_SEP2            9
#define ENC_LED_CTRL1_DIRTY_CACHE_LED   10
#define ENC_LED_CTRL2_DIRTY_CACHE_LED   11
#define ENC_LED_RAID_STS                12
#define ENC_FRU_NUM_USB1                13
#define ENC_FRU_NUM_USB2                14
#if defined(VESSAPP) || defined(WINTEST)
#define ENC_FRU_NUM_RECORD              15
#define ENC_FRU_NUM_SYSTEM              16
#define ENC_FRU_NUM_GLOBE_SATA_STATUS   17
#define ENC_FRU_NUM_ETH1                18
#define ENC_FRU_NUM_ETH2                19
#define ENC_FRU_NUM_POWER               20

#define ENC_FRU_ALL                     255
#endif

#define FRU_LED_STATE_GREEN     0x01
#define FRU_LED_STATE_RED       0x02
#define FRU_LED_STATE_AMBER     0x04
#define FRU_LED_STATE_GREEN_BLINK       0x08
#define FRU_LED_STATE_RED_BLINK         0x10
#define FRU_LED_STATE_AMBER_BLINK       0x20
#define FRU_LED_STATE_OFF       0x80

// PMIC_GET_UINQUE_CMD_ID
// PMIC_RELEASE_UINQUE_CMD_ID
// PMIC_GET_CONFIG_LOCK
// PMIC_RELEASE_CONFIG_LOCK
// PMIC_MODIFY_CL_UCID_TIMEOUT
// PMIC_FORCE_RELEASE_CONFIG_LOCK
// PMIC_VERIFY_CL_UCID

#if defined(VESSAPP) || defined(WINTEST)
#define ENC_SYS_LED_DESC_TEMP_CTRL                         0x0001
#define ENC_SYS_LED_DESC_TEMP_PD                           0x0002
#define ENC_SYS_LED_DESC_VOLTAGE                           0x0004
#define ENC_SYS_LED_DESC_FAN                               0x0008
#define ENC_SYS_LED_DESC_LD                                0x0010
#define ENC_SYS_LED_DESC_USER                              0x0020

typedef struct micFruLEDInfo
{
    u8                  mfli_FruLedID;         /* FRU LED ID */
    u8                  mfli_FruLedStatus;     /* FRU LED Status */
    u16                 mfli_FruLedDesc;       /* Bitmap of Led description */
} PACKED MFLI_t;
#endif

typedef struct MicEnclosureGetSetTerminalSensorCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;        /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Reserved;
    u8                  enc_SensorCnt;        /* Sensor count MAX:16 */
    u16                 enc_SensorStatus;     /* Bitmap of sensor status LSB:Signal_0 0:Low 1:High */
    u16                 enc_TransferLength;   /* size of Data + buffer header, */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
} PACKED micEncGetSetTerminalSensorCmd_t;

typedef struct micTerminalSensorInfo
{
    u8                  mtsi_SensorCnt;        /* Sensor count MAX:16 */
    u8                  mtsi_Reserved;
    u16                 mtsi_SensorStatus;     /* Bitmap of sensor status LSB:Signal_0 0:Low 1:High */
} PACKED MTSI_t;


typedef struct MicEnclosureGetSetTerminalAlarmCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;        /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u8                  enc_Reserved;
    u8                  enc_AlarmCnt;         /* Alarm Cnt MAX:16 */
    u16                 enc_AlarmStatus;      /* Bitmap of alarm status LSB:Alarm_0 0:Low 1:High*/
    u16                 enc_TransferLength;   /* size of Data + buffer header, */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
} PACKED micEncGetSetTerminalAlarmCmd_t;

typedef struct micTerminalAlarmInfo
{
    u8                  mtai_AlarmCnt;        /* Alarm Cnt MAX:16 */
    u8                  mtai_Reserved;
    u16                 mtai_AlarmStatus;     /* Bitmap of alarm status LSB:Alarm_0 0:Low 1:High*/
} PACKED MTAI_t;


#define ENC_UART_RS232_MODE                         0
#define ENC_UART_RS422_MODE                         1

typedef struct MicEnclosureGetSetUARTCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u16                 enc_Reserved;
    u8                  enc_UartId;          /* UART channel Number */
    u8                  enc_UartStatus;      /* UART mode */
    u16                 enc_TransferLength;   /* size of Data + buffer header, */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
} PACKED micEncGetSetUARTCmd_t;

typedef struct micUartInfoResponse
{
    u8                  mui_UartId;         /* UART channel Number */
    u8                  mui_Reserved;
    u16                 mui_UartStatus;     /* UART mode */
} PACKED MUI_t;

#define ENC_POWER_BUTTON_COMPONENT_ID               0x01

#define ENC_COMPONENT_ON                            0x01
#define ENC_COMPONENT_OFF                           0x00

typedef struct MicEnclosureGetSetComponentCmd
{
    u8                  enc_ScsiOpCode;
    u8                  enc_MicSignature;
    u16                 enc_MicOpCode;       /* Class Code snd one of the above mentioned commands*/
    union
    {
        u8              enc_ConfigLock;
        u8              enc_UniqueCmdId;
    }PACKED u;
    u8                  enc_LoginKey;
    u16                 enc_Reserved;
    u8                  enc_ComponentId;      /* Component ID */
    u8                  enc_ComponentStatus;  /* Component Status */
    u16                 enc_TransferLength;   /* size of Data + buffer header, */
    u16                 enc_TransferOffset;
    u8                  enc_EnclosureId;
    u8                  enc_Control;
} PACKED micEncGetSetComponentCmd_t;

typedef struct micEncComponentInfoResponse
{
    u8                  mui_ComponentId;         /* Component ID */
    u8                  mui_Reserved;
    u16                 mui_ComponentStatus;     /* Component Status */
} PACKED MECI_t;

typedef struct micGetUcidOrClCmd
{
    u8          guc_ScsiOpCode;
    u8          guc_MicSignature;
    u16         guc_MicOpCode;
    u8          guc_UCIdOrCLId;       /* Not required for PMIC_FORCE_RELEASE_CONFIG_LOCK */
    u8          guc_Reserved1;
    u32         guc_Timeout;
    u16         guc_TransferLength;
    u16         guc_Reserved2;
    u8          guc_Reserved3;
    Control_t   guc_Control;
} PACKED micGetUcidOrClCmd_t ;
//} micGetUcidOrClCmd_t;

/* Data structure for PMIC_GET_UINQUE_CMD_ID,
 * PMIC_GET_CONFIG_LOCK and PMIC_VERIFY_CL_UCID Command
 */
typedef struct micUcidOrCl
{
    u8      uccl_UcidOrCl;
    u8      uccl_Reserved0;
    u16     uccl_Reserved1;
    u32     uccl_Reserved2;
    u64     uccl_TriggerTime; //In Seconds since 1970
} PACKED micUcidOrCl_t;

/* Possible ASCQs */
#define MICS_CONFIG_LOCK_IN_USE                  (MICS_MODULE_SPECIFIC_ERROR_START + 0x01)
#define MICS_FREE_ID_NOT_AVAILABLE               (MICS_MODULE_SPECIFIC_ERROR_START + 0x02)
#define MICS_MODIFY_TIMEOUT_FAILED               (MICS_MODULE_SPECIFIC_ERROR_START + 0x03)
#define MICS_UCID_OR_CL_ALREADY_TAKEN            (MICS_MODULE_SPECIFIC_ERROR_START + 0x04)

typedef struct micReleaseUcidOrClCmd
{
    u8          ruc_ScsiOpCode;
    u8          ruc_MicSignature;
    u16         ruc_MicOpCode;
    u8          ruc_UcidOrCl;
    u8          ruc_Reserved1;
    u32         ruc_Timeout;
    u16         ruc_TransferLength;
    u16         ruc_Reserved2;
    u8          ruc_Reserved3;
    Control_t   ruc_Control;
} PACKED micReleaseUcidOrClCmd_t;
//} micReleaseUcidOrClCmd_t;

/* PMIC_GET_ERR_TABLE */

typedef struct micGetErrTableCmd
{
    u8          get_ScsiOpCode;
    u8          get_MicSignature;
    u16         get_MicOpCode;
    u8          get_UniqueCmdId;
    u8          get_LoginKey;
    u16         get_LDFlatID;
    u8          get_TableType;
    u8          get_Reserved0;
    u16         get_TransferLength;
    u16         get_TransferOffset;
    u8          get_Reserved2;
    Control_t   get_Control;
} PACKED micGetErrTableCmd_t;
//} micGetErrTableCmd_t;

typedef struct ETblEntry
{
   u64         getd_LBA;
   u16         getd_Count;
   u8          getd_Reserved[6];
} PACKED ETblEntry_t;

typedef struct micGetErrTableData
{
    u64            getd_Entries;
    ETblEntry_t    getd_ETbl[1];       /* Actual number of LBAs depends on getEntries. */
} PACKED micGetErrTableData_t;



/* Define for RCT/WCT/IBT Table Type. */
#define    RCT_ENTRY           0x01
#define    WCT_ENTRY           0x02
#define    IBT_ENTRY           0x03



#define MIGRATE_TYPE_NONE           0
#define MIGRATE_TYPE_FRONT          1
#define MIGRATE_TYPE_REAR           2
#define MIGRATE_TYPE_SSM            3

/* defines for migr_mic_flag */
#define MIGRATE_START               0x1
#define MIGRATE_ENDCOMMIT           0x2


/* PMIC_MIGRATE_ARRAY */
typedef struct micArrayMigrateConfigCmd
{
    u8          mac_ScsiOpCode;
    u8          mac_MicSignature;
    u16         mac_MicOpCode;
    u8          mac_ConfigLock;
    u8          mac_LoginKey;
    u8          mac_MigrateType;
    u8          mac_MigrateFlag;
    u16         mac_MigrateDAFlatID;
    u16         mac_TransferLength;
    u16         mac_TransferOffset;
    u8          mac_Reserved1;
    Control_t   mac_Control;
} PACKED micArrayMigrateConfigCmd_t;


/* PMIC_MIGRATE_GETPROGRESS  CDB */
typedef struct micArrayMigrateGetProgCmd
{
    u8          gmp_ScsiOpCode;
    u8          gmp_MicSignature;
    u16         gmp_MicOpCode;
    u8          gmp_UniqueCmdId;
    u8          gmp_LoginKey;
    u16         gmp_StartArrayID;
    u16         gmp_Reserved0;
    u16         gmp_TransferLength;
    u16         gmp_TransferOffset;
    u8          gmp_ArrayCount;
    Control_t   gmp_Control;
} PACKED micArrayMigrateGetProgCmd_t;
//} micArrayMigrateGetProgCmd_t;

/* PMIC_MIGRATE_GETPROGRESS  DATA */
typedef struct micMigrationProgress
{
    /* general info */
    u16 mp_ArrayID;
    u16 mp_LogDrvId;
    u16 mp_OverallPercentage;
    u8  mp_State;
    u8  mp_type;
    u32 mp_Reserved1;
    u32 mp_Reserved2;
    u64 mp_Reserved3;
    u64 mp_Reserved4;
    u64 mp_Reserved5;

    /* reserved */
    u64 mp_Reserved6;
    u64 mp_Reserved7;
    u64 mp_Reserved8;
    u64 mp_Reserved9;
    u64 mp_Reserved10;

    u64 mp_Reserved11;
    u64 mp_Reserved12;
    u64 mp_Reserved13;
    u64 mp_Reserved14;
    u64 mp_Reserved15;

    u64 mp_Reserved16;
    u64 mp_Reserved17;
    u64 mp_Reserved18;
    u64 mp_Reserved19;
    u64 mp_Reserved20;
}  PACKED micMigrationProgress_t;


/* PMIC_MIGRATE_CLEAR_STALE_NVWM  CDB */
typedef struct micMigrateClearStaleNVWMCmd
{
    u8          mcs_ScsiOpCode;
    u8          mcs_MicSignature;
    u16         mcs_MicOpCode;
    u8          mcs_UniqueCmdId;
    u8          mcs_LoginKey;
    u16         mcs_Reserved0;
    u16         mcs_Reserved1;
    u16         mcs_TransferLength;
    u16         mcs_TransferOffset;
    u8          mcs_Reserved2;
    Control_t   mcs_Control;
} PACKED micMigrateClearStaleNVWMCmd_t;
//} micArrayMigrateGetProgCmd_t;


typedef struct micGetTransitionPDInfoCmd
{
    u8          gtpi_ScsiOpCode;
    u8          gtpi_MicSignature;
    u16         gtpi_MicOpCode;
    u8          gtpi_UniqueCmdId;
    u8          gtpi_LoginKey;
    u16         gtpi_ArrayID;
    u16         gtpi_Reserved1;
    u16         gtpi_TransferLength;
    u16         gtpi_TransferOffset;
    u8          gtpi_Count;
    Control_t   gtpi_Control;

} PACKED micGetTransitionPDInfoCmd_t;

typedef struct micTransitionPDInfo
{
    u16 mtpi_NoOfDrives;
    u16 mtpi_Reserved1;
    u32 mtpi_Reserved2; /* for 8-byte aligment */

    micPDInfoPage0_t mtpi_PDInfo[1];


}  PACKED micTransitionPDInfo_t;

#define PMIC_INITIATOR_LIST_FULL       ( MICS_MODULE_SPECIFIC_ERROR_START + 0x01 )
#define PMIC_INVALID_INITIATOR_INDEX   ( MICS_MODULE_SPECIFIC_ERROR_START + 0x02 )
#define PMIC_LMMTABLE_INVALID          ( MICS_MODULE_SPECIFIC_ERROR_START + 0x03 )
#define PMIC_LMMTABLE_EMPTY            ( MICS_MODULE_SPECIFIC_ERROR_START + 0x04 )
#define PMIC_INITIATOR_LIST_EMPTY      ( MICS_MODULE_SPECIFIC_ERROR_START + 0x05 )
#define PMIC_LMM_ALREADY_EXIST         ( MICS_MODULE_SPECIFIC_ERROR_START + 0x06 )
#define PMIC_INITIATOR_ALREADY_EXIST   ( MICS_MODULE_SPECIFIC_ERROR_START + 0x07 )
#define PMIC_MAPPED_LD_NOT_PRESENT     ( MICS_MODULE_SPECIFIC_ERROR_START + 0x08 )
#define PMIC_LUNMAP_TABLE_ISALREADY_PRESENT   ( MICS_MODULE_SPECIFIC_ERROR_START + 0x09 )
    /* Lun map table is already presetn for request initiator, Use addLD action to add new LD */
#define PMIC_LUNMAP_REQUEST_IS_TOO_BIG        ( MICS_MODULE_SPECIFIC_ERROR_START + 0x0A ) /* Request is too big */
#define PMIC_INVLAID_LUNMAP_OPCODE_TYPE       ( MICS_MODULE_SPECIFIC_ERROR_START + 0x0B )
#define PMIC_RQST_CMD_NOT_ALLOWED_FOR_THIS_PRODUCT_TYPE   ( MICS_MODULE_SPECIFIC_ERROR_START + 0x0C )

/* PMIC_LMM_GET_INITIATOR_LIST CDB */
typedef struct micGetInitiatorListCmd
{
    u8          gil_ScsiOpCode;
    u8          gil_MicSignature;
    u16         gil_MicOpCode;
    u8          gil_UniqueCmdId;
    u8          gil_LoginKey;
    u16         gil_Index;
    u16         gil_Reserved1;
    u16         gil_TransferLength;
    u16         gil_TransferOffset;
    u8          gil_Count;
    Control_t   gil_Control;

} PACKED micGetInitiatorListCmd_t;
//} micGetInitiatorListCmd_t;

/* PMIC_LMM_ADD_INITIATOR CDB */
typedef struct micAddInitiatorCmd
{
    u8          aic_ScsiOpCode;
    u8          aic_MicSignature;
    u16         aic_MicOpCode;
    u8          aic_UniqueCmdId;
    u8          aic_LoginKey;
    u16         aic_Reserved;
    u16         aic_Reserved1;
    u16         aic_TransferLength;
    u16         aic_TransferOffset;
    u8          aic_Reserved2;
    Control_t   aic_Control;

} PACKED micAddInitiatorCmd_t;

/* PMIC_LMM_DELETE_INITIATOR CDB */
typedef struct micDeleteInitiatorCmd
{
    u8          dic_ScsiOpCode;
    u8          dic_MicSignature;
    u16         dic_MicOpCode;
    u8          dic_UniqueCmdId;
    u8          dic_LoginKey;
    u16         dic_Index;
    u16         dic_Reserved1;
    u16         dic_TransferLength;
    u16         dic_TransferOffset;
    u8          dic_Reserved2;
    Control_t   dic_Control;
//} micDeleteInitiatorCmd_t;
} PACKED micDeleteInitiatorCmd_t;

typedef struct micInitiatorName
{
   u8 in_InitiatorName[256];
   u16 in_Index;
   u16 in_Reserved[3];
} PACKED micInitiatorName_t;
//} micInitiatorName_t;

typedef struct micGetInitiatorList
{
   u16 gil_NumofInitiators;
   u16 gil_Reserved[3];
   micInitiatorName_t gil_InitiatorName[1];
} PACKED micGetInitiatorList_t;
//} micGetInitiatorList_t;
/* PMIC_LMM_ADD_INITIATOR Data */

/* PMIC_LMM_GET_LMMTABLE CDB */
typedef struct micGetLMMTableCmd
{
    u8          glmt_ScsiOpCode;
    u8          glmt_MicSignature;
    u16         glmt_MicOpCode;
    u8          glmt_UniqueCmdId;
    u8          glmt_LoginKey;
    u16         glmt_Index;
    u16         glmt_Reserved1;
    u16         glmt_TransferLength;
    u16         glmt_TransferOffset;
    u8          glmt_Count;
    Control_t   glmt_Control;

} PACKED micGetLMMTableCmd_t;

/* LMM Lun map information of a logical drive */
typedef struct micLMMInfo
{
   u16 lmmi_LDID;
   u16 lmmi_LUN;
   u16 lmmi_TgtID;
   u16 lmmi_Reserved;
} PACKED micLMMInfo_t;

/* LMM Entry Data */
typedef struct micLMMEntry
{
   union
   {
       u8 lmme_InitiatorName[256];
       u8 lmme_Reserved[256];
   }PACKED lmme_iname;

   union
   {
       u16 lmme_Index;
       u16 lmme_PortID;
   }PACKED lmme_IndexPort;

   u16 lmme_numberofLUNMaps;
   u8 lmme_reserved[4];
   micLMMInfo_t lmme_lmmi[1];
} PACKED micLMMEntry_t;

/* PMIC_LMM_GET_LMMTABLE Data */
typedef struct micLMMTable
{
   u16 lmmt_NumberofLMMEntry;
   u16 lmmt_Reserved[3];
   micLMMEntry_t lmmt_lmme[1];
} PACKED micLMMTable_t;
//} micLMMTable_t;


/* PMIC_LMM_ADD_LMMENTRY CDB */
/* PMIC_LMM_SET_LMMENTRY CDB */
typedef struct micSetLMMEntryCmd
{
    u8          slme_ScsiOpCode;
    u8          slme_MicSignature;
    u16         slme_MicOpCode;
    u8          slme_UniqueCmdId;
    u8          slme_LoginKey;
    u16         slme_Reserved;
    u16         slme_Reserved1;
    u16         slme_TransferLength;
    u16         slme_TransferOffset;
    u8          slme_Reserved2;
    Control_t   slme_Control;

} PACKED micSetLMMEntryCmd_t;

/* PMIC_LMM_DELETE_LMMENTRY CDB */
typedef struct micDeleteLMMEntryCmd
{
    u8          dlme_ScsiOpCode;
    u8          dlme_MicSignature;
    u16         dlme_MicOpCode;
    u8          dlme_UniqueCmdId;
    u8          dlme_LoginKey;
    u16         dlme_Index;
    u16         dlme_Reserved1;
    u16         dlme_TransferLength;
    u16         dlme_TransferOffset;
    u8          dlme_Reserved2;
    Control_t   dlme_Control;

} PACKED micDeleteLMMEntryCmd_t;

/* PMIC_LMM_GET_LMMTABLE_PSCSI CDB */
typedef struct micGetLMMTableCmd_PSCSI
{
    u8          glmt_ScsiOpCode;
    u8          glmt_MicSignature;
    u16         glmt_MicOpCode;
    u8          glmt_UniqueCmdId;
    u8          glmt_LoginKey;
    u16         glmt_PortID;
    u16         glmt_Reserved1;
    u16         glmt_TransferLength;
    u16         glmt_TransferOffset;
    u8          glmt_Count;
    Control_t   glmt_Control;

} PACKED micGetLMMTableCmd_PSCSI_t;

/* PMIC_LMM_SET_LMMENTRY CDB */
typedef struct micSetLMMEntryCmd_PSCSI
{
    u8          slme_ScsiOpCode;
    u8          slme_MicSignature;
    u16         slme_MicOpCode;
    u8          slme_UniqueCmdId;
    u8          slme_LoginKey;
    u16         slme_PortID;
    u16         slme_Reserved1;
    u16         slme_TransferLength;
    u16         slme_TransferOffset;
    u8          slme_Reserved2;
    Control_t   slme_Control;

} PACKED micSetLMMEntryCmd_PSCSI_t;

/* PMIC_CONTROLLER_GET_TIME */
/* PMIC_CONTROLLER_SET_TIME */

typedef struct micCtlGetSetTimeCmd
{
    u8          gsct_ScsiOpCode;
    u8          gsct_MicSignature;
    u16         gsct_MicOpCode;        /* Config Lock required for Set Time */
    u8          gsct_UniqueCmdId;
    u8          gsct_LoginKey;
    u16         gsct_ControllerID;
    u16         gsct_Reserved;
    u16         gsct_TransferLength;
    u16         gsct_TransferOffset;
    u8          gsct_ControllerCount;
    Control_t   gsct_Control;
} PACKED micCtlGetSetTimeCmd_t;

typedef struct micCtlTime
{
    u64     ct_UTCTime;     /* UTC Time */
    u8      ct_TimeZoneInfo;
    u8      ct_Reserved[6];
    u8      ct_ExtTimeInfo;
}  PACKED micCtlTime_t;

/* The list of possible value for ct_ExtTimeInfo */
#define EXTTI_NOT_VALID         0
#define EXTTI_TIME_DIFFERENCE   1
#define EXTTI_TZ_DST            2 /* For future use */

/* The list of possible state for PMIC_SPIN_UP_DOWN_CHANGE_STATE */
#define SPINDRV_SPIN_UP_REQS       0x0
#define SPINDRV_SPIN_DOWN_REQS     0x1

/* Posible PDFlat ID are
           PDFlatID - Valid PDFlatID (unused spare, unconfigured, configured dead PD flat ids )
           RCM_INVALID_FLAT_ID ( 0xFFFE - Change PD spin state of all used drives - FW will change PD spin of all unused spare, unconfigured, configured dead )
*/

/* PMIC_SPIN_UP_DOWN_CHANGE_STATE      */

typedef struct micChangePDSpinStateCmd
{
    u8          ssc_ScsiOpCode;
    u8          ssc_MicSignature;
    u16         ssc_MicOpCode;
    u8          ssc_UniqueCmdId;
    u8          ssc_LoginKey;
    u16         ssc_PDFlatID;
    u16         ssc_Reserved0;
    u16         ssc_TransferLength;
    u16         ssc_Reserved1;
    u8          ssc_RequestedState;
    Control_t   ssc_Control;
} PACKED micChangePDSpinStateCmd_t;
//} micSpareCheckCmd_t;

/* PMIC_SPIN_UP_DOWN_GET_STATUS        */
typedef struct micGetPDSpinStateCmd
{
    u8          sgs_ScsiOpCode;
    u8          sgs_MicSignature;
    u16         sgs_MicOpCode;
    u8          sgs_UniqueCmdId;
    u8          sgs_LoginKey;
    u16         sgs_PDFlatID;
    u16         sgs_Reserved0;
    u16         sgs_TransferLength;
    u16         sgs_Reserved1;
    u8          sgs_Reserverd2;
    Control_t   sgs_Control;
} PACKED micGetPDSpinStateCmd_t;
//} micSpareCheckCmd_t;

/* list of Possible PD Spin state */
#define PD_SPUN_UP         0x0     /* PD is spun up, ready to access */
#define PD_SPINNING_UP     0x1     /* PD is in process of coming up */
#define PD_SPINNING_DOWN   0x2     /* PD is in process of spinning down    */
#define PD_SPUN_DOWN       0x3
   /* PD is SPUN down, need to issue spin up command to make it accessible */
#define PD_SPIN_INVALID    0xFF    /* PD not present */

typedef struct micPDSpinState
{
    u16 pdss_PDFlatID;                  /*  Spare PD flat ID  */
    u8  pdss_State;                     /*  PD spin state */
    u8  pdss_Reserved[5];               /*  Padding for Inband path    */
}  PACKED micPDSpinState_t;

/* Module specific error return Values */
#define DRV_SPIN_CMD_ALREADY_PENDING       (MICS_MODULE_SPECIFIC_ERROR_START + 0)

/* PMIC_SPARECHECK_START           */
/* PMIC_SPARECHECK_GET_STATUS      */

typedef struct micSpareCheckCmd
{
    u8          sck_ScsiOpCode;
    u8          sck_MicSignature;
    u16         sck_MicOpCode;
    u8          sck_UniqueCmdId;
    u8          sck_LoginKey;
    u16         sck_SpareArrayID;
    u16         sck_Reserved0;
    u16         sck_TransferLength;
    u16         sck_Reserved1;
    u8          sck_Reserved2;
    Control_t   sck_Control;
} PACKED micSpareCheckCmd_t;
//} micSpareCheckCmd_t;

/*
Note:
Array  - Valid Spare Array ID, Shall start spare check/ Get status only on
           the specified array.
       - 0xFFFF, Will start spare check/Get Status of all
           available spare arrays.
*/
/*
   Return data for spare check "Get status" command, following
   structure will be returned for the requested Spare Array / all spare arrays
*/

typedef struct micSpareCheckStatus
{
    u16 sck_SparePDFlatID;             /*  Spare PD Flat ID  */
    u16 sck_SpareArrayID;              /*  Spare array ID */
    u8  sck_State;                     /*  status of Spare Array */
    u8  sck_Reserved[3];               /*  Padding for Inband path    */
}  PACKED micSpareCheckStatus_t;

/* possible Spare check status */
#define SPARECHECK_ACTIVE              0x01
                       /* Spare check is running not complete, yet */
#define SPARE_HEALTHY                  0x02
                       /* Spare check is complete, GOOD health */
#define SPARE_UNHEALTHY                0x03
                       /* Spare check is complete, Bad health */
#define SPARE_INVALID                  0x04
                       /* Spare check is not excuted since power cycle. */

/* Module specific error return Values */
#define SPARE_CHECK_CMD_ALREADY_PENDING        (MICS_MODULE_SPECIFIC_ERROR_START + 0)
#define SPARE_CHECK_INVALID_ARRAY              (MICS_MODULE_SPECIFIC_ERROR_START + 1)
/* Specified PD is either Data drive or an unconfigured drive */
#define SPARE_CHECK_PD_NOT_PRESENT             (MICS_MODULE_SPECIFIC_ERROR_START + 2)
/* Specified Pd is not present */
#define SPARE_CHECK_PD_IS_DEAD                 (MICS_MODULE_SPECIFIC_ERROR_START + 3)
/* Specified Pd is not dead */
#define SPARE_CHECK_NO_SPARE_PRESENT           (MICS_MODULE_SPECIFIC_ERROR_START + 4)
/* Specified spare array in contoller for spare check */
#define SPARE_CHECK_PD_IS_UNCONFIGURED         (MICS_MODULE_SPECIFIC_ERROR_START + 5)
/* Specified PD is unconfigured */

/* BBM */

/* PMIC_BBM_GET_DEFECT_LIST            0x1500 */
typedef struct micGetDefectListCmd
{
    u8          gdlc_ScsiOpCode;
    u8          gdlc_MicSignature;
    u16         gdlc_MicOpCode;
    u8          gdlc_UniqueCmdId;
    u8          gdlc_LoginKey;
    u16         gdlc_PDFlatId;
    u16         gdlc_Reserved1;
    u16         gdlc_TransferLength;
    u16         gdlc_TransferOffset;
    u8          gdlc_Reserved2;
    Control_t   gdlc_Control;
} PACKED micGetDefectListCmd_t;

/* PMIC_BBM_CLEAR_DEFECT_LIST          0x1501 */
typedef struct micClearDefectListCmd
{
    u8          gcdl_ScsiOpCode;
    u8          gcdl_MicSignature;
    u16         gcdl_MicOpCode;
    u8          gcdl_UniqueCmdId;
    u8          gcdl_LoginKey;
    u16         gcdl_PDFlatId;
    u16         gcdl_Reserved1;
    u32         gcdl_Reserved2;
    u8          gcdl_Reserved3;
    Control_t   gcdl_Control;
} PACKED micClearDefectListCmd_t;

#define MIC_DEFECT_LIST_LONG_BLOCK_FORMAT           0
#define MIC_DEFECT_LIST_SHORT_BLOCK_FORMAT          1 /* reserved -- not used */
#define MIC_DEFECT_LIST_BYTES_FROM_INDEX_FORMAT     2 /* reserved -- not used */
#define MIC_DEFECT_LIST_PHYSICAL_SECTOR_FORMAT      3
#define MIC_DEFECT_LIST_VENDOR_SPECIFIC_FORMAT      4 /* reserved -- not used */

typedef struct bbmDefectList
{
    u32 bdl_BadBlockCount;
    u8  bdl_DefectListFormat;
    u8  bdl_Reserved01[3];
    u64 bdl_badBlockLba[1];
} PACKED bbmDefectList_t;

/* PMIC_CONTROLLER_GET_NVRAM_DUMP */
/* PMIC_CONTROLLER_CLEAR_NVRAM_DUMP */

typedef struct micCtlGetClearNVRAMDumpCmd
{
    u8          gcnd_ScsiOpCode;
    u8          gcnd_MicSignature;
    u16         gcnd_MicOpCode;
    u8          gcnd_UniqueCmdId;
    u8          gcnd_LoginKey;
    u16         gcnd_ControllerID;
    u16         gcnd_Reserved;
    u16         gcnd_TransferLength;
    u16         gcnd_TransferOffset;
    u8          gcnd_ControllerCount;
    Control_t   gcnd_Control;
} PACKED micCtlGetClearNVRAMDumpCmd_t;

#define MAX_INFO_CRASH_SIZE  240
typedef struct micWDCrashInfo
{
    u8      wci_ReasonForDump;
    u8      wci_Reserved;
    u8      wci_Year;
    u8      wci_Month;
    u8      wci_Date;
    u8      wci_Hour;
    u8      wci_Min;
    u8      wci_Sec;
    u32     wci_ProgramCounter;
    u32     wci_LinkRegister;
    u32     wci_StackPointer;
    u32     wci_InvalidAddress;
    u32     wci_ErrorCode;
    u8      wci_ThreadName[16];
    u32     wci_InfoSize;
    u32     wci_Info[1]; //Variable but max is MAX_CRASH_INFO_SIZE
} PACKED micWDCrashInfo_t;


/* PMIC_SUBSYSTEM_REBOOT */
/* PMIC_SUBSYSTEM_SHUTDOWN */
typedef struct micSubsystemShutDownRebootCmd
{
    u8          ssrc_ScsiOpCode;
    u8          ssrc_MicSignature;
    u16         ssrc_MicOpCode;
    u8          ssrc_ConfigLock;
    u8          ssrc_LoginKey;
    u8          ssrc_ControllerID;
    u8          ssrc_Reserved0;
    u16         ssrc_Reserved1;
    u16         ssrc_Reserved2;
    u16         ssrc_Reserved3;
    u8          ssrc_Reserved4;
    Control_t   ssrc_Control;
} PACKED micSubsystemShutDownRebootCmd_t;

/* PMIC_HBA_SHUTDOWN */
typedef struct micHBAShutDownCmd
{
    u8          hsd_ScsiOpCode;
    u8          hsd_MicSignature;
    u16         hsd_MicOpCode;
    u8          hsd_ConfigLock;
    u8          hsd_LoginKey;
    u16         hsd_Reserved0;
    u16         hsd_Reserved1;
    u16         hsd_Reserved2;
    u16         hsd_Reserved3;
    u8          hsd_Reserved4;
    Control_t   hsd_Control;
} PACKED micHBAShutDownCmd_t;

/* PMIC_HBA_RESUME */
typedef struct micHBAPowerStateCmd
{
    u8          hpsc_ScsiOpCode;
    u8          hpsc_MicSignature;
    u16         hpsc_MicOpCode;
    u8          hpsc_ConfigLock;
    u8          hpsc_LoginKey;
    u16         hpsc_Reserved0;
    u16         hpsc_Reserved1;
    u16         hpsc_Reserved2;
    u16         hpsc_Reserved3;
    u8          hpsc_Reserved4;
    Control_t   hpsc_Control;
} PACKED micHBAPowerStateCmd_t;

/* Module specific error return Values */
#define MICS_SHUTDOWN_REBOOT_INTERNAL_ERROR        (MICS_MODULE_SPECIFIC_ERROR_START + 0)
/* Sas Topology related commands */
typedef struct MicCmdGetSasTopology
{
    u8                  gst_ScsiOpCode;
    u8                  gst_MicSignature;
    u16                 gst_MicOpCode;

    union
    {
        u8              gst_ConfigLock;
        u8              gst_UniqueCmdId;
    }PACKED u;

    u8                  gst_LoginKey;
    u8                  gst_EnclosureID;    /* starting enclsoure ID */
    u8                  gst_Reserved1;
    u8                  gst_Reserved2;
    u8                  gst_Reserved3;
    u16                 gst_TransferLength;
    u16                 gst_TransferOffset;
#define ALL_ENCLOSURES_PRESENT    0xff
    u8                  gst_Count;      /* if 0xFF get all enclosures present from requested ID to max(16)  */
    u8                  gst_Control;
} PACKED MicCmdGetSasTopology_t;

/* topology response realted structure */
#define ENCLOSURE_TYPE_PHYSICAL     0x01
#define ENCLOSURE_TYPE_VIRTUAL      0x02
#define WWN_BYTES                   0x08
#define MAX_VENDORID                0x08
#define MAX_PRODUCTID               0x10
#define UNKNOWN_VALUE               0xFF

/* SAS routing attribute */
#define RA_DIRECT_ROUTING   0x0
#define RA_SUBTRACTIVE_ROUTING   0x1
#define RA_TABLE_ROUTING   0x2

typedef struct SasConnectedDeviceInfo
{
    u8 EnclosureID;
    u8 NumSlots;
    u8 Reserved1[2];
    u8 EnclosureType; // following fields are meaning only if this is physical.
    u8 DiskID;        // If directly attached to a drive
    u8 ExpanderID;
    u8 Reserved2;
    u8 PortID;
    u8 RoutingAttribute;
    u8 Reserved3[6];
} PACKED SASConnectedDevInfo_t;

typedef struct  SasExpanderExternalPortInfo
{
    u8   PortID;    /* Please refer to description of Ports and their position at the end of the document*/
    u8   NumberOfPhy; // How many phy in this port.
    u8   RoutingAttribute;   // table or subtractive
    u8   EnclosureID;  // for software cross reference
    u8   Reserved1[4];
    u8   ExpanderID;  //for software reference;
    u8   NumDevicesConnected;  // if more than one device connected (0xff if unknown =0 Num connected)
    u8   Reserved2[6];
    u8   PhyIDsInThisConnector[16]; // depth = NumberOfPhy
    SASConnectedDevInfo_t  DeviceConnected[1];  // info about the device connected to this port
} PACKED SASEXPExtPortInfo_t;

typedef struct SASExpanderInfo
{
    u32 ExpanderStructSizeInBytes; // including these bytes
    u8  Reserved1[4];            // for  8 bytes alignment
    u64 SASAddress;         /* The SAS address of this expander */
    u8  EnclosureID;         // for software cross reference
    u8  ExpanderID;          /*  w.r.t to this enclosure , for j300s 0 and 1( 0 to the left and 1 to the right) */
    u8  NumberOfExternalPorts;       /* How mant port in this expander*/
    u8  Reserved2[5];
    SASEXPExtPortInfo_t  ExpanderPortInfo[1];    /* variable array */
} PACKED ExpandersInEnclInfo_t;

typedef struct  SasEnclosureConnectedInfo
{
    u32   EnclosureInfoSizeInBytes; // this enclosure structure size including these 4 bytes,
    u8    Reserved1[4];
    u8    EnclosureID;
    u8    NumberOfslots;
    u8    FlatIDStart;  // Is this required??
    u8    NumOfExpanders;
    u8    Reserved2[4];
#define ENCLOSURE_TYPE_PHYSICAL  0x01
#define ENCLOSUR_TYPE_VIRTUAL    0x02
    u8    EnclosureType; // virtual or physical ( following fileds exists only if physical
    u8    Reserved3[7];
    u8    EnclosureWWN[WWN_BYTES]; //From the inquiry info page 83H.
    u8    EnclosureManufactureString[MAX_VENDORID+MAX_PRODUCTID]; // both vendor and product asci values
    ExpandersInEnclInfo_t ExpanderInfo[1]; //variable array
} PACKED SASEncInfo_t;


typedef struct SASTopologyInfo
{
    u8  NumberOfEnclosures;       /* Enclosure entries presented in this response */
    u8  Reserved[7];
    SASEncInfo_t  ConnectedEnclosureInfo;
} PACKED MicSasMgtStruct_t;

//PMIC_SMP_GET_SAS_REPORT_GENERAL_DISCOVER_INFO
// both report general and disocver commands response
// command structure
typedef struct MicCmdGetSasSMPDiscoverResponse
{
    u8   ssd_ScsiOpCode;
    u8   ssd_MicSignature;
    u16  ssd_MicOpCode;
    u8   ssd_UniqueCmdId;
    u8   ssd_LoginKey;
    u8   ssd_EnclosureId;    /* starting enclsoure ID */
    u8   ssd_ExpanderId;
    u8   ssd_Reserved1;
    u8   ssd_Reserved2;
    u16  ssd_TransferLength;
    u16  ssd_TransferOffset;
    u8   ssd_Reserved3;      /* if 0xFF get all enclosures present from requested ID to max(16)  */
    u8   ssd_Control;
} PACKED MicCmdGetSasSMPDisocverCmdRes_t;

typedef struct PhyInfoForMic
{
    u8 PhyID;
    u8 Reserved2[2];
    u8 AttachedDevType;  //only bits 4 to 6, rem bytes reserved
#define MIC_SMP_DIS_ATTACHED_DEV_MASK 0x70
#define MIC_SMP_DIS_NO_DEV_ATTACHED   0x00
#define MIC_SMP_DIS_END_DEV_ATTACHED  0x10 //0x01
#define MIC_SMP_DIS_EDGE_EXP_ATTACHED 0x20 //0x02
#define MIC_SMP_DIS_FANOUT_ATTACHED   0x30 //0x03
    u8 PhyRateNegotiated;
#define MIC_SMP_PHYLINK_RATE_ENABLED        0x00
#define MIC_SMP_PHYLINK_RATE_DISABLED       0x01
#define MIC_SMP_PHYLINK_RATE_ENABLEDFAIL    0x02
#define MIC_SMP_PHYLINK_RATE_ENABLEDSATA    0x03
#define MIC_SMP_PHYLINK_RATE_ENABLED_1P5GB  0x08
#define MIC_SMP_PHYLINK_RATE_ENABLED_3GB    0x09
    u8 AttachedInitiatorInfo;
#define MIC_SMP_NO_INITIATOR_CONNECTED      0x00
#define MIC_SATA_INITIATOR_CONNECTED        0x01
#define MIC_SMP_INITIATOR_CONNECTED         0x02
#define MIC_STP_INITIATOR_CONNECTED         0x04
#define MIC_SSP_INITIATOR_CONNECTED         0x08
    u8 AttachedTgtInfo;
#define MIC_SMP_NO_TGT_CONNECTED            0x00
#define MIC_SATA_TGT_CONNECTED              0x01
#define MIC_SMP_TGT_CONNECTED               0x02
#define MIC_STP_TGT_CONNECTED               0x04
#define MIC_SSP_TGT_CONNECTED               0x08
#define MIC_SATA_PS_CONNECTED               0x80  // sata Port selector connected
    u8 Resreved3;
    u64 PhySASAddress;
    u64 AttachedSASAddress;
    u8 AttachedPhyID;
    u8 Reserved4[7];
    u8 MinimumPhyLinkRateInfo; //both programmed and hardware Minimum
    u8 MaximumPhyLinkRataInfo; //both programmed and hardware Maximum
/* sas speed defines for SMP command response only*/
#define SAS_SPEED_1P5GB    8
#define SAS_SPEED_3GB      9
/* other values are invalid*/
    u8 PhyCount;
    u8 VirtualPhyAndPartialPathwayTOV;
    u8 RoutingAttribute;
    u8 Reserved5[3];
    u16 VendorSpInfo;
    u16 DriveFlatId;  //if connected device is  end device
    u8 slotNumber;
    u8 Reserved6[3];
    u8 IsConnectedtoExtPort; // true or false
    u16 ConnectorID;  //meaningful only if connected to external port
    u8 Reserved7[5];
}PACKED micRespPhyInfo_t;

// response structure
typedef struct ReportGeneralandDiscover
{
    u16 EnclosureID;
    u16 ExpanderId;
    u16 NumOfPhy;
    u16 Reserved;
    u64 ExpanderSASAddress;
    u64 Reserved2;
    micRespPhyInfo_t PhyInfo[1]; // will run up to  NumOfPhy
}PACKED micRespSASSMPDiscover_t;

// get phyerror log
typedef struct MicCmdGetSasSMPErrorLog
{
    u8   ssd_ScsiOpCode;
    u8   ssd_MicSignature;
    u16  ssd_MicOpCode;
    u8   ssd_UniqueCmdId;
    u8   ssd_LoginKey;
    u8   ssd_EnclosureID;    /* starting enclsoure ID */
    u8   ssd_ExpanderId;
    u8   ssd_Reserved1;
    u8   ssd_Reserved2;
    u16  ssd_TransferLength;
    u16  ssd_TransferOffset;
    u8   ssd_Reserved3;      /* if 0xFF get all enclosures present from requested ID to max(16)  */
    u8   ssd_Control;
} PACKED MicCmdGetSasSMPErrorLog_t;
//response structure

typedef struct PhyErrLogInfo
{
    u8  PhyID;
    u8  Reserved;
    u16 InvalidDwordCount;
    u16 RunningDisparityErrCount;
    u16 LossOfDwordSyncCount;
    u16 PhyResetProblemCount;
    u8  slotNumber;
    u8  Reserved1;
    u16 DriveFlatId;  //if connected device is  end device
    u8  IsConnectedtoExtPort; // true or false
    u8  Reserved3;
    u16 ConnectorID;  //meaningful only if connected to external port
    u8  Reserved4[6];
}PACKED micRespPhyErrorLog_t;

typedef struct SmpErroLogHeader
{
    u16 EnclosureID;
    u16 ExpanderId;
    u16 NumOfPhy;
    u16 Reserved;
    u64 ExpanderSASAddress;
    u64 Reserved2;
    micRespPhyErrorLog_t PhyErrLogInfo[1]; // Will run up to NumOfPhy
}PACKED micRespSasSMPErrorLogHdr_t;

//SMP phy control
typedef struct MicCmdPerformSasSMPPhyControl
{
    u8   ssp_ScsiOpCode;
    u8   ssp_MicSignature;
    u16  ssp_MicOpCode;
    u8   ssp_UniqueCmdId;
    u8   ssp_LoginKey;
    u8   ssp_EnclosureId;    /* starting enclsoure ID */
    u8   ssp_ExpanderId;
    u8   ssp_PhyId; // one of the valid Phy;s for given expander
    u8   ssp_PhyOp; //intended phy operation posiible values below
#define MIC_SMP_PHY_CTRL_NO_OP         0x00
#define MIC_SMP_PHY_CTRL_LINK_RESET    0x01
#define MIC_SMP_PHY_CTRL_HARD_RESET    0x02
#define MIC_SMP_PHY_CTRL_DISABLE       0x03
#define MIC_SMP_PHY_CTRL_CLEAR_ERRLOG  0x05
#define MIC_SMP_PHY_CTRL_CLEAR_AFFLTN  0x06
#define MIC_SMP_PHY_CTRL_TX_SATA_PS    0x08  //SATA Port select sugnal
/* other values are reserved */
    u16  ssp_TransferLength;
    u16  ssp_TransferOffset;
    u8   ssp_Reserved3;      /* if 0xFF get all enclosures present from requested ID to max(16)  */
    u8   ssp_Control;
} PACKED MicCmdDoSMPPhyControl_t;

typedef struct MicCmdGetSasC2CSMPErrorLog
{
    u8   ssd_ScsiOpCode;
    u8   ssd_MicSignature;
    u16  ssd_MicOpCode;
    u8   ssd_UniqueCmdId;
    u8   ssd_LoginKey;
    u8   ssd_Reserved2;    /* starting enclsoure ID */
    u8   ssd_Reserved3;
    u8   ssd_Reserved4;
    u8   ssd_Reserved5;
    u16  ssd_TransferLength;
    u16  ssd_TransferOffset;
    u8   ssd_Reserved6;      /* if 0xFF get all enclosures present from requested ID to max(16)  */
    u8   ssd_Control;
} PACKED MicCmdGetC2CSasSMPErrorLog_t;
//response structure

typedef struct SmpC2CErroLogHeader
{
    u16 PortID;
    u16 Reserved;
    u16 NumOfPhy;
    u16 Reserved1;
    u64 PortSASAddress;
    u64 Reserved2;
    micRespPhyErrorLog_t PhyErrLogInfo[1]; // Will run up to NumOfPhy
}PACKED micRespC2CSasSMPErrorLogHdr_t;

typedef struct MicCmdPerformC2CSasSMPPhyControl
{
    u8   ssp_ScsiOpCode;
    u8   ssp_MicSignature;
    u16  ssp_MicOpCode;
    u8   ssp_UniqueCmdId;
    u8   ssp_LoginKey;
    u8   ssp_Reserved1;
    u8   ssp_Reserved2;
    u8   ssp_PhyId; // one of the valid Phy;s for given expander
    u8   ssp_PhyOp; //intended phy operation possible values define in MicCmdPerformSasSMPPhyControl  command
    u16  ssp_TransferLength;
    u16  ssp_TransferOffset;
    u8   ssp_Reserved3;      /* if 0xFF get all enclosures present from requested ID to max(16)  */
    u8   ssp_Control;
} PACKED MicCmdDoC2CSMPPhyControl_t;
//response if bad is SMP specific. if good just the status alone for the above command

/* PMIC_PASSWORD_JUMPER_GET_STATUS   */
typedef struct micPasswdJumperGetStatusCmd
{
    u8          pjgs_ScsiOpCode;
    u8          pjgs_MicSignature;
    u16         pjgs_MicOpCode;
    u8          pjgs_Reserved0;
    u8          pjgs_Reserved1;
    u16         pjgs_Reserved2;
    u16         pjgs_Reserved3;
    u16         pjgs_TransferLength;
    u16         pjgs_TransferOffset;
    u8          pjgs_Reserved4;
    Control_t   pjgs_Control;
} PACKED micPasswdJumperGetStatusCmd_t;

typedef struct micPasswordJumperStatus
{
   u8  pjs_PasswordJumperPresentStatus;
   u8  pjs_PasswordJumperClearStatus;
   u8  pjs_Reserved[14];
} PACKED micPasswordJumperStatus_t;

/* Possible values for pjs_PasswordJumperPresentStatus */
#define PJS_JUMPER_NOT_PRESENT     0x00
#define PJS_JUMPER_PRESENT         0x01
#define PJS_JUMPER_NOT_SUPPORTED   0xFF

/* PMIC_PASSWORD_JUMPER_CLEAR_STATUS */
typedef struct micPasswdJumperClearStatusCmd
{
    u8          pjcs_ScsiOpCode;
    u8          pjcs_MicSignature;
    u16         pjcs_MicOpCode;
    u8          pjcs_ConfigLock;
    u8          pjcs_LoginKey;
    u16         pjcs_Reserved0;
    u16         pjcs_Reserved1;
    u16         pjcs_Reserved2;
    u16         pjcs_Reserved3;
    u8          pjcs_Reserved4;
    Control_t   pjcs_Control;
} PACKED micPasswdJumperClearStatusCmd_t;

/* Possible values for pjs_PasswordJumperClearStatus */
#define PJCS_JUMPER_NOT_CLEARED    0x00
#define PJCS_JUMPER_CLEARED        0x01
#define PJCS_JUMPER_NOT_SUPPORTED  PJS_JUMPER_NOT_SUPPORTED

/*
 * SMART Operation Values
 *
 * also uses for field modeSenseEnable of smartPdMiniRioScratchPad_t
 *
 */
#define SMART_OP_ENABLE             0x01 /* not support present */
#define SMART_OP_DISABLE            0x02 /* not support present */
#define SMART_OP_DIAG_SHORT         0x03
#define SMART_OP_DIAG_EXTENDED      0x04
#define SMART_OP_DIAG_ABORT         0x05
#define SMART_OP_INVALID            0xFF /* invalid (initialize) value */

/*
 * MIC Command for SMART opeation
 *
 */
typedef struct micSmartOpCmd
{
    u8           smo_ScsiOpCode;           /* management (0xD8) */
    u8           smo_MicSignature;         /* signature */
    u16          smo_MicOpCode;            /* PMIC_SMART_SUBMIT_OP */
    u8           smo_UniqueCmdId;          /**/
    u8           smo_LoginKey;             /**/

    /* ONLY UNCONFIGURATED SATA PD */
    u16          smo_PDFlatId;             /* flat id of unconfigured SATA PD,
                                            * 0xFF: means all unconfigured SATA PD */

    u8          smo_Operation;             /* SMART operation */
    u8          smo_Reserved1;             /* reserved */
    u16         smo_TransferLength;        /* transfer length */
    u16         smo_TransferOffset;        /* transfer offset */
    u8          smo_Reserved2;             /* reserved */
    Control_t   smo_Control;

} PACKED micSmartOpCmd_t;

/*
 * MIC Command for obtaining SMART diagnostic status
 *
 */
typedef struct micSmartGetDiagStatusCmd
{
    u8          sds_ScsiOpCode;       /* management (0xD8) */
    u8          sds_MicSignature;     /* signature */
    u16         sds_MicOpCode;        /* PMIC_SMART_GET_DIAG_STATUS */
    u8          sds_UniqueCmdId;      /**/
    u8          sds_LoginKey;         /**/

    /* ONLY UNCONFIGURATED SATA PD */
    u16         sds_PDFlatId;         /* flat id of unconfigured SATA PD */
    u16         sds_Reserved1;        /* reserved */
    u16         sds_TransferLength;   /* transfer length */
    u16         sds_TransferOffset;   /* transfer offset */
    u8          sds_Reserved2;        /* reserved */
    Control_t   sds_Control;

} PACKED micSmartGetDiagStatusCmd_t;


/*
 * SMART diagnostic status values
 *
 */
#define SMART_DIAG_STATUS_COMPLETE       0x00
#define SMART_DIAG_STATUS_ABORTED        0x01
#define SMART_DIAG_STATUS_INTERRUPTED    0x02
#define SMART_DIAG_STATUS_ERROR          0x03
#define SMART_DIAG_STATUS_ERROR_COMPLETE 0x04
#define SMART_DIAG_STATUS_IN_PROGRESS    0x0F

/*
 * SMART diagnostic internal status
 */
#define SMART_DIAG_STATUS_NEVER_STARTED  0xFF
#define SMART_DIAG_STATUS_FIRED          0xFE

/*
 * MIC Data for SMART diagnostic status
 *
 */
typedef struct micSmartDiagStatus
{
    u16         sds_PDFlatId;              /* flat id of the unconfigured SATA PD */
    u8          sds_Operation;             /* SMART operation */
    u8          sds_Status;                /* diagnostics status */
    u8          sds_Percentage;            /* diagnostic in progress percentage */
    u8          sds_Reserved [11];         /* reserved */

} PACKED micSmartDiagStatus_t;

typedef struct micFCGetParamsInfoCmd
{
    u8  igpc_ScsiOpCode;
    u8  igpc_MicSignature;
    u16 igpc_MicOpCode;
    u8  igpc_UniqueCmdId;
    u8  igpc_LoginKey;
    u8  igpc_PortID;
    u8  igpc_PageCode;
    u8  igpc_SessionID;
    u8  igpc_Reserved2;
    u16 igpc_TransferLength;
    u16 igpc_TransferOffset;
    u8  igpc_ControllerID;
    Control_t igspc_Control;
} PACKED micFCGetParamsInfoCmd_t;


typedef struct micFCSetParamsCmd
{
    u8  ispc_ScsiOpCode;
    u8  ispc_MicSignature;
    u16 ispc_MicOpCode;
    u8  ispc_UniqueCmdId;
    u8  ispc_LoginKey;
    u8  ispc_PortID;/* PortID is valid for only a few pages.  * for Node Parameter Page NodeID */
    u8  ispc_PageCode;
    u16 ispc_SessionIndex;
    u16 ispc_TransferLength;
    u16 ispc_TransferOffset;
    u8  ispc_ControllerID;
    Control_t ispc_Control;
} PACKED micFCSetParamsCmd_t;

/* PMIC_CONTROLLER_ENTER_MAINTENANCE_MODE */
/* PMIC_CONTROLLER_EXIT_MAINTENANCE_MODE */
typedef struct micControllerEnterExitMModeCmd
{
    u8          cemm_ScsiOpCode;
    u8          cemm_MicSignature;
    u16         cemm_MicOpCode;
    u8          cemm_Reserved5;
    u8          cemm_Reserved6;
    u8          cemm_ControllerID;
    u8          cemm_Reserved0;
    u16         cemm_Reserved1;
    u16         cemm_Reserved2;
    u16         cemm_Reserved3;
    u8          cemm_Reserved4;
    Control_t   cemm_Control;
} PACKED micControllerEnterExitMModeCmd_t;

#define CONTROLLER_ALREADY_IN_MAINTENANCE_MODE             (MICS_MODULE_SPECIFIC_ERROR_START + 0)
#define CONTROLLER_CANNOT_EXIT_FROM_NON_MAINTENANCE_MODE   (MICS_MODULE_SPECIFIC_ERROR_START + 1)


/* PMIC_CLIQUE_GET_INFORMATION */
typedef struct micCliqueGetInfoCmd
{
    u8          cgic_ScsiOpCode;
    u8          cgic_MicSignature;
    u16         cgic_MicOpCode;
    u8          cgic_UniqueCmdId;
    u8          cgic_LoginKey;
    u16         cgic_Reserved0;
    u16         cgic_Reserved1;
    u16         cgic_TransferLength;
    u16         cgic_TransferOffset;
    u8          cgic_Reserved2;
    Control_t   cgic_Control;
} PACKED micCliqueGetInfoCmd_t;
//} micSubsystemGetInfoCmd_t;

typedef struct micMemberCtlInfo
{
   u8  mci_Index;
   u8  mci_Reserved[8]; //Reserved to use later for Subsystem level info
   u8  mci_SlotNumber;
   u8  mci_WWN[8];
   u8  mci_ReadinessStatus;
   u8  mci_IsMaster;
}  PACKED micMemberCtlInfo_t;

typedef struct micCliqueGetInfo
{
   u8  cgi_Reserved0[8]; //Reserved to use later for Subsystem level info
   u8  cgi_MaxControllersSupported;
   u8  cgi_NumberOfCtrlsInClique;
   u8  cgi_NumberOfActualCtrlsInClique;
   u8  cgi_RedundancyStatus;
   u8  cgi_RedundancyType;
   u8  cgi_Reserved1[51]; //Reserved for expansion
   micMemberCtlInfo_t cgi_MemberControllerInfo[1]; //Can go till cgi_NumberOfCtrlsInClique or cgi_MaxControllersSupported
}  PACKED micCliqueGetInfo_t;

/* Possible values for cgi_RedundancyStatus */
#define CLRS_NOT_REDUNDANT         0
#define CLRS_REDUNDANT             1
#define CLRS_CRITICAL              2

/* Possible values for cgi_RedundancyType */
#define CLRT_NOT_DEFINED       0
#define CLRT_ACTIVE_ACTIVE     1
#define CLRT_ACTIVE_STANDBY    2

/* Possible values for mci_ReadinessStatus */
#define CRT_ACTIVE         0x00
#define CRT_STANDBY        0x01
#define CRT_MAINTENANCE    0x02
#define CRT_MISSING        0xFC
#define CRT_SHUTDOWN       0xFD
#define CRT_NOT_ACCESSABLE 0xFE
#define CRT_UNKNOWN        0xFF



/* PMIC_CLIQUE_GET_SETTINGS */
/* PMIC_CLIQUE_SET_SETTINGS */

typedef struct micCliqueGetSetSettingsCmd
{
    u8          cgss_ScsiOpCode;
    u8          cgss_MicSignature;
    u16         cgss_MicOpCode;
    u8          cgss_UniqueCmdId;
    u8          cgss_LoginKey;
    u16         cgss_Reserved0;
    u16         cgss_Reserved1;
    u16         cgss_TransferLength;
    u16         cgss_TransferOffset;
    u8          cgss_Reserved2;
    Control_t   cgss_Control;
} PACKED micCliqueGetSetSettingsCmd_t;

typedef struct micCliqueSettings
{
    u8      cs_RedundancyType;
    u8      cs_Reserved[127];
}  PACKED micCliqueSettings_t;

/* Possible values for cs_RedundancyType same as */
/* cgi_RedundancyType mentioned above            */
/* all types of request use the same MIC structure below */
typedef struct SAS_MIC_
{
    u8          sm_ScsiOpCode;
    u8          sm_MicSignature;
    u16         sm_MicOpCode;
    u8          sm_UniqueCmdId;
    u8          sm_PageCode;
    u8          sm_Reserved0;
    u16         sm_Reserved1;
    u8          sm_UnitID; /* is also the external port id */
    u16         sm_TransferLength;
    u16         sm_TransferOffset;
    u8          sm_ControllerID; /* controller id */
    Control_t   sm_Control;
} PACKED micSASGetInfoCmd_t, micSASGetParamCmd_t,
    micSASSetParamCmd_t, SAS_MIC_T;

/* PMIC_GENERIC_FE_CLEAR_STATS  */
typedef struct micGenericFEClearStats
{
    u8          gfcs_ScsiOpCode;
    u8          gfcs_MicSignature;
    u16         gfcs_MicOpCode;
    u8          gfcs_UniqueCmdId;
    u8          gfcs_Reserved0;
    u8          gfcs_Reserved1;
    u8          gfcs_Reserved2;
    u8          gfcs_Reserved3;
    u8          gfcs_UnitID; /* is also the external port id */
    u16         gfcs_TransferLength;
    u16         gfcs_TransferOffset;
    u8          gfcs_ControllerID; /* controller id */
    Control_t   gfcs_Control;
} PACKED micGenericFEClearStats_t;

/* PMIC_FWUPD_EXECUTE */
typedef struct micFwUpdateExecute
{
    u8          fue_ScsiOpCode;
    u8          fue_MicSignature;
    u16         fue_MicOpCode;
    u8          fue_ConfigLock;
    u8          fue_LoginKey;
    u32         fue_TotalLength;     /* in byte. For FWUPD_EXECUTE_INIT only */
    u16         fue_TransferLength;  /* = 0 */
    u16         fue_TransferOffset;  /* = 0 */
    u8          fue_SubOpCode;
    Control_t   fue_Control;
} PACKED micFwUpdateExecute_t;

/*
 * INIT    : To initialize the firmware update process, firmware shall
 *           allocate a temporal resource.
 * VALIDATE: To VALIDATE the image that already transferred to the controller
 *           by calculating and comparing checksum.
 * START   : Start flashing the firmware image onto the flash.
 * FINISH  : To cancel or finish the firmware update process, firmware shall
 *           release the related resource.
 */
#define FWUPD_EXECUTE_INIT       0x00
#define FWUPD_EXECUTE_VALIDATE   0x01
#define FWUPD_EXECUTE_START      0x02
#define FWUPD_EXECUTE_FINISH     0x03

/* PMIC_FWUPD_TRANSFER_IMG */
typedef struct micFwUpdateTransferImg
{
    u8          futi_ScsiOpCode;
    u8          futi_MicSignature;
    u16         futi_MicOpCode;
    u8          futi_ConfigLock;
    u8          futi_LoginKey;
    u32         futi_Reserved0;
    u16         futi_TransferLength; /* in byte */
    u16         futi_TransferOffset; /* in FWUPD_OFFSET_IN_XXX */
    u8          futi_Reserved1;
    Control_t   futi_Control;        /* FWUPD_OFFSET_IN_XXX */
} PACKED micFwUpdateTransferImg_t;

/* value of futi_Control.c_OffsetControl */
#define FWUPD_OFFSET_IN_BYTE 0
#define FWUPD_OFFSET_IN_512B 1
#define FWUPD_OFFSET_IN_1KB  2
#define FWUPD_OFFSET_IN_4KB  3

/* PMIC_FWUPD_GET_STATUS */
typedef struct micFwUpdateGetStatus
{
    u8          fugs_ScsiOpCode;
    u8          fugs_MicSignature;
    u16         fugs_MicOpCode;
    u8          fugs_ConfigLock;
    u8          fugs_LoginKey;
    u32         fugs_Reserved0;
    u16         fugs_TransferLength; /* in byte */
    u16         fugs_TransferOffset; /* in byte */
    u8          fugs_Reserved1;
    Control_t   fugs_Control;
} PACKED micFwUpdateGetStatus_t;

typedef struct
{
    u8 fp_u8Status;
    u8 fp_u8Reserved;
    u8 fp_u8Stage;
    u8 fp_u8Percentage;
/* the following 4 bytes are for controller 1 flash progress, applicable for E-Class only */
    u8 fp_u8Status1;
    u8 fp_u8Stage1;
    u8 fp_u8Percentage1;
    u8 fp_u8Reserved2;
}  PACKED micFlashProgress_t;

#define FLASH_STATUS_OK          0
#define FLASH_STATUS_ERROR       1
#define FLASH_STATUS_ABORTED     2
#define FLASH_STATUS_UNKNOWN     3

#define FLASH_STAGE_XFERING      0
#define FLASH_STAGE_XFERED       1
#define FLASH_STAGE_VALIDATING   2
#define FLASH_STAGE_VALIDATED    3
#define FLASH_STAGE_FLASHING     4
#define FLASH_STAGE_FLASHED      5
#define FLASH_STAGE_READY        6
#define FLASH_STAGE_UNKNOWN      7

/* MIC Command List */
typedef union MicCommandList
{
    MicCmd_t                            GeneralMicCommand;
    micSubsystemGetInfoCmd_t            SubsystemGetInfoCmd;
    micCtlGetSetSettingsCmd_t           CtlGetSetSettingsCmd;
    micArrayCreateConfigCmd_t           micArrayCreateConfigCmd;
    micArrayGetConfigCmd_t              micArrayGetConfigCmd;
    micArrayDeleteConfigCmd_t           micArrayDeleteConfigCmd;
    micLogicalDriveAddCmd_t             micLogicalDriveAddCmd;
    micLogicalDriveDeleteCmd_t          micLogicalDriveDeleteCmd;
    micMediaPatrolAllCmd_t              micMediaPatrolAllCmd;
    micArrayMigrateConfigCmd_t          micArrayMigrateConfigCmd;
    micArrayMigrateGetProgCmd_t         micArrayMigrateGetProgCmd;
    micLdiCmd_t                         micLdiCmd;
    micLdiQuickStartCmd_t               micLdiQuickStartCmd;
    micRebuildStartCmd_t                micRebuildStartCmd;
    micRebuildOtherCmd_t                micRebuildOtherCmd;
    micBKSyncAllCmd_t                   micBKSyncAllCmd;
    micEventClearLogCmd_t               micEventClearLogCmd;
    micEventDisableLoggingCmd_t         micEventDisableLoggingCmd;
    micEventEnableLoggingCmd_t          micEventEnableLoggingCmd;
    micEventGetCmd_t                    micEventGetCmd;
    micEventGetEventInfoCmd_t           micEventGetEventInfoCmd;
    micEventGetSettingsCmd_t            micEventGetParametersCmd;
    micEventResetEventInfoCmd_t         micEventResetEventInfoCm;
    micEventSetEventInfoCmd_t           micEventSetEventInfoCmd;
    micEventSetSettingsCmd_t            micEventSetParametersCmd;
    micRckCmd_t                         micRckCmd;
    micPTCmd_t                          micPassThroughCmd;
    micISCSIGetParamsInfoCmd_t          micISCSIGetParamsCmd;
    micISCSISetParamsCmd_t              micISCSISetParamsCmd;
    micEncCmd_t                         micEnclosureCmd;
    micGetErrTableCmd_t                 micGetErrTableCmd;
    MicCmdGetSasTopology_t              micGetSasTopologyCmd;
    micFwUpdateExecute_t                micFwUpdateExecuteCmd;
    micFwUpdateTransferImg_t            micFwUpdateTransferImgCmd;
    micFwUpdateGetStatus_t              micFwUpdateGetStatusCmd;
}  PACKED MicCommandList_t;

#ifdef LUNCOPY
/* storage services related MIC commands and response structures*/
//PMIC_CREATE_ASSOCIATION
typedef struct micStSvcCreateAssocnCmd
{
   u8          sca_ScsiOpCode;
   u8          sca_MicSignature;
   u16         sca_MicOpCode;
   u8          sca_ConfigLock;
   u8          sca_LoginKey;
   u16         sca_SrcLDFlatID;
   u16         sca_DestLDFlatID;  // if  0xffff means data buffer asociated will have the data
   u16         sca_TransferLength;
   u16         sca_TransferOffset;
   u8          sca_AssnType:7;      // see below
   u8          sca_ClrAssnAftCpy:1; //if this bit is set, assn will be cleared automatically after the copy
   Control_t   sca_Control;
} PACKED micStSvcCreateAssocnCmd_t;


/* type of assocaiotn applicable */
#define MAX_ASSCN_PER_LD          0x08
#define MAX_ASSCN_TYPES           0x7f
#define ASSICATION_TYPE_CLONE     0x01
#define ASSICATION_TYPE_SNAPSHOT  0x02
#define MAX_CONCURRENT_LDCOPY     0x08
// data assocaited with the above command if any
typedef struct micAssociationDestinationInfo
{
   u16 adl_DestinationLDFlatID;
   u16 adl_reserved;
   u8 adl_reserved1[4];
}  PACKED micAssocDestLD_t;

typedef struct micCopyCmdData
{
   micAssocDestLD_t  DestinationLD[1];   // this is variblae array, depth would be indicated by transfer length in CDB
}  PACKED micCopyCommandData_t;
//PMIC_DELETE_ASSOCIATION
typedef struct micStSvcDeleteAssocnCmd
{
   u8          sda_ScsiOpCode;
   u8          sda_MicSignature;
   u16         sda_MicOpCode;
   u8          sda_ConfigLock;
   u8          sda_LoginKey;
   u16         sda_SrcLDFlatID;
   u16         sda_DestLDFlatID;  // if  0xFFFF - all association, if not shoould have valid dest LD ID
   u16         sda_TransferLength;
   u16         sda_TransferOffset;
   u8          sda_Reserved;
   Control_t   sda_Control;
} PACKED micStSvcDeleteAssocnCmd_t;
//no data xfer involved for the above( delete asscn)

//PMIC_START_COPY
//PMIC_STOP_COPY
typedef struct micStSvcStartStopCopy
{
   u8          ssc_ScsiOpCode;
   u8          ssc_MicSignature;
   u16         ssc_MicOpCode;
   u8          ssc_ConfigLock;
   u8          ssc_LoginKey;
   u16         ssc_SrcLDFlatID;
   u16         ssc_DestLDFlatID;  // if  0xFFFF - all association, if not shoould have valid dest LD ID
   u16         ssc_TransferLength;
   u16         ssc_TransferOffset;
   u8          ssc_Reserved;
   Control_t   ssc_Control;
} PACKED micStSvcStartStopCopyCmd_t;
//no data xfer involved for the above( start or stop copy)

//PMIC_GET_COPY_PROGRESS
typedef struct micStSvcGetCopyProgress
{
   u8          sgpc_ScsiOpCode;
   u8          sgpc_MicSignature;
   u16         sgpc_MicOpCode;  //get progress
   u8          sgpc_UniqueCmdId;
   u8          sgpc_LoginKey;
   u16         sgpc_NumAssocn;   // either 1 or all ( no other values allowed )
   u16         sgpc_SrcLDFlatID; // 0xFFFF would be all active copy in subsystem
   u16         sgpc_TransferLength;
   u16         sgpc_TransferOffset;
   u8          sgpc_Reserved1;
   Control_t   sgpc_Control;
} PACKED micStGetCopyProgressCmd_t;
//no data xfer involved for the above( Getcopyprogress)
// response strcuture is below
typedef struct micCopyProgressForEachLD
{
    u32 cpy_SourceLDFlatID;
    u16 cpy_DestinationLdFlatID;
    u8  cpy_CopyState;  // Copy active, Copy Queued, copy paused
    u8  cpy_ProgressInPercentage;
}  PACKED micCopyProgressForEachLD_t;

typedef struct micCopyProgress
{
	u32 NumLDsReported;
   micCopyProgressForEachLD_t CopyProgressOnEach[1]; // this would run upto NumLDsReported
}  PACKED micCopyProgress_t;

//PMIC_GET_ASSOCIATION_INFO
typedef struct micStSvcGetAsscnInfo
{
   u8          sgai_ScsiOpCode;
   u8          sgai_MicSignature;
   u16         sgai_MicOpCode;     //get progress
   u8          sgai_UniqueCmdId;
   u8          sgai_LoginKey;
   u16         sgai_NumAssociations;    //either 1 or all ( no other values allowed )
   u16         sgai_SrcLDFlatID;   //0xFF all assocn of requested type in the controller
   u16         sgai_TransferLength;
   u16         sgai_TransferOffset;
   u8          sgai_AssocnType;
   Control_t   sgai_Control;
} PACKED micStGetAsscnInfoCmd_t;

/* response structure for the above command */
typedef struct DestLDInfo
{
   u16  dli_DestinationLDFlatID;
   u8   dli_CopyStatus;             //active, queued, paused, failed etc
   u8   dli_AssociationType;        // Snapshot or Clone look for ASSICATION_TYPE_CLONE etc
   u32  dli_CopyCompletedTimeStamp; //last known copy completed timestamp which Time in seconds (since 1970-01-01 00:00:00).
   u8   dli_CopyProgressInPercentage;// if Copy was active on this LD.
   u8   dli_DestAssociationHealth; // see below
   u8   dli_LastCopyStartFailureSenseKey;
   u8   dli_Reserved[5];
} PACKED DestLDInfo_t;

typedef struct micLDAssociationInfoDetail
{
    u16 cpy_SourceLDFlatID;
    u16 cpy_NumAssociationsOnThisLD;
    u8  cpy_CopyState;  // if any of the Copy active, Copy Queued, copy paused
    u8  cpy_AssociationHealth; //good-0, inconsistent, etc.
#define ASSOCIATION_GOOD                           0x00 // all present
#define ASSOCIATION_DISJOINT_MISSING_SRC     0x01 // source mising
#define ASSOCIATION_DISJOINT_MISSING_DEST    0x02 // desti mising
#define ASSOCIATION_INCOHERENT_SRC         0x03 // Src does not have Dest LD info
#define ASSOCIATION_INCOHERENT_DEST        0x04 // Dest does not have Src LD info
    u8  cpy_reserved[2];
   DestLDInfo_t cpy_DestinationLdDetails[1]; // this would go till the NumAssociations
} PACKED micLDAssociationInfoDetail_t;

typedef struct micAllAssociationInfo
{
   u32 NumSourceLunsInCtrl; /* would be 1 if requested LD is source. Would be 2, if requested LD is both source and target, would whatever in controller if requested LD is 0xFF*/
   micLDAssociationInfoDetail_t EachSourceAssociationInfo[1]; // go till NumSourceLunsInCtrl
} PACKED micAllAssociationInfo_t;


typedef struct micSenseDatForEachDestLD
{
   u16 DestLdId;
   u8 SenseData;
   u8 Reserved;
}PACKED micSenseDatForEachLD_t;

typedef struct lcMicSenseBuffer
{
   micSenseDatForEachLD_t sensedataForEachLD[8];     //32bytes
   u16 SourceLdId; // this would run upto NumLDsReported 34
   u16 NumberofAssnFailed;//36
   u8 Reserved[10]; //46 bytes
} PACKED lcMicSenseBufferData_t;


/*
 * Defragmentation operation structures
 */

/* Defragmentation Type */

#define DEFRAG_TYPE_FRONT          1

/* Defragmentation Flags */

#define DEFRAG_START               0x1
#define DEFRAG_ENDCOMMIT           0x2


/* PMIC_DEFRAG_ARRAY */
typedef struct micArrayDefragConfigCmd
{
    u8          dfac_ScsiOpCode;
    u8          dfac_MicSignature;
    u16        dfac_MicOpCode;
    u8          dac_ConfigLock;
    u8          dfac_LoginKey;
    u8          dfac_DefragType;
    u8          dfac_DefragFlag;
    u16        dfac_DefragDAFlatID;
    u16        dfac_TransferLength;
    u16        dfac_TransferOffset;
    u8          dfac_Reserved1;
    Control_t   dfac_Control;
} PACKED  micArrayDefragConfigCmd_t;

/* PMIC_GET_DEFRAG_PROGRESS */
typedef struct micArrayDefragGetProgCmd
{
    u8          gdfp_ScsiOpCode;
    u8          gdfp_MicSignature;
    u16         gdfp_MicOpCode;
    u8          gdfp_UniqueCmdId;
    u8          gdfp_LoginKey;
    u16         gdfp_StartArrayID;
    u16         gdfp_Reserved0;
    u16         gdfp_TransferLength;
    u16         gdfp_TransferOffset;
    u8          gdfp_ArrayCount;
    Control_t   gdfp_Control;
} PACKED  micArrayDefragGetProgCmd_t;

/* Data for get profress defrag */

typedef struct micDefragProgress
{
    /* general info */
    u16 dp_ArrayID;
    u16 dp_LogDrvId;
    u16 dp_OverallPercentage;
    u8  dp_State;
    u8  dp_Type;
    u32 dp_Reserved1;                       /* Please change all to dp_ */
    u32 dp_Reserved2;
    u64 dp_Reserved3;
    u64 dp_Reserved4;
    u64 dp_Reserved5;

    /* reserved */
    u64 dp_Reserved6;
    u64 dp_Reserved7;
    u64 dp_Reserved8;
    u64 dp_Reserved9;
    u64 dp_Reserved10;

    u64 dp_Reserved11;
    u64 dp_Reserved12;
    u64 dp_Reserved13;
    u64 dp_Reserved14;
    u64 dp_Reserved15;

    u64 dp_Reserved16;
    u64 dp_Reserved17;
    u64 dp_Reserved18;
    u64 dp_Reserved19;
    u64 dp_Reserved20;

} PACKED  micDefragProgress_t;


//Additional sens keys
#define STSVC_ASC_SRCLD_OFFLINE_OR_RBDLNG         (BGT_MODULE_SPECIFIC_ERROR_START+0x01)
#define STSVC_ASC_TARGETLD_OFFLINE_OR_RBDLNG      (BGT_MODULE_SPECIFIC_ERROR_START+0x02)
#define STSVC_ASC_INVALID_SRCLD                   (BGT_MODULE_SPECIFIC_ERROR_START+0x03)
#define STSVC_ASC_INVALID_LICENSE_FOR_THIS_OP     (BGT_MODULE_SPECIFIC_ERROR_START+0x04)
#define STSVC_ASC_INSUFFICIENT_TARGET_CAPACITY    (BGT_MODULE_SPECIFIC_ERROR_START+0x05)
#define STSVC_ASC_MAX_ASSCN_PRESENT_ON_SRCLD      (BGT_MODULE_SPECIFIC_ERROR_START+0x06)
#define STSVC_ASC_TOO_MANY_ASSCN_REQUESTED        (BGT_MODULE_SPECIFIC_ERROR_START+0x07)
#define STSVC_ASC_ONE_OR_MORE_ASSCN_INVALID       (BGT_MODULE_SPECIFIC_ERROR_START+0x08)
#define STSVC_ASC_COPY_ACTIVE_ON_ASSCN            (BGT_MODULE_SPECIFIC_ERROR_START+0x09)
#define STSVC_ASC_INVALID_SRC_OR_TGT_LD           (BGT_MODULE_SPECIFIC_ERROR_START+0x0a)
#define STSVC_ASC_COPY_NOT_ACTIVE                 (BGT_MODULE_SPECIFIC_ERROR_START+0x0b)
#define STSVC_ONE_OR_MORE_ASSN_FAILED             (BGT_MODULE_SPECIFIC_ERROR_START+0x0c)
#define STSVC_INCOHERENT_OR_DISJOINT_ASSN         (BGT_MODULE_SPECIFIC_ERROR_START+0x0d)
#define STSVC_COPY_QUEUED                         (BGT_MODULE_SPECIFIC_ERROR_START+0x0e)
#endif

#if defined(WINDOWS) || defined(_WINDRIVER)
//#pragma pack (pop, mic_pack, 8)
#pragma pack(pop)  //rock test
//#pragma pack (show)
#endif

#endif
