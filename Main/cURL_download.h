#ifndef __cURL_Download__
#define __cURL_Download__
#include "iostream"
#include "curl/curl.h"
using namespace std;

//cURL下载函数，将从url下载的内容放入content中,成功返回true，失败返回false。
bool cURL_Download(string url,string &content);

//进行POST并下载POST数据后返回的内容放入content。
bool cURL_Post_And_Download(string url,string &content,string post_data,string post_header);

#endif // __cURL_Download__
