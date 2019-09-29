#include "debug.h"

int C_Debug::setDebug(int debug_type)
{
    if(debug_type&Debug_Error_e)
        Debug_Error=printf;
    else
        Debug_Error=printf_NULL;

    if(debug_type&Debug_Info_e)
        Debug_Info=printf;
    else
        Debug_Info=printf_NULL;

    return debug_type;
}

int C_Debug::setDebug_Info(bool Is_Debug_Info)
{
    if(Is_Debug_Info)
        {
            Debug_Info=printf;
            return Debug_Info_e;
        }
    else
        {
            Debug_Info=printf_NULL;
            return 0;
        }
}
int C_Debug::setDebug_Error(bool Is_Debug_Error)
{
    if(Is_Debug_Error)
        {
            Debug_Error=printf;
            return Debug_Error_e;
        }
    else
        {
            Debug_Error=printf_NULL;
            return 0;
        }
}
C_Debug::C_Debug()
{
    //ctor
    setDebug(Debug_No);
}

C_Debug::~C_Debug()
{
    //dtor
}
