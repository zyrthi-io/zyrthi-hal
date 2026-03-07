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

/**
 * @brief I2C 外设句柄（结构体指针，类型安全）
 */
typedef struct i2c_inst* i2c_hdl_t;

/**
 * @brief I2C 配置结构体
 * @note 字段为 0 表示使用适配层默认值
 */
typedef struct {
    u32_t clock_hz;       // 时钟频率（如 100000/400000）
    u8_t sda_pin;         // SDA 引脚（0=使用默认引脚）
    u8_t scl_pin;         // SCL 引脚（0=使用默认引脚）
} i2c_config_t;

// I2C 模块专属状态码
typedef enum {
    I2C_OK               = 0,    // 操作成功
    I2C_ERROR_INVALID_ARG = -1,  // 无效参数
    I2C_ERROR_INVALID_INST = -2, // 无效的实例编号
    I2C_ERROR_TIMEOUT    = -3,   // 通信超时
    I2C_ERROR_NACK       = -4,   // 从机返回 NACK
    I2C_ERROR_BUSY       = -5    // 总线忙
} i2c_status_t;

// I2C 读写返回结构体
typedef struct {
    i2c_status_t status;  // 操作状态码
    u32_t actual_len;     // 实际读写的字节数
} i2c_result_t;

// ==========================
// 规范3：I2C 模块接口
// ==========================

/**
 * @brief 获取默认 I2C 外设句柄
 * @return i2c_hdl_t: 默认 I2C 外设句柄（NULL 表示无默认 I2C）
 */
i2c_hdl_t i2c_default(void);

/**
 * @brief 按编号获取 I2C 外设句柄
 * @param num: I2C 编号（0, 1, ...）
 * @return i2c_hdl_t: I2C 句柄（NULL 表示编号无效）
 */
i2c_hdl_t i2c_get(u8_t num);

/**
 * @brief 打开并配置 I2C 总线
 * @param hdl: I2C 外设句柄
 * @param config: 配置结构体（传值）
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_open(i2c_hdl_t hdl, i2c_config_t config);

/**
 * @brief 关闭 I2C 总线（释放资源）
 * @param hdl: I2C 外设句柄
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_close(i2c_hdl_t hdl);

/**
 * @brief 开始 I2C 传输
 * @param hdl: I2C 外设句柄
 * @param addr: 从机地址（7位，不含读写位）
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_begin(i2c_hdl_t hdl, u8_t addr);

/**
 * @brief 向 I2C 从机写入数据
 * @param hdl: I2C 外设句柄
 * @param data: 待写数据缓冲区
 * @param len: 待写数据长度
 * @return i2c_result_t: 包含状态码和实际写入字节数
 */
i2c_result_t i2c_write(i2c_hdl_t hdl, const u8_t* data, u32_t len);

/**
 * @brief 从 I2C 从机读取数据
 * @param hdl: I2C 外设句柄
 * @param buf: 接收数据缓冲区
 * @param len: 待读数据长度
 * @return i2c_result_t: 包含状态码和实际读取字节数
 */
i2c_result_t i2c_read(i2c_hdl_t hdl, u8_t* buf, u32_t len);

/**
 * @brief 结束 I2C 传输
 * @param hdl: I2C 外设句柄
 * @return i2c_status_t: 状态码
 */
i2c_status_t i2c_end(i2c_hdl_t hdl);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_I2C_H
