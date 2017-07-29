//*--------------------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : Boot_loader main file
//* Object              :
//* Translator          :
//* 1.0 19/03/01 HI     : Creation
//* 1.1 02/10/02 FB     : Add on Svc DataFlash
//*--------------------------------------------------------------------------------------

#include "main.h"
#include "version.h"
#include "string.h"

// Externals
extern char         AT91F_GetChar(void);
extern void         AT91F_PutChar(char);
extern void         Jump(int);
extern unsigned int AT91F_EndOfCalibration(void);

/// Flag set at init time depending on input frequency detection.
volatile unsigned int USBAllowed = 1;


// Variable
struct _AT91S_CDC   pCDC;
AT91S_XMODEM        xModem;
char                Terminal = 0;

// Methods
void (*AT91PF_L1_PUT_Data)(char* data, unsigned int length); //pointer to function L1_PUT_Data for USB or UART
void (*AT91PF_L1_GET_Data)(char* data, unsigned int length); //pointer to function L1_GET_Data for USB or UART
void (*AT91PF_L0_PUT_Data)(char* data, unsigned int length); //pointer to function L0_PUT_Data for USB or UART
int (*AT91PF_L0_GET_Data)(char* data, unsigned int length); //pointer to function L0_GET_Data for USB or UART


//*----------------------------------------------------------------------------
//* \fn    AT91F_L0Term_PUT_Data
//* \brief This function allows data rx by USART
//*----------------------------------------------------------------------------
void AT91F_L0Term_PUT_Data(char* data,unsigned int length)
{
    char temp, buf[12], *dataAscii;
    int i, intValue;

    if (Terminal)
    {
        if (length == 4)
            intValue = *(int *)data;
        else if(length == 2)
            intValue = *(short *)data;
        else
            intValue = *(char *)data;


        dataAscii = buf + 2;
        dataAscii += length*2 -1;

        for (i = 0; i < length * 2; i++)
        {
            temp = (char)(intValue & 0xf);

            if (temp <=0x9)
                *dataAscii = temp | 0x30;
            else *dataAscii = temp + 0x37;

            intValue >>= 4;
            dataAscii --;
        }
        buf[0] = '0';
        buf[1] = 'x';
        buf[length*2 + 2] = '\n';
        buf[length*2 + 3] = '\r';
        AT91PF_L0_PUT_Data(buf, length * 2 + 4);
    }
    else AT91PF_L0_PUT_Data(data, length);
    return;
}


//*----------------------------------------------------------------------------
//* \fn    AT91F_L0UART_GET_Data
//* \brief This function allows data rx by USART
//*----------------------------------------------------------------------------
int AT91F_L0UART_GET_Data(char* data,unsigned int length)
{
    *data = AT91F_GetChar();
    return 1;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_L0UART_PUT_Data
//* \brief This function allows data tx by USART
//*----------------------------------------------------------------------------
void AT91F_L0UART_PUT_Data(char* data,unsigned int length)
{
    int i;

    for (i = 0; i < length; i++)
        AT91F_PutChar(*data++);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_L0USB_PUT_Data
//* \brief This function allows data tx by USB
//*----------------------------------------------------------------------------
void AT91F_L0USB_PUT_Data(char* data,unsigned int length)
{
    pCDC.Write(&pCDC, data, length);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_L0USB_GET_Data
//* \brief This function allows data rx by USB
//*----------------------------------------------------------------------------
int AT91F_L0USB_GET_Data(char* data,unsigned int length)
{
    return pCDC.Read(&pCDC, data, length);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_L1USB_PUT_Data
//* \brief This function allows data tx by USB
//*----------------------------------------------------------------------------
void AT91F_L1USB_PUT_Data(char* data,unsigned int length)
{
#ifdef UDP_HIGH_SPEED
    AT91F_L0USB_PUT_Data(data, length);
#else
    unsigned int size;

    while(length)
    {
        size = (length < SIZEBUFMAX) ? length : SIZEBUFMAX;
        AT91F_L0USB_PUT_Data(data, size);
        length -= size;
        data += size;
    }
#endif
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_L1USB_GET_Data
//* \brief This function allows data rx by USB
//*----------------------------------------------------------------------------
void AT91F_L1USB_GET_Data(char* data,unsigned int length)
{
    unsigned int size;

    while(length)
    {
        size = AT91F_L0USB_GET_Data(data, (length < SIZEBUFMAX) ? length : SIZEBUFMAX);
        length -= size;
        data += size;
    }
}

//*--------------------------------------------------------------------------------------
//* Function Name       : main
//* Object              :
//* Input Parameters    :
//* Output Parameters   :
//*--------------------------------------------------------------------------------------
int main (void)
{
    unsigned int currentNumber;
    volatile int i, length;
    char command, *pData, *ptr, data[SIZEBUFMAX];

    pCDC.currentConfiguration = 1;
    
    // Get which protocol is used
    if (USBAllowed) {
        AT91PF_L1_PUT_Data = AT91F_L1USB_PUT_Data;
        AT91PF_L1_GET_Data = AT91F_L1USB_GET_Data;

        AT91PF_L0_PUT_Data = AT91F_L0USB_PUT_Data;
        AT91PF_L0_GET_Data = AT91F_L0USB_GET_Data;
    }
    else {
        AT91PF_L1_PUT_Data = xModem.AT91F_XMD_Xup;
        AT91PF_L1_GET_Data = xModem.AT91F_XMD_Xdown;

        AT91PF_L0_PUT_Data = AT91F_L0UART_PUT_Data;
        AT91PF_L0_GET_Data = AT91F_L0UART_GET_Data;
    }

    pData = NULL;
    command = 'z';

    // Start waiting some cmd
    while (1) {
        length = AT91PF_L0_GET_Data(data, SIZEBUFMAX);
        ptr = data;
        for(i = 0; i < length; i++) {
            if (*ptr == 0xff);
            else if (*ptr == '#') {
                if (Terminal == 1) {
                    AT91PF_L0_PUT_Data("\n\r", 2);
                }

                if (command == 'S') {
                    AT91PF_L1_GET_Data(pData, currentNumber);

                } else if (command == 'R') {
                    AT91PF_L1_PUT_Data(pData, currentNumber);

                } else if (command == 'O') {
                    *pData = (char) currentNumber;

                } else if (command == 'H') {
                    *((short *)pData) = (short)currentNumber;

                } else if (command == 'W') {
                    *((int *)pData) = currentNumber;

                } else if (command == 'o') {
                    AT91F_L0Term_PUT_Data(pData, 1);

                } else if (command == 'h') {
                    currentNumber = *((short *)pData);
                    AT91F_L0Term_PUT_Data((char*) &currentNumber, 2);

                } else if (command == 'w') {
                    currentNumber = *((int *)pData);
                    AT91F_L0Term_PUT_Data((char*) &currentNumber, 4);

                } else if (command == 'G') {
                    Jump(currentNumber);

                } else if (command == 'T') {
                    Terminal = 1;
                    AT91PF_L0_PUT_Data("\n\r", 2);

                } else if (command == 'N') {
                    if (Terminal == 0) {
                        AT91PF_L0_PUT_Data("\n\r", 2);
                    }
                    Terminal = 0;

                } else if (command == 'V') {
                    AT91PF_L0_PUT_Data("v", 1);
                    AT91PF_L0_PUT_Data((char *)RomBOOT_Version, strlen(RomBOOT_Version));
                    AT91PF_L0_PUT_Data(" ", 1);
                    ptr = (char *)&(__DATE__);
                    i=0;
                    while (*ptr ++ != '\0')
                        i++;
                    AT91PF_L0_PUT_Data((char *)&(__DATE__), i);
                    AT91PF_L0_PUT_Data(" ",1);
                    i = 0;
                    ptr = (char *)&(__TIME__);
                    while (*ptr ++ != '\0')
                        i++;
                    AT91PF_L0_PUT_Data((char *)&(__TIME__), i);
                    AT91PF_L0_PUT_Data("\n\r", 2);
                }

                command = 'z';
                currentNumber = 0;

                if (Terminal) {
                    AT91PF_L0_PUT_Data(">", 1);
                }
            } else {
                if (('0' <= *ptr) && (*ptr <= '9')) {
                    currentNumber = (currentNumber << 4) | (*ptr - '0');

                } else if (('A' <= *ptr) && (*ptr <= 'F')) {
                    currentNumber = (currentNumber << 4) | (*ptr - 'A' + 0xa);

                } else if (('a' <= *ptr) && (*ptr <= 'f')) {
                    currentNumber = (currentNumber << 4) | (*ptr - 'a' + 0xa);

                } else if (*ptr == ',') {
                    pData = (char *)currentNumber;
                    currentNumber = 0;

                } else {
                    command = *ptr;
                    currentNumber = 0;
                }
            }
            ptr++;
        }
    }
}

