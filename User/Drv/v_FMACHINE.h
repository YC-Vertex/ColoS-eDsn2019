#ifndef _V_FMACHINE__H_
#define _V_FMACHINE__H_
#include "main.h"
#define FHALT 0
#define FTARGET 1
#define FMANLINE 2
#define FMANCIR 3

typedef struct fNode fNode;
typedef struct fNode *fnode;

/**************************************
* current:
* 0 - FHALT
* 1 - FTARGET TARX TARY TARZ
* 1 - FLTL R NXTX NXTY NXTZ
* 2 - FNXTLINE XDIRC YDIRC
* 3 - FMANLINE XSPEED YSPEED ZSPEED
* 4 - FMANCIR R THETA SPEED
**************************************/
struct fNode{
  uint16_t current,nxt;
  uint16_t data[8];
};  

float omegaFusion(float omega1,float omega2);

fNode nextJump(fnode cur,uint16_t* data);

void FMachineHandler(void);



#endif
