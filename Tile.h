#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>

#ifndef TILE_H
#define TILE_H

using namespace sf;
using namespace std;

class Tile {
public:
    bool passable;
    Vector2f pos;
    Texture texture;
    Sprite sprite;
    Tile(string, float, float, bool);
    Tile();
    bool setTileSprite(string);
};

#endif