#ifndef __YOSEMITE_H
#define __YOSEMITE_H

#define EX8650_VIRTUAL_BP_NAME      "EX8650 V-ENCL"
#define EX8654_VIRTUAL_BP_NAME      "EX8654 V-ENCL"
#define EX4650_VIRTUAL_BP_NAME      "EX4650 V-ENCL"
#define EX8650EL_VIRTUAL_BP_NAME    "EX8650EL V-ENCL"
#define EX4650EL_VIRTUAL_BP_NAME    "EX4650EL V-ENCL"
#define EX8650M_VIRTUAL_BP_NAME     "EX8650M V-ENCL"
#define YOSEMITE_VIRTUAL_BP_NAME    "SAS Virtual Enclosure"

/*For VPD subDeviceID use*/
#define VPD_SubDeviceID_EX4650A     0x4600
#define VPD_SubDeviceID_EX4650      0x4601
#define VPD_SubDeviceID_EX4650EL    0x4610
#define VPD_SubDeviceID_EX8650A     0x8601
#define VPD_SubDeviceID_EX8654      0x8602
#define VPD_SubDeviceID_EX8658      0x8603
#define VPD_SubDeviceID_EX8650      0x8604
#define VPD_SubDeviceID_EX8650EL    0x8600
#define VPD_SubDeviceID_EX8650M     0x8610
#define VPD_SubDeviceID_EX16650     0xB600
#define VPD_SubDeviceID_EX16654     0xB601
#define VPD_SubDeviceID_EX28654     0xC601

/*For VPD oem code*/
#define VPD_OEMNUMBER_NEC           0x0070
#define VPD_OEMNUMBER_GW            0x0010  /* Gateway */
#define VPD_OEMNUMBER_RACKABLE      0x0300
#define VPD_OEMNUMBER_QUANTA        0x1070
#define VPD_OEMNUMBER_ONS           0x0410

/*for BBU module threshold*/
#ifdef YOSEMITE_OEM_NEC
#define BBUPlusII_TempThresholdCharge       63
#else /* !YOSEMITE_OEM_NEC */
#define BBUPlusII_TempThresholdCharge       60
#endif /* YOSEMITE_OEM_NEC */
#define BBUPlusII_TempThresholdDischarge    60

#define SS1600_BP_NAME              "SuperSwap1600"
#define SS4600_BP_NAME              "SuperSwap4600"
#define NEC_SASBP_NAME              "NEC-AMI918"
#define ACER_SASBP_NAME             "ACER-SAS-BP"
#define GW_1U_SGPIO_BP_NAME         "GW-1U-SGPIO-BP"

/* Common Backend Definitions go here */
#define MAX_CONTROLLERS                     1  /* not in use  */
#define MAX_CHANNELS                        1  /* not in use */
#define MAX_TARGETS                         256 // SSP devices

#define RESERVED_BICS                       256
#define MAXBICS                             4096  /* max cmd per host */

// YOSEMITE specific definitions
#define MAX_SSP_ID                          MAX_TARGETS

#define MAX_ENCLOSURES_SUPPORTED            65
#define MAX_ENCLOSURE_ID                    MAX_ENCLOSURES_SUPPORTED

#define MAX_PD_ID                           1024
#define TOTAL_MAX_TARGETS                   256 // physical drive supported

/* RCM Specific Defines */
#define MAX_COMPONENT_DEVICES               TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_ARRAY         TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_CTLR          TOTAL_MAX_TARGETS

#define MAX_DISK_LDS_IN_ARRAY               32
#define MAX_STORAGE_LDS_IN_CTLR             256 /* 128 */
#define MAX_DISK_EXTENTS_IN_ARRAY           256 /* 64 */

#define MAX_DISK_EXTENTS_IN_LD              16 /* not used in raid_core */
#define MAX_DISK_ARRAYS_IN_CTLR             256 /* 128 */
#define MAX_SPARE_ARRAYS_IN_CTLR            256 /* 128 */

#define MAX_ALLOWED_SECTOR_SIZES            6

/* For RAID 50, there'll be 16 AXLES and for RAID 51, there'll be 2 AXLES */
#define MAX_AXLES                           16
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID5  16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID5  3
#define MAX_AXLES_FOR_RAID51                2

#ifdef SHASTA_RAID60
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID6  16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID6  4
#endif

#define MAX_SPARE_ARRAYS_PER_DATA_ARRAY     8
/* raid 10 configuration */
#define MAX_REBUILDING_PDS_PER_ARRAY        DDF_PHYSICAL_DRIVES/2

/* DDF Definitiona go here */
/* this may be a function of arrays and LUNS */
#define MAX_VIRTUAL_DRIVES                  256
#define MAX_GLOBALSPARES                    256

#define DDF_PHYSICAL_DRIVES                 256
#define DDF_VIRTUAL_DRIVES                  256
// support 4 LD only
#define DDF_DISK_LDS_IN_ARRAY               MAX_DISK_LDS_IN_ARRAY

#define DEFAULT_PROMISE_CO_NAME             "Promise Technology,Inc."
#define DEFAULT_PRODUCT_NAME                "ST EX8650"

#define VENDOR_INFO_MATRIX_FILE     "/oem/fw/VendorInfoMatrix.conf"

#define PROM_SUPPORT_RAID_LEVEL     (PI_FB_RAID_0 | PI_FB_RAID_1 | PI_FB_RAID_1E | \
                                     PI_FB_RAID_5 | PI_FB_RAID_6 | PI_FB_RAID_10 | \
                                     PI_FB_RAID_50 | PI_FB_RAID_60)

#define MAX_RIOS_RES_FOR_MIC_OB     16 // 4

#define PROM_MAX_MEMORY_CONFIG      5

#define OS_MEMORY_RESOURCE_MATRIX_DEF  \
    { 64, 1024},            /* Total System MEMORY_128MB */ \
    { 64, 1024},            /* Total System MEMORY_128MB */ \
    { 64, 1024},            /* Total System MEMORY_256MB */ \
    { 64, 1024},            /* Total System MEMORY_512MB */ \
    {128, 1024}             /* Total System MEMORY_256MB */

#define HIDDEN_MEMORY_RESOURCE_MATRIX_DEF  \
    {  64, 4096},            /* Total System MEMORY_128MB */ \
    { 128, 4096},            /* Total System MEMORY_256MB */ \
    { 192, 8192},            /* Total System MEMORY_256MB */ \
    { 448, 8192},            /* Total System MEMORY_512MB */ \
    { 960, 8192}             /* Total System MEMORY_1GB   */

#define MAX_SSNAME_MATRIX      14

#if 0
#define DEFAULT_VENDOR_MATRIX  \
   /*  CID  BPID  Product ID,    FEIT       BEIT       R,R,R,R,R,R,R,R,R,R   Name[16]       VId[8]     ProductId[16], NFT               R,R,R,R,R,R   Dom-Date  Domain Name */  \
   {  0x20, 0xB0, CTRL_EX865x,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX865x",   "Promise", "ST EX865x",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x21, 0xB1, CTRL_EX4650,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX4650",   "Promise", "ST EX4650",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x22, 0xB2, CTRL_EX8650,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650",   "Promise", "ST EX8650",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x23, 0xB3, CTRL_EX8654,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8654",   "Promise", "ST EX8654",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x24, 0xB4, CTRL_EX8650EL, FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650EL", "Promise", "ST EX8650EL", NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x25, 0xB5, CTRL_EX4650EL, FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX4650EL", "Promise", "ST EX4650EL", NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x26, 0xB6, CTRL_EX8650M,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650M",  "Promise", "ST EX8650M",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0xFF, 0xFF, CTRL_EX8650,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, DEFAULT_PRODUCT_NAME, "Promise", DEFAULT_PRODUCT_NAME, NFT_NOT_DEFINED , {0,0,0,0,0,0}, "", ""}

#define  DEFAULT_SUBSYSTEM_HBA_CAPABILITY_MATRIX  \
    /*  CID, BPID, MCS  , CSV */                  \
    {  0x20, 0xB0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x21, 0xB1, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x22, 0xB2, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x23, 0xB3, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x24, 0xB4, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x25, 0xB5, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x26, 0xB6, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0xFF, 0xFF, 1    , CTRL_SUPPORTED_FIXED }
#else
#define DEFAULT_VENDOR_MATRIX  \
   /*  CID  BPID  Product ID,    FEIT       BEIT       R,R,R,R,R,R,R,R,R,R   Name[16]       VId[8]     ProductId[16], NFT               R,R,R,R,R,R   Dom-Date  Domain Name */  \
   {  0x20, 0xC0, CTRL_EX865x,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX865x",   "Promise", "ST EX865x",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x21, 0xC0, CTRL_EX4650,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX4650",   "Promise", "ST EX4650",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x22, 0xC0, CTRL_EX8650,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650",   "Promise", "ST EX8650",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x23, 0xC0, CTRL_EX8654,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8654",   "Promise", "ST EX8654",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x24, 0xC0, CTRL_EX8650EL, FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650EL", "Promise", "ST EX8650EL", NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x25, 0xC0, CTRL_EX4650EL, FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX4650EL", "Promise", "ST EX4650EL", NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x26, 0xC0, CTRL_EX8650M,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650M",  "Promise", "ST EX8650M",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x27, 0xC0, CTRL_EX8658,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8658",   "Promise", "ST EX8658",   NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x28, 0xC0, CTRL_EX8650A,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX8650A",  "Promise", "ST EX8650A",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x29, 0xC0, CTRL_EX4650A,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX4650A",  "Promise", "ST EX4650A",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x2A, 0xC0, CTRL_EX16650,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX16650",  "Promise", "ST EX16650",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x2B, 0xC0, CTRL_EX16654,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX16654",  "Promise", "ST EX16654",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0x2C, 0xC0, CTRL_EX28654,  FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, "ST EX28654",  "Promise", "ST EX28654",  NFT_NOT_DEFINED, {0,0,0,0,0,0}, "", ""}, \
   {  0xFF, 0xFF, CTRL_EX8650,   FEIT_PCIE, BEIT_SAS, {0,0,0,0,0,0,0,0,0,0}, DEFAULT_PRODUCT_NAME, "Promise", DEFAULT_PRODUCT_NAME, NFT_NOT_DEFINED , {0,0,0,0,0,0}, "", ""}

#define DEFAULT_SUBSYSTEM_HBA_CAPABILITY_MATRIX   \
    /*  CID, BPID, MCS  , CSV */                  \
    {  0x20, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x21, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x22, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x23, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x24, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x25, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x26, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x27, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x28, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x29, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x2A, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x2B, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x2C, 0xC0, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0xFF, 0xFF, 1    , CTRL_SUPPORTED_FIXED }
#endif // 0

#endif /* __YOSEMITE_H */
