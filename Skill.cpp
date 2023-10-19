#include "Skill.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ctime> //to use time()

using namespace std;

void Skill::Vantage(Unit& one, Unit& two) {
	//
}

void Skill::Sol(Unit& one, Unit& two) {
	//seeding the random
	srand(time(0));
	//getting a random number between 0 and 100
	int active = rand() % 101;
	
	cout << "Unit One Skill: " << one.getSkl() << endl;
	cout << "Sol roll: " << active << endl;
	if (active < one.getSkl()) {
		int damage = one.getStr() - two.getDef();
		int heal = damage / 2;
		two.takeDamage(damage);
		one.heal(heal);
		cout << "Sol Activated, Healed: " << heal << ", Hit: " << damage << endl;
		return;
	}
	cout << "Sol Not Activated" << endl;
}