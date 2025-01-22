#ifndef __BLDC_HALL_ENCODER_H__
#define __BLDC_HALL_ENCODER_H__

#include "Arduino.h"
#include <driver/pcnt.h>

class BldcHallEncoder
{
public:
    BldcHallEncoder() = default;

    // 初始化霍爾編碼器
    bool init(int pcntUnit, int pin, float distancePerPulse);

    // 設定去抖濾波器
    bool setGlitchFilter(uint32_t maxGlitchUs);

    // 計算速度 (靈活單位)
    float getSpeed(); // 單位：根據 distancePerPulse 決定 (如 m/s)

    // 返回累積脈衝數
    int32_t getPulseCount();

    // 重置計數器
    bool reset();

private:
    int _pin;
    float _distancePerPulse; // 每脈衝代表的距離
    int32_t _lastPulseCount;
    uint32_t _lastUpdateTime;

    pcnt_unit_t _pcntUnit;
};

#endif // __BLDC_HALL_ENCODER_H__
