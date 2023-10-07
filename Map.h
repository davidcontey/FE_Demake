#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
class Map
{
private:
	Tile tiles[15][14];
public:
	Map() {
		//
	}

	void setTileLocations(){
		cout << 15 * 50<< endl;
		for (int i = 0; i < 15; i++) { // left to right
			for (int j = 0; j < 14; j++) { // up to down
				tiles[i][j].setLeft(i*50);
				tiles[i][j].setRight(tiles[i][j].getLeft() + 50);
				tiles[i][j].setUp(j * 50);
				tiles[i][j].setDown(tiles[i][j].getUp() + 50);
				Vector2f center;
				center.x = (tiles[i][j].getLeft() + tiles[i][j].getRight())/2;
				center.y = (tiles[i][j].getUp() + tiles[i][j].getDown()) / 2;
				tiles[i][j].setCenter(center);
			}
		}
	}

	void printLocations() {
		for (int i = 0; i < 15; i++) { // left to right
			for (int j = 0; j < 14; j++) { // up to down
				Vector2f center;
				center = tiles[i][j].getCenter();
				cout << "Tile: " << i << ", " << j << "\n Left: " << tiles[i][j].getLeft() <<
					", Right: " << tiles[i][j].getRight() <<
					"\n Up: " << tiles[i][j].getUp() <<
					", Down: " << tiles[i][j].getDown() <<
					"\n Center Point: " << center.x << ", " << center.y << endl << endl;
			}
		}
	}

	Vector2f correctPositions(Vector2f mousePos) {
		// mousePos.x
		// mousePos.y
		// look through tiles and find closest?

		cout << "update.x: " << mousePos.x << endl <<
			"update.y: " << mousePos.y << endl;

		int closestX = 0;
		int closestY = 0;

		int i=0, j=0;
		for (i = 0; i < 15; i++) {
			for (j = 0; j < 14; j++) {
				if ((mousePos.x >= tiles[i][j].getLeft() && mousePos.x <= tiles[i][j].getRight()) &&
					(mousePos.y >= tiles[i][j].getUp() && mousePos.y <= tiles[i][j].getDown())) {
				//	cout << "i: " << i <<", j: "<<j<< endl;
				//	cout << "left: " << tiles[i][j].getLeft() << ", right: " << tiles[i][j].getRight() << endl;
				//	cout << "mouse.x: " << mousePos.x << ", mouse.right: " << mousePos.y << endl;
					closestX = i;
					closestY = j;
				}
			}
		}

		Vector2f newCenter = tiles[closestX][closestY].getCenter();

		cout << "closestX: " << closestX << endl<<
			"closestY: "<<closestY<<endl<<
			"tile center : "<<newCenter.x<<", "<<newCenter.y<<endl;

		return tiles[closestX][closestY].getCenter();
	}
};

