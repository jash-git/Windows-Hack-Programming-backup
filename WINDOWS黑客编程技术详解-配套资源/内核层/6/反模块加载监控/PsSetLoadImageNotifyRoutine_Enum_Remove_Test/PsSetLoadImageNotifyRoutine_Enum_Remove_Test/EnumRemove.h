#ifndef _ENUM_REMOVE_H_
#define _ENUM_REMOVE_H_


#include <ntddk.h>


// 遍历回调
BOOLEAN EnumNotifyRoutine();

// 移除回调
NTSTATUS RemoveNotifyRoutine(PVOID pNotifyRoutineAddress);

// 获取 PspLoadImageNotifyRoutine 数组地址
PVOID GetPspLoadImageNotifyRoutine();

// 根据特征码获取 PspLoadImageNotifyRoutine 数组地址
PVOID SearchPspLoadImageNotifyRoutine(PUCHAR pSpecialData, ULONG ulSpecialDataSize);

// 指定内存区域的特征码扫描
PVOID SearchMemory(PVOID pStartAddress, PVOID pEndAddress, PUCHAR pMemoryData, ULONG ulMemoryDataSize);


#endif