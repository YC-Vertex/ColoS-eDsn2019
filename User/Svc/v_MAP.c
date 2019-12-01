#include "v_MAP.h"

#define v_count 36
#define dim 4

int map[v_count + 1][dim + 1] = { 0 };
int parent[2][v_count + 1] = { 0 }, result[3] = { 0 };    //result[0]: length; result[1]: cross_point; result[2]: depth from str to crosp(h_depth in GetRoute())

int query[2][v_count], q_size[2], q_head[2], q_end[2];  //0: Head; 1: Tail;
int visited[2][v_count + 1], t;                         //t: default target


_Bool Route(EDC21Map_InstType * eMap);


void InitMap(EDC21Map_InstType * eMap) {
  for (int i = 0; i < 6*6; ++i) {
    eMap->map[i] = 0x0f;  // 0000 1111
  }
  
  for (int i = 0; i < 6; ++i) {
    eMap->map[0*6+i] &= 0x07;   // 0000 0111 no negY
    eMap->map[5*6+i] &= 0x0b;   // 0000 1011 no posY
    eMap->map[i*6+0] &= 0x0d;   // 0000 1101 no negX
    eMap->map[i*6+5] &= 0x0e;   // 0000 1110 no posX
  }
  
  for (int i = 0; i < 6; ++i) {
    eMap->map[i*7+0] &= 0x09;   // 0000 1001 no negX, posY
  }
  for (int i = 0; i < 5; ++i) {
    eMap->map[i*7+6] &= 0x06;   // 0000 0110 no posX, negY
  }
  
  #ifdef __DEBUG_1__
  // EdcDispMapInfo(eMap);
  #endif
}

_Bool MapHandler(EDC21Map_InstType * eMap) {
  int curP = eMap->curPoint;
  int tarP = eMap->tarPoint;
  if (curP >= 0 && curP <= 35 && tarP >= 0 && tarP <= 35) {
    if (Route(eMap)) {
      // 放在AppLocation.c里面了
      /*
      if (eMap->length == 0) {
        printf(">> Arrive: %d\r\n", eMap->curPoint);
      } else {
        XYPos target = {
          eMap->origin.x + (eMap->route[0] % 6) * 300,
          eMap->origin.y + (eMap->route[0] / 6) * 300
        };
        printf(">> Target: %d (%d %d)\r\n", eMap->route[0], target.x, target.y);
        defaultSetTarget(target.x, target.y, 0);
        WaitTillFinishByLoc(20.f, 2.f);
      }
      */
      return (eMap->length != 0);
    }
    else {
      InitMap(eMap);
      forceUpdate = 1;
      return 0;
    }
  }
  return 0;
}

_Bool UpdateMap(EDC21Map_InstType * eMap, XYPos carPos, int * obs, float angle) {
  const float angleEps = 6.f;
  const int distThres = 600;
  
  _Bool isUpdated = 0;
  
  while (angle > 360) angle -= 360;
  while (angle < 0) angle += 360;
  
  for (int i = 0; i < 4; ++i) {
    if (obs[i] != 0) {
      obs[i] += eMap->delta[i];
    }
  }
  
  if (fabs(angle - 0) < angleEps || fabs(angle - 360) < angleEps) {
    eMap->obs[0] = obs[0];   // posX
    eMap->obs[1] = obs[1];   // negX
    eMap->obs[2] = obs[3];   // posY
    eMap->obs[3] = obs[2];   // negY
  } else if (fabs(angle - 90) < angleEps) {
    eMap->obs[0] = obs[2];   // posX
    eMap->obs[1] = obs[3];   // negX
    eMap->obs[2] = obs[0];   // posY
    eMap->obs[3] = obs[1];   // negY
  } else if (fabs(angle - 180) < angleEps) {
    eMap->obs[0] = obs[1];   // posX
    eMap->obs[1] = obs[0];   // negX
    eMap->obs[2] = obs[2];   // posY
    eMap->obs[3] = obs[3];   // negY
  } else if (fabs(angle - 270) < angleEps) {
    eMap->obs[0] = obs[3];   // posX
    eMap->obs[1] = obs[2];   // negX
    eMap->obs[2] = obs[0];   // posY
    eMap->obs[3] = obs[1];   // negY
  }
  
  for (int i = 0; i < 4; ++i) {
    if (eMap->obs[i] > distThres)
      eMap->obs[i] = 0;
  }
  
  if (eMap->obs[0] != 0) {
    XYPos obsLeft = {carPos.x + eMap->obs[0] - 150 - eMap->origin.x, carPos.y - eMap->origin.y};
    int obsLeftPoint = GetPointIndex(&obsLeft);
    if (obsLeftPoint != -1 && obsLeftPoint % 6 != 5) { // 障碍物左侧点不能是最右边的点
      #ifdef __DEBUG_1__
      printf(">> +OBS: %d %d\r\n", obsLeftPoint, obsLeftPoint + 1);
      #endif
      if ((eMap->map[obsLeftPoint] | 0x01) || (eMap->map[obsLeftPoint+1] | 0x02)) {
        eMap->map[obsLeftPoint] &= 0x0e;    // 0000 1110 posX
        eMap->map[obsLeftPoint+1] &= 0x0d;  // 0000 1101 negX
        isUpdated = 1;
      }
    }
  }
  if (eMap->obs[1] != 0) {
    XYPos obsRight = {carPos.x + eMap->obs[1] + 150 - eMap->origin.x, carPos.y - eMap->origin.y};
    int obsRightPoint = GetPointIndex(&obsRight);
    if (obsRightPoint != -1 && obsRightPoint % 6 != 0) { // 障碍物右侧点不能是最左边的点
      #ifdef __DEBUG_1__
      printf(">> +OBS: %d %d\r\n", obsRightPoint, obsRightPoint - 1);
      #endif
      if ((eMap->map[obsRightPoint] | 0x02) || (eMap->map[obsRightPoint-1] | 0x01)) {
        eMap->map[obsRightPoint] &= 0x0d;    // 0000 1101 negX
        eMap->map[obsRightPoint-1] &= 0x0e;  // 0000 1110 posX
        isUpdated = 1;
      }
    }
  }
  if (eMap->obs[2] != 0) {
    XYPos obsUp = {carPos.x - eMap->origin.x, carPos.y + eMap->obs[2] - 150 - eMap->origin.y};
    int obsUpPoint = GetPointIndex(&obsUp);
    if (obsUpPoint != -1 && obsUpPoint <= 29) { // 障碍物上方点不能是最下方的点
      #ifdef __DEBUG_1__
      printf(">> +OBS: %d %d\r\n", obsUpPoint, obsUpPoint + 6);
      #endif
      if ((eMap->map[obsUpPoint] | 0x04) || (eMap->map[obsUpPoint+6] | 0x08)) {
        eMap->map[obsUpPoint] &= 0x0b;    // 0000 1011 posY
        eMap->map[obsUpPoint+6] &= 0x07;  // 0000 0111 negY
        isUpdated = 1;
      }
    }
  }
  if (eMap->obs[3] != 0) {
    XYPos obsDown = {carPos.x - eMap->origin.x, carPos.y + eMap->obs[3] + 150 - eMap->origin.y};
    int obsDownPoint = GetPointIndex(&obsDown);
    if (obsDownPoint != -1 && obsDownPoint >= 6) { // 障碍物下方点不能是最上方的点
      #ifdef __DEBUG_1__
      printf(">> +OBS: %d %d\r\n", obsDownPoint, obsDownPoint - 6);
      #endif
      if ((eMap->map[obsDownPoint] | 0x08) || (eMap->map[obsDownPoint-6] | 0x04)) {
        eMap->map[obsDownPoint] &= 0x07;    // 0000 0111 negY
        eMap->map[obsDownPoint-6] &= 0x0b;  // 0000 1011 posY
        isUpdated = 1;
      }
    }
  }
  
  if (isUpdated) {
    printf(">> xp%d xn%d yp%d yn%d\r\n", eMap->obs[0], eMap->obs[1], eMap->obs[2], eMap->obs[3]);
  }
  
  return isUpdated;
}

_Bool UpdatePos(EDC21Map_InstType * eMap, XYPos carPos) {
  XYPos car = {carPos.x - eMap->origin.x, carPos.y - eMap->origin.y};
  int index = GetPointIndex(&car);
  if (eMap->curPoint != index) {
    eMap->curPoint = index;
    return 1;
  }
  return 0;
}

int GetPointIndex(XYPos * labyRelPos) {
  int x, y;
  
  if (labyRelPos->x < -100 || labyRelPos->y < -100 || labyRelPos->x > 1900 || labyRelPos->y > 1900)
    return -1;
  
  if (labyRelPos->x % 300 < 150)
    x = labyRelPos->x / 300;
  else
    x = labyRelPos->x / 300 + 1;
  if (labyRelPos->y % 300 < 150)
    y = labyRelPos->y / 300;
  else
    y = labyRelPos->y / 300 + 1;
  return y * 6 + x;
}

void setTargetByPoint(EDC21Map_InstType * eMap, int point) {
  eMap->tarPoint = point;
  eMap->done = 0;
  forceUpdate = 1;
}
void setTargetByPos(EDC21Map_InstType * eMap, XYPos pos) {
  eMap->target = pos;
  pos.x -= eMap->origin.x;
  pos.y -= eMap->origin.y;
  eMap->tarPoint = GetPointIndex(&pos);
  eMap->done = 0;
  forceUpdate = 1;
}

void EdcDispObstacleInfo(EDC21Map_InstType * eMap) {
  printf("Obstacle: ");
  for (int i = 0; i < 4; ++i) {
    printf("%d ", eMap->obs[i]);
  }
  printf("\r\n");
}

void EdcDispMapInfo(EDC21Map_InstType * eMap) {
  printf("Map:\r\n");
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      printf("%x ", eMap->map[i*6+j]);
    }
    printf("\r\n");
  }
}

void EdcDispRouteInfo(EDC21Map_InstType * eMap) {
  printf("Current: %d\t", eMap->curPoint);
  printf("Target: %d\r\n", eMap->tarPoint);
  printf("Route: ");
  for (int i = 0; i < eMap->length; ++i) {
    printf("%d ", eMap->route[i]);
  }
  printf("\r\n");
}



// 以下为内部底层函数

void Init() {
  for (int i = 0; i < v_count + 1; ++i) {
    for (int j = 0; j < dim + 1; ++j) {
      map[i][j] = 0;
    }
  }
  for (int i = 0; i < v_count+1; ++i) {
    parent[0][i] = parent[1][i] = 0;
  }
  result[0] = result[1] = result[2] = 0;
  for (int i = 0; i < v_count; ++i) {
    query[0][i] = query[1][i] = 0;
  }
  q_size[0] = q_size[1] = 0;
  q_head[0] = q_head[1] = 0;
  q_end[0] = q_end[1] = 0;
  memset(visited, 0, 2 * (v_count+1));
  for (int i = 0; i < v_count+1; ++i) {
    visited[0][i] = visited[1][i] = 0;
  }
  t = 0;
}

void BuildMap(uint8_t * edge)
{
    for (int i = 1; i < v_count + 1; i++)
    {
        if (edge[i - 1] & 0x01) {   //right
            map[i][0] = i + 1;    //1-36
            map[i][4] += 1;
        }
        if (edge[i - 1] & 0x02) {   //left
            map[i][1] = i - 1;
            map[i][4] += 1;
        }
        if (edge[i - 1] & 0x04) {   //down
            map[i][2] = i + 6;
            map[i][4] += 1;
        }
        if (edge[i - 1] & 0x08) {   //up
            map[i][3] = i - 6;
            map[i][4] += 1;
        }
    }
}

_Bool BIBFS(int str, int end)
{

  query[0][q_end[0]++] = str;
    q_size[0] += 1;
    query[1][q_end[1]++] = end;
    q_size[1] += 1;
    visited[0][str] = visited[1][end] = 1;
    parent[0][str] = parent[1][end] = -1;

    if (str == end) {
        result[0] = 0;
        result[1] = str;
        result[2] = 0;
        return 1;
    }
    
    while (q_size[0] && q_size[1])
    {
        //Decide Target
        if (q_size[0] > q_size[1])
            t = 1;
        else
            t = 0;

        //Query by Layer
        int num = q_size[t];
        for (int i = 0; i < num; i++) {
            //Get Current Point && Pop it
            int cur = query[t][q_head[t]];
            q_head[t] = (q_head[t] + 1) % 36;
            q_size[t]--;

            //Push Children
            for (int j = 0; j < 4; j++) {
                if (!map[cur][j]) {
                    continue;
                }

                if (visited[t][map[cur][j]]) {
                    continue;
                }
                else {
                    //Record Parent && Depth
                    parent[t][map[cur][j]] = cur;  //parent: 1-36; cur: 1-36;
                    visited[t][map[cur][j]] = visited[t][cur] + 1;
                    //If Intersect?
                    if (visited[!t][map[cur][j]]) {
                        result[0] = visited[t][map[cur][j]] + visited[!t][map[cur][j]] - 2;
                        result[1] = map[cur][j];
                        result[2] = visited[0][map[cur][j]] - 1;
                        return 1;
                    }
                    //Push Child
                    query[t][q_end[t]] = map[cur][j];
                    q_end[t] = (q_end[t] + 1) % 36;
                    q_size[t]++;
                }
            }
        }
    }
    return 0;
}

void GetRoute(int * route, int crosp, int h_depth)
{
    memset(route, -1, 36);
    int head = crosp, tail = parent[1][crosp], h_dp = h_depth - 1, t_dp = result[0] - h_depth + 1, depth = result[0];
    while (h_dp > 0) {
        route[h_dp--] = head - 1;
        head = parent[0][head];
    }

    while (t_dp > 0) {
        route[depth - t_dp + 1] = tail - 1;
        tail = parent[1][tail];
        t_dp--;
    }

    route[0] = head - 1;
}

_Bool Route(EDC21Map_InstType * eMap) //"+1 Job" Finished Here
{
  int curP = eMap->curPoint;
  int tarP = eMap->tarPoint;
  if (curP == tarP || curP == -1 || tarP == -1) {
    if (curP == tarP) eMap->done = 1;
    eMap->length = 0;
    eMap->route[0] = -1;
    return 1;
  }
  eMap->done = 0;
  Init();
  
  BuildMap(eMap->map);
  if (BIBFS(curP + 1, tarP + 1)) {
    GetRoute(eMap->route, result[1], result[2]);
    eMap->length = result[0];
    return 1;
  } else {
    eMap->route[0] = -1;
    eMap->length = 0;
    return 0;
  }
}
