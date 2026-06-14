#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "chessboard.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
using namespace std;

ChessBoard::ChessBoard()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            grid[i][j] = nullptr;

    enPassantX = -1;
    enPassantY = -1;
    enPassantAvailable = false;

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

    loadTextures();
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

void ChessBoard::display()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    const WORD WHITE_SQ = 240;
    const WORD BLACK_SQ = 0;
    const WORD RED_ON_W = 252;
    const WORD RED_ON_B = 12;
    const WORD BLUE_ON_W = 249;
    const WORD BLUE_ON_B = 9;
    const WORD LABEL = 10;

    // Header
    SetConsoleTextAttribute(h, LABEL);
    cout << "\n";
    cout << "         BLUE (Black)  \n\n";
    cout << "       a    b    c    d    e    f    g    h\n";
    SetConsoleTextAttribute(h, 7);

    // Top border
    SetConsoleTextAttribute(h, LABEL);
    cout << "     +----+----+----+----+----+----+----+----+\n";
    SetConsoleTextAttribute(h, 7);

    for (int i = 0; i < 8; i++)
    {
        for (int line = 0; line < 3; line++)
        {
            if (line == 1)
            {
                SetConsoleTextAttribute(h, LABEL);
                cout << "  " << (8 - i) << "  ";
                SetConsoleTextAttribute(h, 7);
            }
            else
            {
                SetConsoleTextAttribute(h, 7);
                cout << "     ";
            }

            for (int j = 0; j < 8; j++)
            {
                bool isWhiteSq = (i + j) % 2 == 0;

                if (grid[i][j] == nullptr)
                {
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
                SetConsoleTextAttribute(h, LABEL);
                cout << "  " << (8 - i);
                SetConsoleTextAttribute(h, 7);
            }

            cout << "\n";
        }

        // Row separator
        SetConsoleTextAttribute(h, LABEL);
        cout << "     +----+----+----+----+----+----+----+----+\n";
        SetConsoleTextAttribute(h, 7);
    }

    // Footer
    SetConsoleTextAttribute(h, LABEL);
    cout << "       a    b    c    d    e    f    g    h\n";
    cout << "\n";
    cout << "          RED (White)  \n\n";

    // Legend
    SetConsoleTextAttribute(h, 12);
    cout << "  RED  pieces = White side  ";
    SetConsoleTextAttribute(h, 9);
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

    char sym = piece->getsymbol();

    // EN PASSANT CHECK
    if (enPassantAvailable && (sym == 'P' || sym == 'p'))
    {
        bool isEnPassant = false;

        // White pawn en passant
        if (sym == 'P' &&
            fromX == 3 &&
            toX == 2 &&
            toY == enPassantY &&
            (toY == fromY - 1 || toY == fromY + 1))
        {
            isEnPassant = true;
        }

        // Black pawn en passant
        if (sym == 'p' &&
            fromX == 4 &&
            toX == 5 &&
            toY == enPassantY &&
            (toY == fromY - 1 || toY == fromY + 1))
        {
            isEnPassant = true;
        }

        if (isEnPassant)
        {
            grid[toX][toY] = piece;
            grid[fromX][fromY] = nullptr;
            piece->setposition(toX, toY);

            delete grid[enPassantX][enPassantY];
            grid[enPassantX][enPassantY] = nullptr;

            enPassantAvailable = false;
            enPassantX = -1;
            enPassantY = -1;

            return true;
        }
    }

    if (!piece->isvalidmove(toX, toY, grid))
        return false;

    // Temporarily make the move
    Piece* captured = grid[toX][toY];
    grid[toX][toY] = piece;
    grid[fromX][fromY] = nullptr;
    piece->setposition(toX, toY);

    // Check if own king is in check after this move
    if (isInCheck(currentTurn))
    {
        grid[fromX][fromY] = piece;
        grid[toX][toY] = captured;
        piece->setposition(fromX, fromY);
        return false;
    }

    if (captured != nullptr)
        delete captured;

    // Reset en passant after every move
    enPassantAvailable = false;
    enPassantX = -1;
    enPassantY = -1;

    // White pawn moved 2 steps from row 6 to row 4
    if (sym == 'P' && fromX == 6 && toX == 4)
    {
        enPassantAvailable = true;
        enPassantX = 4;
        enPassantY = toY;
    }

    // Black pawn moved 2 steps from row 1 to row 3
    if (sym == 'p' && fromX == 1 && toX == 3)
    {
        enPassantAvailable = true;
        enPassantX = 3;
        enPassantY = toY;
    }

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

bool ChessBoard::isUnderAttack(int x, int y, char enemyColor)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] != nullptr &&
                grid[i][j]->getcolor() == enemyColor &&
                grid[i][j]->isvalidmove(x, y, grid))
                return true;
        }
    }
    return false;
}

bool ChessBoard::isInCheck(char color)
{
    int kingX = -1, kingY = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++)
            if (grid[i][j] != nullptr &&
                grid[i][j]->getcolor() == color &&
                (grid[i][j]->getsymbol() == 'K' ||
                    grid[i][j]->getsymbol() == 'k'))
            {
                kingX = i;
                kingY = j;
                break;
            }
        if (kingX != -1) break;
    }
    if (kingX == -1 || kingY == -1)
        return false;

    char enemyColor = (color == 'W') ? 'B' : 'W';

    return isUnderAttack(kingX, kingY, enemyColor);
}

bool ChessBoard::isCheckmate(char color)
{
    if (!isInCheck(color))
        return false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (grid[i][j] != nullptr &&
                grid[i][j]->getcolor() == color)
            {
                for (int x = 0; x < 8; x++)
                {
                    for (int y = 0; y < 8; y++)
                    {
                        if (grid[i][j]->isvalidmove(x, y, grid))
                        {
                            Piece* temp = grid[x][y];
                            grid[x][y] = grid[i][j];
                            grid[i][j] = nullptr;
                            grid[x][y]->setposition(x, y);

                            bool stillInCheck = isInCheck(color);

                            grid[i][j] = grid[x][y];
                            grid[x][y] = temp;
                            grid[i][j]->setposition(i, j);

                            if (!stillInCheck)
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

// ─────────────────────────────────────────
// SFML — load textures
// ─────────────────────────────────────────
void ChessBoard::loadTextures()
{
    const string files[12] = {
        "assets/wP.png", "assets/wR.png", "assets/wN.png",
        "assets/wB.png", "assets/wQ.png", "assets/wK.png",
        "assets/bP.png", "assets/bR.png", "assets/bN.png",
        "assets/bB.png", "assets/bQ.png", "assets/bK.png"
    };

    for (int i = 0; i < 12; i++)
    {
        if (!textures[i].loadFromFile(files[i]))
        {
            char currentDir[MAX_PATH];
            GetCurrentDirectoryA(MAX_PATH, currentDir);
            string msg = "Failed to load: " + files[i] +
                "\n\nProgram is running from:\n" +
                string(currentDir) +
                "\n\nPlace assets folder there.";
            MessageBoxA(NULL, msg.c_str(), "Image Load Error", MB_OK | MB_ICONERROR);
        }
        else
        {
            textures[i].setSmooth(true);
        }
    }
}

// ─────────────────────────────────────────
// SFML — map piece to sprite sheet index
// 0=wP 1=wR 2=wN 3=wB 4=wQ 5=wK  6=bP 7=bR 8=bN 9=bB 10=bQ 11=bK
// ─────────────────────────────────────────
int ChessBoard::getSpriteIndex(char color, char symbol) const
{
    int base = (color == 'W') ? 0 : 6;
    char sym = toupper(symbol);

    if (sym == 'P') return base + 0;
    if (sym == 'R') return base + 1;
    if (sym == 'N') return base + 2;
    if (sym == 'B') return base + 3;
    if (sym == 'Q') return base + 4;
    if (sym == 'K') return base + 5;
    return base;
}

// ─────────────────────────────────────────
// SFML — draw the board, pieces, highlight, labels
// ─────────────────────────────────────────
void ChessBoard::drawSFML(sf::RenderWindow& window,
    int selectedRow, int selectedCol,
    bool pieceSelected)
{
    const float TILE = 80.f;
    const float OFFSET = 40.f;

    sf::Color lightSquare(240, 217, 181);
    sf::Color darkSquare(181, 136, 99);
    sf::Color highlight(246, 246, 105, 180);

    sf::RectangleShape square(sf::Vector2f(TILE, TILE));

    // Draw 8x8 squares
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            square.setPosition(sf::Vector2f(OFFSET + col * TILE, OFFSET + row * TILE));
            square.setFillColor((row + col) % 2 == 0 ? lightSquare : darkSquare);
            window.draw(square);

            if (pieceSelected && row == selectedRow && col == selectedCol)
            {
                square.setFillColor(highlight);
                window.draw(square);
            }
        }
    }

    // Draw pieces
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (grid[row][col] == nullptr) continue;

            char color = grid[row][col]->getcolor();
            char symbol = grid[row][col]->getsymbol();
            int  idx = getSpriteIndex(color, symbol);

            sf::Sprite sprite(textures[idx]);
            sf::FloatRect bounds = sprite.getLocalBounds();
            sprite.setScale(sf::Vector2f((TILE - 8.f) / bounds.size.x,
                (TILE - 8.f) / bounds.size.y));
            sprite.setPosition(sf::Vector2f(OFFSET + col * TILE + 4.f,
                OFFSET + row * TILE + 4.f));
            window.draw(sprite);
        }
    }

    // Draw rank/file labels
    sf::Font font;
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) return;

    sf::Text label(font, "", 14);
    label.setFillColor(sf::Color(255, 255, 255));

    // Files: a-h along the bottom
    for (int col = 0; col < 8; col++)
    {
        label.setString(string(1, char('a' + col)));
        label.setPosition(sf::Vector2f(OFFSET + col * TILE + TILE / 2.f - 5.f,
            OFFSET + 8 * TILE + 6.f));
        window.draw(label);
    }

    // Ranks: 8-1 along the left
    for (int row = 0; row < 8; row++)
    {
        label.setString(to_string(8 - row));
        label.setPosition(sf::Vector2f(8.f, OFFSET + row * TILE + TILE / 2.f - 9.f));
        window.draw(label);
    }
}