#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
  #include <windows.h>

  extern inline void enable_virtual_terminal_processing(void) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= 0X0004;
    SetConsoleMode(hOut, dwMode);
  }
#else
  extern inline void enable_virtual_terminal_processing(void) { }
#endif

#endif