#include "output.h"
#include <stdio.h>
#include <stdint.h>

#define OUTPUT_DEVICE stdout

void PrintGameField(pGameData data)
{
  for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      char ch = '-';
      if (data->fieldState[i][j] == PLAYER_1_VALUE)
      {
        ch = 'X';
      }
      else if (data->fieldState[i][j] == PLAYER_2_VALUE)
      {
        ch = 'O';
      }

      fprintf(OUTPUT_DEVICE, "\t%c", ch);
    }
    fprintf(OUTPUT_DEVICE, "\n");
  }
}