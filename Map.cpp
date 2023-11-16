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

	/*Unit(int x, int y, short lvl, short health, short strength, short magic, short skill,
		short speed, short luck, short defense, short resistance, short move)*/
	Weapon weapon;
	weapon.setSwordStats("Falchion");
	humanArmy.push_back(new Unit(0, 12, "Lissa",1,17,1,5,4,4,8,3,4,5));
	humanArmy.push_back(new Unit(2, 12, "Chrom", 1, 20,7,1,8,8,5,7,1,5, weapon));
	humanArmy.push_back(new Unit(1, 13, "Frederick", 1,28,13,2,12,10,6,14,3,7));
	humanArmy.push_back(new Unit(3, 13, "Robin", 1,19,6,5,5,8,2,6,4,5));
}

void Map::setUpEnemyPositions() {
	// https://fireemblemwiki.org/wiki/The_Verge_of_History#Enemy_data
	// mage has wind
	// myrmidon has bronze sword
	// barb has bronze axe
	// garrick has hand axe
	enemyArmy.clear();
	Weapon weapon;
	weapon.setAxeStats("Hand Axe");
	enemyArmy.push_back(new Unit(7, 0, "Garrick",3, 20,8,0,5,7,2,3,0,0, weapon));
	weapon.setAxeStats("Hand Axe");
	enemyArmy.push_back(new Unit(5, 1, "Ruffian Barbarian #1",1,16,5,0,2,4,2,1,0,5, weapon));
	weapon.setTomeStats("Fire");
	enemyArmy.push_back(new Unit(7, 1, "Ruffian Mage #1",1,14,0,4,3,4,3,0,1,5,weapon));
	enemyArmy.push_back(new Unit(9, 1, "Ruffian Barbarian #2", 1, 16, 5, 0, 2, 4, 2, 1, 0, 5));
	enemyArmy.push_back(new Unit(6, 2, "Ruffian Myrmidon #1", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5));
	enemyArmy.push_back(new Unit(8, 2, "Ruffian Myrmidon #2", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5));
	enemyArmy.push_back(new Unit(9, 5, "Ruffian Mage #2", 1, 14, 0, 4, 3, 4, 3, 0, 1, 5));
	enemyArmy.push_back(new Unit(0, 7, "Ruffian Barbarian #3", 1, 16, 5, 0, 2, 4, 2, 1, 0, 5));
	enemyArmy.push_back(new Unit(6, 8, "Ruffian Barbarian #4", 1, 16, 5, 0, 2, 4, 2, 1, 0, 5));
	enemyArmy.push_back(new Unit(3, 9, "Ruffian Myrmidon #3", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5));
	enemyArmy.push_back(new Unit(8, 11, "Ruffian Myrmidon #4", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5));
}

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

bool Map::isAValidMove(int x, int y, vector<Vector2i> validMoves) {
	for (int i = 0; i < validMoves.size(); i++) {
		if (y == validMoves[i].x && x == validMoves[i].y) {
			return true;
		}
	}
	return false;
}

bool Map::isAValidAttack(int x, int y, vector<Vector2i> validAttacks) {
	for (int i = 0; i < validAttacks.size(); i++) {
		if (y == validAttacks[i].x && x == validAttacks[i].y) {
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

//used for attack purposes - good for one enemy need to fix for range

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

	return -1;
}

vector<int> Map::returnAllAdjacentEnemies(int changedUnit) {
	vector<int> enemies;
	for (int i = 0; i < enemyArmy.size(); i++) {
		if (humanArmy[changedUnit]->pos.y + humanArmy[changedUnit]->weapon.getRange() == 
			enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x == enemyArmy[i]->pos.x) {
			enemies.push_back(i);
		}
		if (humanArmy[changedUnit]->pos.y - humanArmy[changedUnit]->weapon.getRange() == 
			enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x == enemyArmy[i]->pos.x) {
			enemies.push_back(i);
		}

		//up and down checks
		if (humanArmy[changedUnit]->pos.y == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x 
			- humanArmy[changedUnit]->weapon.getRange() == enemyArmy[i]->pos.x) {
			enemies.push_back(i);
		}
		if (humanArmy[changedUnit]->pos.y == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x 
			+ humanArmy[changedUnit]->weapon.getRange() == enemyArmy[i]->pos.x) {
			enemies.push_back(i);
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		cout <<"enemy " <<enemies[i]<<" is adjacent" << endl;
	}

	return enemies;
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

void Map::updatePositions(int selected, Vector2i locs) {
	humanArmy[selected]->pos.x = locs.x;
	humanArmy[selected]->pos.y = locs.y;
	setUpTiles();
}

void Map::fight(int player, int enemy) {
	Game game;
//	game.fight(*humanArmy[player], *enemyArmy[enemy]);
	int attacks = 1;
	string outcome = "";
	if (humanArmy[player]->getSpd() - enemyArmy[enemy]->getSpd() >= 5) {
		attacks = 2;
	}
//	cout << "Enemy health before attack: " << enemyArmy[enemy]->getHP() << endl;
	outcome = humanArmy[player]->attack(*enemyArmy[enemy]);
	outcome += enemyArmy[enemy]->attack(*humanArmy[player]);
	if (attacks == 2) {
		cout << "2x attack" << endl;
		outcome += humanArmy[player]->attack(*enemyArmy[enemy]);
	}
//	cout << "Enemy health after attack: "<<enemyArmy[enemy]->getHP() << endl;
	cout << outcome << endl;


	//should return outcome and print in menu
}

vector<Vector2i> Map::possibleMoves(int unitID) {
	// Get the current unit's position
	int startX = humanArmy[unitID]->pos.x;
	int startY = humanArmy[unitID]->pos.y;

	vector<Vector2i> validMoves;
	vector<Vector2i> finalMoves;
	vector<vector<int>> map = turnMapToInts();

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridHeight; j++) {
			int path = possiblePath(15, 14, map, humanArmy[unitID]->pos.x, humanArmy[unitID]->pos.y, j, i);
			if (path <= humanArmy[unitID]->getMov() && path >= 0) finalMoves.push_back({i,j});
		}
	}

	/*cout << "Valid moves for " << humanArmy[unitID]->getName() << endl;
	for (int i = 0; i < finalMoves.size(); i++) {
		cout << "( " << finalMoves[i].x << "," << finalMoves[i].y << " ) is a valid move"<<endl;
	}*/
	return finalMoves;
}

vector<Vector2i> Map::possibleAttacks(int unitID) {
	// Get the current unit's position
	int startX = humanArmy[unitID]->pos.x;
	int startY = humanArmy[unitID]->pos.y;

	vector<Vector2i> validMoves;
	vector<Vector2i> finalMoves;

	if (humanArmy[unitID]->weapon.getRange() == 0) {
		return finalMoves;
	}

	vector<vector<int>> map = turnMapToInts();

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridHeight; j++) {
			int path = possiblePath(gridHeight, gridLength, map, humanArmy[unitID]->pos.x, humanArmy[unitID]->pos.y, j, i);
			if (path > humanArmy[unitID]->getMov() && path <= 
				humanArmy[unitID]->getMov() + humanArmy[unitID]->weapon.getRange()) finalMoves.push_back({i,j});
		}
	}

	/*cout << "Valid attack moves for " << humanArmy[unitID]->getName() << endl;
	for (int i = 0; i < finalMoves.size(); i++) {
		cout << "( " << finalMoves[i].x << "," << finalMoves[i].y << " ) is a valid move"<<endl;
	}*/
	return finalMoves;
}

vector<vector<string>> Map::getMapWithEnemies() {
	vector<vector<string>> map;
	
	return map;
}

vector<vector<int>> Map::turnMapToInts() {
	vector<vector<int>> map;
	bool isEnemyTile = false;
	for (int i = 0; i < gridHeight; i++) {
		vector<int> row;
		for (int j = 0; j < gridLength; j++) {
			isEnemyTile = isAEnemyTile(i, j);
			if (map1[j][i] == "g" && isEnemyTile) row.push_back(1);
			else if (map1[j][i] == "g") row.push_back(0);
			if (map1[j][i] == "w") row.push_back(1);
			if (map1[j][i] == "n") row.push_back(1);
		}
		map.push_back(row);
	}

	return map;
}

int Map::possiblePath(int n, int m, vector<vector<int>>& grid, int start_x, int start_y, int end_x, int end_y)
{
	// Check if the source or destination cell is blocked
	if (grid[start_x][start_y] == 1 || grid[end_x][end_y] == 1) {
		// Return -1 to indicate no path
		return -1;
	}

	// Create a queue to store the cells to explore
	queue<Vector2i> q;

	// Add the source cell to the queue and mark its distance as 0
	q.push({ start_x, start_y });

	// Define two arrays to represent the four directions of movement
	int dx[4] = { -1, 0, 1, 0 };
	int dy[4] = { 0, 1, 0, -1 };

	// Create a 2D vector to store the distance of each cell from the source
	vector<vector<int>> dis(n, vector<int>(m, -1));

	// Set the distance of the source cell as 0
	dis[start_x][start_y] = 0;

	// Loop until the queue is empty or the destination is reached
	while (!q.empty()) {
		Vector2i p = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			int x = p.x + dx[i];
			int y = p.y + dy[i];

			if (x >= 0 && x < n && y >= 0 && y < m && dis[x][y] == -1) {
				if (grid[x][y] == 0) {
					dis[x][y] = dis[p.x][p.y] + 1;
					q.push({ x, y });
				}
			}
		}
	}

	return dis[end_x][end_y];
}

void Map::showValidMoves(vector<Vector2i> validMoves, vector<Vector2i> validAttacks, int unitID) {
//	vector<vector<string>> newMap = map1;
	tiles.clear();
	for (int i = 0; i < gridLength; i++) {
		vector<Tile*> row;
		for (int j = 0; j < gridHeight; j++) {
			if (map1[i][j] == "g") {
				if (isAPlayerTile(j, i) && humanArmy[unitID]->pos.x != i && humanArmy[unitID]->pos.y !=j) {
					row.push_back(new Tile(getPath() + "ct1.png", j * 50, i * 50, true)); 
					continue;
				}
				else if (isAEnemyTile(j, i)) {
					row.push_back(new Tile(getPath() + "ct1.png", j * 50, i * 50, true));
					continue;
				}
				else if (isAValidMove(j, i, validMoves)) {
					row.push_back(new Tile(getPath() + "validMoveBlue.png", j * 50, i * 50, true));
					continue;
				}
				else if (isAValidAttack(j, i, validAttacks)) {
					row.push_back(new Tile(getPath() + "validMoveRed.png", j * 50, i * 50, true));
					continue;
				}
				else { 
					row.push_back(new Tile(getPath() + "ground.png", j * 50, i * 50, true)); 
					continue;
				}
			}
			if (map1[i][j] == "w") { 
				row.push_back(new Tile(getPath() + "water.png", j * 50, i * 50, true)); 
				continue;
			}
			if (map1[i][j] == "n") { 
				row.push_back(new Tile(getPath() + "wall.png", j * 50, i * 50, true)); 
				continue;
			}
		}
		tiles.push_back(row);
	}
}