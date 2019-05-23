#ifndef _DRIVER_H_
#define _DRIVER_H_


#include <ntddk.h>


VOID DriverUnload(PDRIVER_OBJECT pDriverObject);
NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp);


#endif