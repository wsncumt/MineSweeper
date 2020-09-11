#define _CRT_SECURE_NO_WARNINGS 1

#include "game.h"

//�˵�
void menu()
{
	printf("********************\n");
	printf("*1.play******0.exit*\n");
	printf("********************\n");
}

//��ʼ������
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

//��ʾ����
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

//��ʼ�����׵�λ��
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
//��֤��һ��������
void First_SafeMine(char mineboard[ROWS][COLS], char showboard[ROWS][COLS], int row, int col)//ȷ����һ��������
{
	int x = 0;
	int y = 0;
	int ret = 1;
	int count = 0;
	int a, b;
	printf("������Ҫ�Ų������:");
	scanf("%d%d", &x, &y);
	if (mineboard[x][y] == '1')//���Ϊ�ף����Ϊû����
	{
		mineboard[x][y] = '0';
		while (ret)//�������һ����
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
//ͳ��������Χ�׵ĸ���
int GetMineCount(const char mineboard[ROWS][COLS], int x, int y)
{
	return mineboard[x - 1][y + 1] + mineboard[x][y + 1] + mineboard[x + 1][y + 1] +
		mineboard[x - 1][y] + mineboard[x + 1][y] +
		mineboard[x - 1][y - 1] + mineboard[x][y - 1] + mineboard[x + 1][y - 1] - 8 * '0';
}

//չ���������������������Χû���׾��Զ�չ����
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

////ͳ�����������ӵĸ���
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

//ͳ�������������¶�Ӧ�����׸���
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
//ͳ�����������ų�������
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

//����
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
		printf("��ѡ������a,b��c����\n");
		printf("a.���� b.���� c.ȡ������\n");
		//scanf("%s", &input1);
		input1 = getchar();
		switch (input1)
		{
		case 'a':
		{
			printf("������Ҫ��������:>\n");
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
							printf("�˴������ӣ���ε������Ų顣\n");
						}
						else
						{
							printf("\n�˴��Ѿ��Ų���ˣ����������롣\n");
						}
					}
					else if (mineboard[x][y] == '1')
					{
						printf("\n���ź�����ȵ��˵��ף���Ϸ������\n");
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
					printf("\n�������������������������\n");
				}
			}
			break;
		}
		case 'b':
		{
			int bool1 = 1;
			while (bool1)
			{
				printf("������Ҫ���������:>");
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
						printf("�˴��޷��������ӡ��밴����������м�飺\n(1)�����Ƿ�����\n(2)�˴��Ѿ������ӣ�\n(3)�˴��Ƿ��Ѿ��Ų���ˡ�\n");
					}
				}
				else
				{
					printf("����������������������롣\n");
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
					printf("\n������û�����ӣ���ѡ�����׻���졣\n");
					bool2 = 0;
				}
				else
				{
					printf("\n������Ҫ���������:>");
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
							printf("\n�˴��޷��Ƴ����ӡ��밴����������м�飺\n(1)�����Ƿ�����\n(2)�˴�û�����ӣ�\n(3)�˴������Ƿ��Ѿ��ε���\n");
						}
					}
					else
					{
						printf("����������������������롣\n");
					}
				}
			}
			DisplayBoard(showboard, COL, ROW);
			break;
			}
		}
		if (win == 1)
		{
			printf("��ϲ�㣬�����ų�ȫ�����ס�\n");
			bool = 0;
			DisplayBoard(mineboard,COL,ROW);
		}
	}while ( bool == 1);
}

void game()
{
	//�洢�׵�λ��:�����������̣�һ�����ڴ�ӡ
	char mineboard[COLS][ROWS] ;
	char showboard[COLS][ROWS];

	//��ʼ������
	InitBoard(mineboard, COLS, ROWS, '0');
	InitBoard(showboard, COLS, ROWS, '*');

	//��ʾ����
	//DisplayBoard(mineboard, COL, ROW);
	DisplayBoard(showboard, COL, ROW);

	//������
	SetMine(mineboard,COL,ROW);
	//DisplayBoard(mineboard, COL, ROW);
	First_SafeMine(mineboard, showboard, ROW, COL);
	//DisplayBoard(mineboard, COL, ROW);
	//����
	FindMine(mineboard, showboard, COL, ROW);
}
