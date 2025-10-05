#include "header.h"


int main()
{
    PIECE board[BOARD_SIZE][BOARD_SIZE];
    Texture2D textures[2][6];


    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "Chess");
    SetTargetFPS(60);
    SetTraceLogLevel(LOG_ERROR);
    

    InitBoard(board);
    InitTextures(textures);


    if (!DrawMenu()) return 0;
    else PlayChess(board, textures);

    return 0;
}