#pragma once


#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8
#define SCREEN_SIZE 1000
#define CELL_SIZE (SCREEN_SIZE / BOARD_SIZE)




#include "raylib.h"
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include "data_types.c"





void InitBoard(PIECE(*board)[BOARD_SIZE]);
void InitTextures(Texture2D(*textures)[6]);
int DrawMenu();
void DrawPossibleMoves(int fromX, int fromY, PIECE_COLOR turn_color, PIECE(*board)[BOARD_SIZE]);
int ShowPromotionChoice(Texture2D(*textures)[6], PIECE_COLOR turn_color);
void DrawEndGameMassage(PIECE_COLOR turn);
void DrawPieces(Texture2D(*textures)[6], PIECE_TYPE type, PIECE_COLOR color, int x, int y);
void DrawBoard(PIECE(*board)[BOARD_SIZE], Texture2D(*textures)[6], int dragging, PIECE_COLOR turn, int selectedX, int selectedY, char* status_msg);
int IsOnBoard(int x, int y);
int IsPathClear(int fromX, int fromY, int toX, int toY, PIECE(*board)[BOARD_SIZE]);
int IsValidMove(int fromX, int fromY, int toX, int toY, PIECE_COLOR turnColor, PIECE(*board)[BOARD_SIZE]);;
int IsUnderAttack(int toX, int toY, PIECE_COLOR opponent_color, PIECE(*board)[BOARD_SIZE]);
int IsInCheck(PIECE_COLOR turn_color, PIECE(*board)[BOARD_SIZE]);
int CanMoveAnyPiece(PIECE_COLOR turn_color, PIECE(*board)[BOARD_SIZE]);
void CheckSpecialMoves(PIECE(*board)[BOARD_SIZE], Texture2D(*textures)[6], PIECE_COLOR turn, int selectedX, int selectedY, int x, int y, int* count_taking, int opportunity);
int CheckStatus(PIECE_COLOR turn, PIECE(*board)[BOARD_SIZE], char* status_msg);
void PlayChess(PIECE(*board)[BOARD_SIZE], Texture2D(*textures)[6]);
