#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "ChessBoard.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <string>
using namespace std;

// ── Exception Classes ───────────────────────────────────────────
class ChessException : public exception
{
protected:
    string message;
public:
    ChessException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidInputException : public ChessException
{
public:
    InvalidInputException(const string& input)
        : ChessException("Invalid input: '" + input +
            "'. Use a-h and 1-8. Example: e2") {
    }
};

class InvalidMoveException : public ChessException
{
public:
    InvalidMoveException()
        : ChessException("Invalid move! That move is not allowed.") {
    }
};

// ── Game Class ──────────────────────────────────────────────────
class Game
{
private:
    ChessBoard       board;
    char             currentTurn;
    sf::RenderWindow window;
    int              selectedRow;
    int              selectedCol;
    bool             pieceSelected;
    string           statusMsg;

    bool pixelToBoard(int px, int py, int& row, int& col);
    void drawStatus(sf::Font& font);

public:
    Game();
    void start();
    void switchTurn();
    bool isGameOver();
};