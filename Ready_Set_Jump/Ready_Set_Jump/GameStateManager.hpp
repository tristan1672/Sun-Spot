
typedef void(*FP)(void);

extern int current, previous, next;

extern FP e_fpLoad, e_fpInitialize, e_fpUpdate, e_fpDraw, e_fpFree, e_fpUnload;

void GSM_Initialize(int startingState);

void GSM_Update();
