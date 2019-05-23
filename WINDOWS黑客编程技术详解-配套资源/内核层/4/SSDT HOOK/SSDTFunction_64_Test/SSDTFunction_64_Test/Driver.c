#include "Driver.h"
#include "SSDTFunction.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");

	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	// 获取 SSDT 函数地址
	GetSSDTFunction("NtOpenProcess");

	DbgPrint("Leave DriverEntry\n");
	return status;
}



VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
}


NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}