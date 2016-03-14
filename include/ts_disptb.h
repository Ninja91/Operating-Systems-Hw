#define NOF_PRIOIRITIES 20

struct ts_disptb {
    int ts_tqexp;
    int ts_slpret;
    int ts_quantum;
};

extern struct ts_disptb tsdtab[NOF_PRIOIRITIES];
