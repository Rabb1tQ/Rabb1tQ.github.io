/* Replace "dll.h" with the name of your header */
//#include "pch.h"
#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	  switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
extern "C" __declspec(dllexport) int hello()
{
    int a = 666;
    return a;
}
