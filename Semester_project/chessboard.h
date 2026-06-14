#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Piece.h"
using namespace std;

class ChessBoard
{
private:
    Piece* grid[8][8];
    int  enPassantX;
    int  enPassantY;
    bool enPassantAvailable;

    sf::Texture textures[12];   // only textures stored — sprites built on the fly

    void loadTextures();
    int  getSpriteIndex(char color, char symbol) const;

public:
    ChessBoard();
    ~ChessBoard();

    void   display();
    void   drawSFML(sf::RenderWindow& window,
        int selectedRow, int selectedCol,
        bool pieceSelected);

    Piece* getPiece(int x, int y);
    bool   isInsideBoard(int x, int y);
    bool   movePiece(int fromX, int fromY,
        int toX, int toY,
        char currentTurn);
    bool   isKingAlive(char color);
    bool   isUnderAttack(int x, int y, char enemyColor);
    bool   isInCheck(char color);
    bool   isCheckmate(char color);
};