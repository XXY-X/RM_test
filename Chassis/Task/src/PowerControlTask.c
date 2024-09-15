#include "PowerControlTask.h"

uint32_t test_cnt;
float test_t;
void PowerControlTask(void *pvParameters)
{
    portTickType xLastWakeTime;

    SuperPowerInit();

    while (1)
    {
        // GetDeltaT(&test_cnt);

        INA_READ();//读取电压，电流，功率

        ADC_Filter();//ADC读取超电电压

        // test_t = GetDeltaT(&test_cnt);

        ChargeControl();//电容充放电控制

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1));
    }
}
