extern unsigned char __xdata DIDBuffer[4];
extern unsigned char __xdata UIDBuffer[12];
extern unsigned char __xdata UCIDBuffer[12];
extern unsigned char __xdata IAPDataBuf[128];
extern unsigned char __xdata IAPCFBuf[5];

unsigned char Read_APROM_BYTE(unsigned int __code *u16_addr);
void Write_DATAFLASH_BYTE(unsigned int u16EPAddr, unsigned char u8EPData);
void Write_DATAFLASH_ARRAY(unsigned int u16_addr,unsigned char *pDat,unsigned int num);
void Read_DATAFLASH_ARRAY(unsigned int u16_addr,unsigned char *pDat,unsigned int num);
unsigned char WriteDataToOnePage(unsigned int u16_addr,const unsigned char *pDat,unsigned char num);
