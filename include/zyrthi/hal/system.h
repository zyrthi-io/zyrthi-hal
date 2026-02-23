#ifndef ZYRTHI_HAL_SYSTEM_H
#define ZYRTHI_HAL_SYSTEM_H

// 规范：使用 HAL 层绝对路径引入通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// SYSTEM 模块专属类型
// ==========================
// SYSTEM 模块专属状态码
typedef enum {
    SYS_OK              = 0,    // 初始化成功
    SYS_ERROR_UNSUPPORTED = -1, // 不支持的系统配置
    SYS_ERROR_BUSY      = -2    // 系统资源忙
} sys_status_t;

// ==========================
// SYSTEM 模块核心接口（仅保留初始化）
// ==========================
/**
 * @brief 初始化系统核心资源（系统时钟、基础外设总线等）
 * @return sys_status_t: 状态码（SYS_OK 成功，其他为错误码）
 * @note 必须在调用所有其他 HAL 接口之前调用，仅需调用一次
 */
sys_status_t system_init(void);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_SYSTEM_H