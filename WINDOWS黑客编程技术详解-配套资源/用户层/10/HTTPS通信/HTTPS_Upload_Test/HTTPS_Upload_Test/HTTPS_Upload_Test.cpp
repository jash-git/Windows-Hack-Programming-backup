// HTTPS_Upload_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpsInet.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szHttpsUploadUrl[] = "https://192.168.28.137/mytest1.asp?file=520.zip";
	char szHttpsUploadFileName[] = "C:\\Users\\DemonGan\\Desktop\\520.zip";
	BYTE *pHttpsUploadData = NULL;
	DWORD dwHttpsUploadDataSize = 0;
	DWORD dwRets = 0;
	// 打开文件
	HANDLE hFiles = ::CreateFile(szHttpsUploadFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_ARCHIVE, NULL);
	if (INVALID_HANDLE_VALUE == hFiles)
	{
		return 1;
	}
	// 获取文件大小
	dwHttpsUploadDataSize = ::GetFileSize(hFiles, NULL);
	// 读取文件数据
	pHttpsUploadData = new BYTE[dwHttpsUploadDataSize];
	::ReadFile(hFiles, pHttpsUploadData, dwHttpsUploadDataSize, &dwRets, NULL);
	dwHttpsUploadDataSize = dwRets;
	// 上传数据
	if (FALSE == Https_Upload(szHttpsUploadUrl, pHttpsUploadData, dwHttpsUploadDataSize))
	{
		return 2;
	}
	// 释放内存
	delete []pHttpsUploadData;
	pHttpsUploadData = NULL;
	::CloseHandle(hFiles);

	system("pause");
	return 0;
}

