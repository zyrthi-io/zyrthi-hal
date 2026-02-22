#ifndef ZYRTHI_HAL_TIME_H
#define ZYRTHI_HAL_TIME_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t zyrthi_millis(void);
uint32_t zyrthi_micros(void);
void     zyrthi_delay_ms(uint32_t ms);
void     zyrthi_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif
