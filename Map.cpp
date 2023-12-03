#include "Map.h"


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
	humanArmy.push_back(new Unit(0, 12, "Lissa",1,17,1,5,4,4,8,3,4,5));
	Weapon equipped;
	equipped.setSwordStats("Falchion");
	humanArmy.push_back(new Unit(2, 12, "Chrom", 1, 20,7,1,8,8,5,7,1,5,equipped));
	equipped.setLanceStats("Silver Lance");
	humanArmy.push_back(new Unit(1, 13, "Frederick", 1,28,13,2,12,10,6,14,3,7, equipped));
	equipped.setTomeStats("Thunder");
	humanArmy.push_back(new Unit(3, 13, "Robin", 1,19,6,5,5,8,2,6,4,5, equipped));
}

void Map::setUpEnemyPositions() {
	// https://fireemblemwiki.org/wiki/The_Verge_of_History#Enemy_data
	// mage has wind
	// myrmidon has bronze sword
	// barb has bronze axe
	// garrick has hand axe
	enemyArmy.clear();
	Weapon equipped;
	equipped.setAxeStats("Hand Axe");
	enemyArmy.push_back(new Unit(7, 0, "Garrick",3, 20,8,0,5,7,2,3,0,0, equipped));
	equipped.setAxeStats("Bronze Axe");
	enemyArmy.push_back(new Unit(5, 1, "RuffianA",1,16,5,0,2,4,2,1,0,5, equipped));
	enemyArmy.push_back(new Unit(0, 7, "RuffianA", 1, 16, 5, 0, 2, 4, 2, 1, 0, 5, equipped));
	enemyArmy.push_back(new Unit(6, 8, "RuffianA", 1, 16, 5, 0, 2, 4, 2, 1, 0, 5, equipped));
	enemyArmy.push_back(new Unit(9, 1, "RuffianA", 1, 16, 5, 0, 2, 4, 2, 1, 0, 5, equipped));
	equipped.setTomeStats("Wind");
	enemyArmy.push_back(new Unit(7, 1, "RuffianM",1,14,0,4,3,4,3,0,1,5, equipped));
	enemyArmy.push_back(new Unit(9, 5, "RuffianM", 1, 14, 0, 4, 3, 4, 3, 0, 1, 5, equipped));
	equipped.setSwordStats("Bronze Sword");
	enemyArmy.push_back(new Unit(6, 2, "RuffianS", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5, equipped));
	enemyArmy.push_back(new Unit(8, 2, "RuffianS", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5, equipped));
	enemyArmy.push_back(new Unit(3, 9, "RuffianS", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5, equipped));
	enemyArmy.push_back(new Unit(8, 11, "RuffianS", 1, 15, 4, 0, 5, 6, 4, 1, 0, 5, equipped));
}

void Map::setUpTiles() {
	tiles.clear();
	for (int i = 0; i < gridLength; i++) {
		vector<Tile*> row;
		for (int j = 0; j < gridHeight; j++) {
			if (map1[i][j] == "g") {
				if (isAPlayerTile(j, i)) {
					string unitPath = "textures/" + 
						humanArmy[returnHumanUnitFromPosition(j, i)]->getName() + "/"+
						humanArmy[returnHumanUnitFromPosition(j, i)]->getName() +
						"Sprite.png";
					row.push_back(new Tile(getPath() + unitPath, j * 50, i * 50, true));
				}
				else if (isAEnemyTile(j, i)) {
					string unitPath = "textures/" +
						enemyArmy[returnEnemyUnitFromPosition(j, i)]->getName() + "/" +
						enemyArmy[returnEnemyUnitFromPosition(j, i)]->getName() +
						"Sprite.png";
					row.push_back(new Tile(getPath() + unitPath, j * 50, i * 50, true));
				}
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

int Map::returnHumanUnitFromPosition(int x, int y) {
	for (int i = 0; i < humanArmy.size(); i++) {
		if (y == humanArmy[i]->pos.y && x == humanArmy[i]->pos.x) {
			return i;
		}
	}
	return -1;
}

int Map::returnEnemyUnitFromPosition(int x, int y) {
	for (int i = 0; i < enemyArmy.size(); i++) {
		if (y == enemyArmy[i]->pos.y && x == enemyArmy[i]->pos.x) {
			return i;
		}
	}
	return -1;
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
	//need to fix to account for multi range
	for (int i = 0; i < enemyArmy.size(); i++) {

		if (humanArmy[changedUnit]->equipped.isMultirange()) {
			for (int j = 1; j <= humanArmy[changedUnit]->equipped.getRange(); j++) {

				//THESE ARE JUST CHECKING HARD LEFT/RIGHT OR HARD UP/DOWN
				//right and left
				

				//these are up right, etc.
			//	if (j > 1) {
					//right left
					for (int y = 0; y <= humanArmy[changedUnit]->equipped.getRange()-1; y++) {
						//THESE ARE JUST CHECKING HARD LEFT/RIGHT OR HARD UP/DOWN
						//right and left
						if (humanArmy[changedUnit]->pos.y + j ==
							enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}
						if (humanArmy[changedUnit]->pos.y - j ==
							enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}

						//up and down checks
						if (humanArmy[changedUnit]->pos.y == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
							- j == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}
						if (humanArmy[changedUnit]->pos.y == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
							+ j == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}

						//up right, up left
						if (humanArmy[changedUnit]->pos.y + j == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
							+ y == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}
						if (humanArmy[changedUnit]->pos.y - j == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
							+ y == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}

						//up down
						if (humanArmy[changedUnit]->pos.y - j == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
							- y == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}

						if (humanArmy[changedUnit]->pos.y + j == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
							- y == enemyArmy[i]->pos.x) {
							enemies.push_back(i);
						}
					}	
				//}
			}
		}
		else {
			if (humanArmy[changedUnit]->pos.y + humanArmy[changedUnit]->equipped.getRange() ==
				enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x == enemyArmy[i]->pos.x) {
				enemies.push_back(i);
			}
			if (humanArmy[changedUnit]->pos.y - humanArmy[changedUnit]->equipped.getRange() ==
				enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x == enemyArmy[i]->pos.x) {
				enemies.push_back(i);
			}

			//up and down checks
			if (humanArmy[changedUnit]->pos.y == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
				- humanArmy[changedUnit]->equipped.getRange() == enemyArmy[i]->pos.x) {
				enemies.push_back(i);
			}
			if (humanArmy[changedUnit]->pos.y == enemyArmy[i]->pos.y && humanArmy[changedUnit]->pos.x
				+ humanArmy[changedUnit]->equipped.getRange() == enemyArmy[i]->pos.x) {
				enemies.push_back(i);
			}
		}
		
	}

	sort(enemies.begin(), enemies.end());
	enemies.erase(unique(enemies.begin(), enemies.end()), enemies.end());

	for (int i = 0; i < enemies.size(); i++) {
		cout <<"enemy " << enemies[i] <<" is adjacent" << endl;
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

string Map::fight(int player, int enemy) {
	Game game;
//	game.fight(*humanArmy[player], *enemyArmy[enemy]);
	int attacks = 1;
	string outcome;
	if (humanArmy[player]->isTurn()) {
		if (humanArmy[player]->getSpd() - enemyArmy[enemy]->getSpd() >= 5) {
			attacks = 2;
		}
		
		outcome = humanArmy[player]->attack(*enemyArmy[enemy]);

		if (humanArmy[player]->checkDeath()) {
			humanArmy.erase(humanArmy.begin() + player);
			return "\n" + outcome;
		}

		if (enemyArmy[enemy]->checkDeath()) {
			enemyArmy.erase(enemyArmy.begin() + enemy);
			return "\n" + outcome;
		}

		outcome += "\n";
		
		outcome += enemyArmy[enemy]->attack(*humanArmy[player]);

		if (humanArmy[player]->checkDeath()) {
			humanArmy.erase(humanArmy.begin() + player);
			return "\n" + outcome;
		}

		if (enemyArmy[enemy]->checkDeath()) {
			enemyArmy.erase(enemyArmy.begin() + enemy);
			return "\n" + outcome;
		}

		//brave weapons would 4x attack but I probably wont add those
		if (attacks == 2) {
			if (humanArmy[player]->checkDeath()) {
				humanArmy.erase(humanArmy.begin() + player);
				return "\n" + outcome;
			}

			if (enemyArmy[enemy]->checkDeath()) {
				enemyArmy.erase(enemyArmy.begin() + enemy);
				return "\n" + outcome;
			}

			cout << "2x attack" << endl;
			outcome += "\n" + humanArmy[player]->attack(*enemyArmy[enemy]);
		}
	}
	else {
		if (enemyArmy[enemy]->getSpd() - humanArmy[player]->getSpd() >= 5) {
			attacks = 2;
		}
		outcome = enemyArmy[enemy]->attack(*humanArmy[player]) + "\n";
		outcome += humanArmy[player]->attack(*enemyArmy[enemy]) + "\n";
		if (attacks == 2) {
			cout << "2x attack" << endl;
			outcome += enemyArmy[enemy]->attack(*humanArmy[player]);
		}
	}
	

	
//	cout << "Enemy health after attack: "<<enemyArmy[enemy]->getHP() << endl;
	return outcome;
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

	if (humanArmy[unitID]->equipped.getRange() == 0) {
		return finalMoves;
	}

	vector<vector<int>> map = turnMapToInts();

	for (int i = 0; i < gridLength; i++) {
		for (int j = 0; j < gridHeight; j++) {
			int path = possiblePath(gridHeight, gridLength, map, humanArmy[unitID]->pos.x, humanArmy[unitID]->pos.y, j, i);
			if (path > humanArmy[unitID]->getMov() && path <= 
				humanArmy[unitID]->getMov() + humanArmy[unitID]->equipped.getRange()) finalMoves.push_back({i,j});
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

vector<vector<int>> Map::turnMapToHumanInts() {
	vector<vector<int>> map;
	bool isHumanTile = false;
	for (int i = 0; i < gridHeight; i++) {
		vector<int> row;
		for (int j = 0; j < gridLength; j++) {
			isHumanTile = isAPlayerTile(i, j);
		//	if (map1[j][i] == "g" && isHumanTile) row.push_back(1);
			if (map1[j][i] == "g") row.push_back(0);
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
					string unitPath = "textures/" +
						humanArmy[returnHumanUnitFromPosition(j, i)]->getName() + "/" +
						humanArmy[returnHumanUnitFromPosition(j, i)]->getName() +
						"Sprite.png";
					row.push_back(new Tile(getPath() + unitPath, j * 50, i * 50, true)); 
					continue;
				}
				else if (isAEnemyTile(j, i)) {
					string unitPath = "textures/" +
						enemyArmy[returnEnemyUnitFromPosition(j, i)]->getName() + "/" +
						enemyArmy[returnEnemyUnitFromPosition(j, i)]->getName() +
						"Sprite.png";
					row.push_back(new Tile(getPath() + unitPath, j * 50, i * 50, true));
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

int Map::bestAttack(int enemy) {
	int armyLoc = -1;
	Map gameMap;
	vector<vector<int>> map;
	map = turnMapToHumanInts();
	vector<Unit*> possibleAttacks;
	int minScore = INT_MAX;
	int score = 0;

	for (int i = 0; i < humanArmy.size(); i++) {
		//ignore units it cant hit
		int path = gameMap.possiblePath(gridHeight, gridLength, map, enemyArmy[enemy]->pos.x,
			enemyArmy[enemy]->pos.y, humanArmy[i]->pos.x, humanArmy[i]->pos.y);
		cout << path << endl;
		if (path > enemyArmy[enemy]->getMov() + enemyArmy[enemy]->equipped.getRange() || path < 0) {
			continue;
		}

		score = 0;
		if (enemyArmy[enemy]->effective(*humanArmy[i])) {
			score += 10;
		}

		if (humanArmy[i]->equipped.isAStave() == true) {
			score += 5;
		}

		if (score < minScore) {
			minScore = score;
			armyLoc = i;
		}
	}

	/*if (armyLoc != -1) {
		cout << "best person to attack for this mans is " << humanArmy[armyLoc]->getName() << endl;
	}
	else {
		cout << "nothing for " << enemyArmy[enemy]->getName() << " to attack" << endl;
	}*/

	return armyLoc;
}


void Map::enemyTurns(bool turn) {
	for (int i = 0; i < enemyArmy.size(); i++) {
		enemyArmy[i]->setTurn(turn);
	}
}
void Map::humanTurns(bool turn) {
	for (int i = 0; i < humanArmy.size(); i++) {
		humanArmy[i]->setTurn(turn);
	}
}

bool Map::anyHumanTurns() {
	for (int i = 0; i < humanArmy.size(); i++) {
		if (humanArmy[i]->isTurn()) return true;
	}
	return false;
}

void Map::checkDeaths() {
	for (int i = 0; i < humanArmy.size(); i++) {
		if (humanArmy[i]->checkDeath()) {
			humanArmy.erase(humanArmy.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < enemyArmy.size(); i++) {
		if (enemyArmy[i]->checkDeath()) {
			enemyArmy.erase(enemyArmy.begin() + i);
			i--;
		}
	}
}