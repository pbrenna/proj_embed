#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "accel.h"
#include "average.h"
#include "c8051f020.h"
#include "util.h"
#include "display.h"
unsigned int ev_flags = 0;
sbit Led = P1^6;

void dispatch(){
	unsigned char asd = 1;
	if(!i2c_lock){
		IF_EV(ev_init_accel) {
			EV_DISABLE(ev_init_accel);
			init_accel();
		}else IF_EV(ev_rcv_axis){
			EV_DISABLE(ev_rcv_axis);
			rcv_axis();
		} else IF_EV(ev_read_axis){
			EV_DISABLE(ev_read_axis);
			read_axis();
		} else IF_EV(ev_display_clear){
			EV_DISABLE(ev_display_clear);
			display_clear(ev_display_write_1);
		}else IF_EV(ev_thermometer_read){
			EV_DISABLE(ev_thermometer_read);
			thermometer_read();
		}else IF_EV(ev_display_write_1){
			EV_DISABLE(ev_display_write_1);
			display_write_data_1();
		}else IF_EV(ev_display_write_2){
			EV_DISABLE(ev_display_write_2);
			display_write_data_2();
		}else IF_EV(ev_display_cursor_move){
			EV_DISABLE(ev_display_cursor_move);
			display_go_to_addr(0x40, ev_display_write_2);
		}
	}
	if(SI){
		i2c_state_machine();
	}
	IF_EV(ev_average){
		EV_DISABLE(ev_average);
		calc_average();
	}
	IF_EV(ev_thermometer_save){
		EV_DISABLE(ev_thermometer_save);
		thermometer_save();
	}
	IF_EV(ev_check_average){
		EV_DISABLE(ev_check_average);
		check_average();
	}
}
