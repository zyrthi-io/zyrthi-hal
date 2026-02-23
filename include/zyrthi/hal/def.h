#ifndef ZYRTHI_HAL_DEF_H
#define ZYRTHI_HAL_DEF_H

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t  u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;

typedef int8_t   i8_t;
typedef int16_t  i16_t;
typedef int32_t  i32_t;
typedef int64_t  i64_t;

typedef char char_t;
typedef uint8_t byte_t;
typedef bool bool_t;


// 通用电平枚举（硬件无关抽象）
typedef enum {
    LOW  = 0,
    HIGH = 1
} volt_t;

// 通用引脚模式枚举（硬件无关抽象）
typedef enum {
    INPUT          = 0,
    OUTPUT         = 1,
    INPUT_PULLUP   = 2,
    INPUT_PULLDOWN = 3
} pin_mode_t;

// ==========================
// 编译期静态断言（核心增强：避免跨平台类型位数错误）
// 若平台不支持标准固定位数类型，编译时直接报错，提前暴露问题
// ==========================
// 兼容 C11 之前的编译器（若不支持 _Static_assert，自动禁用）
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
_Static_assert(sizeof(u8_t)  == 1, "u8_t must be 8 bits");
_Static_assert(sizeof(u16_t) == 2, "u16_t must be 16 bits");
_Static_assert(sizeof(u32_t) == 4, "u32_t must be 32 bits");
_Static_assert(sizeof(u64_t) == 8, "u64_t must be 64 bits");

_Static_assert(sizeof(i8_t)  == 1, "i8_t must be 8 bits");
_Static_assert(sizeof(i16_t) == 2, "i16_t must be 16 bits");
_Static_assert(sizeof(i32_t) == 4, "i32_t must be 32 bits");
_Static_assert(sizeof(i64_t) == 8, "i64_t must be 64 bits");

// 验证 byte_t/char_t 位数（char 通常为 8 位，特殊平台可提前发现）
_Static_assert(sizeof(byte_t) == 1, "byte_t must be 8 bits");
_Static_assert(sizeof(char_t) == 1, "char_t must be 8 bits");
#endif

#ifdef __cplusplus
}
#endif

#endif // ZYRTHI_HAL_DEF_H