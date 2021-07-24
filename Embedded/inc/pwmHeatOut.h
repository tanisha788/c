/**
 * @file pwmHeatOut.h
 * @author Sanjokta
 * @brief This contains all the necessary functions to generate pwm signal at pin OC1A (B1).
 * @version 0.1
 * @date 2021-07-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _PWMHEATOUT_H_
#define _PWMHEATOUT_H_

#ifndef __AVR_ATmega328__
    #define __AVR_ATmega328__
#endif

#include <avr/io.h>

/**
 * @brief Initialize OC1A to generate phase corrected 10-bit PWM generator with prescaler 8.  
 * 
 */
void pwmInit_OC1A(void);

/**
 * @brief Set the value of Compare register of OC1A
 * 
 * @param comparevalue 10-bit value which is to be set in Output compare register of OC1A.
 */
void setCompare_OC1A(uint16_t comparevalue);

#endif//_PWMHEATOUT_H_