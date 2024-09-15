#ifndef _OFFLINE_TASK_H
#define _OFFLINE_TASK_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "debug.h"

enum ROBOT_SENSORS_DETECT
{
    NOT_INIT,  // 未初始化掉线检测
    REMOTE_ON, // 遥控器
    REMOTE_OFF,
};
#pragma pack(1)
typedef struct
{
    int16_t remote_receive_num;

    enum ROBOT_SENSORS_DETECT remote_state;

    int8_t is_sensor_off;  // 是否有关键传感器掉线
    int8_t is_motor_error; // 电机报错检测
} OfflineDetector;
#pragma pack()

void Offline_task(void *pvParameters);

extern OfflineDetector offline_detector;

#endif // !_OFFLINE_TASK_H
