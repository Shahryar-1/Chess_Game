#include "piece.h"

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
Piece::~Piece() {}