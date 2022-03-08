//Ÿ��Ʋ �Լ�
//main�Լ��� ���ԵǾ� ����
//exit�Լ��� ���ԵǾ� ����
//���ÿ� ���� �����Լ� Ȥ�� �ɼ��Լ� Ȥ�� exit�Լ��� ������

#include <stdio.h> //�⺻���� �����(printf,scanf)
#include <windows.h> //�ܼ� ��� ���� ����, �ܼ� ȭ�� �����(setconsoletextattribut, system)
#include <time.h> //�ð� ��� ����(clock)
#include <stdlib.h> //���� ����, ���α׷� ����(srand, exit)
#include <conio.h> //��ȭ�� �����(getch)

#define row 14 //2����� 13������� �����ǿ� ��µǰ� 0����� 1������� �����ǿ� ��µ��� ����
#define col 6 

char save[row][col] = { '\0' }; //erase�Լ����� ���� ���ȣ���� �����ϴ� ���� 2�����迭

char nextpuyo1, nextpuyo2, nextnextpuyo1, nextnextpuyo2;
int nowchain, latestchain, highestchain;
int c;
int* combo = &c; //printscreen�Լ����� ����ϴ� ����������

typedef struct Setting
{
	char shape;
	int number;
	int color[5];
	int speed;

}setting; //option�Լ����� ���� �����ϰ� game�Լ��� ���޵Ǵ� ���� ����ü

setting set = { '@', 3, {'M','K','J','O','N'}, 1000 }; //set�� default��

void game(void);
void option(void);

void title(void)
{
	char key;
	static int select = 1; //select���� ���̳Ŀ� ���� Ŀ���� ����Ű�� �׸��� �ٲ�

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("     @@@@@     @   @     @   @     @@@@@          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("     @   @     @   @      @ @      @   @          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("     @@@@@     @   @       @       @   @          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("     @         @   @       @       @   @          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("     @         @@@@@       @       @@@@@          \n");
	printf("                                                  \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("     @@@@@     @   @     @   @     @@@@@          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("     @   @     @   @      @ @      @   @          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("     @@@@@     @   @       @       @   @          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("     @         @   @       @       @   @          \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("     @         @@@@@       @       @@@@@          \n\n\n\n\n"); //�ƽ�Ű ��Ʈ ���

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (select == 1) //Ŀ���� Game Start�� ����ų ��
	{
		printf("\t    ->\tGame Start\n");
		printf("\t\tOption\n");
		printf("\t\tQuit\n\n\n\n");

		printf("\tw = ������ ���� �̵�\n");
		printf("\ts = ������ �Ʒ��� �̵�\n");
		printf("\tx = ������ ����\n");

		key = _getch();

		if (key == 's' || key == 'S')
			select = 2;

		else if (key == 'x' || key == 'X')
		{
			system("cls");

			game(); //game�Լ� ����
		}

	}

	else if (select == 2) //Ŀ���� Option�� ����ų ��
	{
		printf("\t\tGame Start\n");
		printf("\t    ->\tOption\n");
		printf("\t\tQuit\n\n\n\n");

		printf("\tw = ������ ���� �̵�\n");
		printf("\ts = ������ �Ʒ��� �̵�\n");
		printf("\tx = ������ ����\n");

		key = _getch();

		if (key == 'w' || key == 'W')
			select = 1;

		else if (key == 's' || key == 'S')
			select = 3;

		else if (key == 'x' || key == 'X')
			option(); //option�Լ� ����
	}

	else if (select == 3) //Ŀ���� Quit�� ����ų ��
	{
		printf("\t\tGame Start\n");
		printf("\t\tOption\n");
		printf("\t    ->\tQuit\n\n\n\n");

		printf("\tw = ������ ���� �̵�\n");
		printf("\ts = ������ �Ʒ��� �̵�\n");
		printf("\tx = ������ ����\n");

		key = _getch();

		if (key == 'w' || key == 'W')
			select = 2;

		else if (key == 'x' || key == 'X')
		{
			printf("\n");
			exit(0); //���α׷� ����
		}
	}

	system("cls");
	title(); //�̻��� ���� �Է��ϸ� title�Լ� ��ȣ��

	return;
}

int main(void)
{
	title();

	return;
} //title�Լ��� main�Լ��� ��ǻ� ����