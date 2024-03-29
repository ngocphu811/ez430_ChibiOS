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


// *************************************************************************************************
// Include section


// *************************************************************************************************
// Prototypes section

// internal functions
extern void reset_alarm(void);
extern void stop_alarm(void);
extern void alarm_tick(void);

// menu functions
extern void sx_alarm(unsigned char line);
extern void mx_alarm(unsigned char line);
extern void display_alarm(unsigned char line, unsigned char update);


// *************************************************************************************************
// Defines section


// Keep alarm for 10 on-off cycles
#define ALARM_ON_DURATION	(10u)


// *************************************************************************************************
// Global Variable section
struct alarm
{
	union {
		struct {
			// one shot alarm
			unsigned char alarm:1;
			// hourly chime
			unsigned char chime:1;
		};
		unsigned char state:2;
	};
	// is alarm running?
	unsigned char running:1;
	// Alarm hour
	unsigned char hour:5;
	// Alarm minute
	unsigned char minute;
	// Alarm duration
	unsigned char duration;
};
extern struct alarm sAlarm;


// *************************************************************************************************
// Extern section

