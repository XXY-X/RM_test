#include "FrictionWheel.h"

FrictionWheel_t friction_wheels; // 两个摩擦轮

void FrictionWheel_Init()
{
  PID_Init(&friction_wheels.PidFrictionSpeed[LEFT_FRICTION_WHEEL],
           C620_MAX_SEND_CURRENT, 7000.0f, 0, 1.65, 0.003, 0.0, 1000, 1000, 0, 0, 1, ChangingIntegrationRate);
  PID_Init(&friction_wheels.PidFrictionSpeed[RIGHT_FRICTION_WHEEL],
           C620_MAX_SEND_CURRENT, 7000.0f, 0, 1.65, 0.003, 0.0, 1000, 1000, 0, 0, 1, ChangingIntegrationRate);
}

/*  根据机器人等级获得摩擦轮转速 */
void setFrictionSpeed(int8_t shoot_level)
{
  friction_wheels.set_speed_l = BULLET_17MM_26MS_SPEED_L; // 不再限制弹速
  friction_wheels.set_speed_r = BULLET_17MM_26MS_SPEED_R;
}

void FrictionWheel_Set(float speed1, float speed2) // 度/s
{
  friction_wheels.send_to_motor_current[LEFT_FRICTION_WHEEL] =
      PID_Calculate(&friction_wheels.PidFrictionSpeed[LEFT_FRICTION_WHEEL],
                    friction_wheels.friction_motor_msgs[LEFT_FRICTION_WHEEL].speed, speed1);

  friction_wheels.send_to_motor_current[RIGHT_FRICTION_WHEEL] =
      PID_Calculate(&friction_wheels.PidFrictionSpeed[RIGHT_FRICTION_WHEEL],
                    friction_wheels.friction_motor_msgs[RIGHT_FRICTION_WHEEL].speed, speed2);
}
