CC = sdcc 
CFLAGS = -c --model-small --opt-code-size
exe = main
objects = main.rel ev.rel i2c_machine.rel thermometer.rel accel.rel display.rel timer.rel util.rel average.rel init.rel


$(exe): $(objects)
	sdcc $(objects) -o main 

%.rel: %.c
	$(CC) $(CFLAGS) $<
	

clean:
	rm -f *.rel;\
	rm -f *.LST;\
	rm -f *.OBJ;\
	rm -f *.o;  \
	rm -f *.sym;\
	rm -f *.lst;\
	rm -f *.obj;\
	rm -f *.asm;\
	rm -f *.plg;\
	rm -f *.map;\
	rm -f *.mem;\
	rm -f *.lk; \
	rm -f *.rst;\
	rm -f *.lnp;\
	rm -f *.M51;

