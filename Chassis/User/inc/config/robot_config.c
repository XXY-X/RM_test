#include "ChasisController.h"

void setRobotType()
{
#if ROBOT == CHEN_JING_YUAN
    infantry.chassis_type = MECANUM_WHEEL;
    infantry.yaw_motor_type = YAW_GM6020;
#endif

    if (infantry.chassis_type == MECANUM_WHEEL)
    {
        mecanum_pid_init();
    }
}
