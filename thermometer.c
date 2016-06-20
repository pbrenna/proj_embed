#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "util.h"
#include "c8051f020.h"

int therm_old = 0;
sbit Led = P1^6;

int_chars therm_data;
code char therm_read_command[] = {0x08, 0x40, 0x50, 0x50};
void thermometer_read(){
	i2c_command(TERM,therm_read_command,sizeof(therm_read_command), ev_thermometer_save, I2C_STOP, 2, therm_data.raw);
}

void thermometer_save(){
	//remove last 3 bits
	therm_data.temp = therm_data.temp >> 3;
	//if it is negative, fix two's complement representation
	if(therm_data.raw[0] & 0x10)
		therm_data.raw[0] |= 0xF0;
	//get tenths of °C
	therm_data.temp = therm_data.temp * 10 / 16;
	//turn Led on if dT > 10
	if(therm_data.temp-therm_old >= 10 || therm_data.temp-therm_old <= -10){
		Led = 1;
	}
	else{
		Led = 0;
	}
	therm_old = therm_data.temp;
}

