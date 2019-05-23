#ifndef _INJECT_DLL_H_
#define _INJECT_DLL_H_


#include <Windows.h>


// 使用 ZwCreateThreadEx 实现远线程注入
BOOL ZwCreateThreadExInjectDll(DWORD dwProcessId, char *pszDllFileName);


#endif