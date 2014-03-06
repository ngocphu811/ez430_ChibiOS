/*
 * display.c
 *
 *  Created on: 7 févr. 2014
 *      Author: rpa
 */

/***************************************************************************
 **************************** EXPORTED FUNCTIONS ***************************
 **************************************************************************/
#include "msp430.h"
#include "../globals.h"
#include "../cc430f6137_HAL/hal_lcd.h"
#include "../cc430f6137_HAL/hal_lcd_fonts.h"
#include "display.h"
#include <stdlib.h>



/*
	lcd_screens_create()
*/
void lcd_screens_create(uint8_t nr)
{
	/* allocate memory */
	display_nrscreens = nr;
	display_screens = malloc(sizeof(struct lcd_screen) * nr);

	/* the first screen is the active one */
	display_activescr = 0;
	display_screens[0].segmem = LCD_SEG_MEM;
	display_screens[0].blkmem = LCD_BLK_MEM;

	/* allocate mem for the remaining and copy real screen over */
	uint8_t i = 1;
	for (; i<nr; i++) {
		display_screens[i].segmem = malloc(LCD_MEM_LEN);
		display_screens[i].blkmem = malloc(LCD_MEM_LEN);
		memcpy(display_screens[i].segmem, LCD_SEG_MEM, LCD_MEM_LEN);
		memcpy(display_screens[i].blkmem, LCD_BLK_MEM, LCD_MEM_LEN);
	}
}

/*
	lcd_screens_destroy()
*/
void lcd_screens_destroy(void)
{
	uint8_t i = 0;

	/* switch to screen 0 and display any pending data */
	lcd_screen_activate(0);

	/* now we can delete all the screens */
	for (; i<display_nrscreens; i++) {
		if (i != display_activescr) {
			free(display_screens[i].segmem);
			free(display_screens[i].blkmem);
		}
		display_screens[i].segmem = NULL;
		display_screens[i].segmem = NULL;
	}

	free(display_screens);
	display_screens = NULL;
}

/*
	lcd_screen_activate()
   - the memory pointed by display_screens is assumed to be on
	contiguos memory
	if scr_nr == 0xff, then activate next screen.
*/
void lcd_screen_activate(uint8_t scr_nr)
{
	uint8_t prevscr = display_activescr;

	if (scr_nr == 0xff)
		helpers_loop(&display_activescr, 0, display_nrscreens - 1, 1);
	else
		display_activescr = scr_nr;

	/* allocate memory for previous screen */
	display_screens[prevscr].segmem = malloc(LCD_MEM_LEN);
	display_screens[prevscr].blkmem = malloc(LCD_MEM_LEN);

	/* copy real screen contents to previous screen */
	memcpy(display_screens[prevscr].segmem, LCD_SEG_MEM, LCD_MEM_LEN);
	memcpy(display_screens[prevscr].blkmem, LCD_BLK_MEM, LCD_MEM_LEN);

	/* update real screen with contents from activated screen */
	memcpy(LCD_SEG_MEM, display_screens[display_activescr].segmem, LCD_MEM_LEN);
	memcpy(LCD_BLK_MEM, display_screens[display_activescr].blkmem, LCD_MEM_LEN);

	/* free memory from the activated screen */
	free(display_screens[display_activescr].segmem);
	free(display_screens[display_activescr].blkmem);

	/* set activated screen as real screen output */
	display_screens[display_activescr].segmem = LCD_SEG_MEM;
	display_screens[display_activescr].blkmem = LCD_BLK_MEM;
}

void display_clear(uint8_t scr_nr, uint8_t line)
{
	if (line == 1) {
		display_chars(scr_nr, LCD_SEG_L1_3_0, NULL, SEG_OFF);
		display_symbol(scr_nr, LCD_SEG_L1_DP1, SEG_OFF);
		display_symbol(scr_nr, LCD_SEG_L1_DP0, SEG_OFF);
		display_symbol(scr_nr, LCD_SEG_L1_COL, SEG_OFF);
	} else if (line == 2) {
		display_chars(scr_nr, LCD_SEG_L2_5_0, NULL, SEG_OFF);
		display_symbol(scr_nr, LCD_SEG_L2_DP, SEG_OFF);
		display_symbol(scr_nr, LCD_SEG_L2_COL1, SEG_OFF);
		display_symbol(scr_nr, LCD_SEG_L2_COL0, SEG_OFF);
	} else {
		uint8_t *lcdptr = (display_screens ?
		            display_screens[scr_nr].segmem : (uint8_t *)LCD_SEG_MEM);
		uint8_t i = 1;

		for (; i <= 12; i++) {
			*(lcdptr++) = 0x00;
		}
	}
}

char *_sprintf(const char *fmt, int16_t n) {
	int8_t i = 0;
	int8_t j = 0;

	while (1) {
		/* copy chars until end of string or a int substitution is found */
		while (fmt[i] != '%') {
			if (fmt[i] == '\0' || j == SPRINTF_STR_LEN - 2) {
				sprintf_str[j] = '\0';
				return sprintf_str;
			}
			sprintf_str[j++] = fmt[i++];
		}
		i++;

		int8_t digits = 0;
		int8_t zpad = ' ';
		/* parse int substitution */
		while (fmt[i] != 's' && fmt[i] != 'u' && fmt[i] != 'x') {
			if (fmt[i] == '0')
				zpad = '0';
			else
				digits = fmt[i] - '0';
			i++;
		}

		/* show sign */
		if (fmt[i] == 's') {
			if (n < 0) {
				sprintf_str[j++] = '-';
				n = (~n) + 1;
			} else
				sprintf_str[j++] = ' ';
		}

		j += digits - 1;
		int8_t j1 = j + 1;

		/* convert int to string */
		if (fmt[i] == 'x') {
			do {
				sprintf_str[j--] = "0123456789ABCDEF"[n & 0x0F];
				n >>= 4;
				digits--;
			} while (n > 0);
		} else {
			do {
				sprintf_str[j--] = n % 10 + '0';
				n /= 10;
				digits--;
			} while (n > 0);
		}

		/* pad the remaining */
		while (digits > 0) {
			sprintf_str[j--] = zpad;
			digits--;
		}

		j = j1;
	}

	return sprintf_str;
}

// *************************************************************************************************
// @fn          _itopct
// @brief       Converts integer n to a percent string between low and high. (uses _itoa internally)
// @param       uint32_t low		0% value
//				uint32_t high		100% value
//				uint32_t n			integer to convert
//
// @return      uint8_t				string
// *************************************************************************************************
char *_itopct(uint32_t low,uint32_t high,uint32_t n)
{

	// Return "0" if the value is under the low
	if (n < low) return (char *) "  0";

	// Return "100" if the value is over the high
	if (n > high) return (char *) "100";

	return _sprintf("%3u", (((n*100)-(low*100))/(high-low)));
}

void display_symbol(uint8_t scr_nr, enum display_segment symbol,
                                               enum display_segstate state)
{
	if (symbol <= LCD_SEG_L2_DP) {
		// Get LCD memory address for symbol from table
		uint8_t *segmem = (uint8_t *)segments_lcdmem[symbol];
		uint8_t *blkmem = segmem + 0x20;

		if (display_screens) {
			/* get offset */
			uint8_t offset = segmem - LCD_MEM_1;

			segmem = display_screens[scr_nr].segmem + offset;
			blkmem = display_screens[scr_nr].blkmem + offset;
		}

		// Get bits for symbol from table
		uint8_t bits 	= segments_bitmask[symbol];

		// Write LCD memory
		// (bitmask for symbols equals bits)
		write_lcd_mem(segmem, blkmem, bits, bits, state);
	}
}

void display_bits(uint8_t scr_nr, enum display_segment segment,
                  uint8_t bits  , enum display_segstate state)
{
	// Write to single 7-segment character
	if ((segment >= LCD_SEG_L1_3) && (segment <= LCD_SEG_L2_DP)) {
		// Get LCD memory address for segment from table
		uint8_t *segmem = (uint8_t *)segments_lcdmem[segment];
		uint8_t *blkmem = segmem + 0x20;

		if (display_screens) {
			/* get offset */
			uint8_t offset = segmem - LCD_MEM_1;

			segmem = display_screens[scr_nr].segmem + offset;
			blkmem = display_screens[scr_nr].blkmem + offset;
		}

        // Get bitmask for character from table
        uint8_t bitmask = segments_bitmask[segment];

		// When addressing LINE2 7-segment characters need to swap high- and low-nibble,
		// because LCD COM/SEG assignment is mirrored against LINE1
		if (segment >= LCD_SEG_L2_5) {
			bits = SWAP_NIBBLE(bits);
		}

		// Physically write to LCD memory
		write_lcd_mem(segmem, blkmem, bits, bitmask, state);
	}
}

void display_char(uint8_t scr_nr, enum display_segment segment,
                  char chr, enum display_segstate state)
{
     uint8_t bits = 0;       // Bits to write (default ' ' blank)

     // Get bits from font set
     if ((chr >= 0x30) && (chr <= 0x5A)) {
         // Use font set
         bits = lcd_font[chr - 0x30];
     } else if (chr == 0x2D) {
         // '-' not in font set
         bits = BIT1;
     }

     // When addressing LCD_SEG_L2_5, need to convert ASCII '1' and 'L' to 1 bit,
     // because LCD COM/SEG assignment is special for this incomplete character
     if (segment == LCD_SEG_L2_5 && (chr == '1' || chr == 'L')) bits = SWAP_NIBBLE(BIT7);

     // Write bits to memory
     display_bits(scr_nr, segment, bits, state);
}

void display_chars(uint8_t scr_nr,
                   enum display_segment_array segments,
                   char const * str,
                   enum display_segstate state)
{
	uint8_t i = 0;
	uint8_t len = (segments & 0x0f);
	segments = 38 - (segments >> 4);

	for (; i < len; i++) {
		/* stop if we find a null termination */
		if (str) {
			if (str[i] == '\0')
				return;
			display_char(scr_nr, segments + i, str[i], state);
		 } else
			display_char(scr_nr, segments + i, '8', state);
	}
}



