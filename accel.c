#include "i2c_machine.h"
#include "ev.h"

code char accel_init_code[] = {};

void init_accel(){
	i2c_command(ACCEL, accel_init_code, sizeof(accel_init_code), ev_nop, I2C_STOP|I2C_WRITE,0,0);
}




