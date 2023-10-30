#include "Map.h"
#include "Game.h"

Map::Map() {
	gridLength = 14;
	gridHeight = 15;
	setUpMap1();
}

void Map::setUpMap1() {
	setUpPlayerPositions();
	setUpEnemyPositions();
	setUpTiles();
}

void Map::setUpPlayerPositions() {
	humanArmy.clear();
	humanArmy.push_back(new Unit(0, 12));
	humanArmy.push_back(new Unit(2, 12));
	humanArmy.push_back(new Unit(1, 13));
	humanArmy.push_back(new Unit(3, 13));
}

void Map::setUpEnemyPositions() {
	enemyArmy.clear();
	enemyArmy.push_back(new Unit(7, 0));
	enemyArmy.push_back(new Unit(5, 1));
	enemyArmy.push_back(new Unit(7, 1));
	enemyArmy.push_back(new Unit(9, 1));
	enemyArmy.push_back(new Unit(6, 2));
	enemyArmy.push_back(new Unit(8, 2));
	enemyArmy.push_back(new Unit(9, 5));
	enemyArmy.push_back(new Unit(0, 7));
	enemyArmy.push_back(new Unit(6, 8));
	enemyArmy.push_back(new Unit(3, 9));
	enemyArmy.push_back(new Unit(8, 11));
}

//this function will look like hell, im sure you can make it look nice somehow
void Map::setUpTiles() {
	tiles.clear();
	for (int i = 0; i < gridLength; i++) {
		vector<Tile*> row;
		for (int j = 0; j < gridHeight; j++) {
			if (map1[i][j] == "g") {
				if (isAPlayerTile(j, i)) row.push_back(new Tile(getPath() + "ct1.png", j * 50, i * 50, true));
				else if (isAEnemyTile(j, i)) row.push_back(new Tile(getPath() + "ct1.png", j * 50, i * 50, true));
				else row.push_back(new Tile(getPath() + "ground.png", j * 50, i * 50, true));
			}
			if (map1[i][j] == "w") row.push_back(new Tile(getPath() + "water.png", j * 50, i * 50, true));
			if (map1[i][j] == "n") row.push_back(new Tile(getPath() + "wall.png", j * 50, i * 50, true));
			
		}
		tiles.push_back(row);	
	}
}

bool Map::isAPlayerTile(int x, int y) {
	for (int i = 0; i < humanArmy.size(); i++) {
		if (y == humanArmy[i]->pos.y && x == humanArmy[i]->pos.x) {
			return true;
		}
	}
	return false;
}

bool Map::isAEnemyTile(int x, int y) {
	for (int i = 0; i < enemyArmy.size(); i++) {
		if (y == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			return true;
		}
	}
	return false;
}

bool Map::isEnemyAdjacent(int x, int y) {
	cout << endl<<x << endl;
	cout << y << endl;
	for (int i = 0; i < enemyArmy.size(); i++) {
		//right and left checks
		if (y+1 == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			cout << "enemy "<<i<< " is adjacent" << endl;
			return true;
		}

		if (y - 1 == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			cout << "enemy " << i << " is adjacent" << endl;
			return true;
		}

		//up and down checks
		if (y == enemyArmy[i]->pos.y && x - 1 == enemyArmy[i]->pos.x) {
			cout << "enemy " << i << " is adjacent" << endl;
			return true;
		}
		if (y == enemyArmy[i]->pos.y && x + 1 == enemyArmy[i]->pos.x) {
			cout << "enemy " << i << " is adjacent" << endl;
			return true;
		}
	}
	return false;
}

//used for attack or trade purposes
int Map::returnAdjacentUnit(int x, int y) {
	for (int i = 0; i < enemyArmy.size(); i++) {
		if (y + 1 == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			return i;
		}
		if (y - 1 == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			return i;
		}

		//up and down checks
		if (y == enemyArmy[i]->pos.y && x - 1 == enemyArmy[i]->pos.x) {
			return i;
		}
		if (y == enemyArmy[i]->pos.y && x + 1 == enemyArmy[i]->pos.x) {
			return i;
		}
	}
}

//used for movement purposes
int Map::returnUnit(int x, int y) {
	for (int i = 0; i < humanArmy.size(); i++) {
		if (y == humanArmy[i]->pos.y && x == humanArmy[i]->pos.x) {
			return i;
		}
	}

	for (int i = 0; i < enemyArmy.size(); i++) {
		if (y == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			return i;
		}
	}
}

void Map::updatePositions(int selected, Vector2f mousePos) {
	humanArmy[selected]->pos.x = mousePos.x/50;
	humanArmy[selected]->pos.y = mousePos.y/50;
	setUpTiles();
}

void Map::fight(int player, int enemy) {
	Game game;
	game.fight(*humanArmy[player], *enemyArmy[enemy]);
}

vector<Vector2i> Map::possibleMoves(int unitID) {
	// Get the current unit's position
	int startX = humanArmy[unitID]->pos.x;
	int startY = humanArmy[unitID]->pos.y;

	int endX = 1;
	int endY = 7;
	vector<Vector2i> validMoves;

	int dx[] = { 0, 0, 1, -1 };
	int dy[] = { 1, -1, 0, 0 };

	for (int i = 0; i < 4; i++) {
		int newX = startX + dx[i];
		int newY = startY + dy[i];

		if (newX >= 0 && newX < gridLength && newY >= 0 && newY < gridHeight && tiles[newX][newY]->passable) {
			int distance = abs(newX - startX) + abs(newY - startY);
			if (distance <= 6) {
				validMoves.push_back({ newX, newY });
			}
		}
	}

	//for (int i = 0; i < gridLength; i++) {
	//	for (int j = 0; j < gridHeight; j++) {
	//		int dist = abs(i - startX) + abs(j - startY);
	//		if (dist <= 6) { //change this to human thing later
	//			/*bool isPathBlocked = false;
	//			for (int x = min(i, startX); x <= max(i, startX); x++) {
	//				for (int y = min(j, startY); y <= max(j, startY); y++) {
	//					if (map1[x][y] == "w" || map1[x][y]=="n") {
	//						isPathBlocked = true;
	//						break;
	//					}
	//				}
	//				if (isPathBlocked) break;
	//			}*/

	//		//	if (!isPathBlocked) {
	//				validMoves.push_back({ j,i });
	//		//	}
	//		}
	//	}
	//}

	for (int i = 0; i < validMoves.size(); i++) {
		cout << "x: " << validMoves[i].x << ", y:" << validMoves[i].y <<", is a valid move." << endl;
	}





	//gotta pop out the invalid ones

	// we start at startX, startY
	// check in both directions
	// find if you can get to the position in the characters move
	// ? https://www.geeksforgeeks.org/depth-first-traversal-dfs-on-a-2d-array/
	// https://www.geeksforgeeks.org/calculate-the-manhattan-distance-between-two-cells-of-given-2d-array/

	// Possible moves (up, down, left, right)
	



	return validMoves;
}