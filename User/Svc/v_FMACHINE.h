#ifndef _V_FMACHINE__H_
#define _V_FMACHINE__H_
#include "main.h"
#include "v_MOTION.h"
#include "v_EDC21.h"
#include "v_JY61.h"
#define FHALT 0
#define FTARGET 1
#define FMANLINE 2
#define FMANCIR 3

typedef struct fNode fNode;
typedef struct fNode *fnode;

/**************************************
* current:
* 0 - FHALT TIME?
* 1 - FTARGET TARX TARY TARZ
* 1 - FLTL R NXTX NXTY NXTZ
* 2 - FNXTLINE XDIRC YDIRC
* 3 - FMANLINE XSPEED YSPEED ZSPEED
* 4 - FMANCIR R THETA TIME
**************************************/
struct fNode{
  uint8_t current;
  float data[8];
};
extern fnode* queue;

float omegaFusion(float omega1,float omega2);

fNode nextJump(fnode cur,uint16_t* data);

void FMachineHandler(void);



#endif
