#include "LoadImageNotify.h"
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

	status = SetNotifyRoutine();

	DbgPrint("Leave DriverEntry\n");
	return status;
}


VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Enter DriverUnload\n");

	RemoveNotifyRoutine();

	UNICODE_STRING ustrSymName;
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);
	IoDeleteSymbolicLink(&ustrSymName);
	if (pDriverObject->DeviceObject)
	{
		IoDeleteDevice(pDriverObject->DeviceObject);
	}

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
	ULONG ulInputLength = pIoStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG ulOutputLength = pIoStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG ulControlCode = pIoStackLocation->Parameters.DeviceIoControl.IoControlCode;
	PVOID pBuf = pIrp->AssociatedIrp.SystemBuffer;
	ULONG ulInfo = 0;
	
	switch(ulControlCode)
	{
	case IOCTL_TEST:
	{
		break;
	}
	default:
		break;
	}

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	DbgPrint("Leave DriverControlHandle\n");
	return status;
}


NTSTATUS CreateDevice(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Enter CreateDevice\n");
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING ustrDevName, ustrSymName;
	PDEVICE_OBJECT pDevObj = NULL;
	RtlInitUnicodeString(&ustrDevName, DEV_NAME);
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);

	status = IoCreateDevice(pDriverObject, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateDevice Error![0x%X]\n", status);
		return status;
	}

	status = IoCreateSymbolicLink(&ustrSymName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateSymbolicLink Error![0x%X]\n", status);
		return status;
	}

	DbgPrint("Leave CreateDevice\n");
	return status;
}