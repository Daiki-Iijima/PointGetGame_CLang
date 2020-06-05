#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct
{
	int X;
	int Y;
}Point;

void InitBord();
void GetKey(Point*);
void CreatePoint(int);
void BordUpdate(Point);
void Draw();

#define BORD '+'
#define PLAYER 'P'
#define POINT 'U'
#define HEIGHT 10
#define WIDTH 10

char BordMap[WIDTH][HEIGHT];
int Count;
int ClearFlag = 0;


int main()
{
	Point PlayerPoint = {0,0};
	Point ScorePoint[10];

	InitBord(PlayerPoint);							//	������
	BordMap[PlayerPoint.X][PlayerPoint.Y] = PLAYER;	//	�����z�u
	CreatePoint(10);								//	�X�R�A��z�u
	Draw();											//	�`��


	//	���C�����[�v
	for (;;)
	{
		GetKey(&PlayerPoint);		//	�L�[���͂��擾

		//	�|�C���g���l������
		if (BordMap[PlayerPoint.X][PlayerPoint.Y] == POINT)
		{
			Count++;
		}

		BordUpdate(PlayerPoint);		//	�{�[�h�̏���

		//	�N���A�`�F�b�N
		int _h, _w, _c = 0;
		for (_h = 0; _h < HEIGHT; _h++)
		{
			for (_w = 0; _w < WIDTH; _w++)
			{
				if (BordMap[_w][_h] == POINT) _c++;
			}
		}

		if (_c == 0) { 
			
			ClearFlag = 1;

			InitBord(PlayerPoint);							//	������
			BordMap[PlayerPoint.X][PlayerPoint.Y] = PLAYER;	//	�����z�u
			CreatePoint(10);								//	�X�R�A��z�u
		
		}


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
			BordMap[_w][_h] = BORD;		//	�{�[�h�������l�Ŗ��߂�
		}
	}
}

void GetKey(Point *playerPos)
{
	switch (getch()) {
	case 72:    // key up
		playerPos->Y = playerPos->Y - 1;
		break;
	case 80:    // key down
		playerPos->Y = playerPos->Y + 1;
		break;
	case 77:    // key right
		playerPos->X = playerPos->X + 1;
		break;
	case 75:    // key left
		playerPos->X = playerPos->X - 1;
		break;
	default:
		return;
		break;
	}

	//	�ړ��̏����ݒ�
	if (playerPos->Y < 0) playerPos->Y = 0;
	if (playerPos->X < 0) playerPos->X = 0;
	if (playerPos->Y > HEIGHT - 1)playerPos->Y = HEIGHT - 1;
	if (playerPos->X > WIDTH - 1) playerPos->X = WIDTH - 1;
}

void CreatePoint(int createPoint)
{
	// ������������������
	int r;

	//  �����̏�����
	srand((unsigned)time(NULL));

	for (int i = 0; i < createPoint; i++)
	{
		BordMap[rand() % (WIDTH + 1)][rand() % (HEIGHT + 1)] = POINT;
	}
}

void BordUpdate(Point player)
{
	int _h, _w;

	BordMap[player.X][player.Y] = PLAYER;					//	�v���C���[�̈ʒu���X�V

	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			if (_w == player.X && _h == player.Y) continue;
			if (BordMap[_w][_h] == POINT) continue;

			BordMap[_w][_h] = BORD;		//	�{�[�h�̏����X�V
		}
	}
}

void Draw()
{
	char get[256];
	int _h, _w;

	system("cls");								//	��ʂ��N���A

	//	�Q�[���N���A��
	if (ClearFlag == 1) { 
		
		printf("�N���A!!!\n������x�v���C����ɂ́ur�v�L�[�������Ă�������\n����ȊO�̃L�[����͂���ƏI�����܂�"); 
		
		scanf("%s", get);
		if (get[0]=='r')
		{
			ClearFlag = 0;	//	�ĊJ
		}
		else
		{
			exit(0);		//	�I��
		}
	}

	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			printf("%2c", BordMap[_w][_h]);		//	�{�[�h��`��
		}
		printf("\n");
	}

	printf("�l���|�C���g:%d", Count);

}