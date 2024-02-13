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
  bool player_turn = 0; // need to randomize
  uint8_t winner = 0;
  // turns_count

  while ( !(winner = GameWinner(&data)) && !GameFieldFull(&data) )
  {
    PrintGameField(&data);

    if (player_turn)
    {
      printf(ANSI_COLOR_BLUE "\nPlayer %d move:\n" ANSI_COLOR_RESET, player_turn + 1); 
      printf(ANSI_COLOR_BLUE "Enter your turn [1-9]: " ANSI_COLOR_RESET);
    }
    else
    {
      printf(ANSI_COLOR_RED "\nPlayer %d move:\n" ANSI_COLOR_RESET, player_turn + 1); 
      printf(ANSI_COLOR_RED "Enter your turn [1-9]: " ANSI_COLOR_RESET);
    }

    int player_move = 0;
    scanf("%d", &player_move);
    printf("\n");

    // Clear stdin
    int discard;
    while ((discard = getchar()) != '\n' && discard != EOF);

    // check NaN values

    if (player_move < 1 || player_move > 9) 
    {
      fprintf(stderr, "Hella wrong choose\n\n");
      continue;
    }
    else if (!GameValidTurn(&data, player_move)) // add check for the valid range
    {
      fprintf(stderr, "Already filled, oops\n\n");
      continue;
    }

    GameMove(&data, player_turn + 1, player_move); // make player_id

    player_turn = !player_turn;
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