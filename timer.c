#include "ev.h"
#include "timer.h"
#include "average.h"
#include "c8051f020.h"

unsigned char _timer0_counter = 0;
unsigned char lum = 0;
sbit r_i = P0 ^ 6;
sbit button = P3 ^ 7;

void timer0() interrupt 1{
	//this timer is fired every 100ms
	TL0 = TL0V;
	TH0 = TH0V;
	
	EV_ENABLE(ev_read_axis);
	
	//every second
	if(_timer0_counter % 10 == 0){
		EV_ENABLE(ev_thermometer_read);
		EV_ENABLE(ev_check_average);
	}
	//every 300ms
	if(_timer0_counter % 3 == 0){
		EV_ENABLE(ev_average);
	}
	_timer0_counter++;
	if(_timer0_counter > 29)
		_timer0_counter = 0;
	
	//if p3.7 button is pressed, change brightness value.
	if(!button){
			lum+=8; lum = lum %240;
	}
}

void pwm() interrupt 3 {
	if (idle){
		r_i = 0;
	} else {
		TL1 = r_i ?  lum : (240 - lum);
		TH1 = 255;
		r_i = ~r_i;
	}
}