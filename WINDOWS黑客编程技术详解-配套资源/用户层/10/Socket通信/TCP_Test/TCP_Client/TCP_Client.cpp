// TCP_Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpClient.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 连接到服务器
	if (FALSE == Connection("127.0.0.1", 12345))
	{
		printf("Connection Error.\n");
	}
	printf("Connection OK.\n");

	// 发送信息
	char szSendBuf[MAX_PATH] = { 0 };
	while (TRUE)
	{
		gets(szSendBuf);
		// 发送数据
		SendMsg(szSendBuf);
	}

	return 0;
}

