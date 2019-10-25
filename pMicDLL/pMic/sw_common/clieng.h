/*******************************************************************************
 * Filename    : clieng.h
 * Description : CLI Engine header file
 *               * Define the interfaces and data structures exposed by the CLI
 *                 Engine.
 *               * Shared among Telnet/SSH and RS232
 * Created on  : 02/24/03
 * CVS Version : $Id: clieng.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_CLIENGINE_H__
#define __PI_CLIENGINE_H__

/* --- standard C lib header files ----------------------------------------- */
#include <stdio.h>
#include <time.h>

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"
#include "userdata.h"
#include "cliparselib.h"

/* --- constants and data structures --------------------------------------- */
extern time_t * peLastTime;

#define PROMSIE_CLI_ENGINE_VERSION 1


/* --- data structures ----------------------------------------------------- */

/* pcit_unknown, line and password are to be implemented in Phase 1 */
typedef enum
{
	pcit_unknown = 0,
	pcit_line = 1,
	pcit_navigation_cmd = 2,
	pcit_param = 3,
	pcit_password = 4,
	pcit_anykey = 5
} pce_cli_input_type_t;

typedef enum
{
	/* TBD */
	pcnc_nextCommand=1,
	pcnc_previousCommand=2
} pce_cli_navigation_command_t;

/* pcot_text is to be implemented in Phase 1 */
typedef enum
{
	pcot_unknown = 0,
	pcot_text = 1,
	pcot_navigation = 2
} pce_cli_output_type_t;

typedef enum
{
	/* TBD */
	pcgt_baudRate = 1,
	pcgt_flowControl =2
} pce_cli_gettty_type_t;

typedef enum
{
	/* TBD */
	pcst_baudRate = 1,
	pcst_flowControl = 2
} pce_cli_settty_type_t;

/***************************************************************************
* Func Type Name: pce_pfunc_getInput_t 
* Description: get the specified input from the TTY.
* Parameters:    
*   	[in/out] pce_cli_input_type_t *, the in parameter specifies the 
*           desired type of input, if it is unknown, it means get any type 
*           of input; the actual type of the input will be returned to this 
*           parameter;
*       [out] u8 *, the input buffer for the input data to be returned;
*       [in/out] u32 *, the in paramerter specifies the size of the input 
*           buffer; the out parameter specifies the length of the input data
*           returned in the input buffer
* Return: PIERR_NO_ERROR: succeed, otherwise: fail 
* Remarks: none.     
****************************************************************************/
typedef u32 (* pce_pfunc_getInput_t)(pce_cli_input_type_t *, u8 *, u32 *, u32);

/***************************************************************************
* Func Type Name: pce_pfunc_postOutput_t 
* Description: post the specified output to the TTY.
* Parameters:    
*   	[in] pce_cli_output_type_t, the type of the output;
*       [in] u8 *, the output buffer that contains the output data or 
*           parameter;
*       [in] u32, the length of the output data in the output buffer
* Return: PIERR_NO_ERROR: succeed, otherwise: fail 
* Remarks: none.     
****************************************************************************/
typedef u32 (* pce_pfunc_postOutput_t)(pce_cli_output_type_t, u8 *, u32);

/***************************************************************************
* Func Type Name: pfunc_getTTY_t 
* Description: get the TTY settings.
* Parameters:    
*   	[in] pce_cli_gettty_type_t, the type of the configuration;
*       [out] u8 *, the buffer that the configuration data retun to;
*       [in/out] u32 , the in parameter specifies the size of the buffer,
*           the out parameter specifies the returned data length.
* Return: PIERR_NO_ERROR: succeed, otherwise: fail 
* Remarks: none.     
****************************************************************************/
typedef u32 (* pce_pfunc_getTTY_t)(pce_cli_gettty_type_t, u8 *, u32);

/***************************************************************************
* Func Type Name: pce_pfunc_setTTY_t 
* Description: set the TTY settings.
* Parameters:    
*   	[in] pce_cli_settty_type_t, the type of the configuration;
*       [in] u8 *, the buffer that contains/receives the configuration data;
*       [in] u32 , the data length of the configuration buffer.
* Return: PIERR_NO_ERROR: succeed, otherwise: fail 
* Remarks: none.     
****************************************************************************/
typedef u32 (* pce_pfunc_setTTY_t)(pce_cli_settty_type_t, u8 *, u32);

#define CLI_INTERFACE_INBAND    0
#define CLI_INTERFACE_RS232     1
#define CLI_INTERFACE_TELNET    2
#define CLI_INTERFACE_FW        3
#define CLI_INTERFACE_SSH       4

typedef struct
{
	u32 pcep_u32Version; /* to verify the CLI Engine version */
	u32 pcep_u32MaxCmdLineLen; /* the max number of characters for one command */
	u32 pcep_u32CmdHistroyBufSize; /* the size of the command history buffer. In the number of commands. */
	u32 pcep_u32CLIIdleTimeout; /* in minutes. When there is not any input for this amount of time, the CLI will timeout the session, release all the resources and quit itself */
    u32 pcep_u8CLIInterface; /* CLI_INTERFACE_RS232 or CLI_INTERFACE_TELNET */
    u32 pcep_u8Padding[7];
	pce_pfunc_getInput_t pcep_pfGetInput;
	pce_pfunc_postOutput_t pcep_pfPostOutput;
	pce_pfunc_getTTY_t pcep_pfGetTTY;
    pce_pfunc_setTTY_t pcep_pfSetTTY;
    u8 * pcep_pu8MessageQueuePath;
	u8 * pcep_pu8NewLine; /* new line string. e.g. "\n" or "\r\n" */
#ifndef SINGLE_ERROR_HANDLER
   error_handler_t * pcep_pehErrorHandler; 
#else
    void * pcep_pReserved;
#endif
    boolean_t pcep_bEnableScriptEngine;
    boolean_t pcep_bSilentMode;
    boolean_t pcep_bOutput2File;
    boolean_t pcep_bChangeSubsysPath; /* in-band only */
    FILE * pcep_fhFileHandler;
    u32  pcep_u32SubsysPath;
    char  pcep_cUserName[MAX_USER_NAME_LENGTH];
    char  pcep_cPassword[MAX_PASSWORD_LENGTH];
    char  pcep_cInputCmd[MAX_COMMAND_LINE_SIZE+1];
    boolean_t pcep_bProcessConfScript;
    boolean_t pcep_bEnableAutoLogin;
    u8 pcep_u8Reserved[6];
    FILE * pcep_fhConfScript;
    FILE * pcep_fhConfScriptOutput;
} pce_cli_engine_param_t;

/* --- functional routines ------------------------------------------------- */

/***************************************************************************
* Func Name: pce_enterCLI
* Description: enter the CLI Engine.
* Parameters:    
*   	[in] pParam, the parameter of the CLI.
        [in] pLastTime, the pointer of last keystroke time stamp
* Return: PIERR_NO_ERROR: succeed, otherwise: fail 
* Remarks: createCommandProcessor should be called before this func is called.     
****************************************************************************/
u32 pce_enterCLI(pce_cli_engine_param_t * pParam, time_t * pLastTime);

/***************************************************************************
* Func Type Name: pce_quitCLIShell
* Description: release resource used by CLI
* Parameters:
*   	None
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: none.
****************************************************************************/
u32 pce_quitCLIShell();

/***************************************************************************
* Func Type Name: pce_getTerminateSignal
* Description: check if CLI has returned a terminate signal
* Parameters:
*           None
* Return: TRUE/FALSE
* Remarks: none.
****************************************************************************/
boolean_t pce_getTerminateSignal();
#endif /*__PI_CLIENGINE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: clieng.h,v $
 * Revision 1.18.28.3  2009/11/04 03:20:13  xinw
 * merge ssh support
 *
 * Revision 1.18.28.2  2009/11/03 06:27:41  xinw
 * merge ssh support
 *
 * Revision 1.18.28.1  2009/05/20 07:49:13  xinw
 * add fw interface for cli
 *
 * Revision 1.18  2007/09/19 06:39:20  danielz
 * CLI to support processing configuration script
 *
 * Revision 1.17  2007/05/22 00:19:38  debinc
 * add cliparselib
 *
 * Revision 1.16  2005/11/21 06:36:59  weny
 * 1. SW restructuring
 * 2. merge with library changes for VDS
 *
 * Revision 1.15  2004/10/04 18:11:18  debinc
 * do not share extern variable between cli engine and clitest
 *
 * Revision 1.14  2004/09/30 03:45:41  weny
 * fix a in-band compiling error
 *
 * Revision 1.13  2004/09/28 01:51:02  debinc
 * update lastTime when changing time
 *
 * Revision 1.12  2004/08/19 01:50:52  weny
 * fix bug 3655 - When a command longer than 255 chars is sent to CLI, CLI will not return any error message.
 *
 * Revision 1.11  2004/07/20 23:44:52  debinc
 * reorg funtion use dby clitest
 *
 * Revision 1.10  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.9  2004/07/20 01:40:59  debinc
 * export some functions for clitest
 *
 * Revision 1.8  2004/03/24 03:26:29  weny
 * I2 API porting
 *
 * Revision 1.7  2004/02/27 23:42:43  zhengj
 * fix bug#2756
 *
 * Revision 1.6  2003/11/12 19:49:48  sergiyv
 * EVT/DVT Script Engine Support
 *
 * Revision 1.5  2003/11/06 09:45:41  sergiyv
 * Changes for support "| more" command
 *
 * Revision 1.4  2003/10/09 22:27:59  zhengj
 * interface change for input function
 *
 * Revision 1.3  2003/04/16 23:14:34  weny
 * add msg queue path param
 *
 * Revision 1.2  2003/03/27 20:14:34  weny
 * make it conformant to the coding standard
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 ******************************************************************************/
