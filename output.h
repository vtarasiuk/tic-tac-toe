#ifndef OUTPUT_H
#define OUTPUT_H

#include "game.h"
#include <stdio.h>
#include <stdint.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void printGameField(pGameData data);
static inline void discardInputStream()
{
    int discard;
    while ((discard = getchar()) != '\n' && discard != EOF);
}

#endif