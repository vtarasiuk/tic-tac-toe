#include "game.h"

static bool equalFieldValues(short *values);
static short checkHorizontalValues(pGameData data);
static short checkVerticalValues(pGameData data);
static short checkDiagonalValues(pGameData data);

bool validTurn(pGameData data, uint8_t playerChose)
{
    uint8_t rowChosed = (playerChose - 1) / GAME_LINE_SIZE;
    uint8_t colChosed = (playerChose - 1) % GAME_LINE_SIZE;

    return data->grid[rowChosed][colChosed] == 0;
}

void makeTurn(pGameData data, uint8_t playerID, uint8_t playerChose)
{
    uint8_t rowChosed = (playerChose - 1) / GAME_LINE_SIZE;
    uint8_t colChosed = (playerChose - 1) % GAME_LINE_SIZE;
    data->grid[rowChosed][colChosed] = playerID;
}

short won(pGameData data)
{
    GameFieldCheckFunction check_functions[CHECK_FUNCTIONS] = {checkHorizontalValues, checkVerticalValues, checkDiagonalValues};
    short winner;

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

static bool equalFieldValues(short *values)
{
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

static short checkHorizontalValues(pGameData data)
{
    short line[GAME_LINE_SIZE] = {0};
    for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
    {
        for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
        {
            line[j] = data->grid[i][j];
        }

        // Values are equal
        if (equalFieldValues(line))
        {
            return line[0];
        }
    }
    // Values are NOT equal
    return 0;
}

static short checkVerticalValues(pGameData data)
{
    short line[GAME_LINE_SIZE] = {0};
    for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
    {
        for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
        {
            line[j] = data->grid[j][i];
        }

        // Values are equal
        if (equalFieldValues(line))
        {
            return line[0];
        }
    }
    // Values are NOT equal
    return 0;
}

static short checkDiagonalValues(pGameData data)
{
    short line[GAME_LINE_SIZE] = {0};
    // Main diagonal
    for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
    {
        line[i] = data->grid[i][i];
    }
    // Values are equal
    if (equalFieldValues(line))
    {
        return line[0];
    }

    // Side diagonal
    const short expected_sum = GAME_LINE_SIZE - 1;
    for (uint8_t row = 0; row < GAME_LINE_SIZE; row++)
    {
        uint8_t col = expected_sum - row;
        line[row] = data->grid[row][col];
    }
    // Values are equal
    if (equalFieldValues(line))
    {
        return line[0];
    }
    // Values are NOT equal
    return 0;
}

bool gridFull(pGameData data)
{
    for (uint8_t i = 0; i < GAME_LINE_SIZE; i++)
    {
        for (uint8_t j = 0; j < GAME_LINE_SIZE; j++)
        {
            if (data->grid[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}