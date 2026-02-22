#ifndef ZYRTHI_HAL_UART_H
#define ZYRTHI_HAL_UART_H

#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* zyrthi_uart_handle_t;

zyrthi_uart_handle_t zyrthi_uart_default(void);
zyrthi_status_t      zyrthi_uart_init(zyrthi_uart_handle_t uart, uint32_t baud);
void                 zyrthi_uart_putc(zyrthi_uart_handle_t uart, uint8_t c);
int                  zyrthi_uart_getc(zyrthi_uart_handle_t uart);
bool                 zyrthi_uart_available(zyrthi_uart_handle_t uart);

#ifdef __cplusplus
}
#endif

#endif
