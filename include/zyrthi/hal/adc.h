#ifndef ZYRTHI_HAL_ADC_H
#define ZYRTHI_HAL_ADC_H

// 仅引入全局通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// 仅放：ADC 模块专属类型
// ==========================
// ADC 模块状态码
typedef enum {
    ADC_OK              = 0,        // 读取成功
    ADC_ERROR_INVALID_PIN = -1,     // 无效 ADC 引脚
    ADC_ERROR_UNSUPPORTED = -2,     // 引脚不支持 ADC 功能
    ADC_ERROR_TIMEOUT   = -3        // 转换超时
} adc_status_t;

// ADC 数据返回结构体
typedef struct {
    adc_status_t status;  // 操作状态码
    u16_t raw;            // ADC 原始读数
    u16_t volt_mv;        // 转换后的电压值（mV）
} adc_result_t;

// ==========================
// ADC 模块接口
// ==========================
/**
 * @brief 读取 ADC 引脚数据（极简接口，结构体返回所有数据）
 * @param pin: ADC 引脚编号
 * @return adc_result_t: 包含状态码、原始值、电压值的结构体
 */
adc_result_t adc_read(u8_t pin);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_ADC_H