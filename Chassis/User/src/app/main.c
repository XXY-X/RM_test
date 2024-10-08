/**
 ******************************************************************************
 * @file    main.c
 * @brief   主函数，程序进口
 ******************************************************************************
 * @attention
 ******************************************************************************
 */

#include "main.h"

/* clock frequency */
RCC_ClocksTypeDef get_rcc_clock;

int main(void)//
{
    /* get clock frequency */
    RCC_GetClocksFreq(&get_rcc_clock);

#ifdef DEBUG_MODE
    SEGGER_RTT_Init();
    LOG_CLEAR();
#ifdef JSCOPE_RTT_MODE
    JscopeRTTInit();
#endif // JSCOPE_RTT_MODE
#endif // DEBUG_MODE

    /* init */
    BSP_Init();
#if !TEST_TASK_ON
    Robot_Init();
#endif // DEBUG

    /* create task */
    startTask();

    /* 调度 */
    vTaskStartScheduler();

    while (1)
        ;
}

/**
 * @brief STM32初始化
 * @param[in] void
 */
void BSP_Init(void)
{
#ifdef DEBUG_MODE_FREERTOS
    /*  TIM7初始化，用于FreeRTOS 计算CPU占用情况 */
    OS_TICK_Configuration();
    delay_ms(1);
#endif // DEBUG_MODE_FREERTOS

    /*  计数器初始化，us级计时 */
    COUNTER_Configuration();
    delay_ms(1);

    SuperPower_Configuration();
    delay_ms(1);

    /*  CAN1初始化 */
    CAN1_Configuration();
    delay_ms(1);

    /*  CAN2初始化,初始化前CAN1需初始化 */
    CAN2_Configuration();
    delay_ms(1);
    /*  DJI遥控器串口接收配置 */
    DJI_REMOTE_Configuration();
    delay_ms(1);

    /*  与PC间的串口通信 */
    //    PC_UART_Configuration();
    //    delay_ms(1);
    /*  裁判系统通信 */
    REFEREE_Configuration();
    delay_ms(1);

    // WIFI_Configuration();
    // delay_ms(1);

    // BLUE_TOOTH_Configuration();
    // atk_ms53l0m_init(115200);
    //		VOFA_Configuration();

    // delay_ms(1);

    // LED_Configration();
    // delay_ms(1);

    // i2c_init();
    // delay_ms(1);
}

/**
 * @brief 机器人初始化
 * @param[in] void
 */
void Robot_Init(void)
{
    ONLY_LED_R_ON;

    delay_ms(10);

    initRemoteControl(DJI_REMOTE_CONTROL);

    ONLY_LED_B_ON;

    setRobotType(); // 设置机器人类型
}
