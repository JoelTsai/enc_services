#ifndef _MIC_H_
#define _MIC_H_

#define PAGECODE(dev, type, nr) (((dev & 0x3) << 6) | \
                                 ((type) & 0xF) << 2 | ((nr) & 0x3))
#define GET_DEV_TYPE(x) (((x) & 0xC0) >> 6)
#define GET_PG_TYPE(x)  (((x) & 0x3C) >> 2)
#define GET_PG_NR(x)    ((x) & 0x3)

#define PORT_STATUS_ENABLED   (0x1) 
#define PORT_STATUS_SUPPORTED (0x80) /* This is supported in this design */
#define PORT_STATUS_PRESENT   (0x40) /* Physically present on board */


/* device types */
#define DEV_TYPE_EXTERNAL_PORTS  (0x1)
#define DEV_TYPE_SAS_CONTROLLER (0x2)
#define DEV_TYPE_SAS_EXPANDER   (0x3)

/* page types */
#define PG_TYPE_GENERAL   (0x1)
#define PG_TYPE_DEVICE    (0x2)
#define PG_TYPE_ROUTE     (0x3)
#define PG_TYPE_ERROR     (0x4)
#define PG_TYPE_DIAGNOSTIC (0x5)

/* page number */
#define PAGE_NUMBER_0   (0x0)


/* 
 * output structure formats.
 */

/*
 * output structure format for Get Info Page.
 */
//#define PMIC_SAS_FE_GET_INFORMATION (MIC_SAS_FE_MGT_ID | 0x0001)
typedef struct ErrorData 
{ 
    u32 ed_ErrInvalidDwordCount; 
    u32 ed_ErrRunningDisparityErrorCount; 
    u32 ed_ErrLossDwordSynchCount; 
    u32 ed_ErrPhyResetProblemCount; 
    u32 ed_ErrCodeViolationErrorCount; /* Expander provides, SAS controller no*/
	u32 ed_Reserved1;
	u32 ed_Reserved2;
	u32 ed_Reserved3;
} ErrorData_t;   

typedef struct SASPortState 
{    
    u8 sps_ControllerID; /* controller id */
    u8 sps_ExpID; /* expander id */
    u8 sps_PortID; /* port id */
    u8 sps_PortStatus;  /* enabled */
    u8 sps_PortSpeed;       /* operating speed */
#define    LS_DISABLED    (0x0) /* port inactive */
#define    LS_ENABLED     (0x1) /* port active, speed unknown/speed nego fail */
#define    LS_ONE_FIVE_GBPS_ONLINE   (0x2)   /* 1.5 gbps */
#define    LS_THREE_ZERO_GBPS_ONLINE (0x3) /* 3.0 gbps */
    u8 sps_CableSignalStrength; /* cable length in meters */
#define PORT_ROUTE_SUBTRACTIVE (0x1)
#define PORT_ROUTE_TABLE (0x0)
   	u8 sps_RoutingAttribute; /* cascade? Or plain host */
   	u8 sps_LinkStatus;
#define LINK_ONLINE (0x1) /* PortSpeed is valid only if link is online */
#define LINK_OFFLINE (0x0)
	u64 sps_SASAddr; /* SAS Address of the port */
	u32 sps_Reserved1[8]; /* An array of reserved space */
	ErrorData_t sps_PortErrStats; 
} SASPortState_t; 

typedef struct micSASPortStatus 
{     
    /* Nr of ports reported in this request.If unit_id is 0xFF- all of the supported ports Max could be 8 (4 from each controller) for E310S*/
	u8 msps_NrOfPorts; 
    u8 msps_NarrowPortEnable; /*     default: Disabled             */
    u16 msps_Reserved1; 
	u32 msps_Reserved2[7]; /* An array of reserved space */
    SASPortState_t msps_SASPortState[0]; /* This is an array of NrOfPorts*/ 
} micSASPortStatus_t, micExternalPortsGeneralPage0;


/*
 * output structure format for read/write page.
 */
//#define PMIC_SAS_FE_SET_PARAMETERS (MIC_SAS_FE_MGT_ID | 0x0002)
//#define PMIC_SAS_FE_GET_PARAMETERS (MIC_SAS_FE_MGT_ID | 0x0003)

typedef struct SASPortSetting 
{    
    u8 sps_ControllerID; /* controller id */
    u8 sps_PortID; /* port id */
    u8 sps_CableSignalStrength; /* signal strength [1, 8]*/
	u8 sps_Reserved0;
	u32 sps_Reserved1;
	u32 sps_Reserved2;
	u32 sps_Reserved3;
} SASPortSetting_t; 

typedef struct micSASPortSettings 
{     
	/* Nr of ports reported in this request.If unit_id is 0xFF- all of the supported ports Max could be 8 (4 from each controller) for E310S*/
	u8 msps_NrOfPorts; 
    u8 msps_NarrowPortEnable; /*     default: Disabled             */
    u16 msps_Reserved1; 
	u32 msps_Reserved2;
    SASPortSetting_t msps_SASPortSetting[0]; /* This is an array of NrOfPorts*/ 
} micExternalPortSettingsGenPage0;

typedef struct FrontEndInitiatorInfo
{
    u16 feii_InitiatorId; /* Initiator Id */
    u16 feii_PortId;      /* Port Id - initiator logged logical port */
    u8  feii_ControllerId;/* Logged through this controller */
    u8  feii_Reserved;
    u16 feii_Reserved1;
    u64 feii_SASAddress;  /* SAS Address of this initiator */
    u32 feii_Reserved2[12];
} FrontEndInitiatorInfo_t;

typedef struct micFrontEndInitiatorList
{
    u8 mfeil_NrOfInitiators; /* Nr of Initiators listed below */
    u8 mfeil_Reserved0;
    u16 mfeil_Reserved1;
    u32 mfeil_Reserved2[15];
    FrontEndInitiatorInfo_t mfeil_InitiatorInfo[0];
} micFrontEndInitiatorList_t;

typedef struct micFrontEndSASPhyErrorData
{
    u32 mfesped_ErrInvalidDwordCount;
    u32 mfesped_ErrRunningDisparityErrorCount;
    u32 mfesped_ErrLossDwordSynchCount;
    u32 mfesped_ErrPhyResetProblemCount;
    u32 mfesped_ErrCodeViolationErrorCount;
    u32 mfesped_phynum; /* This field indicates phy num */
    u32 mfesped_Reserved2;
    u32 mfesped_Reserved3;
} micFrontEndSASPhyErrorData_t;

typedef struct micFrontEndSASPhyLevelPortStats {
    u8 mfesplps_cid; /* controller id */
    u8 mfesplps_pid; /* external port id */
    u8 mfesplps_expid; /* expander id */
    u8 mfesplps_nrofphys; /* number of phys in this port will be 4 for SAS*/
    u32 mfesplps_reserved1;
#define MAX_SAS_PHY_IN_PORT (4)
    micFrontEndSASPhyErrorData_t ErrorData[1];
} micFrontEndSASPhyLevelPortStats_t;

typedef struct micFrontEndSASAllPhyStats
{
    u8 mfesaps_NrOfPortStats; /* Nr of Phy level stats for each Port*/
    u8 mfesaps_Reserved0;
    u16 mfesaps_Reserved1;
    u32 mfesaps_Reserved2[15];
    micFrontEndSASPhyLevelPortStats_t mfesaps_phystats[0];
} micFrontEndSASAllPhyStats_t;

#endif /* _MIC_H_ */

