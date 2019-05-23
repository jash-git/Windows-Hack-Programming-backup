// ZwCreateThreadEx_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "InjectDll.h"
#include "AdjustTokenPrivilegesTest.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 提升当前进程令牌权限
	EnbalePrivileges(::GetCurrentProcess(), SE_DEBUG_NAME);
	// 远线程注入 DLL
#ifndef _WIN64
	BOOL bRet = ZwCreateThreadExInjectDll(8080, "C:\\Users\\DemonGan\\Desktop\\ZwCreateThreadEx_Test\\Debug\\TestDll.dll");
#else 
	BOOL bRet = ZwCreateThreadExInjectDll(2940, "C:\\Users\\DemonGan\\Desktop\\ZwCreateThreadEx_Test\\x64\\Debug\\TestDll.dll");
#endif
	if (FALSE == bRet)
	{
		printf("Inject Dll Error.\n");
	}
	printf("Inject Dll OK.\n");
	system("pause");
	return 0;
}

