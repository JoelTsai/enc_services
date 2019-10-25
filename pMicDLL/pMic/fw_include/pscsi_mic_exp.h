/*-------------------------------------------------------------------------**
**                                                                         **
**  Filename    : pscsi_mic_exp.h                                          **
**  Description : Stuctures and definitions used exported by PSCSI MGMT    **
**                are defined here.                                        **
**  Created on  : 03/10/2005                                               **
**  Created by  : Santosh Kumar.                                           **
**                                                                         **
**  (C) Copyright Promise Technology Inc., 2005                            **
**  All Rights Reserved.                                                   **
**                                                                         **
**-------------------------------------------------------------------------*/
#ifndef _PSCSI_MIC_EXP_H
#define _PSCSI_MIC_EXP_H

#ifdef ISLAVISTA_VERSION_DEBUG
static char *CVSId = "SId: pscsi_mic_exp.h,v 1.3 2005/02/24 04:39:48 santoshk Exp $";
#endif

/* INCLUDE FILE DECLARATIONS
 */
#include "mic.h"


/* MACRO DEFINE
 */
#define PSCSI_MGMT_MAX_PORTS            2
#define PSCSI_MGMT_MAX_TARGETS          16

#define PSCSI_MGMT_ACCESS_ALL_PORTS     0xFF
#define PSCSI_MGMT_ACCESS_ALL_TARGETS   0xFF


/* PSCSI MIC COMMAND OPCODE
 */
#define PMIC_PSCSI_GET_PORT_INFORMATION         MIC_PSCSI_MGT_ID | 0x0001
#define PMIC_PSCSI_GET_PORT_PARAMETERS          MIC_PSCSI_MGT_ID | 0x0002
#define PMIC_PSCSI_SET_PORT_PARAMETERS          MIC_PSCSI_MGT_ID | 0x0003
#define PMIC_PSCSI_GET_PORT_STATISTICS          MIC_PSCSI_MGT_ID | 0x0004

#define PMIC_PSCSI_GET_TARGET_INFORMATION       MIC_PSCSI_MGT_ID | 0x0010
#define PMIC_PSCSI_GET_TARGET_PARAMETERS        MIC_PSCSI_MGT_ID | 0x0011
#define PMIC_PSCSI_SET_TARGET_PARAMETERS        MIC_PSCSI_MGT_ID | 0x0012
#define PMIC_PSCSI_GET_TARGET_STATISTICS        MIC_PSCSI_MGT_ID | 0x0013

#define PMIC_PSCSI_CLEAR_STATISTICS             MIC_PSCSI_MGT_ID | 0x0020


/*  PSCSI MIC ERROR CODE
 */
#define MICS_INVALID_PSCSI_PORT_ID          (MICS_MODULE_SPECIFIC_ERROR_START + 0x01)
#define MICS_INVALID_PSCSI_DEVICE_ID        (MICS_MODULE_SPECIFIC_ERROR_START + 0x02)


/* EXPORTED STRUCTURE DEFINITION
 */

/* SCSI Command 
 */
typedef struct micPSCSICmd
{
    u8  mpc_ScsiOpCode;     /* common */
    u8  mpc_MicSignature;   /* common */
    u16 mpc_MicOpCode;      /* common */

    union
    {
        u8              mpc_ConfigLock;  /* for write cmd */
        u8              mpc_UniqueCmdId; /* for read cmd */        
    }__attribute__ ((packed)) mpc_u;

    u8  mpc_LoginKey;       /* common */

    u8   mpc_PortID;         /* 0xFF for all ports */
    u8   mpc_TargetID;       /* 0xFF for all devices */
    u8  mpc_Reserved2;      /* reserved */
    u8  mpc_Reserved3;      /* reserved */

    u16 mpc_TransferLength; /* common */
    u16 mpc_TransferOffset; /* common */

    u8  mpc_Reserved4;      /* reserved */

    Control_t mpc_Control;
} __attribute__ ((packed)) micPSCSICmd_t;


/* Config pages definition exposed to user space.
    these definitions will be translated real LSI MPT page
     definitions in pscsi_mpt_intf.c
 */

/* port information */
typedef struct micPSCSIPortInfo
{
    u16  mppi_PortID;

    u16  mppi_MaxSupportedLunsPerTarget;

    u8   mppi_MaxSupportedTransferRate;             /* should be Ultra320 */
#define MPPI_MAX_MODE_U320              (0x01)
#define MPPI_MAX_MODE_U160              (0x02)
#define MPPI_MAX_MODE_U80               (0x03)
#define MPPI_MAX_MODE_U40               (0x04)
#define MPPI_MAX_MODE_U20               (0x05)
#define MPPI_MAX_MODE_U10               (0x06)
#define MPPI_MAX_MODE_U5                (0x07)
#define MPPI_MAX_MODE_UNKNOWN           (0xFF)

    u8   mppi_TerminationStatus;                    /* current termination control status */
#define MPPI_TERM_STATUS_ON             (0x01)
#define MPPI_TERM_STATUS_OFF            (0x02)
#define MPPI_TERM_STATUS_UNKNOWN        (0xFF)

    u8   mppi_Reserved1[2];                         /* Natural alignment */

    u8   mppi_TargetList[PSCSI_MGMT_MAX_TARGETS];   /* currently assigned target ID list to the port */
#define MPPI_TARGET_STATUS_INACTIVE     (0x01)
#define MPPI_TARGET_STATUS_ACTIVE       (0x02)

    /* OnBusTimerValue */
    u32  mppi_OnBusTimerValue;                      /* Bit 0-31 */

    /* PortFlags */
    u8   mppi_TerminationControl;                   /* Bit 4 */
#define MPPI_TERM_CONTROL_AUTO          (0x01)      /* Auto-Termination */
#define MPPI_TERM_CONTROL_OFF           (0x02)      /* Force termination OFF */
#define MPPI_TERM_CONTROL_ON            (0x03)      /* Force termination ON */
#define MPPI_TERM_CONTROL_UNKNOWN       (0xFF)

    u8   mppi_DVControl;                            /* Bit 5-6: Domain Validation Control */
#define MPPI_DVCONTROL_NONE             (0x01)
#define MPPI_DVCONTROL_BASIC            (0x02)
#define MPPI_DVCONTROL_ENHANCED         (0x03)

    u8   mppi_Padding[2];                           /* 64-bits alignment padding */
    u8   mppi_Reserved[32];                         /* reserved for future use */
} micPSCSIPortInfo_t;


/* port settings */
typedef struct micPSCSIPortSettings
{
    u16  mpps_PortID;
    u8   mpps_Reserved1[2];                         /* Natural alignment */

    /* OnBusTimerValue */
    u32  mpps_OnBusTimerValue;                      /* Bit 0-31 */

/* SCSI-SPI Port Page 1 */
    /* Configuration */
    u8   mpps_TargetList[PSCSI_MGMT_MAX_TARGETS];   /* Bit 16-31 */
#define MPPS_TARGET_STATUS_INACTIVE     (0x01)
#define MPPS_TARGET_STATUS_ACTIVE       (0x02)

/* SCSI-SPI Port Page 2 */

    /* PortFlags */
    u8   mpps_TerminationControl;                   /* Bit 4 */
#define MPPS_TERM_CONTROL_AUTO          (0x01)      /* Auto-Termination */
#define MPPS_TERM_CONTROL_OFF           (0x02)      /* Force termination OFF */
#define MPPS_TERM_CONTROL_ON            (0x03)      /* Force termination ON */
#define MPPS_TERM_CONTROL_UNKNOWN       (0xFF)

    u8   mpps_DVControl;                            /* Bit 5-6: Domain Validation Control */
#define MPPS_DVCONTROL_NONE             (0x01)
#define MPPS_DVCONTROL_BASIC            (0x02)
#define MPPS_DVCONTROL_ENHANCED         (0x03)

    u8   mpps_Padding[6];                           /* 64-bits alignment padding */
    u8   mpps_Reserved[32];                         /* reserved for future use */
} micPSCSIPortSettings_t;


/* port statistics */
typedef struct micPSCSIPortStatistics
{
    u16  mppst_PortID;
    u16  mppst_NumberOfConcurrentCmd;   /* current concurrent commands, do we need to split it into R & W */
    u8   mppst_Padding[4];              /* 64-bits alignment padding */
    u8   mppst_Reserved[32];            /* reserved for future use */
} micPSCSIPortStatistics_t;


/* target information */
typedef struct micPSCSITargetInfo
{
#define MPTI_STATUS_ENABLED     1
#define MPTI_STATUS_DISABLED    0

    u16  mpti_PortID;
    u16  mpti_TargetID;

/* SCSI-SPI Device Page 0 */
    /* NegotiatedParameters */
    u8   mpti_InfoUnitStatus;           /* Bit 0: Information Unit */
    u8   mpti_DualTxStatus;             /* Bit 1: Dual Transfer */
    u8   mpti_QASStatus;                /* Bit 2: Quick Arbitrate and Select */
    u8   mpti_HMCSStatus;               /* Bit 3: Hold Margin Control settings */
    u8   mpti_WFCStatus;                /* Bit 4: Write Flow Control */
    u8   mpti_ReadStreamStatus;         /* Bit 5: Read Streaming */
    u8   mpti_RetainTraningInfoStatus;  /* Bit 6: Retain Traning Information */
    u8   mpti_PreCompStatus;            /* Bit 7: Precompensation */
    u16  mpti_NegSyncTxPeriod;          /* Bit 8-15: Negotiated Synchronous Tx Spead */
    u16  mpti_NegSyncOffset;            /* Bit 16-23: Negotiated Synchronous Offset */
    u8   mpti_InlineDataPaddingStatus;  /* Bit 27: Inline Data Padding */
    u8   mpti_Width;                    /* Bit 29: Width */
#define MPTI_WIDTH_NARROW    (0x01)
#define MPTI_WIDTH_WIDE      (0x02)
    u8   mpti_AIPStatus;                /* Bit 31: Asynchronous Information Protection */

    u8   mpti_Reserved1;                /* Natural alignment */

/* Other Info */
    u16  mpti_RunningModeInfo;          /* in which mode the device is running */
#define MPTI_RUNNING_MODE_U5         (0x0005)
#define MPTI_RUNNING_MODE_U10        (0x0010)
#define MPTI_RUNNING_MODE_U20        (0x0020)
#define MPTI_RUNNING_MODE_U40        (0x0040)
#define MPTI_RUNNING_MODE_U80        (0x0080)
#define MPTI_RUNNING_MODE_U160       (0x0160)
#define MPTI_RUNNING_MODE_U320       (0x0320)
#define MPTI_RUNNING_MODE_UNKNOWN    (0xFFFF)

    u8   mpti_Padding[2];               /* 64-bits alignment padding */
    u8   mpti_Reserved[32];             /* reserved for future use */
} micPSCSITargetInfo_t;


/* target settings */
typedef struct micPSCSITargetSettigns
{
#define MPTS_PARAM_STATUS_ENABLED     1
#define MPTS_PARAM_STATUS_DISABLED    0

#define MPTS_PARAM_STATUS_ALLOWED     1 // used for mpts_WDTRStatus and mpts_SDTRStatus
#define MPTS_PARAM_STATUS_DISALLOWED  0

    u16  mpts_PortID;
    u16  mpts_TargetID;

/* SCSI-SPI Device Page 1 */

    /* RequestedParameters */
    u8   mpts_PacketizedStatus;     /* Bit 0: Packetized */
    u8   mpts_DTTxStatus;           /* Bit 1: DT Transfer */
    u8   mpts_QASStatus;            /* Bit 2: Quick Arbitrate and Select */
    u8   mpts_HMCSStatus;           /* Bit 3: Hold Margin Control settings */
    u8   mpts_WFCStatus;            /* Bit 4: Write Flow Control */
    u8   mpts_RSStatus;             /* Bit 5: Read Streaming */
    u8   mpts_RTIStatus;            /* Bit 6: Retain Traning Information */
    u8   mpts_PCStatus;             /* Bit 7: Precompensation */
    u16  mpts_MinSTxPeriod;         /* Bit 8-15: Minimum Synchronous Tx Spead */
    u16  mpts_MaxSOffset;           /* Bit 16-23: Maximum Synchronous Offset */
    u8   mpts_IDPStatus;            /* Bit 27: Inline Data Padding */
    u8   mpts_Width;                /* Bit 29: Width */
#define MPTS_WIDTH_NARROW    (0x01)
#define MPTS_WIDTH_WIDE      (0x02)
    u8   mpts_AIPStatus;            /* Bit 31: Asynchronous Information Protection Generation/Checking */

    /* Configuration */
    u8   mpts_WDTRStatus;           /* Bit 1: WDTR ALLOWED/DISALLOWED */
    u8   mpts_SDTRStatus;           /* Bit 2: SDTR ALLOWED/DISALLOWED */
    u8   mpts_EPStatus;             /* Bit 3: Extended Parameters */
    u8   mpts_FPPRMStatus;          /* Bit 4: Force PPR Message */

/* SCSI-SPI Device Page 2 */
    /* DomainValidation */
    u8   mpts_ISIStatus;            /* Bit 4: ISI Enable */
    u8   mpts_SecondaryDriveStatus; /* Bit 5: Secondary Drive Enable */
    u8   mpts_SlewRateCntl;         /* Bit 7-9: Slew Rate Control */
    u8   mpts_PDSCntl;              /* Bit 10-12: Primary Drive Stregnth Control */
    u8   mpts_SDSCntl;              /* Bit 13-15: Secondary Drive Stregnth Control */
    u8   mpts_XCLKHSTStatus;        /* Bit 28: XCLKH_ST */
    u8   mpts_XCLKSSTStatus;        /* Bit 29: XCLKS_ST */
    u8   mpts_XCLKHDTStatus;        /* Bit 30: XCLKH_DT */
    u8   mpts_XCLKSDTStatus;        /* Bit 31: XCLKS_DT */

    u8   mpts_Reserved[32];         /* reserved for future use */
} micPSCSITargetSettigns_t;


/* target statistics */
typedef struct micPSCSITargetStatistics
{
    u16  mptst_PortID;
    u16  mptst_TargetID;
    u32  mptst_Reserved;
    u64  mptst_NumberOfReadCommands;
    u64  mptst_NubmerOfWriteCommands;
    u64  mptst_Throughput; // ? R/W, in M/B
    u32  mptst_MsgRejectCount;
    u32  mptst_PhaseErrorCount;
    u32  mptst_ParityErrorCount;
    u8   mptst_Reserved1[28];        /* reserved for future use */
} micPSCSITargetStatistics_t;


/* 
 * FE CONTROL INTERFACE RELATED DEFINITIONS AND STRUCTIRES
 */

/* CONTROL OPCODES
 */
typedef struct pscsiCntlInfoDesc
{
    u16 Type;
#define PSCSI_CNTL_GET_LOWEST_TARGET    0x00F1
#define PSCSI_CNTL_GET_MODE_PAGE_19     0x00F2
#define PSCSI_CNTL_SET_MODE_PAGE_19     0x00F3
#define PSCSI_CNTL_GET_NO_OF_PORTS      0x00F4
#define PSCSI_CNTL_CHK_SWAP_PORT_ID     0x00F5

    u16 PortID;
    u16 Index;

    u8 *rcvBuffer;
    u32 rcvBufferSize;

    u8 *sndBuffer;
    u32 sndBufferSize;
} pscsiCntlInfoDesc_t;

/* Structure for Mode Page 19 */
typedef struct ctlPSCSIModePage19Info
{
#define CPMPI_FIELD_U8_UNUSED   0xFF
#define CPMPI_FIELD_U16_UNUSED  0xFFFF

#define CPMPI_STATUS_ENABLED    0x01
#define CPMPI_STATUS_DISABLED   0x02

#define CPMPI_WIDTH_WIDE        0x01
#define CPMPI_WIDTH_NARROW      0x02

    u16  cpmpi_PortID;
    u16  cpmpi_TargetID;

    /* SCSI-SPI Device page0 - NegotiatedParameters */
    u16 cpmpi_TxPdFactor;     /* Transfer Period Factor (0x00~0xFF)*/
    u16 cpmpi_RqAckOffset;    /* Req/Ack Offset (0x00~0xFF)*/
    u8  cpmpi_MaxTxWE;        /* Max Transfer Width (Wide/Narrow) */
    u8  cpmpi_Reserved1;

    /* SCSI-SPI Device page1 - RequestedParameters */
    u8  cpmpi_PackStatus;     /*Packetized Status (Enable/Disable)*/
    u8  cpmpi_DTTxStatus;     /*DT Transfer Status (Enable/Disable)*/
    u8  cpmpi_QASStatus;      /*QAS Status (Enable/Disable)*/
    u8  cpmpi_Reserved2;
    u16 cpmpi_MinTxPeriod;    /* Min Transfer Period Factor (0x00~0xFF)*/
    u16 cpmpi_MaxRqAckOffset; /* Max Req/Ack Offset (0x00~0xFF)*/
    u8  cpmpi_TxWE;           /* Transfer Width (Wide/Narrow)*/
    u8  cpmpi_Reserved3;

    /* SCSI-SPI Device page2 - DomainValidation */
    u8  cpmpi_DvrStrength;    /* Driver Strength (0x00~0x0F)*/
    u8  cpmpi_DvrSlewRate;    /* Driver Slew Rate (0x00~0x0F)*/

    u32  cpmpi_Reserved [12];
} ctlPSCSIModePage19Info_t;

#endif /* _PSCSI_MIC_EXP_H */

