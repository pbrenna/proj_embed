#include "accel.h"
#include "ev.h"
#include "util.h"
#include "c8051f020.h"

#define THRESHOLD 100
unsigned char idle_seconds = 0;
bit idle = 0;
int average[3]={0,0,0};
int old_average[3] = {0,0,0};
int orientation(char in){
	if (in & 0x20){
		in = ~(in|0xC0) + 1;
		return -lut_arccos[in];
	}
	in = in & 0x1f;
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


void check_average(){
	int dx,dy,dz;
	if(idle_seconds > 0){
		dx = average[0]-old_average[0];
		dy = average[1]-old_average[1];
		dz = average[2]-old_average[2];
		if (dx >THRESHOLD || dx < -THRESHOLD || dy >THRESHOLD || dy < -THRESHOLD || dz >THRESHOLD || dz < -THRESHOLD){
			idle_seconds = 0; idle = 0; return;
		}
	}
	memcopy(average, sizeof(average), old_average);
	
	if (idle_seconds  < 5){
		idle_seconds ++; 
		idle = 0;
	} else {
		idle = 1;
	}
		
}
