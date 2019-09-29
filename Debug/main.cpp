#include "debug.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc,char *argv[])
{
    printf("Main Started!\n");
    C_Debug temp;
    temp.setDebug(C_Debug::Debug_Info_e );
    temp.Debug_Error("ssssssErr!\n");
    temp.Debug_Info("ssssssInfo!\n");
    temp.setDebug_Error(true);
    temp.setDebug_Info(true);
    temp.Debug_Error("sssssdddd\n");
    temp.Debug_Info("ssdssdssds\n");
    return 0;
}
