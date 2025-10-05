#include "header.h"




int DrawMenu()
{
    int choice = -1;

    while (choice == -1 && !WindowShouldClose())
    {
        BeginDrawing();


        for (int y = 0; y < BOARD_SIZE; y++)
        {
            for (int x = 0; x < BOARD_SIZE; x++)
            {
                int flag_color = (x + y) % 2;
                Color c = (flag_color == 0) ? (Color) { 240, 217, 181, 255 } : (Color) { 181, 136, 99, 255 };
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, c);
            }
        }


        DrawRectangle(250, 250, 500, 375, DARKGRAY);
        DrawText("MENU", 320, 250, 125, (Color) { 240, 217, 181, 255 });
        DrawText("  PLAY", 320, 400, 80, (Color) { 240, 217, 181, 255 });
        DrawText("  EXIT", 320, 525, 80, (Color) { 240, 217, 181, 255 });


        EndDrawing();

        Vector2 pos_play = { 320, 400 };
        Vector2 pos_exit = { 320, 525 };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse = GetMousePosition();

            Rectangle rect_play = { pos_play.x, pos_play.y, CELL_SIZE * 2, CELL_SIZE };
            Rectangle rect_exit = { pos_exit.x, pos_exit.y, CELL_SIZE * 2, CELL_SIZE };

            if (CheckCollisionPointRec(mouse, rect_play)) return 1;
            else if (CheckCollisionPointRec(mouse, rect_exit)) return 0;
        }
    }

    return choice;
}





void DrawPossibleMoves(int fromX, int fromY, PIECE_COLOR turn_color, PIECE(*board)[BOARD_SIZE])
{
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (IsValidMove(fromX, fromY, x, y, turn_color, board))
            {

                PIECE moved_piece = board[fromY][fromX];
                PIECE target_piece = board[y][x];

                board[y][x] = board[fromY][fromX];
                board[fromY][fromX] = (PIECE){ PT_NONE, COLOR_NONE, 0, 0 };


                if (IsInCheck(turn_color, board))
                {
                    board[fromY][fromX] = moved_piece;
                    board[y][x] = target_piece;
                }
                else
                {
                    for (int i = 0; i < 5; i++)
                    {
                        board[fromY][fromX] = moved_piece;
                        board[y][x] = target_piece;
                        DrawLine(x * CELL_SIZE + i, y * CELL_SIZE, x * CELL_SIZE + i, (y + 1) * CELL_SIZE, GREEN);
                        DrawLine((x + 1) * CELL_SIZE - i, y * CELL_SIZE, (x + 1) * CELL_SIZE - i, (y + 1) * CELL_SIZE, GREEN);
                        DrawLine(x * CELL_SIZE, y * CELL_SIZE + i, (x + 1) * CELL_SIZE, y * CELL_SIZE + i, GREEN);
                        DrawLine(x * CELL_SIZE, (y + 1) * CELL_SIZE - i, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE - i, GREEN);
                    }
                }

            }
        }
    }
}






int ShowPromotionChoice(Texture2D(*textures)[6], PIECE_COLOR turn_color)
{
    int choice = -1;

    while (choice == -1)
    {
        BeginDrawing();


        DrawRectangle(250, 375, 500, 250, DARKGRAY);
        DrawText("Choice piece ", 345, 425, 50, GREEN);


        Vector2* pos = malloc(sizeof(Vector2) * 4);

        pos[0] = (Vector2){ 2 * CELL_SIZE + 10, 4 * CELL_SIZE + 10 };
        pos[1] = (Vector2){ 3 * CELL_SIZE + 10, 4 * CELL_SIZE + 10 };
        pos[2] = (Vector2){ 4 * CELL_SIZE + 10, 4 * CELL_SIZE + 10 };
        pos[3] = (Vector2){ 5 * CELL_SIZE + 10, 4 * CELL_SIZE + 10 };


        if (turn_color == COLOR_WHITE)
        {
            DrawTextureEx(textures[COLOR_WHITE][PT_ROOK], pos[0], 0, 0.7, WHITE);
            DrawTextureEx(textures[COLOR_WHITE][PT_KNIGHT], pos[1], 0, 0.7, WHITE);
            DrawTextureEx(textures[COLOR_WHITE][PT_BISHOP], pos[2], 0, 0.7, WHITE);
            DrawTextureEx(textures[COLOR_WHITE][PT_QUEEN], pos[3], 0, 0.7, WHITE);
        }
        else
        {
            DrawTextureEx(textures[COLOR_BLACK][PT_ROOK], pos[0], 0, 0.7, WHITE);
            DrawTextureEx(textures[COLOR_BLACK][PT_KNIGHT], pos[1], 0, 0.7, WHITE);
            DrawTextureEx(textures[COLOR_BLACK][PT_BISHOP], pos[2], 0, 0.7, WHITE);
            DrawTextureEx(textures[COLOR_BLACK][PT_QUEEN], pos[3], 0, 0.7, WHITE);
        }


        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse = GetMousePosition();

            for (int i = 0; i < 4; i++)
            {
                Rectangle rect = { pos[i].x, pos[i].y, CELL_SIZE * 0.7, CELL_SIZE * 0.7 };

                if (CheckCollisionPointRec(mouse, rect))
                {
                    switch (i)
                    {
                    case 0: choice = PT_ROOK; break;

                    case 1: choice = PT_KNIGHT; break;

                    case 2: choice = PT_BISHOP; break;

                    case 3: choice = PT_QUEEN; break;
                    }
                    break;
                }
            }
            free(pos);
        }
    }

    return choice;
}





void DrawEndGameMassage(PIECE_COLOR turn)
{
    Texture2D win_msg = LoadTexture("win.png");
    Vector2 pos = { 125, 125 };
    double start_time = GetTime();


    while (GetTime() - start_time <= 5 && !WindowShouldClose())
    {
        BeginDrawing();
        DrawTextureEx(win_msg, pos, 0, 1, WHITE);

        if (turn == COLOR_WHITE)
        {
            DrawText("Checkmate!\n White win!", 345, 425, 50, GREEN);
        }
        else if (turn == COLOR_BLACK)
        {
            DrawText("Checkmate!\n Black win!", 345, 425, 50, RED);
        }
        else
        {
            DrawText("   Draw!", 345, 425, 50, GRAY);
        }
        EndDrawing();
    }
}





void DrawPieces(Texture2D(*textures)[6], PIECE_TYPE type, PIECE_COLOR color, int x, int y)
{
    if (type == PT_PAWN)
    {
        Vector2 pos = { x * CELL_SIZE + 10, y * CELL_SIZE + 10 };
        DrawTextureEx(textures[color][PT_PAWN], pos, 0, 0.7, WHITE);
    }
    else if (type == PT_ROOK)
    {
        Vector2 pos = { x * CELL_SIZE + 10, y * CELL_SIZE + 10 };
        DrawTextureEx(textures[color][PT_ROOK], pos, 0, 0.7, WHITE);
    }
    else if (type == PT_KNIGHT)
    {
        Vector2 pos = { x * CELL_SIZE + 10, y * CELL_SIZE + 10 };
        DrawTextureEx(textures[color][PT_KNIGHT], pos, 0, 0.7, WHITE);
    }
    else if (type == PT_BISHOP)
    {
        Vector2 pos = { x * CELL_SIZE + 10, y * CELL_SIZE + 10 };
        DrawTextureEx(textures[color][PT_BISHOP], pos, 0, 0.7, WHITE);
    }
    else if (type == PT_QUEEN)
    {
        Vector2 pos = { x * CELL_SIZE + 10, y * CELL_SIZE + 10 };
        DrawTextureEx(textures[color][PT_QUEEN], pos, 0, 0.7, WHITE);
    }
    else
    {
        Vector2 pos = { x * CELL_SIZE + 10, y * CELL_SIZE + 10 };
        DrawTextureEx(textures[color][PT_KING], pos, 0, 0.7, WHITE);
    }
}





void DrawBoard(PIECE(*board)[BOARD_SIZE], Texture2D(*textures)[6], int dragging, PIECE_COLOR turn, int selectedX, int selectedY, char* status_msg)
{
    BeginDrawing();


    ClearBackground(RAYWHITE);

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            int flag_color = (x + y) % 2;
            Color c = (flag_color == 0) ? (Color) { 240, 217, 181, 255 } : (Color) { 181, 136, 99, 255 };


            DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, c);


            if (board[y][x].type != PT_NONE && board[y][x].color == COLOR_BLACK)
            {
                DrawPieces(textures, board[y][x].type, COLOR_BLACK, x, y);
            }
            else if (board[y][x].type != PT_NONE)
            {
                DrawPieces(textures, board[y][x].type, COLOR_WHITE, x, y);
            }
        }
    }



    if (dragging && IsOnBoard(selectedX, selectedY))
    {

        for (int i = 0; i < 5; i++)
        {
            DrawLine(selectedX * CELL_SIZE + i, selectedY * CELL_SIZE, selectedX * CELL_SIZE + i, (selectedY + 1) * CELL_SIZE, RED);
            DrawLine((selectedX + 1) * CELL_SIZE - i, selectedY * CELL_SIZE, (selectedX + 1) * CELL_SIZE - i, (selectedY + 1) * CELL_SIZE, RED);
            DrawLine(selectedX * CELL_SIZE, selectedY * CELL_SIZE + i, (selectedX + 1) * CELL_SIZE, selectedY * CELL_SIZE + i, RED);
            DrawLine(selectedX * CELL_SIZE, (selectedY + 1) * CELL_SIZE - i, (selectedX + 1) * CELL_SIZE, (selectedY + 1) * CELL_SIZE - i, RED);
        }

        DrawPossibleMoves(selectedX, selectedY, turn, board);

    }


    DrawText(status_msg, 10, 0, 25, RED);


    EndDrawing();
}