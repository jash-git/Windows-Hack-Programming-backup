#include "resource.h"

#include <Windows.h>
#include <Dbt.h>


LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	// 设备已经插入
	case DBT_DEVICEARRIVAL:               
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
		// 逻辑卷
		if (DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)  
		{
			// 根据 dbcv_unitmask 计算出设备盘符
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			DWORD dwDriverMask = lpdbv->dbcv_unitmask;
			DWORD dwTemp = 1;
			char szDriver[4] = "A:\\";
			for (szDriver[0] = 'A'; szDriver[0] <= 'Z'; szDriver[0]++)
			{
				if (0 < (dwTemp & dwDriverMask))
				{
					// 获取设备盘符
					::MessageBox(NULL, szDriver, "设备已插入", MB_OK);
				}
				// 左移1位, 接着判断下一个盘符
				dwTemp = (dwTemp << 1);   
			}
		}
		break;
	}
	// 设备已经移除
	case DBT_DEVICEREMOVECOMPLETE:        
	{
		PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
		// 逻辑卷
		if (DBT_DEVTYP_VOLUME == lpdb->dbch_devicetype)
		{
			// 根据 dbcv_unitmask 计算出设备盘符
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			DWORD dwDriverMask = lpdbv->dbcv_unitmask;
			DWORD dwTemp = 1;
			char szDriver[4] = "A:\\";
			for (szDriver[0] = 'A'; szDriver[0] <= 'Z'; szDriver[0]++)
			{
				if (0 < (dwTemp & dwDriverMask))
				{
					// 获取设备盘符
					::MessageBox(NULL, szDriver, "设备已移除", MB_OK);
				}
				// 左移1位, 接着判断下一个盘符
				dwTemp = (dwTemp << 1);
			}
		}
		break;
	}
	default:
		break;
	}

	return 0;
}


BOOL CALLBACK ProgMainDlg(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_DEVICECHANGE == uiMsg)
	{
		OnDeviceChange(wParam, lParam);
	}
	else if (WM_CLOSE == uiMsg)
	{
		::EndDialog(hWnd, NULL);
	}

	return FALSE;
}


int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevinstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	::DialogBoxParam(hInstance, (LPCSTR)IDD_DIALOG1, NULL, (DLGPROC)ProgMainDlg, NULL);

	::ExitProcess(NULL);
	return 0;
}



