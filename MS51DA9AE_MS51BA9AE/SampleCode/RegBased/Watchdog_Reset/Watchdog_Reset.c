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
//  File Function: ML51 Watchdog reset disable by modify CONFIG demo
//***********************************************************************************************************
#include "MS51_8K_IAR.h"

/***********************************************************************
  WDT CONFIG enable 
  warning : this macro is only when ICP not enable CONFIG WDT function
  copy this marco code to you code to enable WDT reset.
************************************************************************/
void main (void)
{
    unsigned char i;
    P17_QUASI_MODE;
    P17 = 1;
    Disable_WDT_Reset_Config();
/*----------------------------------------------------------------------------------------------*/
/* WDT Init !!! ENABLE CONFIG WDT FIRST !!!                                                     */
/* Warning:                                                                                     */
/* Always check CONFIG WDT enable first, CONFIG not enable, SFR can't enable WDT reset          */
/* Please call Enable_WDT_Reset_Config() function to enable CONFIG WDT reset                    */
/*----------------------------------------------------------------------------------------------*/
    for(i=0;i<3;i++)
    {
     P17=~P17;
     Timer0_Delay(16000000,500,1000);
    }

    TA=0xAA;TA=0x55;WDCON|=0x07;                //Setting WDT prescale 
    set_WDCON_WDCLR;                            //Clear WDT timer
    while((WDCON|~SET_BIT6)==0xFF);             //confirm WDT clear is ok before into power down mode

    set_WDCON_WDTR;                             //WDT run

    while (1)
    {
      if (P00)
      {
         Disable_WDT_Reset_Config();               //Software disable WDT reset CONFIG setting
          for(i=0;i<5;i++)
          {
            P17=~P17;
            Timer0_Delay(16000000,50,1000);
          }
      }
      else 
      {
         Enable_WDT_Reset_Config();
         set_PCON_PD;
      }
    }
}
