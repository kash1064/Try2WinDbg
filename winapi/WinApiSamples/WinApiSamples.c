#include <stdio.h>
#include <windows.h>

int main(void) {
    char lpBuffer[] = { 0x41, 0x42, 0x43 };
    const WCHAR* lpFileName = L"C:\\Users\\Tadpole01\\Downloads\\test.txt";

    HANDLE hFile = CreateFile(
        lpFileName,
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        0,
        NULL
    );

    DWORD nNumberOfBytesToWrite = sizeof(lpBuffer);
    DWORD lpNumberOfBytesWritten;
    BOOL bResult = WriteFile(
        hFile,
        lpBuffer,
        nNumberOfBytesToWrite,
        &lpNumberOfBytesWritten,
        NULL
    );
    CloseHandle(hFile);
	return 0;
}