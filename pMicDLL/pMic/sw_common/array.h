/*******************************************************************************
 * Filename    : array.h
 * Description : basic array header file
 *               * the array element can be the pointer to any type of data
 *               * it supports basic arrar functions
 *                 - create, destroy
 *                 - getAt, removeAt, insertAt, append
 *                 - getSize, removeAll
 *               * it is NOT thread safe. The caller should provide synchronization
 *                 for the array if necessary
 * Created on  : 01/29/03
 * CVS Version : $Id: array.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2003
 * All Rights Reserved
 ******************************************************************************/

#ifndef __PI_ARRAY_H__
#define __PI_ARRAY_H__

/* --- standard C lib header files ----------------------------------------- */

/* --- internal header files ----------------------------------------------- */
#include "pibasic.h"

/* --- constant definitions ------------------------------------------------ */

/* --- data structures ----------------------------------------------------- */

typedef void basic_array_element_t;
typedef void basic_array_t;;

/* --- functional routines ------------------------------------------------- */

/* 
Func Name: createBasicArray
Description: create a basic array without elements
Context: None.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in/out] ppba, the array to be created and returned
*/
__u32 createBasicArray( basic_array_t ** ppba );

/* 
Func Name: destroyBasicArray
Description: destroy the basic array and release the resources
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in/out] ppba, the array to be destroyed. After destruction, it will be set to NULL.
*/
__u32 destroyBasicArray( basic_array_t ** ppba );

/* 
Func Name: getSizeBasicArray
Description: get the size - the number of elements - in the basic array
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
	[in/out] pu32Size, the size to be returned
*/
__u32 getSizeBasicArray( basic_array_t * pba, __u32 * pu32Size );

/* 
Func Name: getAtBasicArray
Description: get the array element at the given index
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
	[in] u32Index, the specified index
	[in/out] ppbae, the array element to be returned
*/
__u32 getAtBasicArray( basic_array_t * pba, __u32 u32Index, basic_array_element_t ** ppbae );

/* 
Func Name: removeAtBasicArray
Description: remove the element at the given index from the array.
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
	[in] u32Index, the specified index
*/
__u32 removeAtBasicArray( basic_array_t * pba, __u32 u32Index );

/* 
Func Name: removeElementBasicArray
Description: remove the element from the array. It will first search for the element
    in the array. If found, it will remove it from the array.
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
	[in] pbae, the element to be removed from the array
*/
__u32 removeElementBasicArray( basic_array_t * pba, basic_array_element_t * pbae );

/* 
Func Name: removeAllBasicArray
Description: remove all the elementsfrom the array.
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
*/
__u32 removeAllBasicArray( basic_array_t * pba );

/* 
Func Name: insertAtBasicArray
Description: insert the element at the given index to the array. 
    If the index is equal or bigger than the array size, the element will be
    appended to the end of the array. If the index is smaller than the array 
    size, the element will be inserted before the array element that is
	originally at the given index.
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
	[in] u32Index, the specified index
	[in] pbae, the element to be inserted
*/
__u32 insertAtBasicArray( basic_array_t * pba, __u32 u32Index, basic_array_element_t * pbae );

/* 
Func Name: appendBasicArray
Description: append the element to the end of the array. 
Context: creasteBasicArray should be called before this func is called.
Return: PIERR_NO_ERROR: succeed, otherwise: fail
Param:
	[in] pba, the array
	[in] pbae, the element to be appended
*/
__u32 appendBasicArray( basic_array_t * pba, basic_array_element_t * pbae );

#endif /*__PI_ARRAY_H__*/

/*******************************************************************************
 * Change Log
 *
 * $Log: array.h,v $
 * Revision 1.1  2003/03/06 01:17:06  weny
 * Phase1 debut
 *
 *
 ******************************************************************************/
