/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

//Uses timer 2
void delayUs(unsigned int delay){// USE 5ms FOR MAIN CODE!!!
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    
    TMR1 = 0;
    PR1 = delay*624;
    IFS0bits.T1IF = 0;
    T1CONbits.ON = 1;
    while(IFS0bits.T1IF == 0);
    T1CONbits.ON = 0;
    
}