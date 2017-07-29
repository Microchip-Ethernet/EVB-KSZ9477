
#if defined(CONFIG_HAVE_SPI_KSZ8863)
static struct spi_board_info ksz8863_info[] __initdata = {
	[0] = {
		.modalias	= "ksz8863",
		.max_speed_hz	= 48000000,
		.bus_num	= 0,
#if defined(CONFIG_SPI_PEGASUS) || defined(CONFIG_SPI_PEGASUS_MODULE)
		.chip_select	= 2,
#else
		.chip_select	= 0,
#endif
		.mode		= SPI_MODE_3,
		.irq		= -1,
	},
	[1] = {
		.modalias	= "ksz8863",
		.max_speed_hz	= 48000000,
		.bus_num	= 0,
		.chip_select	= 1,
		.mode		= SPI_MODE_3,
		.irq		= -1,
	},
};

static int __init ksz8863_spi_init(void)
{
	spi_register_board_info(ksz8863_info, ARRAY_SIZE(ksz8863_info));
	return 0;
}
arch_initcall(ksz8863_spi_init);
#endif
