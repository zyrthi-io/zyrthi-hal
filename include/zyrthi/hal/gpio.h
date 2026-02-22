#ifndef ZYRTHI_HAL_GPIO_H
#define ZYRTHI_HAL_GPIO_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

void zyrthi_gpio_mode(int pin, zyrthi_pin_mode_t mode);
void zyrthi_gpio_write(int pin, zyrthi_voltage_t value);
zyrthi_voltage_t zyrthi_gpio_read(int pin);

#ifdef __cplusplus
}
#endif

#endif
