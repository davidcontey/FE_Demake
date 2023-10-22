#pragma once
#include "Unit.h"
#include "Skill.h"
#include <iostream>
using namespace std;

class Game
{
private:
	Unit test[2];
public:
	Game() {
		//test
	}

	void fight(Unit one, Unit two) {
		Skill test;
		test.Sol(one, two);

		if (one.getSpd() >= two.getSpd()) {
			cout << "meow" << endl;
			cout << "Unit One Goes first\n";
			while (true) {
				int damage = one.getStr() - two.getDef();
				if (damage <= 0) damage = 0;
				cout << "Unit two has " << two.getHP() << " HP"<< endl;
				cout << "Unit one attacks for " << damage << " damage" << endl;
				two.takeDamage(damage);
				if (two.checkDeath()) {
					cout << "Unit Two is dead\n";
					break;
				}
				cout << "Unit two now has " << two.getHP() << " HP" << endl;

				damage = two.getStr() - one.getDef();
				if (damage <= 0) damage = 0;
				cout << "Unit one has " << one.getHP() << " HP" << endl;
				cout << "Unit two attacks for " << damage << " damage" << endl;
				one.takeDamage(damage);
				if (one.checkDeath()) {
					cout << "Unit One is dead\n";
					break;
				}
				cout << "Unit one now has " << one.getHP() << " HP" << endl;
			}
		}
		else {
			cout << "Unit Two Goes First\n";
		}
	}
};

