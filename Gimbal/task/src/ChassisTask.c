#include "ChassisTask.h"

int8_t send_to_chassis_data[2][8];        // 数据
CAN_TxHeaderTypeDef chassis_tx_header[2]; // 传输头
uint32_t chassis_send_wait_time[2];       // 传输等待时间

/**
 * @brief 处理速度数据，将底盘期望速度发送给底盘stm32
 * @param[in] void
 */
void ChassisTask(void *pvParameters)
{
    portTickType xLastWakeTime;
    const portTickType xFrequency = 1; // 1000HZ

    static int i = 0;

    vTaskDelay(6000);

    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();

        if (i % 4 == 0) // 250HZ
        {
            Pack_InfantryMode();

            memcpy(send_to_chassis_data[0], &chassis_send_pack1, 8); // 模式信息

            CanSend(&CHASSIS_CAN_COMM_CAN_Handlerx, send_to_chassis_data[0], SEND_TO_CHASSIS_CAN_ID_1, &chassis_tx_header[0], &chassis_send_wait_time[0]);
        }

        // 1 kHZ
        Pack_Yaw();

        memcpy(send_to_chassis_data[1], &chassis_send_pack2, 8); // yaw轴信息

        CanSend(&CHASSIS_CAN_COMM_CAN_Handlerx, send_to_chassis_data[1], SEND_TO_CHASSIS_CAN_ID_2, &chassis_tx_header[1], &chassis_send_wait_time[1]);

        i++;

        /*  延时  */
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
