#ifndef GAME_STRUCTURE_H
#define GAME_STRUCTURE_H

#define GAME_LINE_SIZE 3

typedef struct
{
    short fieldState[GAME_LINE_SIZE][GAME_LINE_SIZE]; // rename to field_state of something else
} GameData, *pGameData;
// id exchange in the future/// server implementation. // crossplatform // WebSocket
#endif
