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

// rook implementation



Rook::Rook(char color, int x, int y)
    : Piece(color, x, y)
{
}


// Returns symbol of rook
char Rook::getsymbol() const
{
    // Uppercase for White
    // Lowercase for Black
    if (color == 'W')
        return 'R';

    return 'r';
}


// Checks if rook move is valid
bool Rook::isvalidmove(int toX, int toY,
    Piece* board[8][8])
{
    // Rook moves only horizontally or vertically
    if (x != toX && y != toY)
    {
        return false;
    }

    // Moving vertically
    if (y == toY)
    {
        // Moving downward
        if (toX > x)
        {
            for (int i = x + 1; i < toX; i++)
            {
                if (board[i][y] != nullptr)
                {
                    return false;
                }
            }
        }

        // Moving upward
        else
        {
            for (int i = x - 1; i > toX; i--)
            {
                if (board[i][y] != nullptr)
                {
                    return false;
                }
            }
        }
    }

    // Moving horizontally
    if (x == toX)
    {
        // Moving right
        if (toY > y)
        {
            for (int i = y + 1; i < toY; i++)
            {
                if (board[x][i] != nullptr)
                {
                    return false;
                }
            }
        }

        // Moving left
        else
        {
            for (int i = y - 1; i > toY; i--)
            {
                if (board[x][i] != nullptr)
                {
                    return false;
                }
            }
        }
    }

    // Cannot capture own piece
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color)
    {
        return false;
    }

    return true;
}

// Bishop implementation

Bishop::Bishop(char color, int x, int y)
    : Piece(color, x, y)
{
}


// Returns bishop symbol
char Bishop::getsymbol() const
{
    // White bishop
    if (color == 'W')
        return 'B';

    // Black bishop
    return 'b';
}


// Checks if bishop move is valid
bool Bishop::isvalidmove(int toX, int toY,
    Piece* board[8][8])
{
    // Bishop moves diagonally
    int dx = toX - x;
    int dy = toY - y;

    // Absolute values must be equal
    if (abs(dx) != abs(dy))
    {
        return false;
    }

    // Determine movement direction
    int stepX;
    int stepY;

    // Horizontal direction
    if (dx > 0)
        stepX = 1;
    else
        stepX = -1;

    // Vertical direction
    if (dy > 0)
        stepY = 1;
    else
        stepY = -1;

    // Check path for obstacles
    int currentX = x + stepX;
    int currentY = y + stepY;

    while (currentX != toX && currentY != toY)
    {
        if (board[currentX][currentY] != nullptr)
        {
            return false;
        }

        currentX += stepX;
        currentY += stepY;
    }

    // Cannot capture own piece
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color)
    {
        return false;
    }

    return true;
}
