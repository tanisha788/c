/**
 * @file uartOut.h
 * @author Sanjokta
 * @brief This contains necessary functions to output the value of amount of heat actuation using UART in atmega328 MCU.
 * @version 0.1
 * @date 2021-07-23
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _UARTOUT_H_
#define _UARTOUT_H_

#ifndef __AVR_ATmega328__
    #define __AVR_ATmega328__
#endif

#ifndef F_CPU
    #define F_CPU=16000000UL
#endif

#include <avr/io.h>
#include <string.h>
#include <stdio.h>

#define BAUD 9600
#define BRR (F_CPU / 16 / (BAUD-1) )

/**
 * @brief Initializes USART0 of ATMEGA328 with desired Baudrate
 * 
 * @param ubrr Value of Baud Rate Register needed to operate USART in desired Baudrate ( fcpu / (16 * (baud-1) ) )
 */
void USART_Init(unsigned int ubrr);

/**
 * @brief This functions takes in 8-bit data and transmits that serially using usart.
 * 
 * @param data 8-bit data that is to be transmitted
 */
void USART_Transmit(unsigned char data);

/**
 * @brief This function generates a string that contains info about amount of heat actuation.
 * This string is of the form:
 * "Heat actuation : %2u%%\n"
 * 
 * @param adcdata The adcvalue or temperature set value which dictates the amout of heat actuation.
 * @param serialout This char array of length 60 which stores the generated string which is to be transmitted serially.
 */
void heatActuationInPercentage(uint16_t adcdata, char serialout[]);

/**
 * @brief This functions takes in a string and transmits it serially using USART.
 * 
 * @param serialout string that is to be transmitted serially using USART
 */
void outPutString_UART(char serialout[]);

#endif//_UARTOUT_H_