/**
 * @file tempSet.h
 * @author Sanjokta
 * @brief This contains necessary functions to read analog value from the temperature set potentiometer.
 * @version 0.1
 * @date 2021-07-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _TEMP_SET_H_
#define _TEMP_SET_H_

#ifndef __AVR_ATmega328__
    #define __AVR_ATmega328__
#endif

#define TRUE 0xFF
#define FALSE 0x00

#include <avr/io.h>

/**
 * @brief Initialize the ADC of atmega328 MCU
 * 
 */
void initADC(void);

/**
 * @brief This function reads analog value in ADC0 and converts it into a 10bit value if actuation state is TRUE(0xFF)
 * 
 * @param actuationState Actuation state TRUE(0xFF) or FALSE(0x00)
 * @return uint16_t Returns 10-bit value of converted analog signal at pin ADC0
 */
uint16_t readADC0(uint8_t actuationState);

#endif//_TEMP_SET_H_