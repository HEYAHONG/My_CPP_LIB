#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include "iostream"
#include "json/json.h"
#include <fstream>
using namespace std;

//Ĭ��������
#define  config_file_name "config.json"

typedef struct
{
    string  Query_String_Prefix;
    string  modbus_bind_address;
    int     modbus_bind_port;
} config_data_t;

//����load_config���ص����ýṹ��
extern config_data_t config_data;

//���ô洢����
extern Json::Value config;

//�������õ��ļ�
void save_config();

//���������ļ�
void load_config();

#endif // CONFIG_H_INCLUDED
