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
#include "MS51_8K_IAR.h"

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

    /*loop here while P46 = 1; */  
    P17_INPUT_MODE;
    while(P17);


/** IAP program APROM as EEPROM way
   * include eeprom.c in Library       */ 
 
    Write_DATAFLASH_BYTE (0x3882,0x34);

    for(i=0;i<50;i++)
    {
      ArrayData[i]=i;
    }

    StructData.a=0x5555;
    StructData.b=0x55555555;
    StructData.c=0x55;
  
    Write_DATAFLASH_ARRAY(0x38E0,ArrayData,50);//write 50 bytes
    Write_DATAFLASH_ARRAY(0x38FE,(unsigned char *)&StructData,sizeof(StructData));//write structure
  
  
/*call read byte */
    system16highsite = Read_APROM_BYTE((unsigned int __code *)0x38FD)<<8 + Read_APROM_BYTE((unsigned int __code *)0x38FE);

    while(1);

}

