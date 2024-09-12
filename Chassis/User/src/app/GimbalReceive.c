/**
 ******************************************************************************
 * @file    Judge.c
 * @brief   云台数据接收
 ******************************************************************************
 * @attention
 ******************************************************************************
 */

#include "GimbalReceive.h"
#include "ChasisController.h"

GimbalReceivePack1 gimbal_receiver_pack1;
GimbalReceivePack2 gimbal_receiver_pack2;
int8_t gimbal_receive_1_update; // 更新标志，说明收到了一帧消息
int8_t gimbal_receive_2_update;
int8_t gimbal_receive_3_update;
int16_t jump_up_cnt = 0;

float transition_mode_counter; // 计时器

void Gimbal_msgs_Decode1()//解码数据并设置模式
{
    enum ROBOT_STATE robot_state = (enum ROBOT_STATE)gimbal_receiver_pack1.robot_state;
    enum CONTROL_TYPE contro_type = (enum CONTROL_TYPE)gimbal_receiver_pack1.control_type;
    enum CONTROL_MODE_ACTION control_mode_action = (enum CONTROL_MODE_ACTION)gimbal_receiver_pack1.control_mode_action;
    enum GIMBAL_ACTION gimbal_action = (enum GIMBAL_ACTION)gimbal_receiver_pack1.gimbal_mode;
    enum SHOOT_ACTION shoot_action = (enum SHOOT_ACTION)gimbal_receiver_pack1.shoot_mode;

    setRobotState(robot_state);
    setControlMode(contro_type);
    setControlModeAction(control_mode_action);
    setGimbalAction(gimbal_action);
    setShootAction(shoot_action);

//    infantry.target_yaw_v = gimbal_receiver_pack1.robot_speed_w / 10.0f;
    infantry.target_y_v = gimbal_receiver_pack1.robot_speed_y / 10.0f;
    infantry.target_x_v = gimbal_receiver_pack1.robot_speed_x / 10.0f;
    remote_controller.cover_state = gimbal_receiver_pack1.cover_state;
}

void Gimbal_msgs_Decode2()
{
    enum PowerControlState power_state = (enum PowerControlState)gimbal_receiver_pack2.super_power;

    setSuperPower(power_state);
}
