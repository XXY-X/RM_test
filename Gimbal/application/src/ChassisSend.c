#include "ChassisSend.h"

ChassisSendPack1 chassis_send_pack1;
ChassisSendPack2 chassis_send_pack2;

void Pack_InfantryMode()//打包发送数据包1，包含各种模式和状态
{
  chassis_send_pack1.robot_state = remote_controller.robot_state;
  chassis_send_pack1.control_type = remote_controller.control_type;
  chassis_send_pack1.control_mode_action = remote_controller.control_mode_action;
  chassis_send_pack1.gimbal_mode = remote_controller.gimbal_action;
  chassis_send_pack1.shoot_mode = remote_controller.shoot_action;
  chassis_send_pack1.is_pc_on = offline_detector.pc_state == PC_ON;
  chassis_send_pack1.autoaim_id = pc_recv_data.enemy_id;

  chassis_send_pack1.cover_state = bomb_bay_state;

  chassis_send_pack1.robot_speed_x = (int8_t)(chassis_solver.chassis_speed_x * 10.0f);
  chassis_send_pack1.robot_speed_y = (int8_t)(chassis_solver.chassis_speed_y * 10.0f);
  chassis_send_pack1.robot_speed_w = (int8_t)(chassis_solver.chassis_speed_w * 10.0f);
}

void Pack_Yaw()//打包发送数据包2，主要包含云台yaw和pitch角度
{
  chassis_send_pack2.yaw_motor_angle = gimbal_controller.yaw_recv.angle;
  chassis_send_pack2.gimbal_pitch = (int16_t)(gimbal_controller.gyro_pitch_angle * 100.0f);
  chassis_send_pack2.gimbal_yaw_speed = (int16_t)(gimbal_controller.gyro_yaw_speed * 100.0f);
  chassis_send_pack2.super_power = remote_controller.super_power_state;
}
