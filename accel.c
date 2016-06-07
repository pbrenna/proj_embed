#include "ev.h"
#include "i2c_machine.h"
#include "c8051f020.h"
sbit Led = P1^6;
code char accel_init_code[] = {0x07,0x01};

void init_accel(){
	i2c_command(ACCEL, accel_init_code, sizeof(accel_init_code), ev_read_axis, I2C_STOP|I2C_WRITE,0,0);
}
code char axis [] = {0x00};
unsigned char axes[3]={1,2,3};
void read_axis(){
	i2c_command(ACCEL, axis, 1, ev_rcv_axis, I2C_WRITE,0,0);
}

void rcv_axis(){
	Led = STO;
	i2c_command(ACCEL,axis,0,ev_ciao, I2C_STOP,3, axes);
}
