
#if defined(CONFIG_SPI_SPIDEV)
static struct spi_board_info kszdev_info[] __initdata = {
	[0] = {
		.modalias	= "spidev",
		.max_speed_hz	= 20000000,
		.bus_num	= 0,
		.chip_select	= 0,
		.mode		= SPI_MODE_3,
		.irq		= -1,
	},
};

static int __init ksz_spidev_init(void)
{
	spi_register_board_info(kszdev_info, ARRAY_SIZE(kszdev_info));
	return 0;
}
arch_initcall(ksz_spidev_init);
#endif
