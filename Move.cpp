#include "Move.h"

Move::Move()
	: attackType{AttackType::None}, effectType{ EffectType::None }, effectStat{ EffectStat::None },
	damageMultiplier{ 0 },
	moveName{ "None" } {
}

Move::Move(EffectType eT, EffectStat eS, double n, std::string s)
	: effectType{ static_cast<EffectType>(static_cast<int>(eT)) },
	effectStat{ static_cast<EffectStat>(static_cast<int>(eS)) },
	damageMultiplier{ n },
	moveName{ s },
	attackType{ AttackType::None } {
}

Move::Move(AttackType aT, double n, std::string s)
	: attackType{ static_cast<AttackType>(static_cast<int>(aT)) },
	damageMultiplier{ n },
	moveName{ s },
	effectType{ EffectType::None }, effectStat{ EffectStat::None } {
}
