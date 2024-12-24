// @author Ahmed Elwakad
// @date YYYY-MM-DD
// @title Task Title

#include "lpc21xx.h"

#include "GPIO.h"


#define CLOCK_FREQ 12000000

void delay_ms(uint16_t time){
	uint16_t i,j;
	for(i=0;i<time;i++){
		for(j=0;j<6000;j++);
		
	}
	
}
void delay_us(uint32_t us) {
    uint32_t i;
    for (i = 0; i < us * (CLOCK_FREQ / 1000000) / 6; i++) {
        __asm volatile("nop"); // "nop" is a single-cycle no-operation instruction
    }
}



// Function definitions go here

void GPIO_setPinDirection(GPIO_PORT_t port, uint8_t pin, GPIO_t isOutput){
	switch(port){
		case GPIO_PORT0:
			if(pin<16){
				PINSEL0 &= ~( 0x3 << (2*pin));
			}
			else{
				PINSEL1 &= ~( 0x3 << (2*(pin-16)));
			}
			
			if(isOutput==GPIO_OUTPUT){
				IO0DIR |= (1 <<pin);
			}
			else if(isOutput == GPIO_INPUT){
				IO0DIR &= ~(1 <<pin);
			}
			
		break;
			
		case GPIO_PORT1:
			PINSEL2 &= ~( 0x3 << (2*(pin-16)));
		
		  if(isOutput==GPIO_OUTPUT){
				IO1DIR |= (1 <<pin);
			}
			else if(isOutput == GPIO_INPUT){
				IO1DIR &= ~(1 <<pin);
			}
		
		break;
		
		}
	
}

void GPIO_setPinLevel(GPIO_PORT_t port, uint8_t pin, GPIO_OUTPUT_t isHigh){
	switch(port){
		case GPIO_PORT0:	
			if(isHigh==GPIO_HIGH){
			 IO0SET = (1 << pin); // Set pin high
      }
			else {
       IO0CLR = (1 << pin); // Set pin low
			}
			
		break;
			
		case GPIO_PORT1:
		 if (isHigh == GPIO_HIGH) {
         IO1SET = (1 << pin); // Set pin high
     } 
			else {
         IO1CLR = (1 << pin); // Set pin low
     }
     break;
		
		}
	
	
	
}


	
