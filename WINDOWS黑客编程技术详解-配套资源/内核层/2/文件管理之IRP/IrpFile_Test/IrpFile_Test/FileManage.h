#ifndef _FILE_MANAGE_H_
#define _FILE_MANAGE_H


#include <ntifs.h>
#include <ntstatus.h>

// 注意: 路径不需要加 \??\ 作为前缀


// 创建或打开文件
BOOLEAN MyCreateFile(UNICODE_STRING ustrFilePath);

// 获取文件大小
ULONG64 MyGetFileSize(UNICODE_STRING ustrFileName);

// 设置文件隐藏属性
BOOLEAN MyHideFile(UNICODE_STRING ustrFileName);

// 遍历文件夹和文件
BOOLEAN MyQueryFileAndFileFolder(UNICODE_STRING ustrPath);

// 读取文件数据
BOOLEAN MyReadFile(UNICODE_STRING ustrFileName, LARGE_INTEGER liOffset, PUCHAR pReadData, PULONG pulReadDataSize);

// 向文件写入数据
BOOLEAN MyWriteFile(UNICODE_STRING ustrFileName, LARGE_INTEGER liOffset, PUCHAR pWriteData, PULONG pulWriteDataSize);


#endif