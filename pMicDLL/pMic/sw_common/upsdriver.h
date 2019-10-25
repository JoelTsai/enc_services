#ifndef UPSDRIVER_H
#define UPSDRIVER_H

#include "upstypes.h"

#ifdef __cplusplus
extern "C" {
#endif
 
//extern u32 ups_open(UPSINFO *ups);

//extern u32 ups_close(UPSINFO *ups);

extern u32 ups_getUpsStatus(UPSINFO *ups);
extern u32 ups_open_and_init(UPSINFO *ups, u32 u32index);
extern u32 ups_close(UPSINFO *ups);
extern u32 ups_startUpsReconditioning(UPSINFO *ups);


#ifdef __cplusplus
}
#endif

#endif
/*******************************************************************************
 * Change Log
 *
 * $Log: upsdriver.h,v $
 * Revision 1.1.4.3  2009/05/19 03:49:51  xinw
 * add ups opened byte
 *
 * Revision 1.1.4.2  2009/03/23 12:24:20  xinw
 * add support ups
 *
 *
 ******************************************************************************/
