//void i2c_command(unsigned char addr, char* dati, unsigned char lungh, Event callback, unsigned char params, unsigned char read_len);
void i2c_state_machine();

void init_display(Event callback);
void display_write(char* text, unsigned char len, Event callb);
