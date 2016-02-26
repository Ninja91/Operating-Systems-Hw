extern int32 lab2flag;
extern uint32 prctxswintime;
extern uint32 prcpumin;

void app_unlim(void);
void app_lim(void);
void app_sleep(void);
void lab2q3t1(void);
void lab2q4t1(void);
void lab2q4t2(void);
void lab2q4t3(void);
void lab2q5t1(void);

void cpubound(int32, int32);
void iobound(int32, int32, int32);

#define LAB2_HEADER
#define MIN(a,b) (((a) <= (b)) ? (a) : (b))
#define MAX(a,b) (((a) >= (b)) ? (a) : (b))
