#ifndef _INJECT_DLL_H_
#define _INJECT_DLL_H_


#include <Windows.h>


// 使用 CreateRemoteThread 实现远线程注入
BOOL CreateRemoteThreadInjectDll(DWORD dwProcessId, char *pszDllFileName);


#endif