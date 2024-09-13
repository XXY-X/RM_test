#ifndef _SUPER_POWER_H
#define _SUPER_POWER_H

#include "bsp_superpower.h"
#include "pid.h"
#include "Referee.h"
#include "tools.h"
#include "ina260.h"

#include "PowerLimit.h"
#include "remote_control.h"

#define CAP_VOLTAGE_LOW 11
#define CAP_VOLTAGE_HIGH 14

#define SUPERPOWER_SAMPLE_RATIO 8.4f // 超级电容采样比,根据电路设计而定

#define BIT_12_NUM 4096

#define CHARGE_MARGIN 5.0f      // 充电最大功率到实际最大功率的距离
#define MAX_CHARGE_CURRENT 5.0f // 最大充电电流

#define POWER_CHARGE_VOL_MIN_RANGE 18.0f // 开始线性衰减
#define POWER_CHARGE_VOL_MAX_RANGE 21.0f // 衰减到0

#define MIN_CAP_VOL_H 17.0f//H逻辑最小电压
#define MIN_CAP_VOL_L 13.0f//L逻辑最小（大？）电压

#define SUPER_POWER_BIAS -2.8f//偏置
#define SUPER_POWER_RATIO 0.9146f//速率

enum PowerChargeState//电容充电状态
{
    POWER_CHARGE_OFF,//未充电
    POWER_CHARGE_ON//充电中
};

enum SuperPowerState//电容模式
{
    SuperPowerOff,     // 不开电容
    SuperPowerPassive, // 被动电容模式
    SuperPowerActive   // 主动电容模式
};

enum PowerLimitState // 功控状态
{
    POWER_LIMIT_BAT,      // 电池正常供电
    POWER_LIMIT_CAP,      // 电容正常供电
    POWER_LIMIT_BAT_ERROR // 电池不正常供电(电容耗尽)
};

typedef struct SuperPower//超电参数
{
    float actual_vol; // 实际电容电压(乘采样比)

    // 电压采集变量
    uint32_t SUM_UCAP;  // 电容电压
    uint32_t SUM_UDCDC; // 充电电压
    uint32_t SUM_TEMP;  // 温度

    float UCAP;//电容电压？
    float UDCDC;//电源电压？
    float temperate;//超电温度？

    enum SuperPowerState superpower_state;
    enum PowerControlState power_control_state;
    enum PowerChargeState power_charge_state;
    enum PowerLimitState power_limit_state;
    PID_t superpower_charge_pid; // 超级电容充电PID

    float i_set;             // 充电电流
    uint16_t charge_dac_set; // 充电电流dac
    float max_charge_power;  // 最大充电功率
    float charge_power;      // 充电功率
    float actual_power;      // 实际功率

    float current_reduce;

    /* data */
} SuperPower;

#define TEST_MAX_POWER 60 // 测试功率
#define TEST_HP 300 //测试血量
#define MAX_BUFFERING_ENERGY 60
#define REGEREE_TEST 0

typedef struct BufferEnergy//缓冲能量
{
    float Kr;
    float buffering_energy;//缓冲能量
    float lose_ratio; // 掉血比例
    float HP;         // 血量
    float max_Power;  // 最大功率
} BufferEnergy;

extern SuperPower super_power;
extern BufferEnergy buffer_energy;

void ADC_Filter(void);
void SuperPowerInit(void);
void ChargeControl(void);
void Bat_use(void);
void CAP_use(void);
#endif // !_SUPER_POWER_H
