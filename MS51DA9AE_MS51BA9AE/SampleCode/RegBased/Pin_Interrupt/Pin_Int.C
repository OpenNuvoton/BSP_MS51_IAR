/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : Jan/21/2019                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: MS51 pin interrupt demo                                                                  */
/************************************************************************************************************/
#include "MS51_8K_IAR.h"

#pragma vector=0x3B
__interrupt void Pin_INT_ISR(void){
    SFRS = 0;
    switch(PIF)
    {
      case 0x03:  break;
      default: break;
    }
    PIF = 0; 
}
/******************************************************************************
The main C function.  Program execution starts
here after stack initialization.
******************************************************************************/
void main (void) 
{
    P03_QUASI_MODE;
    P03 = 0;
    P04_QUASI_MODE;
    P04 = 1;
    P17_QUASI_MODE;
    P17 = 0;

/*----------------------------------------------------*/
/*  P0.3 set as highlevel trig pin interrupt function */
/*  otherwise, MCU into idle mode.                    */
/*----------------------------------------------------*/
    ENABLE_INT_PORT0;
    ENABLE_BIT3_RISINGEDGE_TRIG;
    ENABLE_BIT4_FALLINGEDGE_TRIG;
    set_EIE_EPI;                            // Enable pin interrupt
    ENABLE_GLOBAL_INTERRUPT;                // global enable bit
    set_PCON_IDLE;
    while(1);




}


