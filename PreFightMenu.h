#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Unit.h"
#include <vector>

using namespace std;
using namespace sf;

class PreFightMenu
{
public:

	PreFightMenu() {
		sz = 17;
	}

	void draw(RenderWindow& window, Unit* attacker, Unit* defender, string path) {
		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			//error
		}

		Vector2u windowSize = window.getSize();

		background.setSize(Vector2f(windowSize.x, windowSize.y));
		background.setFillColor(Color(0, 0, 0, 128));

		for (int i = 0; i < 4; i++) {
			menuItem[i].setSize(Vector2f(60,40));
			menuItem[i].setFillColor(Color::Red);
			menuItem[i].setPosition(290, 200 + i*50);
			menuItem[i].setOutlineColor(Color(0, 0, 0));
			menuItem[i].setOutlineThickness(1);
		}

		for (int i = 0; i < 4; i++) {
			menuItem[i+4].setSize(Vector2f(60, 40));
			menuItem[i+4].setFillColor(Color::Blue);
			menuItem[i+4].setPosition(350, 200 + i*50);
			menuItem[i+4].setOutlineColor(Color(0, 0, 0));
			menuItem[i+4].setOutlineThickness(1);
		}

		for (int i = 0; i < 4; i++) {
			menuItem[i + 8].setSize(Vector2f(45, 40));
			menuItem[i + 8].setFillColor(Color::White);
			menuItem[i + 8].setPosition(245, 200 + i * 50);
			menuItem[i + 8].setOutlineColor(Color(0, 0, 0));
			menuItem[i + 8].setOutlineThickness(1);
		}

		//names

		for (int i = 0; i < 3; i++) {
			menuItem[i + 12].setSize(Vector2f(200, 40));
			
			switch (i) {
				case 0:
					menuItem[i + 12].setFillColor(Color::Blue);
					menuItem[i + 12].setPosition(245, 150);
					break;
				case 1:
					menuItem[i + 12].setFillColor(Color::Red);
					menuItem[i + 12].setPosition(245, 400);
					break;
				case 2:
					menuItem[i + 12].setFillColor(Color::Red);
					menuItem[i + 12].setPosition(245, 450);
					break;
			}
		//	menuItem[i + 12].setPosition(290, 150);
			menuItem[i + 12].setOutlineColor(Color(0, 0, 0));
			menuItem[i + 12].setOutlineThickness(1);
		}

		//defender stats

		for (int i = 0; i < 4; i++) {
			switch (i) {
				case 0:
					text[i].setString(to_string(defender->getHP()));
					break;
				case 1:
					text[i].setString(to_string(defender->computeDamage(*attacker)));
					break;
				case 2:
					text[i].setString(to_string(defender->computeHitRate()));
					break;
				case 3:
					text[i].setString(to_string(defender->computeCritRate()));
					break;
			}
			
			text[i].setFont(font);
			text[i].setCharacterSize(24);
			text[i].setFillColor(Color::White);
			text[i].setPosition(295, 205 + i * 50);
		}

		//attacker stats

		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				text[i + 4].setString(to_string(attacker->getHP()));
				break;
			case 1:
				text[i + 4].setString(to_string(attacker->computeDamage(*defender)));
				break;
			case 2:
				text[i + 4].setString(to_string(attacker->computeHitRate()));
				break;
			case 3:
				text[i + 4].setString(to_string(attacker->computeCritRate()));
				break;
			}

			text[i + 4].setFont(font);
			text[i + 4].setCharacterSize(26);
			text[i + 4].setFillColor(Color::White);
			text[i + 4].setPosition(355, 205 + i * 50);
		}

		//mt, crt, htr, hp

		for (int i = 0; i < 4; i++) {
			switch (i) {
			case 0:
				text[i + 8].setString("HP");
				break;
			case 1:
				text[i + 8].setString("Mt");
				break;
			case 2:
				text[i + 8].setString("Hit");
				break;
			case 3:
				text[i + 8].setString("Crt");
				break;
			}

			text[i + 8].setFont(font);
			text[i + 8].setCharacterSize(26);
			text[i + 8].setFillColor(Color::Black);
			text[i + 8].setPosition(250, 205 + i * 50);
		}

		for (int i = 0; i < 3; i++) {
			text[i + 12].setFont(font);
			text[i + 12].setCharacterSize(26);
			text[i + 12].setFillColor(Color::White);

			switch (i) {
			case 0:
				text[i + 12].setString(attacker->getName());
				text[i + 12].setPosition(250, 150);
				break;
			case 1:
				text[i + 12].setString(defender->getName());
				text[i + 12].setPosition(250, 400);
				break;
			case 2:
				text[i + 12].setString(defender->equipped.getName());
				text[i + 12].setPosition(250, 450);
				break;
			}			
		}

		//buttons 

		menuItem[15].setSize(sf::Vector2f(200, 40));
		menuItem[15].setFillColor(sf::Color::White);
		menuItem[15].setPosition(245, 500);
		menuItem[15].setOutlineColor(sf::Color(0, 0, 0));
		menuItem[15].setOutlineThickness(1);

		text[15].setString("Fight");
		text[15].setFont(font);
		text[15].setCharacterSize(24);
		text[15].setFillColor(Color::Black);
		text[15].setPosition(250,500);

		menuItem[16].setSize(sf::Vector2f(200, 40));
		menuItem[16].setFillColor(sf::Color::White);
		menuItem[16].setPosition(245, 550);
		menuItem[16].setOutlineColor(sf::Color(0, 0, 0));
		menuItem[16].setOutlineThickness(1);

		text[16].setString("Return");
		text[16].setFont(font);
		text[16].setCharacterSize(24);
		text[16].setFillColor(Color::Black);
		text[16].setPosition(250, 550);

		window.draw(background);
		for (int i = 0; i < sz; i++) {
			window.draw(menuItem[i]);
			window.draw(text[i]);
		}
	}

	FloatRect getFightItemBounds() {
		return menuItem[15].getGlobalBounds();
	}

	FloatRect getReturnItemBounds() {
		return menuItem[16].getGlobalBounds();
	}

private:
	Font font;
	RectangleShape background;
	RectangleShape menuItem[17];
	Text text[17];
	int sz;
};

