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

/**
 * @brief PWM 配置结构体
 * @note 字段为 0 表示使用适配层默认值
 */
typedef struct {
    u32_t freq_hz;       // PWM 频率（单位：Hz）
    u32_t duty;          // 初始占空比（0~10000 对应 0%~100%）
} pwm_config_t;

// PWM 模块专属状态码
typedef enum {
    PWM_OK               = 0,    // 操作成功
    PWM_ERROR_INVALID_PIN = -1,  // 无效 PWM 引脚
    PWM_ERROR_INVALID_ARG = -2,  // 无效参数
    PWM_ERROR_UNSUPPORTED = -3   // 引脚不支持 PWM 功能
} pwm_status_t;

// PWM 操作结果结构体
typedef struct {
    pwm_status_t status;  // 操作状态码
    u32_t duty;           // 当前占空比（0~10000）
} pwm_result_t;

// ==========================
// 规范3：PWM 模块接口
// ==========================

/**
 * @brief 打开并配置 PWM 通道
 * @param pin: PWM 输出引脚
 * @param config: 配置结构体（传值）
 * @return pwm_status_t: 状态码
 */
pwm_status_t pwm_open(u8_t pin, pwm_config_t config);

/**
 * @brief 关闭 PWM 通道（释放资源）
 * @param pin: PWM 输出引脚
 * @return pwm_status_t: 状态码
 */
pwm_status_t pwm_close(u8_t pin);

/**
 * @brief 设置 PWM 占空比
 * @param pin: PWM 引脚编号
 * @param duty: 占空比（0~10000 对应 0%~100%）
 * @return pwm_status_t: 状态码
 */
pwm_status_t pwm_write(u8_t pin, u32_t duty);

/**
 * @brief 读取 PWM 当前占空比
 * @param pin: PWM 引脚编号
 * @return pwm_result_t: 包含状态码和当前占空比
 */
pwm_result_t pwm_read(u8_t pin);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_PWM_H
