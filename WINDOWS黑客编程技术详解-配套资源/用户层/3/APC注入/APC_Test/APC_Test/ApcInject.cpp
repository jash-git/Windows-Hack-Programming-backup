#include "stdafx.h"
#include "ApcInject.h"


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText);
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
}


// 根据进程名称获取PID
DWORD GetProcessIdByProcessName(char *pszProcessName)
{
	DWORD dwProcessId = 0;
	PROCESSENTRY32 pe32 = { 0 };
	HANDLE hSnapshot = NULL;
	BOOL bRet = FALSE;
	::RtlZeroMemory(&pe32, sizeof(pe32));
	pe32.dwSize = sizeof(pe32);

	// 获取进程快照
	hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (NULL == hSnapshot)
	{
		ShowError("CreateToolhelp32Snapshot");
		return dwProcessId;
	}

	// 获取第一条进程快照信息
	bRet = ::Process32First(hSnapshot, &pe32);
	while (bRet)
	{
		// 获取快照信息
		if (0 == ::lstrcmpi(pe32.szExeFile, pszProcessName))
		{
			dwProcessId = pe32.th32ProcessID;
			break;
		}

		// 遍历下一个进程快照信息
		bRet = ::Process32Next(hSnapshot, &pe32);
	}

	return dwProcessId;
}


// 根据PID获取所有的相应线程ID
BOOL GetAllThreadIdByProcessId(DWORD dwProcessId, DWORD **ppThreadId, DWORD *pdwThreadIdLength)
{
	DWORD *pThreadId = NULL;
	DWORD dwThreadIdLength = 0;
	DWORD dwBufferLength = 1000;
	THREADENTRY32 te32 = { 0 };
	HANDLE hSnapshot = NULL;
	BOOL bRet = TRUE;

	do
	{
		// 申请内存
		pThreadId = new DWORD[dwBufferLength];
		if (NULL == pThreadId)
		{
			ShowError("new");
			bRet = FALSE;
			break;
		}
		::RtlZeroMemory(pThreadId, (dwBufferLength * sizeof(DWORD)));

		// 获取线程快照
		::RtlZeroMemory(&te32, sizeof(te32));
		te32.dwSize = sizeof(te32);
		hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (NULL == hSnapshot)
		{
			ShowError("CreateToolhelp32Snapshot");
			bRet = FALSE;
			break;
		}

		// 获取第一条线程快照信息
		bRet = ::Thread32First(hSnapshot, &te32);
		while (bRet)
		{
			// 获取进程对应的线程ID
			if (te32.th32OwnerProcessID == dwProcessId)
			{
				pThreadId[dwThreadIdLength] = te32.th32ThreadID;
				dwThreadIdLength++;
			}

			// 遍历下一个线程快照信息
			bRet = ::Thread32Next(hSnapshot, &te32);
		}

		// 返回
		*ppThreadId = pThreadId;
		*pdwThreadIdLength = dwThreadIdLength;
		bRet = TRUE;

	} while (FALSE);

	if (FALSE == bRet)
	{
		if (pThreadId)
		{
			delete[]pThreadId;
			pThreadId = NULL;
		}
	}

	return bRet;
}


// APC注入
BOOL ApcInjectDll(char *pszProcessName, char *pszDllName)
{
	BOOL bRet = FALSE;
	DWORD dwProcessId = 0;
	DWORD *pThreadId = NULL;
	DWORD dwThreadIdLength = 0;
	HANDLE hProcess = NULL, hThread = NULL;
	PVOID pBaseAddress = NULL;
	PVOID pLoadLibraryAFunc = NULL;
	SIZE_T dwRet = 0, dwDllPathLen = 1 + ::lstrlen(pszDllName);
	DWORD i = 0;

	do
	{
		// 根据进程名称获取PID
		dwProcessId = GetProcessIdByProcessName(pszProcessName);
		if (0 >= dwProcessId)
		{
			bRet = FALSE;
			break;
		}

		// 根据PID获取所有的相应线程ID
		bRet = GetAllThreadIdByProcessId(dwProcessId, &pThreadId, &dwThreadIdLength);
		if (FALSE == bRet)
		{
			bRet = FALSE;
			break;
		}

		// 打开注入进程
		hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId);
		if (NULL == hProcess)
		{
			ShowError("OpenProcess");
			bRet = FALSE;
			break;
		}

		// 在注入进程空间申请内存
		pBaseAddress = ::VirtualAllocEx(hProcess, NULL, dwDllPathLen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (NULL == pBaseAddress)
		{
			ShowError("VirtualAllocEx");
			bRet = FALSE;
			break;
		}
		// 向申请的空间中写入DLL路径数据 
		::WriteProcessMemory(hProcess, pBaseAddress, pszDllName, dwDllPathLen, &dwRet);
		if (dwRet != dwDllPathLen)
		{
			ShowError("WriteProcessMemory");
			bRet = FALSE;
			break;
		}

		// 获取 LoadLibrary 地址
		pLoadLibraryAFunc = ::GetProcAddress(::GetModuleHandle("kernel32.dll"), "LoadLibraryA");
		if (NULL == pLoadLibraryAFunc)
		{
			ShowError("GetProcessAddress");
			bRet = FALSE;
			break;
		}

		// 遍历线程, 插入APC
		for (i = 0; i < dwThreadIdLength; i++)
		{
			// 打开线程
			hThread = ::OpenThread(THREAD_ALL_ACCESS, FALSE, pThreadId[i]);
			if (hThread)
			{
				// 插入APC
				::QueueUserAPC((PAPCFUNC)pLoadLibraryAFunc, hThread, (ULONG_PTR)pBaseAddress);
				// 关闭线程句柄
				::CloseHandle(hThread);
				hThread = NULL;
			}
		}

		bRet = TRUE;

	} while (FALSE);

	// 释放内存
	if (hProcess)
	{
		::CloseHandle(hProcess);
		hProcess = NULL;
	}
	if (pThreadId)
	{
		delete[]pThreadId;
		pThreadId = NULL;
	}

	return bRet;
}