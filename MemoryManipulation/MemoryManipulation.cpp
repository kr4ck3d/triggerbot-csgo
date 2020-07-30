
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <memory.h>
#include <TlHelp32.h>
#include <tchar.h>
using namespace std;



 bool checking = true;

DWORD dwGetModuleBaseAddress(TCHAR* lpszModuleName, DWORD pID) {
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32))
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
			{
				dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

void clickMouse() {
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	SendInput(1, &input, sizeof(input));
	ZeroMemory(&input, sizeof(input));
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof(input));

}

int main()
{ 


	DWORD pID;
	DWORD off1, off2, off3, off4, off5, off6, off7;
	DWORD baseAddress;
	DWORD crossID;
	int newHealth = 1000;
	int currentHealth;
	double delay = 0.00001;
	char moduleName[] = "client.dll";
	HWND hGameWindow;
	HANDLE pHandle;

	hGameWindow = FindWindow(NULL, "Counter-Strike: Global Offensive");
	GetWindowThreadProcessId(hGameWindow, &pID);
	pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	DWORD clientBase = dwGetModuleBaseAddress(_T(moduleName), pID);
	while(hGameWindow != NULL){
	ReadProcessMemory(pHandle, (LPCVOID)(clientBase + 0x04D7351C), &off1, sizeof(off1), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(off1 + 0x1C), &off2, sizeof(off2), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(off2 + 0x4), &off3, sizeof(off3), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(off3 + 0x68), &off4, sizeof(off4), NULL);
	crossID = off4;
	if (crossID != 0) {
		cout << crossID;
		clickMouse();
		Sleep(1);
	}
	}
}
