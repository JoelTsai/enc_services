/*******************************************************************************
 * Filename    : event.h
 * Description : Event header file
 *               It provides the constant definitions, data structures and
 *               related functional routines.
 * Created on  : 01/28/03
 * CVS Version : $Id: event.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_EVENT_H__
#define __PI_EVENT_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- constant definitions ------------------------------------------------ */

/* event id - to be done */
/*
#define EVENT_SW 1000

#define EVENT_SW_SHUTDOWN          (EVENT_SW + 0)
#define EVENT_SW_DEBUG             (EVENT_SW + 1)
*/

/* --- data structures ----------------------------------------------------- */

#define EVENT_MASK_NONE 0

#define EVENT_MASK_ALL(type) (~((type)EVENT_MASK_NONE))

#define ADD_EVENT_MASK(type, shift, mask) \
	(((shift) == 0)?((type)(mask) | (type)0x1):((type)(mask) | ((type)0x1 << (type)(shift))))

#define SET_EVENT_MASK(type, shift) \
	(((shift) == 0)?(~((type)EVENT_MASK_NONE)):((~((type)EVENT_MASK_NONE)) << (type)(shift))) /*filter all events with low priority according to shift value*/

#define REMOVE_EVENT_MASK(type, shift, mask) \
	(((shift) == 0)?((type)(mask) & (~((type)0x1))):((type)(mask) & (~((type)0x1 << (type)(shift)))))

#define COMBINE_EVENT_MASK(type, mask1, mask2)  ((type)(mask1) | (type)(mask2))

#define IS_EVENT_MASKED(type, shift, mask) \
	(boolean_t)(((shift) == 0)?(((type)(mask) & (type)0x1) != EVENT_MASK_NONE):\
		(((type)(mask) & ((type)0x1 << (type)(shift))) != EVENT_MASK_NONE))

#define IS_SUB_EVENT_MASK(type, submask, mask) \
	(((type)(mask) & (type)(submask)) == (type)(submask))

#define HAS_COMMON_EVENT_MASK(type, mask1, mask2) \
	((boolean_t)(((type)(mask1) & (type)(mask2)) != EVENT_MASK_NONE))

#ifdef UNIX
typedef u32 event_subscriber_t;  /* the process id of the subscriber */
#else
typedef u32 event_subscriber_t;  /* TBD for Windows */
#endif
 
typedef struct
{
    event_subscriber_t es_esSubscriber;
    u32 es_u32SeverityMask;
    u64 es_u64ClassMask;
} event_subscription_t;

/* --- functional routines ------------------------------------------------- */

/*
 * Commened by Wen Y.
 * Class mask became u64, use the macro definitions instead of the following functions
 */
/*
u32 addEventMask(u32 u32Shift, u32 u32Mask);

u32 removeEventMask(u32 u32Shift, u32 u32Mask);

u32 combineEventMask(u32 u32Mask1, u32 u32Mask2);

boolean_t isEventMasked(u32 u32Shift, u32 u32Mask);

boolean_t isSubEventMask(u32 u32SubMask, u32 u32Mask);

boolean_t hasCommonEventMask(u32 u32Mask1, u32 u32Mask2);
*/

void combineEventSubscription(event_subscription_t * pInOut, const event_subscription_t *pIn);

void copyEventSubscription(event_subscription_t * pOut, const event_subscription_t *pIn);

#endif /*__PI_EVENT_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: event.h,v $
 * Revision 1.4  2007/07/24 18:13:35  JudithLi
 * Event Notification in-band support
 *
 * Revision 1.3  2003/06/16 22:09:05  weny
 * change event class mask from u32 to u64
 *
 * Revision 1.2  2003/05/17 03:03:20  weny
 * Rewrite for I2 Event Notification
 *
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
