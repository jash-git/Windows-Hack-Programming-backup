#include "IrpFile.h"
#include "FileManage.h"
#include "Driver.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");
	NTSTATUS status = STATUS_SUCCESS;

	pDriverObject->DriverUnload = DriverUnload;
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = DriverDefaultHandle;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverDefaultHandle;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DriverControlHandle;

	status = CreateDevice(pDriverObject);

	// IRP 操作文件测试
	MyIrpFileTest();

	DbgPrint("Leave DriverEntry\n");
	return status;
}


VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Enter DriverUnload\n");

	if (pDriverObject->DeviceObject)
	{
		IoDeleteDevice(pDriverObject->DeviceObject);
	}
	UNICODE_STRING ustrSymName;
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);
	IoDeleteSymbolicLink(&ustrSymName);

	DbgPrint("Leave DriverUnload\n");
}


NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	DbgPrint("Enter DriverDefaultHandle\n");
	NTSTATUS status = STATUS_SUCCESS;

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	DbgPrint("Leave DriverDefaultHandle\n");
	return status;
}


NTSTATUS DriverControlHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	DbgPrint("Enter DriverControlHandle\n");
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIoStackLocation = IoGetCurrentIrpStackLocation(pIrp);
	ULONG ulInputLen = pIoStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG ulOutputLen = pIoStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG ulControlCode = pIoStackLocation->Parameters.DeviceIoControl.IoControlCode;
	PVOID pBuffer = pIrp->AssociatedIrp.SystemBuffer;
	ULONG ulInfo = 0;

	switch (ulControlCode)
	{
	case IOCTL_TEST:
	{
		break;
	}
	default:
		break;
	}

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = ulInfo;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	DbgPrint("Leave DriverControlHandle\n");
	return status;
}


NTSTATUS CreateDevice(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Enter CreateDevice\n");
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT pDevObj = NULL;
	UNICODE_STRING ustrDevName, ustrSymName;
	RtlInitUnicodeString(&ustrDevName, DEV_NAME);
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);

	status = IoCreateDevice(pDriverObject, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateDevice Error[0x%X]\n", status);
		return status;
	}

	status = IoCreateSymbolicLink(&ustrSymName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateSymbolicLink Error[0x%X]\n", status);
		return status;
	}

	DbgPrint("Leave CreateDevice\n");
	return status;
}


// IRP 操作文件测试
// 注意：路径不需要加 \??\ 作为前缀
VOID MyIrpFileTest()
{
	// 创建文件
	UNICODE_STRING ustrCreateFile;
	RtlInitUnicodeString(&ustrCreateFile, L"C:\\520.txt");
	MyCreateFile(ustrCreateFile);
	DbgPrint("Create File OK.\n");
	
	// 获取文件大小
	UNICODE_STRING ustrFileSize;
	RtlInitUnicodeString(&ustrFileSize, L"C:\\520.exe");
	ULONG64 ullFileSize = MyGetFileSize(ustrFileSize);
	DbgPrint("FileSize = %I64d Bytes\n", ullFileSize);
	
	// 设置文件隐藏属性
	UNICODE_STRING ustrHideFile;
	RtlInitUnicodeString(&ustrHideFile, L"C:\\520.exe");
	MyHideFile(ustrHideFile);
	DbgPrint("Hide File OK.\n");
	
	// 遍历文件夹和文件
	UNICODE_STRING ustrQueryFile;
	RtlInitUnicodeString(&ustrQueryFile, L"C:\\");
	MyQueryFileAndFileFolder(ustrQueryFile);
	DbgPrint("Query File OK.\n");
	
	// 文件数据写入
	UNICODE_STRING ustrWriteFile;
	LARGE_INTEGER liWriteOffset = { 0 };
	UCHAR szWriteData[256] = "Who Are You? I am Demon`Gan.";
	ULONG ulWriteDataLength = 1 + strlen(szWriteData);
	RtlInitUnicodeString(&ustrWriteFile, L"C:\\520.txt");
	MyWriteFile(ustrWriteFile, liWriteOffset, szWriteData, &ulWriteDataLength);
	DbgPrint("MyWriteFile OK.\n");

	// 文件数据读取
	UNICODE_STRING ustrReadFile;
	LARGE_INTEGER liReadOffset = { 0 };
	UCHAR szReadData[256] = { 0 };
	ULONG ulReadDataLength = 256;
	RtlInitUnicodeString(&ustrReadFile, L"C:\\520.txt");
	MyReadFile(ustrReadFile, liReadOffset, szReadData, &ulReadDataLength);
	DbgPrint("MyReadFile:[%s]\n", szReadData);	
}










