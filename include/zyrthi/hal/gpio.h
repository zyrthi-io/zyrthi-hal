#ifndef ZYRTHI_HAL_GPIO_H
#define ZYRTHI_HAL_GPIO_H

#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// GPIO 模块专属类型
// ==========================

// GPIO 模块状态码
typedef enum {
    GPIO_OK               = 0,    // 操作成功
    GPIO_ERROR_INVALID_PIN = -1,  // 无效引脚
    GPIO_ERROR_UNSUPPORTED = -2   // 不支持的引脚模式
} gpio_status_t;

// GPIO 操作结果结构体
typedef struct {
    gpio_status_t status;  // 操作状态码
    volt_t volt;           // 读取到的电平值（LOW/HIGH）
} gpio_result_t;

// ==========================
// GPIO 模块接口
// ==========================

/**
 * @brief 设置 GPIO 引脚模式
 * @param pin: GPIO 引脚编号
 * @param mode: 引脚模式（INPUT/OUTPUT/INPUT_PULLUP/INPUT_PULLDOWN）
 * @return gpio_status_t: 状态码
 */
gpio_status_t gpio_mode(u8_t pin, pin_mode_t mode);

/**
 * @brief 设置 GPIO 输出电平
 * @param pin: GPIO 引脚编号
 * @param level: 电平（LOW/HIGH）
 * @return gpio_status_t: 状态码
 */
gpio_status_t gpio_write(u8_t pin, volt_t level);

/**
 * @brief 读取 GPIO 输入电平
 * @param pin: GPIO 引脚编号
 * @return gpio_result_t: 包含状态码和电平值的结构体
 */
gpio_result_t gpio_read(u8_t pin);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_GPIO_H
