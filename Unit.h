#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Weapon.h";
#include <string>

using namespace sf;
using namespace std;

class Unit{
private:
    string name;
    short level;
    short hp;
    short maxHP;
    short str;
    short mag;
    short skl;
    short spd;
    short lck;
    short def;
    short res;
    short mov;
    bool turn;
    bool flyer;
public:
    vector<Weapon> inventory;
    Weapon equipped;
    Vector2i pos;

    Unit(int x, int y) {
        level = 0;
        hp = 0;
        maxHP = 0;
        str = 0;
        mag = 0;
        skl = 0;
        spd = 0;
        lck = 0;
        def = 0;
        res = 0;
        mov = 0;
        pos.x = x;
        pos.y = y;
        flyer = false;
        turn = true;
    }

    Unit(int x, int y, string nm, short lvl, short health, short strength, short magic, short skill,
        short speed, short luck, short defense, short resistance, short move, Weapon weap) {
        name = nm;
        level = lvl;
        hp = health;
        maxHP = health;
        str = strength;
        mag = magic;
        skl = skill;
        spd = speed;
        lck = luck;
        def = defense;
        res = resistance;
        mov = move;
        pos.x = x;
        pos.y = y;
        equipped = weap;
        setInventory(weap);
    }

    Unit(int x, int y, string nm, short lvl, short health, short strength, short magic, short skill,
        short speed, short luck, short defense, short resistance, short move) {
        name = nm;
        level = lvl;
        hp = health;
        maxHP = health;
        str = strength;
        mag = magic;
        skl = skill;
        spd = speed;
        lck = luck;
        def = defense;
        res = resistance;
        mov = move;
        pos.x = x;
        pos.y = y;
    }

	Unit() {
		//meow 
	}
    Unit(Unit &t) {
        level = t.level;
        hp = t.hp;
        maxHP = t.maxHP;
        str = t.str;
        mag = t.mag;
        skl = t.skl;
        spd = t.spd;
        lck = t.lck;
        def = t.def;
        res = t.res;
        mov = t.mov;
    }
	Unit(short lvl, short health, short strength, short magic, short skill,
	short speed, short luck, short defense, short resistance, short move) {
		level = lvl;
        hp = health;
		maxHP = health;
		str = strength;
		mag = magic;
		skl = skill;
		spd = speed;
		lck = luck;
		def = defense;
		res = resistance;
		mov = move;
	}

    short getLevel() const {
        return level;
    }

    string getName() const {
        return name;
    }

    short getHP() const {
        return hp;
    }

    short getMaxHP() const {
        return maxHP;
    }

    short getStr() const {
        return str;
    }

    short getMag() const {
        return mag;
    }

    short getSkl() const {
        return skl;
    }

    short getSpd() const {
        return spd;
    }

    short getLck() const {
        return lck;
    }

    short getDef() const {
        return def;
    }

    short getRes() const {
        return res;
    }

    short getMov() const {
        return mov;
    }

    bool isTurn() const {
        return turn;
    }

    bool isFlyer() const {
        return flyer;
    }

    // Setter functions
    void setLevel(short newLevel) {
        level = newLevel;
    }

    void setName(string newName) {
        name = newName;
    }

    void setHP(short newHp) {
        hp = newHp;
    }

    void setMAXHP(short newHp) {
        maxHP = newHp;
    }

    void setStr(short newStr) {
        str = newStr;
    }

    void setMag(short newMag) {
        mag = newMag;
    }

    void setSkl(short newSkl) {
        skl = newSkl;
    }

    void setSpd(short newSpd) {
        spd = newSpd;
    }

    void setLck(short newLck) {
        lck = newLck;
    }

    void setDef(short newDef) {
        def = newDef;
    }

    void setRes(short newRes) {
        res = newRes;
    }

    void setMov(short newMov) {
        mov = newMov;
    }

    void setTurn(bool newTurn) {
        turn = newTurn;
    }
    
    void setFlyer(bool newFlyer) {
        flyer = newFlyer;
    }

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }

    void heal(int heal) {
        hp += heal;
        if (hp > maxHP) hp = maxHP;
    }

    string allyHealCalc(Unit &ally) {
        int heal = (getMag() / 2) + 8;
        ally.heal(heal);
        return getName() + " Heal " + ally.getName() + " " + to_string(heal);
    }

    bool checkDeath() {
        if (hp <= 0) {
            cout << getName() <<" is dead." << endl;
            return true;
        }
        return false;
    }

    void setInventory(Weapon addWeapon) {
        if (inventory.size() < 6) {
            inventory.push_back(addWeapon);
        }
        else {
            cout << "Inventory it full!" << endl;
        }
    }

    void switchWeapon(int x) {
        Weapon temp;
        temp = equipped;
        equipped = inventory[x];
        inventory[x] = temp;

        cout << "Equiped Weapon: " << equipped.getName() << endl;

    };

    string attack(Unit& enemy);
    bool effective(Unit enemy);
    int computeDamage(Unit enemy);
    int computeCritRate();
    int computeCritDamage(Unit enemy);
    int computerAttackSpeed();
    int computeHitRate();

};