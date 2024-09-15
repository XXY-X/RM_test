/**
 ******************************************************************************
 * @file    ChasisControlTask.c
 * @brief   底盘控制任务
 ******************************************************************************
 * @attention
 ******************************************************************************
 */

#include "ChasisControlTask.h"

uint8_t cnt;

/**
 * @brief 底盘控制任务
 * @param[in] void
 */
void ChasisControl_task(void *pvParameters)
{
    portTickType xLastWakeTime;

    vTaskDelay(1000);

    infantry.delta_t = GetDeltaT(&infantry.last_cnt);
    InfantryInit(&infantry);

    // SuperPowerInit();

    // 初始化时间差
    infantry.delta_t = GetDeltaT(&infantry.last_cnt);
    vTaskDelay(1);

    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();

        // 获取两帧之间时间差
        infantry.delta_t = GetDeltaT(&infantry.last_cnt);

        get_sensors_info(&infantry.sensors_info);//获取电机编码器的值并解码

        main_control(&infantry);//根据运动模式和电机类型选择相应的运动解算方式，并得到电机设置电流值

        /* 执行控制 */
        execute_control(&infantry.excute_info);//执行控制，通过CAN发送电流信息给电机

        /*  喂狗 */
        xEventGroupSetBits(xCreatedEventGroup, CHASIS_CONTROL_BIT); // 标志位置一

        /*  延时  */
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}
