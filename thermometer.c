#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "util.h"
#include "c8051f020.h"

int therm_old = 0;
sbit Led = P1^6;

int_chars therm_data;
code char magia[] = {0x08, 0x40, 0x50, 0x50};
void thermometer_read(){
	i2c_command(TERM,magia,4, ev_thermometer_save, I2C_STOP, 2, therm_data.raw);
}
char disp_temp[] = "@        ";
void thermometer_save(){
	therm_data.temp = therm_data.temp >> 3;
	if(therm_data.raw[0] & 0x10)
		therm_data.raw[0] |= 0xF0;
	therm_data.temp = therm_data.temp * 10 / 16;
	if(therm_data.temp-therm_old >= 10 || therm_data.temp-therm_old <= -10){
		Led = 1;
	}
	else{
		Led = 0;
	}
	therm_old = therm_data.temp;
	//len = num2string(therm_data.temp,0, disp_temp+2);
	/*num2string(therm_data.temp%10, disp_temp + 2+len);
	disp_temp[2+len]='.';
	disp_temp[4+len]='`';
	disp_temp[5+len]='C';*/
	//display_write(disp_temp,9,ev_nop);
}

