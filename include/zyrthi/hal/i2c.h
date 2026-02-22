#ifndef ZYRTHI_HAL_I2C_H
#define ZYRTHI_HAL_I2C_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* zyrthi_i2c_handle_t;

zyrthi_i2c_handle_t zyrthi_i2c_default(void);
zyrthi_status_t     zyrthi_i2c_init(zyrthi_i2c_handle_t i2c, uint32_t clock_hz);

// 必须按顺序调用: begin -> write/read -> end
zyrthi_status_t zyrthi_i2c_begin_transmission(zyrthi_i2c_handle_t i2c, uint8_t addr);
zyrthi_status_t zyrthi_i2c_write(zyrthi_i2c_handle_t i2c, const uint8_t* data, uint32_t len);
int              zyrthi_i2c_read(zyrthi_i2c_handle_t i2c, uint8_t* buf, uint32_t len);
zyrthi_status_t zyrthi_i2c_end_transmission(zyrthi_i2c_handle_t i2c);

#ifdef __cplusplus
}
#endif

#endif
