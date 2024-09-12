#include "ChasisController.h"

Infantry infantry;

void InfantryInit(Infantry *infantry)
{
}

/**
 * @brief  转角限制到±180度
 * @param  输入转角
 * @retval 输出转角
 */
float limit_pi(float in)
{
    while (in < -180.0f || in > 180.0f)
    {
        if (in < -180.0f)
            in = in + 360.0f;
        if (in > 180.0f)
            in = in - 360.0f;
    }
    return in;
}

/**
 * @brief  底盘方向偏差获取
 * @param  目标方向(单位为角度)
 * @retval 方向偏差
 */
float angle_z_err_get(float target_ang, float zeros_angle)
{
    // 不同电机的计算不一样，但要保证最终的输出error_angle定义一致
    if (infantry.yaw_motor_type == YAW_GM6020)
    {
        float AngErr_front, AngErr_back;
        AngErr_front = limit_pi(zeros_angle / 22.755555556f - target_ang);
        AngErr_back = limit_pi((zeros_angle + 4096) / 22.755555556f - target_ang);
        if (fabs(AngErr_front) > fabs(AngErr_back))
        {
            infantry.chassis_direction = CHASSIS_BACK;
            return AngErr_back;
        }
        else
        {
            infantry.chassis_direction = CHASSIS_FRONT;
            return AngErr_front;
        }
    }
    return 0;
}

// 获取控制方向
void getDir()
{
    if (infantry.yaw_motor_type == YAW_GM6020)
    {
        // 计算与正对情况的夹角，22.755555556f = 8192 / 360.0f，结果转弧度
        float AngErr_front = limit_pi(GIMBAL_FOLLOW_ZERO / 22.755555556f - gimbal_receiver_pack2.yaw_motor_angle / 22.755555556f) * ANGLE_TO_RAD_COEF;
        infantry.sin_dir = arm_sin_f32(AngErr_front);
        infantry.cos_dir = arm_cos_f32(AngErr_front);
    }
}

void get_sensors_info(Sensors *sensors_info)//反馈信息解码
{
    if (infantry.chassis_type == STEER_WHEEL)//舵轮
    {
        for (int i = 0; i < 4; i++)
        {
            // 舵电机解码，速度没经过滤波
            GM6020_Decode(&sensors_info->steer_recv[i], &sensors_info->steer_decode[i]);

            // 轮电机解码
            M3508_Decode(&sensors_info->wheels_recv[i], &sensors_info->wheels_decode[i], ONLY_SPEED_WITH_REDUCTION, 0.9);
            M3508_Decode(&sensors_info->wheels_recv[i], &sensors_info->wheels_decode_raw[i], ONLY_SPEED_WITHOUT_FILTER_WITH_REDU, 0.9);
        }
    }
    // 麦轮和全向轮无舵向电机
    else if (infantry.chassis_type == MECANUM_WHEEL || infantry.chassis_type == OMNI_WHEEL)
    {
        for (int i = 0; i < 4; i++)
        {
            M3508_Decode(&sensors_info->wheels_recv[i], &sensors_info->wheels_decode[i], ONLY_SPEED_WITH_REDUCTION, 0.9);
            M3508_Decode(&sensors_info->wheels_recv[i], &sensors_info->wheels_decode_raw[i], ONLY_SPEED_WITHOUT_FILTER_WITH_REDU, 0.9);
        }
    }

    infantry.error_angle = angle_z_err_get(gimbal_receiver_pack2.yaw_motor_angle / 22.755555556f, GIMBAL_FOLLOW_ZERO) * ANGLE_TO_RAD_COEF;
    getDir();
}

void chassis_powerdown_control(Infantry *infantry)//掉电
{
    infantry->set_x_v = 0;
    infantry->set_y_v = 0;
    infantry->set_yaw_v = 0;

    for (int i = 0; i < 4; i++)
    {
        infantry->excute_info.steers_set_current[i] = 0;
        infantry->excute_info.wheels_set_current[i] = 0;
    }
}

void chassis_follow_control(Infantry *infantry)//跟随模式
{
    switch (infantry->chassis_type)
    {
    case MECANUM_WHEEL:
        mecanum_follow_control();
        break;
    default:
        break;
    }
}

void main_control(Infantry *infantry)
{
    switch (remote_controller.control_mode_action)
    {
    case FOLLOW_GIMBAL:
        chassis_follow_control(infantry);
        break;

    default:
        chassis_powerdown_control(infantry);
        break;
    }
}

void execute_control(ExcuteTorque *torque)
{
    // 舵
    if (infantry.chassis_type == STEER_WHEEL)
    {
        GM6020_SendPack(torque->steers_send_data, GM6020_STD_CUR_ID_1_4, DJI_6020_MOTORS_1 - 0x204, (int16_t)torque->steers_set_current[0], GM6020_CUR_MODE);
        GM6020_SendPack(torque->steers_send_data, GM6020_STD_CUR_ID_1_4, DJI_6020_MOTORS_2 - 0x204, (int16_t)torque->steers_set_current[1], GM6020_CUR_MODE);
        GM6020_SendPack(torque->steers_send_data, GM6020_STD_CUR_ID_1_4, DJI_6020_MOTORS_3 - 0x204, (int16_t)torque->steers_set_current[2], GM6020_CUR_MODE);
        GM6020_SendPack(torque->steers_send_data, GM6020_STD_CUR_ID_1_4, DJI_6020_MOTORS_4 - 0x204, (int16_t)torque->steers_set_current[3], GM6020_CUR_MODE);
        // CanSend(DJI_STEERS_CAN, torque->steers_send_data, GM6020_STD_ID_1_4, 8);

        // 轮
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_1 - 0x200, torque->wheels_set_current[0], SEND_CURRENT);
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_2 - 0x200, torque->wheels_set_current[1], SEND_CURRENT);
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_3 - 0x200, torque->wheels_set_current[2], SEND_CURRENT);
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_4 - 0x200, torque->wheels_set_current[3], SEND_CURRENT);
        // CanSend(DJI_WHEELS_CAN, torque->wheels_send_data, C620_STD_ID_1_4, 8);
    }
    else if (infantry.chassis_type == MECANUM_WHEEL || infantry.chassis_type == OMNI_WHEEL)
    {
        // 轮
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_1 - 0x200, torque->wheels_set_current[0], SEND_CURRENT);
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_2 - 0x200, torque->wheels_set_current[1], SEND_CURRENT);
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_3 - 0x200, torque->wheels_set_current[2], SEND_CURRENT);
        M3508_SendPack(torque->wheels_send_data, C620_STD_ID_1_4, DJI_3508_MOTORS_4 - 0x200, torque->wheels_set_current[3], SEND_CURRENT);
        CanSend(DJI_WHEELS_CAN, torque->wheels_send_data, C620_STD_ID_1_4, 8);
    }
}
