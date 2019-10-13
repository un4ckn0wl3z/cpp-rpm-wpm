#include "pch.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD pid = 0; // The process ID of our target process
	cout << "PID: ";
	cin >> dec >> pid; // Prompting user for PID

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == nullptr)
	{
		// Failed to get a handle
		cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Prompting user for memory address to read
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the integer to read (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;
	cout << "Reading 0x" << hex << uppercase << memoryAddress << " ..." << endl;

	// Reading the integer from other process
	int intRead = 0;
	BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryAddress, &intRead, sizeof(int), nullptr);
	if (rpmReturn == FALSE)
	{
		cout << "ReadProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	cout << "intRead = " << dec << intRead << endl;

	cout << "Press ENTER to quit." << endl;
	system("pause > nul");

	return EXIT_SUCCESS;
}
