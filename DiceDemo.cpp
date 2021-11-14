#include <iostream>
#include <vector>
#include "Dice.h"
#include <random>
#include <ctime>

using namespace std;

int main() {
	
	Dice obj1 = Dice();
	char inp;
	cout << "Press [1] to Throw      Press any button to stop" << endl;
	cin >> inp;
	while (inp == '1')
	{
		obj1.ThrowDice();
		cin >> inp;
	}

	return 0;
}

