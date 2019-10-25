/*******************************************************************************
 * Filename    : resource.h
 * Description : resource header file
 *               * resource is used together with resource pool to provide
 *                 a flexible way to manage certain type of resources.
 *               * resource is an abstract data type. Each sub class should
 *                 implement the 8 interfaces.
 *               * The header file provides the external definition of resource
 *                 and the related routines. 
 * Created on  : 01/29/03
 * CVS Version : $Id: resource.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_RESOURCE_H__
#define __PI_RESOURCE_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "errorlog.h"

/* --- constant definitions ------------------------------------------------ */
#define MAX_EXTENDED_PARAM_LENGTH 8 /* to avoid frequent malloc system call, use static array size */

/* --- data structures ----------------------------------------------------- */

typedef void work_t;	 /* work assigned to a resource */
typedef void resource_t; /* to encapsulate the logic inside resource pool itself */

typedef struct
{
#ifndef SINGLE_ERROR_HANDLER
    error_handler_t * rp_pehErrorHandler;
    void * rp_pReserved;
#endif
	__u32 rp_u32ResourceTypeId;   /* the type id of the resource */
	__u32 rp_u32ParamLength;      /* the number of bytes of rp_u8Param */
    boolean_t rp_bFulltime;       /* fulltime resource */
    u8 rp_u8Reserved1[7];
	__u8 rp_u8ExtendedParam[MAX_EXTENDED_PARAM_LENGTH];			  /* the parameters of the resource */
} resource_param_t;

/* resource interfaces */
/* 
Func Type Name: pfunc_create_t
Description: create a resource according to the parameters.
Context: None.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in/out] resource_t **, the pointer to the resource to be created and returned.
	[in] resource_param_t *, the parameters of the resource pool.
*/
typedef __u32 (* pfunc_create_t)( resource_t **, resource_param_t * );

/* 
Func Type Name: pfunc_destroy_t
Description: destroy the resource.
Context: pfunc_create_t must be called successfully before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in/out] resource_t **, the pointer to the resource to be destroyed. 
	    After destruction, it will be set to NULL.
*/
typedef __u32 (* pfunc_destroy_t)( resource_t ** );

/* 
Func Type Name: pfunc_reserve_t
Description: reserve the resource. If the resource is free, it can be reserved;
    otherwise the func will fail.
Context: pfunc_create_t must be called successfully before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] resource_t *, the pointer to the resource to be reserved. 
*/
typedef __u32 (* pfunc_reserve_t)( resource_t * );

/* 
Func Type Name: pfunc_assign_t
Description: assign a work to the resource. If the resource is busy, the func
    will fail. The sub class can decide whether to process the assignment
    synchronously or asynchronously.
Context: pfunc_create_t must be called successfully before this func is called.
Return: whether the resource is successfully assigned or not. The return value
    does NOT indicate whether the work has been processed successfully or not.
    PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] resource_t *, the pointer to the resource. 
	[in] work_t *, the pointer to the work to be assigned to the resource.
*/
typedef __u32 (* pfunc_assign_t)( resource_t *, work_t * );

/* 
Func Type Name: pfunc_free_t
Description: free the resource.
Context: pfunc_create_t must be called successfully before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] resource_t *, the pointer to the resource. 
*/
typedef __u32 (* pfunc_free_t)( resource_t * );

/* 
Func Type Name: pfunc_isfree_t
Description: check whether the resource is free
Context: pfunc_create_t must be called successfully before this func is called.
Return: bTrue, it is free; bFalse, it is not free
Param:
	[in] resource_t *, the pointer to the resource. 
*/
typedef boolean_t (* pfunc_isfree_t)( resource_t * );

/* 
Func Type Name: pfunc_istimedout_t
Description: check whether the resource is timed out
Context: pfunc_create_t must be called successfully before this func is called.
Return: bTrue, timedout; bFalse, not timedout
Param:
	[in] resource_t *, the pointer to the resource.
	[in] __u32, the time out period 
*/
typedef boolean_t (* pfunc_istimedout_t)( resource_t *, __u32 );

/* --- functional routines ------------------------------------------------- */

#endif /*__PI_RESOURCE_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: resource.h,v $
 * Revision 1.2  2003/09/16 22:04:18  weny
 * make structure 8 byte aligned
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
