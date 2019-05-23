// TCP_Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TcpServer.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 创建套接字并绑定地址端口进行监听
	if (FALSE == SocketBindAndListen("127.0.0.1", 12345))
	{
		printf("SocketBindAndListen Error.\n");
	}
	printf("SocketBindAndListen OK.\n");

	// 发送信息
	char szSendBuf[MAX_PATH] = {0};
	while (TRUE)
	{
		gets(szSendBuf);
		// 发送数据
		SendMsg(szSendBuf);
	}

	return 0;
}

