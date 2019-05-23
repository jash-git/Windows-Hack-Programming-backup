// Pipe_CMD_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PipeCmd.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szCmd[] = "ping 127.0.0.1";
	char szResultBuffer[512] = {0};
	DWORD dwResultBufferSize = 512;

	// 执行 cmd 命令, 并获取执行结果数据
	if (FALSE == PipeCmd(szCmd, szResultBuffer, dwResultBufferSize))
	{
		printf("pipe cmd error.\n");
	}
	else
	{
		printf("CMD执行结果为:\n%s\n", szResultBuffer);
	}

	system("pause");
	return 0;
}

