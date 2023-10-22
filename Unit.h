#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Unit{
private:
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
public:
    
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

    // Setter functions
    void setLevel(short newLevel) {
        level = newLevel;
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

    void takeDamage(int damage) {
        hp -= damage;
        if (hp < 0) hp = 0;
    }

    void heal(int heal) {
        hp += heal;
        if (hp > maxHP) hp = maxHP;
    }

    bool checkDeath() {
        if (hp <= 0) {
            std::cout << "Unit is dead." << std::endl;
            return true;
        }
        return false;
    }
};