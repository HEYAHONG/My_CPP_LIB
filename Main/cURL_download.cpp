#include "cURL_download.h"
static size_t downloadCallback(void *buffer, size_t sz, size_t nmemb, void *writer)
{
	string* psResponse = (string*) writer;
	size_t size = sz * nmemb;
	psResponse->append((char*) buffer, size);

	return sz * nmemb;
}
bool cURL_Download(string url,string &content)
{
CURL *curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2);
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadCallback);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
CURLcode res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
if(res==CURLE_OK)
    return true;
else
    return false;
}


bool cURL_Post_And_Download(string url,string &content,string post_data,string post_header)
{
if(post_data.empty())
    {
    return cURL_Download(url,content);
    }
CURL *curl;
CURLcode res;
//HTTP报文头
struct curl_slist* headers = NULL;
curl = curl_easy_init();
curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
headers=curl_slist_append(headers, post_header.c_str());
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//curl_easy_setopt(curl,  CURLOPT_CUSTOMREQUEST, "POST");
curl_easy_setopt(curl, CURLOPT_POST, 1);//设置为非0表示本次操作为POST
curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data.c_str());//以Unicode编码上传
curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_data.size());
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, downloadCallback);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
res = curl_easy_perform(curl);
curl_easy_cleanup(curl);
curl_slist_free_all(headers); /* free the list again */
if(res==CURLE_OK)
    return true;
else
    return false;

}
