#include "stdio.h"
#include "KeyBoardHook.H"
int KB(DWORD vk)
{
    printf("vk_code %lu\n",vk);
    return 0;//���ط��㽫��ֹ���ӵĴ���
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
