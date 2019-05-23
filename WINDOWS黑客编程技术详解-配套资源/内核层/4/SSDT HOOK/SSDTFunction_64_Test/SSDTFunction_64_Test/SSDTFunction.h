#ifndef _SSDT_FUNCTION_H_
#define _SSDT_FUNCTION_H_


#include <ntddk.h>
#include <ntimage.h>


#pragma pack(1)
typedef struct _SERVICE_DESCIPTOR_TABLE
{
	PULONG ServiceTableBase;		  // SSDT基址
	PVOID ServiceCounterTableBase; // SSDT中服务被调用次数计数器
	ULONGLONG NumberOfService;     // SSDT服务个数
	PVOID ParamTableBase;		  // 系统服务参数表基址
}SSDTEntry, *PSSDTEntry;
#pragma pack()


// 获取 SSDT 函数地址
PVOID GetSSDTFunction(PCHAR pszFunctionName);

// 根据特征码, 从 KiSystemCall64 中获取 SSDT 地址
PVOID GetSSDTAddress();

// 从 ntdll.dll 中获取 SSDT 函数索引号
ULONG GetSSDTFunctionIndex(UNICODE_STRING ustrDllFileName, PCHAR pszFunctionName);
// 内存映射文件
NTSTATUS DllFileMap(UNICODE_STRING ustrDllFileName, HANDLE *phFile, HANDLE *phSection, PVOID *ppBaseAddress);
// 根据导出表获取导出函数地址, 从而获取 SSDT 函数索引号
ULONG GetIndexFromExportTable(PVOID pBaseAddress, PCHAR pszFunctionName);


#endif