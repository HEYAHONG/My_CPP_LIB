#include "stdio.h"
#include "KeyBoardHook.H"
int KB(DWORD vk)
{
    printf("vk_code %lu\n",vk);
    return 0;//返回非零将阻止钩子的传递
}
int main()
{
 install_KB_hook();
 Set_KB_Fun(KB);
 while(1)
 {
     getchar();
 }
}
