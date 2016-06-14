#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "accel.h"
#include "average.h"
#include "c8051f020.h"
#include "util.h"
unsigned long ev_flags = 0;
sbit Led = P1^6;

char ciao[] = "@           ";
void dispatch(){
	unsigned int i;
	if(!i2c_lock){
		IF_EV(ev_init_accel) {
			EV_DISABLE(ev_init_accel);
			init_accel();
		}else IF_EV(ev_rcv_axis){
			EV_DISABLE(ev_rcv_axis);
			rcv_axis();
		} else IF_EV(ev_read_axis){
			EV_DISABLE(ev_read_axis);
			i = 0;
			while (i < 50000){
				i++;
			}
			read_axis();
		} else IF_EV(ev_ciao){
			EV_DISABLE(ev_ciao);
			Led = 1;
			average[0] = 15;
			num2string(average[0], 1,ciao+1);
			num2string(average[1], 1,ciao+5);
			num2string(average[2], 1,ciao+8);
			display_write(ciao, 12, ev_read_axis);
		} /*else IF_EV(ev_thermometer_read){
			EV_DISABLE(ev_thermometer_read);
			thermometer_read();
		}*/ 
	}/*
	if(SI){
		i2c_state_machine();
	}*/
	IF_EV(ev_average){
		EV_DISABLE(ev_average);
		calc_average();
	}
	IF_EV(ev_thermometer_save){
		EV_DISABLE(ev_thermometer_save);
		thermometer_save();
	}
}
