/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: ML51 TIMER 2 Capture function demo
//***********************************************************************************************************

#include "MS51_32K_IAR.h"
/**
 * @brief       Timer2  interrupt subroutine
 */
#pragma vector=0x63
__interrupt void Capture_ISR (void){
    _push_(SFRS);

    _push_(SFRS);
  
    clr_CAPCON0_CAPF0;                  /* clear capture0 interrupt flag  */
    clr_T2CON_TF2;
  
    _pop_(SFRS);
}


/**
  * @brief   Timer2 16-bit delay register base setting 
*/
void main (void) 
{
    ALL_GPIO_QUASI_MODE;
    P00_QUASI_MODE;
    P00 = 1;

    TIMER2_Compare_Capture_Mode;
    IC3_P00_CAP2_BOTHEDGE_CAPTURE;

    set_EIE_ECAP;                        //Enable Capture interrupt
    set_T2CON_TR2;                       //Triger Timer2
    ENABLE_GLOBAL_INTERRUPT;
    
    while(1);

}

