#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>


struct Module {
	DWORD dwBase;
	DWORD dwSize;
};

class TomMem {
public:
	DWORD pid;
	Module cDLL;
	Module eDLL;
	HANDLE hProc;

	HANDLE GetProcessHandle(const char* process);
	Module GetModule(const char* moduleName);

	DWORD LocalPlayer;
	void GetLocalPlayer(DWORD dwLocalPlayer);


	template <class word>
	void hcout(word wWord) {
		std::cout << std::hex << "0x" << wWord << std::endl;
	}

	template <class readType>
	readType mRead(DWORD address) {
		readType valor;
		ReadProcessMemory(this->hProc, (LPVOID)address, &valor, sizeof(readType), NULL);
		return valor;
	}

	template <class writeType>
	void mWrite(DWORD address, writeType data) {
		WriteProcessMemory(this->hProc, (LPVOID)address, &data, sizeof(writeType), NULL);
	}

	TomMem();
};
