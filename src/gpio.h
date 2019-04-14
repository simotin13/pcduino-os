#ifndef __GPIO_H__
#define __GPIO_H__
#include "common.h"

#define PIO_BASE		(0x01C20800)
#define GPIO_A    		(0)
#define GPIO_B    		(1)
#define GPIO_C    		(2)
#define GPIO_D    		(3)
#define GPIO_E    		(4)
#define GPIO_F    		(5)
#define GPIO_G    		(6)
#define GPIO_H    		(7)
#define GPIO_I    		(8)

/* GPIO bank sizes */
#define GPIO_BANK_SIZE	(32)

#define GPIO_NEXT(__gpio) ((__gpio##_START) + GPIO_BANK_SIZE)

enum sunxi_gpio_number
{
	GPIO_A_START = 0,
	GPIO_B_START = GPIO_A_START + GPIO_BANK_SIZE,
	GPIO_C_START = GPIO_B_START + GPIO_BANK_SIZE,
	GPIO_D_START = GPIO_C_START + GPIO_BANK_SIZE,
	GPIO_E_START = GPIO_D_START + GPIO_BANK_SIZE,
	GPIO_F_START = GPIO_E_START + GPIO_BANK_SIZE,
	GPIO_G_START = GPIO_F_START + GPIO_BANK_SIZE,
	GPIO_H_START = GPIO_G_START + GPIO_BANK_SIZE,
	GPIO_I_START = GPIO_H_START + GPIO_BANK_SIZE,
};

typedef struct GPIO_REG
{
	uint32_t cfg[4];
	uint32_t dat;
	uint32_t drv[2];
	uint32_t pull[2];
} GPIO_REG;

typedef struct A10_GPIO_REGS
{
	GPIO_REG gpio_bank[10];
} A10_GPIO_REGS;

#define GPIO_BANK(pin)			((pin) >> 5)
#define GPIO_NUM(pin)			((pin) & 0x1F)

#define GPIO_CFG_INDEX(pin)		(((pin) & 0x1F) >> 3)
#define GPIO_CFG_OFFSET(pin)	((((pin) & 0x1F) & 0x7) << 2)

#define GPIO_PULL_INDEX(pin)	(((pin) & 0x1f) >> 4)
#define GPIO_PULL_OFFSET(pin)	((((pin) & 0x1f) & 0xf) << 1)

/* SUNXI GPIO number definitions */
#define GPA(_nr)				(GPIO_A_START + (_nr))
#define GPB(_nr)				(GPIO_B_START + (_nr))
#define GPC(_nr)				(GPIO_C_START + (_nr))
#define GPD(_nr)				(GPIO_D_START + (_nr))
#define GPE(_nr)				(GPIO_E_START + (_nr))
#define GPF(_nr)				(GPIO_F_START + (_nr))
#define GPG(_nr)				(GPIO_G_START + (_nr))
#define GPH(_nr)				(GPIO_H_START + (_nr))
#define GPI(_nr)				(GPIO_I_START + (_nr))

/* GPIO pin function config */
#define GPIO_INPUT        		(0)
#define GPIO_OUTPUT       		(1)
#define SUN4I_GPB_UART0   		(2)
#define SUN5I_GPB_UART0   		(2)
#define SUN6I_GPH_UART0   		(2)
#define GPF_UART0         		(4)

/* GPIO pin pull-up/down config */
#define GPIO_PULL_DISABLE 		(0)
#define GPIO_PULL_UP      		(1)
#define GPIO_PULL_DOWN    		(2)

// =============================================================================
// Function prototype
// =============================================================================
extern void gpio_init(void);
extern int sunxi_gpio_set_cfgpin(uint32_t pin, uint32_t val);
extern int gpio_direction_input(uint32_t gpio);
extern void gpio_direction_output(uint32_t gpio, uint32_t value);
extern int sunxi_gpio_input(uint32_t pin);
extern void sunxi_gpio_output(uint32_t pin, uint32_t val);
extern void sunxi_gpio_set_pull(uint32_t pin, uint32_t val);

#endif // __GPIO_H__