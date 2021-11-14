#ifndef _player_H_
#define _player_H_
#include<iostream>

using namespace std;

class player {
public:
	player() {
		order = 0;
		many_ground = 0;
	}

	int get_order() { return order; }
	int get_many_ground() { return many_ground; }
	void set_order(int num) { order = num; }
	void set_many_ground(int many) { many_ground = many; }

private:
	int order;
	int many_ground;
};

void player_order(player p1, player p2);
bool player_win(player p1, player p2);

#endif