/*******************************************************************************
 * Filename    : evtlog.h
 * Description : event logger header file
 *               It provides the external definition of the event logger and 
 *               the related routines and data structures.
 *               The event logger is used to log message to the system
 *               logger or file.
 * Created on  : 07/18/06
 * CVS Version : $Id: evtlog.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2006
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_EVTLOG_H__
#define __PI_EVTLOG_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#undef EVTLOGAPI
#undef EVTLOGAPI
#ifdef WINDOWS
    #include "windows.h"
	#if defined(PROMISE_EVTLOG_DLL)
		#define EVTLOGAPI  __declspec(dllexport)
		#define EVTLOGCALL
	#else
		//#define PROMISEAPI  __declspec(dllimport)
		#define EVTLOGAPI
		#define EVTLOGCALL __cdecl
	#endif
#else
	#define EVTLOGAPI
	#define EVTLOGCALL
#endif

/* --- constant definitions ------------------------------------------------ */

#define EL_INFO                    0x2
#define EL_WARNING                 0x3
#define EL_MINOR                   0x4
#define EL_MAJOR                   0x5
#define EL_CRITICAL                0x6
#define EL_FATAL                   0x7

/* --- data structures ----------------------------------------------------- */


/* --- functional routines ------------------------------------------------- */

/**************************************************************************
* Function Name: el_logMsg 
* Description: log a message.
* Parameters:    
*	    [in] u8Level, the message level
*	    [in] fmt, the msg format
*   	[in] ..., the input to the msg format
* Return: PIERR_NO_ERROR: succeed, otherwise: fail
* Remarks: 
****************************************************************************/
EVTLOGAPI u32 EVTLOGCALL el_logMsg(u8 u8Level, const char * fmt, ...);

#endif /*__PI_ERRORLOGGER_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: evtlog.h,v $
 * Revision 1.1  2006/08/21 10:43:40  danielz
 * event logger header files
 *
 ******************************************************************************/
