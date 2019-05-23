// HTTPS_Download_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "HttpsInet.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char szHttpsDownloadUrl[] = "https://download.microsoft.com/download/0/2/3/02389126-40A7-46FD-9D83-802454852703/vc_mbcsmfc.exe";
	BYTE *pHttpsDownloadData = NULL;
	DWORD dwHttpsDownloadDataSize = 0;
	// HTTPS下载 
	if (FALSE == Https_Download(szHttpsDownloadUrl, &pHttpsDownloadData, &dwHttpsDownloadDataSize))
	{
		return 1;
	}
	// 将数据保存成文件
	Https_SaveToFile("https_downloadsavefile.exe", pHttpsDownloadData, dwHttpsDownloadDataSize);
	// 释放内存
	delete []pHttpsDownloadData;
	pHttpsDownloadData = NULL;

	system("pause");
	return 0;
}

