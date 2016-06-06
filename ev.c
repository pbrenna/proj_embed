#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
unsigned long ev_flags = 0;

code char ciao[] = "@ciao";
void dispatch(){

	if(!i2c_lock){
		IF_EV(ev_ciao){
			EV_DISABLE(ev_ciao);
			display_write(ciao, 5, ev_thermometer_read);
		} else IF_EV(ev_thermometer_read){
			EV_DISABLE(ev_thermometer_read);
			thermometer_read();
		}
	}
	IF_EV(ev_thermometer_save){
		EV_DISABLE(ev_thermometer_save);
		thermometer_save();
	}
}