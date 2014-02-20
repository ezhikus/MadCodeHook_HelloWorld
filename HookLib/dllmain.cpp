#include "stdafx.h"
#include "madCHook.h"

LRESULT (WINAPI * TrueSendMessageW)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = SendMessageW;

__declspec(dllexport) LRESULT WINAPI MySendMessageW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if (Msg == WM_SETTEXT && wcsstr((LPCTSTR)lParam, L"Хабрахабр"NULL)
		return TrueSendMessageW(hWnd, Msg, wParam, (LPARAM)L"Привет, Хабр!");

	return TrueSendMessageW(hWnd, Msg, wParam, lParam);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			HookAPI("User32.dll", "SendMessageW", MySendMessageW, (PVOID*) &TrueSendMessageW);
	}
	return TRUE;
}

