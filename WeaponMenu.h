#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Unit.h"
#include <vector>

class WeaponMenu {
public:
	WeaponMenu() {};

	void draw(sf::RenderWindow& window, Unit* unit, string path) {

		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			//error
		}


		vector<Weapon> inventory = unit->inventory;
		sz = inventory.size() + 1;
		
		if (inventory.size() != 0) {

			for (int i = 0; i < inventory.size() + 1; i++) {
				if (i < inventory.size()) {
					menuItem[i].setSize(sf::Vector2f(200, 40));
					menuItem[i].setFillColor(sf::Color::White);
					menuItem[i].setPosition(300, 200 + (50 * i));
					menuItem[i].setOutlineColor(sf::Color(0, 0, 0));
					menuItem[i].setOutlineThickness(1);

					text[i].setString(inventory[i].getName());
					text[i].setFont(font);
					text[i].setCharacterSize(24);
					text[i].setFillColor(sf::Color::Black);
					text[i].setPosition(310, 205 + (50 * i));
				}
				else {
					menuItem[i].setSize(sf::Vector2f(200, 40));
					menuItem[i].setFillColor(sf::Color::White);
					menuItem[i].setPosition(300, 200 + (50 * i));
					menuItem[i].setOutlineColor(sf::Color(0, 0, 0));
					menuItem[i].setOutlineThickness(1);

					text[i].setString("Close");
					text[i].setFont(font);
					text[i].setCharacterSize(24);
					text[i].setFillColor(sf::Color::Black);
					text[i].setPosition(310, 205 + (50 * i));
				}
				window.draw(menuItem[i]);
				window.draw(text[i]);


			}



		}



	};

	vector<sf::FloatRect>  getItemBounds() {
		vector<sf::FloatRect> globalBounds;

		for (int i = 0; i < sz; i++) {
			globalBounds.push_back(menuItem[i].getGlobalBounds());
		}
		return globalBounds;
	}


private:
	sf::Font font;
	sf::RectangleShape menuItem[7];
	sf::Text text[7];
	int sz;
};