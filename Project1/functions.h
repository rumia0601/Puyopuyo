//�Լ� �������
//���� �Լ����� ���Ǵ� 17������ �Լ����� ������

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
//�ܼ� ��µǴ� ������ �����ϴ� �Լ�
//arr[i][j]�� ������ color�� ��ȯ���� setconsoletextattribute�Լ��� �����ϸ� arr[i][j]�� �ش��ϴ� �������� �ܼ� ��� ������ �ٲ�
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
//�������� ����ϴ� �Լ�
//�������� 7���� ���� �����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : color
{
	printf("                     \n");
	for (int count1 = 2; count1 < row; count1++)
	{
		printf("  ");
		for (int count2 = 0; count2 < col; count2++)
		{
			if (arr[count1][count2] == '*')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); //�� ������ ȸ�� ��
				printf("* ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color(&(arr[count1][count2])));
				printf("%c ", set.shape); //��µǴ� ��ϵ��� ����� set.shape
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
	printf("q = �ݽð�������� ȸ��     w = �ִ��� �Ʒ��� �̵�     e = �ð�������� ȸ��\n");
	printf("a = �������� �̵�           s = �Ʒ��� �̵�            d = ���������� �̵�\n");
	printf("�Է��� Ű : ");

	return;
}

void randomize(char* point)
//��� ������ �������� �����ϴ� �Լ�
//�����Ǵ� ��ϵ��� ������ ������ ���� set.number, set.color[i]
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
//Call by reference ���� �Լ�
//������ ���� ��ϵ��� �̵��� ���� �׻� �� �Լ��� ȣ���
{
	char save;
	save = *a;
	*a = *b;
	*b = save;

	return;
}

void movedown(char arr[][col], int* i1, int* j1, int* i2, int* j2)
//move�Լ����� ���� ù��° �Լ�
//����ڰ� �����ϴ� ��� 2ĭ�� �� �� �Ʒ��� 1ĭ�� �̵���Ű�� �Լ�
//�� �� �ϳ��� �Ʒ��� 1ĭ ������ �� ������ �ƹ��� �ϵ� �Ͼ�� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : swap
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
//move�Լ����� ���� �ι�° �Լ�
//����ڰ� �����ϴ� ��� 2ĭ�� �� �� �������� 1ĭ�� �̵���Ű�� �Լ�
//�� �� �ϳ��� �������� 1ĭ �̵��� �� ������ �ƹ��� �ϵ� �Ͼ�� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : swap
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
//move�Լ����� ���� ����° �Լ�
//����ڰ� �����ϴ� ��� 2ĭ�� �� �� ���������� 1ĭ�� �̵���Ű�� �Լ�
//�� �� �ϳ��� ���������� 1ĭ �̵��� �� ������ �ƹ��� �ϵ� �Ͼ�� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : swap
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
//move�Լ����� ���� �׹�° �Լ�
//����ڰ� �����ϴ� ��� 2ĭ�� �ݽð�������� ȸ����Ű�� �Լ�, ȸ������ �Ǵ� ����� arr[*i2][*j2]��
//arr[*i1][*i2]�� ȸ���� �� ���� ��� �ƹ��� �ϵ� �Ͼ�� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : swap
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
//move�Լ����� ���� �ټ���° �Լ�
//����ڰ� �����ϴ� ��� 2ĭ�� �ð�������� ȸ����Ű�� �Լ�, ȸ������ �Ǵ� ����� arr[*i2][*j2]��
//arr[*i1][*i2]�� ȸ���� �� ���� ��� �ƹ��� �ϵ� �Ͼ�� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : swap
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
//���� ������ Ȯ���ϴ� �Լ�
//��ȯ���� 1�̸� ���� ����, 0�̸� ���ӿ����� �ƴ� ����
//arr[2][2]�� �� ������ �ƴ϶�� ���ӿ���
{
	if (block == '*')
		return 0;

	else
		return 1;
}

void clearbuffer(void)
//���۸� ���� �Լ�
//����ڰ� ���� �Ͽ� �Է��� ���� �� ������ ���� �Ͽ� �Է��� �ǳʶٰ� ����Ǵ� ���� ������
{
	while (getchar() != '\n');

	return;
}

void gravity(char(*arr)[col])
//�����ǿ� �߷��� �����Ű�� �Լ�
//�������� �� ���� �о�, �� ���� ���� ��ϵ��� �ִ� ��� �� ��ϵ��� �ִ��� �Ʒ��� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : swap, showscreen
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
//erase�Լ����� ���� ù��° �Լ�
//arr[i][j]�� combocheck�� �����ϸ� arr[i][j]�� �̿����ִ� ������ ������ ��ϵ��� ���� + 1�� ��ȯ
//����Լ��̴�
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
//erase�Լ����� ���� �ι�° �Լ�
//arr[i][j]�� erase1�� �����ϸ� arr[i][j]�� arr[i][j]�� �̿����ִ� ������ ������ ��ϵ��� �Ͼ� ������ ��ϵ�� �ٲ�
//���� �÷��� ���� �ð��� ��̸� ���� ������� �Լ�
//����Լ��̴�
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
//erase�Լ����� ���� ����° �Լ�
//arr[i][j]�� erase1�� �����ϸ� arr[i][j]�� arr[i][j]�� �̿����ִ� ������ ������ ��ϵ��� �� �������� �ٲ�
//����Լ��̴�
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
//ȿ������ �߻���Ű�� �Լ�
//���簡 �� �����̳Ŀ� ���� �̿� �ش��ϴ� ȿ������ �߻���
{
	switch (chain)
	{
	case 0: break;
	case 1: Beep(65 * 8, 500); break; //���� ��
	case 2: Beep(73 * 8, 500); break; //��
	case 3: Beep(82 * 8, 500); break; //��
	case 4: Beep(87 * 8, 500); break; //��
	case 5: Beep(97 * 8, 500); break; //��
	case 6: Beep(110 * 8, 500); break; //��
	case 7: Beep(123 * 8, 500); break; //��
	default: Beep(130 * 8, 500); break; //���� ��
	}

	return;
}

void erasecheck(char(*arr)[col])
//erase�Լ����� ���� �׹�° �Լ�
//erase�Լ����� ������ 3���� �Լ��� ����Ͽ� ������ ������ ������ ������ 4 ��� �̻� �̿��� �ִ� ��� �� ��ϵ��� �Ͼ�� �ٲ� �� ȿ������ ����ϰ� �� ��ϵ��� ����
//�� �Լ��� ȣ���ϴ� �ٸ� �Լ� : combocheck, erase1, erase2, showscreen, gravity
//����Լ��̴�
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