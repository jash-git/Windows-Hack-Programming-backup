// GlobalHook_Test.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


extern HMODULE g_hDllModule;
// 共享内存
#pragma data_seg("mydata")
    HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:mydata,RWS")


// 钩子回调函数
LRESULT GetMsgProc(
	int code,
	WPARAM wParam,
	LPARAM lParam)
{
	return ::CallNextHookEx(g_hHook, code, wParam, lParam);
}


// 设置全局钩子
BOOL SetGlobalHook()
{
	g_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hDllModule, 0);
	if (NULL == g_hHook)
	{
		return FALSE;
	}
	return TRUE;
}


// 卸载钩子
BOOL UnsetGlobalHook()
{
	if (g_hHook)
	{
		::UnhookWindowsHookEx(g_hHook);
	}
	return TRUE;
}