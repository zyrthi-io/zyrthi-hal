#ifndef ZYRTHI_HAL_PWM_H
#define ZYRTHI_HAL_PWM_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

zyrthi_status_t zyrthi_pwm_write(int pin, uint32_t duty);

#ifdef __cplusplus
}
#endif

#endif
