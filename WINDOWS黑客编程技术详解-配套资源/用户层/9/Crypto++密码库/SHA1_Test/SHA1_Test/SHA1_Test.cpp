// SHA1_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SHA1Test.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// 方式一 输入文件名称
	string sha11 = CalSHA1_ByFile("520.exe");
	printf("sha11=%s\n", sha11.c_str());
	// 方式二 输入文件数据内容
	HANDLE hFile2 = ::CreateFile("520.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	DWORD dwFileSize2 = ::GetFileSize(hFile2, NULL);
	BYTE *pData2 = new BYTE[dwFileSize2];
	::ReadFile(hFile2, pData2, dwFileSize2, NULL, NULL);
	string sha12 = CalSHA1_ByMem(pData2, dwFileSize2);
	printf("sha12=%s\n", sha12.c_str());

	system("pause");
	return 0;
}

