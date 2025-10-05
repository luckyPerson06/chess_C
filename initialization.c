#include "header.h"


void InitBoard(PIECE(*board)[BOARD_SIZE])
{
    for (int y = 1; y < BOARD_SIZE - 1; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (y == 1)
            {
                board[y][x] = (PIECE){ PT_PAWN, COLOR_BLACK, 0, 0 };

            }
            else if (y == BOARD_SIZE - 2)
            {
                board[y][x] = (PIECE){ PT_PAWN, COLOR_WHITE, 0, 0 };
            }
            else
            {
                board[y][x] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };
            }
        }
    }



    board[0][0] = (PIECE){ PT_ROOK, COLOR_BLACK, 0, 0 };
    board[0][1] = (PIECE){ PT_KNIGHT, COLOR_BLACK,0, 0 };
    board[0][2] = (PIECE){ PT_BISHOP, COLOR_BLACK, 0, 0 };
    board[0][3] = (PIECE){ PT_QUEEN, COLOR_BLACK, 0, 0 };
    board[0][4] = (PIECE){ PT_KING, COLOR_BLACK, 0, 0 };
    board[0][5] = (PIECE){ PT_BISHOP, COLOR_BLACK, 0, 0 };
    board[0][6] = (PIECE){ PT_KNIGHT, COLOR_BLACK, 0, 0 };
    board[0][7] = (PIECE){ PT_ROOK, COLOR_BLACK, 0, 0 };



    board[7][0] = (PIECE){ PT_ROOK, COLOR_WHITE, 0, 0 };
    board[7][1] = (PIECE){ PT_KNIGHT, COLOR_WHITE, 0, 0 };
    board[7][2] = (PIECE){ PT_BISHOP, COLOR_WHITE, 0, 0 };
    board[7][3] = (PIECE){ PT_QUEEN, COLOR_WHITE, 0, 0 };
    board[7][4] = (PIECE){ PT_KING, COLOR_WHITE, 0, 0 };
    board[7][5] = (PIECE){ PT_BISHOP, COLOR_WHITE, 0, 0 };
    board[7][6] = (PIECE){ PT_KNIGHT, COLOR_WHITE, 0, 0 };
    board[7][7] = (PIECE){ PT_ROOK, COLOR_WHITE, 0, 0 };

}




void InitTextures(Texture2D(*textures)[6])
{
    textures[COLOR_WHITE][PT_PAWN] = LoadTexture("wp.png");
    textures[COLOR_WHITE][PT_ROOK] = LoadTexture("wr.png");
    textures[COLOR_WHITE][PT_KNIGHT] = LoadTexture("wn.png");
    textures[COLOR_WHITE][PT_BISHOP] = LoadTexture("wb.png");
    textures[COLOR_WHITE][PT_QUEEN] = LoadTexture("wq.png");
    textures[COLOR_WHITE][PT_KING] = LoadTexture("wk.png");


    textures[COLOR_BLACK][PT_PAWN] = LoadTexture("bp.png");
    textures[COLOR_BLACK][PT_ROOK] = LoadTexture("br.png");
    textures[COLOR_BLACK][PT_KNIGHT] = LoadTexture("bn.png");
    textures[COLOR_BLACK][PT_BISHOP] = LoadTexture("bb.png");
    textures[COLOR_BLACK][PT_QUEEN] = LoadTexture("bq.png");
    textures[COLOR_BLACK][PT_KING] = LoadTexture("bk.png");

}