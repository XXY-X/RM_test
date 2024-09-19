#include "can_send_config.h"

// 发送结构体配置(注意不影响接收)
Motor_Communication motor_communication[MOTOR_APP_NUMS];

void Motor_Config_Init()
{
#if ROBOT == CHEN_JING_YUAN
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].can = CAN2;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_id = 0x201;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_id_type = DJI_0x200;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_type = M3508;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x200]; // 发送ID

    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].can = CAN2;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].motor_id = 0x202;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].motor_id_type = DJI_0x200;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].motor_type = M3508;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x200];

    motor_communication[PITCH_MOTOR].can = CAN2;
    motor_communication[PITCH_MOTOR].motor_id = 0x207;
    motor_communication[PITCH_MOTOR].motor_id_type = DJI_0x1FF;
    motor_communication[PITCH_MOTOR].motor_type = GM6020;
    motor_communication[PITCH_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x1FF];

    motor_communication[YAW_MOTOR].can = CAN1;
    motor_communication[YAW_MOTOR].motor_id = 0x205;
    motor_communication[YAW_MOTOR].motor_id_type = DJI_0x1FF;
    motor_communication[YAW_MOTOR].motor_type = GM6020;
    motor_communication[YAW_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x1FF];

    motor_communication[TOGGLE_MOTOR].can = CAN1;
    motor_communication[TOGGLE_MOTOR].motor_id = 0x204;
    motor_communication[TOGGLE_MOTOR].motor_id_type = DJI_0x200;
    motor_communication[TOGGLE_MOTOR].motor_type = M2006;
    motor_communication[TOGGLE_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x200];
#elif ROBOT == NIU_MO_SON
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].can = CAN2;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_id = 0x201;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_id_type = DJI_0x200;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].motor_type = M3508;
    motor_communication[LEFT_FRICTION_WHEEL_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x200]; // 发送ID

    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].can = CAN2;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].motor_id = 0x202;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].motor_id_type = DJI_0x200;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].motor_type = M3508;
    motor_communication[RIGHT_FRICTION_WHEEL_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x200];

    motor_communication[PITCH_MOTOR].can = CAN2;
    motor_communication[PITCH_MOTOR].motor_id = 0x207;
    motor_communication[PITCH_MOTOR].motor_id_type = DJI_0x1FE;
    motor_communication[PITCH_MOTOR].motor_type = GM6020;
    motor_communication[PITCH_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x1FE];

    motor_communication[YAW_MOTOR].can = CAN1;
    motor_communication[YAW_MOTOR].motor_id = 0x205;
    motor_communication[YAW_MOTOR].motor_id_type = DJI_0x1FE;
    motor_communication[YAW_MOTOR].motor_type = GM6020;
    motor_communication[YAW_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x1FE];

    motor_communication[TOGGLE_MOTOR].can = CAN1;
    motor_communication[TOGGLE_MOTOR].motor_id = 0x204;
    motor_communication[TOGGLE_MOTOR].motor_id_type = DJI_0x200;
    motor_communication[TOGGLE_MOTOR].motor_type = M2006;
    motor_communication[TOGGLE_MOTOR].std_id = MOTOR_STD_ID_LIST[DJI_0x200];
#endif
}