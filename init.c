#include "c8051f020.h"
#include "timer.h"

sbit Led = P1 ^ 6;

void init(){
	unsigned int i = 0;
	WDTCN = 0xde;
	WDTCN = 0xad;				//disable watchdog
	OSCICN &= 0x14;     //Disable missing clock detector
	                    //and set internal osc at 2 MHz as the clock source
	EA = 1;							//Enable interrupts globally
	Led = 0;
	
	
	

	XBR0 = 0x05; 		//enable smbus
	XBR1 = 0;
	XBR2 = 0x40; 		//enable crossbar, pull up
	SMB0CN = 0x44;	//enable smb
	SMB0CR = -80;		//set smb frequency
	//EIE1 |= 2;			//enalbe smb interrupt
	SCON0 |= 0x10;	//enable uart0 receive
	P1MDOUT |= 0x40; //Set P1.6 to push-pull
	P0MDOUT |= 0x40; //Set P0.6 to push-pull
	//SM_BUSY=0;
	STO = 1;
	STA = 0;
	SI = 0;					//clear interrupt flag for i2c
	TMOD |= 0x11;		//both timers in 16 bit mode
	ET0 = 1;				//enable timer 0 interrupt
	TR0 = 1; 				//enable timer 0
	TL0 = TL0V;
	TH0 = TH0V;
	TR1 = 1;				//enable timer 1
	ET1 = 1;				//enable timer 1 interrupt
	TH1 = 255;
}







