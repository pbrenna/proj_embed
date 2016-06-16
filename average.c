#include "accel.h"
#include "ev.h"
#include "c8051f020.h"
int average[3]={0,0,0};
sbit Led = P1^6;
int orientation(char in){
	if (in & 0x20){
		in = ~(in|0xC0) + 1;
		return -lut_arccos[in];
	}
	return lut_arccos[in];
}

void calc_average(){
	unsigned char pos;
	average[0] = 0;
	average[1] = 0;
	average[2] = 0;
	for (pos = 0; pos < BUF_LEN; pos++) {
		if (pos == (buf_index - 1)%BUF_LEN)
			continue;
		average[0] += orientation(axes[pos][0]);
		average[1] += orientation(axes[pos][1]);
		average[2] += (orientation(axes[pos][2])>0?900:-900) - orientation(axes[pos][2]);
	}
	average[0] = average[0] / (BUF_LEN -1);
	average[1] = average[1] / (BUF_LEN -1);
	average[2] = average[2] / (BUF_LEN -1);
	EV_ENABLE(ev_display_clear);
}
