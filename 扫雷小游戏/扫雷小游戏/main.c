#define _CRT_SECURE_NO_WARNINGS 1
//扫雷游戏
#include "game.h"

int main(void)
{
	int input;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
			case 1:
				game();
				break;
			case 0:
				printf("退出游戏。\n");
				break;
			default:
				printf("输入错误，请重新输入.\n");
				break;
		}
	} while (input);
	return 0;
}