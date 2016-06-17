void init_accel();
void read_axis();
void rcv_axis();
#define BUF_LEN 7
extern char axes[BUF_LEN][3];
extern unsigned char buf_index;
extern __code int lut_arccos[32];
