#include "v_FMACHINE.h"

float gYdelta=0.f,navAlpha=1.f;
const float beta1=.5f,beta2=.4f,beta3=.4f;

float omegaFusion(float omegaGY,float omegaNav){
  if(fabs(omegaNav)<1e-3f||fabs(omegaGY)<1e-3f){
    gYdelta*=1 - beta2;
    gYdelta+=beta2*(0.f-omegaGY);
    return 0.f;
  }
  float omegaOut=beta1*(omegaGY+gYdelta)+(1-beta1)*navAlpha*omegaNav;
  gYdelta*=1 - beta2;
  gYdelta+=beta2*(omegaOut-omegaGY);
  gYdelta*=1 - beta2;
  navAlpha*=1-beta3;
  navAlpha=beta3*omegaOut/omegaNav;
  return omegaOut;
}


fNode nativeJump(fnode cur,uint16_t* data){
  if(cur->current==FHALT) 
    return (fNode){FHALT,FHALT,{0,0,0,0,0,0,0,0}};
  if(cur->current==FTARGET) {
    if(cur-> nxt==;
    ;
  }
}
  