#ifndef __UART_H__
#define __UART_H__
#include "common.h"

#define UART0_BASE				(0x01C28000)
#define AW_CCM_BASE				(0x01c20000)
#define CONFIG_CONS_INDEX		(1)
#define APB2_CFG				(AW_CCM_BASE + 0x058)
#define APB2_GATE				(AW_CCM_BASE + 0x06C)
#define APB2_RESET				(AW_CCM_BASE + 0x2D8)
#define APB2_GATE_UART_SHIFT	(16)
#define APB2_RESET_UART_SHIFT	(16)

#define UART0_RBR (UART0_BASE + 0x0)    /* receive buffer register */
#define UART0_THR (UART0_BASE + 0x0)    /* transmit holding register */
#define UART0_DLL (UART0_BASE + 0x0)    /* divisor latch low register */
#define UART0_DLH (UART0_BASE + 0x4)    /* divisor latch high register */
#define UART0_IER (UART0_BASE + 0x4)    /* interrupt enable reigster */
#define UART0_IIR (UART0_BASE + 0x8)    /* interrupt identity register */
#define UART0_FCR (UART0_BASE + 0x8)    /* fifo control register */
#define UART0_LCR (UART0_BASE + 0xc)    /* line control register */
#define UART0_LSR (UART0_BASE + 0x14)   /* line status register */

#define BAUD_115200    (0xD) /* 24 * 1000 * 1000 / 16 / 115200 = 13 */
#define NO_PARITY      (0)
#define ONE_STOP_BIT   (0)
#define DAT_LEN_8_BITS (3)
#define LC_8_N_1       (NO_PARITY << 3 | ONE_STOP_BIT << 2 | DAT_LEN_8_BITS)

// =============================================================================
// Function prototype
// =============================================================================
extern void uart0_init(void);
extern void uart0_putc(char c);
extern void uart0_puts(const char *str);

#endif	// __UART_H__