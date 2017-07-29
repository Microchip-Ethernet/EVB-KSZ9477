
#if defined(CONFIG_HAVE_SPI_KSZ8895)
static struct spi_board_info ksz8895_info[] __initdata = {
	[0] = {
		.modalias	= "ksz8895",
		.max_speed_hz	= 25000000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		.irq		= LOW_IRQS + KS8692_INT_EXT_INT0,
#else
		.irq		= -1,
#endif
	},
};

static int __init ksz8895_spi_init(void)
{
	spi_register_board_info(ksz8895_info, ARRAY_SIZE(ksz8895_info));
	return 0;
}
arch_initcall(ksz8895_spi_init);
#endif
