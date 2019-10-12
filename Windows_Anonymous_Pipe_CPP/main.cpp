#include "stdio.h"
#include "wapipe.h"

int main(int argc,char * argv[])
{
    WAPipe Temp;
    if(Temp.Start_New_Process("cmd.exe")!=NULL)
    {
        static char buff[4096];
        size_t  i=0,read_num;
        Temp.WritePipe("dir\r\n",sizeof("dir\r\n"));
        while((read_num=Temp.ReadPipe(buff,sizeof(buff)))>0)
        {

        for(i=0;i<read_num;i++)
        {
            putchar(buff[i]);
        }
        //printf("%ld",GetLastError());
        }
         // getchar();
    }
}
