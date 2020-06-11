#include "hook.h"

char Process[] = "PlantsVsZombies.exe";

void InitiateHooks()
{
	DWORD ammoAddy = FindPattern(Process, "\x8B\x46\x04\x01\x88\x60\x55\x00\x00\x8B\x88\x60\x55\x00\x00", "xxxxx????xx????");
	ammoAddy += 0x3;
	AmmoJmpBack = ammoAddy + 0xC;

	//MsgBox2(ammoAddy, AmmoJmpBack);
	PlaceJMP((BYTE*)ammoAddy, (DWORD)InfiniteAmmo, 0xC);
}

DWORD WINAPI OverwriteValues()
{
	for (;; Sleep(150))
	{
		YaxisPtr = YaxisRegister + 0x5560;
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			*(int*)YaxisPtr = 9000;
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			MsgBox2(YaxisRegister, YaxisPtr);
		}
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		InitiateHooks();
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)OverwriteValues, NULL, NULL, NULL);

		break;
	}
	return TRUE;
}
