#ifndef _DEBUG_H
#define _DEBUG_H

#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "bsp_dwt.h"

/* whether use debug mode or not */
// #define DEBUG_MODE
// #define JSCOPE_RTT_MODE

/*  不同的任务设置一个开关，方便快速开关切换   */

#ifdef DEBUG_MODE

#include "SEGGER_RTT.h"
#include <stdio.h>

// RTT
#define PRINTF(str, ...)       \
    SEGGER_RTT_SetTerminal(0); \
    SEGGER_RTT_printf(0, str, ##__VA_ARGS__) // 字符串发送
#define PRINTF_F(str_temp, str, format) \
    sprintf(str_temp, str, format);     \
    SEGGER_RTT_SetTerminal(0);          \
    SEGGER_RTT_printf(0, str_temp); // 带浮点数的发送

#define LOG_PROTO(window, type, color, format, ...)     \
    SEGGER_RTT_printf(window, "  %s%s" format "\r\n%s", \
                      color,                            \
                      type,                             \
                      ##__VA_ARGS__,                    \
                      RTT_CTRL_RESET)

/* 清屏*/
#define LOG_CLEAR() SEGGER_RTT_WriteString(0, "  " RTT_CTRL_CLEAR)

/* 无颜色日志输出 */
#define LOG(format, ...) LOG_PROTO(0, "", "", format, ##__VA_ARGS__)

/* 有颜色格式日志输出 */
#define LOG_INFO(format, ...) LOG_PROTO(0, "[INFO]: ", RTT_CTRL_TEXT_BRIGHT_GREEN, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) LOG_PROTO(0, "[WARNING]: ", RTT_CTRL_TEXT_BRIGHT_YELLOW, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG_PROTO(0, "[ERROR]: ", RTT_CTRL_TEXT_BRIGHT_RED, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) LOG_PROTO(0, "[FATAL]: ", RTT_CTRL_TEXT_BRIGHT_BLUE, format, ##__VA_ARGS__)

// JSCOPE RTT MODE
#ifdef JSCOPE_RTT_MODE

#pragma pack(push, 1)

typedef struct
{
    float set_point; // 目标

    float raw_point; // 原数据

} acValBuffer;

#pragma pack(pop)

void JscopeRTTInit(void);
void JscopeWrite(float setPoint, float samplePoint);

#endif // JSCOPE_RTT_MODE

#endif

/* 丢帧检测 */
typedef struct Loss_Debugger
{
    uint16_t recv_msgs_num;

    /*  接收帧率计算定义 */
    uint32_t last_can_cnt;
    float can_dt;

    uint16_t loss_num;
} Loss_Debugger;

/* 计时器 */
typedef struct Time_Debugger
{
    uint32_t last_cnt;
    float dt;
} Time_Debugger;

/* 数据接收 */
typedef struct Receive_Debugger
{
    uint32_t last_cnt;
    float dt;
    uint16_t recv_msgs_num;
} Receive_Debugger;

typedef struct GlobalDebugger
{
    Loss_Debugger imu_debugger[2];
    Time_Debugger robot_debugger;
    Receive_Debugger remote_debugger; // 遥控器
    Loss_Debugger gimbal_debugger[2];
    Loss_Debugger friction_debugger[2];
    Loss_Debugger toggle_debugger;
    Loss_Debugger receive_chassis_debugger[2];
    Loss_Debugger pc_receive_debugger;

    int32_t can_send_wait;
} GlobalDebugger;

extern GlobalDebugger global_debugger;
extern float Ozone[8];

int8_t checkIMUOn(void);
void LossUpdate(Loss_Debugger *loss_debugger, float thresh_t);

#endif
