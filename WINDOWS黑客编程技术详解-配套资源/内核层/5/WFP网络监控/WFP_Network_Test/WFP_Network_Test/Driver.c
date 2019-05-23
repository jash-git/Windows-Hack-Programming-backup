#include "Driver.h"
#include "WFP_Network.h"


NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");

	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	// 创建设备
	CreateDevice(pDriverObject);

	// 启动WFP
	WfpLoad(pDriverObject->DeviceObject);

	DbgPrint("Leave DriverEntry\n");
	return status;
}



VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	// 删除回调函数和过滤器,关闭引擎
	WfpUnload();
	
	UNICODE_STRING ustrSymName;
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);
	IoDeleteSymbolicLink(&ustrSymName);
	if (pDriverObject->DeviceObject)
	{
		IoDeleteDevice(pDriverObject->DeviceObject);
	}
}


NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

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

	status = IoCreateDevice(pDriverObject, 0, &ustrDevName, FILE_DEVICE_NETWORK, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		ShowError("IoCreateDevice", status);
		return status;
	}
	status = IoCreateSymbolicLink(&ustrSymName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		ShowError("IoCreateSymbolicLink", status);
		return status;
	}

	DbgPrint("Leave CreateDevice\n");
	return status;
}