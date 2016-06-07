#define EV_ENABLE(ev_enum) (ev_flags |= (1 << ev_enum))
#define EV_DISABLE(ev_enum) (ev_flags &= ~(1 << ev_enum))
#define IF_EV(ev_num) if(ev_flags & (1 << ev_num))

extern unsigned long ev_flags;

typedef enum Event {
	ev_ciao,
	ev_thermometer_read,
	ev_thermometer_save,
	ev_init_accel,
	ev_nop
} Event;

void dispatch();

