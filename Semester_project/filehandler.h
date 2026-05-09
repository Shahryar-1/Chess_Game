#pragma once
#include "ChessBoard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

class FileHandler
{
public:
    // Saves board state and current turn to file
    static void saveGame(ChessBoard& board, char currentTurn);

    // Loads board state and current turn from file
    // Returns true if loaded successfully
    static bool loadGame(ChessBoard& board, char& currentTurn);

    // Checks if a save file exists
    static bool saveExists();

    // Deletes the save file
    static void deleteSave();

private:
    // The save file name
    static const string SAVE_FILE;
};