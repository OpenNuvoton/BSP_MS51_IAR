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
/*  File Function: MS51 ADC / Bandgap input demo                                                       */
/************************************************************************************************************/
#include "MS51_32K_IAR.h"

/************************************************************************************************************/
/*   PWM interrupt subroutine                                                                               */
/************************************************************************************************************/

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{
    PWM0_ClockSource(PWM_FSYS,8);                                    // define PWM0 clock source and divider.
  
    ENABLE_PWM0_CH0_P12_OUTPUT;                                       //Mark since P0.2 also ICE_CLK pin       
    P12_PUSHPULL_MODE;                                               
    PWM0_ConfigOutputChannel(0,Independent,EdgeAligned,0x06FF,10);    // setting PWM channel 0 as 10% duty high of 0x6FF PWM period = 0x00B3
    
    ENABLE_PWM0_CH1_P11_OUTPUT;                                         
    P11_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(1,Independent,EdgeAligned,0x06FF,20);    // setting PWM channel 2 as 30% duty high of 0x6FF PWM period = 0x0219

    ENABLE_PWM0_CH2_P10_OUTPUT;                                         
    P10_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(2,Independent,EdgeAligned,0x06FF,30);    // setting PWM channel 2 as 30% duty high of 0x6FF PWM period = 0x0219
  
    ENABLE_PWM0_CH3_P00_OUTPUT;                                       
    P00_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(3,Independent,EdgeAligned,0x06FF,40);    // setting PWM channel 3 as 40% duty high of 0x6FF PWM period = 0x02CC
  
    ENABLE_PWM0_CH4_P01_OUTPUT;                                       
    P01_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(4,Independent,EdgeAligned,0x06FF,50);    // setting PWM channel 4 as 50% duty high of 0x6FF PWM period = 0x037F
    
    ENABLE_PWM0_CH5_P03_OUTPUT;                                       
    P03_PUSHPULL_MODE;
    PWM0_ConfigOutputChannel(5,Independent,EdgeAligned,0x06FF,60);    // setting PWM channel 5 as 60% duty high of 0x6FF PWM period = 0x0432
    
    PWM0_RUN();
}