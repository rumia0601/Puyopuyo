//타이틀 함수
//main함수가 포함되어 있음
//exit함수가 포함되어 있음
//선택에 따라 게임함수 혹은 옵션함수 혹은 exit함수를 실행함

#include <stdio.h> //기본적인 입출력(printf,scanf)
#include <windows.h> //콘솔 출력 색상 변경, 콘솔 화면 지우기(setconsoletextattribut, system)
#include <time.h> //시간 경과 측정(clock)
#include <stdlib.h> //난수 생성, 프로그램 종료(srand, exit)
#include <conio.h> //심화된 입출력(getch)

#define row 14 //2행부터 13행까지는 게임판에 출력되고 0행부터 1행까지는 게임판에 출력되지 않음
#define col 6 

char save[row][col] = { '\0' }; //erase함수군의 무한 재귀호출을 방지하는 전역 2차원배열

char nextpuyo1, nextpuyo2, nextnextpuyo1, nextnextpuyo2;
int nowchain, latestchain, highestchain;
int c;
int* combo = &c; //printscreen함수에서 출력하는 전역변수들

typedef struct Setting
{
	char shape;
	int number;
	int color[5];
	int speed;

}setting; //option함수에서 수정 가능하고 game함수로 전달되는 전역 구조체

setting set = { '@', 3, {'M','K','J','O','N'}, 1000 }; //set의 default값

void game(void);
void option(void);

void title(void)
{
	char key;
	static int select = 1; //select값이 얼마이냐에 따라 커서가 가리키는 항목이 바뀜

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
	printf("     @         @@@@@       @       @@@@@          \n\n\n\n\n"); //아스키 아트 출력

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (select == 1) //커서가 Game Start를 가리킬 때
	{
		printf("\t    ->\tGame Start\n");
		printf("\t\tOption\n");
		printf("\t\tQuit\n\n\n\n");

		printf("\tw = 선택지 위로 이동\n");
		printf("\ts = 선택지 아래로 이동\n");
		printf("\tx = 선택지 실행\n");

		key = _getch();

		if (key == 's' || key == 'S')
			select = 2;

		else if (key == 'x' || key == 'X')
		{
			system("cls");

			game(); //game함수 시작
		}

	}

	else if (select == 2) //커서가 Option을 가리킬 때
	{
		printf("\t\tGame Start\n");
		printf("\t    ->\tOption\n");
		printf("\t\tQuit\n\n\n\n");

		printf("\tw = 선택지 위로 이동\n");
		printf("\ts = 선택지 아래로 이동\n");
		printf("\tx = 선택지 실행\n");

		key = _getch();

		if (key == 'w' || key == 'W')
			select = 1;

		else if (key == 's' || key == 'S')
			select = 3;

		else if (key == 'x' || key == 'X')
			option(); //option함수 시작
	}

	else if (select == 3) //커서가 Quit를 가리킬 때
	{
		printf("\t\tGame Start\n");
		printf("\t\tOption\n");
		printf("\t    ->\tQuit\n\n\n\n");

		printf("\tw = 선택지 위로 이동\n");
		printf("\ts = 선택지 아래로 이동\n");
		printf("\tx = 선택지 실행\n");

		key = _getch();

		if (key == 'w' || key == 'W')
			select = 2;

		else if (key == 'x' || key == 'X')
		{
			printf("\n");
			exit(0); //프로그램 종료
		}
	}

	system("cls");
	title(); //이상한 값을 입력하면 title함수 재호출

	return;
}

int main(void)
{
	title();

	return;
} //title함수와 main함수는 사실상 같음