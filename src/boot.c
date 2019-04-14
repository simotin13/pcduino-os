#include "common.h"
#include "uart.h"
#include "gpio.h"

void __attribute__((section(".start"))) __attribute__((naked)) start(void)
{
	asm volatile("b     main             \n"
		     ".long 0xffffffff       \n"
		     ".long 0xffffffff       \n"
		     ".long 0xffffffff       \n");
}

int main(void)
{
	gpio_init();
	uart0_init();

	uart0_puts("******** bootting from Allwinner A10 ********\n");
	uart0_puts("build at:");
	uart0_puts(__DATE__);
	uart0_puts(" ");
	uart0_puts(__TIME__);
	uart0_puts("n");

	while(1);

	return 0;
}
