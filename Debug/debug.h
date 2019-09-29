#ifndef __C_DEBUG_H__
#define __C_DEBUG_H__
#include "stdio.h"
#include "stdint.h"

class C_Debug
{
    public:
    typedef int (*printf_t)(const char *,...);
    enum Debug_type
    {
    Debug_No    =0x00,
    Debug_Info_e=0x01<<0,
    Debug_Error_e=0x01<<1
    };
    static  int printf_NULL(const char *,...)
        {
            ;//É¶Ò²²»×ö
            return 0;
        }
    printf_t Debug_Info;
    printf_t Debug_Error;
    virtual int setDebug(int debug_type);
    virtual int setDebug_Info(bool Is_Debug_Info);
    virtual int setDebug_Error(bool Is_Debug_Error);
        C_Debug();
        virtual ~C_Debug();

    protected:


    private:
};

#endif // __C_DEBUG_H__
