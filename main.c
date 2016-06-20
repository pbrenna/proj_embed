#include "c8051f020.h"
#include "init.h"
#include "ev.h"
#include "i2c_machine.h"

sbit Led = P1^6;
void main(){
	Led = 0;
	init();
	init_display(ev_init_accel);
	while(1){
		dispatch();
	}
}