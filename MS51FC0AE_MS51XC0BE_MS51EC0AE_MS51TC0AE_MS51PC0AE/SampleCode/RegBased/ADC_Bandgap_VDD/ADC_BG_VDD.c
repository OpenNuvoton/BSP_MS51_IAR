/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/*  Website: http://www.nuvoton.com                                                                        */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : May/21/2019                                                                                   */
/***********************************************************************************************************/

//**********************************************************************************************************/
//  File Function: MS51 ADC read bandgap to VDD demo                                                  */
//**********************************************************************************************************/
#include "MS51_32K_IAR.h"

//*****************  The Following is in define in Fucntion_define.h  ***************************
//****** Always include Function_define.h call the define you want, detail see main(void) *******
//***********************************************************************************************
double  Bandgap_Voltage,VDD_Voltage,Bandgap_Value;      //please always use "double" mode for this
unsigned  char __xdata ADCdataH, ADCdataL;
int ADCsumH=0, ADCsumL=0;
unsigned char ADCavgH,ADCavgL;
unsigned char BandgapHigh,BandgapLow;
double bgvalue;

 /******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{

/*Read bandgap value */
 //   READ_BANDGAP();
/* ADC Low speed initial*/  
    ENABLE_ADC_BANDGAP;
    ADCCON1|=0x30;            /* clock divider */
    ADCCON2|=0x0E;            /* AQT time */
    AUXR1|=SET_BIT4;          /* ADC clock low speed */
/*start bandgap ADC */
    clr_ADCCON0_ADCF;
    set_ADCCON0_ADCS;                                
    while(ADCF == 0);
    ADCdataH = ADCRH;
    ADCdataL = ADCRL;
/* to convert VDD value */
        
    Bandgap_Voltage= READ_BANDGAP()*3/4;           
    VDD_Voltage = (0x1000/bgvalue)*Bandgap_Voltage;

    
    while(1);

}


