
#include "KeyBoardHook.h"
HHOOK g_hHook=NULL;
KB_fun_t KB_fun=NULL;
LRESULT CALLBACK KeyBoardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{

    //printf("Message %d\n",nCode);
    if (nCode >= HC_ACTION && wParam==WM_KEYDOWN) //有键按下
    {
    	KBDLLHOOKSTRUCT * msg=((KBDLLHOOKSTRUCT*)lParam);
    	if(KB_fun!=NULL)
            if(KB_fun(msg->vkCode))
            {
            return 0;
            }
    }

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);  //将消息还给钩子链，不要影响别人
}

DWORD WINAPI MessageThread(LPVOID p)
{
    g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyBoardHookProc, GetModuleHandle("USER32.dll"), 0);
    if(g_hHook == NULL)
    {
       return 0;
    }
    MSG msg;
	while (1)
	{
		if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
			//writefile("111");
		}
		else
			//writefile("~~");
			Sleep(0);    //避免CPU全负载运行
	}
}

void install_KB_hook()
{
    static int i=0;
    if(i)
        return;
    CreateThread(NULL, 0, MessageThread, 0, 0, NULL);
    i++;
}

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
	    if(g_hHook != NULL)
            {
                UnhookWindowsHookEx(g_hHook);
            }
		break;
	}
	return TRUE;
}

