#pragma once
#include "Unit.h"
class Skill
{
private:
	unsigned id;
public:
	Skill() {
		//
	}

	void Vantage(Unit& one, Unit &two);

	void Sol(Unit& one, Unit& two);
};

