/*******************************************************************************
    Filename: hal_lcd.h

    Copyright 2010 Texas Instruments, Inc.
***************************************************************************/
#ifndef HAL_LCD_H
#define HAL_LCD_H

#ifndef MIN
#define MIN(n,m)   (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n,m)   (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
#define ABS(n)     (((n) < 0) ? -(n) : (n))
#endif

#define LCD_BACKLT_OUT      P8OUT
#define LCD_BACKLT_DIR      P8DIR
#define LCD_BACKLT_SEL      P8SEL
#define LCD_BACKLIGHT_PIN   BIT3
#define LCD_CS_RST_DIR      P9DIR
#define LCD_CS_RST_OUT      P9OUT  
#define LCD_CS_PIN          BIT6 
#define LCD_RESET_PIN       BIT7
#define LCD_SPI_SEL			P9SEL
#define LCD_SPI_DIR			P9DIR
#define LCD_MOSI_PIN		BIT1
#define	LCD_MISO_PIN		BIT2
#define LCD_CLK_PIN   		BIT3

#define LCD_ROW                 110
#define LCD_COL                 138
#define LCD_Size                3505
#define LCD_MEM_Size            110*17
#define LCD_Max_Column_Offset   0x10  
 
#define LCD_Last_Pixel          3505

#define LCD_MEM_Row             0x11
#define LCD_Row                 0x20

// Grayscale level definitions
#define PIXEL_OFF               0
#define PIXEL_LIGHT             1
#define PIXEL_DARK              2
#define PIXEL_ON                3

#define INVERT_TEXT             BIT0
#define OVERWRITE_TEXT          BIT2
#define GRAYSCALE_TEXT			BIT1

/*-------------------------------------------------------------
 *                  Function Prototypes 
 * ------------------------------------------------------------*/ 
//extern void halLcdInit(void);
//extern void halLcdShutDown(void);
//extern void halLcdBackLightInit(void);
//extern void halLcdSetBackLight(unsigned char BackLightLevel);
//extern unsigned int halLcdGetBackLight(void);
//extern void halLcdShutDownBackLight(void);
//extern void halLcdSendCommand(unsigned char Data[]) ;
//extern void halLcdSetContrast(unsigned char ContrastLevel);
//extern unsigned char halLcdGetContrast(void);
//extern void halLcdStandby(void);
//extern void halLcdActive(void);
//
////Move to specified LCD address
//extern void halLcdSetAddress(int Address);
//
////Draw at current segment location
//extern void halLcdDrawCurrentBlock(unsigned int Value);
//extern void halLcdDrawCurrentLine(const unsigned int *value, int length);
//
////Draw at specified location by calling
////LCD_Set_Address(Address) & LCD_Draw_Current_Block( value )
//extern void halLcdDrawBlock(unsigned int Address, unsigned int Value);
//
////Read value from LCD CGRAM
//extern int halLcdReadBlock(unsigned int Address);
//
////Clear LCD Screen
//extern void halLcdClearScreen(void);
//
////Invert black to white and vice versa
//extern void halLcdReverse(void);
//
//// Draw a Pixel @ (x,y) with GrayScale level
//extern void halLcdPixel(  int x,  int y, unsigned char GrayScale);
////Draw Line from (x1,y1) to (x2,y2) with GrayScale level
//extern void halLcdLine(  int x1,  int y1,  int x2,  int y2, unsigned char GrayScale);
//extern void halLcdHLine( int x1, int x2, int y, unsigned char GrayScale);
//extern void halLcdVLine( int x1, int x2, int y, unsigned char GrayScale);
//
//extern void halLcdCircle(int x, int y, int Radius, int GrayScale);
//
//extern void halLcdImage(const unsigned int Image[], int Columns, int Rows, int x, int y);
//extern void halLcdClearImage(int Columns, int Rows,  int x, int y);
//
////Print String of Length starting at current LCD location
//extern void halLcdPrint(char String[], unsigned char TextStyle) ;
//
////Print String of Length starting at (x,y)
//extern void halLcdPrintXY(char String[], int x, int y, unsigned char TextStyle);
//
////Print String of Length starting at (x,y)
//extern void halLcdPrintLine(char String[], unsigned char Line, unsigned char TextStyle);
//extern void halLcdPrintLineCol(char String[], unsigned char Line, unsigned char Col, unsigned char TextStyle);
//
//extern void halLcdCursor(void);
//extern void halLcdCursorOff(void);
////Scroll a single row of pixels
//extern void halLcdScrollRow(int y);
////Scroll a number of consecutive rows from yStart to yEnd
//extern void halLcdHScroll(int yStart, int yEnd);
////Scroll a line of text
//extern void halLcdScrollLine(int Line);

/* Swap nibble */
#define SWAP_NIBBLE(x)              ((((x) << 4) & 0xF0) | (((x) >> 4) & 0x0F))

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

/*
 * Function Prototypes
 */

void halLcdInit(void);

void write_lcd_mem(uint8_t *segmem, uint8_t *blkmem,
                  uint8_t bits, uint8_t bitmask, uint8_t state);
/* Not to be used by modules */
void start_blink(void);
void stop_blink(void);
void clear_blink_mem(void);
#endif /* HAL_LCD_H */
