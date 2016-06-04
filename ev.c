#include "ev.h"
#include "i2c_machine.h"
unsigned long ev_flags = 0;

char ciao[] = "@ciao";
void dispatch(){
	IF_EV(ev_i2c_interrupt) {
		i2c_state_machine();
	}
	IF_EV(ev_ciao){
		display_write(ciao, 5, ev_nop);
	}
}