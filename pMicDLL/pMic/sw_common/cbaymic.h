/***************************************************************
 *
 * Filename    : cbaymic.h
 * Description : Clearbay specific frontend mic definitions
 * Created on  : 2006/10/17
 * CVS Version : $Id: cbaymic.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2006-2007
 * All Rights Reserved
 *
 ****************************************************************/
#ifndef _CBAYMIC_H_
#define _CBAYMIC_H_

//#include "mgtapilib.h"
//#include "cctl_support.h"
#if 0
/*
 * Read/Write MIC. PMIC_SET_LMM_KEY | PMIC_GET_LMM_KEY
 * Used to set the mapping to be used for LMM.
 * It could be either Slotbased or WWN based.
 * Changes takes effect only after reboot.
 * Configuration saved in NVRAM and applied on reboot.
 */
typedef struct micLmmKeyConfig_
{
    u8          cm_ScsiOpCode;
    u8          cm_MicSignature;           
    u16         cm_MicOpCode;
    u8          cm_UniqueCmdId;    
    u8          cm_LoginKey;
    u8          cm_Reserved0;
    u8          cm_Reserved1;
    u8          cm_Reserved2;
#define LMM_KEY_IS_SLOT (1)
#define LMM_KEY_IS_WWN  (2)
    u8          cm_SlotBasedKey; /* boolean: LMM based on Slot or WWN address */
    u16         cm_TransferLength;
    u16         cm_TransferOffset;
    u8          cm_Reserved; 
    Control_t   cm_Control; 
} __attribute__ ((packed)) micLmmKeyConfig_t;
#endif
/* 
 * Output struct: 
 * This information is not controller specific but for the whole subsystem 
 */
typedef struct LmmKeyConfig_ {
    u8 lkc_LmmKeyCurrent; /* current settings */
    u8 lkc_LmmKeyNVRAM;   /* NVRAM settings which take effect on reboot */
    u8 lkc_Reserved[6];
} LmmKeyConfig_t;

/* 
 * Output format:
 * Note, only bytes 0~7 will have values defined for WWN. 
 * Rest will be all zeros.
 */
#define LMM_LOCAL_CTRL_WWN_INDEX (0)
#define LMM_PEER_CTRL_WWN_INDEX (1)

#define LMM_MAX_SLOT_TO_WWN_ENTRIES (2)
typedef struct LmmMapping_ {
    u8 lm_SlotId;
    u8 lm_NrMapping; /* always 2 on cbay. For each slot, nr of WWN addresses */
    u8 lm_Reserved[6];
    u8 lm_WWN[1][256]; /* array of WWN entries each defined to be 256 bytes*/
                      /* array size defined to be NrMapping */
} LmmMapping_t;

#define LMM_MAX_MAP_ENTRIES (6) /* Nr of server slots in clearbay */
typedef struct LmmMapInfo_ {
    u8 lmi_NrMaps;          /* in cbay it is 6 */
    u8 lmi_Reserved[7];
    LmmMapping_t lmi_Maps[1]; /* in cbay an array of 6, one for each slot */
} LmmMapInfo_t;

#endif /* _CBAYMIC_H_ */
/***************************************************************
 * Change Log
 *
 * $Log: cbaymic.h,v $
 * Revision 1.1  2007/01/02 23:13:48  debinc
 * slot wwn mapping support
 *
 * Revision 1.1.2.1  2006/10/17 19:40:53  lakshmi.s
 * clearbay placeholder
 *
 *
 ****************************************************************/
