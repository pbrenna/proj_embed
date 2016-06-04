#define EV_ENABLE(ev_enum) ev_flags |= (1 << ev_enum)
#define IF_EV(ev_num) if(ev_flags & (1 << ev_num))

extern unsigned long ev_flags;

typedef enum Event {
	event1,
	event2,
	event3
} Event;