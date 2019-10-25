/*******************************************************************************
 * Filename    : i2types.h
 * Description : I2 types header file
 *               It defines the data structures used in I2 APIs
 * Created on  : 02/05/2004
 * CVS Version : $Id: i2types.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * Copyright (C) 2004-2004 Promise Technology Inc.
 * All Rights Reserved
 ******************************************************************************/

#ifndef I2_TYPES_H
#define I2_TYPES_H

/* --- standard C lib header files ------------------------------------------ */
#include <time.h>

/* --- internal header files ------------------------------------------------ */
#include "pibasic.h"
#include "i2limit.h"
#include "errorlog.h"
#include "pscsi_mic_exp.h"
#include "mic.h"

#ifdef EMBEDDED
    #include "../../utils/ptiflash/imgheader.h"
    #include "../../utils/ptiflash/ptiflashlib/ptiflashlib.h"
#else
    #include "imgheader.h"
#endif
#define MAX(a, b)  (((a)>(b))?(a):(b))


/* --- constants & data structures ------------------------------------------ */
#define SHUTDOWN_TYPE_SHUTDOWN 1
#define SHUTDOWN_TYPE_REBOOT 2
#define SHUTDOWN_TYPE_POWEROFF 3

#define NULL_SUBSYS_ID  0
typedef struct
{
    u16 di_u16CtrlId; 
    u8 di_u8Padding1[2]; 
    u16 di_u16SubsysId;
    u8 di_u8Padding2[2]; 
} device_id_t;
/*
 * di_u16CtrlId - index of HBA controller or index of controller inside the subsystem
 * di_u16SubsysId - index of subsystem. A HBA should have subsys index as NULL_SUBSYS_ID
 */

#define NULL_SESSION_ID 0
typedef u32 session_id_t;

#define DEFAULT_I2API_TIMEOUT 60 /* seconds */
typedef struct
{
    error_handler_t * ip_pehErrorHandler; /* error handler */ 
#ifndef PLATFORM_64BIT	
    void * ip_pPadding1;       /* padding for 8 byte alignment */
#endif

    u32 ip_u32Version;          /* Library version signature*/
    boolean_t ip_bUseDefault;   /* use the default param */
    u8 ip_u8Padding2[3];        /* padding for 8 byte alignment */

    u32 ip_u32Timeout;         /* timeout of request in seconds */ 
    u8 ip_u8Reserved3[107];    /* reserved for future improvement */

    boolean_t ip_bPluginParamValid; /* whether the plug-in param is valid */
    u8 ip_u8PluginParam[128];  /* plug-in specific parameters */
} i2api_param_t; 

/* 
 * ip_pehErrorHandler - the error handler to pass to the I2 API. It must be set either to NULL or to the pointer of a valid error handler.
 * 
 * ip_u32Version - I2 API library version signature. It must be set to I2API_VERSION.
 * 
 * ip_bUseDefault - whether to use default parameters. If it is set to TRUE, all of the rest parameter will be ignored by the I2 API and default values will be used; if it is FALSE, the rest of the parameters should be set accordingly.
 * 
 * ip_u32Timeout - the max timeout of each API. The default value is 60 seconds.
 * 
 * ip_bPluginParamValid - whether the plugin parameter is valid or not. If it is set to TRUE, the plugin parameters should be set accordingly to the particular plugin; if it is FALSE, the plugin parameters will be ignored and the default values will be used. The default value is FALSE.
 * If an application links with a particular I2 API plugin directly, it may concern about the plugin specific parameter to take more advantage of the plugin's capability; otherwise, it should be set to FALSE to use the default plugin parameters.
 * 
 * ip_u8PluginParam - the plugin specific parameters
 */

/* discover */
#define I2_DOI_IDTYPE_UNKNOWN  0
#define I2_DOI_IDTYPE_WWN      1
#define I2_DOI_IDTYPE_SN       2    /* serial number */
#define I2_DOI_IDTYPE_OTHER    3

typedef struct
{
    u8 doi_u8Vendor[24];
    u8 doi_u8Model[16];
    u8 doi_u8Padding1[7];
    u8 doi_u8IDType; /* I2_DOI_IDTYPE_WWN, I2_DOI_IDTYPE_SN, I2_DOI_IDTYPE_OTHER */
    u8 doi_u8ID[64];
} device_object_identifier_t;

typedef struct
{
    u8 dph_u8Port;
    u8 dph_u8Path; /* ? */
    u8 dph_u8Target;
    u8 dph_u8Lun;
    u8 dph_u8Padding1[4];
    u8 dph_u8DeviceName[MAX_PATH_LENGTH+1];
    u32 dph_u32IRQ;			// Interrupt number;
    u32 dph_u32SlotNumber;		// Slot this controller take place;
    u32 dph_u32BIOSMemStart;		// BIOS rom start address
    u32 dph_u32BIOSMemRange;		// size of BIOS rom
    u8 * dph_pu8BusMasterBase;	// Controller base;
    u32 * dph_pu32BaseAddressATA;   // For ATA base address
    u32 * dph_pu32BaseAddressXOR;   // For XOR, HOST DMA base address
    u32 * dph_pu32BaseAddressSEQ;	// For SEQ base address
    u32 * dph_pu32BaseAddressMMIO;  // For memory mapped IO base address
    u32 * dph_pu32BaseAddressSDRAM; // For SDRAM base address
} discover_path_hba_t;

typedef struct
{
    u8 dps_u8Port;
    u8 dps_u8Path; /* for windows, bus, target and lun are valid only for SCSIPORT */
    u8 dps_u8Target;
    u8 dps_u8Lun;
    u8 dps_u8Padding1[4];
    u8 dps_u8DeviceName[MAX_PATH_LENGTH+1];
} discover_path_scsi_t;

typedef struct
{
    discover_path_scsi_t dpi_dpsScsiPath;
    u8 dpi_u8Padding1[7];      /* not supported for now */
    u8 dpi_u8HostIPAddrType;    /* not supported for now */
    u8 dpi_u8HostIPAddr[64];    /* not supported for now */
} discover_path_iscsi_t;

typedef struct
{
    u32 dpr_u32BaudRate;
    u8 dpr_u8DataBit;
    u8 dpr_u8Parity; 
    u8 dpr_u8StopBit;
    u8 dpr_u8ControlFlow;
    u8 dpr_u8DeviceName[MAX_PATH_LENGTH+1];
} discover_path_rs232_t;

typedef struct
{
    u16 dpt_u16PortNumber;
    u8 dpt_u8Padding1[6];
    u8 dpt_u8UserName[32];
    u8 dpt_u8Password[32];
    u8 dpt_u8HostName[128];
} discover_path_tcpip_t;

typedef struct
{
    u16 dpw_u16PortNumber;
    boolean_t dpw_bUseSSL;
    u8 dpw_u8Padding1[5];
    u8 dpw_u8UserName[32];
    u8 dpw_u8Password[32];
    u8 dpw_u8HostName[128];
    u8 dpw_u8NameSpace[MAX_PATH_LENGTH+1];
} discover_path_wbem_t;

#define I2_COMMPATH_UNKNOW  0
#define I2_COMMPATH_HBA     1
#define I2_COMMPATH_SCSI    2
#define I2_COMMPATH_iSCSI   3
#define I2_COMMPATH_FC      4
#define I2_COMMPATH_RS232   5
#define I2_COMMPATH_TCPIP   6
#define I2_COMMPATH_WBEM    7

typedef struct
{
    u8 dp_u8Padding1[7];
    u8 dp_u8CommPath;
    union 
    {
        discover_path_hba_t dp_dphHba;
        discover_path_scsi_t dp_dpsScsi;
        discover_path_iscsi_t dp_dpiIscsi;
        discover_path_rs232_t dp_dprRS232;
        discover_path_tcpip_t dp_dptTCPIP;
        discover_path_wbem_t dp_dpwWbem;
    } dp_uPath;
} discover_path_t;

typedef struct
{
    device_id_t ddp_diIndex;
    device_object_identifier_t ddp_doiIdentity;
    u8 ddp_u8Padding1[4];
    u16 ddp_u16NumOfPaths;  /* the actual length of the discover path array */
    u16 ddp_u16CurrentPath; /* the current path thru which the API manages the device */
    discover_path_t ddp_dpDiscoverPaths[1]; /* variable length array */
} device_discover_path_t;

typedef struct req_param_device_ids
{
    u32 rpdi_u32DevId;
    u32 rpdi_u32Count;
} req_param_device_ids_t;

typedef struct
{
    u32 rpdd_u32Count;
    u32 rpdd_u32Reserved;
    req_param_device_ids_t rpdd_rpdiIdRange[1];
} req_param_device_del_t;

typedef struct
{
    u32 rpad_u32Count;
    u32 rpad_u32Ids[1];     /* the list of ids to be deleted */
} req_param_array_del_t;

/* request param */
typedef struct req_param_ctrl_info
{
    req_param_device_ids_t rpci_rpdiDeviceIds;
    u16 rpci_u16PageCode;
    u16 rpci_u32Reserved[3];
} req_param_ctrl_info_t;

typedef struct req_param_ctrl_settings
{
    req_param_device_ids_t rpcs_rpdiDeviceIds;
    u16 rpcs_u16PageCode;
    u16 rpcs_u32Reserved[3];
} req_param_ctrl_settings_t;

typedef struct req_param_phydrv_info
{
    req_param_device_ids_t rppi_rpdiDeviceIds;
    u16 rppi_u16PageCode;
    u16 rppi_u16Reserved[3];
} req_param_phydrv_info_t;

typedef struct req_param_phydrv_settings
{
    req_param_device_ids_t rpps_rpdiDeviceIds;
    u16 rpps_u16PageCode;
    u16 rpps_u16Reserved[3];
} req_param_phydrv_settings_t;

typedef struct req_param_logdrv_info
{
    req_param_device_ids_t rpli_rpdiDeviceIds;
} req_param_logdrv_info_t;

typedef struct req_param_logdrv_settings
{
    /* rpls_rpdiDeviceIds.rpdi_u32DevId is valid only for get LD settings */
    req_param_device_ids_t rpls_rpdiDeviceIds;
} req_param_logdrv_settings_t;

/* array info */
typedef struct req_param_array_info
{
    req_param_device_ids_t rpai_rpdiDeviceIds;
} req_param_array_info_t;

typedef struct
{
    u16 rpat_u16CtrlId;          
    u16 rpat_u16ArrayId;
    u8 rpat_u8Padding[4];
    u8 rpat_u8Reserved[8];
} req_param_array_transport_t;

/* array process */
typedef struct req_param_array_process
{
    u8 rpap_u8ActionType;       /* valid only when rpap_bAutomatic is set to FALSE */
    boolean_t rpap_bAutomatic;  /* automatically decide what action type to take */
    u8 rpap_u8Reserved[2];
    u32 rpap_u32ArrayId;
} req_param_array_process_t;

/* get disk array cfg info */
typedef struct
{
    req_param_device_ids_t rpai_rpdiDeviceIds;
} req_param_array_cfg_t;

/* add, modify disk array config */
typedef struct
{
    boolean_t rpad_bAutoId;
    boolean_t rpad_bMediaPatrlEnable;
    boolean_t rpad_bPDMEnable;
    boolean_t rpad_bPowerManagementIgnored;
    u32 rpad_u32ArrayId;
    u8 rpad_u8Name[MAX_ARRAY_NAME_BYTES];
    u8 rpad_u8Reserved[16];
} req_param_array_dacfg_t;

typedef struct
{
    u32 rpap_u32NumberOfPd;
    u32 rpap_u32Reserved;
    u32 rpap_u32PdIds[MAX_PHYDRV_PER_ARRAY];
} req_param_array_pdcfg_t;

/* LD init types - NOT a bitmap */
#define LDI_TYPE_NONE           0x0
#define LDI_TYPE_QUICK          0x01
#define LDI_TYPE_FOREGROUND	0x02
#define LDI_TYPE_BACKGROUND	0x04

/*LD synchronize state types - Not a bitmap*/
#define LD_SYNC_TYPE_NORMAL 0x0
#define LD_SYNC_TYPE_FORCESYNCED 0x01

typedef struct
{
    boolean_t rpal_bAutoId;     /* auto choose an Id for the logical drive */
    boolean_t rpal_bAutoSize;   /* use up the max supported size of the disk array */
    boolean_t rpal_bAutoFit;    /* auto fit the logical drive in a fragment - only valid for addld */
    boolean_t rpal_bAutoRaidLevel;  /* auto set the raid level best suitable for the configuration */
    u8 rpal_u8InitType;         /* whether to initialize the LD after creating it.
                                   LDI_TYPE_NONE: not to initialize the LD
                                   LDI_TYPE_xxx: to do the specified type of initialization on the LD */
    u8 rpal_u8SectorSizeCode;   /* sector size code, 0: 512bytes, 1~5: n*512bytes */
    u8 rpal_u8R5Algorithm;      /* valid only when rpal_u16RaidLevel is RAID5, RAID50 or RAID55.
                                    The values are defined in mic.h with ldd_Raid5AlgoSelect.
                                    If it is 0, the default RAID5_ALGO_RIGHT_ASYMMETRIC will be used */
    u8 rpal_u8SyncType;          /*force to set the LD to synchronized state or not*/
    u8 rpal_u8Reserved2[2];
    u16 rpal_u16RaidLevel;      /* ignored if AutoRaidLevel is set to TRUE */
    u16 rpal_u16NoOfAxle;       /* 0 means auto number of axle */
    u16 rpal_u16LdId;           /* ignored if AutoId is set to TRUE */
    u32 rpal_u32LDAttrib;       /* read/write policy */
    u32 rpal_u32StripeSize;     /* in blocks */
    u64 rpal_u64FragmentEndAddr;    /* in bytes, the ending address of the fragment where the ld tries to fit */
                                    /* Ignored if AutoFit is set to TRUE */
    u64 rpal_u64Size;           /* in blocks. Ingored if AutoSize is set to TRUE */
    u8 rpal_u8Name[MAX_LD_NAME_BYTES];
    u16 rpal_u16PreferredCtrlId;
    u32 rpal_u32LDFlags;          /* for nas */
    u8 rpal_u8Reserved3[10];      /* reserved for future */
} req_param_array_ld_t;

typedef struct
{
    u32 rpal_u32NumberOfLd;
    u32 rpal_u32NumRepeatLd;
    req_param_array_ld_t rpal_rpalLogDrvs[1];
} req_param_array_ldcfg_t;

typedef struct
{
    req_param_array_dacfg_t rpaa_rpadDaCfg;
    req_param_array_pdcfg_t rpaa_rpapPdCfg;
    req_param_array_ldcfg_t rpaa_rpalLdCfg;
} req_param_array_add_t;

typedef struct
{
    u32 rpml_u32LdId;
    boolean_t rpml_bCapacityExpansion; /* TRUE: rpml_u64Capacity is valid; FALSE: keep the original LD capacity */
    u8  rpml_u8SectorSizeCode; /* not used */
	u8  rpml_u8Reserved1[2];
    u64 rpml_u64Capacity;  /* the desired LD capacity (in blocks) to migrate to. It must be greater than the original capacity */
    u16 rpml_u16RaidLevel; /* the desired RAID level to migrate to */
    u16 rpml_u16NoOfAxles; /* the desired number of axles, valid only for some hybrid RAID levels, such as RAID 50
                              set to 0 if do not care */
    u32 rpml_u32StripeSize;/* the desired stripe size (in blocks) to migrate to. set to INVALID_STRIPE_SIZE if no change */
    u8 rpml_u8Reserved2[8];
} req_param_migrate_ldcfg_t;

typedef struct
{
    u32 rpmp_u32PdId;
    u32 rpmp_u32SequenceNo;
    u8 rpmp_u8Reserved[8];
} req_param_migrate_pdcfg_t;

typedef struct
{
    u32 rpm_u32DaId;
    u32 rpm_u32NumOfLd;
    u32 rpm_u32NumOfPd;
    u8 rpm_u8Reserved[12];
    req_param_migrate_ldcfg_t rpm_LdCfg[MAX_LOGDRV_PER_ARRAY];
    req_param_migrate_pdcfg_t rpm_PdCfg[MAX_PHYDRV_PER_ARRAY];
} req_param_migrate_t;

typedef struct
{
    u32 rpla_u32DiskArrayId;
    u32 rpla_u32Reserved;
    req_param_array_ldcfg_t rpla_rpalLdList;
} req_param_logdrv_add_t;

typedef struct
{
    u32 rpld_u32DiskArrayId;
    u32 rpld_u32Reserved;
    u32 rpld_u32Count;
    u32 rpld_u32Ids[1];     /* the list of ids to be deleted */
} req_param_logdrv_del_t;

typedef struct
{
    req_param_device_ids_t rpas_rpdiDeviceIds;
} req_param_array_settings_t;

/* please do NOT delete the following commented lines */

/*typedef req_param_ids_t req_param_array_setting_t;*/

typedef struct
{
    req_param_device_ids_t rpsi_rpdiDeviceIds;
} req_param_spare_info_t;

typedef struct
{
    boolean_t rps_bDedicated;  /* TRUE: dedicated spare; FALSE: global spare */
    boolean_t rps_bRevertible; /* TRUE: revertible spare; FALSE: non-revertible spare */
    boolean_t rps_bMPEnabled;  /* TURE: enable MP; FALSE: disable MP */
    u8 rps_u8Reserved;
    u16 rps_u16SpareId;        /* 0 ~ 255 are valid ids; 0xFFFF indicates invalid or auto spare id */
    u8 rps_u8Reserved1[10];
    u64 rps_u64StartLBA;       /* for non-grouping RAID engine only */
    u64 rps_u64SpareSize;      /* for non-grouping RAID engine only, in number of blocks */
    u32 rps_u32PdId;           /* id of the physical drive to be designated as a spare */
    u32 rps_u32NumberOfAssciatedArrays;  /* number of logical drive or array that this spare is dedicated to */ 
    u32 rps_u32ArrayIds[MAX_ASSOCIATED_ARRAYS_PER_SPARE];
                               /* the array of the ids of the associated arrays */
} req_param_sparecfg_t;

typedef struct
{
    u32 rpsa_u32NoOfSpare;
    u32 rpsa_u32Reserved;
    req_param_sparecfg_t rpsa_rpsSpares[1];
} req_param_spare_add_t;

typedef req_param_array_del_t req_param_spare_del_t;

typedef struct
{
    u32 rpr_u32ArrayId;
    u32 rpr_u32SeqNo;
    u32 rpr_u32Type;
    u32 rpr_u32Reserved;
} req_param_rbprogress_t;

typedef struct
{
    u32 rpr_u32ArrayId;
    u32 rpr_u32SeqNo;
    u32 rpr_u32PdId; /* valid for start only. Set to 0 for stop/pause/resume */
    u32 rpr_u32Type;
} req_param_rbctrl_t;

typedef struct
{
    u32 rpli_u32LdId; /* if it is 0xFFFF, all lds */
    u8 rpli_u8InitType; /* LDI_TYPE_QUICK, LDI_TYPE_FOREGROUND, or LDI_TYPE_BACKGROUND */
    u8 rpli_u8Reserved1[3]; /* for alignment */
    u8 rpli_u8Reserved2[12]; /* for alignment */
    u16 rpli_u16QuickInitSize; /* in MB. Valid only when rpli_u8InitType is equal to LD_INIT_TYPE_QUICK */
    u16 rpli_u16PatternLength; /* in MB. Valid only when rpli_u8InitType is equal to LD_INIT_TYPE_FOREGROUND */
    u8 rpli_u8Pattern[PMIC_SECTOR_SIZE];  /* Valid only when rpli_u8InitType is equal to LD_INIT_TYPE_FOREGROUND */
} req_param_ld_init_t;

typedef struct
{
    u32 rpls_u32LdId; /* if it is 0xFFFF, all lds */
    u8 rpls_u8Policy;         /* valid only for starting Synch */
    u8 rpls_u8Reserved[3];
} req_param_ld_synch_t;

typedef struct
{
    u32 rpr_u32LdId; /* if it is 0xFFFF, all lds */
    boolean_t rpr_bAutoFix;         /* valid only for starting RC */
    boolean_t rpr_bPauseOnError;    /* valid only for starting RC */
    u8 rpr_u8Reserved[2];
} req_param_rc_t;

typedef struct
{
    u32 rps_u32ArrayId; /* if it is 0xFFFF, all arrays - ?*/
    u8 rps_u8Reserved[4];
} req_param_sparechk_t;

#define EVENT_LOCATION_RAM      0x01
#define EVENT_LOCATION_MDD      0x02
#define EVENT_LOCATION_NVRAM    0x04

typedef struct
{
    u32 rpe_u32SeqNo;
    u32 rpe_u32Count;
    u8 rpe_u8EventLocation;    /* EVENT_LOCATION_RAM, MDD, or NVRAM */
    u8 rpe_u8Reserved[3];
    u32 rpe_u32SeverityMask;
    u64 rpe_u64EventClassMask;
} req_param_event_t;

typedef struct
{
    u32 rpec_u32SeverityMask;
    u32 rpec_u32Reserved;
    u64 rpec_u64EventClassMask;
} req_param_event_count_t;

typedef struct
{
    u32 rpes_u32SeverityMask;
    u32 rpes_u32Reserved;
    u64 rpes_u64EventClassMask;
} req_param_event_subscribe_t;

typedef struct
{
    u32 rpei_u32EventId;
    u32 rpei_u32EventCount;
} req_param_event_info_t;

/* iscsi */

typedef struct 
{
    u8 rpii_u8NodeId;
    u8 rpii_u8PortId;
    u8 rpii_u8PageCode;
    u8 rpii_u8Reserved[1];
    u16 rpii_u16SessId;
    u16 rpii_u16PortalId;
} req_param_iscsi_info_t;

typedef struct 
{
    u8 rpini_u8NodeId; 
    u8 rpini_u8Reserved[3];
    u16 rpini_u16NodeIndex;
    u16 rpini_u16NodeCount;
} req_param_iscsi_node_info_t;

typedef struct 
{
    u8 rpisi_u8NodeId; 
    u8 rpisi_u8Reserved;
    u16 rpisi_u16SessId;
    u8 rpisi_u16Reserved1[4];
} req_param_iscsi_sess_info_t;

typedef struct 
{
    u8 rpis_u8NodeId;
    u8 rpis_u8PortId;
    u8 rpis_u8PageCode;
    u8 rpis_u8Reserved[3];
    u16 rpis_u16SessId;
} req_param_iscsi_setting_t;

typedef struct 
{
    u8 rpip_u8PortId;
    u8 rpip_u8Reserved[3];
} req_param_iscsi_ping_t;

typedef struct 
{
    u16 rpsi_u16PortId;
    u16 rpsi_u16PortCount;
} req_param_slp_info_t;

typedef struct 
{
    u16 rpii_u16PortId;
    u16 rpii_u16PortCount;
} req_param_isns_info_t;

typedef struct 
{
    u8 rpcc_u8NodeId;
    u8 rpcc_u8Reserved[3];
    u16 rpcc_u16ChapIndex;
    u16 rpcc_u16ChapCount;
} req_param_chap_config_t;

typedef struct 
{
    u16 rpnl_u16PortId;
    u16 rpnl_u16NodeType;
} req_param_node_list_t;

/* Enclosure and FRU */
typedef struct 
{
    u16 rpei_u16EnclosureId;
    u16 rpei_u16Count;
    u8 rpei_u8Padding[4];
} req_param_encl_info_t;

typedef struct 
{
    u8 rpes_u8EnclosureId;
    u8 rpes_u8ElementType;  
    u8 rpes_u8Padding1[6];
} req_param_encl_settings_t;

typedef struct 
{
    u16 rpbi_u16EnclosureId;
    u16 rpbi_u16BatteryId;
    u16 rpbi_u16Padding1[2];
} req_param_bat_info_t;

typedef struct 
{
    u16 rpfi_u16EnclosureId;
    u16 rpfi_u16FruType;
    u16 rpfi_u16FruId;
    u16 rpfi_u16Padding1[1];
} req_param_fru_info_t;

typedef struct 
{
    u16 rpli_u16EnclosureId;
    u16 rpli_u16ArrayId;
    u16 rpli_u16LogdrvId;
    u16 rpli_u16PhydrvId;
} req_param_locate_info_t;

typedef struct 
{
    u16 rpet_u16Id; /* LD Id for IslaVista, PD Id for Napa */
    u16 rpet_u16TableType;
    u16 rpet_u16Reserved[2];
} req_param_error_table_t;

typedef struct
{
    req_param_device_ids_t rpi_rpdiDeviceIds;
} req_param_initiator_t;

typedef struct 
{
     req_param_device_ids_t rpl_rpdiDeviceIds;
} req_param_lmm_t;   

typedef struct 
{
    u8 rpli_u8CtrlId;
    u8 rpli_u8Reserved[7];
} req_param_lcd_info_t;

typedef struct 
{
    u8 rpls_u8CtrlId;
    u8 rpls_u8Reserved[7];
} req_param_lcd_settings_t;

/* request data */
typedef struct
{
    u32 rdc_u32Count;
} req_data_count_t;

typedef struct req_data_subsys_info
{
    DataBufferHeader_t rdsi_dbhHeader;
    micSubsystemInfo_t rdsi_msirSubsysInfo;
} req_data_subsys_info_t;

typedef struct req_data_subsys_setting
{
    DataBufferHeader_t rdss_dbhHeader;
    micSubsystemSettings_t rdss_micSubsysSettings;
} req_data_subsys_settings_t;

typedef struct req_data_clique_info
{
    DataBufferHeader_t rdci_dbhHeader;
    micCliqueGetInfo_t rdci_mcgiCliqueInfo;
} req_data_clique_info_t;

typedef struct req_data_clique_setting
{
    DataBufferHeader_t rdsi_dbhHeader;
    micCliqueSettings_t rdsi_mcgsCliqueSetting;
} req_data_clique_setting_t;

/*
 * the controller info data structure contains a DataBufferHeader_t, and 
 * following with some micControllerInfoPage0, micControllerInfoPage1, 
 * micControllerInfoPage2, and micControllerInfoPage3.
 */
typedef struct req_data_ctrl_info
{
    DataBufferHeader_t rdci_dbhHeader;
} req_data_ctrl_info_t;

/*
 * the controller settings data structure contains a DataBufferHeader_t, and 
 * following with some micCtrlSettingsPage0, micCtrlSettingsPage3.
 */
typedef struct req_data_ctrl_settings
{
    DataBufferHeader_t rdcs_dbhHeader;
} req_data_ctrl_settings_t;

typedef req_data_count_t req_data_ctrl_count_t;

/*
 * the physical drive info data structure contains a DataBufferHeader_t, and 
 * following with some micPDInfoPage0_t and micPDInfoPage1_t.
 */
typedef struct req_data_phydrv_info
{
    DataBufferHeader_t rdpi_dbhHeader;
} req_data_phydrv_info_t;

typedef struct
{
    u32 major;
    u32 minor;
    u32 oem;
    u32 build;
    u32 signature[2];
    u8 console_id;
    u8 host_no;
    u8 reserved0[2];
    u32 reserved[3];
} drive_info_t;

typedef struct
{
    u8 hni_u8Name[16];
    u8 hni_u8IPAddress[16];
    u8 hni_u8Reserved[32];
} host_network_info_t;

typedef struct
{
    u8 rdhi_u8HostName[64];   /* null teminated */
    u8 rdhi_u8HostOSName[128]; /* null teminated */
    u8 rdhi_u8Reserved[256];
    u32 rdhi_u16NumOfNetwork;
    u32 rdhi_u32Reserved2;
    host_network_info_t rdhi_hniNetwork[1];
} req_data_host_info_t;

/*
 * the physical drive settings data structure contains a DataBufferHeader_t, and 
 * following with some ???.
 */
typedef struct req_data_phydrv_settings
{
    DataBufferHeader_t rdps_dbhHeader;
} req_data_phydrv_settings_t;

typedef req_data_count_t req_data_phydrv_count_t;

/*
 * the logical drive info data structure contains a DataBufferHeader_t, and 
 * following with some micLogicalDriveInfo_t.
 */
typedef struct req_data_logdrv_info
{
    DataBufferHeader_t rdli_dbhHeader;
} req_data_logdrv_info_t;

/*
 * the logical drive settings data structure contains a DataBufferHeader_t, and 
 * following with variable number of micLogicalDriveSettings_t.
 */
typedef struct req_data_logdrv_settings
{
    DataBufferHeader_t rdls_dbhHeader;  /* not valid for set LD settings */
    micLogicalDriveSettings_t rdls_micLDSettings[1];
} req_data_logdrv_settings_t;

typedef req_data_count_t req_data_logdrv_count_t;

/*
 * the disk array info structure contains a DataBufferHeader_t, following with a 
  * number of micArrayConfigurationDef_t, micPhysicalDeviceDef_t, micLogicalDriveDef_t, and micComponentDeviceDef_t.
 */
typedef struct
{
    DataBufferHeader_t rdac_dbhHeader;
} req_data_array_cfg_t;

typedef struct 
{
    DataBufferHeader_t rdai_dbhHeader;
    micArrayInfo_t rdai_micArrayInfo[1];
} req_data_array_info_t;

typedef struct
{
    DataBufferHeader_t rdas_dbhHeader;
    micArraySettings_t rdas_micArraySettings[1];
} req_data_array_settings_t;

typedef struct
{
    DataBufferHeader_t rdmp_dbhHeader;
    micMigrationProgress_t rdmp_micMigrateProg[1];
} req_data_migrate_progress_t;

/*
typedef req_data_count_t req_data_array_count_t;
*/

/*
 * the spare info structure contains a DataBufferHeader_t, following with a 
 * number of micArrayConfigurationDef_t.
 */
typedef struct
{
    DataBufferHeader_t rdsi_dbhHeader;
} req_data_spare_info_t;

typedef struct
{
    DataBufferHeader_t rde_dbhHeader;
    Event_t rde_micEvents[1];
} req_data_event_t;

typedef struct
{
    DataBufferHeader_t rdei_dbhHeader;
    micEventInfo_t rdei_EventInfo[1]; 
} req_data_event_info_t;

typedef struct
{
    u32 elst_u32FirstSeqNo;
    u32 elst_u32LastSeqNo;
    u32 elst_u32NumValidEvents;
    u32 elst_u32LastUpdate;
    u8  elst_Reserved0[48];
} EventLocationStats_t;

typedef struct
{
    DataBufferHeader_t rdes_dbhHeader;
    EventLocationStats_t rdes_elstEventStats[1];
} req_data_event_stats_t;

typedef req_data_count_t req_data_event_count_t;

typedef struct
{
    DataBufferHeader_t rdmp_dbhHeader;
    micMediaPatrolProgress_t rdmp_micMPProgress;
} req_data_mpprogress_t;

/*Added for NAPA */
typedef struct
{
    DataBufferHeader_t rdmp_dbhHeader;
    micHBAMediaPatrolProgress_t rdmp_micMPProgress;
} req_data_hba_mpprogress_t;

typedef struct
{
    DataBufferHeader_t rdr_dbhHeader;
    micRebuildProgress_t  rdr_micRbProgress[1];   
} req_data_rbprogress_t;

typedef struct
{
    DataBufferHeader_t rdl_dbhHeader;
    micLdiProgress_t rdl_micLdiProgress[1];
} req_data_ldiprogress_t;

typedef struct
{
    DataBufferHeader_t rds_dbhHeader;
    micBKSyncProgressData_t rds_micSynchProgress[1];
} req_data_synchprogress_t;

typedef struct
{
    DataBufferHeader_t rdr_dbhHeader;
    micRCProgressData_t rdr_micRCProgress[1];
} req_data_rcprogress_t;

typedef struct
{
    DataBufferHeader_t rds_dbhHeader;
    micSpareCheckStatus_t  rds_micStatus[1];   
} req_data_sparechk_t;

/* for iscsi info and settings */
typedef struct
{
    DataBufferHeader_t rdin_dbhHeader;
    micISCSINodeParameterInfoPage_t rdin_micISCSINode;
} req_data_iscsi_node_t;

typedef struct
{
    DataBufferHeader_t rdii_dbhHeader;
} req_data_iscsi_info_t;

typedef struct
{
    DataBufferHeader_t rdini_dbhHeader;
    micISCSIExtendedNodeParameterInfoPage_t rdini_micISCSINode;
} req_data_iscsi_node_info_t;

typedef struct
{
    DataBufferHeader_t rdis_dbhHeader;
} req_data_iscsi_setting_t;

typedef struct 
{
    DataBufferHeader_t rdip_dbhHeader;
    micISCSIPingControlData_t rdip_micISCSIPing;
} req_data_iscsi_ping_t;

typedef struct 
{
    DataBufferHeader_t rdsi_dbhHeader;
    micSLPInfoSettings_t rdsi_micSLPInfo;
} req_data_slp_info_t;

typedef struct 
{
    DataBufferHeader_t rdii_dbhHeader;
    micISNSInfoSettings_t rdii_micISNSInfo;
} req_data_isns_info_t;

typedef struct 
{
    DataBufferHeader_t rdcc_dbhHeader;
    micChapConfigData_t rdcc_micChapConfig;
} req_data_chap_config_t;

typedef struct 
{
    DataBufferHeader_t rdnl_dbhHeader;
    micNodeInfo_t rdnl_micNodeInfo;
} req_data_node_list_t;

typedef struct
{
    DataBufferHeader_t rdi_dbhHeader;
    micGetInitiatorList_t rdi_micList;
} req_data_initiator_t;

typedef struct
{
    DataBufferHeader_t rdl_dbhHeader;
    micLMMTable_t rdl_micTable;
} req_data_lmm_t;

/* flash */
typedef struct 
{
#define FLASH_XFER_THRU_INBAND   0
#define FLASH_XFER_THRU_TFTP     1
#define FLASH_XFER_THRU_HTTP     2
#define FLASH_XFER_THRU_XMODEM   3
    u8 rpf_u8TransferMethod;
    u8 rpf_u8Reserved[7];
    union
    {
        struct
        { 
            u8 rpf_u8HostName[MAX_HOST_NAME_LEN];
            u32 rpf_u32PortNumber;
	    u8 rpf_u8FileName[MAX_IMAGE_NAME_LEN];
        } rpf_sTFTP;
        u8 rpf_u8ImageFilePath[MAX_PATH_LENGTH+1];
    } rpf_uTransfer;
} req_param_flash_t;

typedef struct
{
#define FLASH_STATUS_OK          0
#define FLASH_STATUS_ERROR       1
#define FLASH_STATUS_ABORTED     2
#define FLASH_STATUS_UNKNOWN     3
#define FLASH_STATUS_NA     	 0xFF /* not applicable, in the case ctrl 0 is not accessible during single ctrl flash upgrade*/
    u8 fp_u8Status;
    u8 fp_u8Reserved;
#define FLASH_STAGE_XFERING      0
#define FLASH_STAGE_XFERED       1
#define FLASH_STAGE_VALIDATING   2
#define FLASH_STAGE_VALIDATED    3
#define FLASH_STAGE_FLASHING     4
#define FLASH_STAGE_FLASHED      5
#define FLASH_STAGE_READY        6
#define FLASH_STAGE_UNKNOWN      7
#define FLASH_STAGE_NA     		 0xFF /* not applicable, in the case ctrl 0 is not accessible during single ctrl flash upgrade */

    u8 fp_u8Stage;
    u8 fp_u8Percentage;
	/* use the reserved 4 bytes for ctrl 1 每 applicable to E-Class only */    
	u8 fp_u8Status1;
	u8 fp_u8Stage1;
	u8 fp_u8Percentage1;
	u8 fp_u8Reserved2;
} flash_progress_t;

typedef struct
{
    ih_t rdfih_ih;
} req_data_flash_image_header_t;

typedef struct
{
    u8 rpfiv_u8EnclID;
    u8 rpfiv_u8CtrlID;
    u8 rpfiv_u8Reserved[6];
} req_param_flash_image_version_t;

typedef struct
{
    DataBufferHeader_t rdfiv_micHeader;
    micFlashImageVersionInfo_t rdfiv_micFlashImageVersionInfo;
} req_data_flash_image_version_t;

/* Enclosure and FRU */
typedef struct
{
    DataBufferHeader_t rdei_dbhHeader;
    MEI_t rdei_meiEnclInfo;
} req_data_encl_info_t;

typedef struct
{
    DataBufferHeader_t rdes_dbhHeader;
    MESH_t rdes_meshHeader;
} req_data_encl_settings_t;

typedef struct
{
    DataBufferHeader_t rdbi_dbhHeader;
    MBI_t rdbi_mbiBatInfo;
} req_data_bat_info_t;

typedef struct
{
    DataBufferHeader_t rdfi_dbhHeader;
    MFRU_t rdfi_mfruFRUInfo;
} req_data_fru_info_t;

/* lock management */
typedef struct
{
    boolean_t rpl_bExtendLock;
    boolean_t rpl_bForceLock;
    u8 rpl_u8LockKey;
    u8 rpl_u8Reserved;
    u32 rpl_u32LockTime; /* in number of seconds */
} req_param_lock_t;

typedef struct
{
    boolean_t rdl_bOwner;
    u8 rdl_u8LockKey;
    u8 rdl_u8Reserved[6];
    u64 rdl_u64ExpirationTime; /* in number of seconds since 0:0:0 Jan 1, 1970 */
} req_data_lock_t;

typedef struct 
{
    DataBufferHeader_t rdet_dbhHeader;
    micGetErrTableData_t rdet_micTable;
} req_data_error_table_t;


typedef struct
{
    DataBufferHeader_t rdcs_dbhHeader;
    micStatsController_t rdcs_micStats;
} req_data_ctrl_stats_t;


typedef struct
{
    DataBufferHeader_t rdps_dbhHeader;
    micStatsPhysicalDrive_t rdps_micStats;
} req_data_phydrv_stats_t;

typedef struct
{
    DataBufferHeader_t rdpse_dbhHeader;
} req_data_phydrv_stats_ext_t;

typedef struct
{
    DataBufferHeader_t rdls_dbhHeader;
    micStatsLogicalDrive_t rdls_micStats;
} req_data_logdrv_stats_t;

typedef struct
{
    DataBufferHeader_t rdt_dbhHeader;
    micCtlTime_t rdt_micTime;
} req_data_time_t;

typedef struct
{
    u32 rpb_u32PdId;
    u32 rpb_u32Padding;
} req_param_bbm_t;

typedef struct
{
    DataBufferHeader_t rdb_dbhHeader;
    bbmDefectList_t rdb_micBbmDefectList;
} req_data_bbm_t;

/* req_data_driver_info_t is HBA specific */
typedef struct
{
    u8 rddi_u8MajorNo;
    u8 rddi_u8MinorNo;
    u8 rddi_u8BuildNo;
    u8 rddi_u8Reserved;
    u32 rddi_u32OEMCode;
    u8 rddi_u8BuildDate;
    u8 rddi_u8BuildMonth;
    u16 rddi_u16BuildYear;
    u8 rddi_u8Reserved2[52];   
} req_data_driver_info_t; 

#define MAX_BYPASS_CMD_CDB_LENGTH 32
#define MAX_BYPASS_CMD_SENSE_LENGTH 64

typedef struct
{
    u32 bc_u32Status;      /* command completion status */
    u32 bc_u32Timeout;    
    u8 bc_u8Reserved[6];   /* reserved for 8 byte alignment */
    u8 bc_u8DataDirection; /* data direction: I2IPC_RW_NONE, I2IPC_RW_READ, I2IPC_RW_WRITE */
    u8 bc_u8CDBLength;   /* the actual length of the CDB */
    u8 bc_u8CDB[MAX_BYPASS_CMD_CDB_LENGTH]; /* by-pass command CDB */
    u32 bc_u32SenseLength; /* the expected sense data length */
    u32 bc_u32ReturnedSenseLength; /* length of the sense retrieved */
    u8 bc_u8SenseBuffer[MAX_BYPASS_CMD_SENSE_LENGTH]; /* sense buffer */
    u32 bc_u32DataLength;  /* length of output data or expected input data */
    u32 bc_u32ReturnedDataLength; /* length of the data retrieved */
    u8 * bc_pu8DataBuffer; /* the data buffer */
#ifndef SUPPORT_64_BIT
    u8 * bc_pu8Padding;    /* pad to 8 byte aligned */
#endif
} bypass_cmd_t;

typedef struct
{
    u8 rps_u8CtrlId;
    u8 rps_u8ShutdownType;
    u8 rps_u8Reserved[6];
} req_param_shutdown_t;

typedef struct
{
    u8 rpf_u8FilePath[256];
} req_param_filesync_t;

typedef struct
{
    u8 rpfp_u8PortId;
    u8 rpfp_u8PageCode;
    u8 rpfp_u8CtrlId;
    u8 rpfp_u8Reserved[5];
} req_param_fc_port_t;

typedef struct
{
    DataBufferHeader_t rdfni_dbhHeader;
    micFCConfigPage_Status_t rdfni_mfsInfo;
} req_data_fc_info_t;

typedef struct
{
    DataBufferHeader_t rdfni_dbhHeader;
    
} req_data_fc_port_info_t;

typedef struct
{
    DataBufferHeader_t rdfld_dbhHeader;
    micFCConfigPage_LoggedIn_Device_List_t rdfld_mfldList;    
} req_data_fc_loggedin_device_t;

typedef struct
{
    DataBufferHeader_t rdfps_dbhHeader;
    micFCConfigPage_Parameters_t rdfps_mfpSetting;
} req_data_fc_port_setting_t;

typedef struct
{
    DataBufferHeader_t rdfps_dbhHeader;
    micFCConfigPage_Known_Initiator_List_t rdfil_mfiList;
} req_data_fc_initiator_list_t;

typedef struct
{    
	u16 rpsp_u16PortId;
	u8 rpsp_u16Padding[6];
} req_param_scsi_port_t;

typedef struct
{
    DataBufferHeader_t ridsp_dbhHeader;
    micPSCSIPortInfo_t ridsp_SCSIPortInfo[1];
} req_data_scsi_port_info_t;

typedef struct
{
    DataBufferHeader_t ridsp_dbhHeader;
    micPSCSIPortStatistics_t rsdsp_SCSIPortStats[1];
} req_data_scsi_port_stats_t;


typedef struct
{
    DataBufferHeader_t rdsp_dbhHeader;
    micPSCSIPortSettings_t rdsp_SCSIPortSettings[1];
} req_data_scsi_port_settings_t;

typedef struct
{    
	u16 rpst_u16PortId;
	u16 rpst_u16TargetId;
	u8 rpst_u8Padding[4];
} req_param_scsi_target_t;

typedef struct
{
    DataBufferHeader_t rdsp_dbhHeader;
    micPSCSITargetInfo_t rdsp_SCSITargetInfo[1];
} req_data_scsi_target_info_t;

typedef struct
{
    DataBufferHeader_t rdsp_dbhHeader;
    micPSCSITargetSettigns_t rdspd_SCSITargetSettings[1];
} req_data_scsi_target_settings_t;

typedef struct
{
    DataBufferHeader_t rdsp_dbhHeader;
    micPSCSITargetStatistics_t rdsp_SCSITargetStats[1];
} req_data_scsi_target_stats_t;

typedef struct
{
    DataBufferHeader_t rdsp_dbhHeader;
    micLMMTable_t rdsplt_SCSIPortLmmTable[1];
} req_data_scsi_port_lmm_table_t;

/* Feature Bits - 64 bytes */
typedef struct
{
    /* Host interface features 每 32 bytes */
    
    /* Host interface type: low word for subsystem; high word for HBA */
#define PI_FB_HOST_INTERFACE_ISCSI   0x00000001
#define PI_FB_HOST_INTERFACE_FC      0x00000002
#define PI_FB_HOST_INTERFACE_SCSI    0x00000004
#define PI_FB_HOST_INTERFACE_SAS     0x00000008
#define PI_FB_HOST_INTERFACE_PCIE    0x00010000
#define PI_FB_HOST_INTERFACE_PCIX    0x00020000
    u32 fb_u32HostInterface;
    u8 fb_u8HostInterfaceReserved2[28];
    
    /* Device interface features 每 32 bytes */
    
    /* Device interface type */
#define PI_FB_DEVICE_INTERFACE_PATA  0x0001
#define PI_FB_DEVICE_INTERFACE_SATA  0x0002
#define PI_FB_DEVICE_INTERFACE_SAS   0x0004
#define PI_FB_DEVICE_INTERFACE_SCSI  0x0008
#define PI_FB_DEVICE_INTERFACE_FC    0x0010
    u16 fb_u16DeviceInterface;
    u8 fb_u8DeviceInterfaceReserved[30];
    
    /* RAID features 每 128 bytes */
    
    /* RAID Levels: low word for simple RAID Levels; high word for hybrid RAID Levels */
#define PI_FB_RAID_0     0x00000001
#define PI_FB_RAID_1     0x00000002
#define PI_FB_RAID_1E    0x00000004
#define PI_FB_RAID_5     0x00000008
#define PI_FB_RAID_6     0x00000010
#define PI_FB_RAID_JBOD  0x00008000
#define PI_FB_RAID_10    0x00010000
#define PI_FB_RAID_50    0x00020000
#define PI_FB_RAID_51    0x00040000
#define PI_FB_RAID_55    0x00080000
#define PI_FB_RAID_60    0x00100000
    u32 fb_u32RAIDLevels;
    
#define PI_RFM_RAID6_MIGRATION_SUPPORTED     0x00000001
#define PI_RFM_RAID6_MIGRATION_OCE_SUPPORTED 0x00000002
#define PI_RFM_RAID6_MIGRATION_RLM_SUPPORTED 0x00000004
    u32 fb_u32RAIDFeaturesMask;
    
#define PI_HAFM_HA_SUPPORTED                 0x00000001
#define PI_HAFM_LUN_AFFINITY_SUPPORTED       0x00000002
#define PI_HAFM_MAINTENANCE_MODE_SUPPORTED   0x00000004
#define PI_HAFM_ACTIVE_STANDBY_SUPPORTED     0x00000008
#define PI_HAFM_UPS_SUPPORTED                0x00000010
    u32 fb_u32HAFeaturesMask;
    u8 fb_u8RAIDReserved[116];
    
    /* software feature bits 每 32 bytes */
#define PI_FB_CIM_SUPPORTED     0x0001
    u32 fb_u32SWFeaturesMask;
    u8 fb_u8SWReserved2[28];
    
#define PI_RAID_ENGINE_DEFAULT               0x0
#define PI_RAID_ENGINE_V3                    0x1
#define PI_RAID_ENGINE_V4                    0x2
    u8 fb_u8RAIDEngine;
    /* reserved 每 31 bytes */
    u8 fb_u8Reserved[31];
    
} feature_bits_t;

/* RAID Capabilities - 192 bytes */

typedef struct
{
    u16 rc_u16MaxPhyDrvs;
    u16 rc_u16MaxLogDrvs;
    u16 rc_u16MaxDataArrays;
    u16 rc_u16MaxSpareArrays;

    u16 rc_u16SpareArrayIDStart;
    u16 rc_u16SpareArrayIDEnd;
    u16 rc_u16MaxPhyDrvPerArray;
    u16 rc_u16MaxLogDrvPerArray;

    u16 rc_u16MaxAxlePerLogDrv;
    u16 rc_u16MaxPhyDrvPerRaid5;
    u16 rc_u16MaxPhyDrvPerRaid6;
    u16 rc_u16MaxSparePerArray;

    u16 rc_u16MaxArrayPerSpare;
    u16 rc_u16MaxMissingPhyDrv;	
    u16 rc_u16MaxTransitPhyDrv;
    u16 rc_u16MaxPhyDrvID;

    u8  rc_u8MaxParityDrivesPerRaid6;
    u8  rc_u8Reserved;
    u16 rc_u16MaxEnclosureID;
    u8  rc_u8Reserved8[60];

#define PI_RC_STRIPE_SIZE_8KB 0x00000001
#define PI_RC_STRIPE_SIZE_16KB 0x00000002
#define PI_RC_STRIPE_SIZE_32KB 0x00000004
#define PI_RC_STRIPE_SIZE_64KB 0x00000008
#define PI_RC_STRIPE_SIZE_128KB 0x00000010
#define PI_RC_STRIPE_SIZE_256KB 0x00000020
#define PI_RC_STRIPE_SIZE_512KB 0x00000040
#define PI_RC_STRIPE_SIZE_1MB 0x00000080
#define PI_RC_STRIPE_SIZE_2MB 0x00000100
#define PI_RC_STRIPE_SIZE_4MB 0x00000200

    u32 rc_u32StripeSizeMask; 

#define PI_RC_SECTOR_SIZE_512B 0x00000001
#define PI_RC_SECTOR_SIZE_1KB 0x00000002
#define PI_RC_SECTOR_SIZE_2KB 0x00000004
#define PI_RC_SECTOR_SIZE_3KB 0x00000008
    u32 rc_u32SectorSizeMask; 
    u16 rc_u16Reserved1[12];

    /* error tables */
    u32 rc_u32MaxRCTEntry;
    u32 rc_u32MaxWCTEntry;

    u32 rc_u32MaxIBTEntry;
    u32 rc_u32MaxBBMEntry;

    u32 rc_u32Reserved2[4];
    u8  rc_u8Reserved2[16];

    /* events */
    u32 rc_u32MaxEventInRam;
    u32 rc_u32MaxEventInNvram;

    u32 rc_u32Reserved3[4];

    /* components */
    u8 rc_u8MaxEnclosure;
    u8 rc_u8MaxCtrl;
    u8 rc_u8MaxHostPortPerCtrl;   /* front end */
    u8 rc_u8MaxExpPortPerCtrl;	   /* for JBOD expansion */
    u8 rc_u8MaxMgmtPortPerCtrl;
    u8 rc_u8MaxComPortPerCtrl;
    u8 rc_u8MaxSubsys; /* for subsystem level high availability */
    u8 rc_u8Reserved4;

    u8 rc_u8Reserved5[16];

    /* LMM - apply to subsytems only */
    u16 rc_u16MaxLMMEntries;
    u16 rc_u16MaxTargets;
    u16 rc_u16MaxLunsPerTarget;
    boolean_t rc_bMaintenance;
    u8 rc_u8CurrentCtrlId;
    u8 rc_u8IsMaster;
    u16 rc_u16Reserved7[3];
} raid_capabilities_t;

/* iSCSI Capability - 64 bytes */
typedef struct
{
    u32 ic_u32HostInterface; /* must be PI_FB_HOST_INTERFACE_ISCSI */  
    u16 ic_u16MaxiSCSITargetNodes;
    u16 ic_u16MaxiSCSIInitiatorNodes;
    
    u16 ic_u16MaxiSCSIPortalGroup;
    u16 ic_u16MaxiSCSIPortal;
    u16 ic_u16MaxiSCSIPortalGroupPerNode;
    u16 ic_u16MaxiSCSIPortalPerPortalGroup;
    
    u16 ic_u16MaxChapRecordsPerNode;
    u16 ic_u16MaxLocalChapRecordsPerNode;
    u16 ic_u16MaxPeerChapRecordsPerNode;
    u16 ic_u16Reserved1;
    
    u16 ic_u16MaxiSCSISessionsPerNodePG;
    u16 ic_u16MaxLoginInitiatorsPerNode;
    u16 ic_u16MaxiSNSInitiators;
    u16 ic_u16MaxiSNSTargets;

#define PI_IC_MULTI_NODE_SUPPORTED               0x00000001
#define PI_IC_VLAN_SUPPORTED                           0x00000002
#define PI_IC_LINK_AGGREGATION_SUPPORTED   0x00000004
#define PI_IC_SLP_SUPPORTED                             0x00000008
	u32 ic_u32FeatureMask;
#define PI_IC_ISCSI_STATSTICS_VER_1              0x00 // iscsi stats supported by first generation iSCSI host interface chip
#define PI_IC_ISCSI_STATSTICS_VER_2              0x01 // iscsi stats supported by second generation iSCSI host interface chip
    u8 ic_u8iSCSIStatsVer;

    u8 ic_u8Reserved2[91];
} iscsi_capabilities_t;

/* FC Capabilities - 64 bytes */
typedef struct
{
    u32 fc_u32HostInterface;  /* must be PI_FB_HOST_INTERFACE_FC */
    u16 fc_u16MaxLoginInitiatorsPerPort;
    u16 fc_u16MaxInitiatorsFromNameServer;
    
    u32 fc_u32SupportedSpeedMask;   /* the mask of MPI_FCPORTPAGE_SUPPORT_xGBIT_SPEED defined in fc_mic_exp.h */

    u16 fc_u16Reserved[54];
} fc_capabilities_t;

typedef struct
{
    u32 sc_u32HostInterface;  /* must be PI_FB_HOST_INTERFACE_FC */
    u16 sc_u16MaxLoginInitiatorsPerController;
    u16 sc_u16MaxLoginInitiatorsPerPort;
    u16 sc_u16Reserved[56];
} sas_capabilities_t;

/* Generic Host Interface Capabilities - 64 bytes */
typedef struct
{
    u32 ghc_u32HostInteface; /* PI_FB_HOST_INTERFACE_ISCSI or PI_FB_HOST_INTERFACE_FC */
    u8 ghc_u8Reserved[60];
} generic_hi_capability_t;

/* firmware capabilities - 256 bytes */
typedef struct
{
    raid_capabilities_t fc_rcRAIDCapabilities;
    union
    {
        generic_hi_capability_t fc_ghcGenericCapabilities;
        iscsi_capabilities_t fc_iciSCSICapabilities;
        fc_capabilities_t fc_fcFCCapabilities;
        sas_capabilities_t fc_scSASCapabilities;
    } fc_uHiCapabilities; 
} firmware_capabilities_t;

typedef struct
{
    u8 cci_u8CtrlId;
    boolean_t cci_bMaintenance;
    u8 cci_bIsMasterBootUp;
    u8 cci_u8Reserved[5]; 
} current_controller_info_t;

typedef struct
{
    DataBufferHeader_t rdst_dbhHeader;
    MicSasMgtStruct_t rdst_topology[1];
} req_data_sas_topology_t;

typedef struct
{
	u8 rpst_u8EnclosureId;
    u8 rpst_u8Count;
	u8 rpst_u8Padding[6];
} req_param_sas_topology_t;

typedef struct
{
	u8 rpssd_u8EnclosureId;
    u8 rpssd_u8ExpanderId;
	u8 rpssd_u8Padding[6];
} req_param_sas_smp_discover_t;

typedef struct
{
    DataBufferHeader_t rdssd_dbhHeader;
    micRespSASSMPDiscover_t rdssd_discover[1];
} req_data_sas_smp_discover_t;

typedef struct
{
	u8 rpspe_u8EnclosureId;
    u8 rpspe_u8ExpanderId;
	u8 rpspe_u8Padding[6];
} req_param_sas_phy_errorlog_t;

typedef struct
{
    DataBufferHeader_t rdspe_dbhHeader;
    micRespSasSMPErrorLogHdr_t rdspe_errorlog[1];
} req_data_sas_phy_errorlog_t;

typedef struct
{
    DataBufferHeader_t rdscpe_dbhHeader;
    micRespC2CSasSMPErrorLogHdr_t rdscpe_errorlog[1];
} req_data_sas_c2cport_phy_errorlog_t;

typedef struct
{
	u8 rpspc_u8EnclosureId;
    u8 rpspc_u8ExpanderId;
    u8 rpspc_u8PhyId;
    u8 rpspc_u8OpCode;
	u8 rpspe_u8Padding[4];
} req_param_sas_phy_control_t;

typedef struct
{
    u8 rpscpc_u8PhyId;
    u8 rpscpc_u8OpCode;
    u8 rpscpc_u8Reserved[6];
} req_param_sas_c2cport_phy_control_t;

typedef struct
{
    u8 es_u8EnclWarningThresh;
    u8 es_u8EnclCriticalThresh;
    u8 es_u8CtrlWarningThresh;
    u8 es_u8CtrlCriticalThresh;
    u8 es_u8EnclosureType;
    u8 es_u8CoolerMode;
    u8 es_u8reserved[2];
    u8 es_u8reserved2[64];
} enclosure_setting_t;

typedef struct
{
	u8 rpspi_u8CtrlId;
    u8 rpspi_u8PortId;
    u8 rpspi_u8PageCode;
	u8 rpspi_u8Padding[5];
} req_param_sashost_port_info_t;

typedef struct
{
	DataBufferHeader_t rdspi_dbhHeader;
    micSASPortStatus_t rdspi_PortStatus;
} req_data_sashost_port_info_t;

typedef struct
{
    DataBufferHeader_t rdsps_dbhHeader;
    micFrontEndSASAllPhyStats_t rdsps_PHYStats;
} req_data_sashost_phy_stats_t;

typedef struct
{
	u8 rpsps_u8CtrlId;
    u8 rpsps_u8PortId;
    u8 rpsps_u8PageCode;
	u8 rpspe_u8Padding[5];
} req_param_sashost_port_setting_t;

typedef struct
{
	DataBufferHeader_t rdsps_dbhHeader;
    micExternalPortSettingsGenPage0 rdsps_PortSetting;
} req_data_sashost_port_setting_t;

typedef struct
{
    DataBufferHeader_t rdfps_dbhHeader;
    micFrontEndInitiatorList_t rdsil_mfiList;
} req_data_sashost_initiator_list_t;

typedef struct 
{
    u8 rpvc_u8NodeId;
    u8 rpvc_u8Reserved[3];
    u16 rpvc_u16VlanIndex;
    u16 rpvc_u16VlanCount;
} req_param_vlan_config_t;

typedef struct 
{
    DataBufferHeader_t rdvc_dbhHeader;
    micVLANInfoSettings_t rdvc_micVlanConfig;
} req_data_vlan_config_t;

typedef struct 
{
    u8 rplac_u8NodeId;
    u8 rplac_u8Reserved[3];
    u16 rplac_u16LinkAggrIndex;
    u16 rplac_u16LinkAggrCount;
} req_param_link_aggr_config_t;

typedef struct 
{
    DataBufferHeader_t rdlac_dbhHeader;
    micLinkAggrInfoSettings_t rdvc_micLinkAggrConfig;
} req_data_link_aggr_config_t;

typedef struct 
{
    u8 rpipi_u8NodeId;
    u8 rpipi_u8Reserved[3];
    u16 rpipi_u16PortalIndex;
    u16 rpipi_u16PortalCount;
} req_param_iscsi_portal_info_t;

typedef struct 
{
    DataBufferHeader_t rdipi_dbhHeader;
    micISCSIPortalInfo_t rdipi_micPortalConfig;
} req_data_iscsi_portal_info_t;

typedef struct 
{
    DataBufferHeader_t rdifi_dbhHeader;
    micISCSIiSNAPMicrocodeUpdate_t rdifi_miciscsiUpdate;
} req_data_iscsi_fw_info_t;

typedef struct
{
    DataBufferHeader_t rdscpe_dbhHeader;
    LmmMapInfo_t rdsm[1];
} req_data_slotwwn_mapping_t;

typedef struct
{
    DataBufferHeader_t rdscpe_dbhHeader;
    MicZoningGroups_t rdzg;
} req_data_zoning_groups_t;

typedef struct
{
	u8 rpzp_u8CtrlId;
    u8 rpzp_u8GroupId;
	u8 rpzp_u8Padding[6];
} req_param_zoning_permission_t;

typedef struct
{
    DataBufferHeader_t rdscpe_dbhHeader;
    MicZoningGroupPermissionTable_t rdzp;
} req_data_zoning_permission_t;

#define PTC_PROTOCOL_TYPE_UNKNOWN 0
#define PTC_PROTOCOL_TYPE_ATA 1
#define PTC_PROTOCOL_TYPE_SCSI 2

#define CMD_RW_NONE I2IPC_RW_NONE
#define CMD_RW_READ I2IPC_RW_READ
#define CMD_RW_WRITE I2IPC_RW_WRITE

#define MAX_PASSTHRU_CDB_LENGTH MAX_BYPASS_CMD_CDB_LENGTH
#define MAX_PASSTHRU_SENSE_LENGTH MAX_BYPASS_CMD_SENSE_LENGTH

typedef struct
{
    u8 ptc_u8DeviceType;
    u8 ptc_u8Reserved;
    u16 ptc_u16DeviceID;
    u8 ptc_u8Reserved1[4];

    u8 ptc_u8CmdProtocol; /* PTC_PROTOCOL_TYPE_UNKNOWN, _ATA, _SCSI */
    u8 ptc_u8DataDirection; /* data direction: CMD_RW_NONE, _READ, _WRITE */
    u8 ptc_u8UniqueCmdId;
    u32 ptc_u32OpCode;
    u8 ptc_u8Reserved2[1];

    u32 ptc_u32Timeout;
    u32 ptc_u32CompletionStatus;

    u8 ptc_u8CDBLength;   /* the actual length of the CDB */
    u8 ptc_u8Reserved3[7];
    u8 ptc_u8CDB[MAX_PASSTHRU_CDB_LENGTH]; /* the direct command CDB */

    u8 ptc_u8ReturnedSenseLength; /* length of the sense retrieved */
    u8 ptc_u8Reserved4[7];   /* reserved for 8 byte alignment */
    u8 ptc_u8SenseBuffer[MAX_PASSTHRU_SENSE_LENGTH]; /* sense buffer */

    u32 ptc_u32DataLength;  /* length of output data or expected input data */
    u32 ptc_u32ReturnedDataLength; /* length of the data retrieved */
    u8 * ptc_pu8DataBuffer; /* the data buffer */
#ifndef SUPPORT_64_BIT
    u8 * ptc_pu8Padding;    /* pad to 8 byte aligned */
#endif
} pass_through_cmd_t;


typedef struct
{
    u8 rpuci_u8UniqueCmdId;
    u8 rpuci_u8Reserved[3];
    u32 rpuci_u32Timeout;
} req_param_unique_cmd_id_t;

typedef struct
{
    DataBufferHeader_t rduci_micHeader;
    micUcidOrCl_t rduci_micUniqueCmdId;
} req_data_unique_cmd_id_t;

typedef struct
{
    DataBufferHeader_t rdli_dbhHeader;
    micLcdDetectionStatus_t rdli_mldsLcdInfo;
} req_data_lcd_info_t;

typedef struct
{
    DataBufferHeader_t rdls_dbhHeader;
    micLcdConfigureParameter_t rdls_mlcpLcdSettings;
} req_data_lcd_settings_t;

#define MAX_COMPONENT_NAME_LEN       80
#define DEBUG_I2_LOG_NAME            "/tmp/i2.log"

typedef struct
{
    u8 rpsds_u8ComponentName[MAX_COMPONENT_NAME_LEN];
    u8 rpsds_u8LogFileName[MAX_PATH_LENGTH+1];
    u8 rpsds_u8TraceLevel;
    boolean_t rpsds_bLogToStdout;
    u8 rpsds_u8Reserved[6];
    u16 rpsds_u16LogFileSize; /* in kb */
    u16 rpsds_u16CtrlId;
    u16 rpsds_u16Reserved1[82]; 

} req_param_software_debug_settings_t;

typedef struct
{
    boolean_t rpfds_bLogToStdout;
    u8 rpfds_u8Reserved[7];
    u16 rpfds_u16CtrlId;
    u16 rpfds_u16Reserved[3]; 
} req_param_firmware_debug_settings_t;

typedef struct
{
    u16 rppss_u16CtrlId;
    u16 rppss_u16Reserved1[3]; 
} req_param_power_schedule_setting_t;

typedef struct
{
    DataBufferHeader_t rdpss_dbhHeader;
micPowerScheduleStatus_t rdpss_micPowerOnStats;
micPowerScheduleStatus_t rdpss_micPowerOffStats;
} req_data_power_schedule_setting_t;

/********** For UPS *********/
typedef struct
{
    /* The id of the UPS: 0 or 1 (same id as controller)*/
    req_param_device_ids_t rpus_rpdiDeviceIds;
} req_param_ups_status_t;


typedef struct
{
    DataBufferHeader_t rdus_dbhHeader;
    micUpsStatusData_t rdus_mcupsInfo[1];
} req_data_ups_status_t;

typedef struct
{
    /* The id of the UPS: 0 or 1 (same id as controller)*/
    req_param_device_ids_t rpus_rpdiDeviceIds;
} req_param_ups_settings_t;

typedef struct
{
    DataBufferHeader_t rdus_dbhHeader;
    micUpsSettingData_t rdus_mcupssetting[1];
} req_data_ups_settings_t;

typedef struct
{
    DataBufferHeader_t rduct_dbhHeader;
    micUpsCacheTriggerData_t rduct_micUpsCacheTrigger;
} req_data_ups_cache_trigger_t;

/*post Software Event*/
typedef struct
{
    u8        rpse_u8EnclosureId;
    u8        rpse_u8ControllerId;
    u16       rpse_u16SourceId;
    u8        rpse_Reserved[4];
    EventId_t rpse_EventId;
    u8        rpse_EventInfo[32];
} req_param_software_event_t;

typedef struct
{
    DataBufferHeader_t rdndni_dbhHeader;
    micNASGetDevNodeHeader_t rdndni_micNASDevNodeHeader;
} req_data_nas_device_node_info_t;

/* --- functional routines ------------------------------------------------- */

boolean_t isDeviceIdEqual(const device_id_t di1, const device_id_t di2);
boolean_t isHBADeviceId(const device_id_t di);
void copyDeviceId(device_id_t * pdiDest, const device_id_t diSource);

boolean_t isDeviceObjectIdEqual(const device_object_identifier_t * pDoi1, 
    const device_object_identifier_t * pDoi2);
void copyDeviceObjectIdentifier(device_object_identifier_t * pDoiDest,
    const device_object_identifier_t * pDoiSource);

boolean_t isDiscoverPathEqual(const discover_path_t * pPath1,
    const discover_path_t * pPath2);
boolean_t isISCSIDiscoverPathEqual(const discover_path_iscsi_t * pPath1,
    const discover_path_iscsi_t * pPath2);
boolean_t isSCSIDiscoverPathEqual(const discover_path_scsi_t * pPath1,
    const discover_path_scsi_t * pPath2);
    
#endif /* I2_TYPES_H */

/******************************************************************************
 * Change Log
 *
 * $Log: i2types.h,v $
 * Revision 1.82.2.7  2010/01/21 10:03:09  xinw
 * add coolermode support
 *
 * Revision 1.82.2.6  2009/11/10 03:12:50  xinw
 * add PowerManagementIgnored for array add
 *
 * Revision 1.82.2.5  2009/10/15 03:01:37  xinw
 * add nas support
 *
 * Revision 1.82.2.4  2009/09/28 06:07:48  xinw
 * [Merge code]Add the feature of "Force LD Synchronized".
 *
 * Revision 1.82.2.3  2009/05/22 06:12:37  xinw
 * add poweroff for shutdown cmd
 *
 * Revision 1.82.2.2  2009/03/23 11:50:07  xinw
 * add ups support
 *
 * Revision 1.82.2.1  2008/12/02 06:54:33  xinw
 * add power schedule support
 *
 * Revision 1.82  2008/08/25 09:08:07  michaell
 * Sync with no fix support
 *
 * Revision 1.81  2008/07/01 07:40:24  xinw
 * modify i2 log file path
 *
 * Revision 1.80  2008/06/25 02:41:54  xinw
 * SW Serviceability Improvement
 *
 * Revision 1.79  2008/06/05 06:47:44  theoz
 * 1. remove CMD_RW_RESET
 * 2. add ptc_u32OpCode into structure pass_through_cmd_t
 *
 * Revision 1.78  2008/05/28 07:01:40  theoz
 * Add Pd Reset Pass Thru Command
 *
 * Revision 1.77  2008/04/03 11:01:15  danielz
 * support LCD management
 *
 * Revision 1.76  2008/02/18 09:56:13  danielz
 * remove req_param_dump_ctrl_debug_info_t and req_data_dump_ctrl_debug_info_t
 * from i2types.h to i2typesob.h as those structure are used for embedded only
 *
 * Revision 1.75  2007/12/06 12:08:17  danielz
 *  support for the extented physical drive statistic information
 *
 * Revision 1.74  2007/11/16 03:06:31  xinw
 * add new struct for delete session
 *
 * Revision 1.73  2007/11/02 07:03:36  theoz
 * Add MIC Pass Thru APIs
 *
 * Revision 1.72  2007/09/21 06:31:40  danielz
 * 2 new fields are added to raid_capabilities_t structure, maximum enclosure id
 * supported and maximum physical drive id
 *
 * Revision 1.71  2007/08/28 10:22:07  danielz
 * support for the dump controller debug information.
 * add a new i2 api i2_dumpCtrlDebugInfo()
 *
 * Revision 1.70  2007/08/21 09:01:13  danielz
 * support for getting version and build information of all the flash images
 * of the controllers
 *
 * Revision 1.69  2007/07/10 19:21:56  JudithLi
 * 14680/ST EX8650M-Host driver can't be updated on WPP 3.03.0000.50
 *
 * Revision 1.68  2007/06/27 05:32:18  danielz
 * new feature bit for Raid6/60 RLM OCM
 *
 * Revision 1.67  2007/06/07 09:56:53  JudithLi
 * i2api v3&v4 consolidation
 *
 * Revision 1.66  2007/04/20 10:26:27  xinw
 * add iscsi fw update support
 *
 * Revision 1.65  2007/03/23 11:02:16  xinw
 * add portalid in req_param_iscsi_info_t
 *
 * Revision 1.64  2007/03/06 09:47:05  xinw
 * add new member in iscsi_capabilities_t for identify Mx10i feature
 *
 * Revision 1.63  2007/02/06 10:57:17  danielz
 * New i2 API i2_getHostInfo() to get host information
 *
 * Revision 1.62  2007/02/01 09:13:07  xinw
 * add product id to feature_bits_t
 *
 * Revision 1.61  2007/02/01 03:59:50  xinw
 * add new Mx10i support
 *
 * Revision 1.60  2007/01/12 01:13:53  debinc
 * sas zoning support
 *
 * Revision 1.59  2007/01/02 23:13:48  debinc
 * slot wwn mapping support
 *
 * Revision 1.58  2006/11/28 08:31:32  danielz
 * include imgheader.h for inband FW update.
 * req_data_flash_image_header_t is used by in-band CLI now
 *
 * Revision 1.57  2006/09/15 02:51:50  xinw
 * add fw update feature
 *
 * Revision 1.56  2006/09/14 03:59:46  danielz
 * New feature in feature bits for active-standby, PI_HAFM_ACTIVE_STANDBY_SUPPORTED
 *
 * Revision 1.55  2006/09/08 00:42:19  xinw
 * modify flash progress struct for dual ctrl
 *
 * Revision 1.54  2006/09/06 23:52:15  debinc
 * move currentctrlinfo out of raid capability
 *
 * Revision 1.53  2006/09/06 09:14:42  danielz
 * Support for clearing port statistics, getting phy level statistics of SAS host
 * Support for getting errorlog of c2c port, phy control to c2c port
 *
 * Revision 1.52  2006/09/06 01:40:50  xinw
 * modify file buf length for cim
 *
 * Revision 1.51  2006/08/24 02:32:44  xinc
 * Support "Configuration Export" in CLI
 *
 * Revision 1.50  2006/08/22 22:07:08  xinw
 * add i2 call for file sync
 *
 * Revision 1.49  2006/08/15 18:11:28  debinc
 * SAS port support part I
 *
 * Revision 1.48  2006/08/02 23:55:11  debinc
 * get sas initiator list
 *
 * Revision 1.47  2006/06/13 01:25:58  debinc
 * sas frontend api
 *
 * Revision 1.46  2006/06/01 00:24:34  debinc
 * fw capability add current ctrl is master or not
 *
 * Revision 1.45  2006/05/31 19:21:05  debinc
 * factory defaults encl
 *
 * Revision 1.44  2006/05/11 23:49:48  debinc
 * sas diag
 *
 * Revision 1.43  2006/04/14 18:39:09  debinc
 * maintenance mode mgmt port info
 *
 * Revision 1.42  2006/04/13 22:09:42  debinc
 * dual ctrl support 2
 *
 * Revision 1.41  2006/04/01 03:36:48  debinc
 * support dual controller shutdown
 *
 * Revision 1.40  2006/04/01 01:05:11  debinc
 * dual controller fc
 *
 * Revision 1.39  2006/03/24 19:59:51  debinc
 * support dual controller subsys info/setting
 *
 * Revision 1.38  2006/03/14 23:48:46  debinc
 * lun affinity support
 *
 * Revision 1.37  2006/02/22 01:28:31  debinc
 * get/set enclosure setting
 *
 * Revision 1.36  2006/02/13 20:43:54  weny
 * add more feature bits and fw capabilites
 *
 * Revision 1.35  2005/12/14 00:36:28  debinc
 * SAS topology support
 *
 * Revision 1.34  2005/11/23 01:46:37  debinc
 * SAS drive CLI
 *
 * Revision 1.33  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.32  2005/06/30 08:10:09  sergiyv
 * MX00P merge
 *
 * Revision 1.31  2005/05/20 23:09:31  debinc
 * FC MIC change
 *
 * Revision 1.30  2005/03/10 23:18:56  debinc
 * frontend type for differen product
 *
 * Revision 1.29  2005/02/19 02:06:53  debinc
 * M500f support
 *
 * Revision 1.28  2004/12/23 03:41:54  weny
 * support bbm
 *
 * Revision 1.27  2004/10/28 04:59:57  weny
 * add more comments to migration data structures
 *
 * Revision 1.26  2004/10/27 18:57:40  debinc
 * shutdown command support
 *
 * Revision 1.25  2004/10/19 04:34:17  weny
 * Online Array Removal support
 *
 * Revision 1.24  2004/10/11 19:45:20  weny
 * use u32 for stripe size in migration
 *
 * Revision 1.23  2004/10/05 19:39:50  debinc
 * remove subsys and enclosure stats
 *
 * Revision 1.22  2004/09/23 04:04:09  weny
 * R5 algorithm support
 *
 * Revision 1.21  2004/09/10 00:41:50  weny
 * spare check to use spare array id
 *
 * Revision 1.20  2004/08/31 06:49:51  weny
 * support accept missing nvram watermark
 *
 * Revision 1.19  2004/08/26 04:03:17  weny
 * add spare id and mp enable in spare param
 *
 * Revision 1.18  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.17  2004/07/13 04:00:03  ken.cai
 * added variable LD sector size setting
 *
 * Revision 1.16  2004/07/09 18:09:16  debinc
 * rearrange session_info_t
 *
 * Revision 1.15  2004/07/08 23:08:47  weny
 * merge with Napa I2 API
 *
 * Revision 1.14  2004/07/08 22:14:06  debinc
 * add inactivity in data structure
 *
 * Revision 1.13  2004/07/06 23:35:27  debinc
 * define req_data_session_info
 *
 * Revision 1.12  2004/07/06 23:16:44  weny
 * use pibasic.h
 *
 * Revision 1.11  2004/06/29 23:14:39  debinc
 * rename httpport from u32 to u16
 *
 * Revision 1.10  2004/06/29 02:02:39  weny
 * change SectorSize to SectorSizeCode
 *
 * Revision 1.9  2004/06/28 20:31:49  weny
 * Added LD Variable Sector Size Support
 *
 * Revision 1.8  2004/06/10 18:03:18  debinc
 * Add some reserved byte to make 8-byte aligned
 *
 * Revision 1.7  2004/06/08 21:25:16  weny
 * change to micMigrationProgress_t
 *
 * Revision 1.6  2004/05/13 18:09:08  zhengj
 * added support for spare check and locate enclosure
 *
 * Revision 1.5  2004/04/21 00:49:54  debinc
 * adjust getAllUsers
 *
 * Revision 1.4  2004/04/20 23:52:28  zhengj
 * added more filed in migration data structure
 *
 * Revision 1.3  2004/04/01 00:58:49  debinc
 * change webserver port to u16
 *
 * Revision 1.2  2004/03/26 00:29:07  zhengj
 * added PDM enable
 *
 * Revision 1.1  2004/03/24 03:24:12  weny
 * I2 API porting
 *
 *
 *****************************************************************************/
