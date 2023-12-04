#include "Unit.h"

string Unit::attack(Unit& enemy) {
	//  [Weapon Hit] + (2*Dexterity) + (Luck / 2)
	// weapon hit + skill(1.5) + luck/2 + triangle advantage + weapon level bonus + skill bonus
	string attackStatus = "";
	int damage = computeDamage(enemy);
	if (damage > 0) {
		srand(time(0));
		//check skill activate

		int percentHit = rand() % 101;
		if (percentHit <= computeHitRate()) {
			int active = rand() % 101;
			if (active < computeCritRate()) {
				damage = computeCritDamage(enemy);
				attackStatus += " Crit";
			}
			attackStatus = " Damage " + to_string(damage) + " ";
			equipped.setUses(equipped.getUses() - 1);
			enemy.takeDamage(damage);
		}
		else {
			attackStatus += " Miss ";
		}
	}
	else {
		return attackStatus + " Damage 0 ";
	}
	return attackStatus;
}

int Unit::computeDamage(Unit enemy) {
	int defensePower = 0;
	if (equipped.getDamageType() == 'P') defensePower = enemy.getDef();
	else defensePower = enemy.getRes();

	int attackPower = 0;
	if (equipped.getDamageType() == 'P') {
		if (effective(enemy)) {
			attackPower = getStr() + 3 * equipped.getMight();
		}
		else {
			attackPower = getStr() + equipped.getMight();
		}
	}
	else {
		if (effective(enemy)) {
			attackPower = getMag() + 3 * equipped.getMight();
		}
		else {
			attackPower = getMag() + equipped.getMight();
		}
	}
	return attackPower - defensePower;
}

bool Unit::effective(Unit enemy) {
	if (equipped.getWeaponType() == "sword" && enemy.equipped.getWeaponType() == "axe")
	{
		return true;
	}
	else if (equipped.getWeaponType() == "axe" && enemy.equipped.getWeaponType() == "lance")
	{
		return true;
	}
	else if (equipped.getWeaponType() == "lance" && enemy.equipped.getWeaponType() == "sword")
	{
		return true;
	}
	else if (equipped.getWeaponType() == "wind" && enemy.isFlyer() == true)
	{
		return true;
	}

	return false;
}

int Unit::computeCritRate() {
	return equipped.getCRT() + (getLck() + getSkl()) / 2;
}

int Unit::computeCritDamage(Unit enemy) {
	if (computeDamage(enemy) * 3 <= 120) {
		return computeDamage(enemy) * 3;
	}
	return 120;
}

int Unit::computerAttackSpeed() {
	if (equipped.getDamageType() == 'M') {
		return getSpd() - equipped.getWeight();
	}
	else{
		if (equipped.getWeight() <= getSpd()) {
			return getSpd();
		}
		else {
			return getSpd() - (equipped.getWeight() - getStr());
		}
	}
}

int Unit::computeHitRate() {
//	return equipped.getHit() * .01 + getSkl() * 2 + getLck() / 2;

	double hitRate = equipped.getHit() + (2 * getSkl()) + (2 * getLck());

	if (hitRate >= 100) {
		return 100;
	}

	return hitRate;
	//  [Weapon Hit] + (2*Dexterity) + (Luck / 2)
	// weapon hit + skill(1.5) + luck/2 + triangle advantage + weapon level bonus + skill bonus
}

//return index of army unit
