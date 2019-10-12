#ifndef __WAPIPE_H__
#define __WAPIPE_H__
#include "windows.h"
#include "iostream"
//#define DEBUG

class WAPipe
{
    public:
        class WA_Handle
        {
        public:

            HANDLE hChildStd_IN_Rd ;
            HANDLE hChildStd_IN_Wr ;
            HANDLE hChildStd_OUT_Rd ;
            HANDLE hChildStd_OUT_Wr ;
            PROCESS_INFORMATION piProcInfo;
            BOOL    Is_SCCUESS;
            WA_Handle()
            {
                hChildStd_IN_Rd=NULL;
                hChildStd_IN_Wr=NULL;
                hChildStd_OUT_Rd=NULL;
                hChildStd_OUT_Wr=NULL;
                Is_SCCUESS=FALSE;
                ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );
            }
            ~WA_Handle()
            {
                if(hChildStd_IN_Rd!=NULL)
                    CloseHandle(hChildStd_IN_Rd);
                if(hChildStd_IN_Wr!=NULL)
                    CloseHandle(hChildStd_IN_Rd);
                if(hChildStd_OUT_Rd!=NULL)
                    CloseHandle(hChildStd_IN_Rd);
                if(hChildStd_OUT_Wr!=NULL)
                    CloseHandle(hChildStd_IN_Rd);
                if(Is_SCCUESS)
                {
                    CloseHandle(piProcInfo.hProcess);
                    CloseHandle(piProcInfo.hThread);
                }

            }

        };
        WAPipe();
        virtual ~WAPipe();
        WA_Handle * WA_Handle_New();
        void        WA_Handle_Delete(WA_Handle * handle);
        WA_Handle * Start_New_Process(std::string cmd);
        DWORD       WritePipe(const void * buff,size_t len,WA_Handle *handle);
        DWORD       WritePipe(const void *buff,size_t len);
        DWORD       ReadPipe(void * buff,size_t len,WA_Handle *handle);
        DWORD       ReadPipe(void * buff,size_t len);


    protected:
        SECURITY_ATTRIBUTES saAttr;
        WA_Handle * LastHandle;

    private:
};

#endif // __WAPIPE_H__
