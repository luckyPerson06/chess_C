#include "header.h"




int IsOnBoard(int x, int y)
{
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
}





int IsPathClear(int fromX, int fromY, int toX, int toY, PIECE(*board)[BOARD_SIZE])
{
    int dx = toX - fromX;
    int dy = toY - fromY;

    int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    int x = fromX + stepX;
    int y = fromY + stepY;

    while (x != toX || y != toY)
    {
        if (board[y][x].type != PT_NONE) return 0;
        x += stepX;
        y += stepY;
    }
    return 1;
}






int IsUnderAttack(int toX, int toY, PIECE_COLOR opponent_color, PIECE(*board)[BOARD_SIZE])
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x].type != PT_NONE && board[y][x].color == opponent_color)
            {
                if (IsValidMove(x, y, toX, toY, opponent_color, board)) return 1;
            }
        }
    }

    return 0;
}






int IsInCheck(PIECE_COLOR turn_color, PIECE(*board)[BOARD_SIZE])
{
    int kingX = 0, kingY = 0;
    PIECE_COLOR opponent_color = (turn_color == COLOR_WHITE) ? COLOR_BLACK : COLOR_WHITE;


    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x].type == PT_KING && board[y][x].color == turn_color)
            {
                kingX = x;
                kingY = y;
                break;
            }
        }
    }


    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x].type != PT_NONE && board[y][x].color == opponent_color)
            {
                if (IsValidMove(x, y, kingX, kingY, opponent_color, board)) return 1;
            }
        }
    }


    return 0;
}






int IsValidMove(int fromX, int fromY, int toX, int toY, PIECE_COLOR turn_ñolor, PIECE(*board)[BOARD_SIZE])
{
    if (!IsOnBoard(fromX, fromY) || !IsOnBoard(toX, toY)) return 0;
    if (fromX == toX && fromY == toY) return 0;


    PIECE p = board[fromY][fromX];
    PIECE target = board[toY][toX];


    if (p.type == PT_NONE) return 0;
    if (p.color != turn_ñolor) return 0;
    if (target.type != PT_NONE && target.color == turn_ñolor) return 0;


    int dx = toX - fromX;
    int dy = toY - fromY;


    switch (p.type)
    {

    case PT_PAWN:

        if (p.color == COLOR_WHITE)
        {
            if (dy == -1 && dx == 0 && target.type == PT_NONE) return 1;
            if (dy == -2 && dx == 0 && fromY == 6 && target.type == PT_NONE && board[fromY - 1][fromX].type == PT_NONE) return 1;
            if (dy == -1 && abs(dx) == 1 && target.type != PT_NONE && target.color == COLOR_BLACK) return 1;
            if (dy == -1 && abs(dx) == 1 && target.type == PT_NONE && board[toY + 1][toX].type == PT_PAWN && board[toY + 1][toX].color == COLOR_BLACK && board[toY + 1][toX].has_moved == -2) return 4;
        }
        else
        {
            if (dy == 1 && dx == 0 && target.type == PT_NONE) return 1;
            if (dy == 2 && dx == 0 && fromY == 1 && target.type == PT_NONE && board[fromY + 1][fromX].type == PT_NONE) return 1;
            if (dy == 1 && abs(dx) == 1 && target.type != PT_NONE && target.color == COLOR_WHITE) return 1;
            if (dy == 1 && abs(dx) == 1 && target.type == PT_NONE && board[toY - 1][toX].type == PT_PAWN && board[toY - 1][toX].color == COLOR_WHITE && board[toY - 1][toX].has_moved == -2) return 4;
        }

        break;


    case PT_ROOK:
        if ((dx == 0 || dy == 0) && IsPathClear(fromX, fromY, toX, toY, board)) return 1;
        break;


    case PT_KNIGHT:
        if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) return 1;
        break;

    case PT_BISHOP:
        if (abs(dx) == abs(dy) && IsPathClear(fromX, fromY, toX, toY, board)) return 1;
        break;

    case PT_QUEEN:
        if ((abs(dx) == abs(dy) || dx == 0 || dy == 0) && IsPathClear(fromX, fromY, toX, toY, board)) return 1;
        break;

    case PT_KING:
        if (abs(dx) <= 1 && abs(dy) <= 1) return 1;

        if (!p.has_moved && dy == 0)
        {
            if (dx == 2)
            {
                PIECE rook = board[fromY][fromX + 3];

                if (rook.type == PT_ROOK && !rook.has_moved && IsPathClear(fromX, fromY, toX, toY, board) && !IsUnderAttack(toX, toY, turn_ñolor == COLOR_WHITE ? COLOR_BLACK : COLOR_WHITE, board) && !IsUnderAttack(toX - 1, toY, turn_ñolor == COLOR_WHITE ? COLOR_BLACK : COLOR_WHITE, board))
                {
                    return 2;
                }
            }


            if (dx == -2)
            {
                PIECE rook = board[fromY][fromX - 4];

                if (rook.type == PT_ROOK && !rook.has_moved && IsPathClear(fromX, fromY, toX, toY, board) && !IsUnderAttack(toX, toY, turn_ñolor == COLOR_WHITE ? COLOR_BLACK : COLOR_WHITE, board) && !IsUnderAttack(toX + 1, toY, turn_ñolor == COLOR_WHITE ? COLOR_BLACK : COLOR_WHITE, board))
                {
                    return 3;
                }
            }
        }

        break;
    }

    return 0;
}







int CanMoveAnyPiece(PIECE_COLOR turn_color, PIECE(*board)[BOARD_SIZE])
{
    for (int fromY = 0; fromY < BOARD_SIZE; fromY++)
    {
        for (int fromX = 0; fromX < BOARD_SIZE; fromX++)
        {
            PIECE p = board[fromY][fromX];

            if (p.type != PT_NONE && p.color == turn_color)
            {
                for (int toY = 0; toY < BOARD_SIZE; toY++)
                {
                    for (int toX = 0; toX < BOARD_SIZE; toX++)
                    {
                        if (IsValidMove(fromX, fromY, toX, toY, turn_color, board))
                        {
                            PIECE backupFrom = board[fromY][fromX];
                            PIECE backupTo = board[toY][toX];

                            board[toY][toX] = board[fromY][fromX];
                            board[fromY][fromX] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };


                            int check = IsInCheck(turn_color, board);


                            board[fromY][fromX] = backupFrom;
                            board[toY][toX] = backupTo;

                            if (!check) return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;

}

void CheckSpecialMoves(PIECE(*board)[BOARD_SIZE], Texture2D(*textures)[6], PIECE_COLOR turn, int selectedX, int selectedY, int x, int y, int *count_taking, int opportunity)
{
    if (board[y][x].type == PT_PAWN && abs(selectedY - y) == 2)
    {
        board[y][x].has_moved = -2;
        *count_taking = 0;
    }
    else board[y][x].has_moved++;


    if (opportunity == 2)
    {
        board[selectedY][selectedX + 1] = board[selectedY][selectedX + 3];
        board[selectedY][selectedX + 3] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };
    }
    else if (opportunity == 3)
    {
        board[selectedY][selectedX - 1] = board[selectedY][selectedX - 4];
        board[selectedY][selectedX - 4] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };
    }
    else if (opportunity == 4)
    {
        if (turn == COLOR_WHITE)
        {
            board[y + 1][x] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };
        }
        else
        {
            board[y - 1][x] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };
        }

    }

    if (*count_taking == 1 || (abs(y - selectedY) == 2 && board[y][x].type == PT_PAWN))
    {
        for (int i = 3; i < 5; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j].type == PT_PAWN && board[i][j].has_moved == -2 && (i != y || j != x))
                {
                    board[i][j].has_moved++;
                }
            }
        }
    }


    (*count_taking)++;


    if (board[y][x].type == PT_PAWN && ((y == 0 && board[y][x].color == COLOR_WHITE) || (y == BOARD_SIZE - 1 && board[y][x].color == COLOR_BLACK)))
    {

        int choice = ShowPromotionChoice(textures, turn);
        board[y][x].type = choice;
    }
}




int CheckNumPiece(PIECE(*board)[BOARD_SIZE])
{
    int count = 0;

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (board[y][x].type != PT_NONE)
            {
                count++;

                if (count > 2) return 0;
            }
        }
    }

    return 1;
}




int CheckStatus(PIECE_COLOR turn, PIECE(*board)[BOARD_SIZE], char* status_msg)
{
    if (IsInCheck(turn, board))
    {
        if (!CanMoveAnyPiece(turn, board))
        {
            DrawEndGameMassage(turn == COLOR_WHITE ? COLOR_BLACK : COLOR_WHITE);
            return 1;
        }
        else
        {
            strcpy(status_msg, "Check!");
        }
    }
    else if (!CanMoveAnyPiece(turn, board) || CheckNumPiece(board))
    {
        DrawEndGameMassage(COLOR_NONE);
        return 1;
    }

    return 0;
}







void PlayChess(PIECE(*board)[BOARD_SIZE], Texture2D(*textures)[6])
{
    int selectedX = -1, selectedY = -1, dragging = 0, count_taking = 0;
    PIECE_COLOR turn = COLOR_WHITE;
    char status_msg[64] = "";


    while (!WindowShouldClose())
    {

        Vector2 mouse = GetMousePosition();
        int x = (int)(mouse.x / CELL_SIZE);
        int y = (int)(mouse.y / CELL_SIZE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {

            if (IsOnBoard(x, y))
            {

                if (!dragging && board[y][x].type != PT_NONE && board[y][x].color == turn)
                {
                    selectedX = x;
                    selectedY = y;
                    dragging = 1;
                    status_msg[0] = '\0';
                }
                else if (dragging)
                {
                    int opportunity = IsValidMove(selectedX, selectedY, x, y, turn, board);

                    if (opportunity)
                    {

                        PIECE moved_piece = board[selectedY][selectedX];
                        PIECE target_piece = board[y][x];

                        board[y][x] = board[selectedY][selectedX];
                        board[selectedY][selectedX] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };


                        if (IsInCheck(turn, board))
                        {
                            board[selectedY][selectedX] = moved_piece;
                            board[y][x] = target_piece;
                            strcpy(status_msg, "Move puts king in check!");
                        }
                        else
                        {

                            moved_piece.has_moved++;
                            CheckSpecialMoves(board, textures, turn, selectedX, selectedY, x, y, &count_taking, opportunity);


                            turn = (turn == COLOR_WHITE) ? COLOR_BLACK : COLOR_WHITE;
                            status_msg[0] = '\0';


                            if(CheckStatus(turn, board, status_msg)) break;
                        }
                    }
                    else
                    {
                        strcpy(status_msg, "Invalid move");
                    }

                    dragging = 0;
                    selectedX = -1;
                    selectedY = -1;

                }

            }
        }

        DrawBoard(board, textures, dragging, turn, selectedX, selectedY, status_msg);

    }
}