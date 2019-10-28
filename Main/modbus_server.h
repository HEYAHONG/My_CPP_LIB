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

//����modbus������
void modbus_server_start(string ip,uint16_t port);

//�ر�modbus������
void modbus_server_stop();


/*
�ص�������Ҫ��ָ�뺯��������������Ϊ:
1.���󣬵�һ���ֽ�Ϊ��վ��ַ���ڶ����ֽ�Ϊ�����룬ʣ��Ϊ�������Ӧ�����ݡ�
2.���󳤶ȡ�
3.��Ӧʹ�õ�mb_mappingָ�룬�����޸Ļ�Ӧ����
����ֵΪNULL��
*/
typedef void  (*modbus_callback)(const uint8_t * request,int request_length,modbus_mapping_t * mb_mapping);
/*
�ص������ṹ�壬������ʽ
*/
typedef struct _modbus_callback_t
{
    modbus_callback modbus_callback_fun;
    _modbus_callback_t * next;
}
modbus_callback_t;

//����ص�������Ҫ�ı���
extern uint8_t Modbus_request[];
extern int Modbus_request_length;
extern modbus_callback_t modbus_callback_start;

//ע��ص�����
void modbus_server_callback_register(modbus_callback modbus_callback_fun);
//ȡ��ע��ص�����
void modbus_server_callback_unregister(modbus_callback modbus_callback_fun);


#endif // MODBUS_SERVER_H_INCLUDED
