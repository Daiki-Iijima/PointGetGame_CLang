#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

void InitBord();
void GetKey(int*, int*);
void EnemyUpdate(int*, int*);
void CreatePoint(int);
void BordUpdate(int, int, int, int);
void Draw();

#define BORD '+'
#define PLAYER 'P'
#define ENEMY 'E'
#define POINT 'U'
#define HEIGHT 10
#define WIDTH 10

char BordMap[HEIGHT][WIDTH];
int Count;
int ClearFlag = 0;

int main()
{
	int PlayerHeightPoint = 0;
	int PlayerWidthPoint = 0;
	int EnemyHeightPoint = 0;
	int EnemyWidthPoint = 0;
	int PointHeightPoint = 0;
	int PointWidthPoint = 0;

	InitBord();									//	������
	CreatePoint(10);

	//	���C�����[�v
	for (;;)
	{
		//	�N���A�`�F�b�N
		int _h, _w, _c = 0;
		for (_h = 0; _h < HEIGHT; _h++)
		{
			for (_w = 0; _w < WIDTH; _w++)
			{
				if (BordMap[_h][_w] == POINT) _c++;
			}
		}

		if (_c == 0) { ClearFlag = 1; }

		GetKey(&PlayerHeightPoint, &PlayerWidthPoint);		//	�L�[���͂��擾
		EnemyUpdate(&EnemyHeightPoint, &EnemyWidthPoint);

		//	�|�C���g���l������
		if (BordMap[PlayerHeightPoint][PlayerWidthPoint] == POINT)
		{
			Count++;
		}

		BordUpdate(PlayerHeightPoint, PlayerWidthPoint, EnemyHeightPoint, EnemyWidthPoint);		//	�{�[�h�̏���
		Draw();									//	�`��
	}
}

void InitBord()
{
	int _h, _w;
	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			BordMap[_h][_w] = BORD;		//	�{�[�h��`��
		}
	}

	BordMap[0][0] = PLAYER;			//	�����z�u
	BordMap[3][3] = ENEMY;

	Draw();
}

void GetKey(int* h, int* w)
{
	switch (getch()) {
	case 72:    // key up
		*h = *h - 1;
		break;
	case 80:    // key down
		*h = *h + 1;
		break;
	case 77:    // key right
		*w = *w + 1;
		break;
	case 75:    // key left
		*w = *w - 1;
		break;
	default:
		return;
		break;
	}

	//	�ړ��̏����ݒ�
	if (*h < 0) *h = 0;
	if (*w < 0) *w = 0;
	if (*h > HEIGHT - 1)*h = HEIGHT - 1;
	if (*w > WIDTH - 1) *w = WIDTH - 1;
}

void EnemyUpdate(int* h, int* w)
{
	// ������������������
	int r;

	//  �����̏�����
	srand((unsigned)time(NULL));

	*h = rand() % (10 + 1);
	*w = rand() % (10 + 1);
}

void CreatePoint(int createPoint)
{
	// ������������������
	int r;

	//  �����̏�����
	srand((unsigned)time(NULL));

	for (int i = 0; i < createPoint; i++)
	{
		BordMap[rand() % (10 + 1)][rand() % (10 + 1)] = POINT;
	}
}

void BordUpdate(int ph, int pw, int eh, int ew)
{
	int _h, _w;

	BordMap[ph][pw] = PLAYER;					//	�v���C���[�̈ʒu���X�V
	BordMap[eh][ew] = ENEMY;					//	�G�̈ʒu���X�V

	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			if (_w == pw && _h == ph) continue;
			if (_w == ew && _h == eh) continue;
			if (BordMap[_h][_w] == POINT) continue;

			BordMap[_h][_w] = BORD;		//	�{�[�h�̏����X�V
		}
	}
}

void Draw()
{
	int _h, _w;

	system("cls");								//	��ʂ��N���A

	if (ClearFlag == 1) { printf("�N���A!!!\n���̃��x���ɍs���ɂ́H"); return; }

	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			printf("%2c", BordMap[_h][_w]);		//	�{�[�h��`��
		}
		printf("\n");
	}

	printf("�l���|�C���g:%d", Count);

}