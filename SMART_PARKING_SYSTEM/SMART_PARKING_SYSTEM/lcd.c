/*
 * lcd.c
 *
 * Created: 26-07-2026 14:29:29
 *  Author: hp
 */ 


/*
 * lcd.c
 *
 *  Created on:
 *      Author:
 */

#include "lcd.h"

/*------------------------------------------------
            Private Function Prototypes
------------------------------------------------*/

static void LCD_EnablePulse(void);
static void LCD_SendNibble(uint8_t nibble);

/*------------------------------------------------
            Enable Pulse
------------------------------------------------*/

static void LCD_EnablePulse(void)
{
	PORTB |= (1 << LCD_EN);
	_delay_us(2);

	PORTB &= ~(1 << LCD_EN);
	_delay_us(100);
}

/*------------------------------------------------
        Send 4-bit Nibble to LCD
------------------------------------------------*/

static void LCD_SendNibble(uint8_t nibble)
{
	/* Clear Data Pins */
	PORTD &= ~((1 << LCD_D4) |
	           (1 << LCD_D5) |
	           (1 << LCD_D6) |
	           (1 << LCD_D7));

	/* Set Data Pins */

	if(nibble & 0x01)
		PORTD |= (1 << LCD_D4);

	if(nibble & 0x02)
		PORTD |= (1 << LCD_D5);

	if(nibble & 0x04)
		PORTD |= (1 << LCD_D6);

	if(nibble & 0x08)
		PORTD |= (1 << LCD_D7);

	LCD_EnablePulse();
}

/*------------------------------------------------
            Send Command
------------------------------------------------*/

void LCD_Command(uint8_t cmd)
{
	PORTB &= ~(1 << LCD_RS);

	LCD_SendNibble(cmd >> 4);
	LCD_SendNibble(cmd & 0x0F);

	_delay_ms(2);
}

/*------------------------------------------------
            Send Character
------------------------------------------------*/

void LCD_Char(uint8_t data)
{
	PORTB |= (1 << LCD_RS);

	LCD_SendNibble(data >> 4);
	LCD_SendNibble(data & 0x0F);

	_delay_ms(2);
}

/*------------------------------------------------
            Display String
------------------------------------------------*/

void LCD_String(const char *str)
{
	while(*str)
	{
		LCD_Char(*str++);
	}
}

/*------------------------------------------------
            Clear LCD
------------------------------------------------*/

void LCD_Clear(void)
{
	LCD_Command(0x01);
	_delay_ms(2);
}

/*------------------------------------------------
            Set Cursor Position
------------------------------------------------*/

void LCD_SetCursor(uint8_t row, uint8_t col)
{
	uint8_t address;

	if(row == 0)
		address = 0x80 + col;
	else
		address = 0xC0 + col;

	LCD_Command(address);
}

/*------------------------------------------------
            Initialize LCD
------------------------------------------------*/

void LCD_Init(void)
{
	/* Configure LCD Pins as Output */

	DDRB |= (1 << LCD_RS) | (1 << LCD_EN);

	DDRD |= (1 << LCD_D4) |
	        (1 << LCD_D5) |
	        (1 << LCD_D6) |
	        (1 << LCD_D7);

	_delay_ms(20);

	PORTB &= ~(1 << LCD_RS);

	/* LCD Initialization Sequence */

	LCD_SendNibble(0x03);
	_delay_ms(5);

	LCD_SendNibble(0x03);
	_delay_us(200);

	LCD_SendNibble(0x03);
	_delay_us(200);

	LCD_SendNibble(0x02);

	/* Function Set: 4-bit, 2 lines, 5x8 font */
	LCD_Command(0x28);

	/* Display ON, Cursor OFF */
	LCD_Command(0x0C);

	/* Entry Mode Set */
	LCD_Command(0x06);

	/* Clear Display */
	LCD_Clear();
}