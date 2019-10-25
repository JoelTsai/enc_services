/*******************************************************************************
 * Filename    : i2plugin.h
 * Description : I2 Plug-In header file
 *               It defines the data structure and functions using in I2 API
 *               plug-in interface
 * Created on  : 02/05/2004
 * CVS Version : $Id: i2plugin.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * Copyright (C) 2004-2004 Promise Technology Inc.
 * All Rights Reserved
 ******************************************************************************/

#ifndef I2_PLUGIN_H
#define I2_PLUGIN_H

/* --- standard C lib header files ----------------------------------------- */
#if defined(WINDOWS)
    /* Windows */
#include <windows.h>
#elif defined(LINUX) || defined(FREEBSD)
    /* LINUX */
#endif /* Operating System */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "i2api.h"

/* --- constant definitions ------------------------------------------------ */
#define MAX_I2API_ORDINALS 0x400
#define I2API_PLUGIN_SPECIFIC_START 0x300

/* I2 API ordinals */
#define I2_ORDINAL_GETPLUGINAPITABLE 0x0
#define I2_ORDINAL_INITIALIZE 0x1
#define I2_ORDINAL_FINALIZE 0x2

#define I2_ORDINAL_DISCOVER	0x10
#define I2_ORDINAL_DISCOVERBYPRDCTPATH	0x11
#define I2_ORDINAL_GETNUMSUBSYSTEMS	0x12
#define I2_ORDINAL_GETNUMHBAS	0x13
#define I2_ORDINAL_GETDISCOVERPATH	0x14
	
#define I2_ORDINAL_GETSUBSYSINFO	0x20
#define I2_ORDINAL_GETSUBSYSSETTINGS	0x21
#define I2_ORDINAL_SETSUBSYSSETTINGS	0x22
	
#define I2_ORDINAL_GETCTRLINFO	0x28
#define I2_ORDINAL_GETCTRLSETTINGS	0x29
#define I2_ORDINAL_SETCTRLSETTINGS	0x2a

#define I2_ORDINAL_GETPDINFO	0x30
#define I2_ORDINAL_GETPDSETTINGS	0x31
#define I2_ORDINAL_SETPDSETTINGS	0x32
#define I2_ORDINAL_LOCATEPD	0x33
#define I2_ORDINAL_GETMISSINGPD	0x34
#define I2_ORDINAL_STOPLOCATEPD	0x3d
#define I2_ORDINAL_LOCATEPDSTATUS	0x3e
	
#define I2_ORDINAL_GETLDINFO	0x38
#define I2_ORDINAL_GETLDSETTINGS	0x39
#define I2_ORDINAL_SETLDSETTINGS	0x3a
#define I2_ORDINAL_GETERRORTABLE	0x3b
#define I2_ORDINAL_LOCATELD	0x3c
	
#define I2_ORDINAL_GETDAINFO	0x40
#define I2_ORDINAL_GETDASETTINGS	0x41
#define I2_ORDINAL_SETDASETTINGS	0x42
#define I2_ORDINAL_LOCATEDA	0x43
#define I2_ORDINAL_GETDACONFIG	0x44
#define I2_ORDINAL_ADDDA	0x45
#define I2_ORDINAL_DELDA	0x46
#define I2_ORDINAL_DELALLDA	0x47
#define I2_ORDINAL_ADDLD	0x48
#define I2_ORDINAL_DELLD	0x49
#define I2_ORDINAL_PRCINCOMPLETEDA	0x4a
#define I2_ORDINAL_MIGRATEDA	0x4b
#define I2_ORDINAL_ONLNDAPROC	0x4c
	
#define I2_ORDINAL_GETSPAREINFO	0x50
#define I2_ORDINAL_GETALLSPAREINFO	0x51
#define I2_ORDINAL_SETSPARESETTINGS	0x52
#define I2_ORDINAL_ADDSPARE	0x53
#define I2_ORDINAL_DELSPARE	0x54
#define I2_ORDINAL_DELALLSPARE	0x55
	
#define I2_ORDINAL_GETSYNCPROGRESS	0x60
#define I2_ORDINAL_GETMIGPROGRESS	0x61
	
#define I2_ORDINAL_GETINITPROGRESS	0x68
#define I2_ORDINAL_STARTINIT	0x69
#define I2_ORDINAL_STOPINIT	0x6a
#define I2_ORDINAL_PAUSEINIT	0x6b
#define I2_ORDINAL_RESUMEINIT	0x6c
	
#define I2_ORDINAL_GETRCPROGRESS	0x6d
#define I2_ORDINAL_STARTRC	0x6e
#define I2_ORDINAL_STOPRC	0x6f
#define I2_ORDINAL_PAUSERC	0x70
#define I2_ORDINAL_RESUMERC	0x71
	
#define I2_ORDINAL_GETRBPROGRESS	0x72
#define I2_ORDINAL_STARTRB	0x73
#define I2_ORDINAL_STOPRB	0x74
#define I2_ORDINAL_PAUSERB	0x75
#define I2_ORDINAL_RESUMERB	0x76
	
#define I2_ORDINAL_GETMPPROGRESS	0x77
#define I2_ORDINAL_STARTMP	0x78
#define I2_ORDINAL_STOPMP	0x79
#define I2_ORDINAL_PAUSEMP	0x7a
#define I2_ORDINAL_RESUMEMP	0x7b
	
#define I2_ORDINAL_GETENCLINFO	0x90
#define I2_ORDINAL_GETENCLSTATUS	0x91
#define I2_ORDINAL_LOCATEENCL	0x92
#define I2_ORDINAL_GETFRUINFO	0x93
#define I2_ORDINAL_LOCATEFRU	0x94
#define I2_ORDINAL_GETBATINFO	0x95
#define I2_ORDINAL_STARTBATRECON	0x96
#define I2_ORDINAL_GETBUZZSTATUS	0x97
#define I2_ORDINAL_TURNONBUZZ	0x98
#define I2_ORDINAL_TURNOFFBUZZ	0x99
	
#define I2_ORDINAL_GETEVENTS	0xa0
#define I2_ORDINAL_GETFIRSTEVENTS	0xa1
#define I2_ORDINAL_GETLASTEVENTS	0xa2
#define I2_ORDINAL_GETEVENTSTAT	0xa3
#define I2_ORDINAL_GETEVENTLOCSTAT	0xa4
#define I2_ORDINAL_CLEAREVENTLOG	0xa5
	
#define I2_ORIDNAL_GETSCSISETTINGS	0xb0
#define I2_ORDINAL_SETSCSISETTINGS	0xb1
#define I2_ORDINAL_GETCHSCSISETTINGS	0xb2
#define I2_ORDINAL_SETCHSCSISETTINGS	0xb3
#define I2_ORDINAL_GETSCSILUNMAP	0xb4
#define I2_ORDINAL_SETSCSILUNMAP	0xb5
	
#define I2_ORDINAL_GETISCSIINFO	0xc0
#define I2_ORDINAL_GETISCSISETTINGS	0xc1
#define I2_ORDINAL_SETISCSISETTINGS	0xc2
#define I2_ORDINAL_GETISCSISLPINFO	0xc3
#define I2_ORDINAL_GETISCSISLPSETTINGS	0xc4
#define I2_ORDINAL_SETISCSISLPSETTINGS	0xc5
#define I2_ORDINAL_GETISNSINFO	0xc6
#define I2_ORDINAL_GETISNSSETTINGS	0xc7
#define I2_ORDINAL_SETISNSSETTINGS	0xc8
#define I2_ORDINAL_GETCHAP	0xc9
#define I2_ORDINAL_SETCHAP	0xca
#define I2_ORDINAL_ADDCHAP	0xcb
#define I2_ORDINAL_DELCHAP	0xcc
#define I2_ORDINAL_ISCSIPING	0xcd
#define I2_ORDINAL_GETISCSINODELIST	0xce
	
#define I2_ORDINAL_LOGIN	0x100
#define I2_ORDINAL_LOGOUT	0x101
#define I2_ORDINAL_GETCURSESSIONINFO	0x102
#define I2_ORDINAL_GETSESSIONINFO	0x103
#define I2_ORDINAL_FORCESESSIONLOGOUT	0x104
	
#define I2_ORDINAL_GETINITIATORLIST	0x110
#define I2_ORDINAL_ADDINITIATOR	0x111 
#define I2_ORDINAL_DELINITIATOR	0x112
#define I2_ORDINAL_GETLMMTABLE	0x113
#define I2_ORDINAL_ADDLMMENTRY	0x114
#define I2_ORDINAL_SETLMMENTRY	0x115
#define I2_ORDINAL_DELLMMENTRY	0x116
	
#define I2_ORDINAL_GETUSER	0x140
#define I2_ORDINAL_GETALLUSER	0x141
#define I2_ORDINAL_ADDUSER	0x142
#define I2_ORDINAL_MODUSER	0x143
#define I2_ORDINAL_DELUSER	0x144
#define I2_ORDINAL_SETPWD	0x145
	
#define I2_ORDINAL_LOCK	0x150
#define I2_ORDINAL_EXTENDLOCK	0x151
#define I2_ORDINAL_UNLOCK	0x152
#define I2_ORDINAL_CHECKLOCK	0x153
	
#define I2_ORDINAL_GETBGASCHEDULE	0x158
#define I2_ORDINAL_ADDBGASCHEDULE	0x159
#define I2_ORDINAL_DELBGASCHEDULE	0x15a
#define I2_ORDINAL_MODBGASCHEDULE	0x15b
	
#define I2_ORDINAL_INITFLASH	0x160
#define I2_ORDINAL_FINIFLASH	0x161
#define I2_ORDINAL_XFERFLASHIMG	0x162
#define I2_ORDINAL_FLASHIMG	0x163
#define I2_ORDINAL_GETFLASHPROGRESS	0x164
#define I2_ORDINAL_GETFLASHIMGHEADER	0x165
#define I2_ORDINAL_VERIFYFLASHIMG	0x166
	
#define I2_ORDINAL_GETSNMPCONFIG	0x170
#define I2_ORDINAL_SETSNMPCONFIG	0x171
	
#define I2_ORDINAL_PAUSEMIGRATION	0x180
#define I2_ORDINAL_RESUMEMIGRATION	0x181	

#define I2_ORDINAL_GETDRIVERINFO	0x2F0

#define I2_ORDINAL_BYPASSCMD	0x2FF
	
/* --- data structures ----------------------------------------------------- */
#if defined(WINDOWS)
    /* Windows */
    typedef FARPROC function_pointer_t;
    typedef HMODULE plugin_handle_t;
#elif defined(LINUX) || defined(FREEBSD)
    /* LINUX */
    typedef void * function_pointer_t;
    typedef void * plugin_handle_t;
#endif /* Operating System */

typedef struct
{
    u16 pat_u16NumOfAPIs;
    u8 pat_u8Reserved[6];
    function_pointer_t  * pat_fpAPIs;
} plugin_api_table_t;

/* --- functional routines ------------------------------------------------- */

/**************************************************************************
 * Function Name: i2_getPlugInAPITable 
 * Description: get the plug-in API table of the API function pointers
 * Parameters:    
 *   	[out] ppTable, the pointer to the plug-in API table
 * Return: PIERR_NO_ERROR: succeed, otherwise: fail
 * Remarks: none.     
 ***************************************************************************/
I2API u32 I2CALL i2_getPlugInAPITable(plugin_handle_t pHandle, plugin_api_table_t ** ppTable);
typedef u32 (* fpGetPlugInAPITable_t)(plugin_handle_t, plugin_api_table_t **);

#endif /* I2_PLUGIN_H */

/******************************************************************************
 * Change Log
 *
 * $Log: i2plugin.h,v $
 * Revision 1.6  2007/08/30 08:53:24  kenh
 * Add FREEBSD in-band support
 *
 * Revision 1.5  2004/07/13 18:48:49  debinc
 * add a #define for in-band
 *
 * Revision 1.4  2004/07/08 23:06:43  weny
 * merge with Napa I2 API
 *
 * Revision 1.3  2004/07/06 23:15:36  weny
 * use pibasic.h
 *
 * Revision 1.2  2004/05/04 18:25:04  weny
 * Using dllexport macroes for exported functions.
 * To make it compatible with DDK compiler for the VDS provider.
 *
 * Revision 1.1  2004/03/24 03:24:12  weny
 * I2 API porting
 *
 *
 *****************************************************************************/
