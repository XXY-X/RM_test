#ifndef _BLUE_TOOTH_TASK_H
#define _BLUE_TOOTH_TASK_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

#include "bluetooth.h"
#include "VOFA.h"
#include "ChasisControlTask.h"
#include "atk_ms53l0m.h"

void BlueToothTask(void *pvParameters);

#endif // !_BLUE_TOOTH_TASK_H
