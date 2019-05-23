// CreateMutex_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


// 判断是否重复运行
BOOL IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	hMutex = ::CreateMutex(NULL, FALSE, "TEST");
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			return TRUE;
		}
	}
	return FALSE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	// 判断是否重复运行
	if (IsAlreadyRun())
	{
		printf("Already Run!!!!\n");
	}
	else
	{
		printf("NOT Already Run!\n");
	}

	system("pause");
	return 0;
}

