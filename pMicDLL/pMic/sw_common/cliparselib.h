/*******************************************************************************
 * Filename    : cliparselib.h
 * Description : CLI Command Processor header file
 * Created on  : 05/17/2007
 * CVS Version : $Id: cliparselib.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/
#ifndef __CLI_PARSE_H__
#define __CLI_PARSE_H__
/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"
#include "i2api.h"
#include "i2apiob.h"
#include "dtdecode.h"

/* --- constants and data structures  --------------------------------------- */
#define MAX_OUTPUT_LINE_LENGTH  79
#define MAX_COMMAND_LINE_SIZE 279
/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: processCmdLineIdList
* Description: process the command line id list to form a unary array of
*       ids.
* Parameters:
*       [in] pu8IdList, a id list form command line, ended with '\0'.
*       [out] pu32Ids, the id array to be returned
*       [in/out] pu32IdCount, as in param - the expected count of ids; as out
*           param - the actually inputed count of ids from the command line.
* Return: PIERR_NO_ERROR, succeeded; otherwise, failed.
* Remarks: pu32Ids is a buffer can at least hold *pu32Count ids.
****************************************************************************/
u32 processCmdLineIdList(const u8 * pu8IdList, u32 * pu32Ids, u32 * pu32IdCount);

u32 retrieveCmdLineSettingsEnable(u8 * pu8Value, u8 * pEnable);
u32 retrieveCmdLineSettingsSize(u8 * pu8Value, u64 * pu64Value,
    u64 u64Min, u64 u64Max);
u32 retrieveCmdLineSettingsUint(u8 * pu8Value, u32 * pu32Value,
    u32 u32Min, u32 u32Max);
u32 retrieveCmdLineSettings(u8 * pu8StrArray[], u32 u32StrArrayLen,
    const char * u8Name, u8 * u8Value, u32 u32Len);
u32 cliparse_validateCmdLineSettings(u8 * pError, const char cOption,
    u8 * pu8StrArray[], char * cNameArray[], u32 u32StrArrayLen, u32 u32NameArrayLen);
u32 processCmdLineSettings(u8 * pu8Settings,
    u8 * pu8StrArray[], u32 * u32ArrayLen);
u32 getCmdLineSettingsString(u8 * pu8Settings[], u32 u32ArrayLen,
    const u8 * pu8SettingName, const u8 * pu8DefaultValue,
    u8 * pu8StrValue, u32 u32Size);
u32 getCmdLineSettingsUint(u8 * pu8Settings[], u32 u32ArrayLen,
    const u8 * pu8SettingName, const u32 u32DefaultValue, u32 * pu32Value);
u32 getCmdLineSettingsSint(u8 * pu8Settings[], u32 u32ArrayLen,
    const u8 * pu8SettingName, const s32 s32DefaultValue, s32 * ps32Value);
u32 getCmdLineSettingsBoolean(u8 * pu8Settings[], u32 u32ArrayLen,
    const u8 * pu8SettingName, const boolean_t bDefaultValue,
    boolean_t * pbValue);
u32 getCmdLineSettingsSize(u8 * pu8Settings[], u32 u32ArrayLen,
    const u8 * pu8SettingName, const u64 u64DefaultValue, u64 * pu64Value);
u32 retrieveCmdLineSettingsPsuType(u8 * pu8Value, u32 * pValue);    
#endif

