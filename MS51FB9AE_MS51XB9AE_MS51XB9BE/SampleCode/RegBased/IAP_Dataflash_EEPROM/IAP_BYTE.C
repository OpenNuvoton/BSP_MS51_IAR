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
#include "MS51_16K_IAR.h"


#define ADDR_BASE 0x5700

#define FLASH_L_LOW      ADDR_BASE+1
#define FLASH_L_HIGH     ADDR_BASE+2
#define FLASH_H_LOW      ADDR_BASE+3
#define FLASH_H_HIGH     ADDR_BASE+4

    unsigned char datatemp;
    unsigned int system16highsite;
/******************************************************************************************************************/  
void main (void) 
{

    P12_INPUT_MODE;
    while(P12);
/* -------------------------------------------------------------------------*/
/*  Dataflash use APROM area, please ALWAYS care the address of you code    */
/*  APROM 0x3800~0x38FF demo as dataflash                                   */
/*   Please use Memory window key in C:0x3800 to check earse result          */        
/* -------------------------------------------------------------------------*/
/*call write byte */
    Write_DATAFLASH_BYTE (0x3800,0x66);  
    Write_DATAFLASH_BYTE (0x3801,0x65);  
    Write_DATAFLASH_BYTE (0x3802,0x64);  
    Write_DATAFLASH_BYTE (0x3803,0x63);  
    Write_DATAFLASH_BYTE (0x3880,0x61);
    Write_DATAFLASH_BYTE (FLASH_L_LOW,0x55);
    Write_DATAFLASH_BYTE (FLASH_L_HIGH,0x77);
    Write_DATAFLASH_BYTE (FLASH_H_LOW,0x88);
    Write_DATAFLASH_BYTE (FLASH_H_HIGH,0x99);
/*call read byte  */

    while(1);

}
//-----------------------------------------------------------------------------------------------------------
