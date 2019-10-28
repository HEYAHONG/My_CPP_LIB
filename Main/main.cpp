#include "iostream"
#include "curl/curl.h"
#include "json/json.h"
#include "pthread.h"

using namespace std;

#include "cURL_download.h"
#include "json_config.h"
#include "modbus_server.h"
#include "mysql_client.h"

//隐藏窗口
#ifdef WIN32
#include "windows.h"

void hide_window()
{
HWND hwnd;

if(hwnd=::FindWindow("ConsoleWindowClass",NULL)) //找到控制台句柄
{
::ShowWindow(hwnd,SW_HIDE); //隐藏控制台窗口
}

}
void hide_taskbar()
{
HWND hwnd;

if(hwnd=::FindWindow("ConsoleWindowClass",NULL)) //找到控制台句柄
{
::SetWindowLong ( hwnd , GWL_EXSTYLE , WS_EX_TOOLWINDOW );//测试无效
}
}

int MessageBox(LPCTSTR lpText,LPCTSTR lpCaption,UINT    uType)
{

HWND hwnd;

if(hwnd=::FindWindow("ConsoleWindowClass",NULL)) //找到控制台句柄
{
return ::MessageBox(
hwnd,
lpText,
lpCaption,
uType
);
}
return 0;
}
#endif // win32

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

int main(int argc,char ** argv)
{
//config["Query_String_Prefix"]=Json::Value("http://47.106.72.188:8087/node/diapi/node3rd/get_ip_port?");
//save_config();
#ifdef WIN32
hide_window();//隐藏窗口
//hide_taskbar();
MessageBox("Test","This is a Test\n",MB_OK);
#endif // WIN32
load_config();

printf("%s\n",config_data.Query_String_Prefix.c_str());



string temp;
if(cURL_Post_And_Download("http://127.0.0.1/modbus_api/post.php",temp,"hhhddededcrfcfgvtrgtyghythgyhgtgrferdfefrfrf","Content-Type:application/json;charset=UTF-8"))
printf("%s\n",temp.c_str());
temp.clear();

if(cURL_Download("http://47.106.72.188:8087/node/diapi/node3rd/get_ip_port?mac=423432432",temp))
printf("%s\n",temp.c_str());




Json::Reader reader;
Json::Value root;
reader.parse(temp.c_str(),root);
printf("\nIP:%s\nPORT:%s\nID:%d\n",root["IP"].asString().c_str(),root["PORT"].asString().c_str(),root["ID"].asInt());

mysql_client_connect();
printf("Mysql stat:\n%s\n",mysql_stat(mysql));
mysql_value test;
test.Mysql_Query(mysql,"select * from mqtt_server.server_table;");
printf("Query Row Length:%d\n",test.get_row_length());
for(int i=0;i<test.get_row_length();i++)
printf("Server %d IP is:%s\n",i,test["IP"].empty()?"No Data":test["IP"][i].c_str());

mysql_client_disconnect();

modbus_server_callback_register(modbus_print_message);
//modbus_server_callback_register(modbus_process_03_code);
modbus_server_start(config_data.modbus_bind_address.c_str(),config_data.modbus_bind_port);
while(1)
{
getchar();
modbus_server_stop();
exit(0);
}
return 0;
}
