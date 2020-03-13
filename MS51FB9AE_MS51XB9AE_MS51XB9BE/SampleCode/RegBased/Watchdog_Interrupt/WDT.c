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
//  File Function: MS51 Watchdog timer interrupt demo (without reset function)
//***********************************************************************************************************
#include "MS51_16K_IAR.h"
 
/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
#pragma vector=0x53
__interrupt void WDT_ISR (void){
    clr_WDCON_WDTF;
    set_WDCON_WDCLR;
    while((WDCON|~SET_BIT6)==0xFF);
    P12 = ~P12;
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
/* Note
  WDT timer base is LIRC 10Khz
*/
    P12_PUSHPULL_MODE;
//--------------------------------------------------------
//Warning:
//Pleaes always check CONFIG WDT disable first 
//only when WDT reset disable, WDT use as pure timer
//--------------------------------------------------------
    TA=0xAA;TA=0x55;WDCON=0x07;      //Setting WDT prescale 
    set_WDCON_WIDPD;                       //WDT run in POWER DOWM mode setting if needed
    ENABLE_WDT_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;
    set_WDCON_WDTR;                       //WDT run
    set_WDCON_WDCLR;                      //Clear WDT timer
    while((WDCON|~SET_BIT6)==0xFF);


    while (1)
    {
      set_PCON_PD;
    }

}
