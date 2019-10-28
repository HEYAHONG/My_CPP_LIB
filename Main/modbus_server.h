#ifndef MODBUS_SERVER_H_INCLUDED
#define MODBUS_SERVER_H_INCLUDED
#include "iostream"
#include "stdint.h"
#include "pthread.h"
#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>
#include <errno.h>
#include "modbus/modbus.h"
using namespace std;

//启动modbus服务器
void modbus_server_start(string ip,uint16_t port);

//关闭modbus服务器
void modbus_server_stop();


/*
回调函数需要的指针函数参数输入依次为:
1.请求，第一个字节为从站地址，第二个字节为功能码，剩余为功能码对应的数据。
2.请求长度。
3.回应使用的mb_mapping指针，用于修改回应数据
返回值为NULL。
*/
typedef void  (*modbus_callback)(const uint8_t * request,int request_length,modbus_mapping_t * mb_mapping);
/*
回调函数结构体，链表形式
*/
typedef struct _modbus_callback_t
{
    modbus_callback modbus_callback_fun;
    _modbus_callback_t * next;
}
modbus_callback_t;

//处理回调函数需要的变量
extern uint8_t Modbus_request[];
extern int Modbus_request_length;
extern modbus_callback_t modbus_callback_start;

//注册回调函数
void modbus_server_callback_register(modbus_callback modbus_callback_fun);
//取消注册回调函数
void modbus_server_callback_unregister(modbus_callback modbus_callback_fun);


#endif // MODBUS_SERVER_H_INCLUDED
