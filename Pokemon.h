#include <string>
#include <iostream>
#include <random>
#include "Type.h"
#include "Move.h"
#pragma once

class Pokemon
{

private:

	Type type;
	Type weakness;

	std::string name;
	double health;
	double attack;
	double defence;

public:

	Move *moves;
	Pokemon(Type t);
	Pokemon();

	Type GetType();
	Type GetWeakness();
	std::string GetName();
	double GetHealth();
	double GetDefence();
	double GetAttack();
	int RandNum(int min, int max);

	void SetHealth(double n);
	void SetDefence(double n);
	void SetAttack(double n);
	void Attack(Pokemon &target, bool getInput, bool &gameOver);
	void ClearInput();
	void PrintMoves();
	void DoAttack(Pokemon &target, double multiplier, const Move &move, bool isPlayer);
	void DoEffect(Pokemon &target, double multiplier, const Move &move, bool self, bool attack, bool isPlayer);
	void Dashes(bool b);
	void OtherDashes();

};

