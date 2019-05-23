// AutoRun_Startup_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include <Shlobj.h>
#pragma comment(lib, "shell32.lib")


BOOL AutoRun_Startup(char *lpszSrcFilePath, char *lpszDestFileName)
{
	BOOL bRet = FALSE;
	char szStartupPath[MAX_PATH] = {0};
	char szDestFilePath[MAX_PATH] = {0};
	// 获取 快速启动目录 路径
	bRet = ::SHGetSpecialFolderPath(NULL, szStartupPath, CSIDL_STARTUP, TRUE);
	printf("szStartupPath=%s\n", szStartupPath);
	if (FALSE == bRet)
	{
		return FALSE;
	}
	// 构造拷贝的 目的文件路径
	::wsprintf(szDestFilePath, "%s\\%s", szStartupPath, lpszDestFileName);
	// 拷贝文件到快速启动目录下
	bRet = ::CopyFile(lpszSrcFilePath, szDestFilePath, FALSE);
	if (FALSE == bRet)
	{
		return FALSE;
	}

	return TRUE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == AutoRun_Startup("C:\\Users\\DemonGan\\Desktop\\520.exe", "520.exe"))
	{
		printf("Startup Error!\n");
	}
	printf("Startup OK!\n");

	system("pause");
	return 0;
}

