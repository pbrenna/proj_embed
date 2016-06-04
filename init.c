#incude "c8051f020.h"


void init(){
	WDTCN = 0xde;
	WDTCN = 0xad;
	OSCICN &= 0x14;     //Disable missing clock detector
	                    //and set internal osc at 2 MHz as the clock source
	EA = 1;
	LED = 0;
	
	
	//initialize i2c
	
	XBR0 = 0x05; 		//enable smbus
	XBR1 = 0;
	XBR2 = 0x40; 		//enable crossbar, pull up
	SMB0CN = 0x44;	//enable smb 
	SMB0CR = -80;
	EIE1 |= 2;			//enalbe smb interrupt
	SCON0 |= 0x10;	//enable uart0 receive
	P1MDOUT |= 0x40; //Set P1.6 to push-pull
	STO = 1;
	STA = 0;
	SI = 0;
}







