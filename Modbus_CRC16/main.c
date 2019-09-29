#include <stdio.h>
#include <stdlib.h>
#include "Modbus_CRC16.h"
int main()
{
    uint8_t T[8]={0x01,0x03,0x00,0x05,0x00,0x02};
    uint16_t i=0;
    printf("CRC16 is:%04X\n",CRC16(T,6));
    CRC16_Arry(T,6,&T[6]);
    printf("Arry is:\n");
    for(i=0;i<sizeof(T);i++)
    {
        printf("%02X",T[i]);
    }
    printf("\n");

    return 0;
}
