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


#include "MS51_16K_IAR.h"
//***********************************************************************************************************
#define SYS_CLK_EN              0
#define SYS_SEL                 2
#define SYS_DIV_EN              0                   //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
#define SYS_DIV                 1
#define I2C_CLOCK               2

#define EEPROM_SLA              0xA0
#define EEPROM_WR               0
#define EEPROM_RD               1

#define LED                     P3
#define EEPROM_PAGE_SIZE               32
#define PAGE_NUMBER             4

#define ERROR_CODE              0x78
#define TEST_OK                 0x00

//========================================================================================================
void Init_I2C(void)
{
    /* Set I2C clock rate */
    I2CLK = I2C_CLOCK; 

    /* Enable I2C */
    set_I2CON_I2CEN;                                   
}
//========================================================================================================
void One_Page_Read(UINT8 u8PageNumber,UINT8 u8DAT)
{
    UINT8  u8Count;
    UINT16  u16Address;

    u16Address = (UINT16)u8PageNumber*32;

    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        LED = ERROR_CODE;
        while (1);
    }

    /* Step2 */
    I2DAT = (EEPROM_SLA | EEPROM_WR);       /* Send (SLA+W) to EEPROM */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */    
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */              
    {
        LED = ERROR_CODE;
        while(1);
    }

    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send I2C EEPROM's High Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */              
    {
        LED = ERROR_CODE;
        while (1);
    }

    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send I2C EEPROM's Low Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */             
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step5 */
    set_STA;                                /* Repeated START */
    clr_SI; 
    while (!SI);
    if (I2STAT != 0x10)                     /* 0x10: A repeated START condition has been transmitted */
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step6 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = (EEPROM_SLA | EEPROM_RD);       /* Send (SLA+R) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x40)                     /* 0x40:  SLA+R has been transmitted; ACK has been received */              
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step7 */                             /* Verify I2C EEPROM data */
    for (u8Count = 0; u8Count <PAGE_SIZE; u8Count++)
    {
        set_AA;                             /* Set Assert Acknowledge Control Bit */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x50)                 /* 0x50:Data byte has been received; NOT ACK has been returned */              
        {
            LED = ERROR_CODE;

            while (1);
        }
       
        if (I2DAT != u8DAT)                 /* Send the Data to EEPROM */    
        {
            LED = ERROR_CODE;

            while (1);
        }
        u8DAT = ~u8DAT; 
    }

    /* Step8 */
    clr_AA;                                 /* Send a NACK to disconnect 24xx64 */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x58)                     /* 0x58:Data byte has been received; ACK has been returned */
    {
        LED = ERROR_CODE;

        while (1);
    }
    
    /* Step9 */    
    clr_SI;
    set_STO;
    while (STO);                            /* Check STOP signal */ 
}
//========================================================================================================
void One_Page_Write(UINT8 u8PageNumber,UINT8 u8DAT)
{
    UINT8  u8Count;
    UINT16 u16Address;

    u16Address = (UINT16)u8PageNumber*32;

    /* Step1 */
    set_STA;                                /* Send Start bit to I2C EEPROM */         
    clr_SI;
    while (!SI);
    if (I2STAT != 0x08)                     /* 0x08:  A START condition has been transmitted*/
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step2 */
    clr_STA;                                /* Clear STA and Keep SI value in I2CON */
    I2DAT = EEPROM_SLA | EEPROM_WR;         /* Send (SLA+W) to EEPROM */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x18)                     /* 0x18: SLA+W has been transmitted; ACK has been received */             
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step3 */
    I2DAT = HIBYTE(u16Address);             /* Send EEPROM's High Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step4 */
    I2DAT = LOBYTE(u16Address);             /* Send EEPROM's Low Byte Address */
    clr_SI;
    while (!SI);
    if (I2STAT != 0x28)                     /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
    {
        LED = ERROR_CODE;

        while (1);
    }

    /* Step5 */
                                            /* Write data to I2C EEPROM */
    for (u8Count = 0; u8Count < PAGE_SIZE; u8Count++)
    {
        I2DAT = u8DAT;                      /* Send data to EEPROM */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x28)                 /* 0x28:  Data byte in S1DAT has been transmitted; ACK has been received */
        {
            LED = ERROR_CODE;

            while (1);
        }   
        u8DAT = ~u8DAT;        
    }
                                            //After STOP condition, a inner EEPROM timed-write-cycle 
                                            //will occure and EEPROM will not response to outside command
                                            /* 0x18: SLA+W has been transmitted; ACK has been received */
    /* Step6 */
    do
    {
        set_STO;                            /* Set I2C STOP Control Bit */
        clr_SI;
        while (STO);                        /* Check STOP signal */
        
        set_STA;                            /* Check if no ACK is returned by EEPROM, it is under timed-write cycle */
        clr_SI;
        while (!SI);
        if (I2STAT != 0x08)                 /* 0x08:  A START condition has been transmitted*/
        {
            LED = ERROR_CODE;

            while (1);
        }

        clr_STA;                            /* Clear STA and Keep SI value in I2CON */
        I2DAT = (EEPROM_SLA | EEPROM_WR);   /* Send (SLA+W) to EEPROM */
        clr_SI;
        while (!SI);
    }while(I2STAT != 0x18);

    /* Step7 */
    set_STO;                                /* Set STOP Bit to I2C EEPROM */
    clr_SI;
    while (STO);                            /* Check STOP signal */
}
//========================================================================================================
void main(void)
{

    ALL_GPIO_QUASI_MODE;
  
    /* Initial I2C function */
    Init_I2C();                                 //initial I2C circuit
    
    /* page0 R/W */

    One_Page_Write(0,0x55);                     //page0, write 0x55,0xAA,........

    One_Page_Read (0,0x55);                     //page0, read  0x55,0xAA,........

    while (1);
/* =================== */
}

