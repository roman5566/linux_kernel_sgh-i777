/*
 * Copyright (C) 2010 Samsung Electronics Co. Ltd.
 *	Jaswinder Singh <jassi.brar@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/platform_device.h>
#include <linux/dma-mapping.h>

#include <plat/devs.h>
#include <plat/irqs.h>

#include <mach/map.h>
#include <mach/irqs.h>

#include <plat/s3c-pl330-pdata.h>

static u64 dma_dmamask = DMA_BIT_MASK(32);

static struct resource s5p6450_pdma_resource[] = {
	[0] = {
		.start  = S5P6450_PA_PDMA,
		.end    = S5P6450_PA_PDMA + SZ_4K,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_DMA0,
		.end	= IRQ_DMA0,
		.flags	= IORESOURCE_IRQ,
	},
};

static struct s3c_pl330_platdata s5p6450_pdma_pdata = {
	.peri = {
		[0] = DMACH_UART0_RX,
		[1] = DMACH_UART0_TX,
		[2] = DMACH_UART1_RX,
		[3] = DMACH_UART1_TX,
		[4] = DMACH_UART2_RX,
		[5] = DMACH_UART2_TX,
		[6] = DMACH_UART3_RX,
		[7] = DMACH_UART3_TX,
		[8] = DMACH_UART4_RX,
		[9] = DMACH_UART4_TX,
		[10] = DMACH_PCM0_TX,
		[11] = DMACH_PCM0_RX,
		[12] = DMACH_I2S0_TX,
		[13] = DMACH_I2S0_RX,
		[14] = DMACH_SPI0_TX,
		[15] = DMACH_SPI0_RX,
		[16] = DMACH_PCM1_TX,
		[17] = DMACH_PCM1_RX,
		[18] = DMACH_PCM2_TX,
		[19] = DMACH_PCM2_RX,
		[20] = DMACH_SPI1_TX,
		[21] = DMACH_SPI1_RX,
		[22] = DMACH_USI_TX,
		[23] = DMACH_USI_RX,
		[24] = DMACH_MAX,
		[25] = DMACH_I2S1_TX,
		[26] = DMACH_I2S1_RX,
		[27] = DMACH_I2S2_TX,
		[28] = DMACH_I2S2_RX,
		[29] = DMACH_PWM,
		[30] = DMACH_UART5_RX,
		[31] = DMACH_UART5_TX,
	},
};

static struct platform_device s5p6450_device_pdma = {
	.name		= "s3c-pl330",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(s5p6450_pdma_resource),
	.resource	= s5p6450_pdma_resource,
	.dev		= {
		.dma_mask = &dma_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platform_data = &s5p6450_pdma_pdata,
	},
};

static struct platform_device *s5p6450_dmacs[] __initdata = {
	&s5p6450_device_pdma,
};

static int __init s5p6450_dma_init(void)
{
	platform_add_devices(s5p6450_dmacs, ARRAY_SIZE(s5p6450_dmacs));

	return 0;
}
arch_initcall(s5p6450_dma_init);
