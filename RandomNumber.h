#pragma once
#include <random>

class RandomNumber
{
public:
	static int RandNum(int min, int max)
	{
		std::random_device seeder;
		std::mt19937 engine(seeder());
		std::uniform_int_distribution<int> dist(min, max);

		return dist(engine);
	}
};

