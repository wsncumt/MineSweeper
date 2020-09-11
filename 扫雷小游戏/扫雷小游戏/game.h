#pragma once
//头文件引用
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef __GAME_H__
#define __GAME_H__

//常量定义区
#define EASY_CONST 10
#define COL 9
#define ROW 9
#define COLS COL+2
#define ROWS ROW+2

//函数声明
void menu();
void game();
void InitBoard(char board[ROWS][COLS], int cols,int rows, char set);
void DisplayBoard(const char board[ROWS][COLS], int cols, int rows);
void SetMine(char board[ROWS][COLS], int col, int row);
void FindMine(const char mineboard[ROWS][COLS], char showboard[ROWS][COLS],int col,int row);
int GetMineCount(const char mineboard[ROWS][COLS], int x, int y);
void OpenMine(const char mineboard[ROWS][COLS], char showboard[ROWS][COLS], int col, int row, int x, int y);
void First_SafeMine(char mineboard[ROWS][COLS], char showboard[ROWS][COLS], int row, int col);
int TrueMineCount(const char mineboard[ROWS][COLS], const char showboard[ROWS][COLS], int cols, int rows, int* pcount);
int Countmine(char showboard[ROWS][COLS], int col, int row);
#endif