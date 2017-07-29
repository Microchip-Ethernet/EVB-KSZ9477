//*--------------------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : USB driver definitions
//* Object              :
//* Translator          :
//* 1.0 07/09/05        : Creation
//*--------------------------------------------------------------------------------------

#ifndef _USB_H
#define _USB_H

//!\defgroup USB USB low level driver API
//! This API masks the USB low level driver internal operations
//! All USB operations are delegated to a USB low level driver instance 
//! such as UDP
/*@{*/

// usb_20.pdf

//_____ S T A N D A R D    D E F I N I T I O N S ___________________________
//! Table 9-4. Standard Request Codes
#define USB_GET_STATUS                 0x00
#define USB_CLEAR_FEATURE              0x01           //!< see FEATURES below
// Reserved for futur use              0x02
#define USB_SET_FEATURE                0x03           //!< see FEATURES below
// Reserved for futur use              0x04
#define USB_SET_ADDRESS                0x05
#define USB_GET_DESCRIPTOR             0x06
#define USB_SET_DESCRIPTOR             0x07
#define USB_GET_CONFIGURATION          0x08
#define USB_SET_CONFIGURATION          0x09
#define USB_GET_INTERFACE              0x0A
#define USB_SET_INTERFACE              0x0B
#define USB_SYNCH_FRAME                0x0C

//! 9.4.5 Get Status
#define REQUEST_DEVICE_STATUS          0x80
#define REQUEST_INTERFACE_STATUS       0x81
#define REQUEST_ENDPOINT_STATUS        0x82
#define DEVICE_RECIPIENT               0x00

//! Table 8-3. Endpoint Type Values in Split Special Token
#define ENDPOINT_TYPE_CONTROL          0x00
#define ENDPOINT_TYPE_ISOCHRONOUS      0x01
#define ENDPOINT_TYPE_BULK             0x02
#define ENDPOINT_TYPE_INTERRUPT        0x03

//! Table 9-6. Standard Feature Selectors
#define USB_ENDPOINT_HALT              0x00
#define USB_DEVICE_REMOTE_WAKEUP       0x01
#define USB_TEST_MODE                  0x02

//! Table 9-7. Test Mode Selectors
#define TEST_J                         0x01
#define TEST_K                         0x02
#define TEST_SEO_NAK                   0x03
#define TEST_PACKET                    0x04
#define TEST_FORCE_ENABLE              0x05

//! Device Status
#define BUS_POWERED                       0
#define SELF_POWERED                      1

//! Device State
#define ATTACHED                          0
#define POWERED                           1
#define DEFAULT                           2
#define ADDRESSED                         3
#define CONFIGURED                        4
#define SUSPENDED                         5

#define USB_CONFIG_ATTRIBUTES_RESERVED    0x80
#define USB_CONFIG_BUSPOWERED            (USB_CONFIG_ATTRIBUTES_RESERVED | 0x00)
#define USB_CONFIG_SELFPOWERED           (USB_CONFIG_ATTRIBUTES_RESERVED | 0x40)
#define USB_CONFIG_REMOTEWAKEUP          (USB_CONFIG_ATTRIBUTES_RESERVED | 0x20)

//! Device descriptor wrappers
#define USB_SPECIFICATION(a)      (a)   //!< USB specification V2.0
#define USB_DEVICE_CLASS(a)       (a)   //!< Class code
#define USB_DEVICE_SUB_CLASS(a)   (a)   //!< Subclass code
#define USB_DEVICE_PROTOCOL(a)    (a)   //!< Device protocol
#define USB_CTL_ENDPOINT_SIZE(a)  (a)   //!< Control endpoint size
#define USB_VENDOR_ID(a)          (a)   //!< Vendor ID (Atmel= 03EBh)
#define USB_PRODUCT_ID(a)         (a)   //!< Product ID: (6124h = CDC) 
#define USB_RELEASE_NUMBER(a)     (a)   //!< Product release number

// Table 2: USB DWG Class support in Windows
// USB Class Drivers
// http://www.microsoft.com/whdc/system/bus/usb/USBFAQ_intro.mspx
// Which USB DWG Classes are supported by Microsoft ?
#define USB_DEVICE_CLASS_RESERVED            0x00
#define USB_DEVICE_CLASS_AUDIO               0x01
#define USB_DEVICE_CLASS_MODEM_CDC           0x02
#define USB_DEVICE_CLASS_HUMAN_INTERFACE_HID 0x03
#define USB_DEVICE_CLASS_MONITOR             0x04
#define USB_DEVICE_CLASS_PHYSICAL_INTERFACE  0x05
#define USB_DEVICE_CLASS_SCANNING_PTP        0x06
#define USB_DEVICE_CLASS_PRINTER             0x07
#define USB_DEVICE_CLASS_MASS_STORAGE_MSC    0x08
#define USB_DEVICE_CLASS_HUB                 0x09
// Chip/smart card interface devices (CCID)  0x0B
// Video class (UVC)                         0x0E
// Bluetooth class                           0xE0
#define USB_DEVICE_CLASS_VENDOR_SPECIFIC     0xFF

//! Table 5.3 - Command Block Status Values (usbmassbulk_10.pdf)
#define CBS_COMMAND_PASSED                      0
#define CBS_COMMAND_FAILED                      1
#define CBS_PHASE_ERROR                         2
// Reserved (Obsolete)                03h and 04h 
// Reserved                           05h to  FFh 

//! Table 9-5. Descriptor Types
#define USB_DEVICE_DESCRIPTOR                     0x01
#define USB_CONFIGURATION_DESCRIPTOR              0x02
#define USB_STRING_DESCRIPTOR                     0x03
#define USB_INTERFACE_DESCRIPTOR                  0x04
#define USB_ENDPOINT_DESCRIPTOR                   0x05
#define USB_DEVICE_QUALIFIER_DESCRIPTOR           0x06
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR  0x07
#define USB_INTERFACE_POWER1_DESCRIPTOR           0x08

//! endpoint descriptors wrappers
#define USB_ENDPOINT_OUT(address) (address & 0xF)    
#define USB_ENDPOINT_IN(address)  ((1 << 7) | (address & 0xF))

#define USB_ENDPOINT_SIZE(a)      (a)
#define USB_INTERVAL(a)           (a)

#define USB_LANGUAGE_ID           0x0409
#define USB_UNICODE(a)            (a), 0x00
#define USB_STRING_HEADER(size)   ((size * 2) + 2), USB_STRING_DESCRIPTOR

//_____ U S B   S T R U C T U R E S _________________________________________

//! Table 9-2. Format of Setup Data (usb_20.pdf)
typedef union  _AT91U_USB_SETUP {
  unsigned long  data32[2];
  unsigned short data16[4];
  unsigned char  data8[8];
  struct {
     unsigned char  bmRequestType;        //!< Characteristics of the request
     unsigned char  bRequest;             //!< Specific request
     unsigned short wValue;               //!< field that varies according to request
     unsigned short wIndex;               //!< field that varies according to request
     unsigned short wLength;              //!< Number of bytes to transfer if Data
  } request;
} S_usb_request;


//_____ U S B   S T R U C T U R E S _________________________________________


//! Table 9-8. Standard Device Descriptor
typedef struct _S_usb_device_descriptor{
   unsigned char  bLength;              //!< Size of this descriptor in bytes
   unsigned char  bDescriptorType;      //!< DEVICE descriptor type
   unsigned short bscUSB;               //!< Binay Coded Decimal Spec. release
   unsigned char  bDeviceClass;         //!< Class code assigned by the USB
   unsigned char  bDeviceSubClass;      //!< Sub-class code assigned by the USB
   unsigned char  bDeviceProtocol;      //!< Protocol code assigned by the USB
   unsigned char  bMaxPacketSize0;      //!< Max packet size for EP0
   unsigned short idVendor;             //!< Vendor ID: ATMEL = 0x03EB
   unsigned short idProduct;            //!< Product ID
   unsigned short bcdDevice;            //!< Device release number
   unsigned char  iManufacturer;        //!< Index of manu. string descriptor
   unsigned char  iProduct;             //!< Index of prod. string descriptor
   unsigned char  iSerialNumber;        //!< Index of S.N.  string descriptor
   unsigned char  bNumConfigurations;   //!< Number of possible configurations
} __attribute__ ((packed)) S_usb_device_descriptor;


//! Definitions for bits in the bmAttributes field of
//!   (Table 9-10) Standard Configuration Descriptor
// Reserved (reset to zero)             //   D4...D0=0
#define USB_CONFIG_BUS_NOWAKEUP    0x80 //!< D5=0 + D6=0 + D7=1
#define USB_CONFIG_SELF_NOWAKEUP   0xC0 //!< D5=0 + D6=1 + D7=1
#define USB_CONFIG_BUS_WAKEUP      0xA0 //!< D5=1 + D6=0 + D7=1
#define USB_CONFIG_SELF_WAKEUP     0xE0 //!< D5=1 + D6=1 + D7=1
// Reserved (set to one)                //   D7=1

//! Table 9-10. Standard Configuration Descriptor
typedef struct _S_usb_configuration_descriptor{
   unsigned char  bLength;              //!< size of this descriptor in bytes
   unsigned char  bDescriptorType;      //!< CONFIGURATION descriptor type
   unsigned short wTotalLength;         //!< total length of data returned
   unsigned char  bNumInterfaces;       //!< number of interfaces for this conf.
   unsigned char  bConfigurationValue;  //!< value for SetConfiguration resquest
   unsigned char  iConfiguration;       //!< index of string descriptor
   unsigned char  bmAttibutes;          //!< Configuration characteristics
   unsigned char  MaxPower;             //!< maximum power consumption
} __attribute__ ((packed)) S_usb_configuration_descriptor;

//! Table 9-12. Standard Interface Descriptor
typedef struct _S_usb_interface_descriptor{
   unsigned char bLength;               //!< size of this descriptor in bytes
   unsigned char bDescriptorType;       //!< INTERFACE descriptor type
   unsigned char bInterfaceNumber;      //!< Number of interface
   unsigned char bAlternateSetting;     //!< value to select alternate setting
   unsigned char bNumEndpoints;         //!< Number of EP except EP 0
   unsigned char bInterfaceClass;       //!< Class code assigned by the USB
   unsigned char bInterfaceSubClass;    //!< Sub-class code assigned by the USB
   unsigned char bInterfaceProtocol;    //!< Protocol code assigned by the USB
   unsigned char iInterface;            //!< Index of string descriptor
} __attribute__ ((packed)) S_usb_interface_descriptor;

//! Table 9-13. Standard Endpoint Descriptor
typedef struct _S_usb_endpoint_descriptor{
   unsigned char  bLength;               //!< Size of this descriptor in bytes
   unsigned char  bDescriptorType;       //!< ENDPOINT descriptor type
   unsigned char  bEndpointAddress;      //!< Address of the endpoint
   unsigned char  bmAttributes;          //!< Endpoint's attributes
   unsigned short wMaxPacketSize;        //!< Maximum packet size for this EP
   unsigned char  bInterval;             //!< Interval for polling EP in ms (ignored for bulk and control, 1 for iso, 1 to 255 for INT)
} __attribute__ ((packed)) S_usb_endpoint_descriptor;

//! Table 9-9. Device_Qualifier Descriptor
typedef struct _S_usb_device_qualifier_descriptor {
   unsigned char  bLength;               //!< Size of this descriptor in bytes
   unsigned char  bDescriptorType;       //!< Device Qualifier descriptor type
   unsigned short bscUSB;                //!< Binay Coded Decimal Spec. release
   unsigned char  bDeviceClass;          //!< Class code assigned by the USB
   unsigned char  bDeviceSubClass;       //!< Sub-class code assigned by the USB
   unsigned char  bDeviceProtocol;       //!< Protocol code assigned by the USB
   unsigned char  bMaxPacketSize0;       //!< Max packet size for EP0
   unsigned char  bNumConfigurations;    //!< Number of possible configurations
   unsigned char  bReserved;             //!< Reserved for future use, must be zero
} __attribute__ ((packed)) S_usb_device_qualifier_descriptor;

//! Table 9-15. String Descriptor Zero, Specifying Languages Supported by the Device
typedef struct _S_usb_language_id{
   unsigned char  bLength;               //!< size of this descriptor in bytes
   unsigned char  bDescriptorType;       //!< STRING descriptor type
   unsigned short wlangid;               //!< language id
} __attribute__ ((packed)) S_usb_language_id;


//_____ U S B   L O W - L E V E L  D R I V E R ____________________________________

#define USB_STATUS_SUCCESS      0
#define USB_STATUS_LOCKED       1
#define USB_STATUS_ABORTED      2
#define USB_STATUS_UNCONFIGURE  3

struct _S_usb;

typedef void (*S_usb_reset)   (struct _S_usb const *);
typedef void (*S_usb_resume)  (struct _S_usb const *);
typedef void (*S_usb_suspend) (struct _S_usb const *);
typedef void (*S_new_request) (struct _S_usb const *);
typedef void (*S_set_address) (struct _S_usb const *);
typedef void (*S_set_configuration) (struct _S_usb const *);
typedef void (*S_set_interface)     (struct _S_usb const *);

typedef void (*S_usb_callback) (void *, char status, unsigned long length); //!< User application callback

typedef char (*S_usb_write) (  
  struct _S_usb const *, unsigned char endpoint,
  char const *pData, unsigned long length,
  S_usb_callback callback, void *pCallbackData);
typedef char (*S_usb_read) (  
  struct _S_usb const *, unsigned char endpoint,
  char *pData, unsigned long length,
  S_usb_callback callback, void *pCallbackData);
typedef char           (*S_usb_stall)  ( struct _S_usb const *, unsigned char endpoint);
typedef unsigned short (*S_usb_halt)   ( struct _S_usb const *, unsigned char endpoint, unsigned char bRequest);
typedef void           (*S_usb_wakeup) ( struct _S_usb const *);
typedef char           (*S_usb_cfg_endpoint) ( struct _S_usb const *, S_usb_endpoint_descriptor const *);
  

//! Usb low level API
typedef struct _S_usb {
  // Data pointers
  S_usb_request      *pSetup;             //!< Last setup packet received
  // Callbacks
  S_usb_reset         reset;              //!< Usb reset callback
  S_usb_resume        resume;             //!< Usb resume callback
  S_usb_suspend       suspend;            //!< Usb suspend callback
  S_new_request       new_request;        //!< new_request callback
  S_set_address       set_address;        //!< set_address callback
  S_set_configuration set_configuration;  //!< set_configuration callback
  S_set_interface     set_interface;      //!< set_interface callback
  // Methods
  S_usb_write         write;        //!< Write method
  S_usb_read          read;         //!< Read method
  S_usb_stall         stall;        //!< Stall method
  S_usb_halt          halt;         //!< Invoked by clear_feature
  S_usb_wakeup        wakeup;       //!< Send a remote wakeup to the host
  S_usb_cfg_endpoint  cfg_endpoint; //!< Configure endpoint  
  // Pointer to the Usb private data
  void *pUdp;
} S_usb;

// Encapsulation of the S_usb setup access
#define Usb_setup(pUsb)           ((pUsb)->pSetup)

// Encapsulation of the S_usb callback access
#define Usb_reset(pUsb)             { if (pUsb->reset)             pUsb->reset(pUsb);              }
#define Usb_resume(pUsb)            { if (pUsb->resume)            pUsb->resume(pUsb);             }
#define Usb_suspend(pUsb)           { if (pUsb->suspend)           pUsb->suspend(pUsb);            }
#define Usb_new_request(pUsb)       { if (pUsb->new_request)       pUsb->new_request(pUsb);        }
#define Usb_set_address(pUsb)       { if (pUsb->set_address)       pUsb->set_address(pUsb);        }
#define Usb_set_configuration(pUsb) { if (pUsb->set_configuration) pUsb->set_configuration(pUsb);  }
#define Usb_set_interface(pUsb)     { if (pUsb->set_interface)     pUsb->set_interface(pUsb);      }

// Encapsulation of the S_usb methods access
#define Usb_read(pUsb, endpoint, pData, length, callback, pCallbackData) \
  (pUsb)->read((pUsb), (endpoint), (pData), (length), (callback), (pCallbackData))

#define Usb_write(pUsb, endpoint, pData, length, callback, pCallbackData) \
  (pUsb)->write((pUsb), (endpoint), (pData), (length), (callback), (pCallbackData))

#define Usb_stall(pUsb, endpoint) \
  (pUsb)->stall((pUsb), (endpoint))
  
#define Usb_halt(pUsb, endpoint, request) \
  (pUsb)->halt((pUsb), (endpoint), (request))
  
#define Usb_wakeup(pUsb) \
  (pUsb)->wakeup((pUsb))

#define Usb_configure_endpoint(pUsb, epDesc) \
  pUsb->cfg_endpoint((pUsb), (epDesc))




/*@}*/

#endif // _USB_H
