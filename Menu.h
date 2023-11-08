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

		attackBox.setSize(Vector2f(200, 40));
		attackBox.setFillColor(Color::White);
		attackBox.setPosition(300, 200);
		attackBox.setOutlineColor(Color(0, 0, 0));
		attackBox.setOutlineThickness(1);

		itemBox.setSize(Vector2f(200, 40));
		itemBox.setFillColor(Color::White);
		itemBox.setPosition(300, 250);
		itemBox.setOutlineColor(Color(0, 0, 0));
		itemBox.setOutlineThickness(1);

		returnBox.setSize(Vector2f(200, 40));
		returnBox.setFillColor(Color::White);
		returnBox.setPosition(300, 300);
		returnBox.setOutlineColor(Color(0, 0, 0));
		returnBox.setOutlineThickness(1);

		waitBox.setSize(Vector2f(200, 40));
		waitBox.setFillColor(Color::White);
		waitBox.setPosition(300, 350);
		waitBox.setOutlineColor(Color(0, 0, 0));
		waitBox.setOutlineThickness(1);

		attackText.setString("Attack");
		attackText.setFont(font);
		attackText.setCharacterSize(24);
		attackText.setFillColor(Color::Black);
		attackText.setPosition(310, 205);

		itemText.setString("Items");
		itemText.setFont(font);
		itemText.setCharacterSize(24);
		itemText.setFillColor(Color::Black);
		itemText.setPosition(310, 255);

		returnText.setString("Return");
		returnText.setFont(font);
		returnText.setCharacterSize(24);
		returnText.setFillColor(Color::Black);
		returnText.setPosition(310, 305);

		waitText.setString("Wait");
		waitText.setFont(font);
		waitText.setCharacterSize(24);
		waitText.setFillColor(Color::Black);
		waitText.setPosition(310, 355);

		window.draw(attackBox);
		window.draw(itemBox);
		window.draw(returnBox);
		window.draw(waitBox);
		window.draw(attackText);
		window.draw(itemText);
		window.draw(returnText);
		window.draw(waitText);
	};

	FloatRect getAttackBoxBounds() { return attackBox.getGlobalBounds(); };
	FloatRect getItemBoxBounds() { return itemBox.getGlobalBounds(); };
	FloatRect getReturnBoxBounds() { return returnBox.getGlobalBounds(); };
	FloatRect getWaitBoxBounds() { return waitBox.getGlobalBounds(); };

private:
	Font font;
	RectangleShape attackBox;
	RectangleShape itemBox;
	RectangleShape returnBox;
	RectangleShape waitBox;
	Text attackText;
	Text itemText;
	Text returnText;
	Text waitText;

};

