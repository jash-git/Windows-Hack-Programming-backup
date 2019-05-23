// AutoRun_Service_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServiceOperate.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BOOL bRet = FALSE;
	char szFileName[MAX_PATH] = "C:\\Users\\DemonGan\\Desktop\\AutoRun_Service_Test\\Debug\\ServiceTest.exe";

	// 创建并启动服务
	bRet = SystemServiceOperate(szFileName, 0);
	if (FALSE == bRet)
	{
		printf("Create Error!\n");
	}
	bRet = SystemServiceOperate(szFileName, 1);
	if (FALSE == bRet)
	{
		printf("Start Error!\n");
	}
	printf("Create and Start OK.\n");

	system("pause");

	// 停止并删除服务
	bRet = SystemServiceOperate(szFileName, 2);
	if (FALSE == bRet)
	{
		printf("Stop Error!\n");
	}
	bRet = SystemServiceOperate(szFileName, 3);
	if (FALSE == bRet)
	{
		printf("Delete Error!\n");
	}
	printf("Stop and Delete OK.\n");

	system("pause");
	return 0;
}

