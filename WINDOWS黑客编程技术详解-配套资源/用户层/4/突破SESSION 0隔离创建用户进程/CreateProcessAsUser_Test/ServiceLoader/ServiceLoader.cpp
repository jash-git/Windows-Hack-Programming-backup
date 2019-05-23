// ServiceLoader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServiceOperate.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = FALSE;
	char szExePath[] = "C:\\Users\\DemonGan\\Desktop\\CreateProcessAsUser_Test\\Debug\\CreateProcessAsUser_Test.exe";

	// 加载服务
	bRet = SystemServiceOperate(szExePath, 0);
	if (bRet)
	{
		printf("INSTALL OK.\n");
	}
	else
	{
		printf("INSTALL ERROR.\n");
	}
	// 启动服务
	bRet = SystemServiceOperate(szExePath, 1);
	if (bRet)
	{
		printf("START OK.\n");
	}
	else
	{
		printf("START ERROR.\n");
	}


	system("pause");

	// 停止服务
	bRet = SystemServiceOperate(szExePath, 2);
	if (bRet)
	{
		printf("STOP OK.\n");
	}
	else
	{
		printf("STOP ERROR.\n");
	}
	// 卸载服务
	bRet = SystemServiceOperate(szExePath, 3);
	if (bRet)
	{
		printf("UNINSTALL OK.\n");
	}
	else
	{
		printf("UNINSTALL ERROR.\n");
	}

	return 0;
}

