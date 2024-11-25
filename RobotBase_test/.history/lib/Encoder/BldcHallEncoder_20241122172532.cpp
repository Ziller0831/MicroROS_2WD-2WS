#include "BldcHallEncoder.h"

bool BldcHallEncoder::init(int pcntUnit, int pin, float pulsesPerRevolution)
{
    _pin = pin;
    _pulsesPerRevolution = pulsesPerRevolution;
    _pcntUnit = static_cast<pcnt_unit_t>(pcntUnit);

    // 配置PCNT單元
    pcnt_config_t pcntConfig = {
        .pulse_gpio_num = pin,
        .ctrl_gpio_num = PCNT_PIN_NOT_USED,
        .unit = _pcntUnit,
        .channel = PCNT_CHANNEL_0,
        .pos_mode = PCNT_COUNT_INC,
        .neg_mode = PCNT_COUNT_DIS,
        .hctrl_mode = PCNT_MODE_KEEP,
        .lctrl_mode = PCNT_MODE_KEEP,
        .counter_h_lim = 32767,
        .counter_l_lim = -32768,
    };

    if (pcnt_unit_config(&pcntConfig) != ESP_OK)
        return false;

    // 啟用PCNT
    pcnt_counter_pause(_pcntUnit);
    pcnt_counter_clear(_pcntUnit);
    pcnt_counter_resume(_pcntUnit);

    return true;
}

bool BldcHallEncoder::setGlitchFilter(uint32_t maxGlitchUs)
{
    return pcnt_set_filter_value(_pcntUnit, maxGlitchUs) == ESP_OK &&
           pcnt_filter_enable(_pcntUnit) == ESP_OK;
}

bool BldcHallEncoder::reset()
{
    return pcnt_counter_clear(_pcntUnit) == ESP_OK;
}

float BldcHallEncoder::getSpeed()
{
    int16_t pulseCount = 0;
    pcnt_get_counter_value(_pcntUnit, &pulseCount);

    uint32_t now = millis();
    uint32_t timeDelta = now - _lastUpdateTime;

    float speed = 0.0;
    if (timeDelta > 0)
    {
        int32_t pulseDelta = pulseCount - _lastPulseCount;
        speed = (pulseDelta / static_cast<float>(_pulsesPerRevolution)) * (60000.0 / timeDelta);
    }

    _lastPulseCount = pulseCount;
    _lastUpdateTime = now;

    return speed; // 返回 RPM
}
