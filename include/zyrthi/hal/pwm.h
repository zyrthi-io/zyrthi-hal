#ifndef ZYRTHI_HAL_PWM_H
#define ZYRTHI_HAL_PWM_H

// 规范1：使用 HAL 层绝对路径引入通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// 规范2：仅放 PWM 模块专属类型
// ==========================
// PWM 模块专属状态码
typedef enum {
    PWM_OK              = 0,    // 操作成功
    PWM_ERROR_INVALID_PIN = -1, // 无效 PWM 引脚
    PWM_ERROR_INVALID_ARG = -2, // 无效参数（频率/占空比超出范围）
    PWM_ERROR_UNSUPPORTED = -3  // 引脚不支持 PWM 功能
} pwm_status_t;

// PWM 操作结果结构体（仅用于 pwm_read，包含状态码和当前占空比）
typedef struct {
    pwm_status_t status;  // 操作状态码
    u32_t duty;           // 当前占空比（表示方式：0~10000 对应 0%~100%，精度 0.01%）
} pwm_result_t;

// ==========================
// 规范3：PWM 模块接口（补全核心功能+极简命名+错误闭环+Doxygen注释）
// ==========================
/**
 * @brief 初始化 PWM 引脚
 * @param pin: PWM 引脚编号
 * @param freq_hz: PWM 总线频率（单位：Hz，如 1000=1kHz）
 * @return pwm_status_t: 状态码
 * @note 占空比默认初始化为 0%
 */
pwm_status_t pwm_init(u8_t pin, u32_t freq_hz);

/**
 * @brief 设置 PWM 引脚占空比
 * @param pin: PWM 引脚编号
 * @param duty: 占空比（表示方式：0~10000 对应 0%~100%，精度 0.01%）
 * @return pwm_status_t: 状态码
 * @note 必须先调用 pwm_init 初始化引脚
 */
pwm_status_t pwm_write(u8_t pin, u32_t duty);

/**
 * @brief 读取 PWM 引脚当前占空比
 * @param pin: PWM 引脚编号
 * @return pwm_result_t: 包含状态码和当前占空比的结构体
 * @note 必须先调用 pwm_init 初始化引脚
 */
pwm_result_t pwm_read(u8_t pin);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_PWM_H