#include "Tile.h"

Tile::Tile(unsigned x, unsigned y) {
	pos.x = x;
	pos.y = y;
}

Tile::Tile(string texName, float x, float y, bool pass) {
	if (!setTileSprite(texName)) {
		return;
	}
	pos = Vector2f(x, y);
	sprite.setPosition(pos);
	passable = pass;
}

bool Tile::setTileSprite(string path) {
	if (!texture.loadFromFile(path)) {
		return false;
	}
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 50, 50));
	return true;
}