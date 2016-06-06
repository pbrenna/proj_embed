#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "util.h"


int therm_old = 0;


int_chars therm_data;
code char magia[] = {0x08, 0x40, 0x50, 0x50};
void thermometer_read(){
	i2c_command(TERM,magia,4, ev_thermometer_save, I2C_STOP, 2, therm_data.raw);
}
char disp_temp[] = "@        ";
void thermometer_save(){

	if(therm_data.raw[1] & 0x10)
		therm_data.raw[1] |= 0xF0;
	therm_data.temp *= 0.0625;
	num2string(therm_data.temp, disp_temp+1);
	display_write(disp_temp,5,ev_nop);
}

