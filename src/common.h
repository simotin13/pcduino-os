#ifndef __COMMON_H___
#define __COMMON_H___

typedef unsigned char	uint8_t;
typedef char			int8_t;
typedef unsigned short	uint16_t;
typedef short			int16_t;
typedef unsigned int	uint32_t;
typedef int				int32_t;

#define set_wbit(addr, v)	(*((volatile unsigned long  *)(addr)) |= (unsigned long)(v))
#define readl(addr)			(*((volatile unsigned long  *)(addr)))
#define writel(v, addr)		(*((volatile unsigned long  *)(addr)) = (unsigned long)(v))

#endif	// __COMMON_H__