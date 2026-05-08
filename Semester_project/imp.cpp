#include"sem.h"

// Piece Class Implementation
//Constructor
Piece::Piece(char color, int x, int y) : color(color), x(x), y(y) {}

// Getter for color
char Piece::getcolor() const 
{
	return color;
}

//Getter for x-position
int Piece::getx() const 
{
	return x;
}

//Getter for y-position
int Piece::gety() const 
{
	return y;
}

// Update piece position
void Piece::setposition(int newX, int newY)
{
	x = newX;
	y = newY;
}

//virtual destructor
Piece::~Piece(){}

//=========================================================
// PAWN CLASS IMPLEMENTATION
//=========================================================

// Constructor
Pawn::Pawn(char color, int x, int y)
    : Piece(color, x, y)
{
}


// Returns symbol of pawn
char Pawn::getsymbol() const
{
    // Uppercase for White
    // Lowercase for Black
    if (color == 'W')
        return 'P';

    return 'p';
}


// Checks if pawn move is valid
bool Pawn::isvalidmove(int toX, int toY,
    Piece* board[8][8])
{
    // White pawn moves upward
    if (color == 'W')
    {
        // One step forward
        if (toX == x - 1 && toY == y && board[toX][toY] == nullptr)
        {
            return true;
        }

        // First move can move two steps
        if (x == 6 && toX == x - 2 && toY == y &&
            board[x - 1][y] == nullptr &&
            board[toX][toY] == nullptr)
        {
            return true;
        }

        // Diagonal capture
        if (toX == x - 1 &&
            (toY == y - 1 || toY == y + 1) &&
            board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() != color)
        {
            return true;
        }
    }

    // Black pawn moves downward
    else
    {
        // One step forward
        if (toX == x + 1 &&
            toY == y &&
            board[toX][toY] == nullptr)
        {
            return true;
        }

        // First move can move two steps
        if (x == 1 &&
            toX == x + 2 &&
            toY == y &&
            board[x + 1][y] == nullptr &&
            board[toX][toY] == nullptr)
        {
            return true;
        }

        // Diagonal capture
        if (toX == x + 1 &&
            (toY == y - 1 || toY == y + 1) &&
            board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() != color)
        {
            return true;
        }
    }

    // Invalid move
    return false;
}
