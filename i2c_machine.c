#include "ev.h"
#include "c8051f020.h"

#define SMB_START 0x08
#define SMB_RESTART 0x10
#define SMB_ADDR_NACK 0x20
#define SMB_ADDR_NACK_R 0x48
#define SMB_ADDR_ACK 0x18
#define SMB_ADDR_ACK_R 0x40
#define SMB_DATA_ACK 0x28
#define SMB_DATA_NACK 0x30
#define SMB_DATA_R_ACK 0x50

#define I2C_STOP 0x01
#define I2C_RECV 0x02
#define I2C_WRITE 0x04
#define DISPLAY 0x7C
#define TERM 0
#define ACCEL 0x98

//state variables for i2c receive
char* i2c_return = 0;
unsigned char _i2c_read_len;
unsigned char _i2c_read_index;

//state variables for i2c send
char* _i2c_send_data;
char _i2c_send_addr;
unsigned char _i2c_send_lungh;
unsigned char _i2c_send_index;

//control variables for i2c state machine
bit i2c_lock = 0;
unsigned char _i2c_params;              //TODO: sostituire con 2 bit nudi e crudi?
Event _i2c_callback;            //event to be enabled after stop

void i2c_command(unsigned char addr, char* dati, unsigned char lungh, Event callback, unsigned char params, unsigned char read_len){
	i2c_lock = 1;
	_i2c_callback = callback;
	//STO=1;
	//STO=0;
	_i2c_send_lungh = lungh;
	_i2c_send_index = 0;
	_i2c_send_data = dati;
	_i2c_send_addr = addr;
	_i2c_params = params;
	_i2c_read_len = read_len;
	_i2c_read_index = 0;
	STA=1;
}

void _i2c_stop(){
	if ((_i2c_read_len == 0) & (_i2c_params & I2C_STOP) ){
		STO = 1;
		STA = 0;
		EV_ENABLE(_i2c_callback);
		//tabella_eventi[_i2c_callback] = 1;
	}
	if (_i2c_params & I2C_WRITE) {
		EV_ENABLE(_i2c_callback);
	}
	i2c_lock = 0;
}


void i2c_state_machine(){
	//clear interrupt bit
	switch(SMB0STA) {
	case SMB_RESTART:
	case SMB_START:
		STA = 0;
		STO = 0;
		if (_i2c_params & I2C_WRITE)
			SMB0DAT = _i2c_send_addr & 0xfe;
		else
			SMB0DAT = _i2c_send_addr | 0x01;
		break;
	case SMB_ADDR_NACK_R:
	case SMB_ADDR_NACK:
		STO = 1;
		STA = 1;
		break;
	case SMB_ADDR_ACK_R:
	case SMB_ADDR_ACK:
		//accendi display
		if(_i2c_send_lungh)
			SMB0DAT = _i2c_send_data[0];
		else 
			_i2c_stop();
		break;
	case SMB_DATA_ACK:
		_i2c_send_index = _i2c_send_index +1;
		//missing break: fall through
	case SMB_DATA_NACK:
		//micro_aspetta(wait_time[inst_p]);
		//milli_aspetta(10);
		if (_i2c_send_index < _i2c_send_lungh) {
			SMB0DAT = _i2c_send_data[_i2c_send_index];
		} else {
			_i2c_stop();
		}
		break;
	case SMB_DATA_R_ACK:
		//TODO in realtà sarà un puntatore
		//i2c_return = SMB0DAT;
		STA = 0;
		STO = 1;
		AA = 0;
		//TODO controlla se ha finito di ricevere
		if(0){
			//cose
		}
		EV_ENABLE(_i2c_callback);
		break;
	default:
		break;
	}
}

void i2c_interrupt() interrupt 7 {
	SI = 0;
	EV_ENABLE(ev_i2c_interrupt);
}

unsigned char init_d[] = {0x38,0x39,0x14,0x74,0x54,0x6f,0x0f,0x01};
void init_display(Event callback){
	i2c_command(DISPLAY, init_d, sizeof(init_d), callback,I2C_STOP|I2C_WRITE, 0);
}

void display_write(char* text, unsigned char len,Event callb){
	i2c_command(DISPLAY, text, len, callb, I2C_STOP|I2C_WRITE,0);
}
