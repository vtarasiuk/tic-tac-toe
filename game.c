#include "game.h"

bool valid_turn(GameDataPtr data, uint8_t playerChose)
{
  uint8_t rowChosed = (playerChose - 1) / GAME_LINE_SIZE;
  uint8_t colChosed = (playerChose - 1) % GAME_LINE_SIZE;

  if (data->fieldState[rowChosed][colChosed] == 0)
  {
    return true;
  }
  return false;
}

void move(GameDataPtr data, uint8_t playerID, uint8_t playerChose)
{
  uint8_t rowChosed = (playerChose - 1) / GAME_LINE_SIZE;
  uint8_t colChosed = (playerChose - 1) % GAME_LINE_SIZE;
  data->fieldState[rowChosed][colChosed] = playerID;
}

int won(GameDataPtr data)
{
  FieldLines lines;
  lines = possible_field_lines(data); // structure

  for (uint8_t i = 0; i < 2 * GAME_LINE_SIZE; i++) // size4of ??? independent
  {
    if (line_filled(lines.straight[i])) // || refactor
    {
      return lines.straight[i][0];
    }
    else if (i < 2 && line_filled(lines.diagonal[i]))
    {
      return lines.diagonal[i][0]; /// change for personIDDD
    }
  }
  return 0;
}

bool line_filled(int line[GAME_LINE_SIZE])
{
  int turnID = 0;
  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    if (i == 0)
    {
      turnID = line[i];      
    }
    else if (turnID != line[i])
    {
      return false;
    }
    if (turnID == 0)
    {
      return false;
    }
  }
  return true;
}

FieldLines possible_field_lines(GameDataPtr data)
{
  FieldLines lines = {0};

  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++) // GAME_FIELD_SIZE
  {
    for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      lines.straight[i][j] = data->fieldState[i][j]; // gorizontal lines copying
    }
  }
  
  for (uint8_t i = GAME_LINE_SIZE; i < 2 * GAME_LINE_SIZE; i++)
  {
    for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      lines.straight[i][j] = data->fieldState[j][i-GAME_LINE_SIZE]; // vertical lines copying
    }
  }

  // fix in the future
  lines.diagonal[0][0] = data->fieldState[0][0];
  lines.diagonal[0][1] = data->fieldState[1][1];
  lines.diagonal[0][2] = data->fieldState[2][2];
  lines.diagonal[1][0] = data->fieldState[2][0];
  lines.diagonal[1][1] = data->fieldState[1][1];
  lines.diagonal[1][2] = data->fieldState[0][2];

  return lines;
}

bool field_full(GameDataPtr data)
{
  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      if (data->fieldState[i][j] == 0)
      {
        return false;
      }
    }
  }
  return true;
}