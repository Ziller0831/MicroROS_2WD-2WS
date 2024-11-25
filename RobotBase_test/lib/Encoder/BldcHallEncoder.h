#ifndef __BLDC_HALL_ENCODER_H__
#define __BLDC_HALL_ENCODER_H__

#include "Arduino.h"
#include <driver/pcnt.h>

class BldcHallEncoder
{
public:
    BldcHallEncoder() = default;

    // 初始化霍爾編碼器
    bool init(int pcntUnit, int pin, float pulsesPerRevolution);

    // 設定消抖濾波器
    bool setGlitchFilter(uint32_t maxGlitchUs);

    // 重置計數器
    bool reset();

    // 計算速度
    float getSpeed(); // 單位: RPM

private:
    int _pin;
    int _pulsesPerRevolution; // 每轉的脈衝數
    int32_t _lastPulseCount;
    uint32_t _lastUpdateTime;

public:
    pcnt_unit_t _pcntUnit;
};

#endif // __BLDC_HALL_ENCODER_H__