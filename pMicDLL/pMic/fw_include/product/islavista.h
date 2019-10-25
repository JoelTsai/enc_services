#ifndef __ISLAVISTA_H
#define __ISLAVISTA_H


/* Backend Definitions go here */
#define MAX_CONTROLLERS                    64      /* assuming each can support 8 targets*/
#define TOTAL_MAX_TARGETS                  256
#define RESERVED_BICS                      256 
#define MAXBICS                            4096   /* (maxcmds/tgt( drive can accept 32 cmds at a time))*maxtgts */
/* RCM Specific Defines */


#define MAX_DISK_LDS_IN_ARRAY              32   
#define MAX_STORAGE_LDS_IN_CTLR            256
#define MAX_DISK_EXTENTS_IN_ARRAY          512
#define MAX_COMPONENT_DEVICES              TOTAL_MAX_TARGETS
#define MAX_DISK_EXTENTS_IN_LD             16
#define MAX_PHYSICAL_DISKS_IN_ARRAY        TOTAL_MAX_TARGETS
#define MAX_PHYSICAL_DISKS_IN_CTLR         TOTAL_MAX_TARGETS  
#define MAX_DISK_ARRAYS_IN_CTLR            256
#define MAX_SPARE_ARRAYS_IN_CTLR           256
#define MAX_ALLOWED_SECTOR_SIZES           6

/* For RAID 50, there'll be 16 AXLES and for RAID 51, there'll be 2 AXLES */
#define MAX_AXLES                               16
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID5      16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID5      3
#define MAX_AXLES_FOR_RAID51                    2

#ifdef SHASTA_RAID60
#define MAX_SPINDLES_IN_AXLE_FOR_HYB_RAID6  16
#define MIN_SPINDLES_IN_AXLE_FOR_HYB_RAID6  4
#endif

#define MAX_SPARE_ARRAYS_PER_DATA_ARRAY    8
#define MAX_REBUILDING_PDS_PER_ARRAY       DDF_PHYSICAL_DRIVES/2 //raid 10 configuration

/* ddf Definitions go here */
#define MAX_PHYSICAL_DRIVES                256
#define MAX_VIRTUAL_DRIVES                 256 /* this may be a function of arrays and LUNS */
#define MAX_GLOBALSPARES                   256

#define DDF_PHYSICAL_DRIVES                   MAX_PHYSICAL_DRIVES
#define DDF_VIRTUAL_DRIVES                 MAX_VIRTUAL_DRIVES
#define DDF_DISK_LDS_IN_ARRAY              MAX_DISK_LDS_IN_ARRAY  // support 4 LD only

#define DEFAULT_PROMISE_CO_NAME            "Promise Technology,Inc."
#define DEFAULT_PRODUCT_NAME               "VTrak"
#define VENDOR_INFO_MATRIX_FILE            "/oem/fw/VendorInfoMatrix.conf"

#if defined(ISCSI) || defined(FC)
#define MULTIPLE_INITAITOR_SUPPORT
#endif

#define MAX_RIOS_RES_FOR_MIC_OB   16

#define PROM_MAX_MEMORY_CONFIG    5
 
#define OS_MEMORY_RESOURCE_MATRIX_DEF  \
    { 64,  256},            /* Total System MEMORY_128 */ \
    {128, 1024},            /* Total System MEMORY_256 */ \
    {192, 1024},            /* Total System MEMORY_512 */ \
    {192, 1024},            /* Total System MEMORY_1GB */ \
    {192, 1024}             /* Total System MEMORY_2GB */ \

#define HIDDEN_MEMORY_RESOURCE_MATRIX_DEF  \
    {  64,  256},            /* Total System MEMORY_128 */ \
    { 128, 4096},            /* Total System MEMORY_256 */ \
    { 320, 8192},            /* Total System MEMORY_512 */ \
    { 832, 8192},            /* Total System MEMORY_1GB */ \
    {1856, 8192}             /* Total System MEMORY_2GB */ \


#define MAX_SSNAME_MATRIX      13

#define DEFAULT_VENDOR_MATRIX  \
    /*  CID, BPID, Product ID, FEIT      , BEIT     ,  R,R,R,R,R,R,R,R,R,R    Name[16]--------"  ,  VId[8]  , ProductId[16], NFT            ,  R,R,R,R,R,R , Dom-Date , Domain Name */  \
    {  0x01, 0x00, CTRL_M500I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M500i"       , "Promise", "VTrak M500i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"}, \
    {  0x01, 0x01, CTRL_M500I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M500i"       , "Promise", "VTrak M500i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"}, \
    {  0x01, 0x02, CTRL_M300I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M300i"       , "Promise", "VTrak M300i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"}, \
    {  0x01, 0x03, CTRL_M200I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M200i"       , "Promise", "VTrak M200i", NFT_IQN        , {0,0,0,0,0,0}, "1994-12", "com.promise"}, \
                                                                                                                                                                                        \
    {  0x04, 0x00, CTRL_M500F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M500f"       , "Promise", "VTrak M500f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
    {  0x04, 0x01, CTRL_M500F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M500f"       , "Promise", "VTrak M500f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
    {  0x04, 0x02, CTRL_M300F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M300f"       , "Promise", "VTrak M300f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
    {  0x04, 0x03, CTRL_M200F, FEIT_FC   , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M200f"       , "Promise", "VTrak M200f", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
                                                                                                                                                                                        \
    {  0x06, 0x00, CTRL_M500P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M500p"       , "Promise", "VTrak M500p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
    {  0x06, 0x01, CTRL_M500P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M500p"       , "Promise", "VTrak M500p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
    {  0x06, 0x02, CTRL_M300P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M300p"       , "Promise", "VTrak M300p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
    {  0x06, 0x03, CTRL_M200P, FEIT_SCSI , BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, "VTrak M200p"       , "Promise", "VTrak M200p", NFT_NOT_DEFINED, {0,0,0,0,0,0}, ""       , ""           }, \
                                                                                                                                                                                        \
    {  0xFF, 0xFF, CTRL_M500I, FEIT_ISCSI, BEIT_SATA, {0,0,0,0,0,0,0,0,0,0}, DEFAULT_PRODUCT_NAME, "Promise", DEFAULT_PRODUCT_NAME, NFT_IQN , {0,0,0,0,0,0}, "1994-12", "com.promise"}, \
                                                                                                                                                                                        
#define  DEFAULT_SUBSYSTEM_HBA_CAPABILITY_MATRIX  \
    /*  CID, BPID, MCS  , CSV */                  \
    {  0x01, 0x00, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x01, 0x01, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x01, 0x02, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x01, 0x03, 1    , CTRL_SUPPORTED_FIXED }, \
                                                  \
    {  0x04, 0x00, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x04, 0x01, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x04, 0x02, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x04, 0x03, 1    , CTRL_SUPPORTED_FIXED }, \
                                                  \
    {  0x06, 0x00, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x06, 0x01, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x06, 0x02, 1    , CTRL_SUPPORTED_FIXED }, \
    {  0x06, 0x03, 1    , CTRL_SUPPORTED_FIXED }, \
                                                  \
    {  0xFF, 0xFF, 1    , CTRL_SUPPORTED_FIXED }, \
                                                  
#endif /* __ISLAVISTA_H */






                                                                 
