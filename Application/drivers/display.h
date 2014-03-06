/*
 * display.h
 *
 *  Created on: 7 févr. 2014
 *      Author: rpa
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

//#include "../cc430f6137_HAL/hal_lcd.h"

/*!
	\brief Virtual LCD screen
	\sa #lcd_screens_create()
*/
struct lcd_screen {
	uint8_t *segmem; /*!< pointer to segment memory location */
	uint8_t *blkmem; /*!< pointer to blinking memory location */
};

/*!
	\brief Creates virtual screens
	\details Virtual screens are used to display data outside of the real screen. After creating <i>nr</i> number of screens, you can select which screen to write data to using the <i>scr_nr</i> argument available in any of the display functions:<br />
	 #display_symbol()<br />
    #display_char()<br />
    #display_chars()<br />
    #display_clear()<br />

	After creating the virtual screens using this function, the screen 0 is always selected as the active screen. This means that any writes to screen 0 will actually be imediately displayed on the real screen, while writes to other screens will be saved until lcd_screen_activate() is called.
	\note Each virtual screen takes 24bytes of memory. It is less than the code that you would actually need to write to handle the cases where these functions are meant to be used. However, RAM memory on the ez430 chronos is limited too so don't use a bazilion of screens.
	\note Never, ever forget to destroy the created screens using lcd_screens_destroy() !
	\sa lcd_screens_destroy(), lcd_screen_activate()
*/
void lcd_screens_create(
	uint8_t nr /*!< the number of screens to create */
);

/*!
	\brief Destroys all virtual screen
	\details Destroys all #lcd_screen created by #lcd_screens_create()
*/
void lcd_screens_destroy(void);

/*!
	\brief Activates a virtual screen
	\details Virtual screens are used to display data outside of the real screen. See lcd_screens_create() on how to create virtual screens.<br />
	This function selects the active screen. The active screen is the screen where any writes to it will be imediately displayed in the real screen.
	\note If you set the <i>scr_nr</i> to 0xff, the next screen will be automatically activated.
	\sa lcd_screens_destroy(), lcd_screens_create()
*/
void lcd_screen_activate(
	uint8_t scr_nr /*!< the screen number to activate, or 0xff */
);

/*!
	\brief Clears the screen
	\details Clears the screen as instructed by <i>line</i>. If no virtual screens are created, the argument <i>scr_nr</i> is ignored, otherwise it selects which screen the operation will affect.
*/
void display_clear(
	uint8_t scr_nr, /*!< the virtual screen number to clear */
	uint8_t line /*!< If zero, clears the entire screen (symbols and lines).<br />If one, clears the first line.<br />If two, clears the second line. */
);

/*
    \brief Display a custom collection of segments
    \details Changes the <i>state</i> of <i>segment</i> state according to user specified <i>bits</i>. If no virtual screens are created, the argument <i>scr_nr</i> is ignored, otherwise it selects which screen the operation will affect.
    \sa #display_char()
*/
void display_bits(
	uint8_t scr_nr, /*!< the virtual screen number where to display */
	enum display_segment segment, /*!< A segment */
	uint8_t bits, /*!< The bits of the segment */
	enum display_segstate state /*!< A bitfield with state operations to be performed on the segment */
);

/*!
	\brief Displays a single character
	\details Changes the <i>state</i> of <i>segment</i> state according to bits calculated from <i>chr</i>. If no virtual screens are created, the argument <i>scr_nr</i> is ignored, otherwise it selects which screen the operation will affect.

	For example, the following line:<br />
	\code
	display_char(0, LCD_SEG_L1_3, 'C', SEG_SET);<br />
	\endcode
	Changes the bits of the 4th segment (from the right) of first line to show a 'C' character. The 'C' character is shown in the real screen.

	Another but a little more complex example:<br />
	\code
	// changes the bits of the 4th segment (from the right) of first line to show the '1' character in the real screen.
	display_char(0, LCD_SEG_L1_3, '1', SEG_SET);

	// makes all bits of the segment to blink. because only the bits corresponding to the '1' character are being shown, only the displayed '1' blinks.
	display_char(0, LCD_SEG_L1_3, '8', BLINK_ON);

	// changes the bits of the segment to show the '8' character. this operation doesn't change the blinking bits, so the displayed '8' will blink.
	display_char(0, LCD_SEG_L1_3, '8', SEG_SET);

	// turns off blinking for the bits corresponding to the '-' character. In this case because the bits of '8' were blinking, turning off '-' will make the bits of '0' continue blinking, while the '-' remains static.
	display_char(0, LCD_SEG_L1_3, '-', BLINK_OFF);
	\endcode
	\sa #display_chars()
*/
void display_char(
	uint8_t scr_nr, /*!< the virtual screen number where to display */
	enum display_segment segment, /*!< A segment */
	char chr, /*!< The character to be displayed */
	enum display_segstate state /*!< A bitfield with state operations to be performed on the segment */
);


/*!
	\brief Displays several consecutive characters
	\details Smiliar to #display_char() except it works with a vector of chars.

	Example:<br />
	\code
	// changes the bits of the 4th to 1st segments (from the right) of the first line to show the "4321" string in the real screen.
	display_chars(0, LCD_SEG_L1_3_0, "4321", SEG_SET);

	// makes all bits of the first three segments to blink. because only the bits corresponding to the "4321" characters are being shown, only the first three displayed "432" segments blink.
	display_chars(0, LCD_SEG_L1_3_0, "888 ", BLINK_ON);

	// changes the bits of the segments to show the "8888" string. this operation doesn't change the blinking bits, so the first three displayed "888" segments will blink, while the last '8' segment is static.
	display_chars(0, LCD_SEG_L1_3_0, "8888", SEG_SET);

	// turns off blinking for the bits corresponding to the "----" characters. In this case because the bits of "888 " were blinking, turning off "----" will actually set the blinking bits to "000 ". Because the "8888" string is being displayed, only the first three "000" bits will blink, the first three "---" bits will remain static and the last segment remains static.
	display_chars(0, LCD_SEG_L1_3_0, "----", BLINK_OFF);
	\endcode
	Also, passing NULL as the <i>str</i> argument is equivalent of passing a vector of '8' characters. Consider the previous example, where the string "8888" can equivalently be replaced with NULL.

	\note See #_sprintf() on how to convert decimals into a string.
	\sa #display_char(), #_sprintf()
*/
void display_chars(
	uint8_t scr_nr, /*!< the virtual screen number where to display */
	enum display_segment_array segments, /*!< A segment array */
	char const * str, /*!< A pointer to a vector of chars to be displayed */
	enum display_segstate state /*!< A bitfield with state operations to be performed on the segment */
);

/*!
	\brief Displays a symbol
	\details Changes the <i>state</i> of the segment of <i>symbol</i>. If no virtual screens are created, the argument <i>scr_nr</i> is ignored, otherwise it selects which screen the operation will affect.
	Example:
	\code
	// turns on the "heart" segment and make it blink
	display_symbol(0, LCD_ICON_HEART, SEG_SET | BLINK_ON);
	\endcode
*/
void display_symbol(
	uint8_t scr_nr,       /*!< the virtual screen number */
	enum display_segment symbol, /*!< the segment to display */
	enum display_segstate state /*!< A bitfield with state operations to be performed on the segment */
);

/*!
	\brief pseudo printf function
	\details Displays in screen <i>scr_nr</i>, at segments <i>segments</i>, the string containing the number <i>n</i> formatted according to <i>fmt</i>. This function is equivalent to calling display_chars(scr_nr, segments, _sprintf(fmt, n), SEG_SET).
	\sa #display_chars, #_sprintf
*/

#define _printf(scr_nr, segments, fmt, n) \
	display_chars((scr_nr), (segments), _sprintf((fmt), (n)), SEG_SET)


/*!
	\brief pseudo sprintf function
	\details Returns a pointer to the string containing the number <i>n</i> formatted according to <i>fmt</i>. The format is NOT compatible with stdio's format.
	Example:
	\code
	// returns " 8"
	_sprintf("%2u", 8);

	// returns "0020"
	_sprintf("%04u", 20);

	// returns "-048"
	_sprintf("%03s", -48);

	// returns " 048"
	_sprintf("%03s", 48);

	// returns "0xff"
	_sprintf("0x%02", 0xff);

	// returns "st1x"
	_sprintf("st%1ux", 1)
	\endcode

	<b>WARNING:</b> You must always specify the number of digits or bad results will happen! "%u" formats are not allowed!

	\return a pointer to a string
*/

char *_sprintf(
	const char *fmt, /*!< the format specifier */
	int16_t n        /*!< the number to be used in the format specifier */
);

/*!
	\brief Converts an integer from a range into a percent string between 0 and 100
	\details Takes the number <i>n</i> and returns a string representation of that number as a percent between low and high. The returned string is 3 characters long.

	Example:
	\code
	// this returns "4F"
	uint8_t *s = _itoa(0x4F, 2, 0);
	\endcode
	\return a string representation of <i>n</i>
*/
char *_itopct(
		uint32_t low,     /*!< the 0% value */
		uint32_t high,     /*!< the 100% value */
		uint32_t n
);

#endif /* DISPLAY_H_ */
