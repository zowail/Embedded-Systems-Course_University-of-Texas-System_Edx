// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 15, 2016
//      Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"








// ***** 2. Global Declarations Section *****

//port E init
void PortE_Init(void);

void systick_init(void);
void Systick_wait(unsigned int delay);
void Systick_wait10ms( unsigned int delay);







// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz
  
	
  EnableInterrupts();           // enable interrupts for the grader
	
	systick_init();   //enable systick
	
	PortE_Init();			// Port E init
	
  while(1){
    
		Systick_wait10ms(10);
		
		
		
		// code b7eery
		
		
		
		if((GPIO_PORTE_DATA_R&0x1))
		{
			GPIO_PORTE_DATA_R^=0x2;		//Toggle PE1
		}
		else
		{
			GPIO_PORTE_DATA_R|=0x2;
		}
		
		
		
		
		/*
		while( (GPIO_PORTE_DATA_R & 0x00) == 1)
		{
			GPIO_PORTE_DATA_R |= 0x02;
		}
		
		if( (GPIO_PORTE_DATA_R & 0x00) == 0)   // if the switch is pressed
		{
			while ( (GPIO_PORTE_DATA_R & 0x00) == 0)   // while the switch is pressed
			{
				GPIO_PORTE_DATA_R ^= 0x02;
				Systick_wait10ms(10);
			}
		}
		
		*/
		
		
		
		
		
		
		
  }
  
}





void PortE_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000010;      // 1) E clock
  while((SYSCTL_RCGC2_R & 0x00000010) == 0) {};            // delay to allow clock to stabilize     
  GPIO_PORTE_AMSEL_R &= 0x00;        // 2) disable analog function
  GPIO_PORTE_PCTL_R &= 0x00000000;   // 3) GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R &= ~0x01;         // 4.1) PE0 input,
  GPIO_PORTE_DIR_R |= 0x02;          // 4.2) PE1 output  
  GPIO_PORTE_AFSEL_R &= 0x00;        // 5) no alternate function    
  GPIO_PORTE_DEN_R |= 0x03;          // 7) enable digital pins PF4-PF1
	GPIO_PORTE_DATA_R|=0x2;		//Initially PE1=1
}









void systick_init(void)
{
NVIC_ST_CTRL_R = 0;
NVIC_ST_RELOAD_R = 0x00FFFFFF;
NVIC_ST_CURRENT_R = 0;
NVIC_ST_CTRL_R = 0x00000005;
}


void Systick_wait(unsigned int delay)
{
NVIC_ST_RELOAD_R = delay - 1;
NVIC_ST_CURRENT_R = 0;
while((NVIC_ST_CTRL_R & 0x00010000) == 0) {}
}


void Systick_wait10ms( unsigned int delay)
{
unsigned int i;
for(i = 0 ; i < delay ; i++)
{
Systick_wait(800000);
}
}