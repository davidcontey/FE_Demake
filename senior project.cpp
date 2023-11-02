#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include "Map.h"
#include "Unit.h"
#include "Tile.h"
#include "Game.h"
#include "Node.h"
#include <cmath>

using namespace sf;
using namespace std;



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

int main()
{
   
    RenderWindow window(VideoMode(750, 700), "Fire Emblem");

    Map gameMap = Map();

    bool dragging = false;
    Vector2f offset;
    Vector2f update = Vector2f(0, 0);
    Vector2i locs;
    Vector2i original;
    vector<Vector2i> possibleMoves;
    Game game;
    int changedUnit = 0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle mouse events
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse click is inside the sprite
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                    
                    locs.x = mousePos.x / 50;
                    locs.y = mousePos.y / 50;

                    if (gameMap.tiles[locs.y][locs.x]->sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        if (gameMap.isAPlayerTile(locs.x, locs.y)) {
                            possibleMoves.clear();
                            original = { locs.x, locs.y };
                            changedUnit = gameMap.returnUnit(locs.x, locs.y);
                            possibleMoves = gameMap.possibleMoves(changedUnit);
                            dragging = true;
                            offset = gameMap.tiles[locs.y][locs.x]->sprite.getPosition() - Vector2f(event.mouseButton.x, event.mouseButton.y);
                        }
                        else {
                            cout << "not a player unit" << endl;
                        }
                    }
                    else {
                        cout << "broke" << endl;
                    }
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                    dragging = false;
                    vector<Vector2i> possibleMoves = gameMap.possibleMoves(changedUnit);
                //    if (gameMap.isMoveValid(changedUnit, mousePos)) 
               //     else gameMap.updatePositions(changedUnit, original);

                    gameMap.updatePositions(changedUnit, mousePos);
                    //fight thing
                   
                    //pull up prompt window here probably

                }
            }
        }

        if (dragging) {
            Vector2f mousePos = Vector2f(Mouse::getPosition(window));
            gameMap.showValidMoves(possibleMoves, changedUnit);

            if (mousePos.x < 0) {
                mousePos.x = 0;
            }
            if (mousePos.x > 1000) {
                mousePos.x = 1000;
            }
            if (mousePos.y < 0) {
                mousePos.y = 0;
            }
            if (mousePos.y > 1000) {
                mousePos.y = 1000;
            }

            update = mousePos + offset;

            gameMap.tiles[locs.y][locs.x]->sprite.setPosition(update);
        }


        window.clear();

        if (dragging == true) {
            window.draw(gameMap.tiles[locs.y][locs.x]->sprite);
        }

        for (int i = 0; i < gameMap.gridLength; i++) {
            for (int j = 0; j < gameMap.gridHeight; j++) {
                window.draw(gameMap.tiles[i][j]->sprite);
            }
        }
        window.display();
    }

    return 0;
}
