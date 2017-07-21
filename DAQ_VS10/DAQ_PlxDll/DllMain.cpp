#include "StdAfx.h"


HMODULE g_hModule;

BOOL APIENTRY DllMain(HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	g_hModule = (HMODULE)hModule;
    return TRUE;
}