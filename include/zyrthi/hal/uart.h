#ifndef ZYRTHI_HAL_UART_H
#define ZYRTHI_HAL_UART_H

// 规范1：使用 HAL 层绝对路径引入通用类型
#include "zyrthi/hal/def.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// 规范2：仅放 UART 模块专属类型
// ==========================

/**
 * @brief UART 外设句柄（结构体指针，类型安全）
 * @note 适配层定义具体结构体内容，HAL 层只声明不定义
 */
typedef struct uart_inst* uart_hdl_t;

/**
 * @brief UART 配置结构体
 * @note 字段为 0 表示使用适配层默认值
 */
typedef struct {
    u32_t baud;           // 波特率（如 9600/115200/460800）
    u8_t data_bits;       // 数据位（5/6/7/8，0=默认8）
    u8_t stop_bits;       // 停止位（1/2，0=默认1）
    u8_t parity;          // 校验位（0=无, 1=奇校验, 2=偶校验）
    u8_t tx_pin;          // TX 引脚（0=使用默认引脚）
    u8_t rx_pin;          // RX 引脚（0=使用默认引脚）
} uart_config_t;

// UART 模块专属状态码
typedef enum {
    UART_OK               = 0,    // 操作成功
    UART_ERROR_INVALID_ARG = -1,  // 无效参数（波特率/句柄/缓冲区等）
    UART_ERROR_INVALID_INST = -2, // 无效的实例编号
    UART_ERROR_TIMEOUT    = -3,   // 收发超时
    UART_ERROR_BUSY       = -4,   // 串口忙（正在收发）
    UART_ERROR_EMPTY      = -5    // 接收缓冲区为空
} uart_status_t;

// UART 操作结果结构体
typedef struct {
    uart_status_t status;  // 操作状态码
    union {
        u8_t ch;           // 接收的字符（getc 用）
        bool_t available;  // 是否有可用数据（available 用）
        u32_t len;         // 实际收发长度（puts/gets 用）
    } data;
} uart_result_t;

// ==========================
// 规范3：UART 模块接口
// ==========================

/**
 * @brief 获取默认 UART 外设句柄（如 UART0）
 * @return uart_hdl_t: 默认 UART 句柄（NULL 表示无默认 UART）
 */
uart_hdl_t uart_default(void);

/**
 * @brief 按编号获取 UART 外设句柄
 * @param num: UART 编号（0, 1, 2, ...）
 * @return uart_hdl_t: UART 句柄（NULL 表示编号无效）
 */
uart_hdl_t uart_get(u8_t num);

/**
 * @brief 打开并配置 UART 外设
 * @param hdl: UART 外设句柄
 * @param config: 配置结构体（传值）
 * @return uart_status_t: 状态码
 */
uart_status_t uart_open(uart_hdl_t hdl, uart_config_t config);

/**
 * @brief 关闭 UART 外设（释放资源）
 * @param hdl: UART 外设句柄
 * @return uart_status_t: 状态码
 */
uart_status_t uart_close(uart_hdl_t hdl);

/**
 * @brief 发送单个字符
 * @param hdl: UART 外设句柄
 * @param c: 待发送的字符
 * @return uart_status_t: 状态码
 * @note 阻塞式发送
 */
uart_status_t uart_putc(uart_hdl_t hdl, u8_t c);

/**
 * @brief 接收单个字符
 * @param hdl: UART 外设句柄
 * @return uart_result_t: 包含状态码和接收字符的结构体
 */
uart_result_t uart_getc(uart_hdl_t hdl);

/**
 * @brief 检查 UART 接收缓冲区是否有可用数据
 * @param hdl: UART 外设句柄
 * @return uart_result_t: 包含状态码和可用状态的结构体
 */
uart_result_t uart_available(uart_hdl_t hdl);

/**
 * @brief 发送字符串
 * @param hdl: UART 外设句柄
 * @param str: 待发送的字符串（以 '\0' 结尾）
 * @return uart_result_t: 包含状态码和实际发送长度的结构体
 */
uart_result_t uart_puts(uart_hdl_t hdl, const char_t* str);

/**
 * @brief 接收字符串
 * @param hdl: UART 外设句柄
 * @param buf: 接收缓冲区
 * @param len: 缓冲区最大长度
 * @return uart_result_t: 包含状态码和实际接收长度的结构体
 */
uart_result_t uart_gets(uart_hdl_t hdl, char_t* buf, u32_t len);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_UART_H
