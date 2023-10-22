#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Unit.h"
#include <vector>

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
	bool isEnemyAdjacent(int x, int y);
	
	int returnUnit(int x, int y);
	int returnAdjacentUnit(int x, int y);

	void updatePositions(int selected, Vector2f mousePos);
//	void fight(int player, int enemy);
};

#endif