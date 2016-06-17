#include "ev.h"
#include "i2c_machine.h"
#include "thermometer.h"
#include "util.h"
#include "average.h"
code unsigned char init_d[] = {0x38,0x39,0x14,0x74,0x54,0x6f,0x0f,0x01};
unsigned char gotoaddr_command[] = {0x80, 0};
code unsigned char clear_command[] = {0x80,0x01};
void init_display(Event callback){
	i2c_command(DISPLAY, init_d, sizeof(init_d), callback,I2C_STOP|I2C_WRITE, 0,0);
}

void display_write(char* text, unsigned char len,Event callb){
	i2c_command(DISPLAY, text, len, callb, I2C_STOP|I2C_WRITE, 0, 0);
}

/*void display_go_to_addr(unsigned char addr, Event callb){
	gotoaddr_command[1] = addr | 0x80;
	i2c_command(DISPLAY, gotoaddr_command, 2, callb, I2C_STOP|I2C_WRITE, 0, 0);
}
*/
void display_clear(Event callb){
	//clears display and moves cursor to address 0
	i2c_command(DISPLAY, clear_command, sizeof(clear_command),
	            callb, I2C_STOP|I2C_WRITE, 0, 0);
}

char _display_string[] = "@T=       X     Y     Z      ";
void display_write_data(){
	num2string(therm_old, 1, _display_string+3);
	num2string(average[0], 1, _display_string+11);
	num2string(average[1], 1, _display_string+17);
	num2string(average[0], 1, _display_string+23);
	display_write(_display_string, sizeof(_display_string), ev_nop); 
}

