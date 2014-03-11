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
// Display functions.
// *************************************************************************************************


// *************************************************************************************************
// Include section

// system
#include <project.h>
#include <string.h>
#include <cc430f6137.h>
//#include <../globals.h>

// driver
#include "display.h"

// logic
//#include "clock.h"
//#include "user.h"
//#include "date.h"
//#include "stopwatch.h"
//#include "temperature.h"


// *************************************************************************************************
// Prototypes section
void write_lcd_mem(unsigned char * lcdmem, unsigned char bits, unsigned char bitmask, unsigned char state);
void clear_line(unsigned char line);
void display_symbol(unsigned char symbol, unsigned char mode);
void display_char(unsigned char segment, unsigned char chr, unsigned char mode);
void display_chars(unsigned char segments, unsigned char * str, unsigned char mode);


// *************************************************************************************************
// Defines section



// *************************************************************************************************
// Global Variable section

// Display flags
volatile s_display_flags display;

// Global return string for itoa function
unsigned char itoa_str[8];


// *************************************************************************************************
// Extern section
extern void (*fptr_lcd_function_line1)(unsigned char line, unsigned char update);
extern void (*fptr_lcd_function_line2)(unsigned char line, unsigned char update);


// *************************************************************************************************
// @fn          lcd_init
// @brief       Erase LCD memory. Init LCD peripheral.
// @param      	none
// @return      none
// *************************************************************************************************
void lcd_init(void)
{
	// Clear entire display memory
	LCDBMEMCTL |= LCDCLRBM + LCDCLRM;

	// LCD_FREQ = ACLK/12/8 = 341.3Hz flickers in the sun
	// LCD_FREQ = ACLK/10/8 = 409.6Hz still flickers in the sun when watch is moving (might be negligible)
	
	// LCD_FREQ = ACLK/8/8 = 512Hz no flickering, even when watch is moving
	// Frame frequency = 512Hz/2/4 = 64Hz, LCD mux 4, LCD on
	LCDBCTL0 = (LCDDIV0 + LCDDIV1 + LCDDIV2) | (LCDPRE0 + LCDPRE1) | LCD4MUX | LCDON;

	// LCB_BLK_FREQ = ACLK/8/4096 = 1Hz
	LCDBBLKCTL = LCDBLKPRE0 | LCDBLKPRE1 | LCDBLKDIV0 | LCDBLKDIV1 | LCDBLKDIV2 | LCDBLKMOD0; 

	// I/O to COM outputs
	P5SEL |= (BIT5 | BIT6 | BIT7);
	P5DIR |= (BIT5 | BIT6 | BIT7);
  
	// Activate LCD output
	LCDBPCTL0 = 0xFFFF;                         // Select LCD segments S0-S15
	LCDBPCTL1 = 0x00FF;                         // Select LCD segments S16-S22

#ifdef USE_LCD_CHARGE_PUMP
	// Charge pump voltage generated internally, internal bias (V2-V4) generation
	LCDBVCTL = LCDCPEN | VLCD_2_72;
#endif
}


// *************************************************************************************************
// @fn          clear_display_all
// @brief       Erase LINE1 and LINE2 segments. Clear also function-specific content.
// @param      	none
// @return      none
// *************************************************************************************************
void clear_display_all(void)
{
	// Clear generic content
	clear_line(LINE1);
	clear_line(LINE2);
	
	// Clean up function-specific content
//	fptr_lcd_function_line1(LINE1, DISPLAY_LINE_CLEAR);
//	fptr_lcd_function_line2(LINE2, DISPLAY_LINE_CLEAR);		
	
}


// *************************************************************************************************
// @fn          clear_display
// @brief       Erase LINE1 and LINE2 segments. Keep icons.
// @param      	none
// @return      none
// *************************************************************************************************
void clear_display(void)
{
	clear_line(LINE1);
	clear_line(LINE2);
}


// *************************************************************************************************
// @fn          clear_line
// @brief       Erase segments of a given line.
// @param      	unsigned char line	LINE1, LINE2
// @return      none
// *************************************************************************************************
void clear_line(unsigned char line)
{
	display_chars(switch_seg(line, LCD_SEG_L1_3_0, LCD_SEG_L2_5_0), NULL, SEG_OFF);
	if (line == LINE1)
	{
		display_symbol(LCD_SEG_L1_DP1, SEG_OFF);
		display_symbol(LCD_SEG_L1_DP0, SEG_OFF);
		display_symbol(LCD_SEG_L1_COL, SEG_OFF);
	}
	else // line == LINE2
	{
		display_symbol(LCD_SEG_L2_DP, SEG_OFF);
		display_symbol(LCD_SEG_L2_COL1, SEG_OFF);
		display_symbol(LCD_SEG_L2_COL0, SEG_OFF);
	}
}


// *************************************************************************************************
// @fn          write_segment
// @brief       Write to one or multiple LCD segments
// @param       lcdmem		Pointer to LCD byte memory
//				bits		Segments to address
//				bitmask		Bitmask for particular display item
//				mode		On, off or blink segments
// @return      
// *************************************************************************************************
void write_lcd_mem(unsigned char * lcdmem, unsigned char bits, unsigned char bitmask, unsigned char state)
{
	if (state == SEG_ON)
	{
		// Clear segments before writing
		*lcdmem = (unsigned char)(*lcdmem & ~bitmask);
	
		// Set visible segments
		*lcdmem = (unsigned char)(*lcdmem | bits);
	}
	else if (state == SEG_OFF)
	{
		// Clear segments
		*lcdmem = (unsigned char)(*lcdmem & ~bitmask);
	}
	else if (state == SEG_ON_BLINK_ON)
	{
		// Clear visible / blink segments before writing
		*lcdmem 		= (unsigned char)(*lcdmem & ~bitmask);
		*(lcdmem+0x20) 	= (unsigned char)(*(lcdmem+0x20) & ~bitmask);
	
		// Set visible / blink segments
		*lcdmem 		= (unsigned char)(*lcdmem | bits);
		*(lcdmem+0x20) 	= (unsigned char)(*(lcdmem+0x20) | bits);
	}
	else if (state == SEG_ON_BLINK_OFF)
	{
		// Clear visible segments before writing
		*lcdmem = (unsigned char)(*lcdmem & ~bitmask);
	
		// Set visible segments
		*lcdmem = (unsigned char)(*lcdmem | bits);

		// Clear blink segments
		*(lcdmem+0x20) 	= (unsigned char)(*(lcdmem+0x20) & ~bitmask);
	}
	else if (state == SEG_OFF_BLINK_OFF)
	{
		// Clear segments
		*lcdmem = (unsigned char)(*lcdmem & ~bitmask);

		// Clear blink segments
		*(lcdmem+0x20) 	= (unsigned char)(*(lcdmem+0x20) & ~bitmask);
	}
}


// *************************************************************************************************
// @fn          _itoa
// @brief       Generic integer to array routine. Converts integer n to string.
//				Default conversion result has leading zeros, e.g. "00123"
//				Option to convert leading '0' into whitespace (blanks)
// @param       unsigned long n			integer to convert
//				unsigned char digits		number of digits
//				unsigned char blanks		fill up result string with number of whitespaces instead of leading zeros  
// @return      unsigned char				string
// *************************************************************************************************
unsigned char * _itoa(unsigned long n, unsigned char digits, unsigned char blanks)
{
	unsigned char i;
	unsigned char digits1 = digits;
	
	// Preset result string
	memcpy(itoa_str, "0000000", 7);

	// Return empty string if number of digits is invalid (valid range for digits: 1-7)
	if ((digits == 0) || (digits > 7)) return (itoa_str);
	
	// Numbers 0 .. 180 can be copied from itoa_conversion_table without conversion
	if (n <= 180)
	{
		if (digits >= 3)
		{
			memcpy(itoa_str+(digits-3), itoa_conversion_table[n], 3);
		}
		else // digits == 1 || 2  
		{
			memcpy(itoa_str, itoa_conversion_table[n]+(3-digits), digits);
		}
	}
	else // For n > 180 need to calculate string content
	{
		// Calculate digits from least to most significant number
		do 								
		{     
			itoa_str[digits-1] = n % 10 + '0';   	
			n /= 10;
		} while (--digits > 0);  		
	}

	// Remove specified number of leading '0', always keep last one
	i = 0;	
	while ((itoa_str[i] == '0') && (i < digits1-1))	
	{
		if (blanks > 0)
		{
			// Convert only specified number of leading '0'
			itoa_str[i]=' ';
			blanks--;
		}
		i++;
	}
	
	return (itoa_str);	
} 


// *************************************************************************************************
// @fn          display_value1
// @brief       Generic decimal display routine. Used exclusively by set_value function.
// @param       unsigned char segments		LCD segments where value is displayed
//				unsigned long value			Integer value to be displayed
//				unsigned char digits			Number of digits to convert
//				unsigned char blanks			Number of leadings blanks in itoa result string
// @return      none
// *************************************************************************************************
void display_value1(unsigned char segments, unsigned long value, unsigned char digits, unsigned char blanks, unsigned char disp_mode)
{
	unsigned char * str;

	str = _itoa(value, digits, blanks);

	// Display string in blink mode
	display_chars(segments, str, disp_mode);
}




// *************************************************************************************************
// @fn          display_hours_12_or_24
// @brief       Display hours in 24H / 12H time format.
// @param       unsigned char segments	Segments where to display hour data
//				unsigned long value		Hour data
//				unsigned char digits		Must be "2"
//				unsigned char blanks		Must be "0"
// @return      none
// *************************************************************************************************
void display_hours_12_or_24(unsigned char segments, unsigned long value, unsigned char digits, unsigned char blanks, unsigned char disp_mode)
{
#if (OPTION_TIME_DISPLAY > CLOCK_24HR)
  unsigned char hours;
#endif

#if (OPTION_TIME_DISPLAY == CLOCK_DISPLAY_SELECT)
	if (sys.flag.am_pm_time)
  {
#endif
#if (OPTION_TIME_DISPLAY > CLOCK_24HR)
    // convert internal 24H time format to 12H time format
    hours = convert_hour_to_12H_format(value);

    // display hours in 12H time format
    display_value1(segments, hours, digits, blanks, disp_mode);
    display_am_pm_symbol(value);
#endif
#if (OPTION_TIME_DISPLAY == CLOCK_DISPLAY_SELECT)
  }
	else
	{
#endif
#if (OPTION_TIME_DISPLAY != CLOCK_AM_PM)
		// Display hours in 24H time format 
		display_value1(segments, (unsigned int) value, digits, blanks, disp_mode);
#endif
#if (OPTION_TIME_DISPLAY == CLOCK_DISPLAY_SELECT)
	}
#endif
}


// *************************************************************************************************
// @fn          display_am_pm_symbol
// @brief       Display AM or PM symbol.
// @param       unsigned char hour		24H internal time format
// @return      none
// *************************************************************************************************
#if (OPTION_TIME_DISPLAY > CLOCK_24HR)
void display_am_pm_symbol(unsigned char hour)
{
	// Display AM/PM symbol
	if (is_hour_am(hour))
	{
		display_symbol(LCD_SYMB_AM, SEG_ON);
	}
	else
	{
		// Clear AM segments first - required when changing from AM to PM
		display_symbol(LCD_SYMB_AM, SEG_OFF);
		display_symbol(LCD_SYMB_PM, SEG_ON);
	}
}
#endif

// *************************************************************************************************
// @fn          display_symbol
// @brief       Switch symbol on or off on LCD.
// @param       unsigned char symbol		A valid LCD symbol (index 0..42)
//				unsigned char state		SEG_ON, SEG_OFF, SEG_BLINK
// @return      none
// *************************************************************************************************
void display_symbol(unsigned char symbol, unsigned char mode)
{
	unsigned char * lcdmem;
	unsigned char bits;
	unsigned char bitmask;
	
	if (symbol <= LCD_SEG_L2_DP) 
	{
		// Get LCD memory address for symbol from table
		lcdmem 	= (unsigned char *)segments_lcdmem[symbol];
	
		// Get bits for symbol from table
		bits 	= segments_bitmask[symbol];
		
		// Bitmask for symbols equals bits
		bitmask = bits;
	
		// Write LCD memory 	
		write_lcd_mem(lcdmem, bits, bitmask, mode);
	}
}


// *************************************************************************************************
// @fn          display_char
// @brief       Write to 7-segment characters.
// @param       unsigned char segment		A valid LCD segment 
//				unsigned char chr			Character to display
//				unsigned char mode		SEG_ON, SEG_OFF, SEG_BLINK
// @return      none
// *************************************************************************************************
void display_char(unsigned char segment, unsigned char chr, unsigned char mode)
{
	unsigned char * lcdmem;			// Pointer to LCD memory
	unsigned char bitmask;			// Bitmask for character
	unsigned char bits, bits1;		// Bits to write
	
	// Write to single 7-segment character
	if ((segment >= LCD_SEG_L1_3) && (segment <= LCD_SEG_L2_DP))
	{
		// Get LCD memory address for segment from table
		lcdmem = (unsigned char *)segments_lcdmem[segment];

		// Get bitmask for character from table
		bitmask = segments_bitmask[segment];
		
		// Get bits from font set
		if ((chr >= 0x30) && (chr <= 0x5A)) 
		{
			// Use font set
			bits = lcd_font[chr-0x30];
		}
		else if (chr == 0x2D)
		{
			// '-' not in font set
			bits = BIT1;
		}
		else
		{
			// Other characters map to ' ' (blank)
			bits = 0;
		}

		// When addressing LINE2 7-segment characters need to swap high- and low-nibble,
		// because LCD COM/SEG assignment is mirrored against LINE1
		if (segment >= LCD_SEG_L2_5) 
		{
			bits1 = ((bits << 4) & 0xF0) | ((bits >> 4) & 0x0F);
			bits = bits1;

			// When addressing LCD_SEG_L2_5, need to convert ASCII '1' and 'L' to 1 bit,
			// because LCD COM/SEG assignment is special for this incomplete character
			if (segment == LCD_SEG_L2_5) 
			{
				if ((chr == '1') || (chr == 'L')) bits = BIT7;
			}
		}
		
		// Physically write to LCD memory		
		write_lcd_mem(lcdmem, bits, bitmask, mode);
	}
}	
	

// *************************************************************************************************
// @fn          display_chars
// @brief       Write to consecutive 7-segment characters.
// @param       unsigned char segments	LCD segment array 
//				unsigned char * str		Pointer to a string
//				unsigned char mode		SEG_ON, SEG_OFF, SEG_BLINK
// @return      none
// *************************************************************************************************
void display_chars(unsigned char segments, unsigned char * str, unsigned char mode)
{
	unsigned char i;
	unsigned char length = 0;			// Write length
	unsigned char char_start;			// Starting point for consecutive write
	
	//single charakter
	if ((segments >= LCD_SEG_L1_3) && (segments <= LCD_SEG_L2_DP))
	{
		length=1;
		char_start=segments;
	}
	//multiple charakters
	switch (segments)
	{
		// LINE1
		case LCD_SEG_L1_3_0:	length=4; char_start=LCD_SEG_L1_3; break;
		case LCD_SEG_L1_2_0:	length=3; char_start=LCD_SEG_L1_2; break;
		case LCD_SEG_L1_1_0: 	length=2; char_start=LCD_SEG_L1_1; break;
		case LCD_SEG_L1_3_1: 	length=3; char_start=LCD_SEG_L1_3; break;
		case LCD_SEG_L1_3_2: 	length=2; char_start=LCD_SEG_L1_3; break;

		// LINE2
		case LCD_SEG_L2_5_0:	length=6; char_start=LCD_SEG_L2_5; break;
		case LCD_SEG_L2_4_0:	length=5; char_start=LCD_SEG_L2_4; break;
		case LCD_SEG_L2_3_0:	length=4; char_start=LCD_SEG_L2_3; break;
		case LCD_SEG_L2_2_0:	length=3; char_start=LCD_SEG_L2_2; break;
		case LCD_SEG_L2_1_0: 	length=2; char_start=LCD_SEG_L2_1; break;
		case LCD_SEG_L2_5_4:	length=2; char_start=LCD_SEG_L2_5; break;
		case LCD_SEG_L2_5_2:	length=4; char_start=LCD_SEG_L2_5; break;
		case LCD_SEG_L2_3_2:	length=2; char_start=LCD_SEG_L2_3; break;
		case LCD_SEG_L2_4_2: 	length=3; char_start=LCD_SEG_L2_4; break;
		case LCD_SEG_L2_4_3: 	length=2; char_start=LCD_SEG_L2_4; break;
	}
	
	// Write to consecutive digits
	for(i=0; i<length; i++)
	{
		// Use single character routine to write display memory
		display_char(char_start+i, *(str+i), mode);
	}
}


// *************************************************************************************************
// @fn          switch_seg
// @brief       Returns index of 7-segment character. Required for display routines that can draw 
//				information on both lines.
// @param       unsigned char line		LINE1, LINE2
//				unsigned char index1		Index of LINE1
//				unsigned char index2		Index of LINE2
// @return      uint8
// *************************************************************************************************
unsigned char switch_seg(unsigned char line, unsigned char index1, unsigned char index2)
{
	if (line == LINE1)
	{
		return index1;
	}
	else // line == LINE2
	{
		return index2;
	}
}


// *************************************************************************************************
// @fn          start_blink
// @brief       Start blinking. 
// @param       none
// @return      none
// *************************************************************************************************
void start_blink(void)
{
	LCDBBLKCTL |= LCDBLKMOD0;
}


// *************************************************************************************************
// @fn          stop_blink
// @brief       Stop blinking.
// @param       none
// @return      none
// *************************************************************************************************
void stop_blink(void)
{
	LCDBBLKCTL &= ~LCDBLKMOD0;
}


// *************************************************************************************************
// @fn          stop_blink
// @brief       Clear blinking memory.
// @param       none
// @return      none
// *************************************************************************************************
void clear_blink_mem(void)
{
	LCDBMEMCTL |= LCDCLRBM;	
}


// *************************************************************************************************
// @fn          set_blink_rate
// @brief       Set blink rate register bits. 
// @param       none
// @return      none
// *************************************************************************************************
void set_blink_rate(unsigned char bits)
{
	LCDBBLKCTL &= ~(BIT7 | BIT6 | BIT5);	
	LCDBBLKCTL |= bits;	
}


// *************************************************************************************************
// @fn          display_all_off
// @brief       Sets everything of on the display
// @param       none
// @return      none
// *************************************************************************************************
void display_all_off(void)
{
	unsigned char * lcdptr = (unsigned char*)0x0A20;
	unsigned char i;
	
	for (i=1; i<=12; i++) 
	{
		*lcdptr = 0x00; 
		lcdptr++;
	}
}

static void mbLCD_init()
{
  chMBInit(&mbLCD, (msg_t *)WA_SIZE, MBSIZE);
}

/*static*/ msg_t LCD_Thread(void *args)
{
  (void)args;
  msg_t res;
  sLCD_Message_t message;
  
  chRegSetThreadName("LCD Thread");
  
  if(chMBGetFreeCountI(&mbLCD) != MBSIZE)
  {
    //	Display error state and blocking conditions
    return NULL;
  }
  
  //	Print welcome string
  display_chars(LCD_SEG_L1_2_0, (uint8_t *)"Hi", SEG_ON);
  chThdSleep(3000);
  message.segment = LCD_SEG_L1_3_0;
  while (TRUE)
  {
    res = chMBFetch(&mbLCD, &message, TIME_INFINITE);
    if(res == RDY_OK)
    {
      switch(message.ID)
      {
	case msgTIME: display_chars(message.segment, message.str, SEG_ON); break;
	case msgDATE: display_chars(message.segment, message.str, SEG_ON); break;
	case msgSYM: display_symbol(message.segment, SEG_ON); break;
	case msgERR: break;
	case msgUSR: break;
      }
    }
  }
}
