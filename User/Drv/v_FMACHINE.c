#include "v_FMACHINE.h"
#include "v_AppConfig.h"

float gYdelta = 0.f, navAlpha = 1.f;
const float beta1 = .5f, beta2 = .4f, beta3 = .4f;
static uint8_t cur = 0;
static uint32_t brks = 0;
fNode nativeJump(fnode cur, uint16_t *data) {
  if (cur->current == FHALT)
    return (fNode){FHALT, FHALT, {0, 0, 0, 0, 0, 0, 0, 0}};
  if (cur->current == FTARGET) {
    if (cur->nxt)
      ;
    ;
  }
}

void initFMachine(EDC21Player_InstType *ep, Position_InstType *p,
                  JY61_InstType *jy, _Bool carFlag) {
  p->deltaX = ep->pos.x;
  p->deltaY = ep->pos.y;
  p->deltaZ = carFlag * (-90);
  jy->ydelta = carFlag * (-90);
  cur = 0;
  for (int i = 0; i < 10; i++) {
    queue[i] = {0, {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}};
  }
}
void callnext() {}

void bk(node fn, _Bool clear) {
  brks++;
  if (clear) {
    for (int i = 0; i < 10; i++) {
      queue[i] = {0, {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}};
    }
  }
  navFlag = 0;
  setSpeed(motor, &Vehicle, 0, 0, 0);
  queue[(cur + 9) % 10] = fn;
  queue[cur] = cur;
  cur = (cur + 8) % 10;
  callnext();
}

void fHalt(float time, uint32_t brk_o) {
  navFlag = 0;
  setSpeed(motor, &Vehicle, 0, 0, 0);
  fHaltCallback(time, brk_o);
}
void fHaltCallback(float time, uint32_t brk_o) {
  if (time > 0) {
    osDelay((uint16_t)time);
    if (brk_o == brks) {
      callnext();
    }
  }
}

void fSetTarget(float x, float y, float z, float jd, uint32_t brk_o) {
  navFlag = 1;
  setTarget(motor, &Vehicle, x, y, z);
  fSetTargetHandler();
}
void fSetTargetHandler() {
  while (1) {
    float dx = (Vehicle->DeltaX - Vehicle->targetX);
    float dy = (Vehicle->DeltaY - Vehicle->targetY);
    float dz = (Vehicle->DeltaZ - Vehicle->targetZ);
    if (fabs(dx) + fabs(dy) <= jd && fabs(dz) < 2) {
      fSetTargetCallback();
      return;
    }
    osDelay(63);
  }
}
void fSetTargetCallback() {
  navFlag = 0;
  callnext();
}


void htasks(fnode fn) {
  switch (fn->current) {
    case 0:
      fHalt(fn->data[0]);
      break;
    case 1:
      fSetTarget(fn->data[0]);
      break;
    case 3:
      fSetTarget(fn->data[0]);
      break;
      
          FNXTLINE XDIRC YDIRC 3 - FMANLINE XSPEED YSPEED ZSPEED 4 -
          FMANCIR R THETA TIME
  }
}
