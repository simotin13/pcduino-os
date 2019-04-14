#include "gpio.h"

int sunxi_gpio_set_cfgpin(uint32_t pin, uint32_t val)
{
	uint32_t cfg;
	uint32_t bank = GPIO_BANK(pin);
	uint32_t index = GPIO_CFG_INDEX(pin);
	uint32_t offset = GPIO_CFG_OFFSET(pin);
	GPIO_REG *pio = &((A10_GPIO_REGS *)PIO_BASE)->gpio_bank[bank];
	cfg = readl(&pio->cfg[0] + index);
	cfg &= ~(0xf << offset);
	cfg |= val << offset;
	writel(cfg, &pio->cfg[0] + index);
	return 0;
}

void sunxi_gpio_set_pull(uint32_t pin, uint32_t val)
{
	uint32_t cfg;
	uint32_t bank = GPIO_BANK(pin);
	uint32_t index = GPIO_PULL_INDEX(pin);
	uint32_t offset = GPIO_PULL_OFFSET(pin);
	GPIO_REG *pio = &((A10_GPIO_REGS *)PIO_BASE)->gpio_bank[bank];
	cfg = readl(&pio->pull[0] + index);
	cfg &= ~(0x3 << offset);
	cfg |= val << offset;
	writel(cfg, &pio->pull[0] + index);
	return;
}

void sunxi_gpio_output(uint32_t pin, uint32_t val)
{
	uint32_t dat;
	uint32_t bank = GPIO_BANK(pin);
	uint32_t num = GPIO_NUM(pin);
	GPIO_REG *pio = &((A10_GPIO_REGS *)PIO_BASE)->gpio_bank[bank];
	dat = readl(&pio->dat);
	if(val) {
		dat |= 1 << num;
	} else {
		dat &= ~(1 << num);
	}
	writel(dat, &pio->dat);
	return;
}

int sunxi_gpio_input(uint32_t pin)
{
	uint32_t dat;
	uint32_t bank = GPIO_BANK(pin);
	uint32_t num = GPIO_NUM(pin);
	GPIO_REG *pio = &((A10_GPIO_REGS *)PIO_BASE)->gpio_bank[bank];
	dat = readl(&pio->dat);
	dat >>= num;
	return (dat & 0x1);
}

int gpio_direction_input(uint32_t gpio)
{
	sunxi_gpio_set_cfgpin(gpio, GPIO_INPUT);
	return sunxi_gpio_input(gpio);
}

void gpio_direction_output(uint32_t gpio, uint32_t value)
{
	sunxi_gpio_set_cfgpin(gpio, GPIO_OUTPUT);
	sunxi_gpio_output(gpio, value);
}

void gpio_init(void)
{
	sunxi_gpio_set_cfgpin(GPB(22), SUN4I_GPB_UART0);
	sunxi_gpio_set_cfgpin(GPB(23), SUN4I_GPB_UART0);
	sunxi_gpio_set_pull(GPB(23), GPIO_PULL_UP);
}

