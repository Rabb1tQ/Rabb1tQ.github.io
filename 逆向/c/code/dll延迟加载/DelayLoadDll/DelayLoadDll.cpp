#include <iostream>
#include<windows.h>
#include "resource.h"

BOOL FreeMyResource(UINT uiResouceName, char* lpszResourceType, char* lpszSaveFileName);

void GetCurrentPath(char* lpszCurrentPath, DWORD dwSize);

void FreeRes_ShowError(char* pszText);

// CDelayLoadDll_TestDlg 消息处理程序


void FreeRes_ShowError(char* pszText)
{
	char szErr[MAX_PATH] = { 0 };
	::wsprintf(szErr, "%s Error[%d]\n", pszText, ::GetLastError());
	::MessageBox(NULL, szErr, "ERROR", MB_OK);
}

// 释放资源
BOOL FreeMyResource(UINT uiResouceName, char* lpszResourceType, char* lpszSaveFileName)
{
	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(uiResouceName), lpszResourceType);
	if (NULL == hRsrc)
	{
		FreeRes_ShowError("FindResource");
		return FALSE;
	}
	DWORD dwSize = ::SizeofResource(NULL, hRsrc);
	if (0 >= dwSize)
	{
		FreeRes_ShowError("SizeofResource");
		return FALSE;
	}
	HGLOBAL hGlobal = ::LoadResource(NULL, hRsrc);
	if (NULL == hGlobal)
	{
		FreeRes_ShowError("LoadResource");
		return FALSE;
	}
	LPVOID lpVoid = ::LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}

	FILE* fp = NULL;
	fopen_s(&fp, lpszSaveFileName, "wb+");
	if (NULL == fp)
	{
		FreeRes_ShowError("LockResource");
		return FALSE;
	}
	fwrite(lpVoid, sizeof(char), dwSize, fp);
	fclose(fp);

	return TRUE;
}


// 获取当前目录
void GetCurrentPath(char* lpszCurrentPath, DWORD dwSize)
{
	::GetModuleFileName(NULL, lpszCurrentPath, dwSize);
	char* p = ::strrchr(lpszCurrentPath, '\\');
	p[0] = '\0';
}

int main()
{
	typedef int (*_pHello)();
	//std::cout << "Hello World!\n";
	// 释放DLL
// 获取当前目录
	char szCurrentPath[MAX_PATH] = { 0 };
	GetCurrentPath(szCurrentPath, MAX_PATH);
	// 构造路径
	::lstrcat(szCurrentPath, "\\dlltest.dll");
	FreeMyResource(IDR_DLLS1, "dlls", szCurrentPath);
	HINSTANCE hDll = LoadLibrary("dlltest.dll");
	_pHello hello = (_pHello)GetProcAddress(hDll, "hello");
	int nHello = hello();
	std::cout << nHello << std::endl;
}