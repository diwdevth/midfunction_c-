#define _CRT_SECURE_NO_WARNINGS
#include "functions.h"

DWORD AmmoJmpBack = 0;
DWORD YaxisRegister = 0x0;
DWORD YaxisPtr;

__declspec(naked) void InfiniteAmmo()
{
	__asm {
		add dword ptr[eax + 0x5560], ecx
		mov ecx, dword ptr[eax + 0x5560]
		mov YaxisRegister, eax
		jmp[AmmoJmpBack]
	}
}
