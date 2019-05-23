#ifndef _DRIVER_H_
#define _DRIVER_H_


#include <ntddk.h>


#define DEV_NAME L"\\Device\\MY_WFP_DEV_NAME"
#define SYM_NAME L"\\DosDevices\\MY_WFP_SYM_NAME"


VOID DriverUnload(PDRIVER_OBJECT pDriverObject);
NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS CreateDevice(PDRIVER_OBJECT pDriverObject);

#endif