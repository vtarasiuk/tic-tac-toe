#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define GAME_LINE_SIZE 3

typedef struct
{
  int fieldState[GAME_LINE_SIZE][GAME_LINE_SIZE]; // id exchange in the future/// server implementation. different checks // crossplatform // WebSocket
  
} GameData, *GameDataPtr;

typedef struct
{
  int straight[2 * GAME_LINE_SIZE][GAME_LINE_SIZE];
  int diagonal[2][3]; // refactor
} FieldLines, *FieldLinesPtr;

bool field_full(GameDataPtr data);
int won(GameDataPtr data);
bool line_filled(int line[GAME_LINE_SIZE]);
FieldLines possible_field_lines(GameDataPtr data);
bool valid_turn(GameDataPtr data, uint8_t playerChose);
void move(GameDataPtr data, uint8_t playerID, uint8_t playerChose);

#endif