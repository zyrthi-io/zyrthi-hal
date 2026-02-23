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
// UART 外设句柄（统一 hd 后缀 → hdl，符合框架句柄命名规范）
typedef void* uart_hdl_t;

// UART 模块专属状态码（补充核心错误码，保持枚举值连续）
typedef enum {
    UART_OK              = 0,    // 操作成功
    UART_ERROR_INVALID_ARG = -1, // 无效参数（波特率/句柄/缓冲区等）
    UART_ERROR_TIMEOUT   = -2,   // 收发超时
    UART_ERROR_BUSY      = -3,   // 串口忙（正在收发）
    UART_ERROR_EMPTY     = -4    // 接收缓冲区为空（仅 getc/gets 时返回）
} uart_status_t;

// UART 操作结果结构体（用于有返回数据的接口：getc/available）
typedef struct {
    uart_status_t status;  // 操作状态码
    union {
        u8_t ch;           // 接收的字符（getc 用）
        bool_t available;  // 是否有可用数据（available 用）
        u32_t len;         // 实际收发长度（puts/gets 用）
    } data;                // 联合存储不同类型的返回数据，节省内存
} uart_result_t;

// ==========================
// 规范3：UART 模块接口（极简命名+错误闭环+Doxygen注释）
// ==========================
/**
 * @brief 获取默认 UART 外设句柄（如 UART0）
 * @return uart_hdl_t: 默认 UART 句柄（NULL 表示无默认 UART）
 * @note 适配层需定义默认 UART 的硬件配置（引脚/波特率等）
 */
uart_hdl_t uart_default(void);

/**
 * @brief 初始化 UART 外设
 * @param hdl: UART 外设句柄（由 uart_default 获取或适配层自定义）
 * @param baud: 波特率（如 9600/115200/460800）
 * @return uart_status_t: 状态码（UART_OK 成功，其他为错误码）
 * @note 数据位默认 8 位、停止位 1 位、无校验位（通用配置）
 */
uart_status_t uart_init(uart_hdl_t hdl, u32_t baud);

/**
 * @brief 发送单个字符
 * @param hdl: UART 外设句柄
 * @param c: 待发送的字符
 * @return uart_status_t: 状态码
 * @note 阻塞式发送，直到发送完成或超时
 */
uart_status_t uart_putc(uart_hdl_t hdl, u8_t c);

/**
 * @brief 接收单个字符
 * @param hdl: UART 外设句柄
 * @return uart_result_t: 包含状态码和接收字符的结构体
 * @note 1. 阻塞式接收，直到接收到字符/超时/缓冲区为空；
 *       2. status=UART_OK 时，data.ch 为有效字符；
 *       3. status=UART_ERROR_EMPTY 表示接收缓冲区无数据。
 */
uart_result_t uart_getc(uart_hdl_t hdl);

/**
 * @brief 检查 UART 接收缓冲区是否有可用数据
 * @param hdl: UART 外设句柄
 * @return uart_result_t: 包含状态码和可用状态的结构体
 * @note status=UART_OK 时，data.available 为 true/false 表示是否有数据
 */
uart_result_t uart_available(uart_hdl_t hdl);

/**
 * @brief 发送字符串（补全核心接口）
 * @param hdl: UART 外设句柄
 * @param str: 待发送的字符串（以 '\0' 结尾）
 * @return uart_result_t: 包含状态码和实际发送长度的结构体
 * @note 阻塞式发送，直到发送完成或超时
 */
uart_result_t uart_puts(uart_hdl_t hdl, const char_t* str);

/**
 * @brief 接收字符串（补全核心接口）
 * @param hdl: UART 外设句柄
 * @param buf: 接收缓冲区（需用户提前分配内存）
 * @param len: 缓冲区最大长度（包含 '\0' 结束符）
 * @return uart_result_t: 包含状态码和实际接收长度的结构体
 * @note 1. 接收到 '\n'/'\r' 或缓冲区满时停止；
 *       2. 自动在缓冲区末尾添加 '\0' 结束符；
 *       3. status=UART_OK 时，data.len 为实际接收的字符数（不含 '\0'）。
 */
uart_result_t uart_gets(uart_hdl_t hdl, char_t* buf, u32_t len);

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_UART_H