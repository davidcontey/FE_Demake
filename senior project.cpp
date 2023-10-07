#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include "Map.h"
#include "Tile.h"

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
    RenderWindow window(VideoMode(750,700), "Fire Emblem");
    
    RectangleShape shape(Vector2f(10,10));
    shape.setFillColor(Color::Green);

    sf::Texture test;
    if (!test.loadFromFile(getPath() + "/ct1.png")) {
    }

    sf::Sprite chrom;
    chrom.setTexture(test);
    chrom.setScale(3.f, 3.f);
    chrom.setPosition(Vector2f(500, 500));
    
    Map gameMap;
    gameMap.setTileLocations();
    gameMap.printLocations();

    
    sf::Sprite temp_chrom;
    temp_chrom.setTexture(test);
    temp_chrom.setScale(3.f, 3.f);
    temp_chrom.setPosition(chrom.getPosition());
    
    bool dragging = false;
    sf::Vector2f offset;
    Vector2f currentPosition = chrom.getPosition();
    Vector2f update = Vector2f(0, 0);
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
                    if (chrom.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        dragging = true;
                        offset = temp_chrom.getPosition() - sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
                    dragging = false;
                    //correct position here
                    cout << "x: " << mousePos.x << endl
                        << "y: " << mousePos.y << endl;

                //    cout << update.x << endl;

                    chrom.setPosition(gameMap.correctPositions(update));
                    temp_chrom.setPosition(chrom.getPosition());
                    currentPosition = chrom.getPosition();
                 //   cout << "\nhi" << endl;
                }
            }
        }

        if (dragging) {
            // Update the sprite's position while dragging
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            update = chrom.getPosition();
            //offset is distance
            //mousePos is you know
            
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
                mousePos.y = 0;
            }


         //   cout << mousePos.x << endl;
            
        //    if ((currentPosition.x - 100.0) <= (event.mouseButton.x) && (event.mouseButton.x) <= (currentPosition.x + 100.0)){
                //if ((currentPosition.y - 100.0) <= (event.mouseButton.y) && (event.mouseButton.y) <= (currentPosition.y + 100.0)) {
                    update = mousePos + offset;
             //       cout << "cock " << endl;
            //        cout << "mouseButton: " << event.mouseButton.x << "currentPosition.x: " << (currentPosition.x - 50) << endl;
                //}
         //   }
        //    cout << "event.mouseButton.x: " << event.mouseButton.x << " (chrom.getPosition().x-5: " << (chrom.getPosition().x - 5) << endl;
            temp_chrom.setPosition(mousePos + offset);
            
        }

        
        window.clear();
        
        if (dragging == true) {
            window.draw(temp_chrom);
        }

        //window.draw(shape);
        
        if (dragging == false) {
            window.draw(chrom);
        }
        window.display();
    }

    return 0;
}

struct Position {
    int x;
    int y;

    bool operator==(Position & position) const{
        return this->x == position.x && this->y == position.y;
    }
};