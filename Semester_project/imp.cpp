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

// Knight implementation
// knight constructor 

Knight::Knight(char color, int x, int y) : Piece(color, x, y){}

// returns symbol of knight
char Knight::getsymbol() const
{
    if (color == 'W')
    {
        return 'N';
    }

    return 'n';
}

bool Knight::isvalidmove(int toX, int toY, Piece* board[8][8])
{
    // Knight moves in L-shape
    int dx = abs(toX - x);
    int dy = abs(toY - y);
    if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2)))
    {
        return false;
    }
    // Cannot capture own piece
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color)
    {
        return false;
    }
    return true;
}


//Queen constructor
Queen::Queen(char color,int x,int y): Piece(color,x,y){}

// checks if queen move is valid
bool Queen::isvalidmove(int toX, int toY, Piece* board[8][8])
{
    int dx = toX - x;
    int dy = toY - y;

    // Vertical Movement
    if (y == toY)
    {
        int step;

        if (toX > x)
        {
            step = 1;
        }
        else
        {
            step = -1;
        }

        // Check path
        for (int i = x + step; i != toX; i += step)
        {
            if (board[i][y] != nullptr)
            {
                return false;
            }
        }

        // Own piece check
        if (board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() == color)
        {
            return false;
        }

        return true;
    }
    // Horizontal Movement
    if (x == toX)
    {
        int step;

        if (toY > y)
        {
            step = 1;
        }
        else
        {
            step = -1;
        }

        // Check path
        for (int i = y + step; i != toY; i += step)
        {
            if (board[x][i] != nullptr)
            {
                return false;
            }
        }

        // Own piece check
        if (board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() == color)
        {
            return false;
        }

        return true;
    }

    // Diagonal Movement
    if (abs(dx) == abs(dy))
    {
        int stepX;
        int stepY;

        if (dx > 0)
        {
            stepX = 1;
        }
        else
        {
            stepX = -1;
        }

        if (dy > 0)
        {
            stepY = 1;
        }
        else
        {
            stepY = -1;
        }
      
        int currentX = x + stepX;
        int currentY = y + stepY;

        // Check diagonal path
        while (currentX != toX && currentY != toY)
        {
            if (board[currentX][currentY] != nullptr)
            {
                return false;
            }

            currentX += stepX;
            currentY += stepY;
        }

        // Own piece check
        if (board[toX][toY] != nullptr &&
            board[toX][toY]->getcolor() == color)
        {
            return false;
        }

        return true;
    }

    return false;
}

//This will return the color for the queen piece 
//if return Capital Q the Piece is White and if small q the piece is black
char Queen::getsymbol() const
{
    if (color == 'W')
    {
        return 'Q';
    }

    return 'q';
}

King ::King(char color,int x,int y):Piece(color,x,y){}


//This will return the color for the king piece 
//if return Capital K the Piece is White and if small k the piece is black
char King::getsymbol() const
{
    if (color == 'W')
    {
        return 'K';
    }

    return 'k';
}


bool King::isvalidmove(int toX, int toY, Piece* board[8][8]) {
    int dx = abs(toX - x);
    int dy = abs(toY - y);
    

    //king as only move one step in any direction
    //so dx and dy must be 0 or 1
    if (dx > 1 || dy > 1)
    {
        // Move is more than 1 step — invalid
        return false;
    }

    //now if the position didnt changes at all means there is no move so it would be alo invalid
    if (dx == 0 && dy == 0) {
        return false;
    }

    //cannot capture its own piece of saem color
    if (board[toX][toY] != nullptr &&
        board[toX][toY]->getcolor() == color) {
        return false;
    }

    //if allt he if conditions are passed then it would retun true
    return true;

}

ChessBoard::ChessBoard()
{

    //intialising all the position with default as null ptr
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            grid[i][j] = nullptr;
        }
    }


    // now giving each piece default positions
    grid[0][0] = new Rook('B', 0, 0);
    grid[0][1] = new Knight('B', 0, 1);
    grid[0][2] = new Bishop('B', 0, 2);
    grid[0][3] = new Queen('B', 0, 3);
    grid[0][4] = new King('B', 0, 4);
    grid[0][5] = new Bishop('B', 0, 5);
    grid[0][6] = new Knight('B', 0, 6);
    grid[0][7] = new Rook('B', 0, 7);


    //giving black pawns its default position
    for (int i = 0; i < 8; i++) 
    {
        //giving pawns in each column
        grid[1][i]= new Pawn('B', 1, i);
    }


    //Giving default positions for white pieces 
    grid[7][0] = new Rook('W', 7, 0);
    grid[7][1] = new Knight('W', 7, 1);
    grid[7][2] = new Bishop('W', 7, 2);
    grid[7][3] = new Queen('W', 7, 3);
    grid[7][4] = new King('W', 7, 4);
    grid[7][5] = new Bishop('W', 7, 5);
    grid[7][6] = new Knight('W', 7, 6);
    grid[7][7] = new Rook('W', 7, 7);


    //giving default positions for white pawns
    for (int i = 0; i < 8; i++) 
    {
        //giving pawns in each column
        grid[6][i] = new Pawn('W', 1, i);
    }

    
}


//destructor for freeing squares adn ggrid for null ptr and if any piece dies
ChessBoard::~ChessBoard()
{

    //checks all the rows
	for (int i = 0; i < 8; i++) 
    {
        //all columns
        for(int j = 0; j < 8; j++) 
        {

            //check if any piece is in the grid or not
            if (grid[i][j] != nullptr) 
            {
                //delete the piece at that position
                delete grid[i][j];

                grid[i][j] = nullptr;
            }
        }
    }
}


void ChessBoard::display() 
{
    cout << "    1   2   3   4   5   6   7   8" << endl;
    for (int i = 0; i < 8; i++) {
        cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == nullptr) 
            {
                //prints . at the position where no piece is present where grid is nullptr
                cout << " . ";
            }
            else 
            {
                //prints piece symbol usign getter function of getsymbol
                cout << " " << grid[i][j]->getsymbol() << " ";
            }
            cout << " |";

        }
        cout << " " << i+1 << endl;
    }
    cout << "    1   2   3   4   5   6   7   8" << endl;
}

// Returns piece at position
Piece* ChessBoard::getPiece(int x, int y)
{
    return grid[x][y];
}


// Checks board boundaries
bool ChessBoard::isInsideBoard(int x, int y)
{
    return (x >= 0 && x < 8 &&
        y >= 0 && y < 8);
}


// Moves piece
bool ChessBoard::movePiece(int fromX, int fromY,
    int toX, int toY,
    char currentTurn)
{
    // Boundary check
    if (!isInsideBoard(fromX, fromY) ||
        !isInsideBoard(toX, toY))
    {
        return false;
    }

    Piece* piece = grid[fromX][fromY];

    // No piece selected
    if (piece == nullptr)
    {
        return false;
    }

    // Wrong turn
    if (piece->getcolor() != currentTurn)
    {
        return false;
    }

    // Invalid movement
    if (!piece->isvalidmove(toX, toY, grid))
    {
        return false;
    }

    // Delete captured piece
    delete grid[toX][toY];

    // Move piece
    grid[toX][toY] = piece;
    grid[fromX][fromY] = nullptr;

    // Update position
    piece->setposition(toX, toY);

    return true;
}


// Checks if king is alive
bool ChessBoard::isKingAlive(char color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (grid[i][j] != nullptr)
            {
                if (grid[i][j]->getcolor() == color &&
                    (grid[i][j]->getsymbol() == 'K' ||
                        grid[i][j]->getsymbol() == 'k'))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Game Implementation 
// Constructor
Game::Game()
{
    currentTurn = 'W';
}


// Switch turns
void Game::switchTurn()
{
    if (currentTurn == 'W')
    {
        currentTurn = 'B';
    }
    else
    {
        currentTurn = 'W';
    }
}


// Checks if game is over
bool Game::isGameOver()
{
    // White king dead
    if (!board.isKingAlive('W'))
    {
        cout << "Black Wins!" << endl;
        return true;
    }

    // Black king dead
    if (!board.isKingAlive('B'))
    {
        cout << "White Wins!" << endl;
        return true;
    }

    return false;
}


// Main game loop
void Game::start()
{
    int fromX, fromY;
    int toX, toY;

    while (!isGameOver())
    {
        board.display();

        cout << currentTurn << "'s Turn" << endl;

        cout << "Enter current position (x y): ";
        cin >> fromX >> fromY;

        cout << "Enter new position (x y): ";
        cin >> toX >> toY;

        if (board.movePiece(fromX, fromY,
            toX, toY, currentTurn))
        {
            switchTurn();
        }
        else
        {
            cout << "Invalid Move!" << endl;
        }
    }
}