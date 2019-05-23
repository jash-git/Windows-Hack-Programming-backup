#include "stdafx.h"
#include "InjectDll.h"


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = {0};
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}


// 使用 CreateRemoteThread 实现远线程注入
BOOL CreateRemoteThreadInjectDll(DWORD dwProcessId, char *pszDllFileName)
{
	HANDLE hProcess = NULL;
	SIZE_T dwSize = 0;
	LPVOID pDllAddr = NULL;
	FARPROC pFuncProcAddr = NULL;

	// 打开注入进程，获取进程句柄
	hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
	if (NULL == hProcess)
	{
		ShowError("OpenProcess");
		return FALSE;
	}
	// 在注入进程中申请内存
	dwSize = 1 + ::lstrlen(pszDllFileName);
	pDllAddr = ::VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == pDllAddr)
	{
		ShowError("VirtualAllocEx");
		return FALSE;
	}
	// 向申请的内存中写入数据
	if (FALSE == ::WriteProcessMemory(hProcess, pDllAddr, pszDllFileName, dwSize, NULL))
	{
		ShowError("WriteProcessMemory");
		return FALSE;
	}
	// 获取LoadLibraryA函数地址
	pFuncProcAddr = ::GetProcAddress(::GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if (NULL == pFuncProcAddr)
	{
		ShowError("GetProcAddress_LoadLibraryA");
		return FALSE;
	}
	// 使用 CreateRemoteThread 创建远线程, 实现 DLL 注入
	HANDLE hRemoteThread = ::CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFuncProcAddr, pDllAddr, 0, NULL);
	if (NULL == hRemoteThread)
	{
		ShowError("CreateRemoteThread");
		return FALSE;
	}
	// 关闭句柄
	::CloseHandle(hProcess);

	return TRUE;
}