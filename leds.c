/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <xc.h>

#define OUTP 0

void initLEDs(){
    //TODO: Initialize the appropriate pins to work with the LEDs
    TRISGbits.TRISG12 = OUTP;
    TRISGbits.TRISG14 = OUTP;
    CNPUGbits.CNPUG14 = 1;
    CNPUGbits.CNPUG12 = 1;
    LATGbits.LATG12 = 1;
    LATGbits.LATG14 = 0;
    
}