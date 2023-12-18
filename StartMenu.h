#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class StartMenu
{
public:
	StartMenu() {};

	void draw(RenderWindow& window, string path) {

		if (!font.loadFromFile(path+"fire_emblem_font.ttf"))
		{
			//error
		}

		for (int i = 0; i < 4; i++) {
			menuItem[i].setSize(Vector2f(200, 70));
			menuItem[i].setFillColor(Color(173, 216, 230, 180));
			menuItem[i].setPosition(300, 200 + (i*100));
			menuItem[i].setOutlineColor(Color(0, 0, 0, 120));
			menuItem[i].setOutlineThickness(1);

			switch (i) {
			case 0:
				text[i].setString("MAP 1");
				break;
			case 1:
				text[i].setString("MAP 2");
				break;
			case 2:
				text[i].setString("MAP 3");
				break;
			case 3:
				text[i].setString("EXIT");
				break;
			}
			text[i].setFont(font);
			text[i].setCharacterSize(24);
			text[i].setFillColor(Color::Black);
			text[i].setPosition(350, 225 + (i*100));
		}

		for (int i = 0; i < 4; i++) {
			window.draw(menuItem[i]);
			window.draw(text[i]);
		}
	};

	FloatRect getItem1Bounds() { return menuItem[0].getGlobalBounds(); };
	FloatRect getItem2Bounds() { return menuItem[1].getGlobalBounds(); };
	FloatRect getItem3Bounds() { return menuItem[2].getGlobalBounds(); };
	FloatRect getItem4Bounds() { return menuItem[3].getGlobalBounds(); };

private:
	Font font;
	RectangleShape menuItem[4];
	Text text[4];

};