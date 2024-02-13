#include "game.h"
#include <stdio.h>

#define CHECK_FUNCTIONS 3

typedef short (*GameFieldCheckFunction) (pGameData);

static bool EqualFieldValues(short *values);
static short CheckHorizontalValues(pGameData data);
static short CheckVerticalValues(pGameData data);
static short CheckDiagonalValues(pGameData data);


bool GameValidTurn(pGameData data, uint8_t move)
{
  uint8_t rowChosed = (move - 1) / GAME_LINE_SIZE;
  uint8_t colChosed = (move - 1) % GAME_LINE_SIZE;

  if (data->fieldState[rowChosed][colChosed] == 0)
  {
    return true;
  }
  return false;
}

void GameMove(pGameData data, uint8_t player_id, uint8_t move)
{
  uint8_t rowChosed = (move - 1) / GAME_LINE_SIZE;
  uint8_t colChosed = (move - 1) % GAME_LINE_SIZE;
  data->fieldState[rowChosed][colChosed] = player_id;
}

short GameWinner(pGameData data)
{
  // Check functions
  GameFieldCheckFunction check_functions[CHECK_FUNCTIONS] = { CheckHorizontalValues, CheckVerticalValues, CheckDiagonalValues };
  short winner;
  
  // Get a winner or 0
  for (uint8_t i = 0; i < CHECK_FUNCTIONS; i++)
  {
    winner = check_functions[i](data);
    if (winner != 0)
    {
      return winner;
    }
  }
  
  return 0;
}

static bool EqualFieldValues(short *values)
{
  // Equality check for all values
  short first_value = values[0];
  for (uint8_t i = 1; i < GAME_LINE_SIZE; i++)
  {
    if (first_value != values[i])
    {
      return false;
    }
  }
  return true;
}

static short CheckHorizontalValues(pGameData data)
{
  short line[GAME_LINE_SIZE] = {0};
  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      // Copy line
      line[j] = data->fieldState[i][j];
    }

    // Values are equal
    if (EqualFieldValues(line))
    {
      return line[0];      // Winner
    }
  }
  
  // Values are NOT equal
  return 0;
}

static short CheckVerticalValues(pGameData data)
{
  short line[GAME_LINE_SIZE] = {0};
  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      // Copy line
      line[j] = data->fieldState[j][i];
    }

    // Values are equal
    if (EqualFieldValues(line))
    {
      return line[0];     // Winner
    }
  }
  
  // Values are NOT equal
  return 0;
}

static short CheckDiagonalValues(pGameData data)
{
  short line[GAME_LINE_SIZE] = {0};
  // Main diagonal
  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    line[i] = data->fieldState[i][i];
  }

  // Values are equal
  if (EqualFieldValues(line))
  {
    return line[0];     // Winner
  }

  // Side diagonal
  const short expected_sum = GAME_LINE_SIZE - 1;
  for (uint8_t row = 0; row < GAME_LINE_SIZE; row++)
  {
    uint8_t col = expected_sum - row;
    line[row] = data->fieldState[row][col];
  }
  
  // Values are equal
  if (EqualFieldValues(line))
  {
    return line[0];     // Winner
  }

  // Values are NOT equal
  return 0;
}

bool GameFieldFull(pGameData data)
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