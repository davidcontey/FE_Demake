#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include "Map.h"
#include "Unit.h"
#include "Tile.h"
#include "Game.h"
#include "Node.h"
#include "Menu.h"
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
    Menu menu;

    bool dragging = false;
    bool showMenu = false;
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
            if (event.type == Event::Closed) {
                window.close();
            }

            // Handle mouse events
            if (showMenu==false) {
                if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
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
                        //   vector<Vector2i> possibleMoves = gameMap.possibleMoves(changedUnit);
                        if (gameMap.isAValidMove(mousePos.x / 50, mousePos.y / 50, possibleMoves))
                        {
                            cout << "move valid" << endl;
                            gameMap.updatePositions(changedUnit, mousePos);
                            showMenu = true;
                        }
                        else {
                            cout << "move invalid" << endl;
                            gameMap.updatePositions(changedUnit, original);
                        }
                        //     else gameMap.updatePositions(changedUnit, original);


                             //fight thing

                             //pull up prompt window here probably

                    }
                }
            }
            else if (showMenu==true) {
                if (Mouse::isButtonPressed(Mouse::Right)) {
                    Vector2i mousePosi = Mouse::getPosition(window);
                    FloatRect menuItemBounds = menu.getItem1Bounds();

                    cout << "meow" << endl;

                    if (menuItemBounds.contains(static_cast<Vector2f>(mousePosi))) {
                        // what ever this does
                        showMenu = false;
                        cout << "menu is closed" << endl;
                    }

                    menuItemBounds = menu.getItem2Bounds();
                    if (menuItemBounds.contains(static_cast<Vector2f>(mousePosi))) {
                        // what ever this does
                        showMenu = false;
                    }
                }
            }
        }
        

        


        window.clear();

        if (dragging) {
            window.draw(gameMap.tiles[locs.y][locs.x]->sprite);
        }

        for (int i = 0; i < gameMap.gridLength; i++) {
            for (int j = 0; j < gameMap.gridHeight; j++) {
                window.draw(gameMap.tiles[i][j]->sprite);
            }
        }

        if (dragging) {

            // TODO: this creates such a dumb problem that at its core is very low on the prio list 
            // please fix later

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

        if (showMenu==true) menu.draw(window, getPath());

        window.display();
    }

    return 0;
}
