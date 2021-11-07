#ifndef _DICE_H_
#define _DICE_H_
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
using namespace std;
class Dice
{
private:
    vector<int> diceCube{ 1,2,3,4,5,6 };

    int shakeDice()
    {
        random_device rd;
        default_random_engine rng(rd());
        shuffle(begin(diceCube), end(diceCube), rng);
        srand(time(0));
        int RandIndx = rand() % diceCube.size();
        return diceCube[RandIndx];
    }

public:
    void ThrowDice()
    {
        int dice1 = shakeDice();
        int dice2 = shakeDice();
        cout <<"Dice One: "<< dice1 << " " <<"Dice Two: " << dice2 << endl;
    }

};
#endif
