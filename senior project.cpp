#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <string>
#include "Map.h"
#include "Unit.h"
#include "Tile.h"
#include "Game.h"
#include "Menu.h"
#include "WeaponMenu.h"
#include "PreFightMenu.h"
#include "SelectEnemyMenu.h"
#include "FightMenu.h"
#include "StartMenu.h"
#include "EndScreen.h"
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
    
    RenderWindow mainMenu(VideoMode(750, 700), "Main Menu");

    StartMenu startMenu;
    Texture texture;
    if (!texture.loadFromFile(getPath()+ "start.png"))
        return EXIT_FAILURE;
    Sprite sprite;
    sprite.scale(.25, .25);
    sprite.setPosition(10, 10);
    sprite.setTexture(texture);

    int mapNum = 0;

    while (mainMenu.isOpen())
    {
        Event event;
        while (mainMenu.pollEvent(event)) {
            //window.clear();
            if (event.type == Event::Closed) {
                mainMenu.close();
                return 0;
            }

            // Handle mouse events

            if (event.type == Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2f mousePos = Vector2f(Mouse::getPosition(mainMenu));
                    FloatRect menuItemBounds = startMenu.getItem1Bounds();

                    if (menuItemBounds.contains(mousePos)) {
                         mapNum = 0;
                         mainMenu.close();
                    }

                    menuItemBounds = startMenu.getItem2Bounds();
                    if (menuItemBounds.contains(mousePos)) {
                        mapNum = 1;
                        mainMenu.close();
                    }

                    menuItemBounds = startMenu.getItem3Bounds();
                    if (menuItemBounds.contains(mousePos)) {
                    
                        mapNum = 2;
                        mainMenu.close();
                    }

                    menuItemBounds = startMenu.getItem4Bounds();
                    if (menuItemBounds.contains(mousePos)) {
                        mainMenu.close();
                        return 0;
                    }
                } 
            }
        }


        mainMenu.clear(Color::White);
        mainMenu.draw(sprite);
        startMenu.draw(mainMenu, getPath());
        mainMenu.display();

    }

    RenderWindow window(VideoMode(750, 700), "Fire Emblem");
    Map gameMap = Map();
    gameMap.enemyTurns(false);
    gameMap.humanTurns(true);
    Menu menu;
    WeaponMenu weaponMenu;
    PreFightMenu preFightMenu;
    SelectEnemyMenu selectEnemyMenu;
    FightMenu fightMenu;

    bool dragging = false;
    bool unitSelected = false;
    bool turn = false;
    bool showMenu = false;
    bool showWeaponMenu = false;
    bool showPreFightMenu = false;
    bool showFight = false;
    bool showEnemyMenu = false;

    Vector2f offset;
    Vector2f update = Vector2f(0, 0);
    Vector2i locs;
    Vector2i original;
    vector<Vector2i> possibleMoves;
    vector<Vector2i> possibleAttacks;
    vector<int> enemies;
    Game game;
    int changedUnit = 0;
    int enemy = -1;
    int enemyTurnVar = 0;
    string fight = "";
    Clock clock;


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
                return 0;
            }
            
            if (gameMap.humanArmy.size() == 0 || gameMap.enemyArmy.size()==0) {
                window.close();
                break;
            }

            // Handle mouse events
            if (!showMenu && !showWeaponMenu && !showPreFightMenu && !showEnemyMenu) {
                if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        // Check if the mouse click is inside the sprite
                        Vector2f mousePos = Vector2f(Mouse::getPosition(window));

                        locs.x = mousePos.x / 50;
                        locs.y = mousePos.y / 50;

                        if (gameMap.tiles[locs.y][locs.x]->sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                            if (gameMap.isAPlayerTile(locs.x, locs.y)) {
                                possibleMoves.clear();
                                possibleAttacks.clear();
                                original = { locs.x, locs.y };
                                changedUnit = gameMap.returnUnit(locs.x, locs.y);
                                if (gameMap.humanArmy[changedUnit]->isTurn()) {
                                    possibleMoves = gameMap.possibleMoves(changedUnit);
                                    possibleAttacks = gameMap.possibleAttacks(changedUnit);
                                    dragging = true;
                                    offset = gameMap.tiles[locs.y][locs.x]->sprite.getPosition() - Vector2f(event.mouseButton.x, event.mouseButton.y);
                                    unitSelected = true;
                                }
                                else {
                                    cout << "not its turn" << endl;
                                }
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
                    if (event.mouseButton.button == Mouse::Left && unitSelected == true) {
                        Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                        dragging = false;
                        //   vector<Vector2i> possibleMoves = gameMap.possibleMoves(changedUnit);
                        if (gameMap.isAValidMove(mousePos.x / 50, mousePos.y / 50, possibleMoves))
                        {
                            enemies.clear();
                            cout << "move valid" << endl;
                            gameMap.updatePositions(changedUnit, mousePos);
                            cout << mousePos.x / 50 << ", " << mousePos.y / 50 << endl;
                            enemy = gameMap.returnAdjacentUnit(mousePos.x / 50, mousePos.y / 50);
                            enemies = gameMap.returnAllAdjacentEnemies(changedUnit);
                            showMenu = true;
                        }
                        else {
                            cout << "move invalid" << endl;
                            gameMap.updatePositions(changedUnit, original);
                        }
                        //     else gameMap.updatePositions(changedUnit, original);


                             //fight thing

                             //pull up prompt window here probably
                        unitSelected = false;
                    }
                }
            }
            else if (showMenu) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                    FloatRect menuItemBounds = menu.getAttackBoxBounds();

                    if (menuItemBounds.contains(mousePos)) {

                        showMenu = false;
                        //    showPreFightMenu = true;
                        showEnemyMenu = true;
                        cout << "attack box" << endl;
                    }

                    menuItemBounds = menu.getItemBoxBounds();
                    if (menuItemBounds.contains(mousePos)) {
                        // what ever this does
                        showMenu = false;
                        showWeaponMenu = true;
                        cout << "item box" << endl;
                    }

                    menuItemBounds = menu.getReturnBoxBounds();
                    if (menuItemBounds.contains(mousePos)) {
                        // what ever this does
                        showMenu = false;
                        cout << "return box" << endl;
                        gameMap.updatePositions(changedUnit, original);
                    }

                    menuItemBounds = menu.getWaitBoxBounds();
                    if (menuItemBounds.contains(mousePos)) {
                        // what ever this does
                        showMenu = false;
                        gameMap.humanArmy[changedUnit]->setTurn(false);
                        cout << "wait box" << endl;
                        if (!gameMap.anyHumanTurns()) {
                            gameMap.enemyTurns(true);
                            enemyTurnVar = 0;
                            gameMap.humanTurns(false);
                        }
                    }
                }
            }
            else if (showWeaponMenu) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    vector<FloatRect> gb = gameMap.getGlobalBounds();
                    for (int i = 0; i < gb.size(); i++) {
                        if (gb[i].contains(static_cast<Vector2f>(mousePosition))) {
                            if (gb.size() - 1 != i) {
                                gameMap.switchWeapon(changedUnit, i);
                                cout << "Weapon Switched" << endl;
                            }
                            showWeaponMenu = false;
                            showMenu = true;
                            break;
                        }
                    }
                }
            }
            else if (showEnemyMenu) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                    vector<FloatRect> enemyBoxes = selectEnemyMenu.getItemBounds();
                    for (int i = 0; i < enemyBoxes.size(); i++) {
                        if (enemyBoxes[i].contains(mousePos)) {
                            if (enemyBoxes.size() - 1 != i) {
                                enemy = selectEnemyMenu.getSelectedEnemy(i);
                                cout << "Enemy " << enemy << " Selected" << endl;
                                showPreFightMenu = true;
                            }
                            showEnemyMenu = false;
                            
                            break;
                        }
                    }
                }
            }
            else if (showPreFightMenu) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                    FloatRect menuItemBounds = preFightMenu.getFightItemBounds();

                    //this is fight

                    if (menuItemBounds.contains(mousePos)) {
                        fight = gameMap.fight(changedUnit, enemy);
                        showPreFightMenu = false;
                        gameMap.humanArmy[changedUnit]->setTurn(false);
                        showFight = true;

                        

                        //    cout << "fight time" << endl;
                    }

                    menuItemBounds = preFightMenu.getReturnItemBounds();
                    if (menuItemBounds.contains(mousePos)) {
                        //    showFight = true;
                        showEnemyMenu = true;
                        showPreFightMenu = false;
                        cout << "returning" << endl;
                    }
                    //this is true
                }
            }

        }

        
        if (gameMap.enemyArmy[enemyTurnVar]->isTurn() && gameMap.enemyArmy.size()!=0) {
            int bestAttack = gameMap.bestAttack(enemyTurnVar);
            cout << bestAttack << endl;
            if (bestAttack != -1) {
                cout << "about to move " << enemyTurnVar <<endl;

                cout << "about to be attacked "<< bestAttack << endl;
                gameMap.moveEnemyUnit(enemyTurnVar, bestAttack);
                fight = gameMap.fight(bestAttack, enemyTurnVar);
                
                fightMenu.draw(window, gameMap.enemyArmy[enemyTurnVar],
                    gameMap.humanArmy[bestAttack], fight, getPath());

         
                
                if (gameMap.enemyArmy[enemyTurnVar]->checkDeath()) {
                    enemyTurnVar--;
                }

                gameMap.drawTiles(window);
            }
            if (enemyTurnVar != -1) {
                gameMap.enemyArmy[enemyTurnVar]->setTurn(false);
            }
            enemyTurnVar++;
        }
    
        
        if (enemyTurnVar >= gameMap.enemyArmy.size()-1 && gameMap.enemyArmy.size()!=0) {
            gameMap.enemyTurns(false);
            gameMap.humanTurns(true);
            enemyTurnVar = 0;
        }
    

        window.clear();

        


        for (int i = 0; i < gameMap.gridLength; i++) {
            for (int j = 0; j < gameMap.gridHeight; j++) {
                window.draw(gameMap.tiles[i][j]->sprite);
            }
        }

        if (dragging) {
            window.draw(gameMap.tiles[locs.y][locs.x]->sprite);

            Vector2f mousePos = Vector2f(Mouse::getPosition(window));
            gameMap.showValidMoves(possibleMoves, possibleAttacks, changedUnit);

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

        if (showMenu && !showWeaponMenu) menu.draw(window, getPath());
        if (showWeaponMenu) gameMap.drawWeaponMenu(window, changedUnit);
        if (showPreFightMenu) preFightMenu.draw(window, gameMap.humanArmy[changedUnit],
            gameMap.enemyArmy[enemy], getPath());
        if (showEnemyMenu) selectEnemyMenu.draw(window, gameMap.enemyArmy, enemies, getPath());
        
        if (showFight) {
            window.clear(Color::Black);
            if (gameMap.enemyArmy[enemy]->isTurn()) {
                showFight = false;
            }
            else {
                fightMenu.draw(window, gameMap.humanArmy[changedUnit],
                    gameMap.enemyArmy[enemy], fight, getPath());
                gameMap.drawTiles(window);
                if (!gameMap.anyHumanTurns()) {
                    gameMap.enemyTurns(true);
                    enemyTurnVar = 0;
                    gameMap.humanTurns(false);
                }
                showFight = false;
            }
        }
        
        gameMap.checkDeaths();
        window.display();

        // this check has to go at the bottom because otherwise the window will play out the current event
        if (gameMap.humanArmy.size() == 0 || gameMap.enemyArmy.size() == 0) {
            window.close();
            break;
        }

    }

    RenderWindow gameOver(VideoMode(750, 700), "Game Over");
    EndScreen end;

    while (gameOver.isOpen())
    {
        Event event;
        while (gameOver.pollEvent(event)) {
            //window.clear();
            if (event.type == Event::Closed) {
                gameOver.close();
                return 0;
            }

            // Handle mouse events

            if (event.type == Event::MouseButtonPressed) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window));
                    FloatRect bounds = end.getItemBounds();

                    if (bounds.contains(mousePos)) {
                        gameOver.close();
                        main();
                    }
                }
            }
        }


        gameOver.clear(Color::White);
        string outcome;
        if (gameMap.humanArmy.size() == 0) {
            outcome = "You Lose : (";
        }
        else {
            outcome = "You Win : )";
        }
        end.draw(gameOver, getPath(), outcome);
        gameOver.display();

    }

    return 0;
}
