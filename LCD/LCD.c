/** LCD.c
 *  Created on: Aug. 24, 2023
 *      Author: art@canhobby.ca
 **/

#include "LCD.h"
#include "stdint.h"
/****  Global Variables   ****/
uint8_t displayfunction;
uint8_t displaycontrol;
uint8_t displaymode;
uint8_t _numlines = 16;
uint8_t _row_offsets[4];

void pulseEnable() {
	GPIO_WriteBit( CtlPort, EN, 0 );
	Delay_Us( 2 );
	GPIO_WriteBit( CtlPort, EN, 1 );
	Delay_Us( 2 );
	GPIO_WriteBit( CtlPort, EN, 0 );
	Delay_Us( 100 );
}

void write4bits( uint8_t wd ) {
	uint16_t tmpA = GPIO_ReadInputData( DtaPort ) & ~Data;
//	printf("\n--- tmpA = 0x%04X --- MSK = 0x%04X\n", tmpA, ~Data );
	tmpA |= (wd << 4);
//	printf("--- tmpA = 0x%04X\n", tmpA );

	GPIO_Write( DtaPort, tmpA );
//	printf("w4 -- GPIOA = 0x%04X\n", GPIO_ReadInputData( DtaPort ) );

	pulseEnable();
}

void send(uint8_t value, uint8_t mode) {
//  digitalWrite(_rs_pin, mode);
  GPIO_WriteBit( CtlPort, RS, mode );

  /* / if there is a RW pin indicated, set it low to Write
  if (_rw_pin != 255) {
    digitalWrite(_rw_pin, LOW);
  }
***/
  if ( displayfunction & LCD_8BITMODE) {
//    write8bits( value );
  } else {
    write4bits( value>>4 );
    write4bits( value );
  }
}

void command(uint8_t value) {
//    printf("\ncmd: value = 0x%02X\n", value );
  send(value, LOW);
}

void display() {
  displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | displaycontrol );
}

void setRowOffsets( int row0, int row1, int row2, int row3 )
{
  _row_offsets[0] = row0;
  _row_offsets[1] = row1;
  _row_offsets[2] = row2;
  _row_offsets[3] = row3;
}


/********** high level commands, for the user! ****/

void LCDprint( uint8_t *stg ) {
	while( *stg ) {
		send( *stg++, HIGH );
	}
}


void setCursor(uint8_t col, uint8_t row)
{
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if ( row >= max_lines ) {
    row = max_lines - 1;    // we count rows starting from 0
  }
  if ( row >= _numlines ) {
    row = _numlines - 1;    // we count rows starting from 0
  }

  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

void write(uint8_t value) {
  send(value, 1 );
}

void clear()
{
  command( LCD_CLEARDISPLAY );  // clear display, set cursor position to zero
  Delay_Us( 2000 );				// this command takes a long time!
}


void LCD_init( uint8_t cols, uint8_t fourbitmode ) {
	CHobby_GPIO_INIT( CtlPort, RS | EN );
	CHobby_GPIO_INIT( DtaPort, Data );
	setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);
	if( cols == 20 ) _numlines = 4;
	if( fourbitmode ) { displayfunction = LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS; }
	else              { displayfunction = LCD_8BITMODE | LCD_2LINE | LCD_5x8DOTS; }

	Delay_Ms( 50 );
	GPIO_WriteBit( CtlPort, RS, LOW );
	GPIO_WriteBit( CtlPort, EN, LOW );

    write4bits(0x03);
    Delay_Us( 4500 );
    write4bits(0x03);
    Delay_Us( 4500 );
    write4bits(0x03);
    Delay_Us( 150 );
    write4bits(0x02);


    command( LCD_FUNCTIONSET | displayfunction );

    displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();

    clear();

    displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    command( LCD_ENTRYMODESET | displaymode );
}
