#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Unit.h"
using namespace std;
using namespace sf;

class FightMenu
{
public:
	FightMenu() { };

	void draw(RenderWindow& window, Unit* attacker, Unit* defender, string outcome, string path) {
		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			// nothing
		}

		if (!attackerTexture.loadFromFile(path + "textures/" + attacker->getName() +
			"/" + attacker->getName() + "Small.png")) {
			//nada
		}
		attackerTexture.setSmooth(true);
		attackerSprite.setTexture(attackerTexture);
		attackerSprite.setTextureRect(IntRect(0, 0, 150, 125));
		Vector2f windowSize;
		attackerSprite.setPosition(window.getSize().x / 6, window.getSize().y / 2);
		window.draw(attackerSprite);
	};

private:
	Font font;
	RectangleShape attackerStatus;
	RectangleShape defenderStatus;
	Texture attackerTexture;
	Sprite attackerSprite;
	Text attackerDamage;
	Text defenderDamage;
};

