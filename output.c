#include "output.h"

void print_game_field(GameDataPtr data)
{
  for (int8_t i = 0; i < GAME_LINE_SIZE; i++)
  {
    for (int8_t j = 0; j < GAME_LINE_SIZE; j++)
    {
      char ch = '-';
      if (data->fieldState[i][j] == 1)
      {
        ch = 'X';
      }
      else if (data->fieldState[i][j] == 2)
      {
        ch = 'O';
      }

      printf("\t%c", ch);
    }
    printf("\n");
  }
  
}