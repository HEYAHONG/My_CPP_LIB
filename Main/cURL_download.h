#ifndef __cURL_Download__
#define __cURL_Download__
#include "iostream"
#include "curl/curl.h"
using namespace std;

//cURL���غ���������url���ص����ݷ���content��,�ɹ�����true��ʧ�ܷ���false��
bool cURL_Download(string url,string &content);

//����POST������POST���ݺ󷵻ص����ݷ���content��
bool cURL_Post_And_Download(string url,string &content,string post_data,string post_header);

#endif // __cURL_Download__
