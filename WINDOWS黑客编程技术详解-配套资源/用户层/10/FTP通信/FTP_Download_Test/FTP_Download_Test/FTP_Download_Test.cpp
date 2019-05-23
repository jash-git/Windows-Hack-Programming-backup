// FTP_Download_Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "WinInet_Ftp.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BYTE *pDownloadData = NULL;
	DWORD dwDownloadDataSize = 0;
	// 下载
	if (FALSE == FTPDownload("ftp://admin:123456789@192.168.0.1/Flower520.zip", &pDownloadData, &dwDownloadDataSize))
	{
		printf("FTP Download Error!\n");
	}
	// 将数据保存为文件
	Ftp_SaveToFile("myftpdownloadtest.zip", pDownloadData, dwDownloadDataSize);
	// 释放内存
	delete []pDownloadData;
	pDownloadData = NULL;
	printf("FTP Download OK.\n");
	system("pause");
	return 0;
}

