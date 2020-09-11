#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

//菜单
void menu()
{
	printf("********************\n");
	printf("*1.play******0.exit*\n");
	printf("********************\n");
}

//初始化棋盘
void InitBoard(char board[ROWS][COLS], int cols, int rows, char set)
{
	int i, j;
	for (i = 0; i < cols; i++)
	{
		for (j = 0; j < rows; j++)
		{
			board[i][j] = set;
		}
	}
}

//显示棋盘
void DisplayBoard(char board[ROWS][COLS], int col, int row)
{
	int i, j;
	printf("    ");
	for (j = 1; j <= col; j++)
	{
		printf("%d ", j);
	}
	printf("\n\n");
	for (i = 1; i <= col; i++)
	{
		printf("%d   ",i);
		for (j = 1; j <= row; j++)
		{
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
}

//初始化地雷的位置
void SetMine(char board[ROWS][COLS], int col, int row)
{
	int x, y;
	int count = EASY_CONST;
	while (count)
	{
		x = rand() % col + 1;
		y = rand() % row + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}
//保证第一个不踩雷
void First_SafeMine(char mineboard[ROWS][COLS], char showboard[ROWS][COLS], int row, int col)//确保第一个不踩雷
{
	int x = 0;
	int y = 0;
	int ret = 1;
	int count = 0;
	int a, b;
	printf("请输入要排查的坐标:");
	scanf("%d%d", &x, &y);
	if (mineboard[x][y] == '1')//如果为雷，则改为没有雷
	{
		mineboard[x][y] = '0';
		while (ret)//随机生成一个雷
		{
			a = rand() % ROW + 1;
			b = rand() % COL + 1;
			if (mineboard[a][b] == '0')
			{
				mineboard[a][b] = '1';
			}
			ret--;
		}
	}
	count = GetMineCount(mineboard, x, y);
	showboard[x][y] = count + '0';
	OpenMine(mineboard, showboard, row, col, x, y);
	DisplayBoard(showboard, row, col);
}
//统计坐标周围雷的个数
int GetMineCount(const char mineboard[ROWS][COLS], int x, int y)
{
	return mineboard[x - 1][y + 1] + mineboard[x][y + 1] + mineboard[x + 1][y + 1] +
		mineboard[x - 1][y] + mineboard[x + 1][y] +
		mineboard[x - 1][y - 1] + mineboard[x][y - 1] + mineboard[x + 1][y - 1] - 8 * '0';
}

//展开无雷区：如果该坐标周围没有雷就自动展开。
void OpenMine(const char mineboard[ROWS][COLS], char showboard[ROWS][COLS], int col, int row,int x,int y)
{
	int ret = 0;
	ret=GetMineCount(mineboard, x, y);
	if (ret == 0)
	{
		showboard[x][y] = ' ';
		if (x > 0 && y + 1 <= col && showboard[x][y + 1] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x, y + 1);
		}
		if (x - 1 > 0 && y + 1 <= col && showboard[x - 1][y + 1] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x - 1, y + 1);
		}
		if (x - 1 > 0 && y >0 && showboard[x - 1][y] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x - 1, y);
		}
		if (x - 1 > 0 && y - 1 >0 && showboard[x - 1][y - 1] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x - 1, y - 1);
		}
		if (x > 0 && y - 1 > 0 && showboard[x][y - 1] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x, y - 1);
		}
		if (x + 1 <= row && y - 1 > 0 && showboard[x + 1][y - 1] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x + 1, y - 1);
		}
		if (x + 1 <= row && y > 0 && showboard[x + 1][y] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x + 1, y);
		}
		if (x + 1 <=row && y + 1 <= col && showboard[x + 1][y + 1] == '*')
		{
			OpenMine(mineboard, showboard, col, row, x + 1, y + 1);
		}
	}
	else
	{
		showboard[x][y] = '0' + ret;
	}
}

////统计棋盘上旗子的个数
//int FlagCount(const char showboard[ROWS][COLS], int cols, int rows)
//{
//	int i, j;
//	int count = 0;
//	for (i = 0; i < cols; i++)
//	{
//		for (j = 0; j < rows; j++)
//		{
//			if (showboard[i][j] == '#')
//			{
//				count++;
//			}
//		}
//	}
//	return count;
//}

//统计棋盘上旗子下对应的真雷个数
int TrueMineCount(const char mineboard[ROWS][COLS],const char showboard[ROWS][COLS], int cols, int rows,int* pcount)
{
	int i, j;
	int count = 0;
	if (*pcount > 0)
	{
		for (i = 0; i < cols; i++)
		{
			for (j = 0; j < rows; j++)
			{
				if (showboard[i][j] == '#')
				{
					if (mineboard[i][j] == '1')
					{
						count++;
					}
				}
			}
		}
	}
	return count;
}
//统计棋盘上已排除的区域
int Countmine(char showboard[ROWS][COLS],int col ,int row)
{
	int i,j;
	int check;
	int win = col * row - EASY_CONST;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= row; j++)
		{
			check = showboard[i][j] - '0';
			if (showboard[i][j] == ' ' || (check > 0 && check < 9))
			{
				win--;
			}
		}
	}
	return win;
}

//排雷
void FindMine(const char mineboard[ROWS][COLS], char showboard[ROWS][COLS], int col, int row)
{
	int x = 0;
	int y = 0;
	int win = 0;
	char input1;
	int bool = 1;
	int ret_trueminecount = 0;
	int flag_count = 0;
	do
	{
		//ret_trueminecount = TrueMineCount(mineboard, showboard, COLS, ROWS,&flag_count);
		printf("请选择（输入a,b或c）：\n");
		printf("a.排雷 b.插旗 c.取消插旗\n");
		//scanf("%s", &input1);
		input1 = getchar();
		switch (input1)
		{
		case 'a':
		{
			printf("请输入要检查的坐标:>\n");
			int bool0 = 1;
			while (bool0) 
			{
				scanf("%d %d", &x, &y);
				if (x > 0 && x <= row && y > 0 && y <= col)
				{
					if (showboard[x][y] != '*')
					{
						if (showboard[x][y] == '#')
						{
							printf("此处有旗子，请拔掉后再排查。\n");
						}
						else
						{
							printf("\n此处已经排查过了，请重新输入。\n");
						}
					}
					else if (mineboard[x][y] == '1')
					{
						printf("\n很遗憾，你踩到了地雷，游戏结束！\n");
						DisplayBoard(mineboard, col, row);
						bool = 0;
						break;
					}
					else
					{
						int count = GetMineCount(mineboard, x, y);
						if (0 == count)
						{
							OpenMine(mineboard, showboard, COL, ROW, x, y);
							bool0 = 0;
							int ret_win = Countmine(showboard, COL, ROW);
							if (ret_win == 0)
							{
								bool = 0;
								win = 1;
								break;
							}
						}
						else
						{
							showboard[x][y] = count + '0';
							int ret_win = Countmine(showboard, COL, ROW);
							bool0 = 0;
							if (ret_win == 0)
							{
								bool = 0;
								win = 1;
								break;
							}
						}
						DisplayBoard(showboard, COL, ROW);
					}
				}
				else
				{
					printf("\n您输入的坐标有误，请重新输入\n");
				}
			}
			break;
		}
		case 'b':
		{
			int bool1 = 1;
			while (bool1)
			{
				printf("请输入要插旗的坐标:>");
				scanf("%d %d", &x, &y);
				if (x > 0 && x <= row && y > 0 && y <= col)
				{
					if (showboard[x][y] == '*')
					{
						showboard[x][y] = '#';
						flag_count++;
						bool1 = 0;
						ret_trueminecount = TrueMineCount(mineboard, showboard, COLS, ROWS, &flag_count);
						if (flag_count==EASY_CONST && ret_trueminecount == EASY_CONST)
						{
							bool = 0;
							win = 1;
						}
					}
					else
					{
						printf("此处无法放置旗子。请按下列情况进行检查：\n(1)坐标是否有误；\n(2)此处已经有旗子；\n(3)此处是否已经排查过了。\n");
					}
				}
				else
				{
					printf("输入的坐标有误，请重新输入。\n");
				}
			}
			DisplayBoard(showboard, COL, ROW);
			break;
		}
		case 'c':
		{
			int bool2 = 1;
			int ret = FlagCount(showboard, COLS, ROWS);
			while (bool2)
			{
				if (ret == 0)
				{
					printf("\n棋盘上没有旗子；请选择排雷或插旗。\n");
					bool2 = 0;
				}
				else
				{
					printf("\n请输入要拔旗的坐标:>");
					scanf("%d %d", &x, &y);
					if (x > 0 && x <= row && y > 0 && y <= col)
					{
						if (showboard[x][y] == '#')
						{
							showboard[x][y] = '*';
							flag_count--;
							bool2 = 0;
							ret_trueminecount = TrueMineCount(mineboard, showboard, COLS, ROWS, &flag_count);
							if (flag_count == EASY_CONST && ret_trueminecount == EASY_CONST)
							{
								bool = 0;
								win = 1;
							}
						}
						else
						{
							printf("\n此处无法移除旗子。请按下列情况进行检查：\n(1)坐标是否有误；\n(2)此处没有旗子；\n(3)此处旗子是否已经拔掉。\n");
						}
					}
					else
					{
						printf("输入的坐标有误，请重新输入。\n");
					}
				}
			}
			DisplayBoard(showboard, COL, ROW);
			break;
			}
		}
		if (win == 1)
		{
			printf("恭喜你，你已排出全部的雷。\n");
			bool = 0;
			DisplayBoard(mineboard,COL,ROW);
		}
	}while ( bool == 1);
}

void game()
{
	//存储雷的位置:生成两个棋盘，一个用于打印
	char mineboard[COLS][ROWS] ;
	char showboard[COLS][ROWS];

	//初始化棋盘
	InitBoard(mineboard, COLS, ROWS, '0');
	InitBoard(showboard, COLS, ROWS, '*');

	//显示棋盘
	//DisplayBoard(mineboard, COL, ROW);
	DisplayBoard(showboard, COL, ROW);

	//布置雷
	SetMine(mineboard,COL,ROW);
	//DisplayBoard(mineboard, COL, ROW);
	First_SafeMine(mineboard, showboard, ROW, COL);
	//DisplayBoard(mineboard, COL, ROW);
	//排雷
	FindMine(mineboard, showboard, COL, ROW);
}
