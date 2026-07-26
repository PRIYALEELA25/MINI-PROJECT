/*
 * servo.h
 *
 * Created: 26-07-2026 14:30:40
 *  Author: hp
 */ 


/*
 * servo.h
 *
 * Created on:
 * Author:
 */

#ifndef SERVO_H_
#define SERVO_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>




#define SERVO_PIN    PB2



/* Initialize Timer1 for Servo PWM */
void Servo_Init(void);

/* Set Servo Angle (0° - 180°) */
void Servo_SetAngle(uint8_t angle);

/* Gate Control Functions */
void Servo_OpenGate(void);
void Servo_CloseGate(void);

#endif /* SERVO_H_ */