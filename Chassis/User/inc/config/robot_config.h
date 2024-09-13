#ifndef _ROBOT_CONFIG_H
#define _ROBOT_CONFIG_H
/*
车的各电机类型设置
*/
/*  机器人宏定义列举 */
#define NIU_MO_SON 0
#define CHEN_JING_YUAN 1

#define ROBOT CHEN_JING_YUAN

typedef enum CHASSIS_TYPE
{
    STEER_WHEEL,   // 舵轮
    MECANUM_WHEEL, // 麦克纳姆轮
    OMNI_WHEEL,    // 全向轮
} CHASSIS_TYPE;

// 麦轮参数
#define MECANUM_WIDTH 0.4  // 麦轮宽
#define MECANUM_LENGTH 0.6 // 麦轮长

// yaw轴电机类型
typedef enum YAW_MOTOR_TYPE
{
    YAW_GM6020,
    YAW_DM_MOTOR
} YAW_MOTOR_TYPE;

#define GIMBAL_FOLLOW_ZERO 2007 // 底盘跟随机械零点
#define GIMBAL_MOTOR_SIGN -1    // 云台电机方向，以逆时针为正

void setRobotType(void);

#endif
