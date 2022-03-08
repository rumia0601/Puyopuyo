//�ɼ� �Լ�
//���� ����ü set�� �����Ų �� �����Լ��� ������ ������ ��
//������ ��ġ�� Ÿ��Ʋ �Լ��� �ǵ��ư�

#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define row 14
#define col 6

char save[row][col];

char nextpuyo1, nextpuyo2, nextnextpuyo1, nextnextpuyo2;
int nowchain, latestchain, highestchain;
int c;
int* combo;

void clearbuffer(void);
int color(char* point);

typedef struct Setting
{
	char shape;
	int number;
	int color[5];
	int speed;

}setting;

setting set;

void option(void)
{
	system("cls");

	static int select = 1; //select���� ���̳Ŀ� ���� Ŀ���� ����Ű�� �׸��� �ٲ�
	char key;

	printf("   @@@@@   @@@@@   @@@@@   @@@@@   @@@@@   @   @\n");
	printf("   @   @   @   @     @       @     @   @   @@  @\n");
	printf("   @   @   @@@@@     @       @     @   @   @ @ @\n");
	printf("   @   @   @         @       @     @   @   @  @@\n");
	printf("   @@@@@   @         @     @@@@@   @@@@@   @   @\n\n\n"); //�ƽ�Ű ��Ʈ ���

	printf("             ###### ���� ���� ######\n");
	printf("                �ѿ� ���� : [%d]\n", set.number);
	printf("                �ѿ� ��� : [%c]\n", set.shape);
	printf("                �ѿ� ���� : ");
	for (int count = 0; count < set.number; count++)
	{
		char currentcolor = set.color[count];
		char* ptr;
		ptr = &currentcolor;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(ptr));
		printf("%c ", set.shape);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}
	printf("\n");
	printf("                ���� �ӵ� : [%d]\n\n", set.speed);

	if (select == 1) //Ŀ���� �ѿ� ������ ����ų ��
	{
		printf("             ###### ���� ���� ######\n");
		printf("            ->\t�ѿ� ����\n");
		printf("                �ѿ� ���\n");
		printf("                �ѿ� ����\n");
		printf("                ���� �ӵ�\n");
		printf("                �ʱⰪ���� ����\n");
		printf("                Ÿ��Ʋ ȭ������ ���ư���\n\n");

		printf("\t\tw = ������ ���� �̵�\n");
		printf("\t\ts = ������ �Ʒ��� �̵�\n");
		printf("\t\tx = ������ ����\n\n");

		key = _getch();

		if (key == 's' || key == 'S')
		{
			select = 2;
		}

		else if (key == 'x' || key == 'X')
		{
			printf("�ѿ� ������ �Է��ϼ���\n");
			printf("�ּڰ� = 1, �ִ� = 5\n");
			printf("��õ���� 3 �Ǵ� 4 �Ǵ� 5 �Դϴ�\n");

			do
			{
				scanf_s("%d", &(set.number));
			} while ((set.number) < 1 || (set.number) > 5);
		} //�ѿ� �����δ� ���� 1, 2, 3, 4, 5�� �Է� ����
	}

	else if (select == 2) //Ŀ���� �ѿ� ����� ����ų ��
	{
		printf("             ###### ���� ���� ######\n");
		printf("                �ѿ� ����\n");
		printf("            ->\t�ѿ� ���\n");
		printf("                �ѿ� ����\n");
		printf("                ���� �ӵ�\n");
		printf("                �ʱⰪ���� ����\n");
		printf("                Ÿ��Ʋ ȭ������ ���ư���\n\n");

		printf("\t\tw = ������ ���� �̵�\n");
		printf("\t\ts = ������ �Ʒ��� �̵�\n");
		printf("\t\tx = ������ ����\n\n");

		key = _getch();

		if (key == 'w' || key == 'W')
		{
			select = 1;
		}

		else if (key == 's' || key == 'S')
		{
			select = 3;
		}

		else if (key == 'x' || key == 'X')
		{
			printf("�ѿ� ����� �Է��ϼ���\n");
			printf("O�� X���� ���ڸ� �Է��ϸ� �˴ϴ�\n");
			printf("���� ���ڵ��� �ѿ��� ����� �� �� �����ϴ�\n");
			printf("*�� �� ������ �ش��ϴ� �����̹Ƿ� �������� �ʽ��ϴ�\n");

			do
			{
				set.shape = _getche();
				clearbuffer();
			} while (set.shape == '*' || set.shape == ' ' || set.shape == '\t' || set.shape == '\n');
		} //�ѿ� ������δ� *�� whitespace�� ������ 1����Ʈ ���ڸ� �Է� ����
	}

	else if (select == 3) //Ŀ���� �ѿ� ������ ����ų ��
	{
		printf("             ###### ���� ���� ######\n");
		printf("                �ѿ� ����\n");
		printf("                �ѿ� ���\n");
		printf("            ->\t�ѿ� ����\n");
		printf("                ���� �ӵ�\n");
		printf("                �ʱⰪ���� ����\n");
		printf("                Ÿ��Ʋ ȭ������ ���ư���\n\n");

		printf("\t\tw = ������ ���� �̵�\n");
		printf("\t\ts = ������ �Ʒ��� �̵�\n");
		printf("\t\tx = ������ ����\n\n");

		key = _getch();

		if (key == 'w' || key == 'W')
		{
			select = 2;
		}

		else if (key == 's' || key == 'S')
		{
			select = 4;
		}

		else if (key == 'x' || key == 'X')
		{

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
			printf("B = �����Ķ���\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("C = �����ʷϻ�\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			printf("D = ���ѿ���\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("E = ���ѻ�����\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			printf("F = �������ֻ�\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("G = ���ѳ����\t\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			printf("J = �����Ķ���\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			printf("K = �����ʷϻ�\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			printf("L = ���ѿ���\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("M = ���ѻ�����\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			printf("N = �������ֻ�\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("O = ���ѳ����\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("\n\n"); //�������� ������� ���� ��� ���

			printf("�ȱ��� ���� ������ ����� ���� �����ϴ�\n");
			printf("������, ���� ���, ȸ��, ���� ����� ���, �� ����, �ܻ� ȿ���� �ش��ϴ� ���̹Ƿ� �������� �ʽ��ϴ�\n");

			_Bool error;

			do
			{
				error = 0;

				for (int count = 0; count < set.number; count++)
				{
					printf("%d��° �ѿ� ������ �Է��ϼ��� : ", count + 1);
					set.color[count] = _getche();
					clearbuffer();
				}

				for (int count = 0; count < set.number; count++)
				{
					char currentcolor = set.color[count];
					char* ptr;
					ptr = &currentcolor;

					if (color(ptr) == 15)
						error = 1;

					for (int count2 = count + 1; count2 < set.number; count2++)
					{
						if (set.color[count2] == set.color[count])
							error = 1;
					}
				}

			} while (error == 1);
		} //�ѿ� �������δ� �ߺ��� ���� ���ĺ� ��/�ҹ��� 12������ �Է� ����
	}

	else if (select == 4) //Ŀ���� ���� �ӵ��� ����ų ��
	{
		printf("             ###### ���� ���� ######\n");
		printf("                �ѿ� ����\n");
		printf("                �ѿ� ���\n");
		printf("                �ѿ� ����\n");
		printf("            ->\t���� �ӵ�\n");
		printf("                �ʱⰪ���� ����\n");
		printf("                Ÿ��Ʋ ȭ������ ���ư���\n\n");

		printf("\t\tw = ������ ���� �̵�\n");
		printf("\t\ts = ������ �Ʒ��� �̵�\n");
		printf("\t\tx = ������ ����\n\n");

		key = _getch();

		if (key == 'w' || key == 'W')
		{
			select = 3;
		}

		else if (key == 's' || key == 'S')
		{
			select = 5;
		}

		else if (key == 'x' || key == 'X')
		{
			printf("���� �ӵ��� �Է��ϼ���\n");
			printf("�������� ������ Ŭ���� �����ϴ�\n");
			printf("�ּҰ� = 1(�̷л� 0.001��), �ִ밪 = 2000000000(�̷л� ����ȭ��)\n");
			printf("��õ���� 1�� 10000 �����Դϴ�\n");

			do
			{
				scanf_s("%d", &(set.speed));
			} while (set.speed < 1 || set.speed > 2000000000);
		} //���� �ӵ��δ� ���� 1�� 20�� ������ ���� �Է� ����
	}

	else if (select == 5) //Ŀ���� �ʱⰪ���� ������ ����ų ��
	{
		printf("             ###### ���� ���� ######\n");
		printf("                �ѿ� ����\n");
		printf("                �ѿ� ���\n");
		printf("                �ѿ� ����\n");
		printf("                ���� �ӵ�\n");
		printf("            ->\t�ʱⰪ���� ����\n");
		printf("                Ÿ��Ʋ ȭ������ ���ư���\n\n");

		printf("\t\tw = ������ ���� �̵�\n");
		printf("\t\ts = ������ �Ʒ��� �̵�\n");
		printf("\t\tx = ������ ����\n\n");

		key = _getch();

		if (key == 'w' || key == 'W')
		{
			select = 4;
		}

		else if (key == 's' || key == 'S')
		{
			select = 6;
		}

		else if (key == 'x' || key == 'X')
		{
			set.shape = '@';
			set.number = 3;
			set.color[0] = 'M';
			set.color[1] = 'K';
			set.color[2] = 'J';
			set.color[3] = 'O';
			set.color[4] = 'N';
			set.speed = 1000;
		} //set�� default������ ����
	}

	else if (select == 6) //Ŀ���� Ÿ��Ʋ ȭ������ ���ư��⸦ ����ų ��
	{
		printf("             ###### ���� ���� ######\n");
		printf("                �ѿ� ����\n");
		printf("                �ѿ� ���\n");
		printf("                �ѿ� ����\n");
		printf("                ���� �ӵ�\n");
		printf("                �ʱⰪ���� ����\n");
		printf("            ->\tŸ��Ʋ ȭ������ ���ư���\n\n");

		printf("\t\tw = ������ ���� �̵�\n");
		printf("\t\ts = ������ �Ʒ��� �̵�\n");
		printf("\t\tx = ������ ����\n\n");

		key = _getch();

		if (key == 'w' || key == 'W')
		{
			select = 5;
		}

		else if (key == 'x' || key == 'X')
		{
			return; //option�Լ��� ����ǹǷ� title�Լ��� �ǵ��ư�
		}

	}

	option(); //�̻��� ���� �Է��ϸ� option�Լ� ��ȣ��
}