#ifndef _GIMBAL_H
#define _GIMBAL_H

#include "pid.h"
#include "GM6020.h"
#include "ins_task.h"
#include "DM_Motor.h"

#include "my_filter.h"
#include "TD.h"
#include "bsp_dwt.h"

#include "gimbal_config.h"

typedef struct GimbalController
{
    // Pitch 轴
    PID_t pitch_current_pid;           // 电流环
    PID_t pitch_speed_pid;             // 速度环
    PID_t pitch_angle_pid;             // 角度环
    Feedforward_t pitch_speed_forward; // 速度环前馈
    Feedforward_t pitch_angle_forward; // 角度环前馈

    GM6020_Recv pitch_recv;//接收的原始数据
    GM6020_Info pitch_info;//解码后的信息
    GM6020_Recv yaw_recv;
    GM6020_Info yaw_info;

    float set_pitch_speed;
    float set_pitch_current;
    float set_pitch_angle;
    float set_pitch_vol;
    float comp_pitch_current; // 重力补偿

    // 陀螺仪信息及其解算
    float gyro_pitch_speed;
    float gyro_pitch_angle;
    float gyro_last_pitch_angle;
    uint32_t last_cnt;
    float delta_t; // 两帧计算之间的时间差

    float target_pitch_angle; // 设定的角度值

    // Yaw在底盘控制
    // // Yaw 轴
    PID_t yaw_current_pid;           // 电流环
    PID_t yaw_speed_pid;             // 速度环
    PID_t yaw_angle_pid;             // 角度环
    Feedforward_t yaw_speed_forward; // 速度环前馈
    Feedforward_t yaw_angle_forward; // 角度环前馈
    // GM6020_Recv yaw_recv;
    // GM6020_Info yaw_info; // 电机信息
    DM_MIT DM_Yaw_Motor;

    float set_yaw_speed;
    float set_yaw_current;
    float set_yaw_angle;
    float set_yaw_vol;

    // 陀螺仪信息及其解算
    float gyro_yaw_speed;
    float gyro_yaw_angle;
    float gyro_last_yaw_angle;

    float target_yaw_angle;

    TD_t pos_yaw_td; // 位置跟踪微分器
    TD_t speed_yaw_td;

    // pitch 限位计算
    float pitch_max_gyro_angle;
    float pitch_min_gyro_angle;
} GimbalController;

extern GimbalController gimbal_controller;

void GimbalPidInit(void);//初始化PID参数
void GimbalClear(void);//清除PID遗留值
void updateGyro(void);//更新陀螺仪信息

// pitch
void limitPitchAngle(void);//限制角度
float GimbalPitchComp(void);//重力补偿
float Gimbal_Pitch_Calculate(float set_point);//计算输出值

// Yaw
float Gimbal_Yaw_Calculate(float set_point);//计算输出值
float Gimbal_Speed_Calculate(float set_point);//计算输出值
float GimbalFrictionModel(void);//云台摩擦力模型

#endif // !_GIMBAL_H
