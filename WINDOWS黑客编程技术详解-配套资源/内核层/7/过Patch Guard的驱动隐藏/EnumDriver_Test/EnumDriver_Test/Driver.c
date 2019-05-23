#include "Driver.h"
#include "EnumDriver.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");

	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	// 遍历驱动模块
	EnumDriver(pDriverObject);

	// 驱动模块隐藏(Bypass Patch Guard)
	UNICODE_STRING ustrDriverName;
	RtlInitUnicodeString(&ustrDriverName, L"EnumDriver_Test.sys");
	HideDriver_Bypass_PatchGuard(pDriverObject, ustrDriverName);
	
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