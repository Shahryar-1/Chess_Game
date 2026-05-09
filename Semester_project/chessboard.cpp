#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "chessboard.h"
#include <windows.h>
#include <iostream>
using namespace std;

ChessBoard::ChessBoard()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = nullptr;

    // BLACK side (BLUE) — rows 0 and 1
    grid[0][0] = new Rook('B', 0, 0);
    grid[0][1] = new Knight('B', 0, 1);
    grid[0][2] = new Bishop('B', 0, 2);
    grid[0][3] = new Queen('B', 0, 3);
    grid[0][4] = new King('B', 0, 4);
    grid[0][5] = new Bishop('B', 0, 5);
    grid[0][6] = new Knight('B', 0, 6);
    grid[0][7] = new Rook('B', 0, 7);
    for (int i = 0; i < 8; i++)
        grid[1][i] = new Pawn('B', 1, i);

    // WHITE side (RED) — rows 6 and 7
    grid[7][0] = new Rook('W', 7, 0);
    grid[7][1] = new Knight('W', 7, 1);
    grid[7][2] = new Bishop('W', 7, 2);
    grid[7][3] = new Queen('W', 7, 3);
    grid[7][4] = new King('W', 7, 4);
    grid[7][5] = new Bishop('W', 7, 5);
    grid[7][6] = new Knight('W', 7, 6);
    grid[7][7] = new Rook('W', 7, 7);
    for (int i = 0; i < 8; i++)
        grid[6][i] = new Pawn('W', 6, i);
}

// Destructor

ChessBoard::~ChessBoard()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] != nullptr)
            {
                delete grid[i][j];
                grid[i][j] = nullptr;
            }
}

// setPiece  (used by loadGame)

void ChessBoard::setPiece(int x, int y, Piece* p)
{
    grid[x][y] = p;
}

void ChessBoard::display()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    const WORD WHITE_SQ = 240;  // white  bg, white  fg (blank)
    const WORD BLACK_SQ = 0;    // black  bg, black  fg (blank)

    // piece colours
    const WORD RED_ON_W = 252;  // white  bg + bright red   (12)
    const WORD RED_ON_B = 12;   // black  bg + bright red   (12)
    const WORD BLUE_ON_W = 249;  // white  bg + bright blue  (9)
    const WORD BLUE_ON_B = 9;    // black  bg + bright blue  (9)

    // label colour (bright green)
    const WORD LABEL = 10;

    // ── header label ────────────────────────────────────────
    SetConsoleTextAttribute(h, LABEL);
    cout << "\n";
    cout << "         BLUE (Black)  \n\n";
    cout << "       a    b    c    d    e    f    g    h\n";
    SetConsoleTextAttribute(h, 7);

    // ── top border ──────────────────────────────────────────
    SetConsoleTextAttribute(h, LABEL);
    cout << "     +----+----+----+----+----+----+----+----+\n";
    SetConsoleTextAttribute(h, 7);

    for (int i = 0; i < 8; i++)
    {
        // ── 3 lines per row ─────────────────────────────────
        for (int line = 0; line < 3; line++)
        {
            if (line == 1)
            {
                // row number on left
                SetConsoleTextAttribute(h, LABEL);
                cout << "  " << (8 - i) << "  ";
                SetConsoleTextAttribute(h, 7);
            }
            else
            {
                // empty left margin
                SetConsoleTextAttribute(h, 7);
                cout << "     ";
            }

            for (int j = 0; j < 8; j++)
            {
                bool isWhiteSq = (i + j) % 2 == 0;

                if (grid[i][j] == nullptr)
                {
                    // empty square
                    SetConsoleTextAttribute(h, isWhiteSq ? WHITE_SQ : BLACK_SQ);
                    cout << "    ";
                    SetConsoleTextAttribute(h, 7);
                    cout << "|";
                }
                else
                {
                    char color = grid[i][j]->getcolor();
                    char sym = grid[i][j]->getsymbol();

                    WORD attr;
                    if (color == 'W')
                        attr = isWhiteSq ? RED_ON_W : RED_ON_B;
                    else
                        attr = isWhiteSq ? BLUE_ON_W : BLUE_ON_B;

                    if (line == 1)
                    {
                        // centre the piece letter (K Q R B N P)
                        // RED for White side, BLUE for Black side
                        SetConsoleTextAttribute(h, attr);
                        cout << " " << sym << "  ";
                        SetConsoleTextAttribute(h, 7);
                        cout << "|";
                    }
                    else
                    {
                        SetConsoleTextAttribute(h, isWhiteSq ? WHITE_SQ : BLACK_SQ);
                        cout << "    ";
                        SetConsoleTextAttribute(h, 7);
                        cout << "|";
                    }
                }
            }

            if (line == 1)
            {
                // row number on right
                SetConsoleTextAttribute(h, LABEL);
                cout << "  " << (8 - i);
                SetConsoleTextAttribute(h, 7);
            }

            cout << "\n";
        }

        // ── row separator ────────────────────────────────────
        SetConsoleTextAttribute(h, LABEL);
        cout << "     +----+----+----+----+----+----+----+----+\n";
        SetConsoleTextAttribute(h, 7);
    }

    // ── footer labels ────────────────────────────────────────
    SetConsoleTextAttribute(h, LABEL);
    cout << "       a    b    c    d    e    f    g    h\n";
    cout << "\n";
    cout << "          RED (White)  \n\n";

    // ── legend ───────────────────────────────────────────────
    SetConsoleTextAttribute(h, 12);   // bright red
    cout << "  RED  pieces = White side  ";
    SetConsoleTextAttribute(h, 9);    // bright blue
    cout << "  BLUE pieces = Black side\n\n";
    SetConsoleTextAttribute(h, 7);
}

// getPiece
Piece* ChessBoard::getPiece(int x, int y)
{
    return grid[x][y];
}
// isInsideBoard
bool ChessBoard::isInsideBoard(int x, int y)
{
    return (x >= 0 && x < 8 && y >= 0 && y < 8);
}

// movePiece

bool ChessBoard::movePiece(int fromX, int fromY,
    int toX, int toY,
    char currentTurn)
{
    if (!isInsideBoard(fromX, fromY) || !isInsideBoard(toX, toY))
        return false;

    Piece* piece = grid[fromX][fromY];

    if (piece == nullptr)
        return false;

    if (piece->getcolor() != currentTurn)
        return false;

    if (!piece->isvalidmove(toX, toY, grid))
        return false;

    delete grid[toX][toY];
    grid[toX][toY] = piece;
    grid[fromX][fromY] = nullptr;
    piece->setposition(toX, toY);

    return true;
}

// isKingAlive
bool ChessBoard::isKingAlive(char color)
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (grid[i][j] != nullptr)
                if (grid[i][j]->getcolor() == color &&
                    (grid[i][j]->getsymbol() == 'K' ||
                        grid[i][j]->getsymbol() == 'k'))
                    return true;
    return false;
}