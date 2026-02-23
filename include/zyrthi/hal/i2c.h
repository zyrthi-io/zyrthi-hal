#ifndef ZYRTHI_HAL_I2C_H
#define ZYRTHI_HAL_I2C_H

// 规范1：使用 HAL 层绝对路径引入通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// 规范2：仅放 I2C 模块专属类型
// ==========================
// I2C 外设句柄
typedef void* i2c_hdl_t;

// I2C 模块专属状态码
typedef enum {
    I2C_OK              = 0,    // 操作成功
    I2C_ERROR_INVALID_ARG = -1, // 无效参数（NULL指针/非法地址/长度为0等）
    I2C_ERROR_TIMEOUT   = -2,   // 通信超时
    I2C_ERROR_NACK      = -3,   // 从机返回NACK
    I2C_ERROR_BUSY      = -4    // 总线忙
} i2c_status_t;

// I2C 读写返回结构体（多字节场景折中方案：状态码+实际读写长度，避免指针陷阱但保留多字节灵活性）
typedef struct {
    i2c_status_t status;  // 操作状态码
    u32_t actual_len;     // 实际读写的字节数
} i2c_result_t;

// ==========================
// 规范3：I2C 模块接口（极简命名+错误闭环+Doxygen注释）
// ==========================
/**
 * @brief 获取默认 I2C 外设句柄
 * @return i2c_hdl_t: 默认 I2C 外设句柄（如 I2C0）
 * @note 适配层需定义默认 I2C 外设的配置（引脚/时钟等）
 */
i2c_hdl_t i2c_default(void);

/**
 * @brief 初始化 I2C 外设
 * @param hdl: I2C 外设句柄
 * @param clock_hz: I2C 总线时钟频率（单位：Hz，如 100000=100kHz）
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_init(i2c_hdl_t hdl, u32_t clock_hz);

/**
 * @brief 开始 I2C 传输（必须按顺序调用：begin -> write/read -> end）
 * @param hdl: I2C 外设句柄
 * @param addr: 从机地址（7位，不含读写位）
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_begin(i2c_hdl_t hdl, u8_t addr);

/**
 * @brief 向 I2C 从机写入数据
 * @param hdl: I2C 外设句柄
 * @param data: 待写数据缓冲区（**不能为 NULL**，适配层需做 NULL 检查）
 * @param len: 待写数据长度（**不能为 0**）
 * @return i2c_result_t: 包含状态码和实际写入字节数的结构体
 * @note 必须在 i2c_begin 之后、i2c_end 之前调用
 */
i2c_result_t i2c_write(i2c_hdl_t hdl, const u8_t* data, u32_t len);

/**
 * @brief 从 I2C 从机读取数据
 * @param hdl: I2C 外设句柄
 * @param buf: 接收数据缓冲区（**不能为 NULL**，适配层需做 NULL 检查）
 * @param len: 待读数据长度（**不能为 0**）
 * @return i2c_result_t: 包含状态码和实际读取字节数的结构体
 * @note 必须在 i2c_begin 之后、i2c_end 之前调用
 */
i2c_result_t i2c_read(i2c_hdl_t hdl, u8_t* buf, u32_t len);

/**
 * @brief 结束 I2C 传输（必须按顺序调用：begin -> write/read -> end）
 * @param hdl: I2C 外设句柄
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_end(i2c_hdl_t hdl);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_I2C_H