#pragma once
#include <iostream>
using namespace std;

class Weapon
{
public:
	Weapon() : name(""), range(0), uses(0), might(0), hit(0), crt(0), weight(0), damageType('P'), stave(false),multirange(false) {};

	Weapon(string name);

	void setSwordStats(string swordName) {
		multirange = false;

		if (swordName == "Bronze Sword") {
			range = 1;
			uses = 50;
			might = 3;
			hit = 100;
			crt = 0;
			weight = 5;
			damageType = 'P';
			weaponType = "sword";
			name = swordName;
		}
		else if (swordName == "Iron Sword") {
			range = 1;
			uses = 40;
			might = 5;
			hit = 95;
			crt = 0;
			weight = 3;
			damageType = 'P';
			weaponType = "sword";
			name = swordName;
		}
		else if (swordName == "Steel Sword") {
			range = 1;
			uses = 35;
			might = 8;
			hit = 90;
			crt = 0;
			weight = 4;
			damageType = 'P';
			weaponType = "sword";
			name = swordName;
		}
		else if (swordName == "Silver Sword") {
			range = 1;
			uses = 30;
			might = 11;
			hit = 85;
			crt = 0;
			weight = 3;
			damageType = 'P';
			weaponType = "sword";
			name = swordName;
		}
		else if (swordName == "Falchion") {
			range = 1;
			uses = INT_MAX;
			might = 5;
			hit = 80;
			crt = 0;
			weight = 5;
			damageType = 'P';
			weaponType = "sword";
			name = swordName;
		}

	};

	void setBowStats(string bowName) {
		multirange = false;
		if (bowName == "Bronze Bow") {
			range = 2;
			uses = 50;
			might = 3;
			hit = 90;
			crt = 0;
			weight = 4;
			damageType = 'P';
			weaponType = "bow";
			name = bowName;
		}
		else if (bowName == "Iron Bow") {
			range = 3;
			uses = 40;
			might = 6;
			hit = 85;
			crt = 0;
			weight = 1;
			damageType = 'P';
			weaponType = "bow";
			name = bowName;
		}
		else if (bowName == "Steel Bow") {
			range = 4;
			uses = 35;
			might = 9;
			hit = 80;
			crt = 0;
			weight = 3;
			damageType = 'P';
			weaponType = "bow";
			name = bowName;
		}
		else if (bowName == "Silver Bow") {
			range = 5; //originall 2 but fuck it
			uses = 30;
			might = 13;
			hit = 75;
			crt = 0;
			weight = 6;
			damageType = 'P';
			weaponType = "bow";
			name = bowName;
		}

	}

	void setAxeStats(string axeName) {
		multirange = false;
		if (axeName == "Hand Axe") {
			range = 2;
			uses = 25;
			might = 3;
			hit = 70;
			crt = 0;
			weight = 4;
			damageType = 'P';
			weaponType = "axe";
			name = axeName;
			multirange = true;
		}
		else if (axeName == "Bronze Axe") {
			range = 1;
			uses = 50;
			might = 5;
			hit = 85;
			crt = 0;
			weight = 7;
			damageType = 'P';
			weaponType = "axe";
			name = axeName;
		}
		

	}

	void setTomeStats(string tomeName) {
		multirange = false;
		if (tomeName == "Fire") {
			range = 2;
			uses = 45;
			might = 2;
			hit = 90;
			crt = 0;
			weight = 0;
			damageType = 'M';
			weaponType = "tome";
			name = tomeName;
			multirange = true;
		}
		else if (tomeName == "Elfire") {
			range = 2;
			uses = 35;
			might = 5;
			hit = 85;
			crt = 0;
			weight = 0;
			damageType = 'M';
			weaponType = "tome";
			name = tomeName;
			multirange = true;
		}
		else if (tomeName == "Thunder") {
			range = 2;
			uses = 45;
			might = 3;
			hit = 80;
			crt = 5;
			weight = 0;
			damageType = 'M';
			weaponType = "tome";
			name = tomeName;
			multirange = true;
		}
		else if (tomeName == "Elthunder") {
			range = 2;
			uses = 35;
			might = 6;
			hit = 75;
			crt = 5;
			weight = 0;
			damageType = 'M';
			weaponType = "tome";
			name = tomeName;
			multirange = true;
		}
		else if (tomeName == "Wind") {
			range = 2;
			uses = 45;
			might = 1;
			hit = 100;
			crt = 0;
			weight = 0;
			damageType = 'M';
			weaponType = "tome";
			name = tomeName;
			multirange = true;
		}
		else if (tomeName == "Katarina's Bolt") {
			range = 2;
			uses = 20;
			might = 11;
			hit = 75;
			crt = 30;
			weight = 0;
			damageType = 'M';
			weaponType = "tome";
			name = tomeName;
			multirange = true;
		}
	}

	void setLanceStats(string lanceName) {
		multirange = false;
		if (lanceName == "Silver Lance") {
			range = 1;
			uses = 30;
			might = 13;
			hit = 75;
			crt = 0;
			weight = 5;
			damageType = 'P';
			weaponType = "lance";
			name = lanceName;
		}
	}

	void setUses(int x) { uses = x; };
	int getUses() { return uses; };

	int getRange() const { return range; };
	int getMight() const { return might; };

	char getDamageType() const { return damageType; }
	int getCRT() const { return crt; };
	int getWeight() const { return weight; };
	int getHit() const { return hit; };
	bool isAStave() const { return stave; };
	bool isMultirange() const { return multirange; };
	string getName() { return name; };
	string getWeaponType() const { return weaponType; }
protected:
	//char rank;
	string name;
	int range;
	int uses;
	int might;
	int hit;
	int crt;
	int weight;
	char damageType;
	string weaponType;
	bool stave;
	bool multirange;
private:
	void setStats(string name);
};

