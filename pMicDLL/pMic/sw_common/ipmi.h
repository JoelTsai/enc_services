#ifndef __IPMI_H
#define __IPMI_H

#ifdef __KERNEL__

typedef struct cbayIPMICMiniRio
{
    struct RIOHeader ipmi_RIOHeader;

    u8* ipmi_dataBuff;
    
    u16 ipmi_dataLen;
    u8  ipmi_commandNo;
    u8  ipmi_reserved;
    
    u32 ipmi_timeout;
#define IPMI_TIMEOUT    (2 * HZ)   /* 2 seconds per ClearBay spec */

} cbayIPMIMiniRio_t;

extern void EnableI2C( u8 PortNumber );
extern void DisableI2C( u8 PortNumber );

extern u8 CbayIPMII2CRegisterInterfaceFunc(
    void(*IPMIInterfaceFunction)( struct RIO* ), u8 CommandNo );
extern void CbayIPMII2CUnRegisterInterfaceFunc( u8 CommandNo );
extern void CbayIMPISendDataToCMMI2C(
    u8* databuff, u16 datalength, RIO_t* IPMIMiniRio );
extern void IPMIFreeMiniRioAndDataBuffer( RIO_t* RioPtr );


u32 ipmi_Init( void );
u32 ipmi_DeInit( void );

int ipmi_IOCTL( struct file* pFile, unsigned long Data );
int ipmi_Release( struct file* pFile );

#endif  /* __KERNEL__ */

#define MAX_TOTAL_IPMI_RESPONSE_LENGTH 512
#define IOCTL_IPMI_BRIDGE       (0x55d1)

typedef struct
{
    unsigned char ir_SubCode;           /* Command Subcode (IN) */
#define IPMI_CMD_SUBCODE_PULL       (0x01)
#define IPMI_CMD_SUBCODE_PUSH       (0x02)
#define IPMI_CMD_SUBCODE_REGISTER   (0xF0)
#define IPMI_CMD_SUBCODE_UNREGISTER (0xF1)
#define IPMI_CMD_SUBCODE_ENABLE     (0xF8)
#define IPMI_CMD_SUBCODE_DISABLE    (0xF9)
#ifndef NDEBUG
#define IPMI_CMD_SUBCODE_INJECT     (0xFE)
#endif
#define IPMI_CMD_SUBCODE_RESET      (0xFF)
    unsigned char ir_Option;
    unsigned char Rsvd[2];

    unsigned short ir_BufferLen;        /* Buffer Size (IN) */
    unsigned short ir_Residual;         /* Residual (OUT) */

    void* ir_pUserBuffer;

} IPMI_Req_t;

typedef struct
{
    u8 icr_Cmd;
    u8 Rsvd[2];
    u8 icr_Options;
#define IPMI_CMD_ENTRY_REGISTERED   (0x01)
#define IPMI_CMD_ENTRY_PRIMARY_ONLY (0x80)

    u16 icr_CmdLength;
    u16 icr_RspLength;

} IPMI_CmdEntry_t;

typedef struct
{   /* This structure is to be populated
     * in network format (i.e. Big Endian) */
    u8 ipv_Addr[4]; /* IP Address */
    u8 ipv_Mask[4]; /* IP Net Mask */
    u8 ipv_DfGW[4]; /* Default Gateway */

} IPv4_Value_t;

#define IPMI_CMD_GET_DEV_INFO           (0x00)
#define IPMI_CMD_SET_IPV4_ADDR          (0x01)
#define IPMI_CMD_GET_IPV4_ADDR          (0x02)
#define IPMI_CMD_GET_THERMAL_READING    (0x03)
#define IPMI_CMD_START_FW_XFER          (0x04)
#define IPMI_CMD_RESTART_SCM            (0x05)
#define IPMI_CMD_GET_DRIVE_INFO         (0x06)
#define IPMI_CMD_GET_IDROM_INFO         (0x08)
#define IPMI_CMD_READ_IDROM             (0x09)
#define IPMI_CMD_WRITE_IDROM            (0x0A)

#define IPMI_CMD_SET_WAITMO             (0x0B)
#define IPMI_CMD_PROCEED                (0x0C)
#define IPMI_CMD_RESTART_SCM_MODEL2     (0x0D)
#define IPMI_CMD_GET_LED_STS            (0x0E)
#define IPMI_CMD_GET_FWUPDT_STS         (0x0F)
#define IPMI_CMD_GET_REBOOT_COUNT       (0x10)
#define IPMI_CMD_RESTART_SCM_TANDEM     (0x11)

#define MAX_IPMI_CMD                    (0xFF)

#define IPMI_ADDR_TYPE_PRIVATE              (0x00)
#define IPMI_ADDR_TYPE_VIRTUAL              (0x01)

#define IPMI_RSP_SUCCESS                        (0x00)
#define IPMI_RSP_FAILED                         (0x01)
#define IPMI_RSP_FW_XFER_FAILED                 (IPMI_RSP_FAILED)
#define IPMI_RSP_RESTART_FAILED                 (IPMI_RSP_FAILED)
#define IPMI_RSP_RESTART_IN_PROGRESS            (0x02)
#define IPMI_RSP_RESTART_UNSUPPORTED            (0x03)
#define IPMI_RSP_INTERNAL_ERROR                 (0xC7)
#define IPMI_RSP_BAD_OFFSET                     (0xC9)
#define IPMI_RSP_DATA_UNAVAILABLE               (0xCB)
#define IPMI_RSP_INVALID                        (0xCC)
#define IPMI_RSP_INVALID_ADDR_TYPE              (IPMI_RSP_INVALID)
#define IPMI_RSP_INVALID_REQ_TYPE               (IPMI_RSP_INVALID)
#define IPMI_RSP_INFO_UNAVAILABLE               (IPMI_RSP_INVALID)
#define IPMI_RSP_INVALID_IDROM_NO               (IPMI_RSP_INVALID)
#define IPMI_RSP_INVALID_XFER_SIZE              (IPMI_RSP_INVALID)
#define IPMI_RSP_CMD_INVALID                    (0xD5)

typedef struct
{
    u8 igc_SeqNo;   /* Sequence Number */
    u8 igc_Cmd;     /* Command Code */

} __attribute__((packed)) IPMI_GenericCmd_t;

typedef struct
{
    u8 igr_SeqNo;   /* Sequence Number */
    u8 igr_Cmd;     /* Command Code */
    u8 igr_RspCode;

} __attribute__((packed)) IPMI_GenericRsp_t;

typedef struct      /* Get Device Information Command */
{
    u8 igdic_SeqNo; /* Sequence Number */
    u8 igdic_Cmd;   /* Command Code (0x00) */

} __attribute((packed)) IPMI_GetDeviceInfo_Cmd_t;

typedef struct
{
    u8  vi_Build;
    u16 vi_OEM;
    u8  vi_Minor;
    u8  vi_Major;

} __attribute((packed)) VerInfo_t;

typedef struct      /* Get Device Information Response */
{
    u8 igdir_SeqNo; /* Sequence Number */
    u8 igdir_Cmd;   /* Command Code (0x00) */

    u8 igdir_RspCode;   /* 0x00 Successful */

    u8 igdir_CmdRevCode;
#define IPMI_DEV_INFO_CMD_REV_CODE          (0x01)
    u8 igdir_ModuleID_Minor;
    u8 igdir_ModuleID_Major;
#define IPMI_DEV_INFO_MODULE_ID_MINOR       (0x2F)
#define IPMI_DEV_INFO_MODULE_ID_MAJOR       (0x00)
    u8 igdir_Mode;      /* 0x00 Operational FW Active
                           0x01 Recovery FW Active
                           0x02 FW Maintenance Mode
                           0x03 Recovery FW Error */
#define IPMI_DEV_INFO_MODE_NORMAL           (0x00)
#define IPMI_DEV_INFO_MODE_RECOVERY         (0x01)
#define IPMI_DEV_INFO_MODE_MAINTENANCE      (0x02)
#define IPMI_DEV_INFO_MODE_RECOVERY_ERROR   (0x03)
    /* Additional Mode Information */
    u8 igdir_AMI;               /* igdir_Mode = Operational FW Active
                                   0x00 Non-Redundant PRIMARY
                                   0x01 Redundant PRIMARY
                                   0x02 Redundant SECONDARY
                                   0x03 Critical PRIMARY
                                   0x04 Fail Over In Progress
                                   0x05 Fail Back In Progress */
#define IPMI_DEV_INFO_MODE_AMI_SINGLE       (0x00)
#define IPMI_DEV_INFO_MODE_AMI_PRIMARY      (0x01)
#define IPMI_DEV_INFO_MODE_AMI_SECONDARY    (0x02)
#define IPMI_DEV_INFO_MODE_AMI_CRITICAL     (0x03)

#define IPMI_DEV_INFO_MODE_AMI_FAILOVER     (0x04)
#define IPMI_DEV_INFO_MODE_AMI_FAILBACK     (0x05)
                                /* igdir_Mode = FW Maintenance Mode
                                   0x00 Not Applicable
                                   0x01 HW version Mismatch
                                   0x02 FW version Mismatch
                                   0x03 Memory Size Mismatch
                                   0x04 PD Table Mismatch
                                   0x05 Peer FW Update in Progress
                                   0x06 Maintenance Mode by CMM Request */
#define IPMI_DEV_INFO_MODE_AMI_NA           (0x00)
#define IPMI_DEV_INFO_MODE_AMI_HW_MISMATCH  (0x01)
#define IPMI_DEV_INFO_MODE_AMI_FW_MISMATCH  (0x02)
#define IPMI_DEV_INFO_MODE_AMI_MEM_MISMATCH (0x03)
#define IPMI_DEV_INFO_MODE_AMI_PD_MISMATCH  (0x04)
#define IPMI_DEV_INFO_MODE_AMI_FW_UPDT_INP  (0x05)
#define IPMI_DEV_INFO_MODE_AMI_BY_REQUEST   (0x06)
#define IPMI_DEV_INFO_MODE_AMI_PEER_FW_MISMATCH   (0x07)
#define IPMI_DEV_INFO_MODE_AMI_UNREPORTABLE (0xFF)
                                /* igdir_Mode = Recovery FW Error
                                   0x00 Not Applicable
                                   0x01 Flash Image corrupted
                                   0x02 Flash Device error
                                   0x03 Internal Diatnostic Error
                                   0x04 Internal Diatnostic Error
                                   0x05 Internal Diatnostic Error */
#define IPMI_DEV_INFO_MODE_AMI_BAD_IMG      (0x01)
#define IPMI_DEV_INFO_MODE_AMI_BAD_DEV      (0x02)
#define IPMI_DEV_INFO_MODE_AMI_INTRNL_ERR3  (0x03)
#define IPMI_DEV_INFO_MODE_AMI_INTRNL_ERR4  (0x04)
#define IPMI_DEV_INFO_MODE_AMI_INTRNL_ERR5  (0x05)

    VerInfo_t igdir_OperationModeFwVer;

} __attribute((packed)) IPMI_GetDeviceInfo_Rsp_t;

typedef struct      /* Set IPv4 Address Command */
{
    u8 isiac_SeqNo; /* Sequence Number */
    u8 isiac_Cmd;   /* Command Code (0x01) */
    u8 isiac_AddrType;  /* 0x00 Private IP Address
                           0x01 Virtual IP Address */

    IPv4_Value_t isiac_IPv4Addr;

} __attribute__((packed)) IPMI_SetIPv4Addr_Cmd_t;

typedef struct      /* Set IPv4 Address Response */
{
    u8 isiar_SeqNo; /* Sequence Number */
    u8 isiar_Cmd;   /* Command Code (0x01) */
    u8 isiar_RspCode;   /* 0x00 Successful
                           0xCC Invalid Address Type */

} __attribute__((packed)) IPMI_SetIPv4Addr_Rsp_t;

typedef struct      /* Get IPv4 Address Command */
{
    u8 igiac_SeqNo; /* Sequence Number */
    u8 igiac_Cmd;   /* Command Code (0x02) */
    u8 igiac_AddrType;  /* 0x00 Private IP Address
                           0x01 Virtual IP Address */

} __attribute__((packed)) IPMI_GetIPv4Addr_Cmd_t;

typedef struct      /* Get IPv4 Address Response */
{
    u8 igiar_SeqNo; /* Sequence Number */
    u8 igiar_Cmd;   /* Command Code (0x02) */
    u8 igiar_RspCode;   /* 0x00 Successful
                           0xCB Not Available */

    IPv4_Value_t igiar_IPv4Addr;

} __attribute__((packed)) IPMI_GetIPv4Addr_Rsp_t;

typedef struct      /* Get Temperature Sensor Command */
{
    u8 igtsc_SeqNo; /* Sequence Number */
    u8 igtsc_Cmd;   /* Command Code (0x03) */

    u8 igtsc_Sensor;    /* 0x00 CPU Temperature
                           0x01 Inlet Air Temperature
                           0x02 Interposer Air Temperature */
#define IPMI_SENSOR_TYPE_CPU                (0x00)
#define IPMI_SENSOR_TYPE_INLET              (0x01)
#define IPMI_SENSOR_TYPE_INTERPOSER         (0x02)

} __attribute__((packed)) IPMI_GetTempSensor_Cmd_t;

typedef struct      /* Get Temperature Sensor Response */
{
    u8 igtsr_SeqNo; /* Sequence Number */
    u8 igtsr_Cmd;   /* Command Code (0x03) */

    u8 igtsr_RspCode;   /* 0x00 Successful
                           0xD5 Command Invalid */
    u8 igtsr_TempC;     /* Temperature in 'C,
                           below ZERO should return ZERO */

} __attribute__((packed)) IPMI_GetTempSensor_Rsp_t;

typedef struct      /* Initiate FW Image Xfer Command */
{
    u8 isfxc_SeqNo; /* Sequence Number */
    u8 isfxc_Cmd;   /* Command Code (0x04) */

    u8 isfxc_HostAddr[4];   /* Host IP Address (Big Endian) */
    u8 isfxc_HostPort[2];   /* Host Port Number (Little Endian) */

    u8 isfxc_ImgSize[4];    /* Image Size (Little Endian) */
    u8 isfxc_ImgName[0];    /* Image File Name */

} __attribute__((packed)) IPMI_StartFWxfer_Cmd_t;

typedef struct      /* Initiate FW Image Xfer Response */
{
    u8 isfxr_SeqNo; /* Sequence Number */
    u8 isfxr_Cmd;   /* Command Code (0x04) */
    u8 isfxr_RspCode;   /* 0x00 Successful
                           0x01 Failed */

} __attribute__((packed)) IPMI_StartFWxfer_Rsp_t;

typedef struct
{
    u8 irsc_SeqNo;  /* Sequence Number */
    u8 irsc_Cmd;    /* Command Code (0x05) */

    u8 irsc_ReqType;        /* Restart Request Type */
#define IPMI_RESTART_TYPE_CLEAN             (0xA5)
#define IPMI_RESTART_TYPE_FORCE             (0x5A)

} __attribute__((packed)) IPMI_RestartSCM_Cmd_t;

typedef struct
{
    u8 irsr_SeqNo;  /* Sequence Number */
    u8 irsr_Cmd;    /* Command Code (0x05) */

    u8 irsr_RspCode;    /* 0x00 Successful
                           0x01 Failed
                           0x02 In Progress
                           0xcc Invalid Request Type */

} __attribute__((packed)) IPMI_RestartSCM_Rsp_t;

typedef struct
{
    u8 irsc_SeqNo;  /* Sequence Number */
    u8 irsc_Cmd;    /* Command Code (0x05) */

    u8 irsc_ReqType;        /* Restart Request Type */
#define IPMI_RESTART_TYPE_CLEAN             (0xA5)
#define IPMI_RESTART_TYPE_FORCE             (0x5A)
    u8 irsc_NxtBoot;        /* Next Boot Type */
#define IPMI_BOOT_TYPE_NORMAL               (0x00)
#define IPMI_BOOT_TYPE_MAINTENANCE          (0x01)

} __attribute__((packed)) IPMI_RestartSCM2_Cmd_t;
typedef IPMI_RestartSCM_Rsp_t IPMI_RestartSCM2_Rsp_t;

typedef IPMI_RestartSCM2_Cmd_t IPMI_RestartSCM3_Cmd_t;
typedef IPMI_RestartSCM_Rsp_t  IPMI_RestartSCM3_Rsp_t;

typedef struct
{
    u8 igdic_SeqNo; /* Sequence Number */
    u8 igdic_Cmd;   /* Command Code (0x06) */

} __attribute__((packed)) IPMI_GetDriveInfoCmd_t;

typedef struct
{
    u8 igdir_SeqNo; /* Sequence Number */
    u8 igdir_Cmd;   /* Command Code (0x06) */

    u8 igdir_RspCode;   /* 0x00 Successful
                           0xcc Information Unavailable */

    u8 igdir_DrvBaySts[0];  /* 0x00 - 0x7f Drive Present, Temperature in degree C
                               0x80 - 0xfd Unused/Invalid
                               0xfe        Drive Present, Temperature Unavailable
                               0xff        Drive Absent */
#define IPMI_DRVBAYSTS_TEMP_UNAVAIL         (0xFE)
#define IPMI_DRVBAYSTS_DRV_ABSENT           (0xFF)

} __attribute__((packed)) IPMI_GetDriveInfoRsp_t;

typedef struct
{
    u8 igiic_SeqNo; /* Sequence Number */
    u8 igiic_Cmd;   /* Command Code (0x08) */

    u8 igiic_IDROM_No;          /* IDROM No. to retrieve information on */

} __attribute__((packed)) IPMI_GetIDROMInfoCmd_t;

typedef struct
{
    u8 igiir_SeqNo; /* Sequence Number */
    u8 igiir_Cmd;   /* Command Code (0x08) */

    u8 igiir_RspCode;   /* 0x00 Successful
                           0xcc IDROM No. Invalid/Out of Range */
    u8 igiir_IDROM_Count;

    /* RspCode other than ZERO (successful)
       does NOT return the following 3 bytes */
    u8 igiir_IDROM_Info;
    u8 igiir_IDROM_Size[2];     /* Size of IDROM (Little Endian) */

} __attribute__((packed)) IPMI_GetIDROMInfoRsp_t;

typedef struct
{
    u8 iric_SeqNo;  /* Sequence Number */
    u8 iric_Cmd;    /* Command Code (0x09) */

    u8 iric_IDROM_No;           /* IDROM No. to read from */
    u8 iric_IDROM_Offset[2];    /* Offset into IDROM to read from (Little Endian) */
    u8 iric_Xfer_Size[2];       /* Number of bytes to read (Little Endian) */

} __attribute__((packed)) IPMI_ReadIDROMCmd_t;

typedef struct
{
    u8 irir_SeqNo;  /* Sequence Number */
    u8 irir_Cmd;    /* Command Code (0x09) */

    u8 irir_RspCode;    /* 0x00 - Successful
                           0xc9 - Bad Offset
                           0xcc - Invalid IDROM No. or Xfer Size */

    u8 irir_IDROM_No;           /* IDROM No. read from */
    /* RspCode other than ZERO (successful)
       does NOT return the data */
    u8 irir_IDROM_Data[0];      /* IDROM Data */
    
} __attribute__((packed)) IPMI_ReadIDROMRsp_t;

typedef struct
{
    u8 iwic_SeqNo;  /* Sequence Number */
    u8 iwic_Cmd;    /* Command Code (0x0a) */

    u8 iwic_IDROM_No;           /* IDROM No. to write to */
    u8 iwic_IDROM_Offset[2];    /* Offset int oIDROM to write to (Little Endian) */
    u8 iwic_IDROM_Data[0];      /* IDROM Data */

} __attribute__((packed)) IPMI_WriteIDROMCmd_t;

typedef struct
{
    u8 iwir_SeqNo;  /* Sequence Number */
    u8 iwir_Cmd;    /* Command Code (0x0a) */

    u8 iwir_RspCode;    /* 0x00 - Successful
                           0xc9 - Bad Offset
                           0xcc - Invalid IDROM No. */

} __attribute__((packed)) IPMI_WriteIDROMRsp_t;

typedef struct      /* Get LED Status Command */
{
    u8 iglsc_SeqNo; /* Sequence Number */
    u8 iglsc_Cmd;   /* Command Code (0x00) */

} __attribute((packed)) IPMI_GetLEDstatus_Cmd_t;

typedef struct      /* Get LED Status Response */
{
    u8 iglsr_SeqNo; /* Sequence Number */
    u8 iglsr_Cmd;   /* Command Code (0x00) */

    u8 iglsr_RspCode;   /* 0x00 - Successful */
    u8 iglsr_StsLED;    /* 0x00 Yellow OFF Green OFF
                           0x01 Yellow OFF Green ON
                           0x02 Yellow ON  Green OFF
                           0x03 Yellow ON  Green ON */
#define IPMI_DEV_INFO_LED_BOTH_OFF          (0x00)
#define IPMI_DEV_INFO_LED_GREEN             (0x01)
#define IPMI_DEV_INFO_LED_YELLOW            (0x02)
#define IPMI_DEV_INFO_LED_BOTH_ON           (IPMI_DEV_INFO_LED_GREEN | IPMI_DEV_INFO_LED_YELLOW)

} __attribute((packed)) IPMI_GetLEDstatus_Rsp_t;

typedef struct      /* Get FirmWare Update Status Command */
{
    u8 igfwusc_SeqNo; /* Sequence Number */
    u8 igfwusc_Cmd;   /* Command Code (0x00) */

} __attribute((packed)) IPMI_GetFWupdtStatus_Cmd_t;

typedef struct      /* Get FirmWare Update Status Response */
{
    u8 igfwusr_SeqNo; /* Sequence Number */
    u8 igfwusr_Cmd;   /* Command Code (0x00) */

    u8 igfwusr_RspCode;   /* 0x00 - Successful */

    u8 igfwusr_FWupdtSts; /* 0x00 Not Applicable
                             0x01 In Progress
                             0x03 Update Successful
                             0x04 Update Failed */
#define IPMI_DEV_INFO_FWUPDT_NA             (0x00)
#define IPMI_DEV_INFO_FWUPDT_INPROGRESS     (0x01)
#define IPMI_DEV_INFO_FWUPDT_SUCCESSFUL     (0x02)
#define IPMI_DEV_INFO_FWUPDT_FAILED         (0x03)

    u8 igfwusr_FWupdtProgress;    /* Firmware Update Percentile */
#ifdef __SUPPORT_ERROR_REPORTING
    u8 igfwusr_FWupdtErr;         /* 0x00 Not Applicable */
#endif
#define IPMI_DEV_INFO_FWUPDT_ERR_NA         (0x00)
#define IPMI_DEV_INFO_FWUPDT_XFER_FAILED    (0x01)
#define IPMI_DEV_INFO_FWUPDT_FLASH_FAILED   (0x02)

} __attribute((packed)) IPMI_GetFWupdtStatus_Rsp_t;

typedef struct
{
    u8 iswtoc_SeqNo; /* Sequence Number */
    u8 iswtoc_Cmd;   /* Command Code */

    u8 iswtoc_TimeOutValue; /* 0xFF No Time Out
                               0x78 120 seconds */

} __attribute((packed)) IPMI_SetWaitTMO_Cmd_t;

typedef struct
{
    u8 iswtor_SeqNo; /* Sequence Number */
    u8 iswtor_Cmd;   /* Command Code */

    u8 iswtor_RspCode;  /* 0x00 - Successful
                           0x01 - Rejected
                           0xcc - Invalid Request */

} __attribute((packed)) IPMI_SetWaitTMO_Rsp_t;

typedef struct
{
    u8 ipsc_SeqNo;  /* Sequence Number */
    u8 ipsc_Cmd;    /* Command Code */

    u8 ipsc_Option;     /* 0x00 Proceed to NORMAL Mode
                         * 0x01 Proceed to MAINTENANCE Mode */

} __attribute((packed)) IPMI_ProceedStartup_Cmd_t;

typedef struct
{
    u8 ipsr_SeqNo;  /* Sequence Number */
    u8 ipsr_Cmd;    /* Command Code */

    u8 ipsr_RspCode;    /* 0x00 - Successful
                           0x01 - Rejected
                           0xcc - Invalid Request */

} __attribute((packed)) IPMI_ProceedStartup_Rsp_t;

typedef struct
{
    u8 igrcc_SeqNo; /* Sequence Number */
    u8 igrcc_Cmd;   /* Command Code */

} __attribute((packed)) IPMI_GetRebootCount_Cmd_t;

typedef struct
{
    u8 igrcr_SeqNo; /* Sequence Number */
    u8 igrcr_Cmd;   /* Command Code */

    u8 igrcr_RspCode;   /* 0x00 - Successful */

    u8 igrcr_Count[2];  /* Reboot Count (Little Endian) */

} __attribute((packed)) IPMI_GetRebootCount_Rsp_t;

#endif  /* __IPMI_H */
