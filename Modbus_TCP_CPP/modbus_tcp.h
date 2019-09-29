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
�ص�������Ҫ��ָ�뺯��������������Ϊ:
1.���󣬵�һ���ֽ�Ϊ��վ��ַ���ڶ����ֽ�Ϊ�����룬ʣ��Ϊ�������Ӧ�����ݡ�
2.���󳤶ȡ�
3.��Ӧʹ�õ�mb_mappingָ�룬�����޸Ļ�Ӧ����
����ֵΪNULL��
*/
typedef void  (*modbus_callback)(const uint8_t * request,int request_length,modbus_mapping_t * mb_mapping);
/*
Debug��ӡ�������塣
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

        void init();//��ʼ��modbusջ

        void start();//��������

        void stop();//ֹͣ����

        void server_callback_register(modbus_callback fun);//ע��ص�����
        void server_callback_unregister(modbus_callback fun);//��ע��ص�����


    protected:
        std::string bind_ip;
        int16_t     bind_port;
        modbus_t    *ctx;
        modbus_mapping_t *mb_mapping;

        int s;//�׽���
        pthread_t  Server_thread;
        static void * Server_thread_loop(void *);
        std::vector<modbus_callback> callback_Arry;


};

#endif // MODBUS_TCP_H
