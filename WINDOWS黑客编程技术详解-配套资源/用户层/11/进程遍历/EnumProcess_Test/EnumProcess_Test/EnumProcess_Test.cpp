// EnumProcess_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "EnumInfo.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 遍历进程
	if (FALSE == EnumProcess())
	{
		printf("Enum Process Error!\n");
	}

	system("pause");
	system("cls");

	// 遍历线程
	if (FALSE == EnumThread())
	{
		printf("Enum Thread Error!\n");
	}

	system("pause");
	system("cls");

	// 遍历指定进程模块
	if (FALSE == EnumProcessModule(6876))
	{
		printf("Enum Process Module Error!\n");
	}

	system("pause");
	return 0;
}

