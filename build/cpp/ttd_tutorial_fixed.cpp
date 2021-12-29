#include <array>
#include <cstring>
#include <stdio.h>
#include <string.h>

void GetCppConGreeting(wchar_t *buffer, size_t size)
{
    wchar_t const *const message = L"HELLO FROM THE WINDBG TEAM. GOOD LUCK IN ALL OF YOUR TIME TRAVEL DEBUGGING!";

    wcscpy_s(buffer, size, message);
}

int main()
{
    std::array<wchar_t, 75> greeting{};
    GetCppConGreeting(greeting.data(), sizeof(greeting));

    wprintf(L"%ls\n", greeting.data());

    return 0;
}