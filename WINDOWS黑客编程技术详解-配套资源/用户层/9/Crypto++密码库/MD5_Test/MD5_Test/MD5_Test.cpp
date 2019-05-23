// MD5_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MD5Test.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 方式一 输入文件名称
	string md51 = CalMD5_ByFile("520.exe");
	printf("md51=%s\n", md51.c_str());
	// 方式二 输入文件数据内容
	HANDLE hFile2 = ::CreateFile("520.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	DWORD dwFileSize2 = ::GetFileSize(hFile2, NULL);
	BYTE *pData2 = new BYTE[dwFileSize2];
	::ReadFile(hFile2, pData2, dwFileSize2, NULL, NULL);
	string md52 = CalMD5_ByMem(pData2, dwFileSize2);
	printf("md52=%s\n", md52.c_str());

	system("pause");
	return 0;
}

