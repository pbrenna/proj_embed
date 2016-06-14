#include "ev.h"
#include "i2c_machine.h"
#include "c8051f020.h"
#include "accel.h"
/*
code float lut_arccos[32] = {
	0,
	2.69,
	5.38,
	8.08,
	10.81,
	13.55,
	16.33,
	19.16,
	22.02,
	24.95,
	27.95,
	31.04,
	34.23,
	37.54,
	41.01,
	44.68,
	48.59,
	52.83,
	57.54,
	62.95,
	69.64,
	79.86,
	90,
	90,
	90,
	90,
	90,
	90,
	90,
	90,
	90,
	90	
};*/


unsigned char buf_index = 0;
sbit Led = P1^6;
code char accel_init_code[] = {0x07,0x01};

void init_accel(){
	i2c_command(ACCEL, accel_init_code, sizeof(accel_init_code), ev_read_axis, I2C_STOP|I2C_WRITE,0,0);
}
code char axis [] = {0x00};
char axes[BUF_LEN][3];
void read_axis(){
	i2c_command(ACCEL, axis, 1, ev_rcv_axis, I2C_WRITE,0,0);
}

void rcv_axis(){
	Led = STO;
	i2c_command(ACCEL,axis,0,ev_ciao, I2C_STOP,3, axes[buf_index++]);
	buf_index = buf_index % BUF_LEN;
}
