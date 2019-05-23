// AutoRun_Task_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyTaskSchedule.h"


int _tmain(int argc, _TCHAR* argv[])
{
	CMyTaskSchedule task;
	BOOL bRet = FALSE;

	// 创建 任务计划
	bRet = task.NewTask("520", "C:\\Users\\DemonGan\\Desktop\\520.exe", "", "");
	if (FALSE == bRet)
	{
		printf("Create Task Schedule Error!\n");
	}

	// 暂停
	printf("Create Task Schedule OK!\n");
	system("pause");

	// 卸载 任务计划
	bRet = task.Delete("520");
	if (FALSE == bRet)
	{
		printf("Delete Task Schedule Error!\n");
	}

	printf("Delete Task Schedule OK!\n");
	system("pause");
	return 0;
}

