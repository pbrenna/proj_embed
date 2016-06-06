void i2c_command(unsigned char addr,
                 char* dati,
								 unsigned char lungh,
								 Event callback,
								 unsigned char params,
								 unsigned char read_len,
								 char*);
void i2c_state_machine();
extern bit i2c_lock;

void init_display(Event callback);
void display_write(char* text, unsigned char len, Event callb);

#define I2C_STOP 0x01
#define I2C_RECV 0x02
#define I2C_WRITE 0x04
#define DISPLAY 0x7C
#define TERM 0
#define ACCEL 0x98