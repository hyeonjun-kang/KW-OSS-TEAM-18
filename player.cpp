#include "player.h"
#include "Dice.h"
#include <iostream>
#include <ctime>
#include <random>

using namespace std;

void player_order(player p1, player p2)
{
	printf("순서 정하기 더 높은 주사위가 나온 사람부터\n");
	printf("player1 throw\n");
	//버튼을 눌러 주사위 굴리기
	srand(time(NULL));
	int dice1 = rand() % 6 + 1;
	printf("player1 dice : %d\n", dice1);

	printf("player2 throw\n");
	//버튼을 눌러 주사위 굴리기
	int dice2 = rand() % 6 + 1;
	printf("player2 dice : %d\n", dice2);
	if (dice1 > dice2) {
		p1.set_order(1);
		p2.set_order(2);
	}
	else {
		p1.set_order(2);
		p2.set_order(1);
	}
}

bool player_win(player p1, player p2)
{
	if (p1.get_order() == 1)
	{
		if (p1.get_many_ground() == 18)
			return true;
		else if (p2.get_many_ground() == 18)
			return false;
	}
	else
	{
		if (p2.get_many_ground() == 18)
			return false;
		else if (p1.get_many_ground() == 18)
			return true;
	}
	
}