/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2019
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: MS51 ADC trig by GPIO demo
//***********************************************************************************************************
#include "MS51_32K_IAR.h"


unsigned char __xdata ResultTable[256];
unsigned char  ADC_CONT_FINAL_FLAG;

/**
 * @brief       ADC Interrupt Subroutine
 * @param       None
 * @return      None
 * @details     Set ADC continus finished flag.
 */
#pragma vector=0x5B
__interrupt void ADC_ISR(void){
  _push_(SFRS);
  
    clr_ADCCON0_ADCF;
    ADC_CONT_FINAL_FLAG = 1;
    
  _pop_(SFRS);
}

/**
 * @brief       ADC continus mode main loop
 * @param       None
 * @return      None
 * @details     None
 */
void main (void) 
{
    unsigned char i;
    unsigned int temp;
/* UART0 initial setting
  * include sys.c in Library for modify HIRC value to 24MHz
  * include uart.c in Library for UART initial setting
*/
    MODIFY_HIRC(HIRC_24);
    P06_PUSHPULL_MODE;
    UART_Open(24000000,UART0_Timer3,115200);
    ENABLE_UART0_PRINTF;
  
/*loop clear XRAM area . */   
    for (i=0;i<192;i++)
    {
        ResultTable[i] =0;
    }
/* ADC continus mode setting . 
   *include adc.c for ADC initial setting
*/
    ENABLE_ADC_CONTINUES_MODE;                         /* Opend ADC as continous mode */
    ENABLE_ADC_CH0;                                    /* and input from AIN0 P1.7  */
    ADC_InitialContinous(0x300,128);                   /* Define data restore in RAM start address and ADC total sample number */
    ADC_ConvertTime(ADC_CH0,2,7);                      /*  ADC clock = Fsys/4, sampling timer select longest value is 7     */
    
    clr_ADCCON0_ADCF;
    ENABLE_ADC_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    
    set_ADCCON0_ADCS;                                  // Trig ADCS bit to start ADC 

/* ADC finished and print the result from XRAM. */
    while(1)
    {
      if (ADC_CONT_FINAL_FLAG)
      {
            DISABLE_ADC;
             for(i=0;i<128;i++)
            {
              temp=(ResultTable[i]<<4)+(ResultTable[i/2+128]&0x0F);
              SFRS = 0;
              printf_UART ("\n ADC No.%BD",i);
              printf_UART (" = 0x%02X ", temp);
              i++;
              temp=(ResultTable[i]<<4)+((ResultTable[(i-1)/2+128]>>4)&0x0F);
              printf_UART ("\n ADC No.%BD",i);
              printf_UART (" = 0x%02X ", temp);
              if(i==127)
              ADC_CONT_FINAL_FLAG=0;
            }
        }
      }        
}
