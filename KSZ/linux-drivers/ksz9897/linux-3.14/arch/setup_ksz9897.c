
#if defined(CONFIG_HAVE_SPI_KSZ9897)
static struct spi_board_info ksz9897_info[] __initdata = {
	[0] = {
		.modalias	= "ksz9897",

		/* Please adjust the maximum SPI clock speed as necessary. */
		.max_speed_hz	= 48000000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,

		/* Please provide a system interrupt number. */
		.irq		= -1,
	},
};

static int __init ksz9897_spi_init(void)
{
	spi_register_board_info(ksz9897_info, ARRAY_SIZE(ksz9897_info));
	return 0;
}
arch_initcall(ksz9897_spi_init);
#endif
