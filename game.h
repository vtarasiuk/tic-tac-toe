#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define GAME_LINE_SIZE 3
#define CHECK_FUNCTIONS 3

typedef struct
{
    short grid[GAME_LINE_SIZE][GAME_LINE_SIZE];
} GameData, *pGameData;

typedef short (*GameFieldCheckFunction) (pGameData);

bool gridFull(pGameData data);
short won(pGameData data);
bool validTurn(pGameData data, uint8_t playerChose);
void makeTurn(pGameData data, uint8_t playerID, uint8_t playerChose);

#endif