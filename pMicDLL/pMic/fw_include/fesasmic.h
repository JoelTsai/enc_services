#ifndef _FESASMIC_H_
#define _FESASMIC_H_

#if defined(HW_E310)
#define MAX_SAS_PHY_IN_PORT (4)
#define MAX_SAS_PORTS_IN_CONTROLLER (4)
#elif defined(HW_CBAY)
#define MAX_SAS_PHY_IN_PORT (4)
#define MAX_SAS_PORTS_IN_CONTROLLER (12) /* each group is a port */
#elif defined(HW_CX20Y) || defined(CX20Y)
#define MAX_SAS_PHY_IN_PORT (4)
#define MAX_SAS_PORTS_IN_CONTROLLER (2) /* each group is a port */
#endif

typedef struct femicControl
{
    u8 c_Control:6;
    u8 c_OffsetControl:2;
} __attribute__ ((packed)) femicControl_t;

#if !defined(CX20Y) /* defined in mic.h */
/* all types of request use the same MIC structure below */
typedef struct SAS_MIC_
{
    u8          sm_ScsiOpCode;
    u8          sm_MicSignature;           
    u16         sm_MicOpCode;
    u8          sm_UniqueCmdId;    
    u8          sm_LoginKey;
    u8          sm_PageCode;
    u8          sm_Reserved0;
    u8          sm_Reserved1;
    u8          sm_UnitID; /* is also the external port id */
    u16         sm_TransferLength;
    u16         sm_TransferOffset;
    u8          sm_ControllerID; /* controller id */
    femicControl_t   sm_Control; 
} __attribute__ ((packed)) micSASGetInfoCmd_t, micSASGetParamCmd_t, 
    micSASSetParamCmd_t, SAS_MIC_T;
#endif

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
    u8 sps_ExpID;        /* expander id */
    u8 sps_PortID;       /* port id */
    u8 sps_PortStatus;   /* enabled */
    u8 sps_PortSpeed;           /* operating speed */
#define    LS_DISABLED    (0x0) /* port inactive */
#define    LS_ENABLED     (0x1) /* port active, speed unknown/speed nego fail */
#define    LS_ONE_FIVE_GBPS_ONLINE   (0x2)   /* 1.5 gbps */
#define    LS_THREE_ZERO_GBPS_ONLINE (0x3)   /* 3.0 gbps */
    u8 sps_CableSignalStrength; /* cable length in meters */
#define PORT_ROUTE_SUBTRACTIVE (0x1)
#define PORT_ROUTE_TABLE (0x0)
    u8 sps_RoutingAttribute;    /* cascade? Or plain host */
    u8 sps_LinkStatus;
#define LINK_ONLINE (0x1)       /* PortSpeed is valid only if link is online */
#define LINK_OFFLINE (0x0)
    u64 sps_SASAddr;            /* SAS Address of the port */
    u32 sps_Reserved1[8];       /* An array of reserved space */
    ErrorData_t sps_PortErrStats; 
} SASPortState_t; 

typedef struct micSASPortStatus 
{     
    /*
     * Nr of ports reported in this request.
     * If unit_id is 0xFF - all of the supported ports 
     * Max could be 8 (4 from each controller) for E310S
     */
    u8 msps_NrOfPorts; 
    u8 msps_NarrowPortEnable; /*     default: Disabled             */
    u16 msps_Reserved1; 
    u32 msps_Reserved2[7];               /* An array of reserved space */
    SASPortState_t msps_SASPortState[0]; /* This is an array of NrOfPorts*/ 
} micSASPortStatus_t, micExternalPortsGeneralPage0;


/*
 * output structure format for read/write page.
 */
typedef struct SASPortSetting 
{    
    u8 sps_ControllerID;        /* controller id */
    u8 sps_PortID;              /* port id */
    u8 sps_CableSignalStrength; /* signal strength [1, 8]*/
    u8 sps_Reserved0;
    u32 sps_Reserved1;
    u32 sps_Reserved2;
    u32 sps_Reserved3;
} SASPortSetting_t; 

typedef struct micSASPortSettings 
{     
    /*
     * Nr of ports reported in this request.
     * If unit_id is 0xFF - all of the supported ports 
     * Max could be 8 (4 from each controller) for E310S
     */
    u8 msps_NrOfPorts; 
    u8 msps_NarrowPortEnable; /*     default: Disabled             */
    u16 msps_Reserved1; 
    u32 msps_Reserved2;
    SASPortSetting_t msps_SASPortSetting[0]; /* This is an array of NrOfPorts*/ 
} micExternalPortSettingsGenPage0;

#define MAX_FE_SAS_INITIATORS (32)
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
    micFrontEndSASPhyErrorData_t ErrorData[0];
} micFrontEndSASPhyLevelPortStats_t;

typedef struct micFrontEndSASAllPhyStats
{
    u8 mfesaps_NrOfPortStats; /* Nr of Phy level stats for each Port*/
    u8 mfesaps_Reserved0;
    u16 mfesaps_Reserved1;
    u32 mfesaps_Reserved2[15];
    micFrontEndSASPhyLevelPortStats_t mfesaps_phystats[0];
} micFrontEndSASAllPhyStats_t;

#define SXP_CTRL_FE_PHY_DISABLE    0x00
#define SXP_CTRL_FE_PHY_ENABLE     0x01
#define SXP_CTRL_FE_PHY_EN_DIS     0x02

typedef struct __sas_ctrl_sas_tgt_fn_reg
{
    int (*sxp_control_front_end_exp_phys)(u8 ctrl, u32 timeout);
} sas_ctrl_sas_tgt_fn_reg_t;

/*
 * Some debug dumps
 */
#ifdef MICDEBUG_SAS
static inline
void _DUMP_SAS_PORT_SETTING(SASPortSetting_t* sps)       {
    int i;                                              
    u8* ch;                                             
    SASPortSetting_t *__tmp_sps;                        
    prom_printk("Dumping SAS Port Setting\nRaw dump\n"); 
    for (i=0, ch = (u8*)sps; i<sizeof(SASPortSetting_t); i++, ch++) {   
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i);                   
        prom_printk("[%02x] ", *ch);                                 
    }                                                       
    prom_printk("\n");                                       
    __tmp_sps = sps;                                
    prom_printk("Controller ID: 0x%x\n", __tmp_sps->sps_ControllerID);       
    prom_printk("Port ID      : 0x%x\n", __tmp_sps->sps_PortID);         
    prom_printk("CableSignalStrength: 0x%x\n", __tmp_sps->sps_CableSignalStrength); 
} 

static inline
void _DUMP_SASMIC_ERRORDATA(ErrorData_t* ed)  {                              
    int i;                                                          
    u8 *ch;                                                         
    ErrorData_t *__tmp_ed;                                          
    prom_printk("Dumping Error Data\nRaw Dump\n");                       
    for (i=0, ch=(u8*)ed; i<sizeof(ErrorData_t); i++, ch++) {                   
        if (i%8 == 0) prom_printk("\n[off 0x%02x:]", i);                 
        prom_printk("[%02x] ", *ch);                                     
    }                                                               
    prom_printk("\n");                                                   
    __tmp_ed = ed;                                                  
    prom_printk("InvalidDwordCount: 0x%x\n",                             
                (__tmp_ed->ed_ErrInvalidDwordCount));    
    prom_printk("RunningDisparityErrorCount: 0x%x\n",                
                (__tmp_ed->ed_ErrRunningDisparityErrorCount));
    prom_printk("LossDwordSynchCount: 0x%x\n",                           
                (__tmp_ed->ed_ErrLossDwordSynchCount));  
    prom_printk("PhyResetProblemCount: 0x%x\n",                          
                (__tmp_ed->ed_ErrPhyResetProblemCount)); 
    prom_printk("CodeViolationErrorCount: 0x%x\n",                       
                (__tmp_ed->ed_ErrCodeViolationErrorCount));
}
    

static inline
void _DUMP_SASMIC_PORTSTATE(SASPortState_t *sps) {                           
    int i;                                                                  
    u8* ch;                                                                 
    SASPortState_t *__tmp_sps;                                              
    prom_printk("Dumping SAS Port State\nRaw dump\n");                           
    for (i=0, ch = (u8*)sps; i<sizeof(SASPortState_t); i++, ch++) {         
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i);                           
        prom_printk("[%02x] ", *ch);                                             
    }                                                                       
    prom_printk("\n");                                                           
    __tmp_sps = sps;                                                        
    prom_printk("Controller ID: 0x%x\n", __tmp_sps->sps_ControllerID);           
    prom_printk("Expander ID: 0x%x\n", __tmp_sps->sps_ExpID);                
    prom_printk("Port ID      : 0x%x\n", __tmp_sps->sps_PortID);                 
    prom_printk("Port Status  : 0x%x\n", __tmp_sps->sps_PortStatus);             
    prom_printk("Port Speed   : 0x%x\n", __tmp_sps->sps_PortSpeed);             
    prom_printk("Routing Attr : 0x%x\n", __tmp_sps->sps_RoutingAttribute);       
    prom_printk("Link Status  : 0x%x\n", __tmp_sps->sps_LinkStatus);             
    prom_printk("SAS Addr: 0x%llx\n", __tmp_sps->sps_SASAddr);                   
    prom_printk("CableSignalStrength: 0x%x\n", __tmp_sps->sps_CableSignalStrength); 
    _DUMP_SASMIC_ERRORDATA(&__tmp_sps->sps_PortErrStats);                    
} 

static inline
void _DUMP_SAS_INITIATOR_INFO (FrontEndInitiatorInfo_t *fei)
{
    int i;
    u8 *ch;

    prom_printk("Dumping Initiator Info\nRaw dump\n");
    for (i=0, ch=(u8*)fei; i<sizeof(FrontEndInitiatorInfo_t); i++, ch++) {
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i);                           
        prom_printk("[%02x] ", *ch);                                             
    }                                                                       

    prom_printk("\nController ID: 0x%x\n"
             "Port ID      : 0x%x\n"
             "Initiator ID : 0x%x\n"
             "SAS Address  : 0x%llx\n",
            fei->feii_ControllerId,
            fei->feii_PortId,
            fei->feii_InitiatorId,
            fei->feii_SASAddress);
}

static inline
void _DUMP_SAS_PHYINFO_PER_PHY (micFrontEndSASPhyErrorData_t *ed)
{
    prom_printk("mfesped_ErrInvalidDwordCount: %x\n", 
                ed->mfesped_ErrInvalidDwordCount);
    prom_printk("mfesped_ErrRunningDisparityErrorCount: %x\n",
                ed->mfesped_ErrRunningDisparityErrorCount);
    prom_printk("mfesped_ErrLossDwordSynchCount: %x\n",
                ed->mfesped_ErrLossDwordSynchCount);
    prom_printk("mfesped_ErrPhyResetProblemCount: %x\n",
                ed->mfesped_ErrPhyResetProblemCount);
    prom_printk("mfesped_ErrCodeViolationErrorCount: %x\n",
                ed->mfesped_ErrCodeViolationErrorCount);
    prom_printk("mfesped_phynum: %x\n",
                ed->mfesped_phynum);
}
static inline
void _DUMP_SAS_PHYINFO_PER_PORT (micFrontEndSASPhyLevelPortStats_t *ps)
{
    int i;
    u8 *ch;
    micFrontEndSASPhyErrorData_t *ed;
    
    prom_printk("Dumping PhyInfo Per Port - Rawdump (%p)\n", ps);
    for (i=0, ch=(u8*)ps; i<sizeof(micFrontEndSASPhyLevelPortStats_t); 
            i++, ch++) {
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i); 
        prom_printk("[%02x] ", *ch); 
    }
    prom_printk("\n");
    
    ed = ps->ErrorData;
    for (i=0; i<ps->mfesplps_nrofphys; i++) {
        _DUMP_SAS_PHYINFO_PER_PHY(&ed[i]);
    }   
}

/* 
 * external macro version to dump PMIC_SAS_FE_GET_PHY_STATS
 * DUMP_SASMIC_PHY_STATS
 */
static inline
void DUMP_SASMIC_PHY_STATS (micFrontEndSASAllPhyStats_t *fesaps)
{
    int i;
    u8 *ch;
    micFrontEndSASPhyLevelPortStats_t *ps;
    
    prom_printk("Dumping Phy header - Rawdump (%p)\n", fesaps);
    for (i=0, ch=(u8*)fesaps; i<sizeof(micFrontEndSASAllPhyStats_t); 
            i++, ch++) {
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i); 
        prom_printk("[%02x] ", *ch); 
    }
    prom_printk("Phy Header %p, Nr of Ports: 0x%x\n", 
                fesaps, fesaps->mfesaps_NrOfPortStats);
    for (i=0; i<fesaps->mfesaps_NrOfPortStats; i++) {
        ps = &fesaps->mfesaps_phystats[i];
        _DUMP_SAS_PHYINFO_PER_PORT(ps);
    }
}

/*
 * external macro version to dump DUMP_SASMIC_INITIATOR_LIST
 * PMIC_SAS_FE_GET_INITIATOR_LIST
 */
static inline
void DUMP_SASMIC_INITIATOR_LIST (micFrontEndInitiatorList_t *mfeil)
{
    int i;
    u8 *ch;
    
    prom_printk("DUMP_SASMIC_INITIATOR_LIST - Rawdump (%p)\n", mfeil);
    for (i=0, ch=(u8*)mfeil; i<sizeof(micFrontEndInitiatorList_t); i++, ch++) {
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i); 
        prom_printk("[%02x] ", *ch); 
    }
    prom_printk("\nNr of Initiators: 0x%x\n", mfeil->mfeil_NrOfInitiators);
    for (i=0; i<mfeil->mfeil_NrOfInitiators; i++) {
        _DUMP_SAS_INITIATOR_INFO(&mfeil->mfeil_InitiatorInfo[i]);
    }
}

/*
 * This is the external macro version to dump all info about  
 * PMIC_SAS_FE_GET_PORT_PARAMETERS
 * PMIC_SAS_FE_SET_PORT_PARAMETERS
 */
static inline
void DUMP_SASMIC_PORTSETTING(micExternalPortSettingsGenPage0 *msps) {   
    int i;                                                          
    u8 *ch;                                                         
    micExternalPortSettingsGenPage0 *__tmp;                         
    prom_printk("DUMP_SASMIC_PORTSETTING - Rawdump (%p)\n", msps);
    for (i=0, ch = (u8*)msps; i<sizeof(micExternalPortSettingsGenPage0); 
                i++, ch++) {                                        
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i);                   
        prom_printk("[%02x] ", *ch);                                     
    }                                                               
    prom_printk("\n");                                                   
    __tmp = msps;                                                   
    prom_printk("Nr of Ports: 0x%x\n", __tmp->msps_NrOfPorts);           
    prom_printk("Narrow Port Enable Setting: 0x%x\n", __tmp->msps_NarrowPortEnable);           
    for (i=0; i<__tmp->msps_NrOfPorts; i++) {                       
        _DUMP_SAS_PORT_SETTING(&__tmp->msps_SASPortSetting[i]);      
    }                                                               
} 


/*
 * This is the external macro version to dump all info about  
 * PMIC_SAS_FE_GET_PORT_INFO
 */
static inline
void DUMP_SASMIC_PORTINFO(micExternalPortsGeneralPage0 *msps)   {
    int i;                                                          
    u8 *ch;                                                         
    micExternalPortsGeneralPage0 *__tmp;                            
    prom_printk("DUMP_SASMIC_PORTINFO - Rawdump (%p)\n", msps);                      
    for (i=0, ch = (u8*)msps; i<sizeof(micExternalPortsGeneralPage0); 
                i++, ch++) {                                        
        if (i%8==0) prom_printk("\n[off 0x%02x:]", i);                   
        prom_printk("[%02x] ", *ch);                                     
    }                                                               
    prom_printk("\n");                                                   
    __tmp = msps;                                                   
    prom_printk("Nr of Ports: 0x%x\n", __tmp->msps_NrOfPorts);           
    prom_printk("Narrow Port Enable Setting: 0x%x\n", __tmp->msps_NarrowPortEnable);           
    for (i=0; i<__tmp->msps_NrOfPorts; i++) {                       
        _DUMP_SASMIC_PORTSTATE(&__tmp->msps_SASPortState[i]);      
    }                                                               
} 

#else  /* No DEBUG_SAS */

#define DUMP_SASMIC_PHY_STATS(mfesplps)
#define DUMP_SASMIC_INITIATOR_LIST(feil) 
#define DUMP_SASMIC_PORTSETTING(msps)
#define DUMP_SASMIC_PORTINFO(msps) 

#endif 

typedef struct {
    u32 ctrl_id;    /* which controller */
    u16 device;     /* device id */
    u16 rsvd;
    u32 status;
    u32 nr_phys;    /* nr of phys */
    u32 nr_ports;   /* nr of ports */
    u32 phy2port[0];    /* phy 2 port mapping - array size is nr_phys*/
} GENERAL_PG_T;

typedef struct {
    u64 sas_addr;
    u32 linkspeed;
    u32 rsvd;
} DEVICE_DATA_T;

typedef struct {
    u32 nr_ports;
    u32 rsvd;   /* reserved */
    DEVICE_DATA_T dev[0]; /* array size is given by nr_ports */
} DEVICE_PG_T;

typedef struct {
    u32 InvalidDwordCount;
    u32 RunningDisparityErrorCount;
    u32 LossDwordSynchCount;
    u32 PhyResetProblemCount;
    u32 CodeViolationErrorCount; /* not used for SAS */
} ERROR_DATA_T;

typedef struct {
    u32 nr_phys;
    u32 clear; /* clear counters */
    ERROR_DATA_T phyerr[0];
} ERROR_PG_T;

typedef struct {
    u32 MaxInvalidDwordCount;
    u32 InvalidDwordCountTime;
    u32 MaxRunningDisparityErrorCount;
    u32 RunningDisparityErrorTime;
    u32 MaxLossDwordSynchCount;
    u32 LossDwordSynchCountTime;
    u32 MaxPhyResetProblemCount;
    u32 PhyResetProblemTime;
} ERR_THRESHOLD_DIAG_PG_T;

typedef GENERAL_PG_T SAS_GENERAL_PG_T;
typedef DEVICE_DATA_T SAS_DEVICE_DATA_T;
typedef DEVICE_PG_T SAS_DEVICE_PG_T;
typedef ERROR_DATA_T SAS_ERROR_DATA_T;
typedef ERROR_PG_T SAS_ERROR_PG_T;
typedef ERR_THRESHOLD_DIAG_PG_T SAS_ERR_THRESHOLD_DIAG_PG_T;

typedef GENERAL_PG_T SAS_EXP_GENERAL_PG_T;
typedef DEVICE_DATA_T SAS_EXP_DEVICE_DATA_T;
typedef DEVICE_PG_T SAS_EXP_DEVICE_PG_T;
typedef ERROR_DATA_T SAS_EXP_ERROR_DATA_T;
typedef ERROR_PG_T SAS_EXP_ERROR_PG_T;
typedef ERR_THRESHOLD_DIAG_PG_T SAS_EXP_ERR_THRESHOLD_DIAG_PG_T;

/* SAS Expander specific structure definitions */
typedef struct {
    u64 sas_addr;
    u32 port_id;
    u32 enable; /* this control is for internal access only. */
} SAS_EXP_ROUTE_DATA_T;

typedef struct {
    u32 nr_routes;
    u32 subvec; /* each bit indicates that particular port is in subt. Mode */
    u32 rsvd;
    SAS_EXP_ROUTE_DATA_T route[0]; /* array size is nr_routes */
} SAS_EXP_ROUTE_PG_T;

typedef struct {
    u8 port_enable;
    u8 loopback_ctrl;
    u8 preem_ctrl;
    u8 swing_ctrl;
    u8 equ_ctrl;
    u8 squlvl_ctrl;
    u8 sxl_ctrl; /* used for cjpat */
} SAS_EXP_MAINTENANCE_DIAG_DATA_T;

typedef struct {
    u32 nr_phys;
    u32 rsvd;
    SAS_EXP_MAINTENANCE_DIAG_DATA_T data[0]; /* array size is nr_phys */
} SAS_EXP_MAINTENANCE_DIAG_PG_T;


extern int fesasmic_initialize_peer_ctrl_micinfo(void);
struct fesas_mic_priv_;
extern int fesas_micreq_complete(struct fesas_mic_priv_*);

/*
 * Datastructure definition for holding SAS Initiator Info. 
 */
#define  MAX_SAS_INITIATORS  (128)
typedef struct initiator_info_ {
    u16 InitiatorId; /* aka DevHandle */
    u16 Port;
    u64 SASAddress;
    int status;
#define II_VALID    (0x1)
#define II_LOGIN_OK (0x2)
} initiator_info_t;

typedef struct initiator_login_info_ {
    initiator_info_t ii[MAX_SAS_INITIATORS+1]; /* index 0 unused */
} initiator_login_info_t;

#endif /* _FESASMIC_H_ */

