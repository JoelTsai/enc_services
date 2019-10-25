/*******************************************************************************
 * Filename    : respool.h
 * Description : resource pool header file
 *               * Resource pool is a pool some homogeneous resources, that can 
 *                 be statically or dynamically allocated and released.
 *               * The header file provides the external definition of resource
 *                 pool and the related routines. 
 * Created on  : 01/29/03
 * CVS Version : $Id: respool.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_RESOURCEPOOL_H__
#define __PI_RESOURCEPOOL_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"
#include "resource.h"
#include "errorlog.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */

typedef void resource_pool_t; /* to encapsulate the logic inside resource pool itself */

typedef struct
{
#ifndef SINGLE_ERROR_HANDLER
    error_handler_t * rpp_pehErrorHandler;
#endif
    __u8 * rpp_pu8ResourcePoolName;/* a pointer to a 0 (zero) ended ASCII string.
                                      It should be no longer than 7 characters */
	__u32 rpp_u32ResourceTypeId;   /* the type id of the resources in the pool */
	__u32 rpp_u32MinResources; /* minimum number of resources that should be 
	                              allocated all the time */
	__u32 rpp_u32MaxResources; /* maximum number of resources that can co-exist
	                              at the same time */
	__u32 rpp_u32Timeout;      /* the timeout period of an idle resource that
	                              is dynamically created. If it is 0 (zero), 
								  the resource should be released immediately
								  after use */
    boolean_t rpp_bImmediateRelease; /* if immediate relase is set to true, 
                                        timeout period will be ignored */
	                           /* enable the internal resource collector to
							      release the timed-out idle resources */
	/* the resource pool will call the following function to
	   create, reserve, assign, free and destroy a resource */
	pfunc_create_t rpp_pfCreate;
	pfunc_reserve_t rpp_pfReserve;
	pfunc_assign_t rpp_pfAssign;
	pfunc_free_t rpp_pfFree;
	pfunc_destroy_t rpp_pfDestroy;
	pfunc_isfree_t rpp_pfIsFree;
	pfunc_istimedout_t rpp_pfIsTimedout;
	__u32 rpp_u32ParamLength;      /* the number of bytes of rpp_u8ExtendedResourceParam */
	__u8 rpp_u8ExtendedResourceParam[MAX_EXTENDED_PARAM_LENGTH];  /* the parameters of the resource */
} resource_pool_param_t;

/* --- functional routines ------------------------------------------------- */

/* 
Func Name: createResourcePool
Description: create a resource pool according to the parameters.
Context: None.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in/out] pprp, the pointer to the resource pool to be created and returned.
	[in] prpp, the parameters of the resource pool.
*/
__u32 createResourcePool( resource_pool_t ** pprp, resource_pool_param_t * prpp );

/* 
Func Name: destroyResourcePool
Description: destroy the resource pool.
Context: createResourcePool must be called successfully before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in/out] pprp, the pointer to the resource pool to be destroyed. 
	    After destruction, it will be set to NULL.
*/
__u32 destroyResourcePool( resource_pool_t ** pprp );

/* 
Func Name: assignWorkToResource
Description: assign a work to a resource of the resource pool. The resource pool
    will look for a free resource and assign the work to it. And the resource will
    handle the work. It is up to the implementation of the resource to complete the
    work in this function all, or complete it asynchronously.
Context: createResourcePool must be called successfully before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] prp, the pointer to the resource pool. 
	[in] pw, the pointer to the work to be assigned.
*/
__u32 assignWorkToResource( resource_pool_t * prp, work_t * pw );

/* 
Func Name: collectResource
Description: collect the resource that has timed out, and release them. It is not
    necessary to call this function explicitly when the internal collector is enabled.
Context: createResourcePool must be called successfully before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] prp, the pointer to the resource pool. 
*/
__u32 collectResource( resource_pool_t * prp );

#endif /*__PI_RESOURCEPOOL_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: respool.h,v $
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
