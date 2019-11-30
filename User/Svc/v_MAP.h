#ifndef _V_MAP__H_
#define _V_MAP__H_

#include "main.h"
#include "v_MOTION.h"

typedef struct EDC21Map_InstType {
  uint8_t * name;
  
  uint8_t map[6*6];
  int route[36];
  int length;
  
  int curPoint;
  XYPos target;
  int tarPoint;
  
  XYPos origin;   // origin of the labyrinth
  int delta[4];   // +, -, <, >
  int obs[4];     // posX, negX, posY, negY
  
  _Bool done;
} EDC21Map_InstType;

extern _Bool forceUpdate;

// 建图相关
void InitMap(EDC21Map_InstType * eMap);
_Bool MapHandler(EDC21Map_InstType * eMap);
_Bool UpdateMap(EDC21Map_InstType * eMap, XYPos carPos, int * obs, float angle);
_Bool UpdatePos(EDC21Map_InstType * eMap, XYPos carPos);
void setTargetByPoint(EDC21Map_InstType * eMap, int point);
void setTargetByPos(EDC21Map_InstType * eMap, XYPos pos);
void EdcDispObstacleInfo(EDC21Map_InstType * eMap);
void EdcDispMapInfo(EDC21Map_InstType * eMap);
void EdcDispRouteInfo(EDC21Map_InstType * eMap);

int GetPointIndex(XYPos * labyRelPos);

#endif