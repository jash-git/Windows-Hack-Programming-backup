// ScreenCapture_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ScreenCapture.h"


int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == ScreenCapture())
	{
		printf("Screen Cpature Error.\n");
	}

	printf("Screen Cpature OK.\n");
	system("pause");
	return 0;
}

