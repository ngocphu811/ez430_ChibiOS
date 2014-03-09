// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//	 
//	 
//	  Redistribution and use in source and binary forms, with or without 
//	  modification, are permitted provided that the following conditions 
//	  are met:
//	
//	    Redistributions of source code must retain the above copyright 
//	    notice, this list of conditions and the following disclaimer.
//	 
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the 
//	    documentation and/or other materials provided with the   
//	    distribution.
//	 
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//	
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************

#ifndef CLOCKTIMER_H_
#define CLOCKTIMER_H_

// *************************************************************************************************
// Defines section

// Definitions for time format
#define TIMEFORMAT_24H					(0u)
#define TIMEFORMAT_12H					(1u)

// *************************************************************************************************
// Prototypes section
extern void reset_clock(void);
extern void sx_time(unsigned char line);
extern void mx_time(unsigned char line);
extern void clock_tick(void);
extern void display_selection_Timeformat1(unsigned char segments, unsigned long index, unsigned char digits, unsigned char blanks, unsigned char dummy);
extern void display_time(unsigned char line, unsigned char update);

// English units support
extern unsigned char convert_hour_to_12H_format(unsigned char hour);
extern unsigned char is_hour_am(unsigned char hour);


// *************************************************************************************************
// Global Variable section
struct time
{
	unsigned long 	system_time;

	// Flag to minimize display updates
	unsigned char 		drawFlag;

	// Viewing style
	unsigned char		line1ViewStyle;
	unsigned char		line2ViewStyle;
	
	// Time data
	unsigned char		hour;
	unsigned char		minute;
	unsigned char 		second;
	
	// Inactivity detection (exits set_value() function)
	unsigned long 	last_activity;
	#ifdef CONFIG_SIDEREAL
	// offset of local time from UTC (=1: set time is UTC+1 =CET)
	s8		UTCoffset;
	#endif
};
extern struct time sTime;


#endif /*CLOCKTIMER_H_*/
