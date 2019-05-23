// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <TlHelp32.h>


int _tmain(int argc, _TCHAR* argv[])
{
	// 加载DLL并获取句柄
	HMODULE hDll = ::LoadLibrary("HideProcess_ZwQuerySystemInformation_Test.dll");
	if (NULL == hDll)
	{
		printf("%s error[%d]\n", "LoadLibrary", ::GetLastError());
	}
	printf("Load Library OK.\n");

	// 设置全局钩子
	typedef HHOOK(*typedef_SetHook)();
	typedef_SetHook SetHook = (typedef_SetHook)::GetProcAddress(hDll, "SetHook");
	if (NULL == SetHook)
	{
		printf("GetProcAddress Error[%d]\n", ::GetLastError());
	}
	HHOOK hHook = SetHook();
	if (NULL == hHook)
	{
		printf("%s error[%d]\n", "SetWindowsHookEx", ::GetLastError());
	}
	printf("Set Windows Hook OK.\n");
	system("pause");
	// 卸载全局钩子
	typedef BOOL(*typedef_UnsetHook)(HHOOK);
	typedef_UnsetHook UnsetHook = (typedef_UnsetHook)::GetProcAddress(hDll, "UnsetHook");
	if (NULL == UnsetHook)
	{
		printf("GetProcAddress Error[%d]\n", ::GetLastError());
	}
	if (FALSE == UnsetHook(hHook))
	{
		printf("%s error[%d]\n", "UnhookWindowsHookE", ::GetLastError());
	}
	printf("Unhook Windows Hook OK.\n");
	// 卸载DLL
	::FreeLibrary(hDll);

	system("pause");
	return 0;
}

