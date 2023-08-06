#pragma once
#include "Type.h"
#include <string>

class Move
{

public:

	AttackType attackType;
	EffectType effectType;
	EffectStat effectStat;
	double damageMultiplier;
	std::string moveName;

	Move();
	Move(AttackType aT, double n, std::string s);
	Move(EffectType eT, EffectStat eS, double n, std::string s);

};

