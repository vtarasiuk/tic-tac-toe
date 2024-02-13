#ifndef GAME_H
#define GAME_H

#include "game_structure.h"
#include <stdint.h>
#include <stdbool.h>

bool GameFieldFull(pGameData data);
short GameWinner(pGameData data);
bool GameValidTurn(pGameData data, uint8_t move);
void GameMove(pGameData data, uint8_t playerID, uint8_t move);

#endif