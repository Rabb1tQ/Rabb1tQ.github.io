// CreateMutex_Test.cpp : 定义控制台应用程序的入口点。
//

#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
// 判断是否重复运行
BOOL IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	bool result = false;
	hMutex = CreateMutex(NULL, FALSE, TEXT("TEST"));
	if (hMutex)
	{
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			result= TRUE;
		}
	}
	return result;
}


int main()
{
	// 判断是否重复运行
	if (IsAlreadyRun())
	{
		printf("Already Run!!!!\n");
	}
	else
	{
		printf("NOT Already Run!\n");
	}

	system("pause");
	return 0;
}

