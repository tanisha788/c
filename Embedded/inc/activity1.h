/**
 * @file activity1.h
 * @author Sanjokta
 * @brief This activity is to sence 2 input and should actuate LED if both inputs are high.
 * @version 0.1
 * @date 2021-07-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _ACTIVITY_1_
#define _ACTIVITY_1_

#ifndef __AVR_ATmega328__
    #define __AVR_ATmega328__
#endif

#include <avr/io.h>

#define TRUE 0xFF
#define FALSE 0x00

/**
 * @brief This function uses pins B0, B3, B2.
 * Sets the directions of pins B3, B2 as input and pin B0 output
 * Also initalizers the pin B3, B2 to high and B0 to low
 */
void activity1_init();

/**
 * @brief This function outputs high in pin B0 if both pin B3 and B2 are pulled low.
 */
void activity1_loop();

/**
 * @brief This function returns TRUE(0xFF) if both pins B3 and B2 are pulled low and
 * returns FALSE(0x00) otherwise.
 * 
 * @return uint8_t returns TRUE(0xFF) or FALSE(0x00) depending on pins B2 and B3.
 */
uint8_t isHeaterActuated();

#endif