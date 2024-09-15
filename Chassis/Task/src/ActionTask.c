#include "ActionTask.h"

void Action_task(void *pvParameters)
{
    portTickType xLastWakeTime;

    vTaskDelay(2000);

    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();

        Gimbal_msgs_Decode1();//云台数据解码，包含一堆控制状态信息
        Gimbal_msgs_Decode2();//云台数据解码，设置放电方式的（电池电容）

        /*  延时  */
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}
