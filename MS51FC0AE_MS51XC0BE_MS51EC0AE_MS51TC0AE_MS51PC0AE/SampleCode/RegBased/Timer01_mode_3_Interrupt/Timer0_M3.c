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
//  File Function: ML51 Timer 0 mode 3 demo
//***********************************************************************************************************
#include "MS51_32K_IAR.h"


/* if define TIMER0_FSYS_DIV12, Timer0 = (256-56)*12/16MHz = 150us ,   */
/*                                Timer1 = (256-200)*12/16MHz = 42us , */
/* if define TIMER0_FSYS, Timer = (256-56)/16MHz = 12.5us              */
/*                          Timer = (256-200)/16MHz = 3.5us            */
#define TH0_INIT        56
#define TL0_INIT        200

/************************************************************************************************************
*    TIMER 0 interrupt subroutine
************************************************************************************************************/
#pragma vector=0x0B
__interrupt void Timer0_ISR(void){              
    _push_(SFRS);

      TL0 = TL0_INIT;                              
    TF0=0;
  
    _pop_(SFRS);
}


#pragma vector=0x1B
__interrupt void Timer1_ISR(void){              
    _push_(SFRS);

      TH0 = TH0_INIT;
    TF1=0;
  
    _pop_(SFRS);
}


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main (void)
{
    P17_PUSHPULL_MODE;
    P05_PUSHPULL_MODE;
    set_P0S_5;
    ENABLE_TIMER0_MODE2;
    TIMER0_FSYS;
    set_TOE_T0OE;

    TH0 = TH0_INIT;            //initial counter values 
    TL0 = TL0_INIT;    
   
    ENABLE_TIMER0_INTERRUPT;                       //enable Timer0 interrupt
    ENABLE_GLOBAL_INTERRUPT;                       //enable interrupts
  
    set_TCON_TR0;                                    //Timer0 run

    while(1);
}

