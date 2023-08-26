
#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include "stdint.h"
#include "debug.h"
#include "CHobby_GPIO.h"

#define CtlPort GPIOC
#define RS GPIO_Pin_14
#define EN GPIO_Pin_15

#define DtaPort GPIOA
#define Data    0xF0

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define HIGH 1
#define LOW  0

/*****   function prototypes to keep the "Warnings" away   ****/
void LCD_init( uint8_t cols, uint8_t fourbitmode );
void LCDprint( uint8_t *stg );
void setCursor(uint8_t col, uint8_t row);
//void send(uint8_t value, uint8_t mode);

#endif /* LCD_LCD_H_ */
