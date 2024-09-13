#ifndef _CHASIS_CONTROLLER_H
#define _CHASIS_CONTROLLER_H
//Libraary
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "arm_math.h"
#include "arm_atan2_f32.h"
//工具/功能性外设
#include "tools.h"
#include "counter.h"
#include "ins.h"
#include "user_lib.h"
#include "VOFA.h"
#include "remote_control.h"
#include "pid.h"

#include "wheel_ins.h"

#include "Offline_Task.h"

#include "can_config.h"
#include "TD.h"

#include "SuperPower.h"
#include "PowerLimit.h"
//电机结构
#include "M3508.h"
#include "GM6020.h"
#include "can_send.h"

#include "robot_config.h"
#include "mecanum.h"
/*
主要执行调用电机反馈值解码函数
调用x，y向速度结算成四个轮子的速度以及电流的函数
调用发送set电流给电机的函数
执行函数间的选择调用，非计算
*/
typedef struct Sensors
{
    GM6020_Recv steer_recv[4];//舵原始数据
    GM6020_Info steer_decode[4]; // 解码过后的舵信息,速度未经过滤波
    M3508_Recv wheels_recv[4];//轮原始数据
    M3508_Info wheels_decode[4];     // 速度已经经过滤波
    M3508_Info wheels_decode_raw[4]; // 速度未经过滤波
} Sensors;//电机传感器反馈值结构体

typedef struct ExcuteTorque
{
    int8_t steers_send_data[8];//舵发送数据
    int8_t wheels_send_data[8];//轮发送数据

    float steers_set_current[4];//舵设置电流
    float wheels_set_current[4];//轮设置电流
} ExcuteTorque;//电机设置电流结构体

/* 底盘跟随方向  */
typedef enum
{
    CHASSIS_FRONT = 1,//前
    CHASSIS_BACK = -1,//后
} chassis_direction_e;

typedef struct Infantry
{
    /*  传感器信息 */
    Sensors sensors_info;//电机传感器反馈值

    /*  执行机构 */
    ExcuteTorque excute_info;//执行，映射为给电机的电流值

    /* 移动控制  */
    float target_yaw_v; //旋转轴目标速度 rad/s
    float target_x_v;//x轴目标速度
    float target_y_v;//y轴目标速度

    // 实际控制量
    float set_yaw_v; //映射后的控制量 rad/s
    float set_x_v;
    float set_y_v;

    // 实际速度
    float x_v;//反馈的实际值
    float y_v;
    float yaw_v;

    // 轮电机设定速度
    float wheels_set_v[4];

    uint32_t last_cnt;
    float delta_t; // 前后两帧时间差

    CHASSIS_TYPE chassis_type;//底盘轮子类型
    chassis_direction_e chassis_direction;//底盘跟随方向
    YAW_MOTOR_TYPE yaw_motor_type;// yaw轴电机类型

    // 跟随参数
    float error_angle;

    // 异常检测
    int16_t abnormal_count; // 异常次数计数
    int8_t is_abnormal;     // 是否正在异常状态

    // 转向PID
    PID_t turn_pid;
    float target_pid_yaw_v;

    // 轮控PID
    PID_t wheels_pid[4];
    float wheels_set_current;

    // 舵控PID
    PID_t steers_pid[4];
    float steers_set_current;

    float cos_dir; // 云台与底盘的夹角
    float sin_dir;
} Infantry;//步兵底盘重要结构体，包含控制信息，主要是跟控制相关的量

extern Infantry infantry;

void InfantryInit(Infantry *infantry);
void main_control(Infantry *infantry);//根据运动模式选择底盘运动解算函数
void execute_control(ExcuteTorque *torque);//执行电机控制信息的发送
void get_sensors_info(Sensors *sensors_info);//解码电机的反馈信息

#endif // !_CHASIS_CONTROLLER_H
