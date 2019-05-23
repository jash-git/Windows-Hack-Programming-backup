#ifndef _APC_INJECT_H_
#define _APC_INJECT_H_


#include <Windows.h>
#include <TlHelp32.h>


// 根据进程名称获取PID
DWORD GetProcessIdByProcessName(char *pszProcessName);

// 根据PID获取所有的相应线程ID
BOOL GetAllThreadIdByProcessId(DWORD dwProcessId, DWORD **ppThreadId, DWORD *dwThreadIdLength);

// APC注入
BOOL ApcInjectDll(char *pszProcessName, char *pszDllName);


#endif