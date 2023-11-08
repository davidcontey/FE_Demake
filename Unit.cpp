#include "Unit.h"

string Unit::attack(Unit& enemy) {
	//  [Weapon Hit] + (2*Dexterity) + (Luck / 2)
	// weapon hit + skill(1.5) + luck/2 + triangle advantage + weapon level bonus + skill bonus

	bool hit = true;
	if (hit) {
		// add weapon damage here
		// add skill proc here
		int damage = getStr() - enemy.getDef();
		if (damage <= 0) {
			damage = 0;
			return getName() + " hits for no damage!\n";
		}
		else {
			enemy.takeDamage(damage);
			return getName() + " hits for " + to_string(damage) + "!\n";
		}
	}

	return getName() + " attack misses";
}