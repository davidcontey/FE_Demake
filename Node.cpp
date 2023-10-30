#include "Node.h"

Node::Node(Node* par, Vector2i& pos) {
	position = pos;
	parent = par;
	g = 0;
	h = 0;
	f = 0;
}

bool Node::operator==(const Node& other) const {
	return position == other.position;
}