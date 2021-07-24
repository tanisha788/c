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
