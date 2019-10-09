#include "c_sqlite3.h"

c_sqlite3::c_sqlite3(std::string path)
{
    //ctor
        sql_db=NULL;
        CSqlite_Open(path.c_str());
}

int c_sqlite3::CSqlite_Open(std::string path)
{
    if(NULL != sql_db)
        CSqlite_Close();
    return sqlite3_open(path.c_str(),&sql_db);

}

void c_sqlite3::CSqlite_Close()
{
    if (NULL != sql_db)
		sqlite3_close(sql_db);
    sql_db=NULL;
}

int c_sqlite3::CSqlite_Exec(std::string sql,char ** errmsg)
{
    if(sql_db == NULL)
        return SQLITE_ERROR;
    Exec_Result.name.clear();
    Exec_Result.value.clear();
    return sqlite3_exec(sql_db,sql.c_str(),CSqlite_Callback,this,errmsg);
}

int c_sqlite3::CSqlite_Callback(void *p,int count,char **value,char **name)
{
    c_sqlite3 * class_ptr=(c_sqlite3 *)p;
    if(class_ptr->Exec_Result.name.size() != (size_t)count)
    {
        int i =0;
        for(i=0;i<count;i++)
        {
            class_ptr->Exec_Result.name.push_back(name[i]);
        }
    }
    std::vector<std::string> temp;
    {
     int i =0;
        for(i=0;i<count;i++)
        {
            temp.push_back(value[i]);
        }
    }

    class_ptr->Exec_Result.value.push_back(temp);

    return SQLITE_OK;
}
c_sqlite3::~c_sqlite3()
{
    //dtor
    CSqlite_Close();
}
