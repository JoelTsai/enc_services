/***************************************************************
 *
 * Filename    : internalmic.h
 * Description : Stuctures and definitions used for Internal tools only  
 * Created on  : 03/01/2006                                              
 * CVS Version : Manoj Mathew                                            
 *                                                                       
 * (C) Copyright Promise Technology Inc., 2006
 * All Rights Reserved
 *
 ****************************************************************/
#ifndef _INTERNAL_MIC_H
#define _INTERNAL_MIC_H

#include "mic.h"


#define PMIC_INTERNAL_REBOOT                   (0x0010 | MIC_INTERNAL_MGT_ID)
#define PMIC_INTERNAL_CONTROLLER_GET_THIS_INFO (0x0011 | MIC_INTERNAL_MGT_ID)
#define PMIC_INTERNAL_CONTROLLER_DUMP_INFO1             (0x0012 | MIC_INTERNAL_MGT_ID)

#define PMIC_INTERNAL_SET_CLEAR_CTL_MODE_FOR_NEXT_BOOT  (0x0013 | MIC_INTERNAL_MGT_ID)

#define PMIC_INTERNAL_READ_FFLASH_NVRAM_DATA            (0x0014 | MIC_INTERNAL_MGT_ID)

#define PMIC_INTERNAL_WRITE_FFLASH_NVRAM_DATA           (0x0015 | MIC_INTERNAL_MGT_ID)
#define PMIC_INTERNAL_EVENT_WAIT                        (0x0016 | MIC_INTERNAL_MGT_ID)
#define PMIC_INTERNAL_CONTROLLER_GET_LED_INFO           (0x0017 | MIC_INTERNAL_MGT_ID)
#define PMIC_INTERNAL_CONTROLLER_GET_STATS              (0x0018 | MIC_INTERNAL_MGT_ID)
#define PMIC_INTERNAL_CONTROLLER_SET_BL_BOOT_DELAY      (0x0019 | MIC_INTERNAL_MGT_ID)

/* PMIC_INTERNAL_REBOOT */
typedef struct micInternalRebootCmd
{
   u8          ir_ScsiOpCode;              
   u8          ir_MicSignature;        
   u16         ir_MicOpCode;        
   u8          ir_ConfigLock;        
   u8          ir_LoginKey;        
   u8          ir_ControllerID;
   u8          ir_RebootTimeInSec; 
   u8          ir_BootUpDelayInSec; 
   u8          ir_RebootType;
   u16         ir_Reserved2;        
   u16         ir_Reserved3;        
   u8          ir_Reserved4;        
   Control_t   ir_Control; 
} __attribute__ ((packed)) micInternalRebootCmd_t;

/* Possible values for ir_RebootType */
#define RT_ABRUPT         1
#define RT_GRACEFULL      2

/* PMIC_INTERNAL_CONTROLLER_GET_THIS_INFO */
typedef struct micInternalCtrlGetThisInfoCmd
{
   u8          icgti_ScsiOpCode;              
   u8          icgti_MicSignature;        
   u16         icgti_MicOpCode;        
   u16         icgti_Reserved0;
   u16         icgti_Reserved1;
   u16         icgti_Reserved2;        
   u16         icgti_TransferLength;        
   u16         icgti_TransferOffset;        
   u8          icgti_Reserved5;        
   Control_t   icgti_Control; 
} __attribute__ ((packed)) micInternalCtrlGetThisInfoCmd_t;

typedef struct micThisCtrlInfo
{
   u8  tci_ControllerID;
   u8  tci_SlotNo; 
   u8  tci_Reserved[6];
} micThisCtrlInfo_t;

/* PMIC_INTERNAL_CONTROLLER_DUMP_INFO1 */

typedef struct micInternalCtrlDumpInfo1Cmd

{

   u8          icdi1_ScsiOpCode;              

   u8          icdi1_MicSignature;        

   u16         icdi1_MicOpCode;        

   u8          icdi1_UniqueCmdId;        

   u8          icdi1_LoginKey;        

   u16         icdi1_ControllerID;        

   u16         icdi1_Reserved0;

   u16         icdi1_TransferLength;        

   u16         icdi1_TransferOffset;        

   u8          icdi1_ControllerCount;        

   Control_t   icdi1_Control; 

} __attribute__ ((packed)) micInternalCtrlDumpInfo1Cmd_t;



typedef struct micCtrlDumpInfo1

{

   u32  cdi1_InfoType;

   u32  cdi1_Reserved;

   u8   cdi1_BannerString[120];

} micCtrlDumpInfo1_t;



/* Possible values for cdi1_InfoType - A BitMap */

#define INFO_TYPE_RIO             0x00000001

#define INFO_TYPE_MEM_ALLOC       0x00000002 

#define INFO_TYPE_IVDUMP          0xFFFFFFFF





/* PMIC_INTERNAL_SET_CLEAR_CTL_MODE_FOR_NEXT_BOOT */

typedef struct micInternalSetClearCtrlModeForNextBootCmd

{

   u8          isccmfnb_ScsiOpCode;              

   u8          isccmfnb_MicSignature;        

   u16         isccmfnb_MicOpCode;        

   u8          isccmfnb_UniqueCmdId;        

   u8          isccmfnb_LoginKey;        

   u16         isccmfnb_ControllerID;        

   u8          isccmfnb_CtrlModeType;

   u8          isccmfnb_Action;

   u16         isccmfnb_Reserved0;        

   u16         isccmfnb_Reserved1;        

   u8          isccmfnb_Reserved2;

   Control_t   isccmfnb_Control; 

} __attribute__ ((packed)) micInternalSetClearCtrlModeForNextBootCmd_t;



/* Possible values for isccmfnb_CtrlModeType */

#define CMFNB_CTRL_MODE_MAINTENANCE  CRT_MAINTENANCE



/* Possible values for isccmfnb_Action */

#define CMFNB_ACTION_CLEAR     0

#define CMFNB_ACTION_SET       1



/* PMIC_INTERNAL_READ_FFLASH_NVRAM_DATA          

   PMIC_INTERNAL_WRITE_FFLASH_NVRAM_DATA */        

typedef struct micInternalReadWriteFFlashNVRAMDataCmd

{

   u8          irwffnd_ScsiOpCode;              

   u8          irwffnd_MicSignature;        

   u16         irwffnd_MicOpCode;        

   u8          irwffnd_UniqueCmdId;        

   u8          irwffnd_LoginKey;        

   u16         irwffnd_ControllerID;        

   u16         irwffnd_Reserved0;

   u16         irwffnd_TransferLength;        

   u16         irwffnd_TransferOffset;        

   u8          irwffnd_Reserved1;

   Control_t   irwffnd_Control; 

} __attribute__ ((packed)) micInternalReadWriteFFlashNVRAMDataCmd_t;



typedef struct micCtrlFWFlashSettings

{

   u8  cfwfns_Version;
   u8  cfwfns_State;
   u8  cfwfns_Reserved[14];


} micCtrlFWFlashSettings_t;





/** 09/15/06 DC - Add Internal Wait Event **/

typedef struct micInternalEventWaitCmd

{

    u8        iewc_ScsiOpCode;

    u8        iewc_MicSignature;

    u16       iewc_MicOpCode;        /* 0x1a16 */

    u32       iewc_SeqNo;                   /* in Big Endian */
#define EVT_MAGIC_SEQ_NO    (0x7fffffff)    /* Magic Number for representing ZERO
                                             * (ZERO in this context is for using
                                             * DEFAULT; i.e. the current Event Log
                                             * Sequence Number in RAM) */
    u8        iewc_Reserved0[7];

    Control_t iewc_Control;

} __attribute__ ((packed)) micInternalEventWaitCmd_t;
/** 09/15/06 DC - Add Internal Wait Event **/

/* Possible values for cfwfns_Version */
#define CFWFS_VERSION          1

/* PMIC_INTERNAL_CONTROLLER_GET_LED_INFO */
typedef struct micInternalCtrlGetLEDInfoCmd
{
   u8          icgli_ScsiOpCode;              
   u8          icgli_MicSignature;        
   u16         icgli_MicOpCode;        
   u8          icgli_UniqueCmdId;        
   u8          icgli_LoginKey;        
   u16         icgli_ControllerID;        
   u16         icgli_Reserved0;
   u16         icgli_TransferLength;        
   u16         icgli_TransferOffset;        
   u8          icgli_ControllerCount;        
   Control_t   icgli_Control; 
} __attribute__ ((packed)) micInternalCtrlGetLEDInfoCmd_t;

typedef struct micLEDInfo
{
    u8 mli_UsageFor;
    u8 mli_ColorCapability;
    u8 mli_CurrentColor;
    u8 mli_OnOff;

} micLEDinfo_t;

typedef struct micCtrlGetLEDInfo
{
    u8  gli_LEDCount;
    u8  gli_Reserved[3];

    micLEDinfo_t gli_LEDInfo[0];
  
} micCtrlGetLEDInfo_t;


/* Possible values for mli_UsageFor */
#define PROM_LED_USAGE_FOR_UNKNOWN         0
#define PROM_LED_USAGE_FOR_POWER           1
#define PROM_LED_USAGE_FOR_CTL_STATUS      2
#define PROM_LED_USAGE_FOR_CACHE_DIRTY     3

/*
Possible values for - Bit Map
   mli_ColorCapability 
   mli_CurentColor 
*/
#define PROM_LED_COLOR_OFF                  0
#define PROM_LED_COLOR_RED                  1
#define PROM_LED_COLOR_GREEN                2
#define PROM_LED_COLOR_AMBER                (PROM_LED_COLOR_RED | PROM_LED_COLOR_GREEN)

/* Possible values for mli_OnOff */
#define PROM_LED_OFF    0
#define PROM_LED_ON     1

/* PMIC_INTERNAL_CONTROLLER_GET_STATS */
typedef struct micInternalCtrlGetStatsCmd
{
   u8          icgs_ScsiOpCode;              
   u8          icgs_MicSignature;        
   u16         icgs_MicOpCode;        
   u8          icgs_UniqueCmdId;        
   u8          icgs_LoginKey;        
   u16         icgs_ControllerID;        
   u16         icgs_Reserved0;
   u16         icgs_TransferLength;        
   u16         icgs_TransferOffset;        
   u8          icgs_ControllerCount;        
   Control_t   icgs_Control; 
} __attribute__ ((packed)) micInternalCtrlGetStatsCmd_t;

typedef struct micInternalCtrlGetStats
{
   u16         cgs_RebootCount;
   u8          cgs_Reserved[62];
  
} micInternalCtrlGetStats_t;

/* PMIC_INTERNAL_CONTROLLER_SET_BL_BOOT_DELAY */
typedef struct micInternalSetBLBootDelayCmd
{
   u8          isbbd_ScsiOpCode;              
   u8          isbbd_MicSignature;        
   u16         isbbd_MicOpCode;        
   u8          isbbd_ConfigLock;        
   u8          isbbd_LoginKey;        
   u8          isbbd_ControllerID;
   u8          isbbd_BootUpDelay; 
   u8          isbbd_Reserved1; 
   u8          isbbd_Reserved2;
   u16         isbbd_Reserved3;        
   u16         isbbd_Reserved4;        
   u8          isbbd_Reserved5;        
   Control_t   isbbd_Control; 
} __attribute__ ((packed)) micInternalSetBLBootDelayCmd_t;


#endif /* _INTERNAL_MIC_H */

