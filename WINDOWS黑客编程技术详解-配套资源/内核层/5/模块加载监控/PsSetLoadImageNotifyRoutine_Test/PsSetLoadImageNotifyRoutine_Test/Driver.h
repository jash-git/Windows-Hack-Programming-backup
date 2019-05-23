#ifndef _DRIVER_H_
#define _DRIVER_H_


#include <ntddk.h>


#define DEV_NAME L"\\Device\\DEV_NAME"
#define SYM_NAME L"\\DosDevices\\SYM_NAME"
#define IOCTL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)


VOID DriverUnload(PDRIVER_OBJECT pDriverObject);
NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DriverControlHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS CreateDevice(PDRIVER_OBJECT pDriverObject);


#endif