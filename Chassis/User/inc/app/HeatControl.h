#ifndef _HEAT_CONTROL_H
#define _HEAT_CONTROL_H

#include "Referee.h"

#define ONE_BULLET_HEAT 10
#define HeatControlThreshold 1.0f
#define PredictControlThreshold 0.9f

typedef struct HeatController
{
    int heat_count;//裁判系统给出热量次数
    int shoot_count;//裁判系统给出发射子弹数
    int last_heat_count;  // 上一次更新时的热量次数，热量更新时会更新
    int last_shoot_count; // 上一次更新热量时的发射子弹数

    short HeatMax;  // 热量上限，由裁判系统给出，每次会更新
    short HeatCool; // 枪口冷却，由裁判系统给出，每次会更新
    short CurHeat;  // 当前热量，由裁判系统给出，每次会更新
    short available_heat;//可用热量
    short shoot_num_during_update; // 热量更新中发射数
    short available_shoot;         // 可发射数量
    char heat_update_flag;// 热量更新标志位
    char shoot_flag; // 打击标志位，置1表示可以射击，由热量更新决定
} HeatController;

extern HeatController heat_controller;

void HeatUpdate(void);

#endif // !_HEAT_CONTROL_H
