#include <iostream>
#include "modbus_tcp.h"

//打印modbus信息回调函数
void modbus_print_message(const uint8_t * buff,int size,modbus_mapping_t * mb_mapping)
{
printf("Request:");
int temp=0;
for(temp=0;temp < size;temp ++)
    printf("%02X",buff[temp]);
printf(",Slave Addr:%d,Function Code:%02X,Data Length:%d\n",buff[0],buff[1],size);
}

void modbus_process_03_code(const uint8_t * buff,int size,modbus_mapping_t * mb_mapping)
{
int temp=0;
if(buff[1]==0x03)
    {
        int start=0,length=0;
        start=buff[2];
        start<<=8;
        start+=buff[3];

        length=buff[4];
        length<<=8;
        length+=buff[5];

        //所有值都填写地址值
        for(temp=0;temp<length;temp++)
            mb_mapping->tab_registers[temp+start]=temp+start+1;
    }
}

int main(int argc,char * argv[])
{

printf("Program Started\n");
Modbus_TCP temp;
temp.SetIP("0.0.0.0",1502);
temp.SetDebug(false,true);
temp.server_callback_register(modbus_print_message);
temp.server_callback_register(modbus_print_message);
temp.server_callback_unregister(modbus_print_message);
temp.server_callback_register(modbus_process_03_code);
temp.init();
temp.start();


while(1)
{
    getchar();
    temp.stop();
    break;
}

return 0;
}
