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

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

// *************************************************************************************************
// Include section
#include <project.h>


// *************************************************************************************************
// Prototypes section
extern void start_stopwatch(void);
extern void stop_stopwatch(void);
extern void reset_stopwatch(void);
extern void split_stopwatch(void);
extern unsigned char is_stopwatch_run(void);
extern unsigned char is_stopwatch_stop(void);
extern void stopwatch_tick(void);
extern void update_stopwatch_timer(void);
extern void mx_stopwatch(unsigned char line);
extern void sx_stopwatch(unsigned char line);
extern void display_stopwatch(unsigned char line, unsigned char update);


// *************************************************************************************************
// Defines section
#define STOPWATCH_1HZ_TICK			(32768/1)
#define STOPWATCH_100HZ_TICK		328 // PFS corrected(32768/100)
#define STOPWATCH_RESET				0x0
#define STOPWATCH_STOP				0x1
#define STOPWATCH_RUN				0x2
#define STOPWATCH_SPLIT				0x4 //no actual state but the bit that is active in both split states
#define STOPWATCH_SPLIT_STOP		0x5
#define STOPWATCH_SPLIT_RUN			0x6
#define STOPWATCH_HIDE				0x8





// *************************************************************************************************
// Global Variable section
struct stopwatch
{
	unsigned char 		state;
	unsigned char		drawFlag;
	unsigned char		swtIs1Hz;
	unsigned char		swtIs10Hz;
	
	//	time[0] 	hour H
	//	time[1] 	hour L
	//	time[2] 	minute H
	//	time[3] 	minute L
	//	time[4] 	second H
	//	time[5] 	second L
	//	time[6] 	1/10 sec 
	//	time[7] 	1/100 sec
	unsigned char		time[8]; //ASCII codes
	unsigned char		time_split[8];
	
	// Display style
	unsigned char 	viewStyle;
	unsigned char 	viewStyle_split;
};
extern struct stopwatch sStopwatch;


// *************************************************************************************************
// Extern section


#endif /*STOPWATCH_H_*/
