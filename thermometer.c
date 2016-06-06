#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "util.h"

char therm_data[2]={0,0};
char therm_data_old[2]={0,0};



code char magia[] = {0x08, 0x40, 0x50, 0x50};
void thermometer_read(){
	i2c_command(TERM,magia,4, ev_thermometer_save, I2C_STOP, 2, therm_data);
}
char* disp_temp = "@    ";
void thermometer_save(){
	num2string(therm_data[0], disp_temp+1);
	display_write(disp_temp,5,ev_nop);
}