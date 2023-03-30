
typedef void(*FP)(void);

extern int e_current_state, e_previous_state, e_next_state;

extern FP e_fpLoad, e_fpInitialize, e_fpUpdate, e_fpDraw, e_fpFree, e_fpUnload;

void GSM_Initialize(int startingState);

void GSM_Update();
