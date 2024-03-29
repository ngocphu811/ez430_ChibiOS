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

#ifndef __DISPLAY_H
#define __DISPLAY_H


// *************************************************************************************************
// Include section

#include <project.h>
#include "ch.h"
/*
 * Set some options at compile time for how the time is displayed
 * The options are, in order of code space used-
 * OPTION_TIME_DISPLAY == CLOCK_24HR
 * OPTION_TIME_DISPLAY == CLOCK_AM_PM
 * OPTION_TIME_DISPLAY == CLOCK_DISPLAY_SELECT
 */

#define CLOCK_24HR              0
#define CLOCK_AM_PM             1
#define CLOCK_DISPLAY_SELECT    2

#ifndef OPTION_TIME_DISPLAY
#warning "OPTION_TIME_DISPLAY not defined, 0 = 24Hr, 1 = AM/PM, 2 = selectable"
#endif

#define MBSIZE			5
#define THREAD_STACKSIZE 	64
#define WA_SIZE			THD_WA_SIZE(THREAD_STACKSIZE)


// *************************************************************************************************
// Extern section

// Constants defined in library
//extern const unsigned char lcd_font[];
//extern const unsigned char * segments_lcdmem[];
//extern const unsigned char segments_bitmask[];
//extern const unsigned char itoa_conversion_table[][3];
const unsigned char lcd_font[];
const unsigned char * segments_lcdmem[];
const unsigned char segments_bitmask[];
const unsigned char itoa_conversion_table[][3];


// *************************************************************************************************
// Global Variable section

// Set of display flags
typedef union
{
  struct
  {
  	// Line1 + Line2 + Icons
    unsigned int full_update      		: 1;    // 1 = Redraw all content
    unsigned int partial_update      	: 1;    // 1 = Update changes
  	
  	// Line only
    unsigned int line1_full_update     	: 1;    // 1 = Redraw Line1 content
    unsigned int line2_full_update     	: 1;    // 1 = Redraw Line2 content

	// Logic module data update flags
    unsigned int update_time      		: 1;    // 1 = Time was updated 
#ifdef CONFIG_SIDEREAL
	unsigned int update_sidereal_time	: 1;	// 1 = Sidereal Time was updated
#endif
    unsigned int update_stopwatch     	: 1;    // 1 = Stopwatch was updated
#ifdef CONFIG_EGGTIMER
    unsigned int update_eggtimer : 1;
#endif
#ifdef CONFIG_INTTIMER
    unsigned int update_inttimer : 1;
#endif
    unsigned int update_temperature   	: 1;    // 1 = Temperature was updated
    unsigned int update_battery_voltage 	: 1;    // 1 = Battery voltage was updated
    unsigned int update_date      		: 1;    // 1 = Date was updated
    unsigned int update_alarm      		: 1;    // 1 = Alarm time was updated
    unsigned int update_acceleration		: 1; 	// 1 = Acceleration data was updated
  } flag;
  unsigned int all_flags;            // Shortcut to all display flags (for reset)
} s_display_flags;

extern volatile s_display_flags display;


// *************************************************************************************************
// Defines section

// Display function modes
#define DISPLAY_LINE_UPDATE_FULL		(BIT0)
#define DISPLAY_LINE_UPDATE_PARTIAL		(BIT1)
#define DISPLAY_LINE_CLEAR				(BIT2)
#define DISPLAY_LINE_MESSAGE			(BIT3)

// Definitions for line view style
#define DISPLAY_DEFAULT_VIEW			(0u)
#define DISPLAY_ALTERNATIVE_VIEW		(1u)
#define DISPLAY_ALTERNATIVE2_VIEW		(2u)
 
// Definitions for line access
#define LINE1							(1u)
#define LINE2							(2u)

// LCD display modes
#define SEG_OFF					(0u)
#define	SEG_ON					(1u)
#define SEG_ON_BLINK_ON			(2u)
#define SEG_ON_BLINK_OFF		(3u)
#define SEG_OFF_BLINK_OFF		(4u)

// 7-segment character bit assignments
#define SEG_A                	(BIT4)
#define SEG_B                	(BIT5)
#define SEG_C                	(BIT6)
#define SEG_D                	(BIT7)
#define SEG_E                	(BIT2)
#define SEG_F                	(BIT0)
#define SEG_G                	(BIT1)

// ------------------------------------------
// LCD symbols for easier access
//
// xxx_SEG_xxx 		= Seven-segment character (sequence 5-4-3-2-1-0)
// xxx_SYMB_xxx 	= Display symbol, e.g. "AM" for ante meridiem 
// xxx_UNIT_xxx 	= Display unit, e.g. "km/h" for kilometers per hour
// xxx_ICON_xxx 	= Display icon, e.g. heart to indicate reception of heart rate data
// xxx_L1_xxx 		= Item is part of Line1 information 
// xxx_L2_xxx 		= Item is part of Line2 information

// Symbols for Line1
#define LCD_SYMB_AM					0
#define LCD_SYMB_PM					1
#define LCD_SYMB_ARROW_UP			2
#define LCD_SYMB_ARROW_DOWN			3
#define LCD_SYMB_PERCENT			4

// Symbols for Line2
#define LCD_SYMB_TOTAL				5
#define LCD_SYMB_AVERAGE			6
#define LCD_SYMB_MAX				7
#define LCD_SYMB_BATTERY			8

// Units for Line1
#define LCD_UNIT_L1_FT				9
#define LCD_UNIT_L1_K				10
#define LCD_UNIT_L1_M				11
#define LCD_UNIT_L1_I				12
#define LCD_UNIT_L1_PER_S			13
#define LCD_UNIT_L1_PER_H			14
#define LCD_UNIT_L1_DEGREE			15

// Units for Line2
#define LCD_UNIT_L2_KCAL			16
#define LCD_UNIT_L2_KM				17
#define LCD_UNIT_L2_MI				18

// Icons
#define LCD_ICON_HEART				19
#define LCD_ICON_STOPWATCH			20
#define LCD_ICON_RECORD				21
#define LCD_ICON_ALARM				22
#define LCD_ICON_BEEPER1			23
#define LCD_ICON_BEEPER2			24
#define LCD_ICON_BEEPER3			25

// Line1 7-segments
#define LCD_SEG_L1_3				26
#define LCD_SEG_L1_2				27
#define LCD_SEG_L1_1				28
#define LCD_SEG_L1_0				29
#define LCD_SEG_L1_COL				30
#define LCD_SEG_L1_DP1				31
#define LCD_SEG_L1_DP0				32

// Line2 7-segments
#define LCD_SEG_L2_5				33
#define LCD_SEG_L2_4				34
#define LCD_SEG_L2_3				35
#define LCD_SEG_L2_2				36
#define LCD_SEG_L2_1				37
#define LCD_SEG_L2_0				38
#define LCD_SEG_L2_COL1				39
#define LCD_SEG_L2_COL0				40
#define LCD_SEG_L2_DP				41


// Line1 7-segment arrays
#define LCD_SEG_L1_3_0				70
#define LCD_SEG_L1_2_0				71
#define LCD_SEG_L1_1_0				72
#define LCD_SEG_L1_3_1				73
#define LCD_SEG_L1_3_2				74

// Line2 7-segment arrays
#define LCD_SEG_L2_5_0				90
#define LCD_SEG_L2_4_0				91
#define LCD_SEG_L2_3_0				92
#define LCD_SEG_L2_2_0				93
#define LCD_SEG_L2_1_0				94
#define LCD_SEG_L2_5_2				95
#define LCD_SEG_L2_3_2				96
#define LCD_SEG_L2_5_4				97
#define LCD_SEG_L2_4_2				98
#define LCD_SEG_L2_4_3				99


// LCD controller memory map
#define LCD_MEM_1          			((unsigned char*)0x0A20)
#define LCD_MEM_2          			((unsigned char*)0x0A21)
#define LCD_MEM_3          			((unsigned char*)0x0A22)
#define LCD_MEM_4          			((unsigned char*)0x0A23)
#define LCD_MEM_5          			((unsigned char*)0x0A24)
#define LCD_MEM_6          			((unsigned char*)0x0A25)
#define LCD_MEM_7          			((unsigned char*)0x0A26)
#define LCD_MEM_8          	 		((unsigned char*)0x0A27)
#define LCD_MEM_9          			((unsigned char*)0x0A28)
#define LCD_MEM_10         			((unsigned char*)0x0A29)
#define LCD_MEM_11         			((unsigned char*)0x0A2A)
#define LCD_MEM_12         			((unsigned char*)0x0A2B)


// Memory assignment
#define LCD_SEG_L1_0_MEM			(LCD_MEM_6)
#define LCD_SEG_L1_1_MEM			(LCD_MEM_4)
#define LCD_SEG_L1_2_MEM			(LCD_MEM_3)
#define LCD_SEG_L1_3_MEM			(LCD_MEM_2)
#define LCD_SEG_L1_COL_MEM			(LCD_MEM_1)
#define LCD_SEG_L1_DP1_MEM			(LCD_MEM_1)
#define LCD_SEG_L1_DP0_MEM			(LCD_MEM_5)
#define LCD_SEG_L2_0_MEM			(LCD_MEM_8)
#define LCD_SEG_L2_1_MEM			(LCD_MEM_9)
#define LCD_SEG_L2_2_MEM			(LCD_MEM_10)
#define LCD_SEG_L2_3_MEM			(LCD_MEM_11)
#define LCD_SEG_L2_4_MEM			(LCD_MEM_12)
#define LCD_SEG_L2_5_MEM			(LCD_MEM_12)
#define LCD_SEG_L2_COL1_MEM			(LCD_MEM_1)
#define LCD_SEG_L2_COL0_MEM			(LCD_MEM_5)
#define LCD_SEG_L2_DP_MEM			(LCD_MEM_9)
#define LCD_SYMB_AM_MEM				(LCD_MEM_1)
#define LCD_SYMB_PM_MEM				(LCD_MEM_1)
#define LCD_SYMB_ARROW_UP_MEM		(LCD_MEM_1)
#define LCD_SYMB_ARROW_DOWN_MEM		(LCD_MEM_1)
#define LCD_SYMB_PERCENT_MEM		(LCD_MEM_5)
#define LCD_SYMB_TOTAL_MEM			(LCD_MEM_11)
#define LCD_SYMB_AVERAGE_MEM		(LCD_MEM_10)
#define LCD_SYMB_MAX_MEM			(LCD_MEM_8)
#define LCD_SYMB_BATTERY_MEM		(LCD_MEM_7)
#define LCD_UNIT_L1_FT_MEM			(LCD_MEM_5)
#define LCD_UNIT_L1_K_MEM			(LCD_MEM_5)
#define LCD_UNIT_L1_M_MEM			(LCD_MEM_7)
#define LCD_UNIT_L1_I_MEM			(LCD_MEM_7)
#define LCD_UNIT_L1_PER_S_MEM		(LCD_MEM_5)
#define LCD_UNIT_L1_PER_H_MEM		(LCD_MEM_7)
#define LCD_UNIT_L1_DEGREE_MEM		(LCD_MEM_5)
#define LCD_UNIT_L2_KCAL_MEM		(LCD_MEM_7)
#define LCD_UNIT_L2_KM_MEM			(LCD_MEM_7)
#define LCD_UNIT_L2_MI_MEM			(LCD_MEM_7)
#define LCD_ICON_HEART_MEM			(LCD_MEM_2)
#define LCD_ICON_STOPWATCH_MEM		(LCD_MEM_3)
#define LCD_ICON_RECORD_MEM			(LCD_MEM_1)
#define LCD_ICON_ALARM_MEM			(LCD_MEM_4)
#define LCD_ICON_BEEPER1_MEM		(LCD_MEM_5)
#define LCD_ICON_BEEPER2_MEM		(LCD_MEM_6)
#define LCD_ICON_BEEPER3_MEM		(LCD_MEM_7)

// Bit masks for write access
#define LCD_SEG_L1_0_MASK			(BIT2+BIT1+BIT0+BIT7+BIT6+BIT5+BIT4)
#define LCD_SEG_L1_1_MASK			(BIT2+BIT1+BIT0+BIT7+BIT6+BIT5+BIT4)
#define LCD_SEG_L1_2_MASK			(BIT2+BIT1+BIT0+BIT7+BIT6+BIT5+BIT4)
#define LCD_SEG_L1_3_MASK			(BIT2+BIT1+BIT0+BIT7+BIT6+BIT5+BIT4)
#define LCD_SEG_L1_COL_MASK			(BIT5)
#define LCD_SEG_L1_DP1_MASK			(BIT6)
#define LCD_SEG_L1_DP0_MASK			(BIT2)
#define LCD_SEG_L2_0_MASK			(BIT3+BIT2+BIT1+BIT0+BIT6+BIT5+BIT4)
#define LCD_SEG_L2_1_MASK			(BIT3+BIT2+BIT1+BIT0+BIT6+BIT5+BIT4)
#define LCD_SEG_L2_2_MASK			(BIT3+BIT2+BIT1+BIT0+BIT6+BIT5+BIT4)
#define LCD_SEG_L2_3_MASK			(BIT3+BIT2+BIT1+BIT0+BIT6+BIT5+BIT4)
#define LCD_SEG_L2_4_MASK			(BIT3+BIT2+BIT1+BIT0+BIT6+BIT5+BIT4)
#define LCD_SEG_L2_5_MASK			(BIT7)
#define LCD_SEG_L2_COL1_MASK		(BIT4)
#define LCD_SEG_L2_COL0_MASK		(BIT0)
#define LCD_SEG_L2_DP_MASK			(BIT7)
#define LCD_SYMB_AM_MASK			(BIT1+BIT0)
#define LCD_SYMB_PM_MASK			(BIT0)
#define LCD_SYMB_ARROW_UP_MASK		(BIT2)
#define LCD_SYMB_ARROW_DOWN_MASK	(BIT3)
#define LCD_SYMB_PERCENT_MASK		(BIT4)
#define LCD_SYMB_TOTAL_MASK			(BIT7)
#define LCD_SYMB_AVERAGE_MASK		(BIT7)
#define LCD_SYMB_MAX_MASK			(BIT7)
#define LCD_SYMB_BATTERY_MASK		(BIT7)
#define LCD_UNIT_L1_FT_MASK			(BIT5)
#define LCD_UNIT_L1_K_MASK			(BIT6)
#define LCD_UNIT_L1_M_MASK			(BIT1)
#define LCD_UNIT_L1_I_MASK			(BIT0)
#define LCD_UNIT_L1_PER_S_MASK		(BIT7)
#define LCD_UNIT_L1_PER_H_MASK		(BIT2)
#define LCD_UNIT_L1_DEGREE_MASK		(BIT1)
#define LCD_UNIT_L2_KCAL_MASK		(BIT4)
#define LCD_UNIT_L2_KM_MASK			(BIT5)
#define LCD_UNIT_L2_MI_MASK			(BIT6)
#define LCD_ICON_HEART_MASK			(BIT3)
#define LCD_ICON_STOPWATCH_MASK		(BIT3)
#define LCD_ICON_RECORD_MASK		(BIT7)
#define LCD_ICON_ALARM_MASK			(BIT3)
#define LCD_ICON_BEEPER1_MASK		(BIT3)
#define LCD_ICON_BEEPER2_MASK		(BIT3)
#define LCD_ICON_BEEPER3_MASK		(BIT3)

static MAILBOX_DECL(mbLCD, WA_SIZE, MBSIZE);

typedef enum
{
  msgDATE,
  msgTIME,
  msgSYM,
  msgERR,
  msgUSR
} emsgLCD_t;

typedef struct
{
  emsgLCD_t ID;
  unsigned char segment;
  char str[6];
  unsigned char state;
} sLCD_Message_t;

// *************************************************************************************************
// API section

// Physical LCD memory write
extern void write_lcd_mem(unsigned char * lcdmem, unsigned char bits, unsigned char bitmask, unsigned char state);

// Display init / clear
extern void lcd_init(void);
extern void clear_display(void);
extern void clear_display_all(void);
extern void clear_line(unsigned char line);

// Blinking function
extern void start_blink(void);
extern void stop_blink(void);
extern void clear_blink_mem(void);
extern void set_blink_rate(unsigned char bits);

// Character / symbol draw functions
extern void display_char(unsigned char segment, unsigned char chr, unsigned char mode);
extern void display_chars(unsigned char segments, unsigned char * str, unsigned char mode);
extern void display_symbol(unsigned char symbol, unsigned char mode);

// Time display function
extern void DisplayTime(unsigned char updateMode);
extern void display_am_pm_symbol(unsigned char timeAM);

// Set_value display functions
extern void display_value1(unsigned char segments, unsigned long value, unsigned char digits, unsigned char blanks, unsigned char disp_mode);
extern void display_hours_12_or_24(unsigned char segments, unsigned long value, unsigned char digits, unsigned char blanks, unsigned char disp_mode);

// Integer to string conversion 
extern unsigned char * _itoa(unsigned long n, unsigned char digits, unsigned char blanks);

// Segment index helper function
extern unsigned char switch_seg(unsigned char line, unsigned char index1, unsigned char index2);

void display_all_off(void);

//static WORKING_AREA(waLCDThread, THREAD_STACKSIZE);
/*static*/ msg_t LCD_Thread(void *args);

#endif // __DISPLAY_
