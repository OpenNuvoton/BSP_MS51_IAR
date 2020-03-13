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
//  File Function: ML51 Watchdog timer interrupt demo (without reset function)
//***********************************************************************************************************
#include "MS51_8K_IAR.h"
 
/************************************************************************************************************
*    WDT interrupt sub-routine
************************************************************************************************************/
#pragma vector=0x53
__interrupt void WDT_ISR (void){
    clr_WDCON_WDTF;
    set_WDCON_WDCLR;
    while((WDCON|~SET_BIT6)==0xFF);
    P17 = ~P17;
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
    WKCON = 0x02;                     //timer base 10k, Pre-scale = 1/16
    RWK = 0XFF;                      //  if prescale is 0x00, never set RWK = 0xff
    RWK = 0X00;
    ENABLE_WKT_INTERRUPT;                          // enable WKT interrupt
    ENABLE_GLOBAL_INTERRUPT;
    set_WKCON_WKTR;                         // Wake-up timer run 

    while(1)
		{
	    P17 = 0;
    Timer0_Delay(16000000,200,1000);
    P17 = 1;
    Timer0_Delay(16000000,200,1000);
    P17 = 0;
    Timer0_Delay(16000000,200,1000);
    P17 = 1;
    Timer0_Delay(16000000,200,1000);
    P17 = 0;
    Timer0_Delay(16000000,200,1000);
    P17 = 1;

		}
}