#include "output.h"
#include "game.h"
#include "common.h"
#include "error.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    if (enableVirtualTerminalProcessing() == EOF)
    {
        fprintf(stderr, "Error: could not enable virtual terminal processing\n");
        getchar();
        return EXIT_FAILURE;
    }

    GameData data = {0};
    bool playerTurn = 0; 
    uint8_t winner; // boolean instead, remove stdint

    do
    {
        printf("\x1B[1;1H\x1B[2J"); // clear screen
        printf(ANSI_COLOR_MAGENTA "This is tic-tac-toe by vtarasiuk. Welcome, Honey\n\n" ANSI_COLOR_RESET);
        printGameField(&data);

        printf(ANSI_COLOR_YELLOW "Last error: [%s]" ANSI_COLOR_RESET, getLastErr());

        if (playerTurn) // make the function that takes a color parameter and the text.
        {
            printf(ANSI_COLOR_BLUE "\nPlayer %d move:\n" ANSI_COLOR_RESET, playerTurn + 1);
            printf(ANSI_COLOR_BLUE "Enter your turn [1-9]: " ANSI_COLOR_RESET);
        }
        else
        {
            printf(ANSI_COLOR_RED "\nPlayer %d move:\n" ANSI_COLOR_RESET, playerTurn + 1);
            printf(ANSI_COLOR_RED "Enter your turn [1-9]: " ANSI_COLOR_RESET);
        }

        int playerChose = 0;
        scanf("%d", &playerChose);
        discardInputStream();
        printf("\x1B[1;1H\x1B[2J"); // clear screen

        if (playerChose < 1 || playerChose > 9)
        {
            setLastErr("%s", "Entered number should be in range from 1 to 9");
            continue;
        }
        else if (!validTurn(&data, playerChose))
        {
            setLastErr("%s", "That cell has already been played");
            continue;
        }

        clearLastErr();
        makeTurn(&data, playerTurn + 1, playerChose);

        playerTurn = !playerTurn;
    } while (!(winner = won(&data)) && !gridFull(&data));

    printGameField(&data);
    if (winner)
    {
        printf(ANSI_COLOR_MAGENTA "Player %d won!\n" ANSI_COLOR_RESET, winner);
    }
    else
    {
        printf(ANSI_COLOR_MAGENTA "GG, Tie!\n" ANSI_COLOR_RESET);
    }

    discardInputStream();
    getchar();

    return 0;
}