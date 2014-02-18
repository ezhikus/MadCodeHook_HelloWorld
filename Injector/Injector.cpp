#include "stdafx.h"
#include <conio.h>
#include "windows.h"
#include "madCHook.h"
#include <tlhelp32.h>

HANDLE GetProcessByName(PCWSTR name)
{
	DWORD pid = 0;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	if (Process32First(snapshot, &process))
	{
		do
		{
			if (_wcsicmp(process.szExeFile, name) == 0)
			{
				pid = process.th32ProcessID;
				break;
			}
		} while(Process32Next(snapshot, &process));
	}

	CloseHandle(snapshot);

	if (pid != 0)
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	return NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{
	InjectLibraryW((DWORD)GetProcessByName(L"firefox.exe"), L"HookLib.dll");
	_getch();
	UninjectLibraryW((DWORD)GetProcessByName(L"firefox.exe"), L"HookLib.dll");
}
