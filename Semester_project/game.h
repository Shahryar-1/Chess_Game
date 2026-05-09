#pragma once
#include "ChessBoard.h"
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

class Game
{
private:
    ChessBoard board;
    char currentTurn;

public:
    Game();
    void start();
    void switchTurn();
    bool isGameOver();
    void showMenu();
    void saveGame();
    bool loadGame();
};
