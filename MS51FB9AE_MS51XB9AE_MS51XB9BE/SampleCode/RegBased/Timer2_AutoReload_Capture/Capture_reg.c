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
//  File Function: MS51 TIMER 2 Capture function demo
//***********************************************************************************************************

#include "MS51_16K_IAR.h"
/**
 * @brief       Timer2  interrupt subroutine
 */
#pragma vector=0x63
__interrupt void Capture_ISR (void){
    clr_CAPCON0_CAPF0;                  /* clear capture0 interrupt flag  */
    P1 = C0L;                            /* For capture mode CxL/CxH with data capture from I/O pin*/
    P2 = C0H;                            
    clr_T2CON_TF2;
}

/**
  * @brief   Timer2 16-bit delay register base setting 
*/
void main (void) 
{
/* Setting Multi function pin setting for GPIO toggle */ 
    ALL_GPIO_QUASI_MODE;
    P00_QUASI_MODE;
    P00 = 1;

    TIMER2_CAP2_Capture_Mode;
    IC3_P00_CAP3_BOTHEDGE_CAPTURE;
      
    set_EIE_ECAP;                        //Enable Capture interrupt
    set_T2CON_TR2;                       //Triger Timer2
    ENABLE_GLOBAL_INTERRUPT;

    while(1);

}

