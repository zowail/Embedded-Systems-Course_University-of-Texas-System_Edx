// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 15, 2016

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

#include "TExaS.h"
#include "zowail.h"




// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts


unsigned long In; //input from PF4
unsigned long Out; //output from PF2



// function to initialize the systick
void Systick_init(void)
		{
				NVIC_ST_CTRL_R = 0;         				//initiate systick by clearing all bits
				NVIC_ST_RELOAD_R = 0x00FFFFFF;  		// max 24 bits 
				NVIC_ST_CURRENT_R = 0;							// 3shan yebda2 y3edd men el awel 7atta law kan lesa gowah 7aga
				NVIC_ST_CTRL_R = 0x00000005;				// enable(bit0) =1 & clock source (bit 2) = 1 y3ny internal clock
																						// b3d kda ya5od el value men reload y7otaha f current w ybda2 el 3add
		}


// delay function for systick		
void Systick_wait(unsigned int delay)
{
	NVIC_ST_RELOAD_R = delay - 1;									// 3shan el delay bybda2 men 0 f hatra7 1
  NVIC_ST_CURRENT_R = 0;												// ha7ot ay value fel current 3shan ysht8al f 7ateet 0 
  while((NVIC_ST_CTRL_R & 0x00010000) == 0) {}	// lama el bit rkam 16 el hea (count = 1 ) kda yb2a 5allas 3add
}



// function to delay 10 ms
void Systick_wait10ms(unsigned int delay)
{
unsigned i;
for(i = 0 ; i < delay ; i++)
{
Systick_wait(800000);
}
}





// function to delay for 100ms

	void Delay100ms(){
		unsigned long i;
			i = 1333333; 
			while(i > 0)
				i = i - 1;
			}

			
			
			
	
		




			
int main(void){ 
	
	unsigned long volatile delay;
  TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  // activate grader and set system clock to 80 MHz
  // initialization goes here

	
	SYSCTL_RCGC2_R |= 0x00000020;     // activate clock for Port F
  //delay = SYSCTL_RCGC2_R;           // allow time for clock to start
	GPIO_PORTF_AMSEL_R = 0x00;        // disable analog on PF
	GPIO_PORTF_PCTL_R = 0x00000000;   // PCTL GPIO on PF
	GPIO_PORTF_DIR_R = 0x04;          // PF2 out & PF4 in (rest are in)
	GPIO_PORTF_AFSEL_R = 0x00;        // disable alt funct on PF
	GPIO_PORTF_DEN_R = 0x14;          // enable digital I/O on PF4 & PF2
	GPIO_PORTF_PUR_R = 0x10;          // enable pull-up on PF4
	GPIO_PORTF_DATA_R = 0x14;					// turn LED on
	

  EnableInterrupts();           // enable interrupts for the grader
	
	
	
	
	Systick_init();   // initialize the Systick
	
	
	
  while(1){
    // body goes here
		
		
		
		Systick_wait10ms(100);
		
		/*
		// Toggle LED if PF4 pressed (and PF2 is not pressed)
		if(GPIO_PORTF_DATA_R == 0x05) // Turn LED OFF
			GPIO_PORTF_DATA_R = 0X01;
		else if(GPIO_PORTF_DATA_R == 0x01) // Turn LED ON
			GPIO_PORTF_DATA_R = 0X05;
		
		*/
		
		// Toggle LED if PF4 pressed (and PF2 is pressed)
		 if(GPIO_PORTF_DATA_R == 0x04) // Turn LED OFF
			GPIO_PORTF_DATA_R = 0X00;
		else if (GPIO_PORTF_DATA_R == 0x00) // Turn LED ON
			GPIO_PORTF_DATA_R = 0X04;
		
		
  }
}
