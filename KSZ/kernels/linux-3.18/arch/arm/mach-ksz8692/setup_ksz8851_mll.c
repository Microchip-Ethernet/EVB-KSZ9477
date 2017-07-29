
#if defined(CONFIG_KS8851_MLL) || defined(CONFIG_KS8851_MLL_MODULE)

/* Change interrupt here. */
#ifdef CONFIG_MICREL_PEGASUS
#define IRQ_KSZ8851MLL		(LOW_IRQS + KS8692_INT_EXT_INT2)
#else
#define IRQ_KSZ8851MLL		-1
#endif

/* Change base address here. */
#define KSZ8851MLL_PA_DATA	(0x1f000000)

/* data line is address bus (here, connect to A2) */
#define CMD_HIGH		0x04

#define KSZ8851MLL_PA_CMD	(KSZ8851MLL_PA_DATA + CMD_HIGH)
#define KSZ8851MLL_SZ		4

static struct resource ksz8851mll_resource[] = {
	[0] = {
		.start = KSZ8851MLL_PA_DATA,
		.end   = KSZ8851MLL_PA_DATA + KSZ8851MLL_SZ - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = KSZ8851MLL_PA_CMD ,
		.end   = KSZ8851MLL_PA_CMD + KSZ8851MLL_SZ - 1,
		.flags = IORESOURCE_MEM,
	},
	[2] = {
		.start = IRQ_KSZ8851MLL,
		.end   = IRQ_KSZ8851MLL,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ksz8851mll_device = {
	.name		= "ks8851_mll",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ksz8851mll_resource),
	.resource	= ksz8851mll_resource,
};

static int __init platform_device_init(void)
{
	int ret;

	ret = platform_device_register(&ksz8851mll_device);
	return ret;
}
arch_initcall(platform_device_init);
#endif

