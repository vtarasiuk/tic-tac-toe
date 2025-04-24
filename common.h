#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
#include <windows.h>
#endif

static inline int enableVirtualTerminalProcessing(void)
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return EOF;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return EOF;
    dwMode |= 0x0004;
    SetConsoleMode(hOut, dwMode);
    return 0;
#else
    return 0;
#endif // _WIN32
}

#endif // COMMON_H