#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <regex>
#include <string>
#include <chrono>
#include <thread>
#include "Unit.h"
#include <sstream>;
using namespace std;
using namespace sf;
using namespace this_thread;
using namespace chrono;

class FightMenu
{
public:
	FightMenu() { };

	vector<string> parseOutcome(string outcome) {
		string inputString = outcome;
		istringstream iss(inputString);
		vector<string> words;
		string word;
		while (getline(iss, word, ' ')) {
			cout << word << endl;
			words.push_back(word);
		}
		return words;
	}

	void draw(RenderWindow& window, Unit* attacker, Unit* defender, 
		string outcome, string path) {
		Vector2u windowSize = window.getSize();
	//	window.clear(Color::Black);
		/*background.setSize(Vector2f(windowSize.x, windowSize.y));
		background.setFillColor(Color(0, 0, 0, 256));*/


		vector<string> outcomes = parseOutcome(outcome);
		if (!font.loadFromFile(path + "fire_emblem_font.ttf"))
		{
			// nothing
		}
		cout << outcome << endl;
		if (!attackerTexture.loadFromFile(path + "textures/" + attacker->getName() +
			"/" + attacker->getName() + "Small.png")) {
			//nada
		}

		if (!defenderTexture.loadFromFile(path + "textures/" + defender->getName() +
			"/" + defender->getName() + "Small.png")) {
			//nada
		}

		attackerTexture.setSmooth(true);
		attackerSprite.setTexture(attackerTexture);
		attackerSprite.setTextureRect(IntRect(0, 0, 150, 125));
		attackerSprite.setPosition(window.getSize().x / 6, window.getSize().y / 2);

		defenderTexture.setSmooth(true);
		defenderSprite.setTexture(defenderTexture);
		defenderSprite.setTextureRect(IntRect(0, 0, 150, 125));
		defenderSprite.setScale(-1.0f,1.0f);
		defenderSprite.setPosition(window.getSize().x - (window.getSize().x / 6), 
			window.getSize().y / 2);


		
		attackerDamage.setFont(font);
		attackerDamage.setCharacterSize(50);
		attackerDamage.setFillColor(Color::White);
		attackerDamage.setPosition(window.getSize().x / 2, 200);

		defenderDamage.setFont(font);
		defenderDamage.setCharacterSize(50);
		defenderDamage.setFillColor(Color::White);
		defenderDamage.setPosition(window.getSize().x / 2, 200);


		Clock clock;
		bool direction = true;
		bool attackerTurn = false;
		bool defenderTurn = false;

		int place = 0;
		int move = 1;

		//likely make this a for loop
		while (true) {
			if (place >= outcomes.size()) {
				return;
			}
		//	cout << outcomes[place] << endl;
			if (outcomes[place] == attacker->getName()) {
				attackerTurn = true;
				defenderTurn = false;
				place++;
				continue;
			}
			else if (outcomes[place] == defender->getName()) {
				defenderTurn = true;
				attackerTurn = false;
				place++;
				continue;
			}
			else if (outcomes[place] == "Damage") {
				place++;
				continue;
			}
			else if (outcomes[place] == "Fight") {
				//do nothing
			}
			else {
				size_t pos;
				int value = stoi(outcomes[place], &pos);

				if (pos == outcomes[place].size()) {
					if (attackerTurn) {
						attackerDamage.setString(outcomes[place]);
					}
					else if (defenderTurn) {
						defenderDamage.setString(outcomes[place]);
					}
				}
				place++;
				continue;
			}


			if (attackerTurn) {
				if (clock.getElapsedTime().asSeconds() > .005f) {
					if (direction) move++;
					else move--;
					
					attackerSprite.setPosition(Vector2f(window.getSize().x / 6 + move, 
						window.getSize().y / 2));

					clock.restart();
				}
				if (move > 60) direction = false;
				
				if (move <= 0) {
					attackerTurn = false; 
					direction = true;
					place++;
					move = 1;
					continue;
				}
				
				window.clear();
				if (!direction) window.draw(attackerDamage);
				
				window.draw(attackerSprite);
				window.draw(defenderSprite);
				window.display();
			}
			else if (defenderTurn) {
				if (clock.getElapsedTime().asSeconds() > .005f) {
					if (direction) move++;
					else move--;

					defenderSprite.setPosition(Vector2f(window.getSize().x - (window.getSize().x / 6) - move,
						window.getSize().y / 2));

					clock.restart();
				}
				if (move > 60) direction = false;
				if (move <= 0) {
					defenderTurn = false;
					direction = true;
					place++;
					move = 1;
					continue;
				}

				window.clear();
				if (!direction) window.draw(defenderDamage);

				window.draw(attackerSprite);
				window.draw(defenderSprite);
				window.display();
			}

		//	window.draw(attackerSprite);
		//	window.display();
		}
		
		


		window.draw(defenderSprite);
		window.draw(attackerSprite);
	};

private:
	Font font;
	RectangleShape attackerStatus;
	RectangleShape background;
	RectangleShape defenderStatus;
	Texture attackerTexture;
	Texture defenderTexture;
	Sprite attackerSprite;
	Sprite defenderSprite;
	Text attackerDamage;
	Text defenderDamage;
};

