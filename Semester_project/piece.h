#pragma once
#include <iostream>
using namespace std;

class Piece
{
protected:
    char color;   // 'W' for White , 'B' for Black
    int x, y;     // Current position on board

public:

    // Constructor
    Piece(char color, int x, int y);

    // Getter functions
    char getcolor() const;
    int getx() const;
    int gety() const;

    // Updates piece position after every move
    void setposition(int newX, int newY);

    // Pure virtual function
    // Every derived piece must define its own movement rules
    virtual bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) = 0;

    // Returns symbol of piece
    // Example: P,R,N,B,Q,K
    virtual char getsymbol() const = 0;

    // Virtual destructor
    virtual ~Piece();
};

