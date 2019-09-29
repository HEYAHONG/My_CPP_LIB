#include "Modbus_CRC16.h"

uint16_t CRC16(uint8_t *arr_buff,uint16_t len)
{
uint16_t crc=0xFFFF;
uint16_t i, j;
 for ( j=0; j<len;j++)
 {
   crc=crc ^*arr_buff++;
   for ( i=0; i<8; i++)
  {
       if( ( crc&0x0001) >0)
       {
           crc=crc>>1;
           crc=crc^ 0xa001;
        }
      else
          crc=crc>>1;
   }
 }
return ( crc);
}


uint8_t *CRC16_Arry(uint8_t *arr_buff,uint16_t len,uint8_t *crc_arry)
{
uint16_t crc=0xFFFF;
uint16_t i, j;
 for ( j=0; j<len;j++)
 {
   crc=crc ^*arr_buff++;
   for ( i=0; i<8; i++)
  {
       if( ( crc&0x0001) >0)
       {
           crc=crc>>1;
           crc=crc^ 0xa001;
        }
      else
          crc=crc>>1;
   }
 }

 crc_arry[1]=crc>>8;
 crc_arry[0]=crc&0xff;
return crc_arry;
}
