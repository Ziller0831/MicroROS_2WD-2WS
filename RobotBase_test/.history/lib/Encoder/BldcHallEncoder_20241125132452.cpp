#include "BldcHallEncoder.h"

#define EC11_PCNT_DEFAULT_HIGH_LIMIT (100)
#define EC11_PCNT_DEFAULT_LOW_LIMIT (-100)

bool BldcHallEncoder::init(int pcntUnit, int pin, float pulsesPerRevolution)
{
    this->_pin = pin;
    this->_pulsesPerRevolution = pulsesPerRevolution;
    this->_pcntUnit = static_cast<pcnt_unit_t>(pcntUnit);

    pinMode(_pin, INPUT_PULLUP);

    // 配置PCNT單元
    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = pin,              // 信號 GPIO 腳位
        .ctrl_gpio_num = PCNT_PIN_NOT_USED, // 不使用控制腳位
        .unit = _pcntUnit,                  // 選擇計數器單元
        .channel = PCNT_CHANNEL_0,          // 使用通道 0
        .pos_mode = PCNT_COUNT_INC,         // 上升沿遞增計數
        .neg_mode = PCNT_COUNT_DIS,         // 忽略下降沿
        .hctrl_mode = PCNT_MODE_KEEP,       // 高電平保持
        .lctrl_mode = PCNT_MODE_KEEP,       // 低電平保持
        .counter_h_lim = 32767,             // 計數器上限
        .counter_l_lim = -32768,            // 計數器下限
    };

    if (pcnt_unit_config(&pcnt_config) != ESP_OK)
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
