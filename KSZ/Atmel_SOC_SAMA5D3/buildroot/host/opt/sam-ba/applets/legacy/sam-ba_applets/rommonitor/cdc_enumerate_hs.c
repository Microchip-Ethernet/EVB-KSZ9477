//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : cdc_enumerate_hs.c
//* Object              : Handle CDC enumeration for UDP HS
//*
//* 1.0 Apr 20 2004     : ODi Creation
//* 1.1 Jun 15 2006     : JCB Change for AT91SAM9265
//*----------------------------------------------------------------------------
#include "main.h"

#ifdef UDP_HIGH_SPEED

#define USE_DMA_IN  1
#define USE_DMA_OUT 1

#define DMA_BUF_SIZE 0x10000

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define SHIFT_INTERUPT    8

//! CDC Class Specific Request Code
//! Table 4: Requests - Abstract Control Model (usbcdc11.pdf)
#define CDC_GET_LINE_CODING               0x21
#define CDC_SET_LINE_CODING               0x20
#define CDC_SET_CONTROL_LINE_STATE        0x22

// Table 2.1 - SubClassCodes Mapped to Command Block Specifications (usb_msc_overview_1.2.pdf)
#define SUBCLASSCODE_RBC     0x01     // Reduced Block Commands (RBC) T10
#define SUBCLASSCODE_SFF_MCC 0x02     // C/DVD devices
#define SUBCLASSCODE_QIC     0x03     // Tape device
#define SUBCLASSCODE_UFI     0x04     // Floppy disk drive (FDD) device
#define SUBCLASSCODE_SFF     0x05     // Floppy disk drive (FDD) device
#define SUBCLASSCODE_SCSI    0x06     // SCSI transparent command set
//                        0x07 - 0xFF // Reserved for futur use

//! Table 24: Type Values for the bDescriptorType Field (usbcdc11.pdf)
#define CDC_CS_INTERFACE 0x24 //!< Type values for the bDescriptorType field
#define CDC_CS_ENDPOINT  0x25 //!< Type values for the bDescriptorType field

//! Table 25: bDescriptor SubType in Functional Descriptors (usbcdc11.pdf)
#define CDC_ST_HEADER    0x00 //!< Header functional descriptor
#define CDC_ST_CMF       0x01 //!< Call Management functional descriptor
#define CDC_ST_ACM       0x02 //!< Abstract Control Management functional descriptor
#define CDC_ST_UNION     0x06 //!< Union functional descriptor

const char devDescriptor[] = {
    /* Device descriptor */
    0x12,   // bLength
    USB_DEVICE_DESCRIPTOR,   // bDescriptorType
    0x00,   // bcdUSBL
    0x02,   //
    0x02,   // bDeviceClass:    CDC class code
    0x00,   // bDeviceSubclass: CDC class sub code
    0x00,   // bDeviceProtocol: CDC Device protocol
    0x40,   // bMaxPacketSize0
    0xEB,   // idVendorL
    0x03,   //
    0x24,   // idProductL
    0x61,   //
    0x10,   // bcdDeviceL
    0x01,   //
    0x00,   // iManufacturer    // 0x01
    0x00,   // iProduct
    0x00,   // SerialNumber
    0x01    // bNumConfigs
};

const char devQualDescriptor[] = {
    /* Device descriptor */
    0x0A,   // bLength
    USB_DEVICE_QUALIFIER_DESCRIPTOR,   // bDescriptorType
    0x00,   // bcdUSBL
    0x02,   //
    0x02,   // bDeviceClass:    CDC class code
    0x00,   // bDeviceSubclass: CDC class sub code
    0x00,   // bDeviceProtocol: CDC Device protocol
    0x40,   // bMaxPacketSize0
    0x01,   // bNumConfigs
    0x00
};

#define MAXPACKETCTRL (unsigned short)(devDescriptor[7])
#define MAXPACKETSIZEOUT (unsigned short)(sConfiguration[57]+(sConfiguration[58]<<8))
#define OSCMAXPACKETSIZEOUT (unsigned short)(sOtherSpeedConfiguration[57]+(sOtherSpeedConfiguration[58]<<8))
#define MAXPACKETSIZEIN (unsigned short)(sConfiguration[64]+(sConfiguration[65]<<8))
#define OSCMAXPACKETSIZEIN (unsigned short)(sOtherSpeedConfiguration[64]+(sOtherSpeedConfiguration[65]<<8))
#define MAXPACKETSIZEINTER (unsigned short)(sConfiguration[41]+(sConfiguration[42]<<8))
#define OSCMAXPACKETSIZEINTER (unsigned short)(sOtherSpeedConfiguration[41]+(sOtherSpeedConfiguration[42]<<8))

char sConfiguration[] = {
    //! ============== CONFIGURATION 1 ===========
    //! Table 9-10. Standard Configuration Descriptor
    0x09,                            // bLength;              //!< size of this descriptor in bytes
    USB_CONFIGURATION_DESCRIPTOR,    // bDescriptorType;      //!< CONFIGURATION descriptor type
    0x43,                            // wTotalLength;         //!< total length of data returned 2 EP + Control
    0x00,
    0x02,                            // bNumInterfaces;       //!< number of interfaces for this conf
    0x01,                            // bConfigurationValue;  //!< value for SetConfiguration resquest
    0x00,                            // iConfiguration;       //!< index of string descriptor
    USB_CONFIG_SELF_NOWAKEUP,        // bmAttibutes;          //!< Configuration characteristics
    0x00,                            // MaxPower;             //!< maximum power consumption

    //! Communication Class Interface Descriptor Requirement
    //! Table 9-12. Standard Interface Descriptor
    0x09,                       // Size of this descriptor in bytes
    USB_INTERFACE_DESCRIPTOR,   // INTERFACE Descriptor Type
    0x00,                       // bInterfaceNumber
    0x00,                       // bAlternateSetting
    0x01,                       // bNumEndpoints
    USB_DEVICE_CLASS_MODEM_CDC, // bInterfaceClass
    SUBCLASSCODE_SFF_MCC,       // bInterfaceSubclass
    0x00,                       // bInterfaceProtocol
    0x00,                       // iInterface

    //! 5.2.3.1 Header Functional Descriptor (usbcdc11.pdf)
    0x05, // bFunction Length
    CDC_CS_INTERFACE, // bDescriptor type: CS_INTERFACE
    CDC_ST_HEADER,    // bDescriptor subtype: Header Func Desc
    0x10,             // bcdCDC: CDC Class Version 1.10
    0x01,

    //! 5.2.3.3 Abstract Control Management Functional Descriptor (usbcdc11.pdf)
    0x04,             // bFunctionLength
    CDC_CS_INTERFACE, // bDescriptor Type: CS_INTERFACE
    CDC_ST_ACM,       // bDescriptor Subtype: ACM Func Desc
    0x00,             // bmCapabilities

    //! 5.2.3.8 Union Functional Descriptor (usbcdc11.pdf)
    0x05,             // bFunctionLength
    CDC_CS_INTERFACE, // bDescriptorType: CS_INTERFACE
    CDC_ST_UNION,     // bDescriptor Subtype: Union Func Desc
    0x00,             // bMasterInterface: Communication Class Interface
    0x01,             // bSlaveInterface0: Data Class Interface

    //! 5.2.3.2 Call Management Functional Descriptor (usbcdc11.pdf)
    0x05, // bFunctionLength
    CDC_CS_INTERFACE, // bDescriptor Type: CS_INTERFACE
    CDC_ST_CMF,       // bDescriptor Subtype: Call Management Func Desc
    0x00,             // bmCapabilities: D1 + D0
    0x01,             // bDataInterface: Data Class Interface 1

    //! Endpoint 1 descriptor
    //! Table 9-13. Standard Endpoint Descriptor
    0x07,                    // bLength
    USB_ENDPOINT_DESCRIPTOR, // bDescriptorType
    0x80+AT91C_EP_INTER,     // bEndpointAddress, Endpoint AT91C_EP_INTER - IN
    ENDPOINT_TYPE_INTERRUPT, // bmAttributes      INT
    0x40, 0x00,              // wMaxPacketSize
    0x10,                    // bInterval, for HS value between 0x01 and 0x10

    //! Table 9-12. Standard Interface Descriptor
    0x09,                     // bLength
    USB_INTERFACE_DESCRIPTOR, // bDescriptorType
    0x01,                     // bInterfaceNumber
    0x00,                     // bAlternateSetting
    0x02,                     // bNumEndpoints
    0x0A,                     // bInterfaceClass
    0x00,                     // bInterfaceSubclass
    0x00,                     // bInterfaceProtocol
    0x00,                     // iInterface

    //! First alternate setting
    //! Table 9-13. Standard Endpoint Descriptor
    0x07,                     //!< bLength
    USB_ENDPOINT_DESCRIPTOR,  //!< bDescriptorType
    0x00+AT91C_EP_OUT,        //!< bEndpointAddress, Endpoint AT91C_EP_OUT - OUT
    ENDPOINT_TYPE_BULK,       //!< bmAttributes      BULK
    0x00, 0x02,               //!< wMaxPacketSize
    0x00,                     //!< bInterval

    //! Table 9-13. Standard Endpoint Descriptor
    0x07,                     //!< bLength
    USB_ENDPOINT_DESCRIPTOR,  //!< bDescriptorType
    0x80+AT91C_EP_IN,         //!< bEndpointAddress, Endpoint AT91C_EP_IN - IN
    ENDPOINT_TYPE_BULK,       //!< bmAttributes      BULK
    0x00, 0x02,               //!< wMaxPacketSize
    0x00                      //!< bInterval
};

char sOtherSpeedConfiguration[] = {
    //! ============== CONFIGURATION 1 ===========
    //! Table 9-10. Standard Configuration Descriptor
    0x09,                            // bLength;              //!< size of this descriptor in bytes
    USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR,    // bDescriptorType;      //!< CONFIGURATION descriptor type
    0x43,                            // wTotalLength;         //!< total length of data returned 2 EP + Control
    0x00,
    0x02,                            // bNumInterfaces;       //!< number of interfaces for this conf
    0x01,                            // bConfigurationValue;  //!< value for SetConfiguration resquest
    0x00,                            // iConfiguration;       //!< index of string descriptor
    USB_CONFIG_SELF_NOWAKEUP,        // bmAttibutes;          //!< Configuration characteristics
    0x00,                            // MaxPower;             //!< maximum power consumption

    //! Communication Class Interface Descriptor Requirement
    //! Table 9-12. Standard Interface Descriptor
    0x09,                       // Size of this descriptor in bytes
    USB_INTERFACE_DESCRIPTOR,   // INTERFACE Descriptor Type
    0x00,                       // bInterfaceNumber
    0x00,                       // bAlternateSetting
    0x01,                       // bNumEndpoints
    USB_DEVICE_CLASS_MODEM_CDC, // bInterfaceClass
    SUBCLASSCODE_SFF_MCC,       // bInterfaceSubclass
    0x00,                       // bInterfaceProtocol
    0x00,                       // iInterface

    //! 5.2.3.1 Header Functional Descriptor (usbcdc11.pdf)
    0x05, // bFunction Length
    CDC_CS_INTERFACE, // bDescriptor type: CS_INTERFACE
    CDC_ST_HEADER,    // bDescriptor subtype: Header Func Desc
    0x10,             // bcdCDC: CDC Class Version 1.10
    0x01,

    //! 5.2.3.3 Abstract Control Management Functional Descriptor (usbcdc11.pdf)
    0x04,             // bFunctionLength
    CDC_CS_INTERFACE, // bDescriptor Type: CS_INTERFACE
    CDC_ST_ACM,       // bDescriptor Subtype: ACM Func Desc
    0x00,             // bmCapabilities

    //! 5.2.3.8 Union Functional Descriptor (usbcdc11.pdf)
    0x05,             // bFunctionLength
    CDC_CS_INTERFACE, // bDescriptorType: CS_INTERFACE
    CDC_ST_UNION,     // bDescriptor Subtype: Union Func Desc
    0x00,             // bMasterInterface: Communication Class Interface
    0x01,             // bSlaveInterface0: Data Class Interface

    //! 5.2.3.2 Call Management Functional Descriptor (usbcdc11.pdf)
    0x05, // bFunctionLength
    CDC_CS_INTERFACE, // bDescriptor Type: CS_INTERFACE
    CDC_ST_CMF,       // bDescriptor Subtype: Call Management Func Desc
    0x00,             // bmCapabilities: D1 + D0
    0x01,             // bDataInterface: Data Class Interface 1

    //! Endpoint 1 descriptor
    //! Table 9-13. Standard Endpoint Descriptor
    0x07,                    // bLength
    USB_ENDPOINT_DESCRIPTOR, // bDescriptorType
    0x80+AT91C_EP_INTER,     // bEndpointAddress, Endpoint AT91C_EP_INTER - IN
    ENDPOINT_TYPE_INTERRUPT, // bmAttributes      INT
    0x40, 0x00,              // wMaxPacketSize
    0x10,                    // bInterval, for HS value between 0x01 and 0x10

    //! Table 9-12. Standard Interface Descriptor
    0x09,                     // bLength
    USB_INTERFACE_DESCRIPTOR, // bDescriptorType
    0x01,                     // bInterfaceNumber
    0x00,                     // bAlternateSetting
    0x02,                     // bNumEndpoints
    0x0A,                     // bInterfaceClass
    0x00,                     // bInterfaceSubclass
    0x00,                     // bInterfaceProtocol
    0x00,                     // iInterface

    //! First alternate setting
    //! Table 9-13. Standard Endpoint Descriptor
    0x07,                     //!< bLength
    USB_ENDPOINT_DESCRIPTOR,  //!< bDescriptorType
    0x00+AT91C_EP_OUT,        //!< bEndpointAddress, Endpoint AT91C_EP_OUT - OUT
    ENDPOINT_TYPE_BULK,       //!< bmAttributes      BULK
    0x40, 0x00,               //!< wMaxPacketSize
    0x00,                     //!< bInterval

    //! Table 9-13. Standard Endpoint Descriptor
    0x07,                     //!< bLength
    USB_ENDPOINT_DESCRIPTOR,  //!< bDescriptorType
    0x80+AT91C_EP_IN,         //!< bEndpointAddress, Endpoint AT91C_EP_IN - IN
    ENDPOINT_TYPE_BULK,       //!< bmAttributes      BULK
    0x40, 0x00,               //!< wMaxPacketSize
    0x00                      //!< bInterval
};


//! 7.1.20 Test Mode Support
static const char test_packet_buffer[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,                // JKJKJKJK * 9
    0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,                     // JJKKJJKK * 8
    0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,                     // JJJJKKKK * 8
    0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // JJJJJJJKKKKKKK * 8
    0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,                          // JJJJJJJK * 8
    0xFC,0x7E,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0x7E                 // {JKKKKKKK * 10}, JK
};


AT91S_CDC cdcData = {
      AT91C_BASE_UDPHS,
      AT91C_BASE_UDPHS_FIFO,
      0,   //!< Current configuration
      0,   //!< Current connection
      0,   //!< Device Status
      NULL,
      NULL,
      NULL
};

//! CDC line coding
typedef struct  {
    unsigned int dwDTERRate;   //!< Baudrate
    char         bCharFormat;  //!< Stop bit
    char         bParityType;  //!< Parity
    char         bDataBits;    //!< data bits
} AT91S_CDC_LINE_CODING, *AT91PS_CDC_LINE_CODING;

AT91S_CDC_LINE_CODING line = { AT91C_BAUDRATE_115200, //!< baudrate
                                  0,   //!< 1 Stop Bit
                                  0,   //!< None Parity
                                  8    //!< 8 Data bits
                             };


static unsigned char AT91F_UDP_IsConfigured(AT91PS_CDC pCdc);
static unsigned int AT91F_UDP_Read(AT91PS_CDC pCdc, char *pData, unsigned int length);
static unsigned int AT91F_UDP_Write(AT91PS_CDC pCdc, const char *pData, unsigned int length);
static void AT91F_CDC_Enumerate(AT91PS_CDC pCdc);

S_usb_request setupPayload;

//*----------------------------------------------------------------------------
//* \fn    AT91F_InitUSB
//* \brief
//*----------------------------------------------------------------------------
void AT91F_InitUSB(void)
{
    unsigned int tmp = 0;

    /* To be done before 480MHz Clock enable !!! */
    AT91C_BASE_UDPHS->UDPHS_CTRL |= AT91C_UDPHS_CTRL_EN_UDPHS;

#if defined (AT91CAP9_UMC_VALID)    // Only for old prerelease-beta-chip
    *AT91C_CCFG_UDPHS |= 0x40000000; // bypass Lock bit
#endif

    // Enable 480MHZ and UDPHS clock (required for driving the pull-up)
    AT91C_BASE_PMC->CKGR_UCKR |= (AT91C_CKGR_UCKR_PLLCOUNT & (3 << 20)) | AT91C_CKGR_UCKR_UPLLEN;
    // Wait until UTMI PLL is locked
    tmp = 0;
    while (((AT91C_BASE_PMC->PMC_SR & AT91C_PMC_SR_LOCKU) == 0) && (tmp++ < DELAY));

    AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_UDPHS);

    // Enables the BIAS
    AT91C_BASE_PMC->CKGR_UCKR |= AT91C_CKGR_UCKR_BIASEN;

    // Connect UDP pull-up (attach)
    AT91C_BASE_UDPHS->UDPHS_CTRL &= ~AT91C_UDPHS_CTRL_DETACH;
}


//*----------------------------------------------------------------------------
//* \fn    AT91F_CDC_Open
//* \brief
//*----------------------------------------------------------------------------
AT91PS_CDC AT91F_CDC_Open(AT91PS_CDC pCdc, AT91PS_UDPHS pUdp, volatile unsigned int * pFIFO)
{
    pCdc->pInterface           = pUdp;
    pCdc->pInterfaceEPT        = pFIFO;
    pCdc->pSetup               = &setupPayload;
    pCdc->currentConfiguration = 0;
    pCdc->currentConnection    = 0;
    pCdc->IsConfigured         = AT91F_UDP_IsConfigured;
    pCdc->Write                = AT91F_UDP_Write;
    pCdc->Read                 = AT91F_UDP_Read;
    return( pCdc );
}

//*----------------------------------------------------------------------------
//* \fn    Size_endpoint
//* \brief
//*----------------------------------------------------------------------------
char Size_endpoint( unsigned short wMaxPacketSize )
{
    unsigned char sizeEpt = 0;

    if ( wMaxPacketSize == 8 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_8;
    } else if ( wMaxPacketSize == 16 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_16;
    } else if ( wMaxPacketSize == 32 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_32;
    } else if ( wMaxPacketSize == 64 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_64;
    } else if ( wMaxPacketSize == 128 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_128;
    } else if ( wMaxPacketSize == 256 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_256;
    } else if ( wMaxPacketSize == 512 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_512;
    } else if ( wMaxPacketSize == 1024 ) {
        sizeEpt = AT91C_UDPHS_EPTCFG_EPT_SIZE_1024;
    } //else {
    //  sizeEpt = 0; // control endpoint
    //}

    return( sizeEpt );

}



//*----------------------------------------------------------------------------
//* \fn    AT91F_UDP_IsConfigured
//* \brief Test if the device is configured and handle enumeration
//*----------------------------------------------------------------------------
static unsigned char AT91F_UDP_IsConfigured(AT91PS_CDC pCdc)
{
    AT91PS_UDPHS pInterface = pCdc->pInterface;
    AT91_REG isr = pInterface->UDPHS_INTSTA;
    unsigned short sizeEpt;
//    unsigned int   tmp = 0;


    // Not remove theses comment lines
    // Uses for USB certification, but need VBUS detect.
    //// Test VBUS
    //if( (AT91C_BASE_PIOA->PIO_PDSR&AT91C_PIO_PA8) == AT91C_PIO_PA8 ) {
    //    // VBUS is present
    //    // Connect UDP pull-up (attach)
    //    AT91C_BASE_UDPHS->UDPHS_CTRL &= ~AT91C_UDPHS_DETACH;
    //}
    //else {
    //    // VBUS is not present
    //    // disconnect UDP pull-up (detach)
    //    AT91C_BASE_UDPHS->UDPHS_CTRL |= AT91C_UDPHS_DETACH;
    //}

    // Suspend
    if (isr & AT91C_UDPHS_INTSTA_DET_SUSPD) {

        pCdc->currentConfiguration = 0;

        // Disables the BIAS
//        AT91C_BASE_CKGR->CKGR_UCKR &= ~AT91C_CKGR_UCKR_BIASEN;
        pInterface->UDPHS_CLRINT = AT91C_UDPHS_CLRINT_DET_SUSPD;

        // Disabled clock UDPHS
//        AT91C_BASE_PMC->PMC_PCDR = (1 << AT91C_ID_UDPHS);
        // Disable 480MHZ
//        AT91C_BASE_CKGR->CKGR_UCKR &= ~AT91C_CKGR_UCKR_UPLLEN;
    }
    // Resume
    else if( (isr & AT91C_UDPHS_INTSTA_WAKE_UP)         // line activity
          || (isr & AT91C_UDPHS_INTSTA_ENDOFRSM) ) {    // pc

        // Enable 480MHZ
//        AT91C_BASE_CKGR->CKGR_UCKR |= (AT91C_CKGR_UCKR_PLLCOUNT & (3 << 20)) | AT91C_CKGR_UCKR_UPLLEN;

        // Wait until UTMI PLL is locked
//        tmp = 0;
//        while (((AT91C_BASE_PMC->PMC_SR & AT91C_PMC_SR_LOCKU) == 0) && (tmp++ < DELAY));

        // Enable clock UDPHS
//        AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_UDPHS);

        pInterface->UDPHS_CLRINT = AT91C_UDPHS_CLRINT_WAKE_UP | AT91C_UDPHS_CLRINT_ENDOFRSM;
    }

    // End Of Bus Reset
    else if (isr & AT91C_UDPHS_INTSTA_ENDRESET) {

        pCdc->currentConfiguration = 0;
        sizeEpt = Size_endpoint( MAXPACKETCTRL );
        pInterface->UDPHS_EPT[0].UDPHS_EPTCFG = sizeEpt | AT91C_UDPHS_EPTCFG_EPT_DIR_OUT |
                                                AT91C_UDPHS_EPTCFG_EPT_TYPE_CTL_EPT | AT91C_UDPHS_EPTCFG_BK_NUMBER_1;

        while( (pInterface->UDPHS_EPT[0].UDPHS_EPTCFG & AT91C_UDPHS_EPTCFG_EPT_MAPD) != AT91C_UDPHS_EPTCFG_EPT_MAPD ) {}

        pInterface->UDPHS_EPT[0].UDPHS_EPTCTLENB = AT91C_UDPHS_EPTCTLENB_RX_SETUP | AT91C_UDPHS_EPTCTLENB_EPT_ENABL;
        pInterface->UDPHS_CLRINT = AT91C_UDPHS_CLRINT_ENDRESET;
    }

    // Endpoint
    else if (isr & (1<<SHIFT_INTERUPT<<0)) {  // ept 0
        AT91F_CDC_Enumerate(pCdc);
    }

    return( pCdc->currentConfiguration );
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_UDP_Read
//* \brief Read available data from AT91C_EP_OUT
//*----------------------------------------------------------------------------
static unsigned int AT91F_UDP_Read(AT91PS_CDC pCdc, char *pData, unsigned int length)
{
    AT91PS_UDPHS pInterface = pCdc->pInterface;
    unsigned int nbBytesRcv = 0;

#if USE_DMA_OUT
    unsigned int bufferSize, dmaStatus;

    while(length) {

        bufferSize = (length > DMA_BUF_SIZE) ? DMA_BUF_SIZE : length;
        pInterface->UDPHS_DMA[AT91C_EP_OUT].UDPHS_DMAADDRESS = (unsigned int) pData;
        pInterface->UDPHS_DMA[AT91C_EP_OUT].UDPHS_DMACONTROL =   ((((unsigned short)bufferSize) & 0xFFFF) << 16)
                                                               | AT91C_UDPHS_DMACONTROL_END_TR_EN
                                                               | AT91C_UDPHS_DMASTATUS_END_BF_ST
                                                               | AT91C_UDPHS_DMACONTROL_CHANN_ENB;

        do {
            dmaStatus = pInterface->UDPHS_DMA[AT91C_EP_OUT].UDPHS_DMASTATUS;
            if(0 == (AT91F_UDP_IsConfigured(pCdc))) {
                return( 0 );
            }
        } while( ((dmaStatus & (AT91C_UDPHS_DMASTATUS_END_TR_ST | AT91C_UDPHS_DMASTATUS_END_BF_ST)) == 0 )
              && ( AT91C_UDPHS_EPTSTA_RX_SETUP != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_SETUP) ) );

        bufferSize -= (dmaStatus >> 16);
        nbBytesRcv += bufferSize;
        length -= bufferSize;
        pData  += bufferSize;
        // If the transfer is achieved due to a short packet: stop the read
        if(dmaStatus & AT91C_UDPHS_DMASTATUS_END_TR_ST) {
            break;
        }
        if( AT91C_UDPHS_EPTSTA_RX_SETUP == (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_SETUP) ) {
            break;
        }
    }
#else
    volatile unsigned int * pInterfaceEPT = pCdc->pInterfaceEPT;
    char *pfifo;
    unsigned int packetSize;

    while (!nbBytesRcv) {
        if (!AT91F_UDP_IsConfigured(pCdc)) {
            break;
        }
        if ( 0 != (pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY ) ) {
            packetSize = ((pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_BYTE_COUNT)>>20);
            pfifo = (char*) ((unsigned int *)(pInterfaceEPT) + (16384 * AT91C_EP_OUT));
            while (packetSize--) {
                pData[nbBytesRcv] = pfifo[nbBytesRcv];
                nbBytesRcv++;
            }
            pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
        }
    }
#endif
    return( nbBytesRcv );
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CDC_Write
//* \brief Send through endpoint AT91C_EP_IN
//*----------------------------------------------------------------------------
static unsigned int AT91F_UDP_Write(AT91PS_CDC pCdc, const char *pData, unsigned int length)
{
    AT91PS_UDPHS  pInterface = pCdc->pInterface;
    unsigned long cpt = 0;

#if USE_DMA_IN
    if (0 != length) {
        while (length) {
            pInterface->UDPHS_DMA[AT91C_EP_IN].UDPHS_DMAADDRESS = (unsigned int) pData;
            cpt = (length < DMA_BUF_SIZE) ? length : DMA_BUF_SIZE;
            length -= cpt;
            pData += cpt;
            pInterface->UDPHS_DMA[AT91C_EP_IN].UDPHS_DMACONTROL =   (((((unsigned short) cpt) & 0xFFFF) << 16)
                                                                  | AT91C_UDPHS_DMACONTROL_END_B_EN
                                                                  | AT91C_UDPHS_DMACONTROL_CHANN_ENB);

            while ((pInterface->UDPHS_DMA[AT91C_EP_IN].UDPHS_DMASTATUS & AT91C_UDPHS_DMASTATUS_END_BF_ST) == 0) {
                if((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD) == AT91C_UDPHS_INTSTA_DET_SUSPD) {
                    return( 0 );
                }
            }
        }
    } else {
        while( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) ) {}
        pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
        while( (0 != (pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY))
            && ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD)!= AT91C_UDPHS_INTSTA_DET_SUSPD) ) {}
    }
#else
    volatile unsigned int * pInterfaceEPT = pCdc->pInterfaceEPT;
    unsigned long packetSize;
    char *pfifo;

    if (0 != length) {
    packetSize = (pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_SPEED) ? MAXPACKETSIZEIN : OSCMAXPACKETSIZEIN;

    while( 0 != (pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) ) {}

    while (length) {
            cpt = MIN(length, packetSize);
            length -= cpt;
            pfifo = (char*)((unsigned int *)(pInterfaceEPT) + (16384 * AT91C_EP_IN));
            while (cpt) {
                *(pfifo++) = *(pData++);
                --cpt;
            }
            pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
            while( (pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY)
                && ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD) != AT91C_UDPHS_INTSTA_DET_SUSPD)) {}

            if ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD) == AT91C_UDPHS_INTSTA_DET_SUSPD) {
                break;
            }
        }
    } else {
        while( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) ) {}
        pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
        while( (0 != (pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY))
            && ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD)!= AT91C_UDPHS_INTSTA_DET_SUSPD) ) {}
    }
#endif

    return( length );
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_SendData
//* \brief Send Data through the control endpoint
//*----------------------------------------------------------------------------
static void AT91F_USB_SendData(AT91PS_CDC pCdc, const char *pData, unsigned int length)
{
    volatile unsigned int * pInterfaceEPT = pCdc->pInterfaceEPT;
    AT91PS_UDPHS         pInterface = pCdc->pInterface;
    unsigned int cpt = 0;
    unsigned int index=0;
    char *pfifo;

    while( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) ) {}

    if(0 != length) {
        while (length) {
            cpt = MIN(length, MAXPACKETCTRL);
            length -= cpt;
            pfifo = (char*)pInterfaceEPT;
            while (cpt--) {
                pfifo[index] = pData[index];
                index++;
            }
            pInterface->UDPHS_EPT[0].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
            while( (0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) )
            && ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD)!= AT91C_UDPHS_INTSTA_DET_SUSPD) ) {}
            if((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD)== AT91C_UDPHS_INTSTA_DET_SUSPD) {
                break;
            }
        }
    }
    else {
        while( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) ) {}
        pInterface->UDPHS_EPT[0].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
        while( ( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) )
            && ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD)!= AT91C_UDPHS_INTSTA_DET_SUSPD) ) {}
    }
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_SendZlp
//* \brief Send zero length packet through the control endpoint
//*----------------------------------------------------------------------------
void AT91F_USB_SendZlp(AT91PS_UDPHS pInterface)
{
    while( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) ) {}
    pInterface->UDPHS_EPT[0].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
    while( ( 0 != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_TX_PK_RDY ) )
        && ((pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_DET_SUSPD)!= AT91C_UDPHS_INTSTA_DET_SUSPD) );
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_SendStall
//* \brief Stall the control endpoint
//*----------------------------------------------------------------------------
void AT91F_USB_SendStall(AT91PS_UDPHS pInterface)
{
    pInterface->UDPHS_EPT[0].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_FRCESTALL;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CDC_Enumerate
//* \brief This function is a callback invoked when a SETUP packet is received
//*----------------------------------------------------------------------------
static void AT91F_CDC_Enumerate(AT91PS_CDC pCdc)
{
    AT91PS_UDPHS         pInterface = pCdc->pInterface;
    volatile unsigned int * pInterfaceEPT = pCdc->pInterfaceEPT;
    S_usb_request        *pSetupData= pCdc->pSetup;
    unsigned long        fifo;
    unsigned short       wMaxPacketSizeOUT;
    unsigned short       wMaxPacketSizeIN;
    unsigned short       wMaxPacketSizeINTER;
    unsigned short       sizeEpt;
    unsigned char        i;
    char                 *pfifo;

    if( AT91C_UDPHS_EPTSTA_RX_SETUP == (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_SETUP) ) {

        fifo = *pInterfaceEPT;
        pSetupData->data32[0]=fifo;
        fifo = *pInterfaceEPT;
        pSetupData->data32[1]=fifo;

        pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_SETUP;

        // Handle supported standard device request Cf Table 9-3 in USB specification Rev 1.1
        switch (pSetupData->request.bRequest) {

            case USB_GET_DESCRIPTOR:

                if (pSetupData->request.wValue == (USB_DEVICE_DESCRIPTOR << 8)) {
                    AT91F_USB_SendData(pCdc, devDescriptor, MIN(sizeof(devDescriptor), pSetupData->request.wLength));
                    // Waiting for Status stage
                    while (AT91C_UDPHS_EPTSTA_RX_BK_RDY != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY));
                    pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                }
                else if (pSetupData->request.wValue == (USB_CONFIGURATION_DESCRIPTOR << 8)) {
                    if (pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_SPEED) {
                        sConfiguration[1] = USB_CONFIGURATION_DESCRIPTOR;
                        AT91F_USB_SendData(pCdc, sConfiguration, MIN(sizeof(sConfiguration), pSetupData->request.wLength));
                        // Waiting for Status stage
                        while (AT91C_UDPHS_EPTSTA_RX_BK_RDY != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY));
                        pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                    }
                    else {
                        sOtherSpeedConfiguration[1] = USB_CONFIGURATION_DESCRIPTOR;
                        AT91F_USB_SendData(pCdc, sOtherSpeedConfiguration, MIN(sizeof(sOtherSpeedConfiguration), pSetupData->request.wLength));
                        // Waiting for Status stage
                        while (AT91C_UDPHS_EPTSTA_RX_BK_RDY != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY));
                        pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                    }
                }
                else if (pSetupData->request.wValue == (USB_DEVICE_QUALIFIER_DESCRIPTOR << 8)) {
                    AT91F_USB_SendData(pCdc, devQualDescriptor, MIN(sizeof(devQualDescriptor), pSetupData->request.wLength));
                    // Waiting for Status stage
                    while (AT91C_UDPHS_EPTSTA_RX_BK_RDY != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY));
                    pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                }
                else if (pSetupData->request.wValue == (USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR << 8)) {
                    if (pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_SPEED) {

                        sOtherSpeedConfiguration[1] = USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR;
                        AT91F_USB_SendData(pCdc, sOtherSpeedConfiguration, MIN(sizeof(sOtherSpeedConfiguration), pSetupData->request.wLength));
                        // Waiting for Status stage
                        while (AT91C_UDPHS_EPTSTA_RX_BK_RDY != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY));
                        pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                    }
                    else {
                        sConfiguration[1] = USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR;
                        AT91F_USB_SendData(pCdc, sConfiguration, MIN(sizeof(sConfiguration), pSetupData->request.wLength));
                        // Waiting for Status stage
                        while (AT91C_UDPHS_EPTSTA_RX_BK_RDY != (pInterface->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY));
                        pInterface->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                    }
                }
                else {
                    AT91F_USB_SendStall(pInterface);
                }
                break;

            case USB_SET_ADDRESS:
                AT91F_USB_SendZlp(pInterface);
                pInterface->UDPHS_CTRL |= ( ((pSetupData->request.wValue)&0x7F) | AT91C_UDPHS_CTRL_FADDR_EN );
                break;

            case USB_SET_CONFIGURATION:
                pCdc->currentConfiguration = (unsigned char)pSetupData->request.wValue;  // The lower byte of the wValue field specifies the desired configuration.
                AT91F_USB_SendZlp(pInterface);

                if (pInterface->UDPHS_INTSTA & AT91C_UDPHS_INTSTA_SPEED) {
                    // High Speed
                    wMaxPacketSizeOUT   = MAXPACKETSIZEOUT;
                    wMaxPacketSizeIN    = MAXPACKETSIZEIN;
                    wMaxPacketSizeINTER = MAXPACKETSIZEINTER;

                } else {
                    // Full Speed
                    wMaxPacketSizeOUT   = OSCMAXPACKETSIZEOUT;
                    wMaxPacketSizeIN    = OSCMAXPACKETSIZEIN;
                    wMaxPacketSizeINTER = OSCMAXPACKETSIZEINTER;
                }

                sizeEpt = Size_endpoint( wMaxPacketSizeOUT );
                pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTCFG = sizeEpt | AT91C_UDPHS_EPTCFG_EPT_DIR_OUT | AT91C_UDPHS_EPTCFG_EPT_TYPE_BUL_EPT | AT91C_UDPHS_EPTCFG_BK_NUMBER_2;
                while( (pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTCFG & AT91C_UDPHS_EPTCFG_EPT_MAPD) != AT91C_UDPHS_EPTCFG_EPT_MAPD ) {}
    #if USE_DMA_OUT
                pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTCTLENB = AT91C_UDPHS_EPTCTLENB_AUTO_VALID | AT91C_UDPHS_EPTCTLENB_EPT_ENABL;
    #else
                pInterface->UDPHS_EPT[AT91C_EP_OUT].UDPHS_EPTCTLENB = AT91C_UDPHS_EPTCTLENB_RX_BK_RDY | AT91C_UDPHS_EPTCTLENB_EPT_ENABL;
    #endif

                sizeEpt  = Size_endpoint( wMaxPacketSizeIN );
                pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCFG = sizeEpt | AT91C_UDPHS_EPTCFG_EPT_DIR_IN | AT91C_UDPHS_EPTCFG_EPT_TYPE_BUL_EPT | AT91C_UDPHS_EPTCFG_BK_NUMBER_2;
                while( (pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCFG & AT91C_UDPHS_EPTCFG_EPT_MAPD) != AT91C_UDPHS_EPTCFG_EPT_MAPD ) {}
    #if USE_DMA_IN
                pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCTLENB =  AT91C_UDPHS_EPTCTLENB_AUTO_VALID | AT91C_UDPHS_EPTCTLENB_EPT_ENABL;
    #else
                pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCTLENB =  AT91C_UDPHS_EPTCTLENB_SHRT_PCKT | AT91C_UDPHS_EPTCTLENB_EPT_ENABL;
    #endif
                sizeEpt  = Size_endpoint( wMaxPacketSizeINTER );
                pInterface->UDPHS_EPT[AT91C_EP_INTER].UDPHS_EPTCFG = sizeEpt | AT91C_UDPHS_EPTCFG_EPT_DIR_IN | AT91C_UDPHS_EPTCFG_EPT_TYPE_INT_EPT| AT91C_UDPHS_EPTCFG_BK_NUMBER_1;
                while( (pInterface->UDPHS_EPT[AT91C_EP_INTER].UDPHS_EPTCFG & AT91C_UDPHS_EPTCFG_EPT_MAPD) != AT91C_UDPHS_EPTCFG_EPT_MAPD ) {}
                pInterface->UDPHS_EPT[AT91C_EP_INTER].UDPHS_EPTCTLENB =  AT91C_UDPHS_EPTCTLENB_EPT_ENABL;
                break;

            case USB_GET_CONFIGURATION:
                AT91F_USB_SendData(pCdc, (char *) &(pCdc->currentConfiguration), sizeof(pCdc->currentConfiguration));
                break;

            case USB_CLEAR_FEATURE:
                // 9.4.1 Clear Feature ( CLEAR_FEATURE ) (usb_20.pdf)
                // This request is used to clear or disable a specific feature.
                if (pSetupData->request.wValue == USB_ENDPOINT_HALT) {
                    //! Notify the application (disable endpoint)
                    //! Send a ZLP
                    pInterface->UDPHS_EPTRST = (1<<(pSetupData->request.wIndex & 0x000F));
                    pInterface->UDPHS_EPT[(pSetupData->request.wIndex & 0x000F)].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTCLRSTA_TOGGLESQ | AT91C_UDPHS_EPTSETSTA_FRCESTALL;
                    AT91F_USB_SendZlp(pInterface);
                }
                else if (pSetupData->request.wValue == USB_DEVICE_REMOTE_WAKEUP) {
                    pCdc->devStatus &= ~(1 << 1); // Remote wakeup disabled
                    AT91F_USB_SendZlp(pInterface);
                }
                else {
                    // USB_TEST_MODE
                    AT91F_USB_SendStall(pInterface);
                }
                break;

            case USB_GET_STATUS:
                if (pSetupData->request.bmRequestType == REQUEST_DEVICE_STATUS) {
                    if( USB_CONFIG_SELF_NOWAKEUP == (sConfiguration[7] & USB_CONFIG_SELF_NOWAKEUP) ) {  // bmAttibutes, D6=1 (D7 always 1)
                        pCdc->devStatus |= (1 << 0); // Self powered device
                    }
                    else {
                        pCdc->devStatus &= ~(1 << 0); // Bus powered device
                    }
                    //! Return the device status
                    AT91F_USB_SendData(pCdc, (char *)&(pCdc->devStatus), 2);
                }
                else if (pSetupData->request.bmRequestType == REQUEST_ENDPOINT_STATUS) {
                    pCdc->eptStatus = (unsigned short)((pInterface->UDPHS_EPT[(pSetupData->request.wIndex & 0x000F)].UDPHS_EPTSTA & AT91C_UDPHS_EPTSETSTA_FRCESTALL) ? 1 : 0);
                    //! Return the endpoint status
                    AT91F_USB_SendData(pCdc, (char *)&(pCdc->eptStatus), 2);
                }
                else {
                    AT91F_USB_SendStall(pInterface);
                }
                break;

            case USB_SET_FEATURE:
                if (pSetupData->request.wValue == USB_ENDPOINT_HALT) {
                    //! Notify the application (enable endpoint)
                    //! - Abort the current transfer
                    pInterface->UDPHS_EPT[(pSetupData->request.wIndex & 0x000F)].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_FRCESTALL;
                    //! Send a ZLP
                    AT91F_USB_SendZlp(pInterface);
                }
                else if(pSetupData->request.wValue == USB_TEST_MODE){
                  // 7.1.20 Test Mode Support
                  if( (pSetupData->request.bmRequestType == DEVICE_RECIPIENT) &&
                      ((pSetupData->request.wIndex & 0x000F) == 0) )          {
                    // the lower byte of wIndex must be zero
                    // the most significant byte of wIndex is used to specify the specific test mode

                    pInterface->UDPHS_IEN &= ~AT91C_UDPHS_IEN_DET_SUSPD; // remove suspend for TEST
                    pInterface->UDPHS_TST |= AT91C_UDPHS_TST_SPEED_CFG_HS; // force High Speed (remove suspend)

                    switch( (pSetupData->request.wIndex & 0xFF00)>>8 ) {

                      case TEST_PACKET:
                        //Test mode Test_Packet:
                        //Upon command, a port must repetitively transmit the following test packet until
                        //the exit action is taken. This enables the testing of rise and fall times, eye
                        //patterns, jitter, and any other dynamic waveform specifications.
                        //The test packet is made up by concatenating the following strings.
                        //(Note: For J/K NRZI data, and for NRZ data, the bit on the left is the first one
                        //transmitted. “S” indicates that a bit stuff occurs, which inserts an “extra” NRZI data bit.
                        //“* N” is used to indicate N occurrences of a string of bits or symbols.)
                        //A port in Test_Packet mode must send this packet repetitively. The inter-packet timing
                        //must be no less than the minimum allowable inter-packet gap as defined in Section 7.1.18 and
                        //no greater than 125 us.

                        // Send ZLP
                        AT91F_USB_SendZlp(pInterface);

                        pInterface->UDPHS_DMA[AT91C_EP_IN].UDPHS_DMACONTROL = 0;
                        pInterface->UDPHS_DMA[AT91C_EP_OUT].UDPHS_DMACONTROL = 0;

                        // Configure endpoint 2, 64 bytes, direction IN, type BULK, 1 bank
                        pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCFG = AT91C_UDPHS_EPTCFG_EPT_SIZE_64 | AT91C_UDPHS_EPTCFG_EPT_DIR_IN | AT91C_UDPHS_EPTCFG_EPT_TYPE_BUL_EPT | AT91C_UDPHS_EPTCFG_BK_NUMBER_1;
                        while( (pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCFG & AT91C_UDPHS_EPTCFG_EPT_MAPD) != AT91C_UDPHS_EPTCFG_EPT_MAPD ) {}

                        pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTCTLENB =  AT91C_UDPHS_EPTCTLENB_EPT_ENABL;

                        // Tst PACKET
                        pInterface->UDPHS_TST |= AT91C_UDPHS_TST_TST_PKT;

                        // Write FIFO
                        pfifo = (char*)((unsigned int *)(pInterfaceEPT) + (16384 * AT91C_EP_IN));
                        for( i=0; i<sizeof(test_packet_buffer); i++) {
                            pfifo[i] = test_packet_buffer[i];
                        }
                        // Send packet
                        pInterface->UDPHS_EPT[AT91C_EP_IN].UDPHS_EPTSETSTA = AT91C_UDPHS_EPTSETSTA_TX_PK_RDY;
                        for(;;);
//                        break;

                      case TEST_J:
                        //Test mode Test_J:
                        //Upon command, a port’s transceiver must enter the high-speed J state and remain in that
                        //state until the exit action is taken. This enables the testing of the high output drive
                        //level on the D+ line.
                        // Send a ZLP
                        AT91F_USB_SendZlp(pInterface);
                        pInterface->UDPHS_TST = AT91C_UDPHS_TST_TST_J;
                        for(;;);
//                        break;

                      case TEST_K:
                        //Test mode Test_K:
                        //Upon command, a port’s transceiver must enter the high-speed K state and remain in
                        //that state until the exit action is taken. This enables the testing of the high output drive
                        //level on the D- line.
                        // Send a ZLP
                        AT91F_USB_SendZlp(pInterface);
                        pInterface->UDPHS_TST = AT91C_UDPHS_TST_TST_K;
                        for(;;);
//                        break;

                      case TEST_SEO_NAK:
                        //Test mode Test_SE0_NAK:
                        //Upon command, a port’s transceiver must enter the high-speed receive mode
                        //and remain in that mode until the exit action is taken. This enables the testing
                        //of output impedance, low level output voltage, and loading characteristics.
                        //In addition, while in this mode, upstream facing ports (and only upstream facing ports)
                        //must respond to any IN token packet with a NAK handshake (only if the packet CRC is
                        //determined to be correct) within the normal allowed device response time. This enables testing of
                        //the device squelch level circuitry and, additionally, provides a general purpose stimulus/response
                        //test for basic functional testing.

                        pInterface->UDPHS_IEN = 0;

                        // Send a ZLP
                        AT91F_USB_SendZlp(pInterface);
                        for(;;);
//                        break;

                      default:
                            AT91F_USB_SendStall(pInterface);
                        break;

                    }
                    // The exit action is to power cycle the device.
                    // The device must be disconnected from the host
                  }
                  else {
                        AT91F_USB_SendStall(pInterface);
                  }
                }
                else if(pSetupData->request.wValue == USB_DEVICE_REMOTE_WAKEUP){
                    pCdc->devStatus |= (1 << 1); // Remote wakeup enabled
                    AT91F_USB_SendZlp(pInterface);
                }
                else {
                    AT91F_USB_SendStall(pInterface);
                }
                break;

            // handle CDC class requests
            case CDC_SET_LINE_CODING:
                while((AT91C_BASE_UDPHS->UDPHS_EPT[0].UDPHS_EPTSTA & AT91C_UDPHS_EPTSTA_RX_BK_RDY) == 0);
                AT91C_BASE_UDPHS->UDPHS_EPT[0].UDPHS_EPTCLRSTA = AT91C_UDPHS_EPTSTA_RX_BK_RDY;
                AT91F_USB_SendZlp(pInterface);
                break;

            case CDC_GET_LINE_CODING:
                AT91F_USB_SendData(pCdc, (char *) &line, MIN(sizeof(line), pSetupData->request.wLength));
                break;

            case CDC_SET_CONTROL_LINE_STATE:
                pCdc->currentConnection = (unsigned char)pSetupData->request.wValue;
                AT91F_USB_SendZlp(pInterface);
                break;

            // case USB_SET_INTERFACE:  MUST BE STALL for us
            default:
                AT91F_USB_SendStall(pInterface);
                break;

        }
    }
}

#endif
