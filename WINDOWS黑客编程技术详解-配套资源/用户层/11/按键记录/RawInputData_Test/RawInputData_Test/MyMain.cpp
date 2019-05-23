#include "resource.h"
#include "RawInputTest.h"


BOOL CALLBACK ProgMainDlg(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == uiMsg)
	{
		// 注册原始输入设备
		Init(hWnd);
	}
	else if (WM_CLOSE == uiMsg)
	{
		::EndDialog(hWnd, NULL);
	}
	else if (WM_INPUT == uiMsg)
	{
		// 获取获取按键消息
		GetData(lParam);
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