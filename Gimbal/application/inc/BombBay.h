#ifndef _BOMB_BAY_H
#define _BOMB_BAY_H

// #define BOMBBAY_SERVOS_ON_POS 1200 //弹舱盖舵机打开位置
// #define BOMBBAY_SERVOS_OFF_POS 470 //弹舱盖舵机关闭位置

#define BOMBBAY_SERVOS_ON_POS 700   //弹舱盖舵机打开位置
#define BOMBBAY_SERVOS_OFF_POS 3050 //弹舱盖舵机关闭位置

void BombBay_Set(int position);//设置弹舱位置，有以上两个值对应打开和关闭

#define BOMB_BAY_ON BombBay_Set(BOMBBAY_SERVOS_ON_POS);//宏定义，调用更优美
#define BOMB_BAY_OFF BombBay_Set(BOMBBAY_SERVOS_OFF_POS);

enum BOMB_BAY_STATE
{
    BOMB_BAY_COVER_ON,
    BOMB_BAY_COVER_OFF
};

extern enum BOMB_BAY_STATE bomb_bay_state;//弹舱状态

#endif
