#
# Makefile for the linux kernel.
#

# Object file lists.

obj-y                       := board-micrel.o gpio.o

obj-$(CONFIG_LEDS_CLASS)		+= leds.o
obj-$(CONFIG_PCI)			+= ks8692_pci.o pci.o
obj-$(CONFIG_CPU_FREQ_INTEGRATOR)	+= cpu.o
