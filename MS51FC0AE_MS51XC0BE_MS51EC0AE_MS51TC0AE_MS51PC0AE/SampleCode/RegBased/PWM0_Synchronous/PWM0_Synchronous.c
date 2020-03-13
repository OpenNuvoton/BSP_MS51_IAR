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
/*  File Function: MS51 PWM simple output demo                                                              */
/************************************************************************************************************/
#include "MS51_32K_IAR.h"


/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    PWM0_ClockSource(PWM_FSYS,128);                                    // define PWM0 clock source and divider.
 
    ENABLE_PWM0_CH2_P10_OUTPUT;                                         
    P10_PUSHPULL_MODE;
    ENABLE_PWM0_CH3_P00_OUTPUT;                                       
    P00_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(2,Synchronous,EdgeAligned,0x6FF,30);    // setting PWM channel 2&3 as 30% duty high of 0x6FF PWM period = 0x0219

    ENABLE_PWM0_CH4_P01_OUTPUT;                                       
    P01_PUSHPULL_MODE;
    ENABLE_PWM0_CH5_P03_OUTPUT;                                       
    P03_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(4,Synchronous,EdgeAligned,0x6FF,50);    // setting PWM channel 4&5 as 50% duty high of 0x6FF PWM period = 0x037F
    
    PWM0_RUN();
  
    while(1);

}