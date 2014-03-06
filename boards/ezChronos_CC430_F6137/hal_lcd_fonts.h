/*******************************************************************************
    Filename: hal_lcd_fonts.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef FONTS_H
#define FONTS_H

#define FONT_HEIGHT		12                    // Each character has 13 lines 
//typedef unsigned short uint8_t;

/*!
	\brief Enumeration of segment states
*/
enum display_segstate {
	SEG_OFF		= 1u, /*!< turn selected segment bits to OFF */
	SEG_ON		= 2u, /*!< turn selected segment bits to ON */
	SEG_SET		= 3u, /*!< turn OFF all bits of segment, then turn ON only selected bits */
	BLINK_OFF	= 4u, /*!< turn blinking OFF on selected segment bits */
	BLINK_ON		= 8u, /*!< turn blinking ON on selected segment bits */
	BLINK_SET	= 12u /*!< turn blinking OFF on all bits of segment, then turn blinking ON on only selected bits */
};

/*!
	\brief Enumeration of all ez430 chronos LCD segments
*/
enum display_segment {
	/* Symbols for Line1 */
	LCD_SYMB_AM				=	0, /*!< AM symbol segment */
	LCD_SYMB_PM				=	1, /*!< PM symbol segment */
	LCD_SYMB_ARROW_UP		=	2, /*!< little up arrow symbol segment */
	LCD_SYMB_ARROW_DOWN	=	3, /*!< little down arrow symbol segment */
	LCD_SYMB_PERCENT		=	4, /*!< percent symbol segment */

	/* Symbols for Line2 */
	LCD_SYMB_TOTAL			=	5, /*!< TOTAL symbol segment */
	LCD_SYMB_AVERAGE		=	6, /*!< AVG symbol segment */
	LCD_SYMB_MAX			=	7, /*!< MAX symbol segment */
	LCD_SYMB_BATTERY		=	8, /*!< BATT symbol segment */

	/* Units for Line1 */
	LCD_UNIT_L1_FT			=	9,  /*!< FT symbol segment */
	LCD_UNIT_L1_K			=	10, /*!< K symbol segment */
	LCD_UNIT_L1_M			=	11, /*!< M symbol segment */
	LCD_UNIT_L1_I			=	12, /*!< I symbol segment */
	LCD_UNIT_L1_PER_S		=	13, /*!< /s symbol segment */
	LCD_UNIT_L1_PER_H		=	14, /*!< /h symbol segment */
	LCD_UNIT_L1_DEGREE	=	15, /*!< º symbol segment */

	/* Units for Line2 */
	LCD_UNIT_L2_KCAL		=	16, /*!< kcal symbol segment */
	LCD_UNIT_L2_KM			=	17, /*!< Km symbol segment */
	LCD_UNIT_L2_MI			=	18, /*!< MI symbol segment */

	/* Icons */
	LCD_ICON_HEART			=	19, /*!< HEART symbol segment */
	LCD_ICON_STOPWATCH	=	20, /*!< STOPWATCH symbol segment */
	LCD_ICON_RECORD		=	21, /*!< RECORD symbol segment */
	LCD_ICON_ALARM			=	22, /*!< ALARM symbol segment */
	LCD_ICON_BEEPER1		=	23, /*!< segment 1 of ((( symbol */
	LCD_ICON_BEEPER2		=	24, /*!< segment 2 of ((( symbol */
	LCD_ICON_BEEPER3		=	25, /*!< segment 3 of ((( symbol */

	/* Line1 7-segments */
	LCD_SEG_L1_3			=	26, /*!< line1, 4th segment */
	LCD_SEG_L1_2			=	27, /*!< line1, 3rd segment */
	LCD_SEG_L1_1			=	28, /*!< line1, 2nd segment */
	LCD_SEG_L1_0			=	29, /*!< line1, 1st segment */
	LCD_SEG_L1_COL			=	30, /*!< line1, : segment */
	LCD_SEG_L1_DP1			=	31, /*!< ?? */
	LCD_SEG_L1_DP0			=	32, /*!< ?? */

	/* Line2 7-segments */
	LCD_SEG_L2_5			=	33, /*!< line2, 6th segment */
	LCD_SEG_L2_4			=	34, /*!< line2, 5th segment */
	LCD_SEG_L2_3			=	35, /*!< line2, 4th segment */
	LCD_SEG_L2_2			=	36, /*!< line2, 3rd segment */
	LCD_SEG_L2_1			=	37, /*!< line2, 2nd segment */
	LCD_SEG_L2_0			=	38, /*!< line2, 1st segment */
	LCD_SEG_L2_COL1		=	39, /*!< line2, 2nd : segment */
	LCD_SEG_L2_COL0		=	40, /*!< line2, 1st : segment */
	LCD_SEG_L2_DP			=	41, /*!< ?? */
};

/*!
	\brief Enumeration of LCD segment arrays
	\details The LCD_SEG_L1_3_2 member means the segments on line 1 from position 3 to 2 (inclusive). Segments are numbered from right to left.
	\sa #display_chars()
*/
enum display_segment_array {
	/* Line1 7-segment arrays */
	LCD_SEG_L1_3_2			=	0xc2, /*!< line1, segments 3-2 */
	LCD_SEG_L1_3_1			=	0xc3, /*!< line1, segments 3-1 */
	LCD_SEG_L1_3_0			=	0xc4, /*!< line1, segments 3-0 */
	LCD_SEG_L1_2_1			=	0xb2, /*!< line1, segments 2-1 */
	LCD_SEG_L1_2_0			=	0xb3, /*!< line1, segments 2-0 */
	LCD_SEG_L1_1_0			=	0xa2, /*!< line1, segments 1-0 */

	/* Line2 7-segment arrays */
	LCD_SEG_L2_5_4			=	0x52, /*!< line2, segments 5-4 */
	LCD_SEG_L2_5_3			=	0x53, /*!< line2, segments 5-3 */
	LCD_SEG_L2_5_2			=	0x54, /*!< line2, segments 3-2 */
	LCD_SEG_L2_5_1			=	0x55, /*!< line2, segments 3-1 */
	LCD_SEG_L2_5_0			=	0x56, /*!< line2, segments 1-0 */
	LCD_SEG_L2_4_3			=	0x42, /*!< line2, segments 4-3 */
	LCD_SEG_L2_4_2			=	0x43, /*!< line2, segments 4-2 */
	LCD_SEG_L2_4_1			=	0x44, /*!< line2, segments 4-1 */
	LCD_SEG_L2_4_0			=	0x45, /*!< line2, segments 4-0 */
	LCD_SEG_L2_3_2			=	0x32, /*!< line2, segments 3-2 */
	LCD_SEG_L2_3_1			=	0x33, /*!< line2, segments 3-1 */
	LCD_SEG_L2_3_0			=	0x34, /*!< line2, segments 3-0 */
	LCD_SEG_L2_2_1			=	0x22, /*!< line2, segments 2-1 */
	LCD_SEG_L2_2_0			=	0x23, /*!< line2, segments 2-0 */
	LCD_SEG_L2_1_0			=	0x12, /*!< line2, segments 1-0 */
};

/* LCD controller memory map */
#define LCD_MEM_1          			((uint8_t*)0x0A20)
#define LCD_MEM_2          			((uint8_t*)0x0A21)
#define LCD_MEM_3          			((uint8_t*)0x0A22)
#define LCD_MEM_4          			((uint8_t*)0x0A23)
#define LCD_MEM_5          			((uint8_t*)0x0A24)
#define LCD_MEM_6          			((uint8_t*)0x0A25)
#define LCD_MEM_7          			((uint8_t*)0x0A26)
#define LCD_MEM_8          	 		((uint8_t*)0x0A27)
#define LCD_MEM_9          			((uint8_t*)0x0A28)
#define LCD_MEM_10         			((uint8_t*)0x0A29)
#define LCD_MEM_11         			((uint8_t*)0x0A2A)
#define LCD_MEM_12         			((uint8_t*)0x0A2B)


/* Memory assignment */
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

/* Bit masks for write access */
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

#define LCD_SEG_MEM     (LCD_MEM_1)
#define LCD_BLK_MEM   (LCD_MEM_1 + 0x20)
#define LCD_MEM_LEN   12

#define SPRINTF_STR_LEN 8

/* storage for itoa function */
static char sprintf_str[SPRINTF_STR_LEN];

/* pointer to active screen */
static struct lcd_screen *display_screens;
static uint8_t display_nrscreens;
static uint8_t display_activescr;

/* 7-segment character bit assignments */
#define SEG_A     (BIT4)
#define SEG_B     (BIT5)
#define SEG_C     (BIT6)
#define SEG_D     (BIT7)
#define SEG_E     (BIT2)
#define SEG_F     (BIT0)
#define SEG_G     (BIT1)

/* Table with memory bit assignment for digits "0"-"9" and chars "A"-"Z"
     A
   F   B
     G
   E   C
     D
*/
static const uint8_t lcd_font[] = {
	SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F, // Displays "0"
	SEG_B + SEG_C,                           // Displays "1"
	SEG_A + SEG_B +      SEG_D + SEG_E +      SEG_G, // Displays "2"
	SEG_A + SEG_B + SEG_C + SEG_D +            SEG_G, // Displays "3"
	SEG_B + SEG_C +            SEG_F + SEG_G, // Displays "4"
	SEG_A +      SEG_C + SEG_D +      SEG_F + SEG_G, // Displays "5"
	SEG_A +      SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, // Displays "6"
	SEG_A + SEG_B + SEG_C,                         // Displays "7"
	SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, // Displays "8"
	SEG_A + SEG_B + SEG_C + SEG_D +      SEG_F + SEG_G, // Displays "9"
	0                                        ,     // Displays " " (:)
	0                                        ,     // Displays " " (;)
	SEG_A +                        SEG_F + SEG_G,  // Displays "<" as high c
	SEG_D +            SEG_G,    // Displays "="
	0                                        ,     // Displays " " (>)
	SEG_A + SEG_B +            SEG_E +      SEG_G, // Displays "?"
	0                                        ,     // Displays " " (@)
	SEG_A + SEG_B + SEG_C +      SEG_E + SEG_F + SEG_G, // Displays "A"
	SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, // Displays "b"
	SEG_D + SEG_E +      SEG_G,  // Displays "c"
	SEG_B + SEG_C + SEG_D + SEG_E +      SEG_G, // Displays "d"
	SEG_A +           +SEG_D + SEG_E + SEG_F + SEG_G, // Displays "E"
	SEG_A +                  SEG_E + SEG_F + SEG_G, // Displays "f"
	SEG_A + SEG_B + SEG_C + SEG_D +      SEG_F + SEG_G, // Displays "g" same as 9
	SEG_C +      SEG_E + SEG_F + SEG_G, // Displays "h"
	SEG_E            ,     // Displays "i"
	SEG_A + SEG_B + SEG_C + SEG_D                  , // Displays "J"
	SEG_D +      SEG_F + SEG_G,  // Displays "k"
	SEG_D + SEG_E + SEG_F      , // Displays "L"
	SEG_A + SEG_B + SEG_C +      SEG_E + SEG_F      , // Displays "M"
	SEG_C +      SEG_E +      SEG_G,   // Displays "n"
	SEG_C + SEG_D + SEG_E +      SEG_G, // Displays "o"
	SEG_A + SEG_B +            SEG_E + SEG_F + SEG_G, // Displays "P"
	SEG_A + SEG_B + SEG_C +            SEG_F + SEG_G, // Displays "q"
	SEG_E +      SEG_G,    // Displays "r"
	SEG_A +      SEG_C + SEG_D +      SEG_F + SEG_G, // Displays "S" same as 5
	SEG_D + SEG_E + SEG_F + SEG_G, // Displays "t"
	SEG_C + SEG_D + SEG_E            , // Displays "u"
	SEG_C + SEG_D + SEG_E            , // Displays "v" same as u
	SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, // Displays "W"
	SEG_B + SEG_C +     +SEG_E + SEG_F + SEG_G, // Displays "X" as H
	SEG_B + SEG_C + SEG_D +      SEG_F + SEG_G, // Displays "Y"
	SEG_A + SEG_B +      SEG_D + SEG_E +      SEG_G, // Displays "Z" same as 2
	SEG_B + SEG_E + SEG_G, //Displays "[" as _|`
	0,                     //Displays "\" ( )
	SEG_C + SEG_F + SEG_G, //Displays "]" as `|_
	SEG_A,                 //Displays "^"
	SEG_D                 //Displays "_"
};


/* Table with memory address for each display element */
static const uint8_t *segments_lcdmem[] = {
	LCD_SYMB_AM_MEM,
	LCD_SYMB_PM_MEM,
	LCD_SYMB_ARROW_UP_MEM,
	LCD_SYMB_ARROW_DOWN_MEM,
	LCD_SYMB_PERCENT_MEM,
	LCD_SYMB_TOTAL_MEM,
	LCD_SYMB_AVERAGE_MEM,
	LCD_SYMB_MAX_MEM,
	LCD_SYMB_BATTERY_MEM,
	LCD_UNIT_L1_FT_MEM,
	LCD_UNIT_L1_K_MEM,
	LCD_UNIT_L1_M_MEM,
	LCD_UNIT_L1_I_MEM,
	LCD_UNIT_L1_PER_S_MEM,
	LCD_UNIT_L1_PER_H_MEM,
	LCD_UNIT_L1_DEGREE_MEM,
	LCD_UNIT_L2_KCAL_MEM,
	LCD_UNIT_L2_KM_MEM,
	LCD_UNIT_L2_MI_MEM,
	LCD_ICON_HEART_MEM,
	LCD_ICON_STOPWATCH_MEM,
	LCD_ICON_RECORD_MEM,
	LCD_ICON_ALARM_MEM,
	LCD_ICON_BEEPER1_MEM,
	LCD_ICON_BEEPER2_MEM,
	LCD_ICON_BEEPER3_MEM,
	LCD_SEG_L1_3_MEM,
	LCD_SEG_L1_2_MEM,
	LCD_SEG_L1_1_MEM,
	LCD_SEG_L1_0_MEM,
	LCD_SEG_L1_COL_MEM,
	LCD_SEG_L1_DP1_MEM,
	LCD_SEG_L1_DP0_MEM,
	LCD_SEG_L2_5_MEM,
	LCD_SEG_L2_4_MEM,
	LCD_SEG_L2_3_MEM,
	LCD_SEG_L2_2_MEM,
	LCD_SEG_L2_1_MEM,
	LCD_SEG_L2_0_MEM,
	LCD_SEG_L2_COL1_MEM,
	LCD_SEG_L2_COL0_MEM,
	LCD_SEG_L2_DP_MEM,
};


/* Table with bit mask for each display element */
static const uint8_t segments_bitmask[] = {
	LCD_SYMB_AM_MASK,
	LCD_SYMB_PM_MASK,
	LCD_SYMB_ARROW_UP_MASK,
	LCD_SYMB_ARROW_DOWN_MASK,
	LCD_SYMB_PERCENT_MASK,
	LCD_SYMB_TOTAL_MASK,
	LCD_SYMB_AVERAGE_MASK,
	LCD_SYMB_MAX_MASK,
	LCD_SYMB_BATTERY_MASK,
	LCD_UNIT_L1_FT_MASK,
	LCD_UNIT_L1_K_MASK,
	LCD_UNIT_L1_M_MASK,
	LCD_UNIT_L1_I_MASK,
	LCD_UNIT_L1_PER_S_MASK,
	LCD_UNIT_L1_PER_H_MASK,
	LCD_UNIT_L1_DEGREE_MASK,
	LCD_UNIT_L2_KCAL_MASK,
	LCD_UNIT_L2_KM_MASK,
	LCD_UNIT_L2_MI_MASK,
	LCD_ICON_HEART_MASK,
	LCD_ICON_STOPWATCH_MASK,
	LCD_ICON_RECORD_MASK,
	LCD_ICON_ALARM_MASK,
	LCD_ICON_BEEPER1_MASK,
	LCD_ICON_BEEPER2_MASK,
	LCD_ICON_BEEPER3_MASK,
	LCD_SEG_L1_3_MASK,
	LCD_SEG_L1_2_MASK,
	LCD_SEG_L1_1_MASK,
	LCD_SEG_L1_0_MASK,
	LCD_SEG_L1_COL_MASK,
	LCD_SEG_L1_DP1_MASK,
	LCD_SEG_L1_DP0_MASK,
	LCD_SEG_L2_5_MASK,
	LCD_SEG_L2_4_MASK,
	LCD_SEG_L2_3_MASK,
	LCD_SEG_L2_2_MASK,
	LCD_SEG_L2_1_MASK,
	LCD_SEG_L2_0_MASK,
	LCD_SEG_L2_COL1_MASK,
	LCD_SEG_L2_COL0_MASK,
	LCD_SEG_L2_DP_MASK,
};

//extern const unsigned char fonts_lookup[];
//extern const unsigned int fonts[];
//extern const unsigned int GrayScale_fonts[];

extern const uint8_t lcd_font[];
extern const uint8_t *segments_lcdmem[];
extern const uint8_t segment_bitmask[];


#endif /* FONTS_H */
