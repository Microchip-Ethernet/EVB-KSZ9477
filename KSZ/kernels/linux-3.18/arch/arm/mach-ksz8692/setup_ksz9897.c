
#if defined(CONFIG_HAVE_SPI_KSZ9897)
static struct spi_board_info ksz9897_info[] __initdata = {
	[0] = {
		.modalias	= "ksz9897",
		.max_speed_hz	= 12500000,
		/* for KSZ8692 SPI master controller id/bus number */
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		.irq		= LOW_IRQS + KS8692_INT_EXT_INT0,
#else
		.irq		= -1,
#endif
	},
	[1] = {
		.modalias	= "ksz9897_2",
		.max_speed_hz	= 30000000,
		/* for FTDI master controller id/bus number */
		.bus_num	= 2,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		.irq		= LOW_IRQS + KS8692_INT_EXT_INT0,
#else
		.irq		= -1,
#endif
	},
};

static int __init ksz9897_spi_init(void)
{
	spi_register_board_info(ksz9897_info, ARRAY_SIZE(ksz9897_info));
	return 0;
}
arch_initcall(ksz9897_spi_init);
#endif
