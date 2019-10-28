#include "mysql_client.h"
mysql_config_t mysql_config =
{
   "127.0.0.1",
   "root",
   "toor",
   "",
   3306
};
MYSQL * mysql=NULL;

void mysql_client_connect()
{

if(mysql==NULL)
    {
    if((mysql=mysql_init(mysql))==NULL)
        fprintf(stderr,"Cannot initialize MySQL");
    }
if(mysql_real_connect(mysql,mysql_config.address.c_str(),mysql_config.user.c_str(),mysql_config.password.c_str(),mysql_config.dbname.c_str(),mysql_config.port,NULL,0)==NULL)
    fprintf(stderr,"%d:%s \n",mysql_errno(mysql),mysql_error(mysql));

}

void mysql_client_disconnect()
{
mysql_close(mysql);
}


//≤‚ ‘mysql_value¿‡
vector<string> mysql_value::operator[](mysql_value::_ArryIndex index)
{
int i=0;
//printf("%s\n",index.ArryIndex_data.c_str());
while(strcmp(index_string_data[i].c_str(),index.ArryIndex_data.c_str()) && i < index_length)
    {

    //printf("%s:%s",index_string_data[i].c_str(),index.ArryIndex_data.c_str());
    i++;
    }
if(i<index_length)
    last_result=row_string_data[i];
else
    last_result.clear();

return last_result;
}
void mysql_value::clear()
{
last_result.clear();
index_string_data.clear();
row_string_data.clear();
index_length=0;
row_length=0;
}
bool mysql_value::Data_Init(MYSQL_RES * RES)
{
if(RES == NULL) return false;
this->clear();
index_length = mysql_num_fields(RES);
row_length   = mysql_num_rows(RES);

MYSQL_FIELD * mysqlField = NULL;
MYSQL_ROW mysqlRow;

while ((mysqlField = mysql_fetch_field(RES)) !=NULL)
    index_string_data.push_back(mysqlField->name);

row_string_data.resize(index_length);

	while ((mysqlRow = mysql_fetch_row(RES)) !=NULL)
	{
	    int i=0;
		for (i = 0; i < index_length; i++)
		{
			row_string_data[i].push_back(mysqlRow[i]);
		}
	}

return true;
}

bool mysql_value::Mysql_Query(MYSQL * connection,string query)
{
if (mysql_query(connection, query.c_str()))
    return false;
MYSQL_RES * mysqlResult = NULL;
mysqlResult = mysql_store_result(connection);
if(mysqlResult != NULL)
    {
    this->Data_Init(mysqlResult);
    mysql_free_result(mysqlResult);
    return true;
    }
else
    return false;
}

mysql_value::_ArryIndex::operator int()
{
return 0;
}
mysql_value::_ArryIndex::_ArryIndex()
{
ArryIndex_data="";
}
mysql_value::_ArryIndex::_ArryIndex(string & data)
{
ArryIndex_data=data;
}
mysql_value::_ArryIndex::_ArryIndex(const string & data)
{
ArryIndex_data=data;
}
mysql_value::_ArryIndex::_ArryIndex(char * data)
{
ArryIndex_data=data;
}
mysql_value::_ArryIndex::_ArryIndex(const char * data)
{
ArryIndex_data=data;
}
mysql_value::_ArryIndex::~_ArryIndex()
{
ArryIndex_data.clear();
}

