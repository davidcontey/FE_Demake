#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Unit.h"
#include <vector>

using namespace sf;

class SelectEnemyMenu {
public:
	SelectEnemyMenu() {};

	void draw(RenderWindow& window, vector<Unit*> units, vector<int> selected, string path) {
		inRangeEnemies.clear();
		allEnemies.clear();
		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			//error
		}

	//	inRangeEnemies = units;

		allEnemies = units;

		vector<Vector2i> enemyPos;

		for (int i = 0; i < selected.size(); i++) {
			inRangeEnemies.push_back(units[selected[i]]);
			enemyPos.push_back(units[selected[i]]->pos);
		}
		sz = inRangeEnemies.size() + 1;

		if (inRangeEnemies.size() != 0) {

			for (int i = 0; i < inRangeEnemies.size() + 1; i++) {
				if (i < inRangeEnemies.size()) {
					menuItem[i].setSize(Vector2f(200, 40));
					menuItem[i].setFillColor(Color::White);
					menuItem[i].setPosition(300, 200 + (50 * i));
					menuItem[i].setOutlineColor(Color(0, 0, 0));
					menuItem[i].setOutlineThickness(1);

					text[i].setString(inRangeEnemies[i]->getName());
					text[i].setFont(font);
					text[i].setCharacterSize(24);
					text[i].setFillColor(Color::Black);
					text[i].setPosition(310, 205 + (50 * i));
				}
				else {
					menuItem[i].setSize(Vector2f(200, 40));
					menuItem[i].setFillColor(Color::White);
					menuItem[i].setPosition(300, 200 + (50 * i));
					menuItem[i].setOutlineColor(Color(0, 0, 0));
					menuItem[i].setOutlineThickness(1);

					text[i].setString("Return");
					text[i].setFont(font);
					text[i].setCharacterSize(24);
					text[i].setFillColor(Color::Black);
					text[i].setPosition(310, 205 + (50 * i));
				}
				window.draw(menuItem[i]);
				window.draw(text[i]);
			}
		}
	};

	vector<FloatRect>  getItemBounds() {
		vector<FloatRect> globalBounds;

		for (int i = 0; i < sz; i++) {
			globalBounds.push_back(menuItem[i].getGlobalBounds());
		}
		return globalBounds;
	}

	int getSelectedEnemy(int selected) {
		for (int i = 0; i < allEnemies.size(); i++) {
			for (int j = 0; j < inRangeEnemies.size(); j++) {
				if (inRangeEnemies[selected]->pos.x == allEnemies[i]->pos.x && 
					inRangeEnemies[selected]->pos.y == allEnemies[i]->pos.y) {
					return i;
				}
			}
		}
	}

private:
	Font font;
	RectangleShape menuItem[7];
	Text text[7];
	vector<Unit*> inRangeEnemies;
	vector<Unit*> allEnemies;
	int sz;
};