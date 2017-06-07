/**************
Lisa Chiang 
304-255-524
HW#6 11/4/2016
Black Jack Game
**************/

#include <string>
#include <iostream>
#include <cmath>
#include "time.h"
#include <cstdlib>

void draw_card(int &card_num, int &card_type) //drawing a number and suite
{
	card_num = (rand() % 13) + 1;
	card_type = (rand() % 4) + 1;
}

void aceor11(int &num, int sum); //choosing whether ace is 1 or 11

string card_number(int &num, int sum) //changing integer into string
{
	if (num == 1)
	{
		aceor11(num, sum); //referring to 1 or 11 function
		return "Ace";
	}
	else if (num == 2)
	{
		return"Two";
	}
	else if (num == 3)
	{
		return"Three";
	}
	else if (num == 4)
	{
		return"Four";
	}
	else if (num == 5)
	{
		return"Five";
	}
	else if (num == 6)
	{
		return"Six";
	}
	else if (num == 7)
	{
		return"Seven";
	}
	else if (num == 8)
	{
		return"Eight";
	}
	else if (num == 9)
	{
		return"Nine";
	}
	else if (num == 10)
	{
		num = 10;
		return"Ten";
	}
	else if (num == 11)
	{
		num = 10;
		return"Jack";
	}
	else if (num == 12)
	{
		num = 10;
		return"Queen";
	}
	else if (num == 13)
	{
		num = 10;
		return"King";
	}
}

string card_type(int type) //changing integer into card suite/type
{
	if (type == 1)
	{
		return"Spades";
	}
	else if (type == 2)
	{
		return"Hearts";
	}
	else if (type == 3)
	{
		return"Diamonds";
	}
	else if (type == 4)
	{
		return"Clubs";
	}
}

void aceor11(int &num, int sum) //deciding between letting ace be 1 or 11
{
	if (sum <= 10)
	{
		num = 11;
	}
	else
	{
		num = 1;
	}
}

int main()
{
	string another_card; //asking if they want another card ("Y" || "y")
	int num; //the number of the card
	int type; //the suite of the card
	int sum = 0; //player's current total
	int d_sum = 0; //dealer's current total
	int money = 100; //amount of available money
	int bet; //how much they bet

	 //setup of game 
	srand((int)time(0)); //srand
	num = 0; type = 0; //setting num and type
	
	while (money > 0 && money < 1000)
	{
		//betting amount 
		cout << "You have $" << money << ". Enter bet: ";
		cin >> bet;
		while (bet > money)
		{
			//asking them to enter betting amount within limits
			cout << "You only have $" << money << " to bet. Enter bet: ";
			cin >> bet;
		}
		cout << endl;

		//beginning the game of player drawing TWO CARDS
		cout << "Your cards are: " << endl;
		for (int i = 0; i < 2; i++)
		{
			draw_card(num, type);

			cout << "\t"; cout << card_number(num, sum);
			cout << " of " << card_type(type); cout << endl;
			sum += num;
		}

		//deciding what to output to player - either draw again or 21!
		if (sum == 21)
		{
			cout << "Your total is " << sum << "!" << endl << endl;
			another_card = "n";
		}
		else
		{
			cout << "Your total is " << sum << ". Do you want another card (y/n)?";
			cin >> another_card;
			cout << endl;
		}

		while (another_card == "Y" || another_card == "y")
		{
			//drawing another card 
			draw_card(num, type);
			cout << "You draw a: " << endl;
			cout << "\t" << card_number(num, sum);
			cout << " of " << card_type(type); cout << endl;
			sum += num;

			cout << "Your total is " << sum;

			//deciding what to output to player - either draw again or 21! or busted!
			if (sum > 21)
			{
				cout << ".  You busted!" << endl << endl;
				another_card = "n";
			}
			else if (sum == 21)
			{
				cout << "!" << endl << endl;
				another_card = "n";
			}
			else
			{
				cout << ". Do you want another card (y/n)?";
				cin >> another_card;
				cout << endl;
			}
		}

		//moving onto the dealer's cards - 2 draws
		cout << "The dealer's cards are: " << endl;
		for (int i = 0; i < 2; i++)
		{
			draw_card(num, type);

			cout << "\t" << card_number(num, d_sum);
			cout << " of " << card_type(type); cout << endl;
			d_sum = d_sum + num;
		}
		cout << "The dealer's total is " << d_sum << "." << endl << endl;

		//allowing dealer to draw again as long as the sum is <= 16
		if (d_sum <= 16)
		{
			cout << "The dealer draws a card." << endl;

			draw_card(num, type);

			cout << "\t" << card_number(num, d_sum);
			cout << " of " << card_type(type); cout << endl;
			d_sum += num;

			cout << "The dealer's total is " << d_sum << "." << endl;
		}

		//dispersing bets and wins
		if (sum <= 21 && d_sum <= 21)
		{
			if (sum > d_sum)
			{
				cout << "You win $" << bet << "!";
				money = bet + money;
			}
			else if (sum < d_sum)
			{
				cout << "Too bad. You lose $" << bet << ".";
				money = money - bet;
			}
			else if (sum == d_sum)
			{
				cout << "A draw! You get back your $" << bet << ".";
			}
		}
		else if (sum > 21 && d_sum > 21)
		{
			cout << "Too bad. You lose $" << bet << ".";
			money = money - bet;
		}
		else if (sum > 21 && d_sum <= 21)
		{
			cout << "Too bad. You lose $" << bet << ".";
			money = money - bet;
		}
		else if (sum <= 21 && d_sum > 21)
		{
			cout << "You win $" << bet << "!";
			money = bet + money;
		}

		sum = 0; d_sum = 0;

		cout << endl << endl;
	}

	cout << "You have $" << money << ".\tGAME OVER.";

	system("pause");
	return 0;
}