#include "c_sqlite3.h"
#include "stdio.h"
int main(int argc,char *argv[])
{
    c_sqlite3 temp;
    char * errmsg=NULL;

    temp.CSqlite_Exec("SELECT *  FROM Data",&errmsg);

    printf("Error Message Is %s\n",errmsg);

    size_t i=0,j=0;
    printf("Name Is:\n");
    for(i=0;i<temp.Exec_Result.name.size();i++)
    {
        printf((temp.Exec_Result.name[i]+"\t").c_str());
    }
    printf("\nValue Is:\n");

    for(i=0;i<temp.Exec_Result.value.size();i++)
    {
        for(j=0;j<temp.Exec_Result.value[i].size();j++)
        {
            printf((temp.Exec_Result.value[i][j]+"\t").c_str());
        }
        printf("\n");
    }

    while(1)
    {
        getchar();
        break;
    }
    return 0;
}
