#include "v_EVENT.h"

void SWout(){
  setTarget(&Vehicle, 500, 2600, -180.f);
  WaitTillFinishByLoc(30.f, 5.f);
  setTarget(&Vehicle, 450, 2350, -180.f);
  WaitTillFinishByLoc(30.f, 5.f);
  setCircle(motor, &Vehicle, 90, 250, 2);
  
  // old version
  /*
  setSpeed(motor, &Vehicle, 500, 0, 0);
  osDelay(500);
  setSpeed(motor, &Vehicle, 0, 0, 0);
  osDelay(200);
  
  setCircle(motor, &Vehicle, -160, -110, 2.5);
  setCircle(motor, &Vehicle, 70, 300, 2);
  */
};

void NEout(){
  setTarget(&Vehicle, 2600, 500, -90.f);
  WaitTillFinishByLoc(30.f, 5.f);
  setTarget(&Vehicle, 2350, 450, -90.f);
  WaitTillFinishByLoc(30.f, 5.f);
  setCircle(motor, &Vehicle, 90, -250, 2);
  
  // old version
  /*
  setSpeed(motor, &Vehicle, 500, 0, 0);
  osDelay(500);
  setSpeed(motor, &Vehicle, 0, 0, 0);
  osDelay(200);
  
  setCircle(motor, &Vehicle, 160, 110, 2.5);
  setCircle(motor, &Vehicle, -70, -300, 2);
  */
};

void ToLeftEntry(_Bool turn) {
  setTarget(&Vehicle, 200, 850, Vehicle.deltaZ);
  WaitTillFinishByLoc(40.f, 5.f);
  if (turn) {
    setTarget(&Vehicle, 200, 850, 0.f);
    WaitTillFinishByLoc(40.f, 5.f);
  }
}

void ToBottomEntry(_Bool turn) {
  setTarget(&Vehicle, 1750, 2350, Vehicle.deltaZ);
  WaitTillFinishByLoc(40.f, 5.f);
  if (turn) {
    setTarget(&Vehicle, 1750, 2350, -90.f);
    WaitTillFinishByLoc(40.f, 5.f);
  }
}

void ToTopEntry(_Bool turn) {
  setTarget(&Vehicle, 850, 200, Vehicle.deltaZ);
  WaitTillFinishByLoc(40.f, 4.f);
  if (turn) {
    setTarget(&Vehicle, 850, 200, 90.f);
    WaitTillFinishByLoc(40.f, 4.f);
  }
}

void ToRightEntry(_Bool turn) {
  setTarget(&Vehicle, 2350, 1750, Vehicle.deltaZ);
  WaitTillFinishByLoc(40.f, 4.f);
  if (turn) {
    setTarget(&Vehicle, 2350, 1750, -180.f);
    WaitTillFinishByLoc(40.f, 4.f);
  }
}

void ToP1() {
  setTarget(&Vehicle, 2300, 2350, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToP2() {
  setTarget(&Vehicle, 2300, 2600, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToP3() {
  setTarget(&Vehicle, 2350, 2300, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToP4() {
  setTarget(&Vehicle, 2600, 2300, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToSWout() {
  setTarget(&Vehicle, 450, 2350, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToNEout() {
  setTarget(&Vehicle, 2350, 450, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToSWgarage() {
  setTarget(&Vehicle, 120, 2600, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToNEgarage() {
  setTarget(&Vehicle, 2600, 120, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
}

void ToCollection() {
  setTarget(&Vehicle, 90, 550, Vehicle.deltaZ);
  WaitTillFinishByLoc(60.f, 6.f);
  setTarget(&Vehicle, 90, 550, -90.f);
  WaitTillFinishByLoc(60.f, 6.f);
  setTarget(&Vehicle, 90, 160, -90.f);
  WaitTillFinishByLoc(60.f, 6.f);
}