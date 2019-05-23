// HTTP_Download_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpInet.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szHttpDownloadUrl[] = "http://www.demongan.com/source/ccc/dasanxia/520.zip";
	BYTE *pHttpDownloadData = NULL;
	DWORD dwHttpDownloadDataSize = 0;
	// HTTP下载 
	if (FALSE == Http_Download(szHttpDownloadUrl, &pHttpDownloadData, &dwHttpDownloadDataSize))
	{
		return 1;
	}
	// 将下载数据保存成文件
	Http_SaveToFile("http_downloadsavefile.zip", pHttpDownloadData, dwHttpDownloadDataSize);
	// 释放内存
	delete []pHttpDownloadData;
	pHttpDownloadData = NULL;

	system("pause");
	return 0;
}

