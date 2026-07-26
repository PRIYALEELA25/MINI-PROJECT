/*
 * servo.c
 *
 * Created: 26-07-2026 14:30:20
 *  Author: hp
 */ 
/*
 * servo.c
 *
 * Created on:
 * Author:
 */

#include "servo.h"


void Servo_Init(void)
{
    /* PB2 (OC1B) as Output */
    DDRB |= (1 << SERVO_PIN);

    /* Stop Timer1 */
    TCCR1A = 0;
    TCCR1B = 0;

   

    TCCR1A |= (1 << WGM11);

    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << WGM13);


    TCCR1A |= (1 << COM1B1);

    /*
     * Prescaler = 8
     */

    TCCR1B |= (1 << CS11);

    /*
     * PWM Frequency = 50Hz
     *
     * Timer Tick = 16MHz / 8 = 2MHz
     * 20ms = 40000 counts
     */

    ICR1 = 40000;

    /* Start at 0 Degree */

    Servo_SetAngle(0);
}



void Servo_SetAngle(uint8_t angle)
{
    uint16_t pulse;


    pulse = 2000 + ((uint32_t)angle * 2000) / 180;

    OCR1B = pulse;
}

void Servo_OpenGate(void)
{
    Servo_SetAngle(90);

    _delay_ms(1000);
}


void Servo_CloseGate(void)

{
    Servo_SetAngle(0);

    _delay_ms(1000);
}