#include "ev.h"
#include "timer.h"
#include "c8051f020.h"
sbit Led = P1^6;
unsigned char _timer0_counter = 0;
void timer0() interrupt 1{
	TL0 = TL0V;
	TH0 = TH0V;
	
	EV_ENABLE(ev_read_axis);
	
	if(_timer0_counter % 10 == 0){
		EV_ENABLE(ev_thermometer_read);
		Led = 1;
	}
	if(_timer0_counter % 3 == 0){
		EV_ENABLE(ev_average);
	}
	_timer0_counter++;
	if(_timer0_counter > 29)
		_timer0_counter = 0;
	
}