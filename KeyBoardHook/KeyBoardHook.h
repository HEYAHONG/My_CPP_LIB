#ifndef KEYBOARDHOOK_H_INCLUDED
#define KEYBOARDHOOK_H_INCLUDED
#include "windows.h"
#include "stdio.h"

typedef int (*KB_fun_t)(DWORD);
extern KB_fun_t KB_fun;
inline void Set_KB_Fun(KB_fun_t fun)
{
    KB_fun=fun;
}
void install_KB_hook();

#endif // KEYBOARDHOOK_H_INCLUDED
