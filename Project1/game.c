//게임 함수
//게임이 종료되면 타이틀 함수로 되돌아감
//외부 텍스트파일(Test.txt)의 내용을 읽어 arr[i][j]에 저장하는 구간이 있음

#include <stdio.h> 
#include <windows.h> 
#include <time.h> 
#include <stdlib.h>
#include <conio.h>
#include "functions.h"

#define row 14
#define col 6

char save[row][col];

char nextpuyo1, nextpuyo2, nextnextpuyo1, nextnextpuyo2;
int nowchain, latestchain, highestchain;
int c;
int* combo;

setting set;

int color(char* point);

void game(void)
{
	//게임 시작 부분
	//게임에 사용할 지역변수들을 선언하고, 게임판을 출력한 뒤 효과음을 발생시키고 netxpuyo를 nowpuyo로 바꾼 뒤 게임판 위에 올려놓는다

	srand((unsigned)time(NULL));

	_Bool finish = 0;

	char arr[row][col];

	char* key;
	char k;
	key = &k;
	char trash;

	char nowpuyo1, nowpuyo2;
	randomize(&nowpuyo1);
	randomize(&nowpuyo2);
	randomize(&nextpuyo1);
	randomize(&nextpuyo2);
	randomize(&nextnextpuyo1);
	randomize(&nextnextpuyo2);

	int *i1, *i2, *j1, *j2;
	int ii1 = 0, ii2 = 0, jj1 = 0, jj2 = 0;

	i1 = &ii1, i2 = &ii2, j1 = &jj1, j2 = &jj2;

	for (int count1 = 0; count1 < row; count1++)
		for (int count2 = 0; count2 < col; count2++)
			arr[count1][count2] = '*';

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	*i1 = 0;
	*j1 = 2;
	*i2 = 1;
	*j2 = 2;

	showscreen(arr);

	Beep(65 * 8, 100);
	Beep(73 * 8, 100);
	Beep(82 * 8, 100);
	Beep(87 * 8, 100);
	Beep(97 * 8, 100);
	Beep(110 * 8, 100);
	Beep(123 * 8, 100);
	Beep(130 * 8, 1000); //출력 : 도레미파솔라시도 (시작하는 느낌)

	system("cls");

	nowpuyo1 = nextpuyo1;
	nowpuyo2 = nextpuyo2;
	nextpuyo1 = nextnextpuyo1;
	nextpuyo2 = nextnextpuyo2;
	randomize(&nextnextpuyo1);
	randomize(&nextnextpuyo2);

	while (1)
	{
		if (finish == 1)
			//다음 블록을 사용하기 전에 처리되는 부분
			//동일한 색의 블록이 4개 이상 이웃하는지 아닌지를 판단
			//이웃하면 삭제, 연쇄를 일으키고 다음 블록을 사용
		{

			Sleep(1);

			gravity(arr);
			erasecheck(arr);
			if(nowchain != 0)
				latestchain = nowchain;
			nowchain = 0;

			if (latestchain > highestchain)
				highestchain = latestchain;

			if ((gameover(arr[2][2]) == 1)) 
			//게임 종료 부분
			//최종 게임판과 최종 점수를 출력하고 효과음을 발생시킨 뒤 게임을 종료한다
			{
				system("cls");
				showscreen(arr);

				printf("\n\nGame over!\n\n");

				Beep(130 * 8, 100);
				Beep(123 * 8, 100);
				Beep(110 * 8, 100);
				Beep(97 * 8, 100);
				Beep(87 * 8, 100);
				Beep(82 * 8, 100);
				Beep(73 * 8, 100);
				Beep(65 * 8, 1000); //출력 : 도시라솔파미레도 (끝나는 느낌)

				nowchain = 0;
				highestchain = 0;
				latestchain = 0;

				printf("아무키나 입력하면 타이틀 화면으로 돌아갑니다 : ");
				trash = _getch();

				return;
			}

			*i1 = 0;
			*j1 = 2;
			*i2 = 1;
			*j2 = 2;

			system("cls");
		}

		arr[*i1][*j1] = nowpuyo1;
		arr[*i2][*j2] = nowpuyo2;

		showscreen(arr);

		char data = 'n';
		double before, after, gap;

		before = clock();

		do //set.speed라는 시간동안 사용자로부터 키를 입력받음. 주어진 시간 내 키를 입력받지 못한 경우 키는 강제로 'n'이 됨
		{
			if (_kbhit())
			{
				data = _getche();
				break;
			}

			after = clock();
			gap = after - before;

		} while (gap <= set.speed);

		*key = data;

		if (*key == 's' || *key == 'S') //블록 2칸을 아래로 이동
		{
			movedown(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'a' || *key == 'A') //블록 2칸을 왼쪽으로 이동
		{
			moveleft(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'd' || *key == 'D') //블록 2칸을 오른쪽으로 이동
		{
			moveright(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'w' || *key == 'W') //블록 2칸을 최대한 아래로 이동시키고 다음 블록을 사용함
		{
			for (int count = 1; count < row; count++)
			{
				movedown(arr, i1, j1, i2, j2);

				Sleep(1);
				system("cls");
				showscreen(arr);
			}

			nowpuyo1 = nextpuyo1;
			nowpuyo2 = nextpuyo2;
			nextpuyo1 = nextnextpuyo1;
			nextpuyo2 = nextnextpuyo2;
			randomize(&nextnextpuyo1);
			randomize(&nextnextpuyo2); //다음 블록을 현재의 블록으로, 다다음 블록을 다음 블록으로 바꾼 뒤 다다음 블록을 랜덤 생성

			finish = 1;
		}

		else if (*key == 'q' || *key == 'Q') //블록 2칸을 반시계 방향으로 회전
		{
			turnleft(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'e' || *key == 'E') //블록 2칸을 반시계 방향으로 회전
		{
			turnright(arr, i1, j1, i2, j2);
			finish = 0;
		}
		
		else if (*key == 'p' || *key == 'P') //치트키를 입력할 경우 강제로 현재의 게임판이 미리 정해놓은 판으로 바뀜
		{
			char ch;
			FILE *fp;

			fp = fopen("Cheat.txt", "r");

			for (int i = 0; i < row; i++) //Cheat.txt에 적혀 있는 0, 1, 2, 3, 4, 5들을 게임판 위의 블록들로 바꿈
			{
				for (int j = 0; j < col; j++)
				{
					fscanf(fp, "%c", &ch);

					switch (ch)
					{
					case '0': arr[i][j] = '*'; break;
					case '1': arr[i][j] = set.color[0]; break;
					case '2': arr[i][j] = set.color[1]; break;
					case '3': arr[i][j] = set.color[2]; break;
					case '4': arr[i][j] = set.color[3]; break;
					case '5': arr[i][j] = set.color[4]; break;
					default: arr[i][j] = '*';
					}
				}

				fscanf(fp, "%c", &ch);
			}

			fclose(fp);

			finish = 1;
		}

		else if (*key == 'n') //시간이 경과한 경우 블록 2칸을 아래로 1칸 내리거나 다음 블록을 사용함
		{

			if (*i1 == row - 1 || *i2 == row - 1)
			{
				system("cls");
				showscreen(arr);

				nowpuyo1 = nextpuyo1;
				nowpuyo2 = nextpuyo2;
				nextpuyo1 = nextnextpuyo1;
				nextpuyo2 = nextnextpuyo2;
				randomize(&nextnextpuyo1);
				randomize(&nextnextpuyo2); //다음 블록을 현재의 블록으로, 다다음 블록을 다음 블록으로 바꾼 뒤 다다음 블록을 랜덤 생성

				finish = 1;
			}

			else if (*i1 > *i2 && arr[*i1 + 1][*j1] != '*')
			{
				system("cls");
				showscreen(arr);

				nowpuyo1 = nextpuyo1;
				nowpuyo2 = nextpuyo2;
				nextpuyo1 = nextnextpuyo1;
				nextpuyo2 = nextnextpuyo2;
				randomize(&nextnextpuyo1);
				randomize(&nextnextpuyo2); //다음 블록을 현재의 블록으로, 다다음 블록을 다음 블록으로 바꾼 뒤 다다음 블록을 랜덤 생성

				finish = 1;
			}


			else if (*i1 < *i2 && arr[*i2 + 1][*j2] != '*')
			{
				system("cls");
				showscreen(arr);

				nowpuyo1 = nextpuyo1;
				nowpuyo2 = nextpuyo2;
				nextpuyo1 = nextnextpuyo1;
				nextpuyo2 = nextnextpuyo2;
				randomize(&nextnextpuyo1);
				randomize(&nextnextpuyo2); //다음 블록을 현재의 블록으로, 다다음 블록을 다음 블록으로 바꾼 뒤 다다음 블록을 랜덤 생성

				finish = 1;
			}

			else if ((*i1 == *i2) && ((arr[*i1 + 1][*j1] != '*') || (arr[*i2 + 1][*j2] != '*')))
			{
				system("cls");
				showscreen(arr);

				nowpuyo1 = nextpuyo1;
				nowpuyo2 = nextpuyo2;
				nextpuyo1 = nextnextpuyo1;
				nextpuyo2 = nextnextpuyo2;
				randomize(&nextnextpuyo1);
				randomize(&nextnextpuyo2); //다음 블록을 현재의 블록으로, 다다음 블록을 다음 블록으로 바꾼 뒤 다다음 블록을 랜덤 생성

				finish = 1;
			}

			else
			{
				movedown(arr, i1, j1, i2, j2);
				finish = 0;
			}
		}

		system("cls");
	}

	return;
}