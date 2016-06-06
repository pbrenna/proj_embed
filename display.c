#include "ev.h"
#include "i2c_machine.h"
code unsigned char init_d[] = {0x38,0x39,0x14,0x74,0x54,0x6f,0x0f,0x01};
void init_display(Event callback){
	i2c_command(DISPLAY, init_d, sizeof(init_d), callback,I2C_STOP|I2C_WRITE, 0,0);
}

void display_write(char* text, unsigned char len,Event callb){
	i2c_command(DISPLAY, text, len, callb, I2C_STOP|I2C_WRITE,0,0);
}
