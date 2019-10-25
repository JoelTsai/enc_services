/*--------------------------------------------------------------------------**
**
**             Filename    : fc_mic_exp.h
**             Description : Defines to Handle FiberChannel Management Commands
**             Created on  : 06/02/2004
**             Created by  : Alex C.
**             (C) Copyright Promise Technology Inc., 2004
**             All Rights Reserved.
**
**--------------------------------------------------------------------------*/
#ifndef _FC_MIC_EXP_H
#define _FC_MIC_EXP_H

#ifdef ISLAVISTA_VERSION_DEBUG
static char *CVSId = "$Id: fc_mic_exp.h 117 2010-05-06 10:01:05Z spoca.huang $";
#endif


//=======================================================================
// for MIC related definitions
#define MIC_FC_ACCESS_ALL_PORTS	0xFF

#define FC_MAX_WWN_BYTECNT		8  /* Bytes in a target WWN name */
#define FC_MAX_NAME_BYTECNT		(64-16)  /* Bytes in a target name */

#define FC_MAX_NODES				1
#define FC_MAX_PORTS				2
#define FC_MAX_NUM_ALIAS			15
#define FC_MAX_NUM_INITIATORS		0x200	// it's 0x100 for 929 and 0x200 for 929X & 949X
#define FC_MAX_LOGGEDIN_DEVICES	FC_MAX_NUM_INITIATORS
#define FC_MAX_FRAME_SIZE			0x800
#define FC_MAX_KNOWN_INITIATOR	0x200
#define FC_MAX_FRIENDLY_NAME_LENGTH	48

#define MIC_FC_PAGE_GENERAL		0
#define MIC_FC_PAGE_PORTINFO		1
#define MIC_FC_PAGE_PORTSTAT		2
#define MIC_FC_PAGE_SFP			3

#ifdef DUAL_CTL
#define CONTROLLER_STATE_AP			0x00000001
#define CONTROLLER_STATE_ACTIVE		0x00000002
#define CONTROLLER_STATE_PASSIVE		0x00000004
#define CONTROLLER_STATE_AA			0x00000010
#define CONTROLLER_STATE_AA_FO		0x00000020
#define CONTROLLER_STATE_AA_FB		0x00000040
#define CONTROLLER_STATE_MASTER		0x00000100
#define CONTROLLER_STATE_SLAVE		0x00000200
#define CONTROLLER_STATE_SINGLE		0x00000400
#define CONTROLLER_STATE_INIT			0x80000000
#endif

//=======================================================================
// SMIS definitions - definition according to v2.8
typedef struct FC_SMIS_FCPort		//Capabilities and management of a Fibre Channel Port Device
{
	u16			PortType;
#define FC_SMIS_FCPORT_PORTTYPE_UNKNOWN				(0)
#define FC_SMIS_FCPORT_PORTTYPE_OTHER				(1)
#define FC_SMIS_FCPORT_PORTTYPE_NPORT				(10)		// Point-to-Point
#define FC_SMIS_FCPORT_PORTTYPE_NLPORT				(11)		// Arbitrated Loop
#define FC_SMIS_FCPORT_PORTTYPE_FNLPORT				(12)
#define FC_SMIS_FCPORT_PORTTYPE_NXPORT				(13)
#define FC_SMIS_FCPORT_PORTTYPE_EPORT				(14)
#define FC_SMIS_FCPORT_PORTTYPE_FPORT				(15)
#define FC_SMIS_FCPORT_PORTTYPE_FLPORT				(16)
#define FC_SMIS_FCPORT_PORTTYPE_BPORT				(17)
#define FC_SMIS_FCPORT_PORTTYPE_GPORT				(18)
#define FC_SMIS_FCPORT_PORTTYPE_VENDOR				(16000)
#define FC_SMIS_FCPORT_PORTTYPE_RESERVED				(65535)
	
   	u16			SupportedCOS[8];	// 65535 (-1) as non-value entry
	u16			ActiveCOS[8];
#define FC_SMIS_FCPORT_COS_UNKNOWN					(0)
#define FC_SMIS_FCPORT_COS_1							(1)
#define FC_SMIS_FCPORT_COS_2							(2)
#define FC_SMIS_FCPORT_COS_3							(3)
#define FC_SMIS_FCPORT_COS_4							(4)
#define FC_SMIS_FCPORT_COS_5							(5)
#define FC_SMIS_FCPORT_COS_6							(6)
#define FC_SMIS_FCPORT_COS_F							(7)

	u16			SupportedFC4Types[8];
	u16			ActiveFC4Type[8];
#define FC_SMIS_FCPORT_FC4TYPE_UNKNOWN				(0)
#define FC_SMIS_FCPORT_FC4TYPE_OTHER					(1)
#define FC_SMIS_FCPORT_FC4TYPE_LLC					(4)
#define FC_SMIS_FCPORT_FC4TYPE_IP						(5)
#define FC_SMIS_FCPORT_FC4TYPE_FCP					(8)
#define FC_SMIS_FCPORT_FC4TYPE_GPP					(9)
#define FC_SMIS_FCPORT_FC4TYPE_IPI3_MASTER			(17)
#define FC_SMIS_FCPORT_FC4TYPE_IPI3_SLAVE			(18)
#define FC_SMIS_FCPORT_FC4TYPE_IPI3_PEER				(19)
#define FC_SMIS_FCPORT_FC4TYPE_CPIPI3_MASTER		(21)
#define FC_SMIS_FCPORT_FC4TYPE_CPIPI3_SLAVE			(22)
#define FC_SMIS_FCPORT_FC4TYPE_CPIPI3_PEER			(23)
#define FC_SMIS_FCPORT_FC4TYPE_SBCCS_CH				(25)
#define FC_SMIS_FCPORT_FC4TYPE_SBCCS_CTL				(26)
#define FC_SMIS_FCPORT_FC4TYPE_SB2_CH				(27)
#define FC_SMIS_FCPORT_FC4TYPE_SB2_CTL				(28)
#define FC_SMIS_FCPORT_FC4TYPE_GS						(32)
#define FC_SMIS_FCPORT_FC4TYPE_SW					(34)
#define FC_SMIS_FCPORT_FC4TYPE_SNMP					(36)
#define FC_SMIS_FCPORT_FC4TYPE_HIPPI_FP				(64)
#define FC_SMIS_FCPORT_FC4TYPE_BBL_CTL				(80)
#define FC_SMIS_FCPORT_FC4TYPE_BBL_FDDI				(81)
#define FC_SMIS_FCPORT_FC4TYPE_BBL_8023				(82)
#define FC_SMIS_FCPORT_FC4TYPE_VI						(88)
#define FC_SMIS_FCPORT_FC4TYPE_AV						(96)
#define FC_SMIS_FCPORT_FC4TYPE_VENDOR				(255)

		u16		Reserved1;
		u32		Reserved2;
}__attribute__ ((packed))  FC_SMIS_FCPort_t;

typedef struct FC_SMIS_FCPort_Statistics
{
	u64               	LIPCount;
	u64              	NOSCount;
	u64              	ErrorFrames;
	u64             	DumpedFrames;
	u64              	LinkFailures;
	u64              	LossOfSignalCounter;
	u64             	LossOfSyncCounter;
	u64             	PrimitiveSeqProtocolErrCount;
	u64             	CRCErrors;
	u64              	InvalidTxWords;
	u64              	FramesTooShort;
	u64              	FramesTooLong;
   	u64 			BufferCreditNotProvided;
   	u64 			BufferCreditNotReceived;
   	u64 			DelimiterErrors;
   	u64 			EncodingDisparityErrors;
   	u64 			LinkResetsReceived;
   	u64 			LinkResetsTransmitted;
   	u64 			MulticastFramesReceived;
   	u64 			MulticastFramesTransmitted;
   	u64 			FBSYFrames;
   	u64 			PBSYFrames;
   	u64 			FRJTFrames;
   	u64 			PRJTFrames;
   	u64 			RXClass1Frames;
   	u64 			TXClass1Frames;
   	u64 			Class1FBSY;				// N/A
   	u64 			Class1PBSY;				// N/A
   	u64 			Class1FRJT;				// N/A
   	u64 			Class1PRJT;				// N/A
   	u64 			RXClass2Frames;		// N/A
   	u64 			TXClass2Frames;		// N/A
   	u64 			Class2FBSY;				// N/A
   	u64			Class2PBSY;				// N/A
   	u64 			Class2FRJT;				// N/A
   	u64 			Class2PRJT;				// N/A
   	u64 			RXClass3Frames;
   	u64 			TXClass3Frames;
   	u64 			Class3FramesDiscarded;
   	u64 			RXBroadcastFrames;
   	u64 			TXBroadcastFrames; 
   }__attribute__ ((packed))  FC_SMIS_FCPort_Statistics_t;

typedef struct FC_SMIS_FCPort_Rate_Statistics
{
   	u64		 	TxFrameRate;
   	u64 			RxFrameRate;
   	u64 			MaxTxFrameRate;
   	u64 			MaxRxFrameRate;
   	u64 			TxRate;
   	u64 			RxRate;
   	u64 			PeakTxRate;
   	u64 			PeakRxRate;
   }__attribute__ ((packed))  FC_SMIS_FCPort_Rate_Statistics_t;


//=======================================================================
typedef struct FC_ConfigPage_Statistics
{
    u64                     TimeSinceReset;
    u64                     TxFrames;
    u64                     RxFrames;
    u64                     TxWords;
    u64                     RxWords;
    u64                     LipCount;
    u64                     NosCount;
    u64                     ErrorFrames;
    u64                     DumpedFrames;
    u64                     LinkFailureCount;
    u64                     LossOfSyncCount;
    u64                     LossOfSignalCount;
    u64                     PrimativeSeqErrCount;
    u64                     InvalidTxWordCount;
    u64                     InvalidCrcCount;
    u64                     FcpInitiatorIoCount;
    u64			  Reserved[8];
}__attribute__ ((packed))  FC_ConfigPage_Statistics_t,FC_VENDOR_Statistics_t;

//-----------------------------------------------------------------------
// structure matches micFCConfigPageSFP_t
typedef struct FC_ConfigPage_SFP
{
    u8                      Flags;
#define MPI_FCPORTPAGE_FLAGS_MODDEF_MASK              (0x00000007)
#define MPI_FCPORTPAGE_FLAGS_MODDEF2                  (0x00000001)
#define MPI_FCPORTPAGE_FLAGS_MODDEF1                  (0x00000002)
#define MPI_FCPORTPAGE_FLAGS_MODDEF0                  (0x00000004)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_NOGBIC            (0x00000007)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_CPR_IEEE_CX       (0x00000006)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_COPPER            (0x00000005)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_OPTICAL_LW        (0x00000004)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_SEEPROM           (0x00000003)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_SW_OPTICAL        (0x00000002)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_LX_IEEE_OPT_LW    (0x00000001)
#define MPI_FCPORTPAGE_FLAGS_MODDEF_SX_IEEE_OPT_SW    (0x00000000)
#define MPI_FCPORTPAGE_FLAGS_CC_BASE_OK               (0x00000010)
#define MPI_FCPORTPAGE_FLAGS_CC_EXT_OK                (0x00000020)

    u8                      Reserved1;
    u16                    Reserved2;
    u32                    HwConfig1;
    u32                    HwConfig2;

    u8                      Id;
#define MPI_FCPORTPAGE_BASE_ID_UNKNOWN        (0x00)
#define MPI_FCPORTPAGE_BASE_ID_GBIC           (0x01)
#define MPI_FCPORTPAGE_BASE_ID_FIXED          (0x02)
#define MPI_FCPORTPAGE_BASE_ID_SFP            (0x03)
#define MPI_FCPORTPAGE_BASE_ID_SFP_MIN        (0x04)
#define MPI_FCPORTPAGE_BASE_ID_SFP_MAX        (0x7F)
#define MPI_FCPORTPAGE_BASE_ID_VEND_SPEC_MASK (0x80)

    u8                      ExtId;
#define MPI_FCPORTPAGE_BASE_EXTID_UNKNOWN     (0x00)
#define MPI_FCPORTPAGE_BASE_EXTID_MODDEF1     (0x01)
#define MPI_FCPORTPAGE_BASE_EXTID_MODDEF2     (0x02)
#define MPI_FCPORTPAGE_BASE_EXTID_MODDEF3     (0x03)
#define MPI_FCPORTPAGE_BASE_EXTID_SEEPROM     (0x04)
#define MPI_FCPORTPAGE_BASE_EXTID_MODDEF5     (0x05)
#define MPI_FCPORTPAGE_BASE_EXTID_MODDEF6     (0x06)
#define MPI_FCPORTPAGE_BASE_EXTID_MODDEF7     (0x07)
#define MPI_FCPORTPAGE_BASE_EXTID_VNDSPC_MASK (0x80)

    u8                      Connector;
#define MPI_FCPORTPAGE_BASE_CONN_UNKNOWN      (0x00)
#define MPI_FCPORTPAGE_BASE_CONN_SC           (0x01)
#define MPI_FCPORTPAGE_BASE_CONN_COPPER1      (0x02)
#define MPI_FCPORTPAGE_BASE_CONN_COPPER2      (0x03)
#define MPI_FCPORTPAGE_BASE_CONN_BNC_TNC      (0x04)
#define MPI_FCPORTPAGE_BASE_CONN_COAXIAL      (0x05)
#define MPI_FCPORTPAGE_BASE_CONN_FIBERJACK    (0x06)
#define MPI_FCPORTPAGE_BASE_CONN_LC           (0x07)
#define MPI_FCPORTPAGE_BASE_CONN_MT_RJ        (0x08)
#define MPI_FCPORTPAGE_BASE_CONN_MU           (0x09)
#define MPI_FCPORTPAGE_BASE_CONN_SG           (0x0A)
#define MPI_FCPORTPAGE_BASE_CONN_OPT_PIGT     (0x0B)
#define MPI_FCPORTPAGE_BASE_CONN_RSV1_MIN     (0x0C)
#define MPI_FCPORTPAGE_BASE_CONN_RSV1_MAX     (0x1F)
#define MPI_FCPORTPAGE_BASE_CONN_HSSDC_II     (0x20)
#define MPI_FCPORTPAGE_BASE_CONN_CPR_PIGT     (0x21)
#define MPI_FCPORTPAGE_BASE_CONN_RSV2_MIN     (0x22)
#define MPI_FCPORTPAGE_BASE_CONN_RSV2_MAX     (0x7F)
#define MPI_FCPORTPAGE_BASE_CONN_VNDSPC_MASK  (0x80)

    u8                      Transceiver[8];
    u8                      Encoding;
#define MPI_FCPORTPAGE_BASE_ENCODE_UNSPEC     (0x00)
#define MPI_FCPORTPAGE_BASE_ENCODE_8B10B      (0x01)
#define MPI_FCPORTPAGE_BASE_ENCODE_4B5B       (0x02)
#define MPI_FCPORTPAGE_BASE_ENCODE_NRZ        (0x03)
#define MPI_FCPORTPAGE_BASE_ENCODE_MANCHESTER (0x04)

    u8                      BitRate_100mbs;
    u8                      Reserved3;
    u8                      Length9u_km;
    u8                      Length9u_100m;
    u8                      Length50u_10m;
    u8                      Length62p5u_10m;
    u8                      LengthCopper_m;
    u8                      Reseverved2;
    u8                      VendorName[16];
    u8                      Reserved4;
    u8                      VendorOUI[3];
    u8                      VendorPN[16];
    u8                      VendorRev[4];
    u16                     Reserved5;
    u8                      Reserved6;
    u8                      CC_BASE;
    u8                      Options[2];
#define MPI_FCPORTPAGE_EXT_OPTION1_RATESEL    (0x20)
#define MPI_FCPORTPAGE_EXT_OPTION1_TX_DISABLE (0x10)
#define MPI_FCPORTPAGE_EXT_OPTION1_TX_FAULT   (0x08)
#define MPI_FCPORTPAGE_EXT_OPTION1_LOS_INVERT (0x04)
#define MPI_FCPORTPAGE_EXT_OPTION1_LOS        (0x02)

    u8                      BitRateMax;
    u8                      BitRateMin;
    u8                      VendorSN[16];
    u8                      DateCode[8];
    u8                      Reserved7[3];
    u8                      CC_EXT;
}__attribute__ ((packed))  FC_ConfigPage_SFP_t,  FC_VENDOR_SFP_t;

//-----------------------------------------------------------------------
typedef struct micFCConfigPage_Parameters
{
    u8				PortID;
    u8				ControllerID;
    u16 				Reserved16;	 	//Padding
    u32 				Reserved32;	 	//Padding
    u32                     	Flags;
#define MPI_FCPORTPAGE_FLAGS_PORT_OFFLINE              (0x00400000)
#define MPI_FCPORTPAGE_FLAGS_MAINTAIN_LOGINS           (0x00000002)

    u8                      	LinkConfig;
#define MPI_FCPORTPAGE_LCONFIG_SPEED_1GIG              (0x00)
#define MPI_FCPORTPAGE_LCONFIG_SPEED_2GIG              (0x01)
#define MPI_FCPORTPAGE_LCONFIG_SPEED_4GIG              (0x02)
#define MPI_FCPORTPAGE_LCONFIG_SPEED_10GIG             (0x03)
#define MPI_FCPORTPAGE_LCONFIG_SPEED_AUTO              (0x0F)

    u8                      	TopologyConfig;
#define MPI_FCPORTPAGE_TOPOLOGY_NLPORT                 (0x01)
#define MPI_FCPORTPAGE_TOPOLOGY_NPORT                  (0x02)
#define MPI_FCPORTPAGE_TOPOLOGY_AUTO                   (0x0F)

    u8                      	HardALPA;
#define MPI_FCPORTPAGE_HARD_ALPA_NOT_USED              (0xFF)

    u8                      	Reserved2;
    // Current Alias ALPAs	- READ Only now
    // u8                      	NumAliases;					// No use for now
    // FC_Alias_Info_t         Alias[FC_MAX_NUM_ALIAS];	// No use for now
    u8     		 		Reserved[64];
}__attribute__ ((packed))  FC_ConfigPage_Parameters_t, FC_VENDOR_Parameters_t, micFCConfigPage_Parameters_t;

//-----------------------------------------------------------------------
typedef struct micFCConfigPage_Status
{
    u8			PortID;
    u8			ControllerID;
    u16 			Reserved16;	 	//Padding
    u32 			Reserved32;	 	//Padding
    u32                   HardwareVersion;
    u32                   FirmwareVersion;

    u32                     Flags;
#define MPI_FCPORTPAGE_FLAGS_PROT_FCP_INIT             (0x08)           // FC initiator
#define MPI_FCPORTPAGE_FLAGS_PROT_FCP_TARG             (0x04)           // FC target

#define MPI_FCPORTPAGE_FLAGS_ALIAS_ALPA_SUPPORTED      (0x00000010)
#define MPI_FCPORTPAGE_FLAGS_ALIAS_WWN_SUPPORTED       (0x00000020)

#define MPI_FCPORTPAGE_FLAGS_ATTACH_POINT_TO_POINT     (0x00000100)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_PRIVATE_LOOP       (0x00000200)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_FABRIC_DIRECT      (0x00000400)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_PUBLIC_LOOP        (0x00000800)

    u32                     MaxFrameSize;               // 0x800
    u32                     PortIdentifier;             // FC Port Identifier
    u32     		  MaxFailOverPorts;		// max number of possible alias
    u64                     WWNN;                               // own WWNN
    u64                     WWPN;                               // own WWPN
    u64                     FabricWWNN;                 // Fabric WWNN, NULL if not fabric
    u64                     FabricWWPN;                 // Fabric WWPN  , NULL if not fabric
    u32                     SupportedServiceClass;
#define MPI_FCPORTPAGE_SUPPORT_CLASS_1                 (0x00000001)
#define MPI_FCPORTPAGE_SUPPORT_CLASS_2                 (0x00000002)
#define MPI_FCPORTPAGE_SUPPORT_CLASS_3                 (0x00000004)

    u32                     SupportedSpeeds;
#define MPI_FCPORTPAGE_SUPPORT_1GBIT_SPEED             (0x00000001)
#define MPI_FCPORTPAGE_SUPPORT_2GBIT_SPEED             (0x00000002) 
#define MPI_FCPORTPAGE_SUPPORT_10GBIT_SPEED            (0x00000004) 
#define MPI_FCPORTPAGE_SUPPORT_4GBIT_SPEED             (0x00000008) 

    u32                     CurrentSpeed;
#define MPI_FCPORTPAGE_CURRENT_SPEED_1GBIT             MPI_FCPORTPAGE_SUPPORT_1GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_2GBIT             MPI_FCPORTPAGE_SUPPORT_2GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_10GBIT            MPI_FCPORTPAGE_SUPPORT_10GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_4GBIT             MPI_FCPORTPAGE_SUPPORT_4GBIT_SPEED

    u8                      LinkType;
#define MPI_FCPORTPAGE_LTYPE_RESERVED                  (0x00)
#define MPI_FCPORTPAGE_LTYPE_OTHER                     (0x01)
#define MPI_FCPORTPAGE_LTYPE_UNKNOWN                   (0x02)
#define MPI_FCPORTPAGE_LTYPE_COPPER                    (0x03)
#define MPI_FCPORTPAGE_LTYPE_SINGLE_1300               (0x04)
#define MPI_FCPORTPAGE_LTYPE_SINGLE_1500               (0x05)
#define MPI_FCPORTPAGE_LTYPE_50_LASER_MULTI            (0x06)
#define MPI_FCPORTPAGE_LTYPE_50_LED_MULTI              (0x07)
#define MPI_FCPORTPAGE_LTYPE_62_LASER_MULTI            (0x08)
#define MPI_FCPORTPAGE_LTYPE_62_LED_MULTI              (0x09)
#define MPI_FCPORTPAGE_LTYPE_MULTI_LONG_WAVE           (0x0A)
#define MPI_FCPORTPAGE_LTYPE_MULTI_SHORT_WAVE          (0x0B)
#define MPI_FCPORTPAGE_LTYPE_LASER_SHORT_WAVE          (0x0C)
#define MPI_FCPORTPAGE_LTYPE_LED_SHORT_WAVE            (0x0D)
#define MPI_FCPORTPAGE_LTYPE_1300_LONG_WAVE            (0x0E)
#define MPI_FCPORTPAGE_LTYPE_1500_LONG_WAVE            (0x0F)

    u8                      PortState;
#define MPI_FCPORTPAGE_PORTSTATE_UNKNOWN               (0x01)      /*(SNIA)HBA_PORTSTATE_UNKNOWN       1 Unknown */
#define MPI_FCPORTPAGE_PORTSTATE_ONLINE                (0x02)      /*(SNIA)HBA_PORTSTATE_ONLINE        2 Operational */
#define MPI_FCPORTPAGE_PORTSTATE_OFFLINE               (0x03)      /*(SNIA)HBA_PORTSTATE_OFFLINE       3 User Offline */
#define MPI_FCPORTPAGE_PORTSTATE_BYPASSED              (0x04)      /*(SNIA)HBA_PORTSTATE_BYPASSED      4 Bypassed */
#define MPI_FCPORTPAGE_PORTSTATE_DIAGNOST              (0x05)      /*(SNIA)HBA_PORTSTATE_DIAGNOSTICS   5 In diagnostics mode */
#define MPI_FCPORTPAGE_PORTSTATE_LINKDOWN              (0x06)      /*(SNIA)HBA_PORTSTATE_LINKDOWN      6 Link Down */
#define MPI_FCPORTPAGE_PORTSTATE_ERROR                 (0x07)      /*(SNIA)HBA_PORTSTATE_ERROR         7 Port Error */
#define MPI_FCPORTPAGE_PORTSTATE_LOOPBACK              (0x08)      /*(SNIA)HBA_PORTSTATE_LOOPBACK      8 Loopback */

    u8                      MaxAliasesSupported;
    u8                      NumCurrentAliases;

    u8                     NumberActiveALPA;              // active ALPA in a loop
    u8                     ActiveALPA[127];

    u8                     SymbolicName[256];
    u64                    AliasWWPN;                               // alias WWPN
    u8     		 	 Reserved[24];

    FC_ConfigPage_Statistics_t 	Statistics;
    FC_ConfigPage_SFP_t 		SFP_Status;
    FC_ConfigPage_Parameters_t 	PortSettings;
}__attribute__ ((packed))  micFCConfigPage_Info_0_t, micFCConfigPage_Status_t;


//-----------------------------------------------------------------------
typedef struct FC_VENDOR_FCPortInfo
{
    u32                   HardwareVersion;
    u32                   FirmwareVersion;

    u32                     Flags;
#define MPI_FCPORTPAGE_FLAGS_PROT_FCP_INIT             (0x08)           // FC initiator
#define MPI_FCPORTPAGE_FLAGS_PROT_FCP_TARG             (0x04)           // FC target
#define MPI_FCPORTPAGE_FLAGS_ALIAS_ALPA_SUPPORTED      (0x00000010)
#define MPI_FCPORTPAGE_FLAGS_ALIAS_WWN_SUPPORTED       (0x00000020)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_POINT_TO_POINT     (0x00000100)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_PRIVATE_LOOP       (0x00000200)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_FABRIC_DIRECT      (0x00000400)
#define MPI_FCPORTPAGE_FLAGS_ATTACH_PUBLIC_LOOP        (0x00000800)

    u32                     MaxFrameSize;               // 0x800
    u32                     PortIdentifier;             	// FC Port Identifier
    u32     		  MaxFailOverPorts;		// max number of possible alias
    u64                     WWNN;                               // own WWNN
    u64                     WWPN;                               // own WWPN
    u64                     FabricWWNN;                 // Fabric WWNN, NULL if not fabric
    u64                     FabricWWPN;                 // Fabric WWPN  , NULL if not fabric
    u32                     SupportedServiceClass;
#define MPI_FCPORTPAGE_SUPPORT_CLASS_1                 (0x00000001)
#define MPI_FCPORTPAGE_SUPPORT_CLASS_2                 (0x00000002)
#define MPI_FCPORTPAGE_SUPPORT_CLASS_3                 (0x00000004)

    u32                     SupportedSpeeds;
#define MPI_FCPORTPAGE_SUPPORT_1GBIT_SPEED             (0x00000001) /* (SNIA)HBA_PORTSPEED_1GBIT 1  1 GBit/sec  */
#define MPI_FCPORTPAGE_SUPPORT_2GBIT_SPEED             (0x00000002) /* (SNIA)HBA_PORTSPEED_2GBIT 2  2 GBit/sec  */
#define MPI_FCPORTPAGE_SUPPORT_10GBIT_SPEED            (0x00000004) /* (SNIA)HBA_PORTSPEED_10GBIT 4 10 GBit/sec */
#define MPI_FCPORTPAGE_SUPPORT_4GBIT_SPEED             (0x00000008) /* (SNIA)HBA_PORTSPEED_4GBIT   8   4 GBit/sec */

    u32                     CurrentSpeed;
#define MPI_FCPORTPAGE_CURRENT_SPEED_1GBIT             MPI_FCPORTPAGE_SUPPORT_1GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_2GBIT             MPI_FCPORTPAGE_SUPPORT_2GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_10GBIT           MPI_FCPORTPAGE_SUPPORT_10GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_4GBIT             MPI_FCPORTPAGE_SUPPORT_4GBIT_SPEED
#define MPI_FCPORTPAGE_CURRENT_SPEED_NOT_NEGOTIATED    (0x00008000)        /* (SNIA)HBA_PORTSPEED_NOT_NEGOTIATED (1<<15) Speed not established */

    u8                      LinkType;
#define MPI_FCPORTPAGE_LTYPE_RESERVED                  (0x00)
#define MPI_FCPORTPAGE_LTYPE_OTHER                     (0x01)
#define MPI_FCPORTPAGE_LTYPE_UNKNOWN                   (0x02)
#define MPI_FCPORTPAGE_LTYPE_COPPER                    (0x03)
#define MPI_FCPORTPAGE_LTYPE_SINGLE_1300               (0x04)
#define MPI_FCPORTPAGE_LTYPE_SINGLE_1500               (0x05)
#define MPI_FCPORTPAGE_LTYPE_50_LASER_MULTI            (0x06)
#define MPI_FCPORTPAGE_LTYPE_50_LED_MULTI              (0x07)
#define MPI_FCPORTPAGE_LTYPE_62_LASER_MULTI            (0x08)
#define MPI_FCPORTPAGE_LTYPE_62_LED_MULTI              (0x09)
#define MPI_FCPORTPAGE_LTYPE_MULTI_LONG_WAVE           (0x0A)
#define MPI_FCPORTPAGE_LTYPE_MULTI_SHORT_WAVE          (0x0B)
#define MPI_FCPORTPAGE_LTYPE_LASER_SHORT_WAVE          (0x0C)
#define MPI_FCPORTPAGE_LTYPE_LED_SHORT_WAVE            (0x0D)
#define MPI_FCPORTPAGE_LTYPE_1300_LONG_WAVE            (0x0E)
#define MPI_FCPORTPAGE_LTYPE_1500_LONG_WAVE            (0x0F)

    u8                      PortState;
#define MPI_FCPORTPAGE_PORTSTATE_UNKNOWN               (0x01)      /*(SNIA)HBA_PORTSTATE_UNKNOWN       1 Unknown */
#define MPI_FCPORTPAGE_PORTSTATE_ONLINE                (0x02)      /*(SNIA)HBA_PORTSTATE_ONLINE        2 Operational */
#define MPI_FCPORTPAGE_PORTSTATE_OFFLINE               (0x03)      /*(SNIA)HBA_PORTSTATE_OFFLINE       3 User Offline */
#define MPI_FCPORTPAGE_PORTSTATE_BYPASSED              (0x04)      /*(SNIA)HBA_PORTSTATE_BYPASSED      4 Bypassed */
#define MPI_FCPORTPAGE_PORTSTATE_DIAGNOST              (0x05)      /*(SNIA)HBA_PORTSTATE_DIAGNOSTICS   5 In diagnostics mode */
#define MPI_FCPORTPAGE_PORTSTATE_LINKDOWN              (0x06)      /*(SNIA)HBA_PORTSTATE_LINKDOWN      6 Link Down */
#define MPI_FCPORTPAGE_PORTSTATE_ERROR                 (0x07)      /*(SNIA)HBA_PORTSTATE_ERROR         7 Port Error */
#define MPI_FCPORTPAGE_PORTSTATE_LOOPBACK              (0x08)      /*(SNIA)HBA_PORTSTATE_LOOPBACK      8 Loopback */

    u8                      MaxAliasesSupported;
    u8                      NumCurrentAliases;

    u8                      SymbolicName[256];
    u64                    AliasWWPN;                               // alias WWPN
    u8     		 	 Reserved[56];
}__attribute__ ((packed))   FC_VENDOR_FCPortInfo_t;


typedef struct micFCConfigPage_Info_1
{
    u8		PortID;
    u8		ControllerID;
    u16 		Reserved16;	 	//Padding
    u32 		Reserved32;	 	//Padding
    FC_SMIS_FCPort_t 				SMIS_PortInfo;
    FC_VENDOR_FCPortInfo_t			VENDOR_PortInfo;
    FC_VENDOR_Parameters_t 		VENDOR_PortSettings;
}__attribute__ ((packed))  micFCConfigPage_Info_1_t;


typedef struct micFCConfigPage_Info_2
{
    u8		PortID;
    u8		ControllerID;
    u16 		Reserved16;	 	//Padding
    u32 		Reserved32;	 	//Padding
    FC_SMIS_FCPort_Statistics_t 		SMIS_Statistics;
    FC_SMIS_FCPort_Rate_Statistics_t	SMIS_Rate_Statistics;
    FC_VENDOR_Statistics_t 			VENDOR_Statistics;
}__attribute__ ((packed))  micFCConfigPage_Info_2_t;


typedef struct micFC_ConfigPage_Info_3
{
    u8		PortID;
    u8		ControllerID;
    u16 		Reserved16;	 	//Padding
    u32 		Reserved32;	 	//Padding
    FC_VENDOR_SFP_t 				VENDOR_SFP_Status;
}__attribute__ ((packed))  micFCConfigPage_Info_3_t;

typedef struct micFC_ConfigPage_Info_all
{
	union {
    		micFCConfigPage_Info_0_t 		Info_Page_0;
    		micFCConfigPage_Info_1_t 		Info_Page_1;
    		micFCConfigPage_Info_2_t 		Info_Page_2;
    		micFCConfigPage_Info_3_t 		Info_Page_3;
	} micFC_ConfigPage_Info_all_union;
}__attribute__ ((packed))  micFC_ConfigPage_Info_all_t;



//=======================================================================
typedef struct micFC_LoggedIn_Devices	// [ABC] V4 Also for micFC_Initiator_Device_t
{
    u64                	wwpn;
    u32                	portId;
    u32 			Reserved;	 	//Padding
    u8 			SymbolicName[FC_MAX_NAME_BYTECNT];
} __attribute__ ((packed)) micFC_LoggedIn_Devices_t, micFC_Known_Initiator_Device_t, nvFCFriendlyNameEntry_t;

typedef struct micFCConfigPage_LoggedIn_Device_List {
    u8		PortID;
    u8		ControllerID;
    u16 		Reserved16;	 	//Padding
    u32 		NumberLoggedInDevices;	 //Logged-in devices
    micFC_LoggedIn_Devices_t	LoggedInDevices[FC_MAX_LOGGEDIN_DEVICES];
}__attribute__ ((packed))  micFCConfigPage_LoggedIn_Device_List_t;


//=======================================================================
typedef struct micFCConfigPage_Known_Initiator_List {
    u32 		Reserved;	 		//Padding
    u32 		NumberInitiators;	//Initiators
    micFC_Known_Initiator_Device_t		Initiator[FC_MAX_KNOWN_INITIATOR]; // [ABC] V4
}__attribute__ ((packed))  micFCConfigPage_Known_Initiator_List_t;


//===================================================================
typedef struct FC_Alias_Info	// No use for now
{
    u8       Flags;
#define MPI_FCPORTPAGE_FLAGS_ALPA_ACQUIRED             (0x01)
#define MPI_FCPORTPAGE_FLAGS_HARD_ALPA                 (0x02)
#define MPI_FCPORTPAGE_FLAGS_HARD_WWNN                 (0x04)
#define MPI_FCPORTPAGE_FLAGS_HARD_WWPN                 (0x08)
#define MPI_FCPORTPAGE_FLAGS_DISABLE                   (0x10)

    u8       AliasAlpa;
    u16     Reserved;
    u32     ReservedPadding;
    u64     AliasWWNN;
    u64     AliasWWPN;
} __attribute__ ((packed))  FC_Alias_Info_t, micFCConfigPage_Parameters_Alias_t;


//===================================================================
typedef struct FC_INFO_DESC		//[ABC] same as FD_INFO_DESC to match internal data structure
{
    u16 Type;
    u16 PortID;
#ifdef DUAL_CTL
    u16 ControllerID;	// void if not E-Class to be backward compatible with M-Class
#endif
    u16 Index;
    u8 *rcvBuffer;
    u32 rcvBufferSize;
    u32 *sndBuffer;    
    u32 sndBufferSize; 
}FCID_t;

extern void fcMgmtInit (void);
extern u32 fcSendElsRSCN(void);
extern u8 fc4MicEntry (void *pRio_ext, void* pBuffer, void (*CallBackFn)(void *), void *CallBackData, u32 *CallBackSts);


//===================================================================
#ifdef 	_FC_MGMT_C	// Only in MIC layer
#define 	CRASH_EVENT              	0xFFFF0000
#define 	CRASH_FILE_PATH 		"/islavista/conf/fw/crashfile_port_"

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
    u8  igpc_ControllerID;	// [ABC] for DUAL_CTL
    Control_t igspc_Control;
} __attribute__ ((packed)) micFCGetParamsInfoCmd_t;


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
    u8  ispc_ControllerID;	// [ABC] for DUAL_CTL
    Control_t ispc_Control;
} __attribute__ ((packed)) micFCSetParamsCmd_t;


typedef struct fcScratchBufferStruct
{
	MAHandlerHeader_t   	isb_Header;
    	u16                 		isb_MicOpCode;
    	u16                 		isb_iscsiProcessState;
    	u32                 		isb_iscsiControl;
	RIO_t 				*CallBackRio;
	u32 					isb_status;
	u8 					*pDataBuffer;
}fcMgmtScratchBuf_t;

typedef struct fcResourceHandlerStruct
{
	GenericResHanger_t	irh_ResHanger;
}fcResourceHandler_t;
#endif

#endif /* _FC_MIC_EXP_H */


/*
 * $Log: fc_mic_exp.h,v $
 * Revision 1.1.2.9  2006/03/10 22:48:54  haipao.fan
 * single image
 *
 * Revision 1.1.2.5.2.8  2006/02/17 01:55:33  alexc
 * Add MaxFailOverPorts
 *
 * Revision 1.1.2.5.2.6  2006/01/26 23:51:51  alexc
 * Add FC MIC change for alias
 *
 * Revision 1.1.2.5.2.5  2005/12/14 03:58:39  alexc
 * Add C2C support for configuration sync
 *
 * Revision 1.1.2.5.2.4  2005/11/08 01:28:42  alexc
 * Use FE driver handle for interface access
 *
 * Revision 1.1.2.5.2.3  2005/09/23 23:42:50  alexc
 * Add controllerID field
 *
 * Revision 1.1.2.5.2.1  2005/09/19 22:22:53  alexc
 * Remove RIO kernel structure from FED
 *
 * Revision 1.1.2.6  2005/09/16 18:28:25  alexc
 * Move RIO out of FED
 *
 * Revision 1.1.2.5  2005/08/25 17:42:22  alexc
 * Add 4G support
 *
 * Revision 1.1.2.4  2005/08/16 23:40:43  alexc
 * E-class FC porting
 *
 * Revision 1.5  2005/05/20 22:35:42  alexc
 * Add new MIC command definitions for multiple pagecode
 *
 * Revision 1.4  2005/03/10 04:40:16  alexc
 * Add FC set parameter fix
 *
 * Revision 1.3  2005/02/24 04:39:48  alexc
 * no message
 *
 * Revision 1.2  2005/02/12 03:29:35  alexc
 * Add Fibre Channel modules
 *
 * Revision 1.1.2.3  2005/02/05 03:01:47  alexc
 * Adjust for 8 bytes padding
 *
 * Revision 1.1.2.2  2005/02/01 23:36:27  alexc
 * Add padding for SW
 *
 * Revision 1.1.2.1  2005/01/13 01:25:25  alexc
 * Add Fibre Channel support
 *
 * 
 * 8     10/21/04 4:57p Alexchen
 * Fix invalid initiator list bug #4709
 * 
 * 6     8/25/04 8:00p Alexchen
 * 
 * 3     8/18/04 3:26p Alexchen
 * Change LogginDevice structure
 * 
 * 1     6/15/04 2:53p Cynthiax
 * 
 *
 * Revision 1.10  2004/06/02 02:50:19  alexc
 * initial version
 *
 */
