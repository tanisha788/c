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