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
  uint8_t playerTurn = 1;
  uint8_t winner = 0;

  while ( !(winner = GameWinner(&data)) && !GameFieldFull(&data) )
  {
    PrintGameField(&data);

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

    int player_move = 0;
    scanf("%d", &player_move);
    printf("\n");

    // 2\ and program die (Not a Number) possible solution: int[] and cast to char at the end

    if (player_move < 1 || player_move > 9) 
    {
      fprintf(stderr, "Hella wrong choose\n\n");
      continue;
    }
    else if (!ValidTurn(&data, player_move)) // add check for the valid range
    {
      fprintf(stderr, "Already filled, oops\n\n");
      continue;
    }

    Move(&data, playerTurn, player_move);

    if (playerTurn == 1)
    {
      playerTurn = 2;
    }
    else
    {
      playerTurn = 1;
    }
  }

  PrintGameField(&data);

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