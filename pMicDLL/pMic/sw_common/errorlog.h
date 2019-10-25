/*******************************************************************************
 * Filename    : errorlog.h
 * Description : error logging header file
 *               It provides the external definition of the error handler and 
 *               the related routines and data structures.
 *               The error handler can be used to print logs to the stdout,
 *               syslog, a log file and a specified TTY.
 * Created on  : 01/27/03
 * CVS Version : $Id: errorlog.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_ERRORLOG_H__
#define __PI_ERRORLOG_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#undef ERRLOGAPI
#undef ERRLOGCALL
#ifdef WINDOWS
    #include "windows.h"
	#if defined(PROMISE_ERRLOG_DLL)
		#define ERRLOGAPI  __declspec(dllexport)
		#define ERRLOGCALL
	#else
		//#define PROMISEAPI  __declspec(dllimport)
		#define ERRLOGAPI
		#define ERRLOGCALL __cdecl
	#endif
#else
	#define ERRLOGAPI
	#define ERRLOGCALL
#endif

/* --- constant definitions ------------------------------------------------ */
#define EH_TRACE_NONE  0
#define EH_TRACE_ERROR 1
#define EH_TRACE_INFO  2
#define EH_TRACE_DATA  3

#ifdef SINGLE_ERROR_HANDLER
#define GET_ERROR_HANDLER(pEH) getErrorHandler()
#else
#define GET_ERROR_HANDLER(pEH) pEH
#endif

#define MAX_MSG_SIZE 255

/* --- data structures ----------------------------------------------------- */
typedef void error_handler_t;

typedef struct
{
    boolean_t ehp_bLogToStdout;   /* whether log to the stdout */
    boolean_t ehp_bLogToSysLog;   /* whether log to the system log */
    boolean_t ehp_bLogToFile;     /* whether log to a file. If yes, ehp_pu8RemoteMachineIP 
	                                 and ehp_pu8LogFilePath must be specified */
    boolean_t ehp_bLogToTTY;      /* whether log to the specified TTY. If yes, 
	                                 ehp_pu8TTY must be specified - not supported for now */
    u8 ehp_reserved;
    u8 ehp_u8TraceLevel;        /* 0: no trace; 1: error; 2: info */
    u16 ehp_u32LogFileSize;      /* the size of the log file in KB. If 0, no limit */
    u8 *ehp_pu8RemoteMachineIP;  /* the IP address of the remote machine 
                                      where the log file resides on. If null, 
                                      the file is local - not supported for now */
#ifndef PLATFORM_64BIT
    u8 *ehp_pu8Padding1;
#endif
    u8 *ehp_pu8LogFilePath;      /* the path to the log file */
#ifndef PLATFORM_64BIT
    u8 *ehp_pu8Padding2;
#endif
    u8 *ehp_pu8TTY;              /* the path to the TTY - not supported for now */
#ifndef PLATFORM_64BIT
    u8 *ehp_pu8Padding3;
#endif
    u8 *ehp_pu8CallerName;       /* the name of the calling module. The name should
	                                  not exceed 8 characters */
#ifndef PLATFORM_64BIT
    u8 *ehp_pu8Padding4;
#endif
} error_handler_param_t;

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: createErrorHandler 
* Description: create an error handler according to the specified parameters.
* Parameters:    
*   	[in/out] ppHandler, the pointer to the error handler to be returned
*   	[in] pParam, the parameters of the error handler to be created
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: none.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL createErrorHandler(error_handler_t ** ppHandler, error_handler_param_t * pParam);

/**************************************************************************
* Function Name: destroyErrorHandler 
* Description: destroy the error handler.
* Parameters:    
*   	[in/out] ppHandler, the pointer to the error handler to be destroyed.
*	        it will be set to NULL after destruction.
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: createErrorHandler should be called before call this function.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL destroyErrorHandler(error_handler_t ** ppHandler);

#ifdef SINGLE_ERROR_HANDLER
/**************************************************************************
* Function Name: getErrorHandler 
* Description: get the error handler global to the program
* Parameters: None.
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: createErrorHandler should be called before this function is called.     
****************************************************************************/
ERRLOGAPI error_handler_t * ERRLOGCALL getErrorHandler();
#endif

/**************************************************************************
* Function Name: modifyErrorHandler 
* Description: modify the error handler according to the specified parameters.
* Parameters:    
*   	[in] pHandler, the pointer to the error handler to be modified
*	    [in] pParam, the pointer to the parameters to alter the behavior of 
*           the specified error handler
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
*       It currently returns PIERR_NOT_IMPLEMENTED for now.
* Remarks: createErrorHandler should be called before this function is called.
*       It is NOT implemeted for now.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL modifyErrorHandler(error_handler_t * pHandler, error_handler_param_t *pParam);

/**************************************************************************
* Function Name: logInfoMsg 
* Description: log an info type msg.
* Parameters:    
*	    [in] pHandler, the pointer to the error handler
*	    [in] fmt, the msg format
*   	[in] ..., the input to the msg format
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: createErrorHandler should be called before this function is called.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL logInfoMsg(error_handler_t * pHandler, const char * fmt, ...);

/**************************************************************************
* Function Name: logeErrMsg 
* Description: log an error type msg.
* Parameters:    
*	    [in] pHandler, the pointer to the error handler
*   	[in] errCode, the error code
*	    [in] fmt, the msg format
*   	[in] ..., the input to the msg format
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: createErrorHandler should be called before this function is called.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL logErrMsg(error_handler_t * pHandler, u32 errCode, const char * fmt, ...);

/**************************************************************************
* Function Name: logSysErrMsg 
* Description: log a system error msg. The system error code is in errno.
* Parameters:    
*	    [in] pHandler, the pointer to the error handler
*	    [in] fmt, the msg format
*   	[in] ..., the input to the msg format
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: createErrorHandler should be called before this function is called.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL logSysErrMsg(error_handler_t * pHandler, const char * fmt, ...);

/**************************************************************************
* Function Name: logDataMsg 
* Description: log a data msg. The system error code is in errno.
* Parameters:    
*	    [in] pHandler, the pointer to the error handler
*       [in] pu8Data, the data to be logged
*       [in] u32DataLen, the length of the data in bytes
*	    [in] fmt, the msg format
*   	[in] ..., the input to the msg format
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: createErrorHandler should be called before this function is called.     
****************************************************************************/
ERRLOGAPI u32 ERRLOGCALL logDataMsg(error_handler_t * pHandler, u8 * pu8Data, u32 u32DataLen,
    const char * fmt, ...);

#endif /*__PI_ERRORLOG_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: errorlog.h,v $
 * Revision 1.5  2004/07/06 23:14:09  weny
 * pad the data structure to 8 byte aligned
 *
 * Revision 1.4  2004/05/04 18:25:03  weny
 * Using dllexport macroes for exported functions.
 * To make it compatible with DDK compiler for the VDS provider.
 *
 * Revision 1.3  2004/03/24 03:27:33  weny
 * I2 API porting
 *
 * Revision 1.2  2003/03/11 23:54:28  weny
 * add logDataMsg
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
