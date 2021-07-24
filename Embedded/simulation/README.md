# Project In Action

![inaction](ProjectInAction.gif)

## Code 

### project_main.c

``` C
#include<avr/io.h>
#include<util/delay.h>

// pins used are: 
// B0 as output and initalized to 0
// B1 as Input and initialize it to high
// B2 as Input and initialize it to high
#include "activity1.h"

// pins used are:
// AC0 used as analog input for temperature set control
#include "tempSet.h"

// pins used are:
// OC1A (B1) to output pwm signal
#include "pwmHeatOut.h"

// UART0 is used to output amount of heat actuated
#include "uartOut.h"

int main(void)
{
	// activity 1
	activity1_init();

	// activity 2
	initADC();

	// activity 3
	pwmInit_OC1A();

	// activity 4
	USART_Init(BRR);

	while(1){
		uint16_t adcData = 0;
		char outputstr[30];

		// activity 1
		activity1_loop();
		
		// activity 2
		adcData = readADC0(isHeaterActuated());
		
		// activity 3
		setCompare_OC1A(adcData);

		// activity 4
		heatActuationInPercentage(adcData, outputstr);
		outPutString_UART(outputstr);

		_delay_ms(200);
	}
	
	return 0;
}
```

### activity1.c

``` C
#include "activity1.h"

volatile uint8_t isActuated = FALSE;

void activity1_init(){
    
    DDRB = DDRB |  (1<<PB0);
    PORTB = PORTB & ~(1<<PB0);

    //Set B3 as Input and initialize it to high
    DDRB = DDRB & ~(1<<PB3);
    PORTB = PORTB |  (1<<PB3);

    //Set B2 as Input and initialize it to high
    DDRB = DDRB & ~(1<<PB2);
    PORTB = PORTB |  (1<<PB2);
}

void activity1_loop(){
        if(isActuated)
            PORTB = PORTB | (1<<PB0);
        else
            PORTB = PORTB & ~(1<<PB0);

}

uint8_t isHeaterActuated(){
    if( !(PINB & (1<<PB3)) && !(PINB & (1<<PB2))){
        isActuated = TRUE;
    }
    else{
        isActuated = FALSE;
    }
    return isActuated;
}
```

### tempSet.c

``` C
#include "tempSet.h"

void initADC(void){
    ADMUX |= (1<<REFS0);
    ADCSRA |= (1<<ADEN); 
}

uint16_t readADC0(uint8_t actuationState){
    if(actuationState == TRUE){
        ADCSRA |= (1<<ADEN);

        ADMUX &= ~(1<<MUX0);
	    ADMUX &= ~(1<<MUX1);
	    ADMUX &= ~(1<<MUX2);
	    ADMUX &= ~(1<<MUX3);

        ADCSRA |= (1<<ADSC);

        while( !(ADCSRA & (1<<ADIF)) );
        ADCSRA |= (1<<ADIF);

        return ADC;
    }
    else{
        ADCSRA &= ~(1<<ADEN);
        return 0x0000;
    }
}
```
### pwmHeatOut.c

``` C
#include "pwmHeatOut.h"

void pwmInit_OC1A(void){
    TCCR1A |= (1<<COM1A1) | (1<<WGM11) | (1<<WGM10); // using OC1A, 10-bit phase correct
    TCCR1B |= (1<<CS11); // prescaler clk/8
    DDRB |= (1<<PB1);
    OCR1A = 0;
}

void setCompare_OC1A(uint16_t comparevalue){
    OCR1A = comparevalue;
}
```
### uartOut.h

``` C
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
```