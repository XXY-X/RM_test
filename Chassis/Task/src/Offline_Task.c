#include "Offline_Task.h"

OfflineDetector offline_detector;

void Offline_task(void *pvParameters)
{
    vTaskDelay(pdMS_TO_TICKS(5000)); // 待机器人初始化后开始检测

    while (1)
    {
        // 遥控器
        if (global_debugger.remote_debugger.recv_msgs_num != offline_detector.remote_receive_num)
        {
            offline_detector.remote_state = REMOTE_ON;
            offline_detector.remote_receive_num = global_debugger.remote_debugger.recv_msgs_num;
        }
        else
        {
            offline_detector.remote_state = REMOTE_OFF;
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // 所有数据都应该超过5HZ
    }
}
