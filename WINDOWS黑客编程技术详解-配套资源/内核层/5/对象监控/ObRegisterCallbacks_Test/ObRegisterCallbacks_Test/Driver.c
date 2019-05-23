#include "NotifyRoutine.h"
#include "Driver.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");

	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	// 编程方式绕过签名检查
//	BypassCheckSign(pDriverObject);

	// 设置进程回调函数
	SetProcessCallbacks();

	// 设置线程回调函数
	SetThreadCallbacks();

	DbgPrint("Leave DriverEntry\n");
	return status;
}



VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	// 删除进程回调函数
	RemoveProcessCallbacks();

	// 删除线程回调函数
	RemoveThreadCallbacks();
}


NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}