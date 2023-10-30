#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Unit.h"
#include <vector>
#include <queue>
#include <cmath>
#include <set>

#pragma once
class Node
{
public:
	Node* parent;
	Vector2i position;
	int g, h, f;

	Node(Node* par, Vector2i& pos);
	bool operator==(const Node& other) const;
};

