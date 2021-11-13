#include<iostream>
#include<Windows.h>
#include<conio.h>

using namespace std;

#define INIT_POS 1

//-----------------------------------------
//콘솔 내부의 특정 위치로 커서를 이동하는 함수.
void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//콘솔 창 크기와 제목을 관리하는 함수.
void SetConsoleView()
{
	system("mode con:cols=80 lines=20");
	system("title Dice Game");
}

//키보드 입력 감지 및 입력된 키보드를 반환하는 함수.
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}
//-----------------------------------------
//2차원 배열로 이루어진 맵
const int originMap[6][6] = { {1, 1, 2, 2, 3, 3},
								{4, 4, 5, 5, 6, 6},
								{8, 8, 9, 9, 10, 10},
								{12, 12, 15, 15, 16, 16},
								{18, 18, 20, 20, 24, 24},
								{25, 25, 30, 30, 36, 36} };

//포지션 구조체
struct Pos
{
	int x;
	int y;
};

//키보드 입력을 저장해 놓은 enum
enum KEYBOARD
{
	IS_ARROW = 224,
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	SPACE = 32,
};

//색상을 저장해놓은 enum
enum COLOR
{
	GREEN = 10,
	MINT,
	RED,
	PINK,
	YELLOW,
	WHITE,
};

//게임 매니저 클래스
class GameManager
{
private:
	Pos player;				//플레이어 커서 위치.
	int spaceCount;			//뒤집은 횟수.
	int player1Count;		//player1 영토 갯수
	int player2Count;		//plyaer2 영토 갯수
	int colorMap[6][6];//땅 색깔 저장 함수,p1은 GREEN p2는 RED
	bool turn;//누구 차례인지에 대한 변수, TRUE면 P1, FALSE 면 P2
public:
	void StartGame()
	{
		Init();		//게임 초기화
		DrawBack();	//배경 그리기

		//게임 루프 시작
		int key = 0;
		while (true)//게임 끝나는 조건 함수 넣기
		{
			
			key = GetKeyDown();	//키 입력 받는 함수
			if (key == KEYBOARD::IS_ARROW)
			{
				//화살표들.
				MovePos();
			}
			if (key == KEYBOARD::SPACE)//현재 좌표 ColorMap 색 바꾸고 그 플레이어의 영토수 +1
			{
				if (turn == false) {
					if (colorMap[player.y][player.x] == GREEN) {//만약 이미 땅이 상대방이 색깔이면, 상대방 땅 갯수 -1 후 자신의 색으로 변경후 한번의 기회 더 가짐
						colorMap[player.y][player.x] = RED;
						player2Count++;
						player1Count--;
					}
					else {
						colorMap[player.y][player.x] = RED;
						player2Count++;
						turn = true;
					}
				}
				else{
					if (colorMap[player.y][player.x] == RED) {//만약 이미 땅이 상대방이 색깔이면, 상대방 땅 갯수 -1 후 자신의 색으로 변경후 한번의 기회 더 가짐
						colorMap[player.y][player.x] = GREEN;
						player1Count++;
						player2Count--;
					}
					else {
						colorMap[player.y][player.x] = GREEN;
						player1Count++;
						turn = false;
					}
				}

			}
			//draw
			DrawMain();
			score();
			Sleep(100);
			if ((player1Count + player2Count) == 36) {
				DrawGameClear();
				break;
			}
		}
	}

	//맵 초기화
	void Init()
	{
		player.x = 0;
		player.y = 0;
		spaceCount = 0;
		player1Count = 0;
		player2Count = 0;
		for (int i = 0; i < 6; i++) {
			for (int k = 0; k < 6; k++) {
				colorMap[i][k] = 0;
			}
		}
		turn = true;
		
	}
	void score(){//각 플레이어 먹은 땅 갯수 출력 함수
		GotoXY(25, 6);
		printf("□    %02d     □     %02d    □", player1Count, player2Count);
	}


	//커서의 위치 이동
	void MovePos()
	{
		GotoXY(INIT_POS + (player.x * 4), INIT_POS + (player.y * 2) + 1);
		printf("  ");

		//키보드 입력을 받아서, 해당 위치로 이동을 시켜준다.
		switch (_getch())
		{
		case KEYBOARD::LEFT:
			--player.x;
			if (player.x <= 0)
			{
				player.x = 0;
			}
			break;
		case KEYBOARD::RIGHT:
			++player.x;
			if (player.x >= 5)
			{
				player.x = 5;
			}
			break;
		case KEYBOARD::UP:
			--player.y;
			if (player.y <= 0)
			{
				player.y = 0;
			}
			break;
		case KEYBOARD::DOWN:
			++player.y;
			if (player.y >= 5)
			{
				player.y = 5;
			}
			break;
		}
	}

	void DrawMain()
	{
		//map draw
		SetTextColor(WHITE);
		int d = 0;
		int c;
		for (int y = 0; y < 6; ++y)
		{
			GotoXY(INIT_POS, INIT_POS + (2 * y));
			for (int x = 0; x < 6; ++x)
			{
				c = colorMap[y][x];
				if(c == GREEN){ SetTextColor(GREEN); }//color맵에 따라 색 칠하기
				else if(c==RED){ SetTextColor(RED); }
				else{ SetTextColor(WHITE); }
				d = originMap[y][x];
				printf("[%02d]    ", d);
				SetTextColor(WHITE);
			}
		}
		SetTextColor(WHITE);
	
		//player draw
		GotoXY(INIT_POS + (player.x * 4), INIT_POS + (player.y * 2) + 1);
		printf(" ^");


		GotoXY(25, 1);
		printf("Press Space Bar");
	}

	void DrawBack()
	{
		SetTextColor(WHITE);
		GotoXY(25, 5);
		cout << "□□player1□□□player2□□";
		GotoXY(25, 7);
		cout << "□           □           □";
		GotoXY(25, 8);
		cout << "□□□□□□□□□□□□□□";
		GotoXY(25, 10);
		cout << "Kwang Woon Univ";
		GotoXY(25, 11);
		cout << "OSS ";
		SetTextColor(PINK);
		cout << "team 18";
		SetTextColor(WHITE);
	}

	void DrawGameClear()
	{
		SetTextColor(YELLOW);
		GotoXY(3, 5);
		cout << "=========================";
		GotoXY(3, 6);
		cout << "======= C L E A R =======";
		GotoXY(3, 7);
		cout << "=========================";
		SetTextColor(WHITE);
	}

	void SetTextColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};

//메인함수
int main(void)
{
	SetConsoleView();
	GameManager* pGameMgr = new GameManager();
	pGameMgr->StartGame();
	delete(pGameMgr);
	return 0;
}
