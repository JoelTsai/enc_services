/*******************************************************************************
 * Filename    : syncobj.h
 * Description : Synchronous Object header file
 * Created on  : 08/06/03
 * CVS Version : $Id: syncobj.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_SYNCOBJ_H__
#define __PI_SYNCOBJ_H__

/* --- standard C lib header files ----------------------------------------- */
#if defined(WINDOWS)
    #include <windows.h>
#elif defined(LINUX) || defined(FREEBSD)
    #include <errno.h>
    #include <pthread.h>
    #include <unistd.h>
#endif

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */

#if defined(WINDOWS)
typedef struct
{
    HANDLE  sm_hMutex;
} sync_mutex_t;
#elif defined(LINUX) || defined(FREEBSD)
typedef struct
{
    pthread_mutex_t sm_ptmMutex;
    pthread_mutexattr_t sm_ptmMutexAttr;  /* always recursive NP */
} sync_mutex_t;
#endif
/* --- functional routines ------------------------------------------------- */

/******************************************************************************
* Function Name: sync_createMutex
* Description: create a mutex
* Parameters:    
*       [out] psm, the mutex to be created
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: none.
*******************************************************************************/
u32 sync_createMutex(sync_mutex_t * psm);

/******************************************************************************
* Function Name: sync_destroyMutex
* Description: destroy a mutex
* Parameters:    
*       [in] psm, the mutex to be destroyed
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: the psm is created by sync_createMutex().
*******************************************************************************/
u32 sync_destroyMutex(sync_mutex_t *psm);

/******************************************************************************
* Function Name: sync_acquireMutex
* Description: acquire a mutex
* Parameters:    
*       [in] psm, the mutex to be acquired
*       [in] u32Timeout, the maximum waiting period if the mutex has been acquired
*           by another thread. This is only supported on Windows.
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: the psm is created by sync_createMutex()..
*******************************************************************************/
u32 sync_acquireMutex(sync_mutex_t *psm, u32 u32Timeout);

/******************************************************************************
* Function Name: sync_releaseMutex
* Description: release a mutex.
* Parameters:    
*       [in] psm, the mutex to be acquired
* Return: the completion error code. PIERR_NO_ERROR, succeeded; otherwise, failed
* Remarks: the psm is created by sync_createMutex(). 
*******************************************************************************/
u32 sync_releaseMutex(sync_mutex_t *psm);

#endif /*__PI_SYNCOBJ_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: syncobj.h,v $
 * Revision 1.2  2007/08/30 08:53:24  kenh
 * Add FREEBSD in-band support
 *
 * Revision 1.1  2003/08/12 01:21:03  weny
 * add for in-band support on Windows
 *
 ******************************************************************************/
