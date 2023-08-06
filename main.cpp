#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include "Pokemon.h"


using namespace std;

void Dashes();
void ClearInput();
char GetInput(Pokemon &p, Pokemon &b);
int RandNum(int min, int max);

int main()
{
   
	cout << boolalpha;
	cout << setprecision(4);
  
	Pokemon player{};
	Pokemon bot{};
	int playerChoice{};
	int botChoice{};
	bool gameOver{ false };
  
	/*
	for (int i = 0; i < 10; i++)
	{
		for (int i = 0; i < 10; i++)
		{
			cout << RandNum(1, 999999999);
			cout << " ";
		}
		cout << endl << endl;
	}
	*/

	cout << endl << "Hello, this is a pokemon game!" << endl;

	Dashes();
	cout << "Pick your pokemon. 'C' for Charmander, 'S' for Squirtle, and 'B' for Bulbasaur: ";
	GetInput(player, bot);	

	while (!gameOver)
	{
		if (!gameOver)
		{
			player.Attack(bot, true, gameOver);
		}

		if (!gameOver)
		{
			bot.Attack(player, false, gameOver);
		}

		/*
		std::cout << std::endl << "Player attack: " << player.GetAttack() << std::endl;
		std::cout << std::endl << "Player defence: " << player.GetDefence() << std::endl;
		std::cout << std::endl << "Bot attack: " << bot.GetAttack() << std::endl;
		std::cout << std::endl << "Bot defence: " << bot.GetDefence() << std::endl << std::endl;
		*/
	}

	cout << endl;
	return 0;
	
}

void Dashes()
{
	cout << "\n===============================\n" << endl;
}

void ClearInput()
{
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char GetInput(Pokemon &p, Pokemon &b)
{
	char c;
	bool validInput{ false };

	while (!validInput)
	{
		validInput = true;
		cin >> c;
		c = std::toupper(c);

		if (c == 'C')
		{
			cout << endl << "You chose Charmander!" << endl;
			p = { Type::Fire };
		}
		else if (c == 'S')
		{
			cout << endl << "You chose Squirtle!" << endl;
			p = { Type::Water };
		}
		else if (c == 'B')
		{
			cout << endl << "You chose Bulbasaur!" << endl;
			p = { Type::Grass };
		}
		else
		{
			cout << endl << "Error - Invalid choice, try again: ";
			validInput = false;
		}

		ClearInput();
	}

	int botChoice = RandNum(1, 3);

	if (botChoice == 1)
	{
		b = { Type::Fire };
	}
	else if (botChoice == 2)
	{
		b = { Type::Water };
	}
	else
	{
		b = { Type::Grass };
	}
			
	cout << endl << "The bot chose " << b.GetName() << "!" << endl;

	Dashes();

	return c;
}

int RandNum(int min, int max)
{

	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(engine);

}