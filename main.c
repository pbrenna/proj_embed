#include "c8051f020.h"
#include "init.h"
#include "ev.h"
#include "i2c_machine.h"


void main(){
	init();
	init_display(ev_init_accel);
	while(1){
		dispatch();
	}
}
