#ifndef ZYRTHI_HAL_GPIO_H
#define ZYRTHI_HAL_GPIO_H

#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// 仅放：GPIO 模块专属类型
// ==========================
typedef enum {
    GPIO_OK              = 0,    // 操作成功
    GPIO_ERROR_INVALID_PIN = -1, // 无效引脚
    GPIO_ERROR_UNSUPPORTED = -2  // 不支持的引脚模式
} gpio_status_t;

typedef struct {
    gpio_status_t status;  // 操作状态码
    volt_t volt;          // 读取到的电平值（LOW/HIGH）
} gpio_result_t;

// ==========================
// GPIO 模块接口
// ==========================
gpio_status_t gpio_mode(u8_t pin, pin_mode_t mode);
gpio_status_t gpio_write(u8_t pin, volt_t level);
gpio_result_t gpio_read(u8_t pin);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_GPIO_H