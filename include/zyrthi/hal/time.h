#ifndef ZYRTHI_HAL_TIME_H
#define ZYRTHI_HAL_TIME_H

// 规范：使用 HAL 层绝对路径引入通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// TIME 模块专属类型
// ==========================
// TIME 模块专属状态码（仅保留核心错误码，移除溢出相关）
typedef enum {
    TIME_OK              = 0,    // 操作成功
    TIME_ERROR_INVALID_ARG = -1, // 无效参数（延时时间为负数/超出范围）
    TIME_ERROR_UNSUPPORTED = -2  // 不支持的精度（如部分MCU不支持us级延时）
} time_status_t;

// TIME 计时结果结构体（极简，仅状态码+计数值）
typedef struct {
    time_status_t status;  // 操作状态码
    u32_t value;           // 计时值（ms/us）
} time_result_t;

// ==========================
// TIME 模块接口（明确自动回绕说明）
// ==========================
/**
 * @brief 获取系统启动后的毫秒数
 * @return time_result_t: 包含状态码和毫秒数的结构体
 * @note 1. u32_t 最大值(4294967295)对应约 49.7 天，溢出后自动回绕为0；
 *       2. 计算时间差直接用 end.value - start.value 即可（unsigned特性自动处理回绕）；
 *       3. 这是嵌入式计时的通用方案，无需额外处理溢出逻辑。
 */
time_result_t millis(void);

/**
 * @brief 获取系统启动后的微秒数
 * @return time_result_t: 包含状态码和微秒数的结构体
 * @note 1. u32_t 最大值对应约 71 分钟，溢出后自动回绕为0；
 *       2. 精度取决于系统定时器配置，部分MCU可能存在±1us误差；
 *       3. 时间差计算同 millis()，直接相减即可。
 */
time_result_t micros(void);

/**
 * @brief 毫秒级阻塞式延时
 * @param ms: 延时时间（单位：毫秒，u32_t 最大支持约 49.7 天）
 * @return time_status_t: 状态码（TIME_OK 成功，其他为错误码）
 */
time_status_t delay_ms(u32_t ms);

/**
 * @brief 微秒级阻塞式延时
 * @param us: 延时时间（单位：微秒，u32_t 最大支持约 71 分钟）
 * @return time_status_t: 状态码（TIME_OK 成功，其他为错误码）
 * @note 部分MCU硬件限制，us级延时可能存在±1us误差
 */
time_status_t delay_us(u32_t us);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_TIME_H