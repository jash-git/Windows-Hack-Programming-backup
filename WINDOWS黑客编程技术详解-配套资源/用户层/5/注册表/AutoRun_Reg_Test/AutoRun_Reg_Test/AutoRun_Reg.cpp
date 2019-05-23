#include "stdafx.h"
#include "AutoRun_Reg.h"


void ShowError(char *lpszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error!\nError Code Is:%d\n", lpszText, ::GetLastError());
#ifdef _DEBUG
	::MessageBox(NULL, szErr, "ERROR", MB_OK | MB_ICONERROR);
#endif
}


BOOL Reg_CurrentUser(char *lpszFileName, char *lpszValueName)
{
	// 默认权限
	HKEY hKey;
	// 打开注册表键
	if (ERROR_SUCCESS != ::RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey))
	{
		ShowError("RegOpenKeyEx");
		return FALSE;
	}
	// 修改注册表值，实现开机自启
	if (ERROR_SUCCESS != ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ, (BYTE *)lpszFileName, (1 + ::lstrlen(lpszFileName))))
	{
		::RegCloseKey(hKey);
		ShowError("RegSetValueEx");
		return FALSE;
	}
	// 关闭注册表键
	::RegCloseKey(hKey);

	return TRUE;
}


BOOL Reg_LocalMachine(char *lpszFileName, char *lpszValueName)
{
	// 管理员权限
	HKEY hKey;
	// 打开注册表键
	if (ERROR_SUCCESS != ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE, &hKey))
	{
		ShowError("RegOpenKeyEx");
		return FALSE;
	}
	// 修改注册表值，实现开机自启
	if (ERROR_SUCCESS != ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ, (BYTE *)lpszFileName, (1 + ::lstrlen(lpszFileName))))
	{
		::RegCloseKey(hKey);
		ShowError("RegSetValueEx");
		return FALSE;
	}
	// 关闭注册表键
	::RegCloseKey(hKey);

	return TRUE;
}