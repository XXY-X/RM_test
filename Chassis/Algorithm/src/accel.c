#include "accel.h"

/**
 * @brief  梯形控制
 * @param  反馈；设定；加速度
 * @retval 输出值
 */
float ramp_control(float ref, float set, float accel)
{
    float ramp = LIMIT_MAX_MIN(accel, 1, 0) * (set - ref);
    return ref + ramp;
}
