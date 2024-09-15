#include "BlueToothTask.h"

BlueToothSendData data;
uint16_t distance = 0;

/**
 * @brief 蓝牙发送debug任务
 * @param[in] void
 */
void BlueToothTask(void *pvParameters)
{
  portTickType xLastWakeTime;

  vTaskDelay(2000);

  while (1)
  {
    xLastWakeTime = xTaskGetTickCount();

    // TOF读取测试
    // distance = readAtkDis();

    /*  延时  */
    vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(20));
  }
}
