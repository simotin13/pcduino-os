#include "common.h"
#include "uart.h"

static void clock_init_uart_legacy(void)
{
	/* Open the clock gate for UART0 */
	set_wbit(APB2_GATE, 1 << (APB2_GATE_UART_SHIFT + CONFIG_CONS_INDEX - 1));
	/* Deassert UART0 reset (only needed on A31/A64/H3) */
	set_wbit(APB2_RESET, 1 << (APB2_RESET_UART_SHIFT + CONFIG_CONS_INDEX - 1));
}

static void clock_init_uart(void)
{
	clock_init_uart_legacy();
}

void uart0_init(void)
{
	clock_init_uart();

	/* select dll dlh */
	writel(0x80, UART0_LCR);
	/* set baudrate */
	writel(0, UART0_DLH);
	writel(BAUD_115200, UART0_DLL);
	/* set line control */
	writel(LC_8_N_1, UART0_LCR);
}

void uart0_putc(char c)
{
	while (!(readl(UART0_LSR) & (1 << 6))) {}
	writel(c, UART0_THR);
}

void uart0_puts(const char *str)
{
	while (*str) {
		if (*str == '\n')
		{
			uart0_putc('\r');
		}
		uart0_putc(*str++);
	}
}
