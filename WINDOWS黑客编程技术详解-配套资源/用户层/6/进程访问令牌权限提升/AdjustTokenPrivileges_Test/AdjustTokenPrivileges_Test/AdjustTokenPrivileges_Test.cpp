// AdjustTokenPrivileges_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AdjustTokenPrivilegesTest.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 修改当前进程令牌访问权限
	if (FALSE == EnbalePrivileges(::GetCurrentProcess(), SE_DEBUG_NAME))
	{
		printf("Enable Privileges Error!\n");
	}

	printf("Enable Privileges OK!\n");
	system("pause");
	return 0;
}

