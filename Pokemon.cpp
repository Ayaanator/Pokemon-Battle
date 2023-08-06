#include "Pokemon.h"

Pokemon::Pokemon(Type t)
{

	moves = new Move[4];
	double defenceIncreaseMult{ 1.5 };
	double attackIncreaseMult{ 1.5 };
	double specialAttackMult{ 1.5 };

	if (t == Type::Fire)
	{
		health = 66; 
		attack = 20;
		defence = 0.9;
		name = "Charmander";
		type = Type::Fire;
		weakness = Type::Water;
		
		moves[0] = { AttackType::Normal, 1, "Scratch" };
		moves[1] = { AttackType::Special, specialAttackMult, "Flamethrower" };
		moves[2] = { EffectType::Self, EffectStat::Attack, attackIncreaseMult, "Dragon Dance" };
		moves[3] = { EffectType::Opponent, EffectStat::Defense, defenceIncreaseMult, "Growl" };

	}
	else if (t == Type::Water)
	{
		health = 80;
		attack = 13.3;
		defence = 0.8;
		name = "Squirtle";
		type = Type::Water;
		weakness = Type::Grass;

		moves[0] = { AttackType::Normal, 1, "Tackle" };
		moves[1] = { AttackType::Special, specialAttackMult, "Watergun" };
		moves[2] = { EffectType::Self, EffectStat::Defense, defenceIncreaseMult, "Prepare" };
		moves[3] = { EffectType::Opponent, EffectStat::Defense, defenceIncreaseMult, "Tease" };
	}
	else if(t == Type::Grass)
	{
		health = 100;
		attack = 7.5;
		defence = 0.66;
		name = "Bulbasaur";
		type = Type::Grass;
		weakness = Type::Fire;

		moves[0] = { AttackType::Normal, 1, "Headbutt" };
		moves[1] = { AttackType::Special, specialAttackMult, "Vine Slash" };
		moves[2] = { EffectType::Self, EffectStat::Defense, defenceIncreaseMult, "Growth" };
		moves[3] = { EffectType::Opponent, EffectStat::Attack, attackIncreaseMult, "Compliment" };
	}

}

Pokemon::Pokemon()
	: health{ 0 }, attack{ 0 }, defence{ 0 }, 
	name{ "None" },
	type{ Type::None }, weakness{ Type::None }, 
	moves{new Move[4]} {

	moves[0] = { AttackType::None, 0, "None" };
	moves[1] = { AttackType::None, 0, "None" };
	moves[2] = { AttackType::None, 0, "None" };
	moves[3] = { AttackType::None, 0, "None" };
}

Type Pokemon::GetType() { return type; }

Type Pokemon::GetWeakness() { return weakness; }

std::string Pokemon::GetName() { return name; }

double Pokemon::GetHealth() { return health; }

double Pokemon::GetDefence() { return defence; }

double Pokemon::GetAttack() { return attack; }

void Pokemon::SetHealth(double n) { health = n; }

void Pokemon::SetDefence(double n) { defence = n; }

void Pokemon::SetAttack(double n) { attack = n; }

void Pokemon::Attack(Pokemon &target, bool getInput, bool &gameOver)
{
	if (getInput)
	{
		if (health > 0)
		{
			PrintMoves();
			std::cout << std::endl << "Choose a move: ";

			int n;
			bool validInput{ false };
			while (!validInput)
			{
				validInput = true;
				std::cin >> n;
				ClearInput();

				if (n == 1 || n == 2 || n == 3 || n == 4)
				{
					Move move = moves[n - 1];
					std::cout << std::endl << name << " uses " << move.moveName;

					if (move.attackType == AttackType::Normal)
					{
						std::cout << "!" << std::endl;
						DoAttack(target, 1, move, true);
					}
					else if (move.attackType == AttackType::Special)
					{
						if (type == target.type)
						{
							std::cout << "!" << std::endl;
							DoAttack(target, 1, move, true);
						}
						else
						{
							if (type == target.weakness)
							{
								std::cout << ", it's very effective!" << std::endl;
								DoAttack(target, 2, move, true);
							}
							else
							{
								std::cout << ", it's not very effective..." << std::endl;
								DoAttack(target, 0.5, move, true);
							}
						}

					}
					else if (move.effectType == EffectType::Self)
					{
						if (move.effectStat == EffectStat::Attack)
						{
							std::cout << "!" << std::endl;
							DoEffect(target, 1, move, true, true, true);
						}
						else
						{
							std::cout << "!" << std::endl;
							DoEffect(target, 1, move, true, false, true);
						}
					}
					else if (move.effectType == EffectType::Opponent)
					{
						if (move.effectStat == EffectStat::Attack)
						{
							if (type == target.type)
							{
								std::cout << "!" << std::endl;
								DoEffect(target, 1, move, false, true, true);
							}
							else
							{
								if (type == target.weakness)
								{
									std::cout << ", it's very effective!" << std::endl;
									DoEffect(target, 1.5, move, false, true, true);
								}
								else
								{
									std::cout << ", it's not very effective..." << std::endl;
									DoEffect(target, 0.75, move, false, true, true);
								}
							}
						}
						else
						{
							if (type == target.type)
							{
								std::cout << "!" << std::endl;
								DoEffect(target, 1, move, false, false, true);
							}
							else
							{
								if (type == target.weakness)
								{
									std::cout << ", it's very effective!" << std::endl;
									DoEffect(target, 1.5, move, false, false, true);
								}
								else
								{
									std::cout << ", it's not very effective..." << std::endl;
									DoEffect(target, 0.75, move, false, false, true);
								}
							}
						}
					}
				}
				else
				{
					std::cout << "Error - Enter a valid choice: ";
					validInput = false;
				}

			}
		}
		else
		{
			gameOver = true;
			std::cout << name << " fainted, you lost...";
			std::cout << "\n===============================";
		}

	}
	else
	{
		if (health > 0)
		{
			int n{ RandNum(0, 100) };
			if (n < 34)
			{
				n = 0;
			}
			else if (n > 33 && n < 67)
			{
				n = 1;
			}
			else if (n > 66 && n < 84)
			{
				n = 2;
			}
			else
			{
				n = 3;
			}

			Move move = moves[n];
			std::cout << std::endl << "The foe's " << name << " uses " << move.moveName;

			if (move.attackType == AttackType::Normal)
			{
				std::cout << "!" << std::endl;
				DoAttack(target, 1, move, false);
			}
			else if (move.attackType == AttackType::Special)
			{
				if (type == target.type)
				{
					std::cout << "!" << std::endl;
					DoAttack(target, 1, move, false);
				}
				else
				{
					if (type == target.weakness)
					{
						std::cout << ", it's very effective!" << std::endl;
						DoAttack(target, 2, move, false);
					}
					else
					{
						std::cout << ", it's not very effective..." << std::endl;
						DoAttack(target, 0.5, move, false);
					}
				}
			}
			else if (move.effectType == EffectType::Self)
			{
				if (move.effectStat == EffectStat::Attack)
				{
					std::cout << "!" << std::endl;
					DoEffect(target, 1, move, true, true, false);
				}
				else
				{
					std::cout << "!" << std::endl;
					DoEffect(target, 1, move, true, false, false);
				}
			}
			else if (move.effectType == EffectType::Opponent)
			{
				if (move.effectStat == EffectStat::Attack)
				{
					if (type == target.type)
					{
						std::cout << "!" << std::endl;
						DoEffect(target, 1, move, false, true, false);
					}
					else
					{
						if (type == target.weakness)
						{
							std::cout << ", it's very effective!" << std::endl;
							DoEffect(target, 1.5, move, false, true, false);
						}
						else
						{
							std::cout << ", it's not very effective..." << std::endl;
							DoEffect(target, 0.75, move, false, true, false);
						}
					}
				}
				else
				{
					if (type == target.type)
					{
						std::cout << "!" << std::endl;
						DoEffect(target, 1, move, false, false, false);
					}
					else
					{
						if (type == target.weakness)
						{
							std::cout << ", it's very effective!" << std::endl;
							DoEffect(target, 1.5, move, false, false, false);
						}
						else
						{
							std::cout << ", it's not very effective..." << std::endl;
							DoEffect(target, 0.75, move, false, false, false);
						}
					}
				}
			}
		}
		else
		{
			gameOver = true;
			std::cout << std::endl << "The foe's " << name << " fainted, you won!" << std::endl;
			std::cout << "\n===============================";
		}

	}
}

void Pokemon::ClearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Pokemon::PrintMoves()
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << i + 1 << ". " << moves[i].moveName << std::endl;
	}
}

void Pokemon::DoAttack(Pokemon &target, double multiplier, const Move &move, bool isPlayer)
{
	double damage = move.damageMultiplier * attack * multiplier * target.defence;
	target.health -= damage;

	if (isPlayer)
	{
		std::cout << std::endl << "The foe's " << target.GetName() << " takes " <<
		damage << " damage, leaving it at " <<
		target.GetHealth() << " HP! " << std::endl;
		
		if (target.health > 0)
		{
			OtherDashes();
		}
		else
		{
			Dashes(false);
		}
	}
	else
	{
		std::cout << std::endl << target.GetName() << " takes " <<
		damage << " damage, leaving it at " <<
		target.GetHealth() << " HP! " << std::endl;

		Dashes(true);
	}

}

void Pokemon::DoEffect(Pokemon &target, double multiplier, const Move &move, bool self, bool attack, bool isPlayer)
{
	if (isPlayer)
	{
		if (self == true)
		{
			if (attack == true)
			{
				double statIncrease = move.damageMultiplier * multiplier;
				this->attack += statIncrease;

				std::cout << std::endl << name << "'s attack increases!" << std::endl;
			}
			else
			{
				double statIncrease = move.damageMultiplier * multiplier / 25;
				this->defence -= statIncrease;

				std::cout << std::endl << name << "'s defence increases!" << std::endl;
			}
		}
		else
		{
			if (attack == true)
			{
				double statDecrease = move.damageMultiplier * multiplier;
				target.attack -= statDecrease;

				std::cout << std::endl << "The foe's " << target.name << "'s attack decreases!" << std::endl;
			}
			else
			{
				double statDecrease = move.damageMultiplier * multiplier / 10;
				target.defence += statDecrease;

				std::cout << std::endl << "The foe's " << target.name << "'s defence decreases!" << std::endl;
			}
		}

		OtherDashes();
	}
	else
	{
		if (self == true)
		{
			if (attack == true)
			{
				double statIncrease = move.damageMultiplier * multiplier;
				this->attack += statIncrease;

				std::cout << std::endl << "The foe's " << name << "'s attack increases!" << std::endl;
			}
			else
			{
				double statIncrease = move.damageMultiplier * multiplier / 25;
				this->defence -= statIncrease;

				std::cout << std::endl << "The foe's " << name << "'s defence increases!" << std::endl;
			}
		}
		else
		{
			if (attack == true)
			{
				double statDecrease = move.damageMultiplier * multiplier;
				target.attack -= statDecrease;

				std::cout << std::endl << target.name << "'s attack decreases!" << std::endl;
			}
			else
			{
				double statDecrease = move.damageMultiplier * multiplier / 10;
				target.defence += statDecrease;

				std::cout << std::endl << target.name << "'s defence decreases!" << std::endl;
			}
		}

		Dashes(true);
	}
}

int Pokemon::RandNum(int min, int max)
{

	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);

	return dist(engine);

}

void Pokemon::Dashes(bool b)
{
	if (b == true)
	{
		std::cout << "\n===============================\n" << std::endl;
	}
	else
	{
		std::cout << "\n===============================" << std::endl;
	}
}

void Pokemon::OtherDashes()
{
	std::cout << "\n-------------------------------" << std::endl;
}