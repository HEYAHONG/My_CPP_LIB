#ifndef MYSQL_CLIENT_H_INCLUDED
#define MYSQL_CLIENT_H_INCLUDED
#include "stdint.h"
#include "stdio.h"
#include "iostream"
#include "vector"
#include "cstring"
using namespace std;
#include "mysql/mysql.h"

typedef struct
{
    string address;
    string user;
    string password;
    string dbname;
    int      port;
} mysql_config_t;

//存储mysql连接信息
extern mysql_config_t mysql_config;

//mysql连接
extern MYSQL * mysql;

//连接mysql
void mysql_client_connect();

void mysql_client_disconnect();

class mysql_value
{
public:
    class _ArryIndex
        {
        public:
            operator int();
            _ArryIndex();
            _ArryIndex(const string &);
            _ArryIndex(string &);
            _ArryIndex(const char *);
            _ArryIndex(char *);
            ~_ArryIndex();
            string ArryIndex_data;
        };
    vector<string> operator[](mysql_value::_ArryIndex);
    void   clear();
    int    get_index_length()
        {
        return index_length;
        };
    int    get_row_length()
        {
        return row_length;
        }
    vector<string> get_last_result()
        {
        return last_result;
        }
    bool IsEmpty()
        {
            return index_string_data.empty();
        }
    bool IsRowEmpty()
        {
            return row_string_data.empty();
        }
    bool Data_Init(MYSQL_RES * RES);
    bool Mysql_Query(MYSQL *connection,string query);
    vector<string>          last_result;
protected:
    vector<string>          index_string_data;
    int                     index_length;
    vector<vector<string>>  row_string_data;
    int                     row_length;
};
#endif // MYSQL_CLIENT_H_INCLUDED
