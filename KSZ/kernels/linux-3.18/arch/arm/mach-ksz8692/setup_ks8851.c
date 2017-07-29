
#if defined(CONFIG_KS8851) || defined(CONFIG_KS8851_MODULE)
static struct spi_board_info ksz8851_sli_info[] __initdata = {
	[0] = {
		.modalias	= "ks8851",
#if 1
		.max_speed_hz	= 12500000,
#else
		.max_speed_hz	= 5000000,
#endif
		/* for KSZ8692 SPI master controller id/bus number */
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
#if defined(CONFIG_PEGASUS_NO_MDIO)
		.irq		= LOW_IRQS + KS8692_INT_EXT_INT2,
#else
		.irq		= LOW_IRQS + KS8692_INT_EXT_INT0,
#endif
#else
		.irq		= -1,
#endif
	},
	[1] = {
		.modalias	= "ks8851_2",
		.max_speed_hz	= 30000000,
		/* for FTDI master controller id/bus number */
		.bus_num	= 2,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		.irq		= LOW_IRQS + KS8692_INT_EXT_INT2,
#else
		.irq		= -1,
#endif
	},
};

static int __init ksz8851_sli_init(void)
{
	spi_register_board_info(ksz8851_sli_info,
		ARRAY_SIZE(ksz8851_sli_info));
	return 0;
}
arch_initcall(ksz8851_sli_init);
#endif
