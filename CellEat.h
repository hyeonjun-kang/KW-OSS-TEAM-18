#ifndef _CELLEAT_
#define _CELLEAT_
#include <iostream>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


using namespace std;

enum {ROW = 6, COL = 6};
 int orignMap[ROW][COL] = {
	{1, 1, 2, 2, 3, 3},
	{4, 4, 5, 5, 6, 6},
	{8, 8, 9, 9, 10, 10},
	{12, 12, 15, 15, 16, 16},
	{18, 18, 20, 20, 24, 24},
	{25, 25, 30, 30, 36, 36} };
class CellEater
{
private:
	int row, col;
	void setRow(int row) { this->row = row; };
	void setCol(int col) { this->col = col; };
	int getRow() { return row; };
	int getCol() { return col; };
public:

	void mapDisplay()
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if(orignMap[i][j] != 0)
				{
					if (orignMap[i][j] < 10)
					{
						printf(ANSI_COLOR_YELLOW"0%d " ANSI_COLOR_RESET, orignMap[i][j]);
					}
					else
						printf(ANSI_COLOR_YELLOW"%d " ANSI_COLOR_RESET, orignMap[i][j]);
				}

				else
				{
					printf(ANSI_COLOR_RED"0%d " ANSI_COLOR_RESET, orignMap[i][j]);
				}
			}
			printf("\n");
		}
	}


	bool isAvailable(int target)
	{
		for (int row = 0; row < ROW; row++)
		{
			for (int col = 0; col < COL; col++)
			{
				if (orignMap[row][col] == target)
				{
					setCol(col);
					setRow(row);
					return true;
				}
			}
		}
		return false;
	};

	void checkCell()
	{
		char act;
		int score = 0;
		Dice callDice = Dice();
		printf("Your Field:\n");
		mapDisplay();
		while (score != 12)
		{
			printf("[1] throw dice [2] stop");
			scanf("%c",&act);
			if (act == '1')
			{
				int target = callDice.GetDiceValue();
				printf("Dice Throw = %d\n", target);
				if (isAvailable(target))
				{
					orignMap[getRow()][getCol()] = 0;
					score++;
					mapDisplay();
				}
				printf("Score is %d\n", score);
			}
			else if (act == '2')
			{
				printf("Score is %d",score);
				break;
			}
		}

	

	};
};
#endif