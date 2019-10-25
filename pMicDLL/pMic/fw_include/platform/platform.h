#ifndef _PLATFORM_H_
#define _PLATFORM_H_

/*******************************************************************************
 *
 * Filename    : platform.h
 * Description :
 * Created on  : 11/23/2004
 * CVS Version :
 *
 * (C) Copyright Promise Technology Inc., 2002-2005
 * All Rights Reserved
 *
 ******************************************************************************/

#if defined(HW_IRVINE)
#include "irvine_hw.h"
#elif defined(HW_ISLAVISTA)
#include "islavista_hw.h"
//Code Review For Single Image PTT 2006,0315
#elif defined(PROM_HW_SHASTA_HBA)
#include "shasta_hw.h"
#elif defined(HW_YOSEMITE)
#include "yosemite_hw.h"
#elif defined(HW_X86)
#include "x86_hw.h"
#elif defined(SCLASS)
#include "sclass_hw.h"
#elif defined(CX20Y)
#include "cx20y_hw.h"
#elif defined(SMARTSTOR)
#include "smartstor_hw.h"
#elif defined(VESS2K)
#include "vess2k_hw.h"
#else
#error Platform not defined !. For defining platform, refer to defines HW_ISLAVISTA.
#endif


#endif /* _PLATFORM_H_ */


