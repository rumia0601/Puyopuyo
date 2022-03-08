//옵션 함수
//전역 구조체 set을 변경시킨 후 게임함수로 보내는 역할을 함
//수정을 마치면 타이틀 함수로 되돌아감

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

	static int select = 1; //select값이 얼마이냐에 따라 커서가 가르키는 항목이 바뀜
	char key;

	printf("   @@@@@   @@@@@   @@@@@   @@@@@   @@@@@   @   @\n");
	printf("   @   @   @   @     @       @     @   @   @@  @\n");
	printf("   @   @   @@@@@     @       @     @   @   @ @ @\n");
	printf("   @   @   @         @       @     @   @   @  @@\n");
	printf("   @@@@@   @         @     @@@@@   @@@@@   @   @\n\n\n"); //아스키 아트 출력

	printf("             ###### 현재 설정 ######\n");
	printf("                뿌요 종류 : [%d]\n", set.number);
	printf("                뿌요 모양 : [%c]\n", set.shape);
	printf("                뿌요 색상 : ");
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
	printf("                게임 속도 : [%d]\n\n", set.speed);

	if (select == 1) //커서가 뿌요 종류를 가리킬 때
	{
		printf("             ###### 설정 변경 ######\n");
		printf("            ->\t뿌요 종류\n");
		printf("                뿌요 모양\n");
		printf("                뿌요 색상\n");
		printf("                게임 속도\n");
		printf("                초기값으로 변경\n");
		printf("                타이틀 화면으로 돌아가기\n\n");

		printf("\t\tw = 선택지 위로 이동\n");
		printf("\t\ts = 선택지 아래로 이동\n");
		printf("\t\tx = 선택지 실행\n\n");

		key = _getch();

		if (key == 's' || key == 'S')
		{
			select = 2;
		}

		else if (key == 'x' || key == 'X')
		{
			printf("뿌요 종류를 입력하세요\n");
			printf("최솟값 = 1, 최댓값 = 5\n");
			printf("추천값은 3 또는 4 또는 5 입니다\n");

			do
			{
				scanf_s("%d", &(set.number));
			} while ((set.number) < 1 || (set.number) > 5);
		} //뿌요 종류로는 정수 1, 2, 3, 4, 5만 입력 가능
	}

	else if (select == 2) //커서가 뿌요 모양을 가리킬 때
	{
		printf("             ###### 설정 변경 ######\n");
		printf("                뿌요 종류\n");
		printf("            ->\t뿌요 모양\n");
		printf("                뿌요 색상\n");
		printf("                게임 속도\n");
		printf("                초기값으로 변경\n");
		printf("                타이틀 화면으로 돌아가기\n\n");

		printf("\t\tw = 선택지 위로 이동\n");
		printf("\t\ts = 선택지 아래로 이동\n");
		printf("\t\tx = 선택지 실행\n\n");

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
			printf("뿌요 모양을 입력하세요\n");
			printf("O나 X같은 문자를 입력하면 됩니다\n");
			printf("공백 문자들은 뿌요의 모양이 될 수 없습니다\n");
			printf("*은 빈 공간에 해당하는 문자이므로 지원하지 않습니다\n");

			do
			{
				set.shape = _getche();
				clearbuffer();
			} while (set.shape == '*' || set.shape == ' ' || set.shape == '\t' || set.shape == '\n');
		} //뿌요 모양으로는 *과 whitespace를 제외한 1바이트 문자만 입력 가능
	}

	else if (select == 3) //커서가 뿌요 색상을 가리킬 때
	{
		printf("             ###### 설정 변경 ######\n");
		printf("                뿌요 종류\n");
		printf("                뿌요 모양\n");
		printf("            ->\t뿌요 색상\n");
		printf("                게임 속도\n");
		printf("                초기값으로 변경\n");
		printf("                타이틀 화면으로 돌아가기\n\n");

		printf("\t\tw = 선택지 위로 이동\n");
		printf("\t\ts = 선택지 아래로 이동\n");
		printf("\t\tx = 선택지 실행\n\n");

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
			printf("B = 진한파란색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("C = 진한초록색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			printf("D = 진한옥색\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("E = 진한빨간색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
			printf("F = 진한자주색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("G = 진한노란색\t\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			printf("J = 연한파란색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			printf("K = 연한초록색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			printf("L = 연한옥색\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			printf("M = 연한빨간색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			printf("N = 연한자주색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("O = 연한노란색\t");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			printf("\n\n"); //여러가지 색상들의 실제 모습 출력

			printf("똑깥은 색을 여러번 사용할 수는 없습니다\n");
			printf("검정색, 연한 흰색, 회색, 진한 흰색은 배경, 빈 공간, 잔상 효과에 해당하는 색이므로 지원하지 않습니다\n");

			_Bool error;

			do
			{
				error = 0;

				for (int count = 0; count < set.number; count++)
				{
					printf("%d번째 뿌요 색상을 입력하세요 : ", count + 1);
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
		} //뿌요 색상으로는 중복이 없는 알파벳 대/소문자 12종류만 입력 가능
	}

	else if (select == 4) //커서가 게임 속도를 가리킬 때
	{
		printf("             ###### 설정 변경 ######\n");
		printf("                뿌요 종류\n");
		printf("                뿌요 모양\n");
		printf("                뿌요 색상\n");
		printf("            ->\t게임 속도\n");
		printf("                초기값으로 변경\n");
		printf("                타이틀 화면으로 돌아가기\n\n");

		printf("\t\tw = 선택지 위로 이동\n");
		printf("\t\ts = 선택지 아래로 이동\n");
		printf("\t\tx = 선택지 실행\n\n");

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
			printf("게임 속도를 입력하세요\n");
			printf("작을수록 빠르고 클수록 느립니다\n");
			printf("최소값 = 1(이론상 0.001초), 최대값 = 2000000000(이론상 정지화면)\n");
			printf("추천값은 1과 10000 사이입니다\n");

			do
			{
				scanf_s("%d", &(set.speed));
			} while (set.speed < 1 || set.speed > 2000000000);
		} //게임 속도로는 정수 1과 20억 사이의 값만 입력 가능
	}

	else if (select == 5) //커서가 초기값으로 변경을 가리킬 때
	{
		printf("             ###### 설정 변경 ######\n");
		printf("                뿌요 종류\n");
		printf("                뿌요 모양\n");
		printf("                뿌요 색상\n");
		printf("                게임 속도\n");
		printf("            ->\t초기값으로 변경\n");
		printf("                타이틀 화면으로 돌아가기\n\n");

		printf("\t\tw = 선택지 위로 이동\n");
		printf("\t\ts = 선택지 아래로 이동\n");
		printf("\t\tx = 선택지 실행\n\n");

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
		} //set을 default값으로 변경
	}

	else if (select == 6) //커서가 타이틀 화면으로 돌아가기를 가리킬 때
	{
		printf("             ###### 설정 변경 ######\n");
		printf("                뿌요 종류\n");
		printf("                뿌요 모양\n");
		printf("                뿌요 색상\n");
		printf("                게임 속도\n");
		printf("                초기값으로 변경\n");
		printf("            ->\t타이틀 화면으로 돌아가기\n\n");

		printf("\t\tw = 선택지 위로 이동\n");
		printf("\t\ts = 선택지 아래로 이동\n");
		printf("\t\tx = 선택지 실행\n\n");

		key = _getch();

		if (key == 'w' || key == 'W')
		{
			select = 5;
		}

		else if (key == 'x' || key == 'X')
		{
			return; //option함수가 종료되므로 title함수로 되돌아감
		}

	}

	option(); //이상한 값을 입력하면 option함수 재호출
}