/***************************************************************
 *
 * Filename    : cpld.h
 * Description :  All CPLD register access to go through this file.
 * Created on  :  2006/06/12
 * CVS Version : $Id: cpld.h 117 2010-05-06 10:01:05Z spoca.huang $
 *
 * (C) Copyright Promise Technology Inc., 2002-2003
 * All Rights Reserved
 *
 ****************************************************************/
#ifndef _CPLD_H_
#define _CPLD_H_

#if defined(HW_ISLAVISTA) || defined(HW_E310) || defined(HW_CBAY) || defined(HW_CX20Y) || defined(CX20Y)


#ifdef CPLDDBG
#define CPLD_DBG_PRINT(fmt, args...) prom_printk(fmt, args);
#else
#define CPLD_DBG_PRINT(fmt, args...)
#endif


static inline
int check_frontend_for_sas (void)
{
#define CPLD_CLASS_OFF (0xF)
    u8 cpld_reg;
    cpld_reg = *(u8*) (PROM_CPLD_VIRTUAL_ADDRESS+CPLD_CLASS_OFF);

    CPLD_DBG_PRINT("cpld_reg value: 0x%x\n", cpld_reg);

    /* yes - e310s shouldnt this be 0x15? */
    /* clearbay is also sas frontend */
    return ((cpld_reg == 0x11) || (cpld_reg == 0x19)); 
}

static inline
int check_frontend_for_fc (void)
{
#define CPLD_CLASS_OFF (0xF)
    u8 cpld_reg;
    cpld_reg = *(u8*) (PROM_CPLD_VIRTUAL_ADDRESS+CPLD_CLASS_OFF);

    CPLD_DBG_PRINT("cpld_reg value: 0x%x\n", cpld_reg);

    return ((cpld_reg == 0x10) || (cpld_reg == 0x14)); /* yes - e310f|e300f */
}

static inline
int peer_ctrl_available (void)
{
#if defined(CX20Y)
    return (0);
#else
    extern u32 cctlPeerCtrlState;
    return (cctlPeerCtrlState == CCTL_PEER_CONTROLLER_UP);
#endif
}

static inline
int get_controller_slot_num (void)
{
#define CPLD_SLOT_OFF (0x3)
    u8 cpld_reg;

    cpld_reg =  *(u8*)(PROM_CPLD_VIRTUAL_ADDRESS+CPLD_SLOT_OFF);
    return (cpld_reg & 0x20 ? 1 : 0);
}

static inline
int get_peer_controller_slot_num (void)
{
    u8 cpld_reg;

    cpld_reg =  *(u8*)(PROM_CPLD_VIRTUAL_ADDRESS+CPLD_SLOT_OFF);
    return (cpld_reg & 0x20 ? 0 : 1); /* reversed */
}


static inline
int daughter_expander_installed (void)
{
    u8 cpld_reg;

    cpld_reg =  *(u8*)(PROM_CPLD_VIRTUAL_ADDRESS+CPLD_SLOT_OFF);
    return (cpld_reg & 0x80 ? 0 : 1);
}

static inline
int get_nr_of_expanders (void)
{
    return (daughter_expander_installed() ? 2 : 1);
}

static inline
int get_nr_of_ports (void)
{
    /* check for daughter card installed? */
    if (daughter_expander_installed()) {
        return 4;
    }
    return 2;
}

static inline
int get_nr_of_controllers (void)
{
    /* check for other controller presence */
    if (peer_ctrl_available()) return 2;

    return 1;
}

static inline
int get_board_revision (void)
{
    u8 cpld_reg;
    cpld_reg = *(u8*) (PROM_CPLD_VIRTUAL_ADDRESS);

    return ( ((cpld_reg & 0xf0) >> 4));
}

static inline
u8 ResetPromController (void)
{
   u8 *CPLDPtr = NULL;

   //CPLDPtr = (u8 *) ioremap (PROM_CPLD_BASE_ADDR, 8);
   CPLDPtr = (u8*) (PROM_CPLD_VIRTUAL_ADDRESS + 7);

   *CPLDPtr = 0x1;

   while (1); //No where to go
   return 0;
}

static inline 
void ResetZoningExpander (void)
{
#ifdef HW_CBAY
    volatile u8 *CPLDPtr = (u8*) (PROM_CPLD_VIRTUAL_ADDRESS + 9);
    volatile int i;
    *CPLDPtr |= 0x4;
    for (i=0; i<100000; i++);
    *CPLDPtr &= ~0x4;
#else
  /* do nothing */
#endif
}

static inline 
void ResetInterposerExpander (void)
{
#ifdef HW_CBAY
    volatile u8 *CPLDPtr = (u8*) (PROM_CPLD_VIRTUAL_ADDRESS + 9);
    volatile int i;
    *CPLDPtr |= 0x8;
    for (i=0; i<100000; i++);
    *CPLDPtr &= ~0x8;
#else
  /* do nothing */
#endif
}

#endif /* known supported platform */

#endif /* _CPLD_H_ */
/***************************************************************
 * Change Log
 *
 * $Log: cpld.h,v $
 * Revision 1.1.4.3  2008/09/17 03:24:06  quennel.liu
 * Sas front-end mic support - login initiators
 *
 * Revision 1.1.4.2  2008/08/21 02:58:19  willy.lin
 * no message
 *
 * Revision 1.1.2.1  2007/07/20 18:34:25  randallc
 * Moved headers files to new directory because of licensing issues and to
 * allow for easier distribution of each module as an individual piece.
 *
 * Revision 1.1.2.14  2007/07/03 22:40:45  lakshmi.s
 * GPL related changes. replace printk() support with timestamp from kernel to use prom_printk() defined within fw. remove crash collection for clearbay
 *
 * Revision 1.1.2.13  2007/04/27 17:46:30  lakshmi.s
 * Provide proc interface to reboot interposer
 *
 * Revision 1.1.2.12  2007/04/19 21:52:45  lakshmi.s
 * remove mdelay and include volatile and a dummy loop
 *
 * Revision 1.1.2.11  2007/04/17 21:33:43  lakshmi.s
 * CPLD update for ResetExpander interface useful only on clearbay, Fab3 board
 *
 * Revision 1.1.2.10  2007/03/29 21:41:41  lakshmi.s
 * ZNG: new mics and events on zoning path
 *
 * Revision 1.1.2.9  2007/02/07 19:44:33  lakshmi.s
 * source cleanup for GPL release
 *
 * Revision 1.1.2.8  2006/11/30 01:53:26  lakshmi.s
 * update check for sas frontend - include clearbay too
 *
 * Revision 1.1.2.7  2006/09/25 21:56:27  lakshmi.s
 * added header and conditionally printed debugs
 *
 *
 ****************************************************************/
