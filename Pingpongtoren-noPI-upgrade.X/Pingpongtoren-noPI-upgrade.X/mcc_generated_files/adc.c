/**
  ADC Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc.c

  @Summary
    This is the generated driver implementation file for the ADC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for ADC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18345
        Driver Version    :  2.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc.h"
#include "device_config.h"
#include "mcc.h"

/**
  Section: Macro Declarations
*/

#define ACQ_US_DELAY 5

void (*ADC_InterruptHandler)(void);

/**
  Section: ADC Module APIs
*/

uint16_t ADC_result = 0;

void ADC_Initialize(void)
{
    // set the ADC to the options selected in the User Interface
    
    // ADFM left; ADNREF VSS; ADPREF VDD; ADCS FOSC/32; 
    ADCON1 = 0x20;
    
    // ADACT TMR2_match_PR2; 
    ADACT = 0x05;
    
    // ADRESL 0; 
    ADRESL = 0x00;
    
    // ADRESH 0; 
    ADRESH = 0x00;
    
    // ADGO stop; ADON enabled; CHS ANA0; 
    ADCON0 = 0x01;
    
    // Enabling ADC interrupt.
    PIE1bits.ADIE = 1;
	
	// Set Default Interrupt Handler
    ADC_SetInterruptHandler(ADC_DefaultInterruptHandler);
}

void ADC_SelectChannel(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;  
}

void ADC_StartConversion(void)
{
    // Start the conversion
    ADCON0bits.ADGO = 1;
}


bool ADC_IsConversionDone(void)
{
    // Start the conversion
   return ((bool)(!ADCON0bits.ADGO));
}

adc_result_t ADC_GetConversionResult(void)
{
    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

adc_result_t ADC_GetConversion(adc_channel_t channel)
{
    // select the A/D channel
    ADCON0bits.CHS = channel;    
    
    // Turn on the ADC module
    ADCON0bits.ADON = 1;

    // Acquisition time delay
    __delay_us(ACQ_US_DELAY);

    // Start the conversion
    ADCON0bits.ADGO = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.ADGO)
    {
    }

    // Conversion finished, return the result
    return ((adc_result_t)((ADRESH << 8) + ADRESL));
}

void ADC_TemperatureAcquisitionDelay(void)
{
    __delay_us(200);
}

void ADC_ISR(void)
{
    // Clear the ADC interrupt flag
    PIR1bits.ADIF = 0;
	
	if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
}

void ADC_SetInterruptHandler(void (* InterruptHandler)(void)){
    ADC_InterruptHandler = InterruptHandler;
}

void ADC_DefaultInterruptHandler(void){
    // add your ADC interrupt custom code
    // or set custom function using ADC_SetInterruptHandler()
}

uint16_t ADC_GetResult(void) {
    return ADC_result;
}

// ADC initialiseren en calibreren
void ADC_Start(uint16_t reference) {
    ADC_SelectChannel(Receiver);
    ADC_StartConversion();
    TMR2_Initialize();
    TMR2_StartTimer();
}

/**
 End of File
*/