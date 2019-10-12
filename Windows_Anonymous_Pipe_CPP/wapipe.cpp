#include "wapipe.h"

WAPipe::WAPipe()
{
    //ctor
   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
   saAttr.bInheritHandle = TRUE;
   saAttr.lpSecurityDescriptor = NULL;
   LastHandle=NULL;

}
WAPipe::WA_Handle * WAPipe::WA_Handle_New()
{
WA_Handle * handle = new WA_Handle;

// Create a pipe for the child process's STDOUT.

if ( ! CreatePipe(&handle->hChildStd_OUT_Rd, &handle->hChildStd_OUT_Wr, &saAttr, 0) )
      {
          WA_Handle_Delete(handle);
          return NULL;
      }

// Ensure the read handle to the pipe for STDOUT is not inherited.

if ( ! SetHandleInformation(handle->hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) )
      {
          WA_Handle_Delete(handle);
          return NULL;
      }

// Create a pipe for the child process's STDIN.

if (! CreatePipe(&handle->hChildStd_IN_Rd, &handle->hChildStd_IN_Wr, &saAttr, 0))
      {
          WA_Handle_Delete(handle);
          return NULL;
      }

// Ensure the write handle to the pipe for STDIN is not inherited.

if ( ! SetHandleInformation(handle->hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) )
      {
          WA_Handle_Delete(handle);
          return NULL;
      }

    return handle;

}
void WAPipe::WA_Handle_Delete(WA_Handle * handle)
{
    if(handle != NULL)
        delete handle;
}
WAPipe::WA_Handle *  WAPipe::Start_New_Process(std::string cmd)
{
    WA_Handle *handle=WA_Handle_New();
    if(handle == NULL)
        return NULL;

    STARTUPINFO siStartInfo;
    ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = handle->hChildStd_OUT_Wr;
    siStartInfo.hStdOutput = handle->hChildStd_OUT_Wr;
    siStartInfo.hStdInput = handle->hChildStd_IN_Rd;
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
    handle->Is_SCCUESS = CreateProcess(NULL,
      (LPSTR)cmd.c_str(),     // command line
      NULL,          // process security attributes
      NULL,          // primary thread security attributes
      TRUE,          // handles are inherited
      0,             // creation flags
      NULL,          // use parent's environment
      NULL,          // use parent's current directory
      &siStartInfo,  // STARTUPINFO pointer
      &handle->piProcInfo);  // receives PROCESS_INFORMATION
    if(!handle->Is_SCCUESS)
    {
        WA_Handle_Delete(handle);
        return NULL;
    }
    else
    {
        LastHandle=handle;
        return handle;

    }

}

DWORD WAPipe::WritePipe(const void * buff,size_t len,WA_Handle *handle)
{
    DWORD  dwWritten=0;
    if(handle->Is_SCCUESS)
    {
            if(!WriteFile(handle->hChildStd_IN_Wr, (const char *)buff, len, &dwWritten, NULL))
            {
              dwWritten=0;
                #ifdef DEBUG
                printf("Error:%ld",GetLastError())
                #endif // DEBUG
                ;
            }

    }
    return dwWritten;
}
DWORD WAPipe::WritePipe(const void * buff,size_t len)
{
    if(LastHandle != NULL)
    {
        return WritePipe(buff,len,LastHandle);
    }
    else
        return 0;
}
DWORD  WAPipe::ReadPipe(void * buff,size_t len,WA_Handle *handle)
{
    DWORD dwRead=0;
    if(handle->Is_SCCUESS)
    {
        if(!ReadFile(handle->hChildStd_OUT_Rd,(char *)buff,len,&dwRead,NULL))
        {
            dwRead=0;
            #ifdef DEBUG
            printf("Error:%ld",GetLastError())
            #endif // DEBUG
            ;
        }

    }
    return dwRead;
}
DWORD WAPipe::ReadPipe(void * buff,size_t len)
{
    if(LastHandle != NULL)
    {
        return ReadPipe(buff,len,LastHandle);
    }
    else
        return 0;
}
WAPipe::~WAPipe()
{
    //dtor
    if(LastHandle != NULL)
        TerminateProcess(LastHandle->piProcInfo.hProcess,0);
    WA_Handle_Delete(LastHandle);
}
