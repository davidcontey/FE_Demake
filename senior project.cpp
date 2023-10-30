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

vector<Vector2i> astar(vector<vector<int>>& map, Vector2i& start, Vector2i& end) {
    Node* startNode = new Node(nullptr, start);
    startNode->g = startNode->h = startNode->f = 0;
    Node* endNode = new Node(nullptr, end);
    endNode->g = endNode->h = endNode->f = 0;

    vector<Node*> openList;
    vector<Node*> closedList;

    openList.push_back(startNode);

    while (!openList.empty()) {
        Node* currentNode = openList[0];
        int currentIndex = 0;
        for (int i = 0; i < openList.size(); i++) {
            if (openList[i]->f < currentNode->f) {
                currentNode = openList[i];
                currentIndex = i;
            }
        }

        openList.erase(openList.begin() + currentIndex);
        closedList.push_back(currentNode);

        if (currentNode->position.x == 7 && currentNode->position.y == 6) {
            cout << "meow" << endl;
        }

        if (*currentNode == *endNode) {
            vector<Vector2i> path;
            Node* current = currentNode;
            while (current != nullptr) {
                path.push_back(current->position);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        vector<Vector2i> newPositions = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

        vector<Node*> children;

        for (const auto& newPosition : newPositions) {
            int newX = currentNode->position.x + newPosition.x;
            int newY = currentNode->position.y + newPosition.y;
            if (newX < 0 || newX >= map.size() || newY < 0 || newY >= map[newX].size()) {
                continue;
            }
            if (map[newX][newY] != 0) {
                continue;
            }
            Vector2i newInfo = { newX, newY };
            Node* newNode = new Node(currentNode, newInfo);
            children.push_back(newNode);
        }

        for (Node* child : children) {
            bool inClosedList = false;
            for (Node* closedChild : closedList) {
                if (*child == *closedChild) {
                    inClosedList = true;
                    break;
                }
            }

            if (inClosedList) {
                continue;
            }

            child->g = currentNode->g + 1;
            child->h = (child->position.x - endNode->position.x) * (child->position.x - endNode->position.x) +
                (child->position.y - endNode->position.y) * (child->position.y - endNode->position.y);
            child->f = child->g + child->h;

            bool inOpenList = false;
            for (Node* openNode : openList) {
                if (*child == *openNode && child->g > openNode->g) {
                    inOpenList = true;
                    break;
                }
            }

            if (!inOpenList) {
                openList.push_back(child);
            }
        }
    }
    
    return vector<Vector2i>();
}

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
    std::vector<std::vector<int>> map = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 }
    };

    Vector2i start = { 12, 0 };
    Vector2i end = { 9, 3 };

    vector<Vector2i> path = astar(map, start, end);

    for (const auto& point : path) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;






    RenderWindow window(VideoMode(750, 700), "Fire Emblem");

    Map gameMap = Map();

    bool dragging = false;
    Vector2f offset;
    Vector2f update = Vector2f(0, 0);
    Vector2i locs;
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
                            changedUnit = gameMap.returnUnit(locs.x, locs.y);
                            vector<Vector2i> validMoves = gameMap.possibleMoves(changedUnit);
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

                    gameMap.updatePositions(changedUnit, mousePos);

                    //fight thing
                    if (gameMap.isEnemyAdjacent(mousePos.x / 50, mousePos.y / 50)) {
                    //    gameMap.fight(changedUnit, gameMap.returnAdjacentUnit(mousePos.x / 50, mousePos.y / 50));
                    }
                    //pull up prompt window here probably

                }
            }
        }

        if (dragging) {
            Vector2f mousePos = Vector2f(Mouse::getPosition(window));

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
