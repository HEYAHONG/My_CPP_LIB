#include "json_config.h"
Json::Value config;
//�������õ��ļ�
void save_config()
{
std::string out = config.toStyledString();
std::ofstream ofs;
ofs.open(config_file_name,std::ofstream::out);
if(ofs.is_open())
    {
    ofs << out;
    ofs.close();
    }
}

//���������ļ�
std::string Config_in;
config_data_t config_data;
void load_config()
{
std::ifstream ifs;
ifs.open(config_file_name,std::ifstream::in|std::ifstream::binary);
if(ifs.is_open())
    {

    //��ȡ�ļ�����
    ifs.seekg (0, ifs.end);
    int file_length = ifs.tellg();
    ifs.seekg (0, ifs.beg);

    //��ȡ���ݵ�Config_in;
    char * buf=(char *)malloc(file_length+3);
    ifs.read(buf,file_length);
    Config_in=buf;
    free(buf);

    //����json
    config.clear();
    Json::Reader reader;
    reader.parse(Config_in,config);

    ifs.close();
    }

//�������õ��ṹ��
if(!config["Query_String_Prefix"].isNull())
        config_data.Query_String_Prefix=config["Query_String_Prefix"].asString();
else
    config_data.Query_String_Prefix="";

if(!config["modbus_bind_address"].isNull())
    config_data.modbus_bind_address=config["modbus_bind_address"].asString();
else
    config_data.modbus_bind_address="127.0.0.1";

if(!config["modbus_bind_port"].isNull())
    config_data.modbus_bind_port=config["modbus_bind_port"].asInt();
else
    config_data.modbus_bind_port=1502;
}
