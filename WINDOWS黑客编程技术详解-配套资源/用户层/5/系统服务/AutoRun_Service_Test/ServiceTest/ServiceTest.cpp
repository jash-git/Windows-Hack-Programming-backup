// ServiceTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


// 服务入口函数以及处理回调函数
void __stdcall ServiceMain(DWORD dwArgc, char *lpszArgv);
void __stdcall ServiceCtrlHandle(DWORD dwOperateCode);
BOOL TellSCM(DWORD dwState, DWORD dwExitCode, DWORD dwProgress);
void DoTask();

// 全局变量
char g_szServiceName[MAX_PATH] = "ServiceTest.exe";    // 服务名称 
SERVICE_STATUS_HANDLE g_ServiceStatusHandle = { 0 };


int _tmain(int argc, _TCHAR* argv[])
{
	// 注册服务入口函数
	SERVICE_TABLE_ENTRY stDispatchTable[] = { { g_szServiceName, (LPSERVICE_MAIN_FUNCTION)ServiceMain }, { NULL, NULL } };
	::StartServiceCtrlDispatcher(stDispatchTable);

	return 0;
}


void __stdcall ServiceMain(DWORD dwArgc, char *lpszArgv)
{
	g_ServiceStatusHandle = ::RegisterServiceCtrlHandler(g_szServiceName, ServiceCtrlHandle);

	TellSCM(SERVICE_START_PENDING, 0, 1);
	TellSCM(SERVICE_RUNNING, 0, 0);

	// 自己程序实现部分代码放在这里
	// !!注意!! 此处一定要为死循环, 否则在关机再开机的情况(不是点击重启), 不能创建用户进程
	while (TRUE)
	{
		Sleep(5000);
		DoTask();
	}
}


void __stdcall ServiceCtrlHandle(DWORD dwOperateCode)
{
	switch (dwOperateCode)
	{
	case SERVICE_CONTROL_PAUSE:
	{
		// 暂停
		TellSCM(SERVICE_PAUSE_PENDING, 0, 1);
		TellSCM(SERVICE_PAUSED, 0, 0);
		break;
	}
	case SERVICE_CONTROL_CONTINUE:
	{
		// 继续
		TellSCM(SERVICE_CONTINUE_PENDING, 0, 1);
		TellSCM(SERVICE_RUNNING, 0, 0);
		break;
	}
	case SERVICE_CONTROL_STOP:
	{
		// 停止
		TellSCM(SERVICE_STOP_PENDING, 0, 1);
		TellSCM(SERVICE_STOPPED, 0, 0);
		break;
	}
	case SERVICE_CONTROL_INTERROGATE:
	{
		// 询问
		break;
	}
	default:
		break;
	}
}

BOOL TellSCM(DWORD dwState, DWORD dwExitCode, DWORD dwProgress)
{
	SERVICE_STATUS serviceStatus = { 0 };
	BOOL bRet = FALSE;

	::RtlZeroMemory(&serviceStatus, sizeof(serviceStatus));
	serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	serviceStatus.dwCurrentState = dwState;
	serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_SHUTDOWN;
	serviceStatus.dwWin32ExitCode = dwExitCode;
	serviceStatus.dwWaitHint = 3000;

	bRet = ::SetServiceStatus(g_ServiceStatusHandle, &serviceStatus);
	return bRet;
}

void DoTask()
{
	// 自己程序实现部分代码放在这里
}