#ifndef __C_SQLITE3_H__
#define __C_SQLITE3_H__
#include "iostream"
#include "vector"
#include "string.h"
#include "sqlite3.h"

class c_sqlite3
{
    public:
        c_sqlite3(std::string path="sqlite3.db");
        virtual ~c_sqlite3();
        virtual int   CSqlite_Open(std::string path);
        virtual void  CSqlite_Close();
        virtual int   CSqlite_Exec(std::string sql,char **errmsg);
        struct Exec_Reslut_t
        {
            std::vector<std::string> name;
            std::vector<std::vector<std::string>> value;
        } Exec_Result;
        virtual Exec_Reslut_t * Get_Exec_Result()
        {
            return &Exec_Result;
        }

    protected:
        static int CSqlite_Callback(void *p,int count,char **value,char **name);
        sqlite3  *sql_db;
    private:

};

#endif // __C_SQLITE3_H__
