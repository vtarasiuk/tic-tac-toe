#include "output.h"
#include "game.h"
#include "common.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#define ERRBUF_SIZE 512
_Thread_local char last_error[ERRBUF_SIZE];

void set_last_err(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(last_error, ERRBUF_SIZE, fmt, ap);
  va_end(ap);
}

void clear_last_err()
{
  last_error[0] = '\0';
}

const char *last_err(void) {
  return (last_error[0] != '\0') ? last_error : "";
}

int main()
{
  enable_virtual_terminal_processing();

  GameData data = {0};
  int8_t playerTurn = 1;
  uint8_t winner;

  do
  {
    printf("\x1B[1;1H\x1B[2J"); // clear screen
    printf(ANSI_COLOR_MAGENTA "This is tic-tac-toe by vtarasiuk. Welcome, Honey\n\n" ANSI_COLOR_RESET);
    print_game_field(&data);

    printf(ANSI_COLOR_YELLOW "Last error: [%s]" ANSI_COLOR_RESET, last_err());

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
    if (scanf("%d", &playerChose) == 0) // after scanf add the cleaning of the stdin cause it does not make sense
    {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
    }
    printf("\x1B[1;1H\x1B[2J"); // clear screen

    if (playerChose < 1 || playerChose > 9) 
    {
      set_last_err("%s", "Entered number should be in range from 1 to 9");
      continue;
    }
    else if (!valid_turn(&data, playerChose))
    {
      set_last_err("%s", "That cell has already been played");
      continue;
    }

    clear_last_err();
    move(&data, playerTurn, playerChose);

    if (playerTurn == 1)
    {
      playerTurn = 2;
    }
    else
    {
      playerTurn = 1;
    }
  }
  while (!(winner = won(&data)) && !field_full(&data));

  print_game_field(&data);
  if (winner)
  {
    printf(ANSI_COLOR_MAGENTA "Player %d won!\n" ANSI_COLOR_RESET, winner);
  }
  else
  {
    printf(ANSI_COLOR_MAGENTA "GG, Tie!\n" ANSI_COLOR_RESET);
  }

  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  getchar();

  return 0;
}