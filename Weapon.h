#pragma once
#include <iostream>
using namespace std;

class Weapon
{
public:
	Weapon() : name(""), range(0), uses(0), might(0), hit(0), crt(0), weight(0), weaponType('P') {};



	void setSwordStats(string swordName) {
		if (swordName == "Bronze Sword") {
			range = 1;
			uses = 50;
			might = 3;
			hit = 100;
			crt = 0;
			weight = 5;
			weaponType = 'P';
			name = swordName;
		}
		else if (swordName == "Iron Sword") {
			range = 1;
			uses = 40;
			might = 5;
			hit = 95;
			crt = 0;
			weight = 3;
			weaponType = 'P';
			name = swordName;
		}
		else if (swordName == "Steel Sword") {
			range = 1;
			uses = 35;
			might = 8;
			hit = 90;
			crt = 0;
			weight = 4;
			weaponType = 'P';
			name = swordName;
		}
		else if (swordName == "Silver Sword") {
			range = 1;
			uses = 30;
			might = 11;
			hit = 85;
			crt = 0;
			weight = 3;
			weaponType = 'P';
			name = swordName;
		}
		else if (swordName == "Falchion") {
			range = 1;
			uses = INT_MAX;
			might = 5;
			hit = 80;
			crt = 0;
			weight = 5;
			weaponType = 'P';
			name = swordName;
		}

	};

	void setBowStats(string bowName) {

		if (bowName == "Bronze Bow") {
			range = 2;
			uses = 50;
			might = 3;
			hit = 90;
			crt = 0;
			weight = 4;
			weaponType = 'P';
			name = bowName;
		}
		else if (bowName == "Iron Bow") {
			range = 3;
			uses = 40;
			might = 6;
			hit = 85;
			crt = 0;
			weight = 1;
			weaponType = 'P';
			name = bowName;
		}
		else if (bowName == "Steel Bow") {
			range = 4;
			uses = 35;
			might = 9;
			hit = 80;
			crt = 0;
			weight = 3;
			weaponType = 'P';
			name = bowName;
		}
		else if (bowName == "Silver Bow") {
			range = 5; //originall 2 but fuck it
			uses = 30;
			might = 13;
			hit = 75;
			crt = 0;
			weight = 6;
			weaponType = 'P';
			name = bowName;
		}

	}

	void setAxeStats(string axeName) {

		if (axeName == "Hand Axe") {
			range = 2;
			uses = 25;
			might = 3;
			hit = 70;
			crt = 0;
			weight = 4;
			weaponType = 'P';
			name = axeName;
		}
		

	}

	void setTomeStats(string tomeName) {
		if (tomeName == "Fire") {
			range = 2;
			uses = 45;
			might = 2;
			hit = 90;
			crt = 0;
			weight = 0;
			weaponType = 'M';
			name = tomeName;
		}
		else if (tomeName == "Elfire") {
			range = 2;
			uses = 35;
			might = 5;
			hit = 85;
			crt = 0;
			weight = 0;
			weaponType = 'M';
			name = tomeName;
		}
		else if (tomeName == "Thunder") {
			range = 2;
			uses = 45;
			might = 3;
			hit = 80;
			crt = 5;
			weight = 0;
			weaponType = 'M';
			name = tomeName;
		}
		else if (tomeName == "Elthunder") {
			range = 2;
			uses = 35;
			might = 6;
			hit = 75;
			crt = 5;
			weight = 0;
			weaponType = 'M';
			name = tomeName;
		}
		else if (tomeName == "Katarina's Bolt") {
			range = 2;
			uses = 20;
			might = 11;
			hit = 75;
			crt = 30;
			weight = 0;
			weaponType = 'M';
			name = tomeName;
		}
	}

	void setUses(int x) { uses = x; };
	int getUses() { return uses; };

	int getRange() const { return range; };
	int getMight() const { return might; };

	char getWeaponType() const { return weaponType; }
	int getCRT() const { return crt; };
	int getWeight() const { return weight; };
	int getHit() const { return hit; };
	string getName() { return name; };
protected:
	//char rank;
	string name;
	int range;
	int uses;
	int might;
	int hit;
	int crt;
	int weight;
	char weaponType;
};

