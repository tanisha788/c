#include "uartOut.h"

void USART_Init(unsigned int ubrr){
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    
    /* Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data){
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)));
    
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

void heatActuationInPercentage(uint16_t adcdata, char serialout[]){
    uint32_t mydata = (uint32_t)( (uint32_t)adcdata * (uint32_t) 100);
    mydata = (uint32_t) (mydata / (uint32_t) 1024);
    sprintf(serialout, "Heat actuation : %2u%%\n", (uint16_t)mydata);
}

void outPutString_UART(char serialout[]){
    short n = strlen(serialout);
    for(int i=0;i<n;i++)
        USART_Transmit(serialout[i]);
}