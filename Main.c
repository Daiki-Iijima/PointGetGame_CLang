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

	InitBord(PlayerPoint);							//	初期化
	BordMap[PlayerPoint.X][PlayerPoint.Y] = PLAYER;	//	初期配置
	CreatePoint(10);								//	スコアを配置
	Draw();											//	描画


	//	メインループ
	for (;;)
	{
		GetKey(&PlayerPoint);		//	キー入力を取得

		//	ポイントを獲得する
		if (BordMap[PlayerPoint.X][PlayerPoint.Y] == POINT)
		{
			Count++;
		}

		BordUpdate(PlayerPoint);		//	ボードの情報を

		//	クリアチェック
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

			InitBord(PlayerPoint);							//	初期化
			BordMap[PlayerPoint.X][PlayerPoint.Y] = PLAYER;	//	初期配置
			CreatePoint(10);								//	スコアを配置
		
		}


		Draw();									//	描画
	}
}

void InitBord()
{
	int _h, _w;
	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			BordMap[_w][_h] = BORD;		//	ボードを初期値で埋める
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

	//	移動の上限を設定
	if (playerPos->Y < 0) playerPos->Y = 0;
	if (playerPos->X < 0) playerPos->X = 0;
	if (playerPos->Y > HEIGHT - 1)playerPos->Y = HEIGHT - 1;
	if (playerPos->X > WIDTH - 1) playerPos->X = WIDTH - 1;
}

void CreatePoint(int createPoint)
{
	// 生成した乱数を入れる
	int r;

	//  乱数の初期化
	srand((unsigned)time(NULL));

	for (int i = 0; i < createPoint; i++)
	{
		BordMap[rand() % (WIDTH + 1)][rand() % (HEIGHT + 1)] = POINT;
	}
}

void BordUpdate(Point player)
{
	int _h, _w;

	BordMap[player.X][player.Y] = PLAYER;					//	プレイヤーの位置を更新

	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			if (_w == player.X && _h == player.Y) continue;
			if (BordMap[_w][_h] == POINT) continue;

			BordMap[_w][_h] = BORD;		//	ボードの情報を更新
		}
	}
}

void Draw()
{
	char get[256];
	int _h, _w;

	system("cls");								//	画面をクリア

	//	ゲームクリア時
	if (ClearFlag == 1) { 
		
		printf("クリア!!!\nもう一度プレイするには「r」キーを押してください\nそれ以外のキーを入力すると終了します"); 
		
		scanf("%s", get);
		if (get[0]=='r')
		{
			ClearFlag = 0;	//	再開
		}
		else
		{
			exit(0);		//	終了
		}
	}

	for (_h = 0; _h < HEIGHT; _h++)
	{
		for (_w = 0; _w < WIDTH; _w++)
		{
			printf("%2c", BordMap[_w][_h]);		//	ボードを描画
		}
		printf("\n");
	}

	printf("獲得ポイント:%d", Count);

}