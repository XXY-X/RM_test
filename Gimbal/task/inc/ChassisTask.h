#ifndef _CHASSIS_TASK_H
#define _CHASSIS_TASK_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "ChassisSolver.h"
#include "can_config.h"

#include "ChassisSend.h"

#include "bsp_can.h"
#include "can.h"

void ChassisTask(void *pvParameters);//给底盘发送控制信息

#endif // !_CHASSIS_TASK_H
