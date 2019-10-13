// DummyWritter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <Windows.h>
#include <iostream>
using namespace std;

int main() {
	DWORD pid = 0; // The process ID of our target process
	cout << "PID: ";
	cin >> dec >> pid; // Prompting user for PID

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == NULL) { // Failed to get a handle
		cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// Prompting user for memory address to overwrite
	uintptr_t memoryAddress = 0x0;
	cout << "Memory address of the integer to overwrite (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;

	// Prompting user for integer value to overwrite
	int intToWrite = 0;
	cout << "Integer to write (in decimal): ";
	cin >> dec >> intToWrite;

	// Overwriting the integer in the other process
	BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryAddress, &intToWrite, sizeof(int), NULL);
	if (wpmReturn == FALSE) {
		cout << "WriteProcessMemory failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	cout << "Overwritten successfully" << endl;

	cout << "Press ENTER to quit." << endl;
	system("pause > nul");

	return EXIT_SUCCESS;
}