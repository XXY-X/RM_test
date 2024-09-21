#include "GimbalTask.h"

uint8_t motor_send_data[2][SEND_ID_NUMS][8];
uint8_t is_has_motor_data[2][SEND_ID_NUMS];

SI_t SI_obeject;
SawToothWave saw_tooth_wave;

void Gimbal_Powerdown_Cal()
{
    limitPitchAngle();
    GimbalClear();

    motor_communication[PITCH_MOTOR].control = 0;
    motor_communication[YAW_MOTOR].control = 0;

    // TEST
    // SawToothInit(&saw_tooth_wave, 16.0f, 10, 200, gimbal_controller.gyro_yaw_angle);
}

void Gimbal_Autoaim_Cal()
{
    // 设置目标角度
    if (pc_recv_data.enemy_id != 0 && fabsf(gimbal_controller.target_pitch_angle - pc_recv_data.pitch / 100.0f) < 60.0f && fabsf(gimbal_controller.target_yaw_angle - pc_recv_data.yaw) < 70.0f)
    {
        if (offline_detector.pc_state == PC_ON)
        {
            gimbal_controller.target_pitch_angle = pc_recv_data.pitch / 100.0f;
            gimbal_controller.target_yaw_angle = pc_recv_data.yaw;
        }
    }
    pc_send_data.mode = AUTO_AIM; // 改变发送的模式

    // pitch限制幅值
    limitPitchAngle();
    motor_communication[PITCH_MOTOR].control = Gimbal_Pitch_Calculate(gimbal_controller.target_pitch_angle);

    // yaw计算
    motor_communication[YAW_MOTOR].control = Gimbal_Yaw_Calculate(gimbal_controller.target_yaw_angle);
}

void Gimbal_Small_Buff_Cal()
{
    // 设置目标角度
    if (pc_recv_data.enemy_id != 0 && fabsf(gimbal_controller.target_pitch_angle - pc_recv_data.pitch / 100.0f) < 60.0f && fabsf(gimbal_controller.target_yaw_angle - pc_recv_data.yaw) < 70.0f)
    {
        gimbal_controller.target_pitch_angle = pc_recv_data.pitch / 100.0f;
        gimbal_controller.target_yaw_angle = pc_recv_data.yaw;
    }
    pc_send_data.mode = SMALL_BUFF; // 改变发送的模式

    // pitch限制幅值
    limitPitchAngle();
    motor_communication[PITCH_MOTOR].control = Gimbal_Pitch_Calculate(gimbal_controller.target_pitch_angle);

    // yaw计算
    motor_communication[YAW_MOTOR].control = Gimbal_Yaw_Calculate(gimbal_controller.target_yaw_angle);
}

void Gimbal_Big_Buff_Cal()
{
    // 更新传感器信息
    updateGyro();
    GM6020_Decode(&gimbal_controller.pitch_recv, &gimbal_controller.pitch_info);
    // GM6020_Decode(&gimbal_controller.yaw_recv, &gimbal_controller.yaw_info);

    // 设置目标角度
    if (pc_recv_data.enemy_id != 0 && fabsf(gimbal_controller.target_pitch_angle - pc_recv_data.pitch / 100.0f) < 60.0f && fabsf(gimbal_controller.target_yaw_angle - pc_recv_data.yaw) < 70.0f)
    {
        gimbal_controller.target_pitch_angle = pc_recv_data.pitch / 100.0f;
        gimbal_controller.target_yaw_angle = pc_recv_data.yaw;
    }
    pc_send_data.mode = BIG_BUFF; // 改变发送的模式

    // pitch限制幅值
    limitPitchAngle();
    motor_communication[PITCH_MOTOR].control = Gimbal_Pitch_Calculate(gimbal_controller.target_pitch_angle);

    // yaw计算
    motor_communication[YAW_MOTOR].control = Gimbal_Yaw_Calculate(gimbal_controller.target_yaw_angle);
}

void Gimbal_SI_Cal()
{
}

void Gimbal_Act_Cal()
{
    pc_send_data.mode = 0; // 改变发送的模式

    // pitch限制幅值
    limitPitchAngle();
    motor_communication[PITCH_MOTOR].control = Gimbal_Pitch_Calculate(gimbal_controller.target_pitch_angle);

    // yaw计算
    motor_communication[YAW_MOTOR].control = Gimbal_Yaw_Calculate(gimbal_controller.target_yaw_angle);
}

void Gimbal_Test_Cal()
{
    // pitch限制幅值
    // limitPitchAngle();
    // Gimbal_Pitch_Calculate(gimbal_controller.target_pitch_angle);
    // GM6020_SendPack(dji_motors_send_data, GM6020_STD_VOL_ID_1_4, PITCH_MOTOR_CAN_ID - 0x204, (int16_t)gimbal_controller.set_pitch_vol);

    // yaw计算
    // Gimbal_Yaw_Calculate(SawWaveRun(&saw_tooth_wave, gimbal_controller.delta_t));
    // Gimbal_Speed_Calculate(90.0f);
    // GM6020_SendPack(dji_motors_send_data_2, GM6020_STD_VOL_ID_1_4, YAW_MOTOR_CAN_ID - 0x204, (int16_t)gimbal_controller.set_yaw_vol);
}

void Gimbal_Backturn_Cal()
{
    // pitch限制幅值
    limitPitchAngle();
    Gimbal_Pitch_Calculate(gimbal_controller.target_pitch_angle);
    // GM6020_SendPack(dji_motors_send_data, GM6020_STD_VOL_ID_1_4, PITCH_MOTOR_CAN_ID - 0x204, (int16_t)gimbal_controller.set_pitch_vol);

    // yaw计算
    // Gimbal_Yaw_Calculate(gimbal_controller.target_yaw_angle);
    // GM6020_SendPack(dji_motors_send_data_2, GM6020_STD_VOL_ID_1_4, YAW_MOTOR_CAN_ID - 0x204, (int16_t)gimbal_controller.set_yaw_vol);
}

void Shoot_Powerdown_Cal()
{
    BOMB_BAY_ON;

    // 摩擦轮高速时进行减速
    if (friction_wheels.friction_motor_msgs[LEFT_FRICTION_WHEEL].speed > 6000 || friction_wheels.friction_motor_msgs[RIGHT_FRICTION_WHEEL].speed > 6000)
    {
        FrictionWheel_Set(0, 0);
    }
    // 减小到一定程度后设置为 0
    else
    {
        PID_Clear(&friction_wheels.PidFrictionSpeed[LEFT_FRICTION_WHEEL]);
        PID_Clear(&friction_wheels.PidFrictionSpeed[RIGHT_FRICTION_WHEEL]);

        friction_wheels.send_to_motor_current[LEFT_FRICTION_WHEEL] = 0;
        friction_wheels.send_to_motor_current[RIGHT_FRICTION_WHEEL] = 0;
    }

    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[LEFT_FRICTION_WHEEL];
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[RIGHT_FRICTION_WHEEL];

    // 拨盘电机
    motor_communication[TOGGLE_MOTOR].control = Toggle_Calculate(TOGGLE_STOP, 0.0f);
}

void Shoot_Check_Cal()
{
    // 弹舱盖

    // 拨盘

    // 摩擦轮
}

void Shoot_Fire_Cal()
{
    BOMB_BAY_OFF;

    // 摩擦轮
    setFrictionSpeed(chassis_pack_get_1.bullet_level);
    FrictionWheel_Set(-friction_wheels.set_speed_l, friction_wheels.set_speed_r);
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[LEFT_FRICTION_WHEEL];
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[RIGHT_FRICTION_WHEEL];

    // 拨盘
    // 设置拨盘转动速度
    selectShootFreq(chassis_pack_get_1.robot_level, chassis_pack_get_1.buff_state);

    // PID计算
    if (chassis_pack_get_1.is_shootable && toggle_controller.is_shoot && remote_controller.gimbal_action != GIMBAL_SMALL_BUFF_MODE && remote_controller.gimbal_action != GIMBAL_BIG_BUFF_MODE)
    {
        remote_controller.single_shoot_flag = FALSE; // 连发情况也将单发标志位清零
        motor_communication[TOGGLE_MOTOR].control = Toggle_Calculate(TOGGLE_SPEED, SIGN_ROTATE * toggle_controller.shoot_freq_speed);
    }
    else if (remote_controller.gimbal_action == GIMBAL_SMALL_BUFF_MODE || remote_controller.gimbal_action == GIMBAL_BIG_BUFF_MODE)
    {
        // 大符模式，采用单发模式
        if (remote_controller.single_shoot_flag && chassis_pack_get_1.is_shootable) // 触发单发射击标志
        {
            ToggleAddGrid(&toggle_controller.set_pos, 1);
            remote_controller.single_shoot_flag = FALSE;
        }
        motor_communication[TOGGLE_MOTOR].control = Toggle_Calculate(TOGGLE_POS, toggle_controller.set_pos);
    }
    else
    {
        remote_controller.single_shoot_flag = FALSE; // 不打弹情况将打击标志位清零
        motor_communication[TOGGLE_MOTOR].control = Toggle_Calculate(TOGGLE_SPEED, 0.0f);
    }
}

void Shoot_Test_Cal()
{
    BOMB_BAY_ON;

    // 摩擦轮
    setFrictionSpeed(chassis_pack_get_1.bullet_level);
    FrictionWheel_Set(-2000, 2000);
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[LEFT_FRICTION_WHEEL];
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[RIGHT_FRICTION_WHEEL];

    // 拨盘
    motor_communication[TOGGLE_MOTOR].control = Toggle_Calculate(TOGGLE_SPEED, -150.0f);
}

void Shoot_Autoaim_Cal()
{
    // 弹舱盖

    // 拨盘

    // 摩擦轮
}

void Shoot_Supply_Cal()
{
    BOMB_BAY_ON;

    FrictionWheel_Set(0, 0);
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[LEFT_FRICTION_WHEEL];
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].control = friction_wheels.send_to_motor_current[RIGHT_FRICTION_WHEEL];

    motor_communication[TOGGLE_MOTOR].control = Toggle_Calculate(TOGGLE_SPEED, 0.0f);
}

void Motor_Data_Pack()
{
    memset(is_has_motor_data[0], 0, SEND_ID_NUMS * 2);
    uint8_t can_select = 0;
    for (int i = 0; i < MOTOR_APP_NUMS; i++)
    {
        can_select = motor_communication[i].can == CAN1 ? 0 : 1;
        switch (motor_communication[i].motor_type)
        {
        case GM6020:
            GM6020_SendPack(motor_send_data[can_select][motor_communication[i].motor_id_type], motor_communication[i].std_id, motor_communication[i].motor_id - 0x204, (int16_t)motor_communication[i].control, GM6020_CUR_MODE);
            is_has_motor_data[can_select][motor_communication[i].motor_id_type] = TRUE;
            break;
        case M3508:
            M3508_SendPack(motor_send_data[can_select][motor_communication[i].motor_id_type], motor_communication[i].std_id, motor_communication[i].motor_id - 0x200, motor_communication[i].control, SEND_CURRENT);
            is_has_motor_data[can_select][motor_communication[i].motor_id_type] = TRUE;
            break;
        case M2006:
            M2006_SendPack(motor_send_data[can_select][motor_communication[i].motor_id_type], motor_communication[i].std_id, motor_communication[i].motor_id - 0x200, motor_communication[i].control);
            is_has_motor_data[can_select][motor_communication[i].motor_id_type] = TRUE;
            break;
        case DM_MOTOR:
            if (i == YAW_MOTOR) // 目前仅仅适配yaw轴电机，TODO:适配到所有电机
            {
                DM_Motor_Control(&gimbal_controller.DM_Yaw_Motor, motor_send_data[can_select][motor_communication[i].motor_id_type], DM_MIT_CONTROL);
                is_has_motor_data[can_select][motor_communication[i].motor_id_type] = TRUE;
            }
            break;
        default:
            break;
        }
    }
}

void Motor_Data_Send()
{
    for (int i = 0; i < SEND_ID_NUMS; i++)
    {
        if (is_has_motor_data[0][i])
        {
            CanSend(&hcan1, motor_send_data[0][i], MOTOR_STD_ID_LIST[i], &motor_tx_header[0][i], &motor_wait_time[0][i]);
        }
        if (is_has_motor_data[1][i])
        {
            CanSend(&hcan2, motor_send_data[1][i], MOTOR_STD_ID_LIST[i], &motor_tx_header[1][i], &motor_wait_time[1][i]);
        }
    }
}

void updataSensors()
{
    // 更新传感器信息
    updateGyro();

    // PITCH电机解码  TODO:扩展到所有类型电机
    if (motor_communication[PITCH_MOTOR].motor_type == GM6020)
    {
        GM6020_Decode(&gimbal_controller.pitch_recv, &gimbal_controller.pitch_info);
    }

    // YAW电机解码  TODO:扩展到所有类型电机
    if (motor_communication[YAW_MOTOR].motor_type == GM6020)
    {
        GM6020_Decode(&gimbal_controller.yaw_recv, &gimbal_controller.yaw_info);
    }

    // 摩擦轮电机解码  TODO:扩展到所有类型电机
    if (motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_type == M3508)
    {
        for (int i = 0; i < 2; i++)
        {
            M3508_Decode(&friction_wheels.friction_motor_recv[i], &friction_wheels.friction_motor_msgs[i], ONLY_SPEED, 0.90);
        }
    }

    // 拨盘电机解码 TODO:扩展到所有类型电机
    if (motor_communication[TOGGLE_MOTOR].motor_type == M2006)
    {
        M2006_Decode(&toggle_controller.toggle_recv, &toggle_controller.toggle_info, WITH_REDUCTION, 0.90);
    }
}

/**
 * @brief 云台控制任务
 * @param[in] void
 */
void GimbalTask(void *pvParameters)
{
    portTickType xLastWakeTime;
    const portTickType xFrequency = 1; // 1kHZ

    FrictionWheel_Init();
    GimbalPidInit();
    TogglePidInit();
    DM_Motor_Init(&gimbal_controller.DM_Yaw_Motor, 3.141593f, 10, 30);

    /* 系统辨识以及测试 */
    SIInit(&SI_obeject, 10, 160.0f);
    // SawToothInit(&saw_tooth_wave, 50, 10, 1000, 20);

    vTaskDelay(2000);

    int index = 0;

    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();

        global_debugger.robot_debugger.dt = DWT_GetDeltaT(&global_debugger.robot_debugger.last_cnt);

        // 更新传感器信息
        updataSensors();

        switch (remote_controller.gimbal_action)
        {
        case GIMBAL_POWERDOWN: // 掉电模式
            Gimbal_Powerdown_Cal();
            break;
        case GIMBAL_ACT_MODE: // 云台运动模式
            Gimbal_Act_Cal();
            break;
        case GIMBAL_AUTO_AIM_MODE: // 自瞄模式
            Gimbal_Autoaim_Cal();
            break;
        case GIMBAL_SMALL_BUFF_MODE:
            Gimbal_Small_Buff_Cal();
            break;
        case GIMBAL_BIG_BUFF_MODE:
            Gimbal_Big_Buff_Cal();
            break;
        case GIMBAL_SI_MODE:
            Gimbal_SI_Cal();
            break;
        case GIMBAL_TEST_MODE:
            Gimbal_Test_Cal();
            break;
        default:
            Gimbal_Powerdown_Cal();
            break;
        }

        switch (remote_controller.shoot_action)
        {
        case SHOOT_POWERDOWN_MODE: // 掉电模式
            Shoot_Powerdown_Cal();
            break;
        case SHOOT_CHECK_MODE: // 自检模式
            Shoot_Check_Cal();
            break;
        case SHOOT_FIRE_MODE: // 开火模式
            Shoot_Fire_Cal();
            break;
        case SHOOT_TEST_MODE: // 弹道测试模式
            Shoot_Test_Cal();
            break;
        case SHOOT_AUTO_AIM_MODE: // 自瞄模式
            Shoot_Autoaim_Cal();
            break;
        case SHOOT_SUPPLY_MODE: // 补给模式
            Shoot_Supply_Cal();
            break;
        default:
            Shoot_Powerdown_Cal();
            break;
        }

        Motor_Data_Pack(); // 电机数据打包
        Motor_Data_Send(); // 电机数据发送

        if (index % 4 == 0)
        {
            SendtoPC(); // 将信息发送给上位机
        }
        index++;

        /*  延时  */
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
