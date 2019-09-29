#ifndef CPP__MODBUS_TCP_H
#define CPP__MODBUS_TCP_H
#include <iostream>
#include <string>
#include <vector>
#include "stdint.h"
#include "pthread.h"
#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>
#include <errno.h>
#include "modbus/modbus.h"
#include "modbus/modbus-tcp.h"

/*
回调函数需要的指针函数参数输入依次为:
1.请求，第一个字节为从站地址，第二个字节为功能码，剩余为功能码对应的数据。
2.请求长度。
3.回应使用的mb_mapping指针，用于修改回应数据
返回值为NULL。
*/
typedef void  (*modbus_callback)(const uint8_t * request,int request_length,modbus_mapping_t * mb_mapping);
/*
Debug打印函数定义。
*/
typedef int    (*Debug_Printf_t)(FILE *fp,const char * format,...);

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
int  Debug_Printf_NULL(FILE * fp,const char * format,...);
#ifdef __cplusplus
}
#endif // __cplusplus


class Modbus_TCP
{
        Debug_Printf_t Debug_Error;
        Debug_Printf_t Debug_Info;
    public:
        Modbus_TCP();
        Modbus_TCP(std::string ip,int16_t port);
        virtual ~Modbus_TCP();
        void SetIP(std::string ip,int16_t port);
        void SetDebug(bool Is_Debug_Error,bool Is_Debug_Info);
        bool Get_Is_Debug_Error();
        bool Get_IS_Debug_Info();

        void init();//初始化modbus栈

        void start();//启动服务

        void stop();//停止服务

        void server_callback_register(modbus_callback fun);//注册回调函数
        void server_callback_unregister(modbus_callback fun);//反注册回调函数


    protected:
        std::string bind_ip;
        int16_t     bind_port;
        modbus_t    *ctx;
        modbus_mapping_t *mb_mapping;

        int s;//套接字
        pthread_t  Server_thread;
        static void * Server_thread_loop(void *);
        std::vector<modbus_callback> callback_Arry;


};

#endif // MODBUS_TCP_H
