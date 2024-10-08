#ifndef _MECANUM_H
#define _MECANUM_H

#include "accel.h"
#include "math.h"
#include "tools.h"

// 麦克纳姆轮组件

/*  设置CAN ID时 请严格按照如图来设置 ，否则的话，需要更改以下序号 */
/*
||0x201  ||0x202
                -->  右
||0x203  ||0x204

*/
/*
底盘速度运动解算
反馈：x_v 目标:target_v 设置值（可能目标值和设置值有不同的对应关系）：set_v
 解算成wheel_set_v[i],然后得到wheel_set_curent[i]，最后直接对应到控制四个轮子的电流大小
*/




// 以下序号0表示0x201电机
#define LEFT_UP_WHEEL 0    // 左上电机
#define LEFT_DOWN_WHEEL 2  // 左下电机
#define RIGHT_DOWN_WHEEL 3 // 右下电机
#define RIGHT_UP_WHEEL 1   // 右上电机

#define WHEEL_RADIUS 0.06f
#define SPEED_TO_DEGEREE_S 180.0f / WHEEL_RADIUS / PI // 从米/s转到度/s转化
#define DEGEREE_S_TO_MS PI *WHEEL_RADIUS / 180.0f     // 由度/s转到m/s

// 正运动学
void mecanum_pos_kinematics(void);

// 逆运动学
void mecanum_inv_kinematics(void);
// 底盘跟随策略
void mecanum_follow_control(void);

void mecanum_pid_init(void);

#endif
