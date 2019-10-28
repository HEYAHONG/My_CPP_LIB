#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
#include "iostream"
#include "json/json.h"
#include <fstream>
using namespace std;

//默认配置名
#define  config_file_name "config.json"

typedef struct
{
    string  Query_String_Prefix;
    string  modbus_bind_address;
    int     modbus_bind_port;
} config_data_t;

//用于load_config加载的配置结构体
extern config_data_t config_data;

//配置存储变量
extern Json::Value config;

//保存配置到文件
void save_config();

//加载配置文件
void load_config();

#endif // CONFIG_H_INCLUDED
