#define _CRT_SECURE_NO_WARNINGS 1
//ɨ����Ϸ
#include "game.h"

int main(void)
{
	int input;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
			case 1:
				game();
				break;
			case 0:
				printf("�˳���Ϸ��\n");
				break;
			default:
				printf("�����������������.\n");
				break;
		}
	} while (input);
	return 0;
}