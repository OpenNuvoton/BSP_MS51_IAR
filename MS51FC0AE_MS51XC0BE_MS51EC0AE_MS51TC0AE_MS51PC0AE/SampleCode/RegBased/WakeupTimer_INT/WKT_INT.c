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
//  File Function: ML51 WKT auto wakeup demo
//***********************************************************************************************************
#include "MS51_32K_IAR.h"


#pragma vector=0x8B
__interrupt void WKT_ISR(void){
    _push_(SFRS);

      clr_WKCON_WKTF;                                   //clear interrupt flag
    P17 ^= 1;
  
    _pop_(SFRS);
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{

    P17_PUSHPULL_MODE;
//-----------------------------------------------------
//  WKT initial   
//-----------------------------------------------------  

    WKCON = 0x07;                      //timer base 10k, Pre-scale = 1/1024
//    RWK = 0XFF;                      //  if prescale is 0x00, never set RWK = 0xff
    RWKH = 0xFF;
    RWKL = 0xF0;
    ENABLE_WKT_INTERRUPT;                     // enable WKT interrupt
    set_WKCON_WKTR;                    // Wake-up timer run 
    ENABLE_GLOBAL_INTERRUPT;
  
    while(1)
    {
      set_PCON_PD;
    }
}

