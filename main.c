#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "output.h"
#include "game.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main()
{
  printf(ANSI_COLOR_MAGENTA "This is tic-tac-toe by vtarasiuk. Welcome, Honey\n\n" ANSI_COLOR_RESET);

  GameData data = {0};
  int8_t playerTurn = 1;
  uint8_t winner;

  print_game_field(&data);
  do
  {
    if (playerTurn == 1)
    {
      printf(ANSI_COLOR_BLUE "\nPlayer %d move:\n" ANSI_COLOR_RESET, playerTurn); 
      printf(ANSI_COLOR_BLUE "Enter your turn [1-9]: " ANSI_COLOR_RESET);
    }
    else
    {
      printf(ANSI_COLOR_RED "\nPlayer %d move:\n" ANSI_COLOR_RESET, playerTurn); 
      printf(ANSI_COLOR_RED "Enter your turn [1-9]: " ANSI_COLOR_RESET);
    }

    int playerChose = 0;
    scanf("%d", &playerChose);
    printf("\n");

    // 2\ and program die

    if (playerChose < 1 || playerChose > 9) 
    {
      fprintf(stderr, "Hella wrong choose\n");
      continue;
    }
    else if (!valid_turn(&data, playerChose))
    {
      fprintf(stderr, "Already filled, oops\n");
      continue;
    }

    move(&data, playerTurn, playerChose);

    if (playerTurn == 1)
    {
      playerTurn = 2;
    }
    else
    {
      playerTurn = 1;
    }

    print_game_field(&data);
  }
  while (!(winner = won(&data)) && !field_full(&data));

  if (winner)
  {
    printf(ANSI_COLOR_MAGENTA "Player %d won!\n" ANSI_COLOR_RESET, winner);
  }
  else
  {
    printf(ANSI_COLOR_MAGENTA "GG, Tie!\n" ANSI_COLOR_RESET);
  }

  return 0;
}