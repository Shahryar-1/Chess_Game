#pragma once
#include <iostream>
using namespace std;

// BASE CLASS : Piece
// Every chess piece will inherit from this class
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

// PAWN CLASS
class Pawn : public Piece
{
public:
    // Constructor
    Pawn(char color, int x, int y);

    // Checks if pawn move is valid
    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    // Returns symbol of pawn
    char getsymbol() const override;
};

// ROOK CLASS
// Moves horizontally and vertically
class Rook : public Piece
{
public:

    Rook(char color, int x, int y);

    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    char getsymbol() const override;
};

// BISHOP CLASS
// Moves diagonally
class Bishop : public Piece
{

public:

    Bishop(char color, int x, int y);

    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    char getsymbol() const override;
};

// KNIGHT CLASS
// Moves in L-shape
class Knight : public Piece
{

public:

    Knight(char color, int x, int y);

    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    char getsymbol() const override;
};

// QUEEN CLASS
// Can move in all directions
class Queen : public Piece
{

public:

    Queen(char color, int x, int y);

    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    char getsymbol() const override;
};

// KING CLASS
// Can move one step in any direction
class King : public Piece
{

public:

    King(char color, int x, int y);

    bool isvalidmove(int toX, int toY,
        Piece* board[8][8]) override;

    char getsymbol() const override;
};

// CHESS BOARD CLASS
// Controls the whole board and pieces
class ChessBoard
{

private:

    // 8x8 board storing piece pointers
    Piece* grid[8][8];

public:

    // Constructor
    ChessBoard();

    // Destructor
    ~ChessBoard();

    // Displays board on console
    void display();

    // Returns piece at given position
    // Returns nullptr if square is empty
    Piece* getPiece(int x, int y);

    // Checks if coordinates are inside board
    bool isInsideBoard(int x, int y);

    // Moves piece from one position to another
    bool movePiece(int fromX, int fromY,
        int toX, int toY,
        char currentTurn);

    // Checks if king of given color is alive
    bool isKingAlive(char color);
};

// GAME CLASS
// Controls complete gameplay
class Game
{

private:

    ChessBoard board;

    // Stores whose turn it is
    // 'W' = White
    // 'B' = Black
    char currentTurn;

public:

    // Constructor
    Game();

    // Starts the game loop
    void start();

    // Switches turns after every move
    void switchTurn();

    // Checks if game is over
    bool isGameOver();
};