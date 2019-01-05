/**
 * KSZ8462 register definitions
 *
 * Copyright 2015 Microchip Technology Inc.
 *
 * Copyright 2011-2014 Micrel, Inc.
 *
 * Copyright 2009 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/


#ifndef __KSZ8462_H
#define __KSZ8462_H


#define KS_CCR				0x108
#define CCR_LITTLE_ENDIAN		(1 << 10)
#define CCR_EEPROM			(1 << 9)
#define CCR_SPI				(1 << 8)
#define CCR_8BIT			(1 << 7)
#define CCR_16BIT			(1 << 6)
#define CCR_32BIT			(1 << 5)
#define CCR_SHARED			(1 << 4)
#define CCR_64PIN			(1 << 1)
#define CCR_32PIN			(1 << 0)

/* MAC address registers */
#define KS_MARL				0x110
#define KS_MARM				0x112
#define KS_MARH				0x114

#define KS_EEPCR			0x122
#define EEPCR_EEDW			(1 << 5)
#define EEPCR_EESA			(1 << 4)
#define EEPCR_EESB			(1 << 3)
#define EEPCR_EEDO			(1 << 2)
#define EEPCR_EESCK			(1 << 1)
#define EEPCR_EECS			(1 << 0)

#define KS_MBIR				0x124
#define MBIR_DONE			(1 << 15)
#define MBIR_TXMBF			(1 << 12)
#define MBIR_TXMBFA			(1 << 11)
#define MBIR_TX_SHIFT			(8)
#define MBIR_RXMBF			(1 << 4)
#define MBIR_RXMBFA			(1 << 3)
#define MBIR_RX_SHIFT			(0)
#define MBIR_FAIL_CNT			(0x7)

#define KS_GRR				0x126
#define GRR_BIST			(1 << 3)
#define GRR_PTP				(1 << 2)
#define GRR_QMU				(1 << 1)
#define GRR_GSR				(1 << 0)

#define KS_WFCR				0x12A
#define WFCR_MPRXE			(1 << 7)
#define WFCR_WF3E			(1 << 3)
#define WFCR_WF2E			(1 << 2)
#define WFCR_WF1E			(1 << 1)
#define WFCR_WF0E			(1 << 0)

#define KS_WF0CRC0			0x130
#define KS_WF0CRC1			0x132
#define KS_WF0BM0			0x134
#define KS_WF0BM1			0x136
#define KS_WF0BM2			0x138
#define KS_WF0BM3			0x13A

#define KS_WF1CRC0			0x140
#define KS_WF1CRC1			0x142
#define KS_WF1BM0			0x144
#define KS_WF1BM1			0x146
#define KS_WF1BM2			0x148
#define KS_WF1BM3			0x14A

#define KS_WF2CRC0			0x150
#define KS_WF2CRC1			0x152
#define KS_WF2BM0			0x154
#define KS_WF2BM1			0x156
#define KS_WF2BM2			0x158
#define KS_WF2BM3			0x15A

#define KS_WF3CRC0			0x160
#define KS_WF3CRC1			0x162
#define KS_WF3BM0			0x164
#define KS_WF3BM1			0x166
#define KS_WF3BM2			0x168
#define KS_WF3BM3			0x16A

#define KS_TXCR				0x170
#define TXCR_TCGICMP			(1 << 8)
#define TXCR_TCGUDP			(1 << 7)
#define TXCR_TCGTCP			(1 << 6)
#define TXCR_TCGIP			(1 << 5)
#define TXCR_FTXQ			(1 << 4)
#define TXCR_TXFCE			(1 << 3)
#define TXCR_TXPE			(1 << 2)
#define TXCR_TXCRC			(1 << 1)
#define TXCR_TXE			(1 << 0)

#define KS_TXSR				0x172
#define TXSR_TXLC			(1 << 13)
#define TXSR_TXMC			(1 << 12)
#define TXFID_MASK			(0x3f)
#define TXFID_SHIFT			(0)
#define TXSR_TXFID_MASK			(TXFID_MASK << TXFID_SHIFT)
#define TXSR_TXFID_GET(_v)		(((_v) >> TXFID_SHIFT) & TXFID_MASK)

#define KS_RXCR1			0x174
#define RXCR1_FRXQ			(1 << 15)
#define RXCR1_RXUDPFCC			(1 << 14)
#define RXCR1_RXTCPFCC			(1 << 13)
#define RXCR1_RXIPFCC			(1 << 12)
#define RXCR1_RXPAFMA			(1 << 11)
#define RXCR1_RXFCE			(1 << 10)
#define RXCR1_RXEFE			(1 << 9)
#define RXCR1_RXMAFMA			(1 << 8)
#define RXCR1_RXBE			(1 << 7)
#define RXCR1_RXME			(1 << 6)
#define RXCR1_RXUE			(1 << 5)
#define RXCR1_RXAE			(1 << 4)
#define RXCR1_RXINVF			(1 << 1)
#define RXCR1_RXE			(1 << 0)
#define RXCR1_FILTER_MASK		(RXCR1_RXINVF | RXCR1_RXAE | \
					 RXCR1_RXMAFMA | RXCR1_RXPAFMA)

#define RX_TYPE_CFG_2			(1 << 11)
#define RX_TYPE_CFG_1			(1 << 8)
#define RX_TYPE_ALL			(1 << 4)
#define RX_TYPE_INVERSE			(1 << 1)

#define RX_PROMISCUOUS			(RX_TYPE_ALL | RX_TYPE_INVERSE)
#define RX_ALL_HASH			(0)
#define RX_ALL_HASH_INVERSE		(RX_ALL_HASH | RX_TYPE_INVERSE)
#define RX_ALL_SAME			(RX_TYPE_CFG_2 | RX_TYPE_CFG_1)
#define RX_ALL_SAME_INVERSE		(RX_ALL_SAME | RX_TYPE_INVERSE)
#define RX_UNI_SAME_MULTI_HASH		(RX_TYPE_CFG_2)
#define RX_UNI_SAME_MULTI_HASH_INVERSE	\
	(RX_UNI_SAME_MULTI_HASH | RX_TYPE_INVERSE)
#define RX_UNI_HASH_ALL_MULTI		(RX_TYPE_ALL)
#define RX_UNI_SAME_ALL_MULTI		\
	(RX_TYPE_CFG_2 | RX_TYPE_CFG_1 | RX_TYPE_ALL)
#define RX_MULTI_HASH_ALL_UNI		(RX_TYPE_CFG_2 | RX_TYPE_ALL)
#define RX_MULTI_SAME_ALL_UNI		(RX_TYPE_CFG_1 | RX_TYPE_ALL)

#define KS_RXCR2			0x176
#ifdef KSZ846X_SLI
#define RXCR2_SRDBL_MASK		(0x7 << 5)
#define RXCR2_SRDBL_SHIFT		(5)
#define RXCR2_SRDBL_4B			(0x0 << 5)
#define RXCR2_SRDBL_8B			(0x1 << 5)
#define RXCR2_SRDBL_16B			(0x2 << 5)
#define RXCR2_SRDBL_32B			(0x3 << 5)
#define RXCR2_SRDBL_FRAME		(0x4 << 5)
#endif
#define RXCR2_PAUSE_TIMER		(1 << 8)
#define RXCR2_IUFFP			(1 << 4)
#define RXCR2_RXIUFCEZ			(1 << 3)
#define RXCR2_UDPLFE			(1 << 2)
#define RXCR2_RXICMPFCC			(1 << 1)
#define RXCR2_RXSAF			(1 << 0)

#define KS_TXMIR			0x178

#define KS_RXBUFSIZE			0x17A

#define KS_RXFHSR			0x17C
#define RXFSHR_RXFV			(1 << 15)
#define RXFSHR_RXICMPFCS		(1 << 13)
#define RXFSHR_RXIPFCS			(1 << 12)
#define RXFSHR_RXTCPFCS			(1 << 11)
#define RXFSHR_RXUDPFCS			(1 << 10)
#define RXFSHR_RXBF			(1 << 7)
#define RXFSHR_RXMF			(1 << 6)
#define RXFSHR_RXUF			(1 << 5)
#define RXFSHR_RXMR			(1 << 4)
#define RXFSHR_RXFT			(1 << 3)
#define RXFSHR_RXFTL			(1 << 2)
#define RXFSHR_RXRF			(1 << 1)
#define RXFSHR_RXCE			(1 << 0)
#define	RXFSHR_ERR			(RXFSHR_RXCE | RXFSHR_RXRF | \
					RXFSHR_RXFTL | RXFSHR_RXMR | \
					RXFSHR_RXIPFCS | RXFSHR_RXTCPFCS)

#define KS_RXFHBCR			0x17E
#define RXFHBCR_CNT_MASK		(0x0fff)

#define KS_TXQCR			0x180
#define TXQCR_TXQMAM			(1 << 1)
#define TXQCR_METFE			(1 << 0)

#define KS_RXQCR			0x182
#define RXQCR_RXDTTS			(1 << 12)
#define RXQCR_RXDBCTS			(1 << 11)
#define RXQCR_RXFCTS			(1 << 10)
#define RXQCR_RXIPHTOE			(1 << 9)
#define RXQCR_RXDTTE			(1 << 7)
#define RXQCR_RXDBCTE			(1 << 6)
#define RXQCR_RXFCTE			(1 << 5)
#define RXQCR_ADRFE			(1 << 4)
#define RXQCR_SDA			(1 << 3)
#define RXQCR_RRXEF			(1 << 0)
#define RXQCR_CMD_CNTL			(RXQCR_RXFCTE | RXQCR_ADRFE)
#define RXQCR_STATUS			\
	(RXQCR_RXDTTS | RXQCR_RXDBCTS | RXQCR_RXFCTS)

#define KS_TXFDPR			0x184
#define TXFDPR_TXFPAI			(1 << 14)
#define TXFDPR_TXFP_MASK		(0x7ff)

#define KS_RXFDPR			0x186
#define RXFDPR_RXFPAI			(1 << 14)
#define RXFDPR_EMS			(1 << 11)

#define KS_RXDTTR			0x18C
#define RXDTTR_MAX			0xcfff

#define KS_RXDBCTR			0x18E

#define KS_IER				0x190
#define KS_ISR				0x192
#define IRQ_LCI				(1 << 15)
#define IRQ_TXI				(1 << 14)
#define IRQ_RXI				(1 << 13)
#define IRQ_TS				(1 << 12)
#define IRQ_RXOI			(1 << 11)
#define IRQ_TRIG			(1 << 10)
#define IRQ_TXPSI			(1 << 9)
#define IRQ_RXPSI			(1 << 8)
#define IRQ_TXSAI			(1 << 6)
#define IRQ_RXWFDI			(1 << 5)
#define IRQ_RXMPDI			(1 << 4)
#define IRQ_LDI				(1 << 3)
#define IRQ_EDI				(1 << 2)
#define IRQ_SPIBEI			(1 << 1)
#define IRQ_DEDI			(1 << 0)

#define KS_RXFTR			0x19C
#define RXFTR_MASK			(0x00ff)

#define KS_TXNTFSR			0x19E

#define KS_MAHTR0			0x1A0
#define KS_MAHTR1			0x1A2
#define KS_MAHTR2			0x1A4
#define KS_MAHTR3			0x1A6

#define KS_FCLWR			0x1B0
#define KS_FCHWR			0x1B2
#define KS_FCOWR			0x1B4

#define KS_RXFC				0x1B8
#define RXFC_MASK			(0xff)
#define RXFC_SHIFT			(8)
#define RXFC_GET(_v)			(((_v) >> RXFC_SHIFT) & RXFC_MASK)

#define KS_CIDER			0x0
#ifdef KSZ846X_HLI
#define CIDER_ID_8462			(0x8430)
#define CIDER_ID_8441			(0x8410)
#endif
#ifdef KSZ846X_SLI
#define CIDER_ID_8462			(0x8420)
#define CIDER_ID_8441			(0x8400)
#endif
#define CIDER_ID_MASK			(~0xf)
#define CIDER_REV_MASK			(0x7)
#define CIDER_REV_SHIFT			(1)
#define CIDER_REV_GET(_v)		(((_v) >> CIDER_REV_SHIFT) & \
	CIDER_REV_MASK)

#define KS_PMCTRL			0x032
#define PMCTRL_WKEVT_MASK		(0xf << 2)
#define PMCTRL_WKEVT_FRAME		(1 << 5)
#define PMCTRL_WKEVT_MAGICPKT		(1 << 4)
#define PMCTRL_WKEVT_LINK		(1 << 3)
#define PMCTRL_WKEVT_ENERGY		(1 << 2)
#define PMCTRL_PM_MASK			(0x3 << 0)
#define PMCTRL_PM_NORMAL		(0x0 << 0)
#define PMCTRL_PM_ENERGY		(0x1 << 0)
#define PMCTRL_PM_SOFTDOWN		(0x2 << 0)
#define PMCTRL_PM_RESERVED		(0x3 << 0)

#define KS_PME				0x034

#define PME_POLARITY			(1 << 4)
#define PME_WOL_WAKEUP			(1 << 3)
#define PME_WOL_MAGICPKT		(1 << 2)
#define PME_WOL_LINKUP			(1 << 1)
#define PME_WOL_ENERGY			(1 << 0)

#define KS_GST				0x036
#define GST_MASK			(0x000f)

#define KS_CTPDC			0x038
#define CTPDC_PLL_AUTO_POWERDOWN	(1 << 4)
#define CTPDC_SWITCH_CLK_AUTO_SHUTDOWN	(1 << 3)
#define CTPDC_CPU_CLK_AUTO_SHUTDOWN	(1 << 2)
#define CTPDC_WAIT_PERIOD_MASK		(3)
#define CTPDC_WAIT_5_3_S		0
#define CTPDC_WAIT_1_6_S		1
#define CTPDC_WAIT_1_0_mS		2
#define CTPDC_WAIT_3_2_uS		3

/* TX Frame control */

#define TXFR_TXIC			(1 << 15)
#define TXFR_TXFID_MASK			(TXFID_MASK << TXFID_SHIFT)

#endif
