#include "ev.h"
unsigned long ev_flags = 0;


void dispatch(){
	IF_EV(ev_i2c_interrupt) {
		i2c_state_machine();
	}
}