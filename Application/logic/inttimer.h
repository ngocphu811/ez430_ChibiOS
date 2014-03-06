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

#ifndef inttimer_H_
#define inttimer_H_

// *************************************************************************************************
// Include section
#include <project.h>

// *************************************************************************************************
// Prototypes section
extern void init_inttimer(void);
extern void start_inttimer(void);
extern void stop_inttimer(void);
extern void stop_inttimer_alarm(void);
extern void set_inttimer_to_defaults(void);
extern void set_inttimer(void);
extern void inttimer_tick(void);
extern void mx_inttimer(u8 line);
extern void sx_inttimer(u8 line);
extern void display_inttimer(u8 line, u8 update);
extern u8 inttimer_visible(void);


// *************************************************************************************************
// Defines section
#define INTTIMER_STOP_ON			(0u)
#define INTTIMER_RUN_ON 			(1u)
#define INTTIMER_STOP_OFF           (2u)
#define INTTIMER_RUN_OFF            (3u)
#define INTTIMER_STOP_REST       	(4u)
#define INTTIMER_RUN_REST       	(5u)
#define INTTIMER_ALARM              (6u)

#define INTTIMER_ALARM_DURATION			(4u)

// *************************************************************************************************
// Global Variable section
struct inttimer
{
        //NOTE: u8 means unsigned char
	u8	state;
	u8	drawFlag;
	
	// Values that are decremented each second
	u8	minutes;
	u8	seconds;
    u8  workIs;
    u8  workBs;
	
	// length of "on" interval
	u8	def_on_minutes;
	u8	def_on_seconds;
    // length of "off" interval
	u8	def_off_minutes;
	u8	def_off_seconds;
    // length of "rest" interval
	u8	def_rest_minutes;
	u8	def_rest_seconds;
    // number of intervals per block, blocks per workout
    u8 def_workIs;
    u8 def_workBs;
    //Number of times to request buzzer double-beep when time is up	
	u8	duration;
};
extern struct inttimer sInttimer;


// *************************************************************************************************
// Extern section

#endif /*inttimer_H_*/
