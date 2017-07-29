
#if defined(CONFIG_KSZ8462_HLI) || defined(CONFIG_KSZ8462_HLI_MODULE)

/* data line is address bus (here, connect to A2) */
#define CMD_HIGH		0x04

/* (0x1c000000 + 0x03000000) */
#define KSZ8462HLI_PA_DATA	(0x1f000000)
#define KSZ8462HLI_PA_CMD	(KSZ8462HLI_PA_DATA + CMD_HIGH)
#define KSZ8462HLI_SZ		4

#define IRQ_KSZ8462HLI		0

static struct resource ksz8462hli_resource[] = {
	[0] = {
		.start = KSZ8462HLI_PA_DATA,
		.end   = KSZ8462HLI_PA_DATA + KSZ8462HLI_SZ - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = KSZ8462HLI_PA_CMD ,
		.end   = KSZ8462HLI_PA_CMD + KSZ8462HLI_SZ - 1,
		.flags = IORESOURCE_MEM,
	},
	[2] = {
		.start = IRQ_KSZ8462HLI,
		.end   = IRQ_KSZ8462HLI,
		.flags = IORESOURCE_IRQ,
	},
};

struct platform_device ksz8462hli_device = {
	.name		= "ksz8462_hli",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(ksz8462hli_resource),
	.resource	= ksz8462hli_resource,
};

static int __init ksz8462_init(void)
{
	return platform_device_register(&ksz8462hli_device);
}
arch_initcall(ksz8262_init);
#endif
