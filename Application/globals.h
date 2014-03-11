/*
 * globals.h
 *
 *  Created on: 7 févr. 2014
 *      Author: rpa
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <msp430.h>
#include <stdint.h>

//#define	NULL	0

/*
typedef unsigned short uint8_t;
typedef unsigned int uint16_t;
typedef short int8_t;
typedef int int16_t;
typedef unsigned long uint32_t;
typedef long int32_t;
*/

/*
 * Global variables
 */

/* System internal flags */
volatile s_system_flags sys;
/* Flags set by logic modules */
volatile s_request_flags request;
/* Messages flags */
volatile s_message_flags message;

/*
 * Global Functions
 */


// *************************************************************************************************
// @fn          to_lpm
// @brief       Go to LPM0/3. 
// @param       none
// @return      none
// *************************************************************************************************
void to_lpm(void)
{
	// Go to LPM3
	_BIS_SR(LPM3_bits + GIE); 
	__no_operation();
}

#endif /* GLOBALS_H_ */
