// AutoRun_Reg_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AutoRun_Reg.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 第一种方式修改注册表:HKEY_CURRENT_USER
	if (FALSE == Reg_CurrentUser("C:\\Users\\DemonGan\\Desktop\\520_1.exe", "520"))
	{
		printf("Reg_CurrentUser Error!\n");
	}
	// 第二种方式修改注册表:HKEY_LOCAL_MACHINE
	if (FALSE == Reg_LocalMachine("C:\\Users\\DemonGan\\Desktop\\520_2.exe", "520"))
	{
		printf("Reg_LocalMachine Error!\n");
	}

	printf("Reg OK.\n");

	system("pause");
	return 0;
}

