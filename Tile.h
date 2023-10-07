#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

class Tile {
private:
	float left, right, up, down;
    Vector2f center;
	string Color; // change this to a texture probably
public:
    Tile() {

    }
	Tile(float newLeft, float newRight, float newUp, float newDown) {
		left = newLeft;
		right = newRight;
		up = newUp;
		down = newDown;
	}

    float getLeft() const {
        return left;
    }

    // Setter for left
    void setLeft(float newLeft) {
        left = newLeft;
    }

    // Getter for right
    float getRight() const {
        return right;
    }

    // Setter for right
    void setRight(float newRight) {
        right = newRight;
    }

    // Getter for up
    float getUp() const {
        return up;
    }

    // Setter for up
    void setUp(float newUp) {
        up = newUp;
    }

    // Getter for down
    float getDown() const {
        return down;
    }

    // Setter for down
    void setDown(float newDown) {
        down = newDown;
    }

    // Getter for center
    Vector2f getCenter() const {
        return center;
    }

    // Setter for center
    void setCenter(Vector2f newCenter) {
        center = newCenter;
    }
};