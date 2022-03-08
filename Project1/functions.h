//함수 헤더파일
//게임 함수에서 사용되는 17종류의 함수들을 정의함

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

typedef struct Setting
{
	char shape;
	int number;
	int color[5];
	int speed;

}setting;

setting set;

int color(char* point) 
//콘솔 출력되는 색상을 결정하는 함수
//arr[i][j]를 대입한 color의 반환값을 setconsoletextattribute함수에 대입하면 arr[i][j]에 해당하는 색상으로 콘솔 출력 색상이 바뀜
{
	switch (*point)
	{
	case 'A': return 15;
	case 'B': return 1;
	case 'C': return 2;
	case 'D': return 3;
	case 'E': return 4;
	case 'F': return 5;
	case 'G': return 6;
	case 'H': return 15;
	case 'I': return 15;
	case 'J': return 9;
	case 'K': return 10;
	case 'L': return 11;
	case 'M': return 12;
	case 'N': return 13;
	case 'O': return 14;
	case 'P': return 15;
	case 'a': return 15;
	case 'b': return 1;
	case 'c': return 2;
	case 'd': return 3;
	case 'e': return 4;
	case 'f': return 5;
	case 'g': return 6;
	case 'h': return 15;
	case 'i': return 15;
	case 'j': return 9;
	case 'k': return 10;
	case 'l': return 11;
	case 'm': return 12;
	case 'n': return 13;
	case 'o': return 14;
	case 'p': return 15;
	default: return 15;
	}
}

void showscreen(char(*arr)[col])
//게임판을 출력하는 함수
//전역변수 7개의 값을 출력함
//이 함수가 호출하는 다른 함수 : color
{
	printf("                     \n");
	for (int count1 = 2; count1 < row; count1++)
	{
		printf("  ");
		for (int count2 = 0; count2 < col; count2++)
		{
			if (arr[count1][count2] == '*')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //빈 공간은 회색 별
				printf("* ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(&(arr[count1][count2])));
				printf("%c ", set.shape); //출력되는 블록들의 모양은 set.shape
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}
		printf(" \n");
	}
	printf("               \n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("Next Puyo : ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(&nextpuyo1));
	printf("%c\n", set.shape);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(&nextpuyo2));
	printf("\t    %c", set.shape);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\nNext Next Puyo : ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(&nextnextpuyo1));
	printf("%c\n", set.shape);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(&nextnextpuyo2));
	printf("\t\t %c", set.shape);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\nNow Chain : %d", nowchain);
	printf("\nLast Chain : %d", latestchain);
	printf("\nMax  Chain : %d\n\n", highestchain);
	printf("q = 반시계방향으로 회전     w = 최대한 아래로 이동     e = 시계방향으로 회전\n");
	printf("a = 왼쪽으로 이동           s = 아래로 이동            d = 오른쪽으로 이동\n");
	printf("입력한 키 : ");

	return;
}

void randomize(char* point)
//블록 색상을 랜덤으로 생성하는 함수
//생성되는 블록들의 종류와 색상은 각각 set.number, set.color[i]
{
	switch (rand() % set.number)
	{
	case 0: *point = set.color[0]; return;
	case 1: *point = set.color[1]; return;
	case 2: *point = set.color[2]; return;
	case 3: *point = set.color[3]; return;
	case 4: *point = set.color[4]; return;
	default: return;
	}
}

void swap(char* a, char* b)
//Call by reference 스왑 함수
//게임판 내의 블록들이 이동할 때엔 항상 이 함수가 호출됨
{
	char save;
	save = *a;
	*a = *b;
	*b = save;

	return;
}

void movedown(char arr[][col], int* i1, int* j1, int* i2, int* j2)
//move함수군에 속한 첫번째 함수
//사용자가 조종하는 블록 2칸을 둘 다 아래로 1칸씩 이동시키는 함수
//둘 중 하나라도 아래로 1칸 내려갈 수 없으면 아무런 일도 일어나지 않음
//이 함수가 호출하는 다른 함수 : swap
{
	if ((*i1 >= row - 1) || (*i2 >= row - 1))
		return;

	else if (*i2 > *i1)
	{
		if (arr[*i2 + 1][*j2] != '*')
			return;

		else
		{
			swap((&arr[*i2 + 1][*j2]), (&arr[*i2][*j2]));
			swap((&arr[*i1 + 1][*j1]), (&arr[*i1][*j1]));

			(*i1)++;
			(*i2)++;

			return;
		}
	}

	else if (*i2 == *i1)
	{
		if (arr[*i2 + 1][*j2] != '*' || arr[*i1 + 1][*j1] != '*')
			return;

		else
		{
			swap((&arr[*i2 + 1][*j2]), (&arr[*i2][*j2]));
			swap((&arr[*i1 + 1][*j1]), (&arr[*i1][*j1]));

			(*i1)++;
			(*i2)++;

			return;
		}
	}

	else if (*i2 < *i1)
	{
		if (arr[*i1 + 1][*j1] != '*')
			return;

		else
		{
			swap((&arr[*i1 + 1][*j1]), (&arr[*i1][*j1]));
			swap((&arr[*i2 + 1][*j2]), (&arr[*i2][*j2]));

			(*i1)++;
			(*i2)++;

			return;
		}
	}
}

void moveleft(char arr[][col], int* i1, int* j1, int* i2, int* j2)
//move함수군에 속한 두번째 함수
//사용자가 조종하는 블록 2칸을 둘 다 왼쪽으로 1칸씩 이동시키는 함수
//둘 중 하나라도 왼쪽으로 1칸 이동할 수 없으면 아무런 일도 일어나지 않음
//이 함수가 호출하는 다른 함수 : swap
{
	if ((*j1 <= 0) || (*j2 <= 0))
		return;

	else if (*j1 > *j2)
	{
		if (arr[*i2][*j2 - 1] != '*')
			return;

		else
		{
			swap((&arr[*i2][*j2]), (&arr[*i2][*j2 - 1]));
			swap((&arr[*i1][*j1]), (&arr[*i1][*j1 - 1]));

			(*j1)--;
			(*j2)--;

			return;
		}
	}

	else if (*j1 == *j2)
	{
		if (arr[*i2][*j2 - 1] != '*' || arr[*i1][*j1 - 1] != '*')
			return;

		else
		{
			swap((&arr[*i2][*j2]), (&arr[*i2][*j2 - 1]));
			swap((&arr[*i1][*j1]), (&arr[*i1][*j1 - 1]));

			(*j1)--;
			(*j2)--;

			return;
		}
	}

	else if (*j1 < *j2)
	{
		if (arr[*i1][*j1 - 1] != '*')
			return;

		else
		{
			swap((&arr[*i1][*j1]), (&arr[*i1][*j1 - 1]));
			swap((&arr[*i2][*j2]), (&arr[*i2][*j2 - 1]));

			(*j1)--;
			(*j2)--;

			return;
		}
	}
}

void moveright(char arr[][col], int* i1, int* j1, int* i2, int* j2)
//move함수군에 속한 세번째 함수
//사용자가 조종하는 블록 2칸을 둘 다 오른쪽으로 1칸씩 이동시키는 함수
//둘 중 하나라도 오른쪽으로 1칸 이동할 수 없으면 아무런 일도 일어나지 않음
//이 함수가 호출하는 다른 함수 : swap
{
	if ((*j1 >= col - 1) || (*j2 >= col - 1))
		return;

	else if (*j1 > *j2)
	{
		if (arr[*i1][*j1 + 1] != '*')
			return;

		else
		{
			swap((&arr[*i1][*j1]), (&arr[*i1][*j1 + 1]));
			swap((&arr[*i2][*j2]), (&arr[*i2][*j2 + 1]));

			(*j1)++;
			(*j2)++;

			return;
		}
	}

	else if (*j1 == *j2)
	{
		if (arr[*i1][*j1 + 1] != '*' || arr[*i2][*j2 + 1] != '*')
			return;

		else
		{
			swap((&arr[*i1][*j1]), (&arr[*i1][*j1 + 1]));
			swap((&arr[*i2][*j2]), (&arr[*i2][*j2 + 1]));

			(*j1)++;
			(*j2)++;

			return;
		}
	}

	else if (*j1 < *j2)
	{
		if (arr[*i2][*j2 + 1] != '*')
			return;

		else
		{
			swap((&arr[*i2][*j2]), (&arr[*i2][*j2 + 1]));
			swap((&arr[*i1][*j1]), (&arr[*i1][*j1 + 1]));

			(*j1)++;
			(*j2)++;

			return;
		}
	}
}

void turnleft(char arr[][col], int* i1, int* j1, int* i2, int* j2)
//move함수군에 속한 네번째 함수
//사용자가 조종하는 블록 2칸을 반시계방향으로 회전시키는 함수, 회전축이 되는 블록은 arr[*i2][*j2]임
//arr[*i1][*i2]가 회전할 수 없는 경우 아무런 일도 일어나지 않음
//이 함수가 호출하는 다른 함수 : swap
{
	if (*i1 < *i2)
	{
		if ((*j1 == 0) || (*j2 == 0) || (arr[*i1][*(j1)-1] != '*') || (arr[*i2][*(j2)-1] != '*'))
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 + 1][*j1 - 1]);
			(*i1)++;
			(*j1)--;

			return;
		}
	}

	else if (*j1 < *j2)
	{
		if ((*i1 == 11) || (*i2 == 11) || (arr[*i1 + 1][*j1] != '*') || (arr[*i2 + 1][*j2] != '*'))
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 + 1][*j1 + 1]);
			(*i1)++;
			(*j1)++;

			return;
		}
	}

	else if (*i1 > *i2)
	{
		if ((*j1 == col - 1) || (*j2 == col - 1) || (arr[*i1][*(j1)+1] != '*') || (arr[*i2][*(j2)+1] != '*'))
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 - 1][*j1 + 1]);
			(*i1)--;
			(*j1)++;

			return;
		}
	}

	else if (*j1 > *j2)
	{
		if ((*i1 == 0) || (*i2 == 0) || (arr[*i1 - 1][*j1] != '*') || (arr[*i2 - 1][*j2] != '*'))
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 - 1][*j1 - 1]);
			(*i1)--;
			(*j1)--;

			return;
		}
	}
}

void turnright(char arr[][col], int* i1, int* j1, int* i2, int* j2)
//move함수군에 속한 다섯번째 함수
//사용자가 조종하는 블록 2칸을 시계방향으로 회전시키는 함수, 회전축이 되는 블록은 arr[*i2][*j2]임
//arr[*i1][*i2]가 회전할 수 없는 경우 아무런 일도 일어나지 않음
//이 함수가 호출하는 다른 함수 : swap
{
	if (*i1 < *i2)
	{
		if ((*j1 == col - 1) || (*j2 == col - 1) || (arr[*i1][*(j1)+1] != '*') || (arr[*i2][*(j2)+1] != '*'))
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 + 1][*j1 + 1]);
			(*i1)++;
			(*j1)++;

			return;
		}
	}

	else if (*j1 < *j2)
	{
		if ((*i1 == 0) || (*i2 == 0) || (arr[*i1 - 1][*j1] != '*') || arr[*i2 - 1][*j2] != '*')
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 - 1][*j1 + 1]);
			(*i1)--;
			(*j1)++;

			return;
		}
	}

	else if (*i1 > *i2)
	{
		if ((*j1 == 0) || (*j2 == 0) || (arr[*i1][*(j1)-1] != '*') || arr[*i2][*(j2)-1] != '*')
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 - 1][*j1 - 1]);
			(*i1)--;
			(*j1)--;

			return;
		}
	}

	else if (*j1 > *j2)
	{
		if ((*i1 == 11) || (*i2 == 11) || (arr[*i1 + 1][*j1] != '*') || arr[*i2 + 1][*j2] != '*')
			return;

		else
		{
			swap(&arr[*i1][*j1], &arr[*i1 + 1][*j1 - 1]);
			(*i1)++;
			(*j1)--;

			return;
		}
	}
}

int gameover(char block)
//게임 오버를 확인하는 함수
//반환값이 1이면 게임 오버, 0이면 게임오버가 아닌 상태
//arr[2][2]가 빈 공간이 아니라면 게임오버
{
	if (block == '*')
		return 0;

	else
		return 1;
}

void clearbuffer(void)
//버퍼를 비우는 함수
//사용자가 이전 턴에 입력한 여러 값 때문에 다음 턴에 입력을 건너뛰고 진행되는 것을 방지함
{
	while (getchar() != '\n');

	return;
}

void gravity(char(*arr)[col])
//게임판에 중력을 적용시키는 함수
//게임판의 각 열을 읽어, 빈 공간 위에 블록들이 있는 경우 그 블록들을 최대한 아래로 내림
//이 함수가 호출하는 다른 함수 : swap, showscreen
{

	for (int j = 0; j < col; j++)
	{

		for (int i = row - 1; i >= 0; i--)
		{

			while ((arr[i][j] != '*') && (arr[i + 1][j] == '*'))
			{
				swap(&arr[i][j], &arr[i + 1][j]);
				i++;

				system("cls");
				showscreen(arr);
			}
		}
	}

	return;
}

void combocheck(char(*arr)[col], char color, char puyo, int i, int j)
//erase함수군에 속한 첫번째 함수
//arr[i][j]를 combocheck에 대입하면 arr[i][j]와 이웃해있는 동일한 색상의 블록들의 개수 + 1를 반환
//재귀함수이다
{
	if (i == -1 || i == row)
		return;

	else if (j == -1 || j == col)
		return;

	else if (puyo != color)
		return;

	else
	{
		if (save[i][j] == 1)
			return;

		save[i][j] = 1;
		(*combo)++;

		combocheck(arr, color, arr[i + 1][j], i + 1, j);
		combocheck(arr, color, arr[i][j + 1], i, j + 1);
		combocheck(arr, color, arr[i - 1][j], i - 1, j);
		combocheck(arr, color, arr[i][j - 1], i, j - 1);

		return;
	}
}

void erase1(char(*arr)[col], char color, char puyo, int i, int j)
//erase함수군에 속한 두번째 함수
//arr[i][j]를 erase1에 대입하면 arr[i][j]와 arr[i][j]와 이웃해있는 동일한 색상의 블록들이 하얀 색상의 블록들로 바뀜
//게임 플레이 도중 시각적 재미를 위해 만들어진 함수
//재귀함수이다
{
	if (arr[i][j] == '*')
		return;

	else if (i == -1 || i == row)
		return;

	else if (j == -1 || j == col)
		return;

	else if (puyo != color)
		return;

	else
	{
		arr[i][j] = 'P';

		erase1(arr, color, arr[i + 1][j], i + 1, j);
		erase1(arr, color, arr[i][j + 1], i, j + 1);
		erase1(arr, color, arr[i - 1][j], i - 1, j);
		erase1(arr, color, arr[i][j - 1], i, j - 1);

		return;
	}
}

void erase2(char(*arr)[col], char color, char puyo, int i, int j)
//erase함수군에 속한 세번째 함수
//arr[i][j]를 erase1에 대입하면 arr[i][j]와 arr[i][j]와 이웃해있는 동일한 색상의 블록들이 빈 공간으로 바뀜
//재귀함수이다
{
	if (arr[i][j] == '*')
		return;

	else if (i == -1 || i == row)
		return;

	else if (j == -1 || j == col)
		return;

	else if (puyo != color)
		return;

	else
	{
		arr[i][j] = '*';

		erase2(arr, color, arr[i + 1][j], i + 1, j);
		erase2(arr, color, arr[i][j + 1], i, j + 1);
		erase2(arr, color, arr[i - 1][j], i - 1, j);
		erase2(arr, color, arr[i][j - 1], i, j - 1);

		return;
	}
}

void sound(int chain)
//효과음을 발생시키는 함수
//현재가 몇 연쇄이냐에 따라 이에 해당하는 효과음이 발생함
{
	switch (chain)
	{
	case 0: break;
	case 1: Beep(65 * 8, 500); break; //낮은 도
	case 2: Beep(73 * 8, 500); break; //레
	case 3: Beep(82 * 8, 500); break; //미
	case 4: Beep(87 * 8, 500); break; //파
	case 5: Beep(97 * 8, 500); break; //솔
	case 6: Beep(110 * 8, 500); break; //라
	case 7: Beep(123 * 8, 500); break; //시
	default: Beep(130 * 8, 500); break; //높은 도
	}

	return;
}

void erasecheck(char(*arr)[col])
//erase함수군에 속한 네번째 함수
//erase함수군의 나머지 3가지 함수를 사용하여 게임판 내에서 동일한 색상이 4 블록 이상 이웃해 있는 경우 그 블록들을 하얗게 바꾼 뒤 효과음을 출력하고 그 블록들을 없앰
//이 함수가 호출하는 다른 함수 : combocheck, erase1, erase2, showscreen, gravity
//재귀함수이다
{
	int same = 1;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			*combo = 0;

			if (arr[i][j] == '*')
				continue;

			else
				combocheck(arr, arr[i][j], arr[i][j], i, j);

			if (*combo >= 4)
			{
				same = 0;

				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						save[i][j] = '\0';

				nowchain++;

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				erase1(arr, arr[i][j], arr[i][j], i, j);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

				system("cls");
				showscreen(arr);
				Sleep(1);
				sound(nowchain);

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				erase2(arr, arr[i][j], arr[i][j], i, j);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

				system("cls");
				showscreen(arr);
				Sleep(1);
			}

			else
			{
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						save[i][j] = '\0';
			}
		}
	}

	if (same == 1)
		return;

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			save[i][j] = '\0';

	gravity(arr);
	erasecheck(arr);

	return;
}