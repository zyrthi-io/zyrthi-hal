#ifndef ZYRTHI_HAL_DEF_H
#define ZYRTHI_HAL_DEF_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ZYRTHI_LOW  = 0,
    ZYRTHI_HIGH = 1
} zyrthi_voltage_t;

typedef enum {
    ZYRTHI_INPUT          = 0,
    ZYRTHI_OUTPUT         = 1,
    ZYRTHI_INPUT_PULLUP   = 2,
    ZYRTHI_INPUT_PULLDOWN = 3
} zyrthi_pin_mode_t;

typedef enum {
    ZYRTHI_OK               = 0,
    ZYRTHI_ERROR_INVALID_PIN     = -1,
    ZYRTHI_ERROR_INVALID_ARG     = -2,
    ZYRTHI_ERROR_UNSUPPORTED     = -3,
    ZYRTHI_ERROR_TIMEOUT         = -4,
    ZYRTHI_ERROR_NACK            = -5,
    ZYRTHI_ERROR_BUSY            = -6
} zyrthi_status_t;

#ifdef __cplusplus
}
#endif

#endif
