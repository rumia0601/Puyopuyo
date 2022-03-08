//���� �Լ�
//������ ����Ǹ� Ÿ��Ʋ �Լ��� �ǵ��ư�
//�ܺ� �ؽ�Ʈ����(Test.txt)�� ������ �о� arr[i][j]�� �����ϴ� ������ ����

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
	//���� ���� �κ�
	//���ӿ� ����� ������������ �����ϰ�, �������� ����� �� ȿ������ �߻���Ű�� netxpuyo�� nowpuyo�� �ٲ� �� ������ ���� �÷����´�

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
	Beep(130 * 8, 1000); //��� : �������ļֶ�õ� (�����ϴ� ����)

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
			//���� ����� ����ϱ� ���� ó���Ǵ� �κ�
			//������ ���� ����� 4�� �̻� �̿��ϴ��� �ƴ����� �Ǵ�
			//�̿��ϸ� ����, ���⸦ ����Ű�� ���� ����� ���
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
			//���� ���� �κ�
			//���� �����ǰ� ���� ������ ����ϰ� ȿ������ �߻���Ų �� ������ �����Ѵ�
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
				Beep(65 * 8, 1000); //��� : ���ö���Ĺ̷��� (������ ����)

				nowchain = 0;
				highestchain = 0;
				latestchain = 0;

				printf("�ƹ�Ű�� �Է��ϸ� Ÿ��Ʋ ȭ������ ���ư��ϴ� : ");
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

		do //set.speed��� �ð����� ����ڷκ��� Ű�� �Է¹���. �־��� �ð� �� Ű�� �Է¹��� ���� ��� Ű�� ������ 'n'�� ��
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

		if (*key == 's' || *key == 'S') //��� 2ĭ�� �Ʒ��� �̵�
		{
			movedown(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'a' || *key == 'A') //��� 2ĭ�� �������� �̵�
		{
			moveleft(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'd' || *key == 'D') //��� 2ĭ�� ���������� �̵�
		{
			moveright(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'w' || *key == 'W') //��� 2ĭ�� �ִ��� �Ʒ��� �̵���Ű�� ���� ����� �����
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
			randomize(&nextnextpuyo2); //���� ����� ������ �������, �ٴ��� ����� ���� ������� �ٲ� �� �ٴ��� ����� ���� ����

			finish = 1;
		}

		else if (*key == 'q' || *key == 'Q') //��� 2ĭ�� �ݽð� �������� ȸ��
		{
			turnleft(arr, i1, j1, i2, j2);
			finish = 0;
		}

		else if (*key == 'e' || *key == 'E') //��� 2ĭ�� �ݽð� �������� ȸ��
		{
			turnright(arr, i1, j1, i2, j2);
			finish = 0;
		}
		
		else if (*key == 'p' || *key == 'P') //ġƮŰ�� �Է��� ��� ������ ������ �������� �̸� ���س��� ������ �ٲ�
		{
			char ch;
			FILE *fp;

			fp = fopen("Cheat.txt", "r");

			for (int i = 0; i < row; i++) //Cheat.txt�� ���� �ִ� 0, 1, 2, 3, 4, 5���� ������ ���� ��ϵ�� �ٲ�
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

		else if (*key == 'n') //�ð��� ����� ��� ��� 2ĭ�� �Ʒ��� 1ĭ �����ų� ���� ����� �����
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
				randomize(&nextnextpuyo2); //���� ����� ������ �������, �ٴ��� ����� ���� ������� �ٲ� �� �ٴ��� ����� ���� ����

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
				randomize(&nextnextpuyo2); //���� ����� ������ �������, �ٴ��� ����� ���� ������� �ٲ� �� �ٴ��� ����� ���� ����

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
				randomize(&nextnextpuyo2); //���� ����� ������ �������, �ٴ��� ����� ���� ������� �ٲ� �� �ٴ��� ����� ���� ����

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
				randomize(&nextnextpuyo2); //���� ����� ������ �������, �ٴ��� ����� ���� ������� �ٲ� �� �ٴ��� ����� ���� ����

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