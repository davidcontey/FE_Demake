#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class EndScreen
{
public:
	EndScreen() {};

	void draw(RenderWindow& window, string path, string outcome) {

		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			//error
		}

		Vector2u windowSize = window.getSize();

		background.setSize(Vector2f(windowSize.x, windowSize.y));
		background.setFillColor(Color(0, 0, 0, 128));

		text.setString("Game Over\n"+outcome+"\nClick anywhere to return \nto the main menu");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(Color::Black);
		text.setPosition(300, 300);
		

		window.draw(background);
		window.draw(text);
		
	};

	FloatRect getItemBounds() { return background.getGlobalBounds(); }

private:
	RectangleShape background;
	Font font;
	Text text;

};

