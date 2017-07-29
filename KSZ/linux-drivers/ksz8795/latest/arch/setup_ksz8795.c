
#if defined(CONFIG_HAVE_SPI_KSZ8795)
static struct spi_board_info ksz8795_info[] __initdata = {
	[0] = {
		.modalias	= "ksz8795",

		/* Please adjust the maximum SPI clock speed as necessary. */
		.max_speed_hz	= 48000000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,

		/* Please provide a system interrupt number. */
		.irq		= -1,
	},
};

static int __init ksz8795_spi_init(void)
{
	spi_register_board_info(ksz8795_info, ARRAY_SIZE(ksz8795_info));
	return 0;
}
arch_initcall(ksz8795_spi_init);
#endif
