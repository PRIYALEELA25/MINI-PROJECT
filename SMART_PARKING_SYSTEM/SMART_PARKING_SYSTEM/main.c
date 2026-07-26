
 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"
#include "servo.h"

#define ENTRY_SENSOR    PC0
#define EXIT_SENSOR     PC1

uint8_t availableSlots;



void DisplayStatus(void)
{
    LCD_Clear();

    LCD_SetCursor(0,0);
    LCD_String("Available:");

    LCD_SetCursor(0,11);
    LCD_Char(availableSlots + '0');

    LCD_SetCursor(1,0);

    if(availableSlots == 0)
        LCD_String("PARKING FULL");
    else
        LCD_String("WELCOME");
}



int main(void)
{
    /* PC0 & PC1 as Inputs */
    DDRC &= ~((1<<ENTRY_SENSOR) | (1<<EXIT_SENSOR));

    /* Enable Internal Pull-up Resistors */
    PORTC |= (1<<ENTRY_SENSOR) | (1<<EXIT_SENSOR);

    LCD_Init();
    Servo_Init();

    Servo_CloseGate();

    /* Initially two parking spaces are free */
    availableSlots = 2;

    DisplayStatus();

    while(1)
    {
       
        if(!(PINC & (1<<ENTRY_SENSOR)))
        {
            if(availableSlots > 0)
            {
                LCD_Clear();
                LCD_String("Gate Opening");

                Servo_OpenGate();

                while(!(PINC & (1<<ENTRY_SENSOR)));

                _delay_ms(300);

                Servo_CloseGate();

                availableSlots--;

                DisplayStatus();
            }
            else
            {
                LCD_Clear();
                LCD_String("PARKING FULL");

                LCD_SetCursor(1,0);
                LCD_String("NO ENTRY");

                _delay_ms(1500);

                DisplayStatus();
            }
        }

     

        if(!(PINC & (1<<EXIT_SENSOR)))
        {
            LCD_Clear();
            LCD_String("THANK YOU");

            Servo_OpenGate();

            while(!(PINC & (1<<EXIT_SENSOR)));

            _delay_ms(300);

            Servo_CloseGate();

            if(availableSlots < 2)
            {
                availableSlots++;
            }

            DisplayStatus();
        }

        _delay_ms(100);
    }

    return 0;
}