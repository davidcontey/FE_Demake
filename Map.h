#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Unit.h"
#include "Game.h"
#include "Weapon.h"
#include <vector>
#include <queue>
#include <set>
#include "WeaponMenu.h"

#ifndef MAP_H
#define MAP_H

class Map
{
private:
	vector<Vector2i> playerPositions;
	vector<Vector2i> enemyPositions;
	void setUpMap1();
	void setUpPlayerPositions();
	void setUpEnemyPositions();
	void setUpTiles();
	WeaponMenu menu;
public:
	vector<vector<Tile*>> tiles;
	vector<Unit*> humanArmy;
	vector<Unit*> enemyArmy;
	int gridLength;
	int gridHeight;

	string getPath() {
		string currentFilePath(__FILE__);

		string path = "";
		size_t found = currentFilePath.find_last_of("\\/");
		if (found != std::string::npos) {
			std::string projectPath = currentFilePath.substr(0, found);
			path = projectPath;
		}

		for (size_t i = 0; i < path.length(); ++i) {
			if (path[i] == '\\') {
				path[i] = '/';
			}
		}

		size_t lastSlash = path.find_last_of('/');

		if (lastSlash != string::npos) {
			path = path.substr(0, lastSlash + 1);
		}

		return path;
	}

	Map();



	vector<vector<string>> map1 = { 
	{ "g","g","g","g","g","g","g","g","g","g","g","g","g","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","g","g","g","g","g" },
	{ "w","w","w","w","w","w","g","g","g","w","w","w","w","w","w" },
	{ "w","w","w","w","w","w","g","g","g","w","w","w","w","w","w" },
	{ "w","w","w","w","w","w","g","g","g","w","w","w","w","w","w" },
	{ "g","g","g","g","g","g","g","g","g","g","w","w","g","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","w","w","g","g","g" },
	{ "g","g","n","n","g","g","n","n","g","g","g","g","g","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","g","g","g","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","w","w","g","g","g" },
	{ "g","g","n","n","g","g","n","n","g","g","w","w","w","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","w","w","w","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","w","w","g","g","g" },
	{ "g","g","g","g","g","g","g","g","g","g","w","w","g","g","g" }, 
	};

	bool isAPlayerTile(int x, int y);
	bool isAEnemyTile(int x, int y);
	bool isAValidMove(int x, int y, vector<Vector2i> validMoves);
	bool isAValidAttack(int x, int y, vector<Vector2i> validAttacks);
	bool isEnemyAdjacent(int x, int y);
	
	int returnUnit(int x, int y);
	int returnAdjacentUnit(int x, int y);
	int bestAttack(int enemy);
	vector<int> returnAllAdjacentEnemies(int changedUnit);

	void updatePositions(int selected, Vector2f mousePos);
	void updatePositions(int selected, Vector2i locs);
	string fight(int player, int enemy);

	vector<Vector2i> possibleMoves(int unitID);
	vector<Vector2i> possibleAttacks(int unitID);
	bool isMoveValid(int unitID, Vector2f mousePos);
	vector<vector<string>> getMapWithEnemies();
	vector<vector<int>> turnMapToInts();
	vector<vector<int>> turnMapToHumanInts();
	int possiblePath(int n, int m, vector<vector<int>>& grid, int start_x, int start_y, int end_x, int end_y);
	void showValidMoves(vector<Vector2i> validMoves, vector<Vector2i> validAttacks, int unitID);
	void switchWeapon(int unitID, int x) { humanArmy[unitID]->switchWeapon(x); };

	void drawWeaponMenu(sf::RenderWindow& window, int unitID) {
		menu.draw(window, humanArmy[unitID], getPath());
	}

	void enemyTurns(bool turn);
	void humanTurns(bool turn);

	bool anyHumanTurns();

	vector<sf::FloatRect> getGlobalBounds() { return menu.getItemBounds(); };
};

#endif