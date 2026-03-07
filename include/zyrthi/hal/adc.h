#ifndef ZYRTHI_HAL_ADC_H
#define ZYRTHI_HAL_ADC_H

// 仅引入全局通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// ADC 模块专属类型
// ==========================

/**
 * @brief ADC 配置结构体
 * @note 字段为 0 表示使用适配层默认值
 */
typedef struct {
    u8_t atten;          // 衰减（0=0dB, 1=2.5dB, 2=6dB, 3=11dB）
    u8_t width;          // 分辨率（12=12位, 11=11位, 10=10位）
} adc_config_t;

// ADC 模块状态码
typedef enum {
    ADC_OK               = 0,    // 读取成功
    ADC_ERROR_INVALID_PIN = -1,  // 无效 ADC 引脚
    ADC_ERROR_UNSUPPORTED = -2,  // 引脚不支持 ADC 功能
    ADC_ERROR_TIMEOUT    = -3    // 转换超时
} adc_status_t;

// ADC 数据返回结构体
typedef struct {
    adc_status_t status;  // 操作状态码
    u16_t raw;            // ADC 原始读数
    u16_t volt_mv;        // 转换后的电压值（mV，由适配层计算）
} adc_result_t;

// ==========================
// ADC 模块接口
// ==========================

/**
 * @brief 打开并配置 ADC 通道
 * @param pin: ADC 输入引脚
 * @param config: 配置结构体（传值）
 * @return adc_status_t: 状态码
 */
adc_status_t adc_open(u8_t pin, adc_config_t config);

/**
 * @brief 关闭 ADC 通道（释放资源）
 * @param pin: ADC 输入引脚
 * @return adc_status_t: 状态码
 */
adc_status_t adc_close(u8_t pin);

/**
 * @brief 读取 ADC 引脚数据
 * @param pin: ADC 引脚编号
 * @return adc_result_t: 包含状态码、原始值、电压值的结构体
 */
adc_result_t adc_read(u8_t pin);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_ADC_H
