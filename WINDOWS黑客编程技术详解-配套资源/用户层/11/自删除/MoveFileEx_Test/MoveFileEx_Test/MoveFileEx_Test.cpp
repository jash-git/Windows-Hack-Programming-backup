// MoveFileEx_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


BOOL RebootDelete(char *pszFileName)
{
	// 重启删除文件
	char szTemp[MAX_PATH] = "\\\\?\\";
	::lstrcat(szTemp, pszFileName);
	BOOL bRet = ::MoveFileEx(szTemp, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
	return bRet;
}


int _tmain(int argc, _TCHAR* argv[])
{
	if (FALSE == RebootDelete("C:\\Users\\Test\\Desktop\\520.exe"))
	{
		printf("Set Reboot Delete Error.\n");
	}
	else
	{
		printf("Set Reboot Delete OK.\n");
	}

	system("pause");
	return 0;
}

