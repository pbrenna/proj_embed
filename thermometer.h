typedef union int_chars{
	int temp;
	unsigned char raw[2]; 
}int_chars;




extern int_chars therm_data;
extern int therm_old;
void thermometer_read();
void thermometer_save();
