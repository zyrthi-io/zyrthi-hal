/**
 * @file zyrthi_hal.h
 * @brief ZYRTHI HAL 层汇总头文件（最小核心集）
 * @note 1. 仅包含 HAL 最基础的核心模块，满足极简启动需求；
 *       2. 如需使用其他模块（如 UART/I2C/PWM/TIME），可单独引入对应头文件；
 *       3. 所有模块均已统一命名规范、错误闭环、语义清晰。
 */
#ifndef ZYRTHI_HAL_H
#define ZYRTHI_HAL_H

// 兼容 C++ 编译（和其他 HAL 模块保持一致）
#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// HAL 最小核心集（必选模块）
// ==========================
// 通用类型定义（所有模块的基础）
#include "zyrthi/hal/def.h"
// 系统核心初始化（HAL 启动入口）
#include "zyrthi/hal/system.h"
// GPIO 通用输入输出（嵌入式最基础外设）
#include "zyrthi/hal/gpio.h"

// ==========================
// HAL 扩展模块（可选，按需引入）
// ==========================
/* 在业务代码中单独引入
#include "zyrthi/hal/time.h"    // 计时/延时模块
#include "zyrthi/hal/uart.h"    // UART 串口模块
#include "zyrthi/hal/i2c.h"     // I2C 总线模块
#include "zyrthi/hal/pwm.h"     // PWM 脉冲宽度调制模块
#include "zyrthi/hal/adc.h"     // ADC 模数转换模块
*/

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_H