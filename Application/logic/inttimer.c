// inttimer - interval timer adapted from the eggtimer that
// comes with OpenChronos
// by Riad Wahby <rsw@jfet.org>
//
// original GPL notice from eggtimer.c
/*
	 Copyright (C) 2011 Angelo Arrifano <miknix@gmail.com>
	   - Updated to use new improved timer0 API

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//
//
// Original copyright notice from eggtimer.c
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
// Inttimer feature
// *************************************************************************************************

// *************************************************************************************************
// Include section

// system
#include "config.h"	//gibbons: bit of a hack: forces next ifdef statement to work
#ifdef CONFIG_INTTIMER

#include "project.h"

#include <string.h>

// driver
#include "inttimer.h"
#include "ports.h"
#include "display.h"
#include "timer.h"
#include "buzzer.h"
#include "user.h"

// logic
#include "menu.h"
#include "inttimer.h"


// *************************************************************************************************
// Prototypes section
void init_inttimer(void);
void start_inttimer(void);
void stop_inttimer(void);
void stop_inttimer_alarm(void);
void set_inttimer_to_defaults(void);
//void set_inttimer(void);
void inttimer_tick(void);
void mx_inttimer(u8 line);
void sx_inttimer(u8 line);
void display_inttimer(u8 line, u8 update);
u8 inttimer_visible(void);

// *************************************************************************************************
// Defines section


// *************************************************************************************************
// Global Variable section
struct inttimer sInttimer;


// *************************************************************************************************
// Extern section
extern void menu_skip_next(line_t line); // in ezchronos.c


// *************************************************************************************************
// @fn          init_inttimer
// @brief       Initialize inttimer; intended to be called once, on firmware restart
// @param       none
// @return      none
// *************************************************************************************************
void init_inttimer()
{
    sInttimer.state = INTTIMER_STOP_REST;
    sInttimer.duration = INTTIMER_ALARM_DURATION;
    
    // Set int timer defaults
    sInttimer.def_on_minutes = 0;
    sInttimer.def_on_seconds = 30;
    sInttimer.def_off_minutes = 0;
    sInttimer.def_off_seconds = 10;
    sInttimer.def_rest_minutes = 2;
    sInttimer.def_rest_seconds = 0;
    sInttimer.def_workIs = 12;
    sInttimer.def_workBs = 3;
    
    set_inttimer_to_defaults();
}


// *************************************************************************************************
// @fn          start_inttimer
// @brief       Sets inttimer state to on, draws inttimer icon blinking
// @param       none
// @return      none
// *************************************************************************************************
void start_inttimer(void)
{
    if (sInttimer.state & 1) {
        // odd state value means the timer is already running
        return;
    } else {
	    // change to the running state corresponding to present stop state
	    sInttimer.state ^= 1;
    }

	// Set inttimer icon (doesn't exist so I wont untill I'll use stopwatch for now)
	display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_ON);

	Timer0_A1_Register(inttimer_tick);
}


// *************************************************************************************************
// @fn          stop_inttimer
// @brief       Sets inttimer state to off, but doesn't reset inttimer count. 
//		  Also draws inttimer icon (solid on, no blink)
// @param       none
// @return      none
// *************************************************************************************************
void stop_inttimer(void)
{	
    if (sInttimer.state & 1) { 
        // odd state means timer is running
        sInttimer.state ^= 1;

	    // Clear inttimer icon (doesn't exist so I'll use stopwatch for now)
	    display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_OFF); // Assumes the inttimer menu is active
	    Timer0_A1_Unregister(inttimer_tick);
    }
}


// *************************************************************************************************
// @fn          stop_inttimer_alarm
// @brief       Puts inttimer in STOP mode, halts alarm mode and buzzing if active, updates inttimer
//			symbol. Safe to call, even if inttimer menu not active.
// @param       none
// @return      none
// *************************************************************************************************
void stop_inttimer_alarm(void)
{
	// We dont need the timer active anymore
	Timer0_A1_Unregister(inttimer_tick);

	sInttimer.state = INTTIMER_STOP_REST;
	sInttimer.duration = INTTIMER_ALARM_DURATION;

	if (inttimer_visible()) {
		display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_OFF);
	}
	else {
		display_symbol(LCD_ICON_RECORD, SEG_OFF_BLINK_OFF);
	}
	stop_buzzer(); // FIXME: needs to play friendly with other buzzer-using modules (e.g. alarm)
}


// *************************************************************************************************
// @fn          set_inttimer_to_defaults
// @brief       Clears inttimer counter, resets inttimer state
// @param       none
// @return      none
// *************************************************************************************************
void set_inttimer_to_defaults(void)
{
	// reset to stop, set rest interval time
    sInttimer.state = INTTIMER_STOP_REST;
	sInttimer.minutes = sInttimer.def_rest_minutes;
	sInttimer.seconds = sInttimer.def_rest_seconds;
    sInttimer.workIs = sInttimer.def_workIs;
    sInttimer.workBs = sInttimer.def_workBs;
	
	if (inttimer_visible()) {
		display.flag.line2_full_update = 1; // gibbons: this is hardcoded to line 2; change?
	}
}


// *************************************************************************************************
// @fn          set_inttimer
// @brief       Sets the inttimer variables.
// @param       none
// @return      none
// *************************************************************************************************
void set_inttimer(void){

    u8 select = 0;
    // need to be s32s to work with set_value
    s32 def_workIs = sInttimer.def_workIs;
    s32 def_workBs = sInttimer.def_workBs;
    s32 def_rmin = sInttimer.def_rest_minutes;
    s32 def_rsec = sInttimer.def_rest_seconds;
    s32 def_fmin = sInttimer.def_off_minutes;
    s32 def_fsec = sInttimer.def_off_seconds;
    s32 def_omin = sInttimer.def_on_minutes;
    s32 def_osec = sInttimer.def_on_seconds;
    u8 * str;

    // clear display so we can use both lines
    clear_display();

	// Loop values until all are set or user breaks set
	while(1) 
	{
		// Idle timeout: exit without saving 
		if (sys.flag.idle_timeout) break;
		
		// M2 (short): save, then exit 
		if (button.flag.num) 
		{
            // prevent zero time for all timers
			if ((def_rmin == 0) && (def_rsec == 0)) def_rsec = 1;
			if ((def_fmin == 0) && (def_fsec == 0)) def_fsec = 1;
			if ((def_omin == 0) && (def_osec == 0)) def_osec = 1;
            if (def_workIs == 0) def_workIs = 1;
            if (def_workBs == 0) def_workBs = 1;

			// Store local variables in global Eggtimer default and counters
            sInttimer.def_on_minutes = def_omin;
            sInttimer.def_on_seconds = def_osec;
            sInttimer.def_off_minutes = def_fmin;
            sInttimer.def_off_seconds = def_fsec;
            sInttimer.def_rest_minutes = def_rmin;
            sInttimer.def_rest_seconds = def_rsec;
            sInttimer.def_workIs = def_workIs;
            sInttimer.def_workBs = def_workBs;
			break;
		}

		switch (select)
		{
			case 0: // set work blocks
                display_chars(LCD_SEG_L1_3_0, (u8 *) "BLKS", SEG_ON);
                clear_line(LINE2);
			    set_value(&def_workBs, 2, 0, 1, 19, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_2, display_value1);
			    select++; // increment
			    break;

			case 1:	// set work intervals per block
                display_chars(LCD_SEG_L1_3_0, (u8 *) "INTV", SEG_ON);
			    set_value(&def_workIs, 2, 0, 1, 99, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_2, display_value1);
			    select++;
			    break;
                                        
            case 2:	// set rest timer minutes
                display_chars(LCD_SEG_L1_3_0, (u8 *) "REST", SEG_ON);
                str = _itoa(def_rsec, 2, 0);
                display_chars(LCD_SEG_L2_1_0, str, SEG_ON); // show seconds
		        display_symbol(LCD_SEG_L2_COL0, SEG_ON);    // show colon
			    set_value(&def_rmin, 2, 0, 0, 99, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_2, display_value1);
			    select++;
			    break;

            case 3: // set rest timer seconds
                set_value(&def_rsec, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_1_0, display_value1);
                select++;
                break;

            case 4: // set work-on minutes
                display_chars(LCD_SEG_L1_3_0, (u8 *) "W ON", SEG_ON);
                str = _itoa(def_osec, 2, 0);
                display_chars(LCD_SEG_L2_1_0, str, SEG_ON); // show seconds; colon is already on
			    set_value(&def_omin, 2, 0, 0, 99, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_2, display_value1);
                select++;
                break;

            case 5: // set work-on seconds
                set_value(&def_osec, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_1_0, display_value1);
                select++;
                break;

            case 6: // set work-off minutes
                display_chars(LCD_SEG_L1_2_0, (u8 *) "OFF", SEG_ON);
                str = _itoa(def_fsec, 2, 0);
                display_chars(LCD_SEG_L2_1_0, str, SEG_ON); // show seconds; colon is already on
			    set_value(&def_fmin, 2, 0, 0, 99, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_3_2, display_value1);
                select++;
                break;

            case 7: // set work-off seconds
                set_value(&def_fsec, 2, 0, 0, 59, SETVALUE_ROLLOVER_VALUE + SETVALUE_DISPLAY_VALUE + SETVALUE_NEXT_VALUE, LCD_SEG_L2_1_0, display_value1);
                select = 0;
                break;

		}
	}
	
	// Clear button flag
	button.all_flags = 0;
	
}

// *************************************************************************************************
// @fn          inttimer_tick
// @brief       To be called every second; decreases inttimer counter and sets display update flag.
// @param       none
// @return      none
// *************************************************************************************************
void inttimer_tick(void)
{

    sInttimer.drawFlag = 1;
    display.flag.update_inttimer = 1;

    if (sInttimer.state == INTTIMER_RUN_ON) {

        if ((sInttimer.minutes == 0) && (sInttimer.seconds == 1)) {
            // done with this on interval; update state to off interval
            sInttimer.state = INTTIMER_RUN_OFF;
            sInttimer.minutes = sInttimer.def_off_minutes;
            sInttimer.seconds = sInttimer.def_off_seconds;
            sInttimer.drawFlag = 3;
            request.flag.inttimer_buzzer_off = 1;
        } else if (sInttimer.seconds-- == 0) { // decrement seconds, decrement min if necessary
            sInttimer.seconds = 59;
            sInttimer.drawFlag++;
            sInttimer.minutes--;
        }

    } else if (sInttimer.state == INTTIMER_RUN_OFF) {

        if ((sInttimer.minutes == 0) && (sInttimer.seconds == 1)) {
            // done with this off interval; decide where to go
            if (sInttimer.workIs-- == 1) {
                // done with this block; go to a rest interval
                sInttimer.workIs = sInttimer.def_workIs;
                sInttimer.state = INTTIMER_RUN_REST;
                sInttimer.minutes = sInttimer.def_rest_minutes;
                sInttimer.seconds = sInttimer.def_rest_seconds;
                sInttimer.drawFlag = 3;
            } else {
                // next work interval
                sInttimer.state = INTTIMER_RUN_ON;
                sInttimer.minutes = sInttimer.def_on_minutes;
                sInttimer.seconds = sInttimer.def_on_seconds;
                sInttimer.drawFlag = 3;
                request.flag.inttimer_buzzer_on = 1;
            }
        } else if (sInttimer.seconds-- == 0) {
            sInttimer.seconds = 59;
            sInttimer.drawFlag++;
            sInttimer.minutes--;
        }
    
    } else if (sInttimer.state == INTTIMER_RUN_REST) {

        if ((sInttimer.minutes == 0) && (sInttimer.seconds == 1)) {
            // done with this rest interval; do we continue or finish?
            if (sInttimer.workBs-- == 0) {
                // done!
                sInttimer.state = INTTIMER_ALARM;
            } else {
                // next work interval
                sInttimer.state = INTTIMER_RUN_ON;
                sInttimer.minutes = sInttimer.def_on_minutes;
                sInttimer.seconds = sInttimer.def_on_seconds;
                sInttimer.workIs = sInttimer.def_workIs;
                sInttimer.drawFlag = 3;
                request.flag.inttimer_buzzer_on = 1;
            }
        } else if (sInttimer.seconds-- == 0) {
            sInttimer.seconds = 59;
            sInttimer.drawFlag++;
            sInttimer.minutes--;
        }

    }
                
 	if (sInttimer.state == INTTIMER_ALARM) {
		// Decrement alarm duration counter
		if (sInttimer.duration-- > 0)
		{
			request.flag.inttimer_buzzer_off = 1;
		}
		else
		{
			stop_inttimer_alarm(); // Set state to Stop and reset duration
            set_inttimer_to_defaults(); // reset timer
		}
	}
}


// *************************************************************************************************
// @fn          mx_inttimer
// @brief       inttimer set routine. Mx stops inttimer and resets count.
// @param       u8 line	LINE2
// @return      none
// *************************************************************************************************
void mx_inttimer(u8 line)
{
	// Stop inttimer
	stop_inttimer();

    // if the timer is already reset, go into setup mode
    // otherwise just reset the timer to present defaults
    if ( (sInttimer.state == INTTIMER_STOP_REST) &&
         (sInttimer.minutes == sInttimer.def_rest_minutes) &&
         (sInttimer.seconds == sInttimer.def_rest_seconds) ) {
        set_inttimer();
    }

	set_inttimer_to_defaults();
	
	// Display inttimer time
	display_inttimer(line, DISPLAY_LINE_UPDATE_FULL);
}


// *************************************************************************************************
// @fn          sx_inttimer
// @brief       inttimer direct function. S2 starts/stops inttimer, but does not reset count.
// @param       u8 line	LINE2
// @return      none
// *************************************************************************************************
void sx_inttimer(u8 line)
{
	if (sInttimer.state & 1)
	{
		// stop
		stop_inttimer();
	}
	else 
	{
		// start
		start_inttimer();
	}
}


// *************************************************************************************************
// @fn          display_inttimer
// @brief       inttimer user routine.
// @param       u8 line		LINE2
//		u8 update	DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_UPDATE_FULL
// @return      none
// *************************************************************************************************
void display_inttimer(u8 line, u8 update)
{
	u8 * str;

    if (update == DISPLAY_LINE_UPDATE_FULL) {
        sInttimer.drawFlag = 3;
   		
		display_symbol(LCD_SEG_L2_COL1, SEG_OFF);
		display_symbol(LCD_SEG_L2_COL0, SEG_ON);
		
		if (sInttimer.state & 1) { // Blink if running or alarm triggered
			display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_ON);
		}
		else { // Solid on if not running
			display_symbol(LCD_ICON_RECORD, SEG_ON_BLINK_OFF);
		}
    }

	if (update == DISPLAY_LINE_CLEAR) {
		// Stop blinking icon only if inttimer isn't running
		if (!(sInttimer.state & 1)) display_symbol(LCD_ICON_RECORD, SEG_OFF);
	} else {
	    // Partial line update only
		// Check draw flag to minimize workload
		switch(sInttimer.drawFlag) 
		{
		    case 3: // update init flag
                if (sInttimer.state < 2) {
                    display_chars(LCD_SEG_L2_5_4, (u8 *) " W", SEG_ON);
                } else if (sInttimer.state < 4) {
                    str = _itoa(sInttimer.workIs, 2, 0);
                    display_chars(LCD_SEG_L2_5_4, str, SEG_ON);
                } else {
                    display_chars(LCD_SEG_L2_5_4, (u8 *) " R", SEG_ON);
                }
		    case 2: // minutes changed
			str = _itoa(sInttimer.minutes, 2, 0);
			display_chars(LCD_SEG_L2_3_2, str, SEG_ON);
		    case 1: // Seconds changed
			str = _itoa(sInttimer.seconds, 2, 0);
			display_chars(LCD_SEG_L2_1_0, str, SEG_ON);
		}
		sInttimer.drawFlag = 0; // Clear draw flag
	}

    return;
}


// *************************************************************************************************
// @fn          inttimer_visible
// @brief       Is inttimer visible?
// @param       none
// @return      1=Inttimer menu currently visible, 0=menu not visible
// *************************************************************************************************
u8 inttimer_visible(void)
{
	return (ptrMenu_L2 == &menu_L2_Inttimer); // gibbons: currently hardcoded to Line2; change?
}

#endif //ifdef CONFIG_INTTIMER
