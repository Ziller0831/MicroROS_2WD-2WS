#include "BldcHallEncoder.h"

bool BldcHallEncoder::init(int pcntUnit, int pin_A, int pin_B, float distancePerPulse)
{
    _pin_A = pin_A;
    _pin_B = pin_B;
    _distancePerPulse = distancePerPulse;
    _pcntUnit = static_cast<pcnt_unit_t>(pcntUnit);

    pcnt_config_t pcntConfig = {
        .pulse_gpio_num = (gpio_num_t)_pin_A,
        .ctrl_gpio_num = (gpio_num_t)_pin_B,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_KEEP,
        .pos_mode = PCNT_COUNT_INC,
        .neg_mode = PCNT_COUNT_DIS,
        .counter_h_lim = 32767,
        .counter_l_lim = -32768,
        .unit = _pcntUnit,
        .channel = PCNT_CHANNEL_0,
    };

    if (pcnt_unit_config(&pcntConfig) != ESP_OK)
        return false;

    pcnt_counter_clear(_pcntUnit);
    pcnt_counter_resume(_pcntUnit);

    _lastUpdateTime = millis();
    _lastPulseCount = 0;

    return true;
}

bool BldcHallEncoder::setGlitchFilter(uint32_t maxGlitchUs)
{
    return pcnt_set_filter_value(_pcntUnit, maxGlitchUs) == ESP_OK &&
           pcnt_filter_enable(_pcntUnit) == ESP_OK;
}

float BldcHallEncoder::getSpeed()
{
    uint32_t now = millis();
    int16_t pulseCount = 0;

    // 獲取目前脈衝數
    pcnt_get_counter_value(_pcntUnit, &pulseCount);

    int32_t deltaTicks = pulseCount - _lastPulseCount;
    uint32_t deltaTime = now - _lastUpdateTime;

    float speed = 0.0f;

    if (deltaTime > 0)
    {
        speed = (deltaTicks * _distancePerPulse) / (deltaTime / 1000.0f); // 單位: m/s 或其他單位
    }

    // 更新記錄
    _lastPulseCount = pulseCount;
    _lastUpdateTime = now;

    return speed;
}

int32_t BldcHallEncoder::getPulseCount()
{
    int pulse_count = 0;
    pcnt_get_counter_value(_pcntUnit, &currentPulseCount);
    return currentPulseCount; // 返回當前的脈衝數
}

bool BldcHallEncoder::reset()
{
    return pcnt_counter_clear(_pcntUnit) == ESP_OK;
}
