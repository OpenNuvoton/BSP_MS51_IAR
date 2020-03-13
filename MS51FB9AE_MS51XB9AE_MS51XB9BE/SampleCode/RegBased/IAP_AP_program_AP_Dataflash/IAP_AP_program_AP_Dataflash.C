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
//  File Function: MS51_16K dataflash use as EEPROM demo 
//***********************************************************************************************************
#include "MS51_16K_IAR.H"

struct
{
  unsigned int a;
  unsigned long b;
  unsigned char  c;
  
}StructData;

unsigned char ArrayData[50];
unsigned char i;
unsigned int system16highsite;


/******************************************************************************************************************/  
void main (void) 
{
    unsigned char i;
  

    for (i=0;i<128;i++)
    {
      IAPDataBuf[i]=i;
    }
/*if P1.7 trig to low start Write APROM */ 
/*Check with Nulink ICP please always keep P1.7 to high */
    while(P17);
    Erase_APROM(0x1000,128);
    Erase_Verify_APROM(0x1000,128);
    Program_APROM(0x1000,128);
    Program_Verify_APROM(0x1000,128);

    while(1);

}

