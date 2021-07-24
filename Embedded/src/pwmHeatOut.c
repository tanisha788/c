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