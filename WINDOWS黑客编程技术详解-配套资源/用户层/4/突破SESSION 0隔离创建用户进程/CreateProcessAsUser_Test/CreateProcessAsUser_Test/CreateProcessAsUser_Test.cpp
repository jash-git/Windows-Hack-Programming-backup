// CreateProcessAsUser_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

#include <UserEnv.h>
#include <WtsApi32.h>
#pragma comment(lib, "UserEnv.lib")
#pragma comment(lib, "WtsApi32.lib")


// 服务入口函数以及处理回调函数
void __stdcall ServiceMain(DWORD dwArgc, char *lpszArgv);
void __stdcall ServiceCtrlHandle(DWORD dwOperateCode);
void DoTask();
// 显示消息对话框
void ShowMessage(TCHAR *lpszMessage, TCHAR *lpszTitle);
// 创建用户进程
BOOL CreateUserProcess(char *lpszFileName);

// 全局变量
char g_szServiceName[MAX_PATH] = "CreateProcessAsUser_Test.exe";    // 服务名称 
SERVICE_STATUS g_ServiceStatus = { 0 };
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
	g_ServiceStatus.dwServiceType = SERVICE_WIN32;
	g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	g_ServiceStatus.dwWin32ExitCode = 0;
	g_ServiceStatus.dwServiceSpecificExitCode = 0;
	g_ServiceStatus.dwCheckPoint = 0;
	g_ServiceStatus.dwWaitHint = 0;

	g_ServiceStatusHandle = ::RegisterServiceCtrlHandler(g_szServiceName, ServiceCtrlHandle);

	g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	g_ServiceStatus.dwCheckPoint = 0;
	g_ServiceStatus.dwWaitHint = 0;
	::SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);

	// 自己程序实现部分代码放在这里
	DoTask();
}


void __stdcall ServiceCtrlHandle(DWORD dwOperateCode)
{
	switch (dwOperateCode)
	{
	case SERVICE_CONTROL_PAUSE:
	{
		// 暂停
		g_ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		break;
	}
	case SERVICE_CONTROL_CONTINUE:
	{
		// 继续
		g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		break;
	}
	case SERVICE_CONTROL_STOP:
	{
		// 停止
		g_ServiceStatus.dwWin32ExitCode = 0;
		g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		g_ServiceStatus.dwCheckPoint = 0;
		g_ServiceStatus.dwWaitHint = 0;
		::SetServiceStatus(g_ServiceStatusHandle, &g_ServiceStatus);
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


void DoTask()
{
	// 自己程序实现部分代码放在这里
	// 显示对话框
	ShowMessage("Hi Demon·Gan\nThis Is From Session 0 Service!\n", "HELLO");
	// 创建用户桌面进程
	CreateUserProcess("C:\\Users\\DemonGan\\Desktop\\520.exe");
}


void ShowMessage(TCHAR *lpszMessage, TCHAR *lpszTitle)
{
	// 获取当前的Session ID
	DWORD dwSessionId = ::WTSGetActiveConsoleSessionId();
	// 显示消息对话框
	DWORD dwResponse = 0;
	::WTSSendMessage(WTS_CURRENT_SERVER_HANDLE, dwSessionId,
		lpszTitle, (1 + ::lstrlen(lpszTitle)),
		lpszMessage, (1 + ::lstrlen(lpszMessage)),
		0, 0, &dwResponse, FALSE);
}


// 突破SESSION 0隔离创建用户进程
BOOL CreateUserProcess(char *lpszFileName)
{
	BOOL bRet = TRUE;
	DWORD dwSessionID = 0;
	HANDLE hToken = NULL;
	HANDLE hDuplicatedToken = NULL;
	LPVOID lpEnvironment = NULL;
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	si.cb = sizeof(si);

	do
	{
		// 获得当前Session ID
		dwSessionID = ::WTSGetActiveConsoleSessionId();

		// 获得当前Session的用户令牌
		if (FALSE == ::WTSQueryUserToken(dwSessionID, &hToken))
		{
			ShowMessage("WTSQueryUserToken", "ERROR");
			bRet = FALSE;
			break;
		}

		// 复制令牌
		if (FALSE == ::DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL,
			SecurityIdentification, TokenPrimary, &hDuplicatedToken))
		{
			ShowMessage("DuplicateTokenEx", "ERROR");
			bRet = FALSE;
			break;
		}

		// 创建用户Session环境
		if (FALSE == ::CreateEnvironmentBlock(&lpEnvironment,
			hDuplicatedToken, FALSE))
		{
			ShowMessage("CreateEnvironmentBlock", "ERROR");
			bRet = FALSE;
			break;
		}

		// 在复制的用户Session下执行应用程序，创建进程
		if (FALSE == ::CreateProcessAsUser(hDuplicatedToken,
			lpszFileName, NULL, NULL, NULL, FALSE,
			NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
			lpEnvironment, NULL, &si, &pi))
		{
			ShowMessage("CreateProcessAsUser", "ERROR");
			bRet = FALSE;
			break;
		}

	} while (FALSE);
	// 关闭句柄, 释放资源
	if (lpEnvironment)
	{
		::DestroyEnvironmentBlock(lpEnvironment);
	}
	if (hDuplicatedToken)
	{
		::CloseHandle(hDuplicatedToken);
	}
	if (hToken)
	{
		::CloseHandle(hToken);
	}
	return bRet;
}




