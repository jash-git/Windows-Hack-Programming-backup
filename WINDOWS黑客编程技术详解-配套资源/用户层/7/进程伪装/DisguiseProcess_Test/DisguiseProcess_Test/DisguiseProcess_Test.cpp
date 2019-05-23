// DisguiseProcess_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DisguiseProcess.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == DisguiseProcess(4368, L"C:\\Windows\\explorer.exe", L"explorer.exe"))
	{
		printf("Dsisguise Process Error.\n");
	}
	printf("Dsisguise Process OK.\n");

	system("pause");
	return 0;
}

