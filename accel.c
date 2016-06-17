#include "ev.h"
#include "i2c_machine.h"
#include "c8051f020.h"
#include "accel.h"

__code int lut_arccos[32] = {
	0,
	27,
	54,
	81,
	108,
	135,
	163,
	192,
	220,
	250,
	280,
	310,
	342,
	375,
	410,
	447,
	486,
	528,
	575,
	630,
	696,
	799,
	900,
	900,
	900,
	900,
	900,
	900,
	900,
	900,
	900,
	900	
};


unsigned char buf_index = 0;
__sbit __at(0x90+6) Led;
__code char accel_init_code[] = {0x07,0x01};

void init_accel(){
	i2c_command(ACCEL, accel_init_code, sizeof(accel_init_code), ev_read_axis, I2C_STOP|I2C_WRITE,0,0);
}
__code char axis [] = {0x00};
char axes[BUF_LEN][3];
void read_axis(){
	i2c_command(ACCEL, axis, 1, ev_rcv_axis, I2C_WRITE,0,0);
}

void rcv_axis(){
	Led = STO;
	i2c_command(ACCEL,axis,0,ev_nop, I2C_STOP,3, axes[buf_index++]);
	buf_index = buf_index % BUF_LEN ;
}
