#pragma once
#include "singleton.h"

class RandomFunction : public Singleton<RandomFunction>
{
public:
	RandomFunction() { srand(GetTickCount64()); };
	~RandomFunction() {};

	inline int getInt(int num) { return rand() % num; }

	inline int getFromInTo(int fromNum, int toNum) 
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}
};