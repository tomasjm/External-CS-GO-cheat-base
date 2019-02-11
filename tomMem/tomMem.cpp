#include "tomMem.h" 

HANDLE TomMem::GetProcessHandle(const char* process) {
	HANDLE hProc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 proc;
	BOOL processList;
	bool success = false;
	proc.dwSize = sizeof(proc);
	do {
		if (!strcmp(proc.szExeFile, process)) {
			this->pid = proc.th32ProcessID;
			success = true;
			CloseHandle(hProc);
			break;
		}
	} while (Process32Next(hProc, &proc));
	if (success) {
		std::cout << "Handle creado correctamente." << std::endl;
	}
	else {
		std::cout << "Error al crear handle, proceso no encontrado." << std::endl;
	}
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->pid);
}

Module TomMem::GetModule(const char* moduleName) {
	Module foundModule;
	DWORD dwModuleBaseAddress;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->pid);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(MODULEENTRY32);
	bool success = false;
	do
	{
		if (!strcmp(mEntry.szModule, moduleName))
		{
			dwModuleBaseAddress = (DWORD)mEntry.modBaseAddr;
			foundModule.dwBase = dwModuleBaseAddress;
			foundModule.dwSize = mEntry.modBaseSize;
			success = true;
			break;
		}
	} while (Module32Next(hSnapshot, &mEntry));
	if (success) {
		std::cout << "Se ha conseguido el modulo " << moduleName << " correctamente: ";
		this->hcout<DWORD>(foundModule.dwBase);
	} else {
		std::cout << "Error al conseguir el modulo " << moduleName << std::endl;
	}
	return foundModule;
}

void TomMem::GetLocalPlayer(DWORD dwLocalPlayer) {
	this->LocalPlayer = this->mRead<DWORD>(this->cDLL.dwBase + dwLocalPlayer);
	if (this->LocalPlayer != NULL) {
		std::cout << "LocalPlayer ha sido encontrado en: ";
		this->hcout<DWORD>(this->LocalPlayer);
	}
	else {
		std::cout << "No se ha podido encontrar LocalPlayer" << std::endl;
	}
}

TomMem::TomMem() {
	this->hProc = this->GetProcessHandle("csgo.exe");
	this->cDLL = this->GetModule("client_panorama.dll");
	this->eDLL = this->GetModule("engine.dll");
}

