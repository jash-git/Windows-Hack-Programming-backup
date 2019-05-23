// ReadDirecotryChangesW_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MonitorFile.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 注意目录路径的末尾要加上反斜杠'\'
	MonitorFile("C:\\Users\\DemonGan\\Desktop\\temp\\");

	printf("monitor...\n");
	getchar();
	return 0;
}

