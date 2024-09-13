#ifndef _GIMBAL_RECEIVE_H
#define _GIMBAL_RECEIVE_H

#include "stdint.h"

#include "remote_control.h"

#pragma pack(push, 1)
/*
云台数据包接收解码，并把各信息赋值到相应变量
*/
typedef struct GimbalReceivePack1//云台接收结构体1，主要是控制相关的状态量
{
  uint16_t robot_state : 1;// 机器人状态(掉线模式0，控制模式1)
  uint16_t control_type : 2;// 控制类型(遥控器0，蓝牙1，键鼠2)
  uint16_t control_mode_action : 4;//0~4  5种控制模式
  uint16_t gimbal_mode : 3;//0~6   7种云台模式
  uint16_t shoot_mode : 3;//0~5   6种打弹模式
  uint16_t _ : 2;//空标志位
  uint16_t is_pc_on : 1;
  uint8_t autoaim_id; // 自瞄ID

  uint8_t __;
  uint8_t cover_state : 1;//弹舱状态
  uint8_t reserved : 7;

  int8_t robot_speed_x; // * 10 描述 x方向为云台正方向
  int8_t robot_speed_y; // * 10描述
  int8_t robot_speed_w;
} GimbalReceivePack1;

typedef struct GimbalReceivePack2 // 云台yaw和pitch角度
{
  int16_t yaw_motor_angle; // 云台yaw轴电机角度
  int16_t gimbal_pitch;    // 底盘
  int16_t gimbal_yaw_speed;
  int16_t super_power;
} GimbalReceivePack2;

#pragma pack(pop)

extern GimbalReceivePack2 gimbal_receiver_pack2;
extern GimbalReceivePack1 gimbal_receiver_pack1;

extern int8_t gimbal_receive_1_update;
extern int8_t gimbal_receive_2_update;

void Gimbal_msgs_Decode1(void);//解码函数
void Gimbal_msgs_Decode2(void);

#define GIMBAL_FOLLOW_DEAD_ANGLE 1.0f
#define SIGN_MOTOR_FOLLOW -1.0f

#endif // !_GIMBAL_RECEIVE_H
