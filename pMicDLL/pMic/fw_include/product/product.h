#ifndef __PRODUCT_H
#define __PRODUCT_H

#ifdef ISLAVISTA
#include "islavista.h"
#endif

#if defined(HW_YOSEMITE)
#include "yosemite.h"
#endif

//Code Review For Single Image PTT 2006,0315
#if defined (PROM_HW_SHASTA_HBA)
#include "shasta.h"
#endif

#ifdef SCLASS
#include "sclass.h"
#endif

#ifdef CX20Y
#include "cx20y_products.h"
#endif

#ifdef SMARTSTOR
#include "smartstor_products.h"
#endif

#ifdef VESS2K
#include "vess2k_products.h"
#endif

#endif /*__PRODUCT_H */
