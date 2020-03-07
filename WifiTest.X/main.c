/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  PIC24FJ256GA705
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB 	          :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <string.h>
#include "mcc_generated_files/system.h"
#include "../App/App.h"
#include "mcc_generated_files/uart1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/clock.h"
/*
                         Main application
 */
static eAppStates appState = APP_INIT;

static const uint8_t testString[] = "AT\r\n";
static const uint8_t resetString[] = "AT+RST\r\n";
static const uint8_t versionString[] = "AT+GMR\r\n";
static const uint8_t modeString[] = "AT+CWMODE=1\r\n";
static const uint8_t connectString[] = "AT+CWJAP=\"Hillary's Secret Email Server\",\"ilovescooter\"\r\n";
static uint32_t testStringLength = 0;
static uint32_t transmitIndex = 0;
static uint32_t receiveIndex = 0;
static uint32_t modeStringLength = 0;
static uint32_t connectStringLength = 0;
static uint8_t receiveBuffer[512];
static uint8_t connectState = 0;
static uint32_t setModeCounter = 0;

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        if(UART1_IsRxReady())
        {
            receiveBuffer[receiveIndex++] = UART1_Read();                                        
        }
        
        switch( appState )
        {
            case APP_INIT:
            {
                testStringLength = strlen((const char *)testString);
                modeStringLength = strlen((const char *)modeString);
                connectStringLength = strlen((const char *)connectString);
                
                transmitIndex = 0;
                receiveIndex = 0;
                uint32_t i = 0;
                
                // reset the ESP32 WROOM
                IO_RC9_SetLow();
                for(i = 0; i < 400000; i++);
                IO_RC9_SetHigh();
                for(i = 0; i < 400000; i++);
                
                appState = APP_SET_MODE;
                break;
            }         
            case APP_SEND_OK :
            {
                if(transmitIndex < testStringLength)
                {
                    if(UART1_IsTxReady())
                    {
                        UART1_Write(testString[transmitIndex]);
                        transmitIndex++;
                    }                    
                }
                else
                {
                    uint32_t i = 0;
                    transmitIndex = 0;
                    //for(i = 0; i < 40000; i++);
                    appState = APP_CONNECT;                    
                }
                break;
            }
            case APP_GET_RESPONSE : 
            {
                
                break;
            }
            case APP_SET_MODE:
            {                
                uint32_t i;
                if(transmitIndex < modeStringLength )
                {
                    if(UART1_IsTxReady())
                    {
                        UART1_Write(modeString[transmitIndex]);
                        transmitIndex++;
                    }
                }
                else
                {                                        
                    if(setModeCounter++ > 4000)
                    {
                        transmitIndex = 0;                                  
                        appState = APP_CONNECT;
                    }                        
                }
                break;
            }
            case APP_CONNECT :
            {                               
                if(transmitIndex < connectStringLength)
                {
                  if(UART1_IsTxReady())
                  {
                      UART1_Write(connectString[transmitIndex]);
                      transmitIndex++;
                  }
                }
                else
                {
                    transmitIndex = 0;                    
                    appState = APP_IDLE;
                }
                break;               
            }
            case APP_IDLE :
            default:
            {
                break;
            }
        }
    }

    return 1;
}
/**
 End of File
*/

