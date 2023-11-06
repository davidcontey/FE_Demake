#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;



class Menu
{
public:
	Menu() { cout << "menu created" << endl; };

	void draw(RenderWindow& window, string path) {
		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			// nothing
		}

		menuItem1.setSize(Vector2f(200, 40));
		menuItem1.setFillColor(Color::White);
		menuItem1.setPosition(300, 200);
		menuItem1.setOutlineColor(Color(0, 0, 0));
		menuItem1.setOutlineThickness(1);

		menuItem2.setSize(Vector2f(200, 40));
		menuItem2.setFillColor(Color::White);
		menuItem2.setPosition(300, 250);
		menuItem2.setOutlineColor(Color(0, 0, 0));
		menuItem2.setOutlineThickness(1);


		text1.setString("Items");
		text1.setFont(font);
		text1.setCharacterSize(24);
		text1.setFillColor(Color::Black);
		text1.setPosition(310, 205);


		text2.setString("Wait");
		text2.setFont(font);
		text2.setCharacterSize(24);
		text2.setFillColor(Color::Black);
		text2.setPosition(310, 255);

		window.draw(menuItem1);
		window.draw(menuItem2);
		window.draw(text1);
		window.draw(text2);
	};

	FloatRect getItem1Bounds() { return menuItem1.getGlobalBounds(); };
	FloatRect getItem2Bounds() { return menuItem2.getGlobalBounds(); };

private:
	Font font;
	RectangleShape menuItem1;
	RectangleShape menuItem2;
	Text text1;
	Text text2;

};

