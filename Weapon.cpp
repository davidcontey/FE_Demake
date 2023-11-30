#include "Weapon.h"

Weapon::Weapon(string name) {
	setStats(name);
}

void Weapon::setStats(string newName) {
	if (name == "Bronze Sword") {
		range = 1;
		uses = 50;
		might = 3;
		hit = 100;
		crt = 0;
		weight = 5;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Iron Sword") {
		range = 1;
		uses = 40;
		might = 5;
		hit = 95;
		crt = 0;
		weight = 3;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Steel Sword") {
		range = 1;
		uses = 35;
		might = 8;
		hit = 90;
		crt = 0;
		weight = 4;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Silver Sword") {
		range = 1;
		uses = 30;
		might = 11;
		hit = 85;
		crt = 0;
		weight = 3;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Falchion") {
		range = 1;
		uses = INT_MAX;
		might = 5;
		hit = 80;
		crt = 0;
		weight = 5;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Bronze Bow") {
		range = 2;
		uses = 50;
		might = 3;
		hit = 90;
		crt = 0;
		weight = 4;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Iron Bow") {
		range = 3;
		uses = 40;
		might = 6;
		hit = 85;
		crt = 0;
		weight = 1;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Steel Bow") {
		range = 4;
		uses = 35;
		might = 9;
		hit = 80;
		crt = 0;
		weight = 3;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Silver Bow") {
		range = 5; //originall 2 but fuck it
		uses = 30;
		might = 13;
		hit = 75;
		crt = 0;
		weight = 6;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Bronze Axe") {
		range = 1;
		uses = 50;
		might = 4;
		hit = 80;
		crt = 0;
		weight = 7;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Hand Axe") {
		range = 2;
		uses = 25;
		might = 3;
		hit = 70;
		crt = 0;
		weight = 4;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Silver Lance") {
		range = 1;
		uses = 30;
		might = 13;
		hit = 75;
		crt = 0;
		weight = 5;
		weaponType = 'P';
		name = newName;
	}
	else if (newName == "Fire") {
		range = 2;
		uses = 45;
		might = 2;
		hit = 90;
		crt = 0;
		weight = 0;
		weaponType = 'M';
		name = newName;
	}
	else if (newName == "Elfire") {
		range = 2;
		uses = 35;
		might = 5;
		hit = 85;
		crt = 0;
		weight = 0;
		weaponType = 'M';
		name = newName;
	}
	else if (newName == "Thunder") {
		range = 2;
		uses = 45;
		might = 3;
		hit = 80;
		crt = 5;
		weight = 0;
		weaponType = 'M';
		name = newName;
	}
	else if (newName == "Elthunder") {
		range = 2;
		uses = 35;
		might = 6;
		hit = 75;
		crt = 5;
		weight = 0;
		weaponType = 'M';
		name = newName;
	}
	else if (newName == "Wind") {
		range = 2;
		uses = 45;
		might = 1;
		hit = 100;
		crt = 0;
		weight = 0;
		weaponType = 'M';
		name = newName;
	}
	else if (newName == "Katarina's Bolt") {
		range = 2;
		uses = 20;
		might = 11;
		hit = 75;
		crt = 30;
		weight = 0;
		weaponType = 'M';
		name = newName;
	}
}