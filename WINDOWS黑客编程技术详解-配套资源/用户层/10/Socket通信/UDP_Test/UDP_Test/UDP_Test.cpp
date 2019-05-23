// UDP_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "UDPTest.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szIp[MAX_PATH] = { 0 };
	int iPort = 0;
	// 输入程序UDP绑定的IP和端口
	printf("Input IP and Port:\n");
	scanf("%s%d", szIp, &iPort);
	getchar();

	// 绑定地址
	if (FALSE == Bind(szIp, iPort))
	{
		printf("Bind Error.\n");
	}
	printf("Bind OK.\n");

	// 输入发送数据目的主机的IP和端口
	printf("Input Dest IP and Dest Port:\n");
	scanf("%s%d", szIp, &iPort);
	getchar();
	// 发送数据
	char szBuf[MAX_PATH] = {0};
	while (TRUE)
	{
		gets(szBuf);
		SendMsg(szBuf, szIp, iPort);
	}

	return 0;
}

