
#if defined(CONFIG_HAVE_SPI_KSZ8463)
static struct spi_board_info ksz8463_info[] __initdata = {
	[0] = {
		.modalias	= "ksz8463",

		/* Please adjust the maximum SPI clock speed as necessary. */
		.max_speed_hz	= 48000000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,

		/* Please provide a system interrupt number. */
		.irq		= -1,
	},
	[1] = {
		.modalias	= "ksz8463_2",

		/* Please adjust the maximum SPI clock speed as necessary. */
		.max_speed_hz	= 30000000,
		/* for FTDI master controller id/bus number */
		.bus_num	= 2,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,

		/* Please provide a system interrupt number. */
		.irq		= -1,
	},
};

static int __init ksz8463_spi_init(void)
{
	spi_register_board_info(ksz8463_info, ARRAY_SIZE(ksz8463_info));
	return 0;
}
arch_initcall(ksz8463_spi_init);
#endif
