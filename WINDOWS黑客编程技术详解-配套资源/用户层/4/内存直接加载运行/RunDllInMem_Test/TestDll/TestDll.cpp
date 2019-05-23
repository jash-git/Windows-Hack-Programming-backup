// TestDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


BOOL ShowMessage(char *lpszText, char *lpszCaption)
{
	::MessageBox(NULL, lpszText, lpszCaption, MB_OK);

	return TRUE;
}