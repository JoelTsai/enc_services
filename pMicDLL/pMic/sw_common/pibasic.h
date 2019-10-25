/*******************************************************************************
 * Filename    : pibasic.h
 * Description : promise iBox types header file
 *               It provides the definitions of some basic and common data types.
 * Created on  : 01/28/03
 * CVS Version : $Id: pibasic.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/


#ifndef I2_BASIC_H
#define I2_BASIC_H

/* --- standard C lib header files ------------------------------------------ */
#if defined(WINDOWS)
    #include <windows.h>
#elif defined(LINUX) || defined(FREEBSD)
    #include <pthread.h>
#endif

/* --- internal header files ------------------------------------------------ */

/* --- constants & data structures ------------------------------------------ */

#define IN
#define OUT

typedef unsigned char u8;
typedef u8 __u8;
typedef unsigned short u16;
typedef u16 __u16;
typedef unsigned int u32;
typedef u32 __u32;
typedef char s8;
typedef short s16;
typedef int s32;
#ifdef WINDOWS
    typedef unsigned __int64 u64;
    typedef __int64 s64;
    typedef DWORD pid_t;
#else
    typedef unsigned long long u64;
    typedef long long s64;
#endif
typedef u64 __u64;

#ifndef TRUE
    #define TRUE 0x1
#endif

#ifndef FALSE
    #define FALSE 0x0
#endif

#ifndef SOLARIS
typedef u8 boolean_t;
#endif

#if defined(WINDOWS)
    #define CURRENT_PROCESS_ID()    GetCurrentProcessId()
    #define CURRENT_THREAD_ID()     GetCurrentThreadId()
    #define strcasecmp _stricmp
    #define strncasecmp _strnicmp
    #define snprintf _snprintf
    #define vsnprintf _vsnprintf
    #define __attribute__(__X__)
#elif defined(LINUX) || defined(FREEBSD)
    #define strcmpi strcasecmp
    #define stricmp strcasecmp
    #define CURRENT_PROCESS_ID()    getpid()
    #define CURRENT_THREAD_ID()     pthread_self()
#endif

#define MAX_PATH_LENGTH	255

/* --- functional routines ------------------------------------------------- */

/* no functions */

#endif /* I2_BASIC_H */

/******************************************************************************
 * Change Log
 *
 * $Log: pibasic.h,v $
 * Revision 1.45  2008/03/07 06:23:19  kenh
 * Porting to Solaris OS
 *
 * Revision 1.44  2007/08/30 08:53:24  kenh
 * Add FREEBSD in-band support
 *
 * Revision 1.43  2007/07/27 06:39:12  weny
 * changes for I2 API Dev Kit - to obsolete prbasic.h
 *
 * Revision 1.6  2007/03/06 00:58:24  weny
 * correct typedef from s32 to s64 for Linux.
 *
 * Revision 1.5  2007/03/04 01:14:13  weny
 * fix compiling error with VC++ .NET 2002.
 *
 * Revision 1.4  2006/08/22 06:15:55  fieldsy
 * InBand BGA support
 *
 * Revision 1.3  2004/07/20 20:54:26  weny
 * I2 API clean up
 *
 * Revision 1.2  2004/07/15 22:59:59  debinc
 * interface defintion
 *
 * Revision 1.1  2004/03/24 03:24:12  weny
 * I2 API porting
 *
 *
 *****************************************************************************/

