/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    MSP430/hal_lld.c
 * @brief   MSP430 HAL subsystem low level driver source.
 *
 * @addtogroup HAL
 * @{
 */

#include "ch.h"
#include "hal.h"

/*===========================================================================*/
/* Driver exported variables.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local variables and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

/*===========================================================================*/
/* Driver interrupt handlers.                                                */
/*===========================================================================*/

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

/**
 * @brief   Low level HAL driver initialization.
 *
 * @notapi
 */
void hal_lld_init(void) {

  /*
  /* RTC initially stopped.*//*
  WDTCTL = 0x5A80;

  /* Clock sources setup.*//*
  DCOCTL  = VAL_DCOCTL;
  BCSCTL1 = VAL_BCSCTL1;
#if MSP430_USE_CLOCK == MSP430_CLOCK_SOURCE_XT2CLK
  do {
    int i;
    IFG1 &= ~OFIFG;
     for (i = 255; i > 0; i--)
       asm("nop");
  } while (IFG1 & OFIFG);
#endif
  BCSCTL2 = VAL_BCSCTL2;
  */
  	//taskDISABLE_INTERRUPTS();

/* Disable the watchdog. */
WDTCTL = WDTPW + WDTHOLD;
  
// ---------------------------------------------------------------------
// Configure PMM
//SetVCore(3);					///<<<<<<<<<<<<<<<<<<<<<

// Set global high power request enable
PMMCTL0_H = 0xA5;
PMMCTL0_L |= PMMHPMRE;
PMMCTL0_H = 0x00;

// ---------------------------------------------------------------------
// Enable 32kHz ACLK
P5SEL |= 0x03; // Select XIN, XOUT on P5.0 and P5.1
UCSCTL6 &= ~XT1OFF; // XT1 On, Highest drive strength
UCSCTL6 |= XCAP_3; // Internal load cap

UCSCTL3 = SELA__XT1CLK; // Select XT1 as FLL reference
UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV | SELM__DCOCLKDIV;

// ---------------------------------------------------------------------
// Configure CPU clock for 12MHz
_BIS_SR(SCG0); // Disable the FLL control loop
UCSCTL0 = 0x0000; // Set lowest possible DCOx, MODx
UCSCTL1 = DCORSEL_5; // Select suitable range
UCSCTL2 = FLLD_1 + 0x16E; // Set DCO Multiplier
_BIC_SR(SCG0); // Enable the FLL control loop

// Worst-case settling time for the DCO when the DCO range bits have been
// changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
// UG for optimization.
// 32 x 32 x 8 MHz / 32,768 Hz = 250000 = MCLK cycles for DCO to settle
__delay_cycles(250000);

// Loop until XT1 & DCO stabilizes, use do-while to insure that
// body is executed at least once
do
{
UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
SFRIFG1 &= ~OFIFG; // Clear fault flags
} while ((SFRIFG1 & OFIFG));


}

/** @} */
