#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <vector>
#include <chrono>
#include <dos.h>

using namespace std;

class score_board
{
public:
	void player_score_display(int, int);
};

void score_board::player_score_display(int points, int shots)
{
	int k;
	cout << "Brains: " << points << endl;
	cout << "Shots: " << shots << endl;
	for (int k = 0; k <= 25; k++)
	{
		cout << "*";
	}
}

class m_Dice
{
public:
	int side;
	int brains = 0;
	int shots = 0;
	bool re_roll = false;
	void green(int);
	void yellow(int);
	void red(int);
	
};

void m_Dice::green(int m_roll)
{
	re_roll = false;
	if (m_roll <= 3)
	{
		++brains;
		cout << "*** You got a brain!" << endl;

	}
	else if (m_roll ==4 || m_roll == 5)
	{
		re_roll = true;
		cout << "*** You got a reroll!" << endl;
	}
	else if (m_roll == 6)
	{
		++shots;
		cout << "*** You got shot!" << endl;
	}
}

void m_Dice::yellow(int m_roll)
{
	re_roll = false;
	if ((m_roll == 1 || m_roll ==  2))
	{
		++brains;
		cout << "*** You got a brain!" << endl;
	}
	else if ((m_roll == 3 || m_roll ==  4))
	{
		re_roll = true;
		cout << "*** You got a reroll!" << endl;
	}
	else if ((m_roll == 5 || m_roll == 6))
	{
		++shots;
		cout << "*** You got shot!" << endl;
	}
}

void m_Dice::red(int m_roll)
{
	re_roll = false;
	if (m_roll == 1)
	{
		++brains;
		cout << "*** You got a brain!" << endl;
	}
	else if ((m_roll ==  2 || m_roll ==  3))
	{
		re_roll = true;
		cout << "*** You got a reroll!" << endl;
	}
	else if ((m_roll >= 4))
	{
		++shots;
		cout << "*** You got shot!" << endl;
	}
}

void show_score(int b, int s)
{
	if (s == 0)
	{
		cout << "You have " << b << " brains and you haven't been shot yet!"<< endl;
	}
	else
	{
		cout << "You have " << b << " brains and you've been shot " << s << " times!" << endl;
	}
}
int roll() //to facilitate the roll of the dice
{
	int face = 0;
	face = rand() % 6 + 1;
	return face;
}

void perform(vector <int> total_dice)
{
	int count = 0;
	int board = 1;
	bool done = false;
	int green_reroll = 0;
	int yellow_reroll = 0;
	int red_reroll = 0;
	bool end_turn = false;
	bool no_select = false;
	m_Dice your_turn;
	vector <pair <string, bool>> roll_tracker{};//this is to store the # of rerolls so that rerolls can be performed on the current turn AND be carried forward in cases where rerolling yields another reroll
	int draw;
	string i;
	int temp;
	cout << "Your roll resulted in: \n";
	while (board < 4 && end_turn == false)
	{
		temp = 0;
		count = total_dice.size() - 1;
		temp = rand() % count + 0;
		draw = total_dice[temp];
		your_turn.re_roll = false;
		if (draw == 1)
		{
			cout << "A green die." << endl;
			your_turn.green(roll());
			if (your_turn.re_roll == true)
			{
				green_reroll++;
				your_turn.re_roll = false;
			}
			else if (your_turn.re_roll == false)
			{
				total_dice.erase(total_dice.begin() + temp);
			}
		}
		else if (draw == 2)
		{
			cout << "A yellow die." << endl;
			your_turn.yellow(roll());
			if (your_turn.re_roll == true)
			{
				yellow_reroll++;
				your_turn.re_roll = false;
			}
			else if (your_turn.re_roll == false)
			{
				total_dice.erase(total_dice.begin() + temp);
			}
		}
		else if (draw == 3)
		{
			cout << "A red die." << endl;
			your_turn.red(roll());
			if (your_turn.re_roll == true)
			{
				red_reroll++;
				your_turn.re_roll = false;
			}
			else if (your_turn.re_roll == false)
			{
				total_dice.erase(total_dice.begin() + temp);
			}
		}
		while (board == 3 || no_select == true)
		{
			show_score(your_turn.brains, your_turn.shots);
			if (your_turn.shots >= 3)
			{
				cout << "You were shot " << your_turn.shots <<" times. You're dead!" << endl;
				end_turn = true;
				break;
			}
			cout << "Would you like to stop here? There are: " << total_dice.size() << " dice left. Y/N" << endl;
			cin >> i;
			if (i == "y" || i == "n")
			{
				if (i == "y")
				{
					green_reroll = 0;
					yellow_reroll = 0;
					red_reroll = 0;
					count = total_dice.size();
					end_turn = true;
					board = 0;
					no_select = false;
				}
				if (i == "n")//after initiating this logic statement, board and the variables to count brains and shots are not being increased
				{
					end_turn = false;
					no_select = false;
					board = green_reroll + yellow_reroll + red_reroll;
					temp = board;
					//for (int k = 0; k < board; k++)
					while (temp >0 && green_reroll > 0 || temp>0 && yellow_reroll > 0 || temp>0 && red_reroll > 0)
						{
							if (green_reroll > 0)
							{
								cout << "Re-rolling: Green die" << endl;
								green_reroll--;
								temp--;
								your_turn.green(roll());//now getting the issue where calling the roll function here doesn't allow the brains or the shots variable to increase in the main function
								if (your_turn.re_roll == true)
								{
									green_reroll++;
									your_turn.re_roll = false;
								}
							}
							else if (yellow_reroll > 0)
							{
								cout << "Re-rolling: Yellow die" << endl;
								yellow_reroll--;
								temp--;
								your_turn.yellow(roll());
								if (your_turn.re_roll == true)
								{
									yellow_reroll++;
									your_turn.re_roll = false;
								}
							}
							else if (red_reroll > 0)
							{
								cout << "Re-rolling: Red die" << endl;
								red_reroll--;
								temp--;
								your_turn.red(roll());
								if (your_turn.re_roll == true)
								{
									red_reroll++;
									your_turn.re_roll = false;
								}
							}
						}
						//the reroll function had to be scrapped because the class variables brains and shots were not being properly incremented. Void functions don't return values to another function.
						if (board != 3)
						{
							cout << "The other dice resulted in: \n";
						}
				}
			}
			else
			{
				no_select = true;
			}
		}
		++board;//it would be better to make the reroll below a seperate function to call.
		if (total_dice.size() < 3)
		{
			break;
		}
	}
	count = total_dice.size() - 1;
}

int main()
{
	string i;
	cout << "Welcome to Zombie Dice! Press any key to start." << endl;
	cin >> i;
	vector <int> fill{ 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3 };
	srand(time(NULL));
	perform(fill);
	//count = total_dice.size() - 1; // this fixed the error "vector subscript out of range"
	return 0;
}
