// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "timer.h"
#include "config.h"


#define ON 1
#define OFF 0
#define RUNL LATGbits.LATG12
#define STOPL LATGbits.LATG14

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */

typedef enum stateTypeEnum{
    
    RUN_LED, STOP_LED, DeBounce1a, DeBounce2a, DeBounce1b, DeBounce2b, Wait1, Wait2
    
}stateType;

volatile stateType state = RUN_LED;

int main(void)
{
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    initLEDs();
    initSW2();
    ODCGbits.ODCG12 = 1;// open drain collector for RUNLED
    ODCGbits.ODCG14 = 1;// open drain collector for STOPLED
    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        
        switch(state){
            
            case RUN_LED:
                ODCGbits.ODCG12 = 1;
                ODCGbits.ODCG14 = 0;
                RUNL = ON;
                STOPL = OFF;
                
                
                break;
                
            case STOP_LED: 
                ODCGbits.ODCG14 = 1;
                ODCGbits.ODCG12 = 0;
                RUNL = OFF;
                STOPL = ON;
                
                
                break;
            
            case DeBounce1b:
                
                delayUs(5);
                state = STOP_LED;
                
                break;
                
            case DeBounce2b:    
            
                delayUs(5);
                state = RUN_LED;
                
                break;
                
            case DeBounce1a:
                
                delayUs(5);
                state = Wait1;
                
                break;
                
                
            case DeBounce2a: 
                
                delayUs(5);
                state = Wait2;
                
                
                break;
                
            case Wait1:
                
                
                break;
                
                
            case Wait2:
                
                
                break;
            
            
       
            
            
        }
        
    }
    
    return 0;
}


// Want to raise flag when switch is pressed and released
// Press changes state from RUN to STOP and vice versa
// After each press/release, debounce 5ms

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    
    IFS1bits.CNAIF = 0;
    PORTA;
    
    if(PORTAbits.RA7 == 1){// button released
        
        if(state == Wait1){
            
            state = DeBounce1b;
            
        }
        
        else if(state == Wait2){
            
            state = DeBounce2b;
            
        }
  
        
    }
    
    else if(PORTAbits.RA7 == 0){// button pressed
        //state = STOP_LED;
        if(state == RUN_LED){
            
            state = DeBounce1a;
            
        }
        
        else if(state == STOP_LED){
            
            state = DeBounce2a;
            
        }
        
        
    }
    

}