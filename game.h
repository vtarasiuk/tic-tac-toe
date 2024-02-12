#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define GAME_LINE_SIZE 3

#define PLAYER_1_VALUE 1
#define PLAYER_2_VALUE 2

#define CHECK_FUNCTIONS 3

typedef struct
{
  short fieldState[GAME_LINE_SIZE][GAME_LINE_SIZE]; // id exchange in the future/// server implementation. // crossplatform // WebSocket
} GameData, *pGameData;

bool GameFieldFull(pGameData data); // no static !!!!!!!!!!!!!
short GameWinner(pGameData data);
bool ValidTurn(pGameData data, uint8_t move);
void Move(pGameData data, uint8_t playerID, uint8_t move);

#endif