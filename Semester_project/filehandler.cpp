#include "FileHandler.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

// Save file name
const string FileHandler::SAVE_FILE = "savegame.txt";

// ─────────────────────────────────────────
// Save game
// ─────────────────────────────────────────
void FileHandler::saveGame(ChessBoard& board, char currentTurn)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    ofstream file(SAVE_FILE);
    if (!file.is_open())
    {
        SetConsoleTextAttribute(h, 12); // red
        cout << "\n  ERROR: Could not open save file!\n";
        SetConsoleTextAttribute(h, 7);
        return;
    }

    // Line 1: whose turn it is
    file << currentTurn << "\n";

    // Lines 2-9: board state
    // Each cell: WK, BP, -- (empty)
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Piece* p = board.getPiece(i, j);
            if (p == nullptr)
                file << "-- ";
            else
                file << p->getcolor() << p->getsymbol() << " ";
        }
        file << "\n";
    }

    file.close();

    SetConsoleTextAttribute(h, 10); // green
    cout << "\n  Game saved to '" << SAVE_FILE << "'\n";
    SetConsoleTextAttribute(h, 7);
}

// ─────────────────────────────────────────
// Load game
// ─────────────────────────────────────────
bool FileHandler::loadGame(ChessBoard& board, char& currentTurn)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    ifstream file(SAVE_FILE);
    if (!file.is_open())
    {
        SetConsoleTextAttribute(h, 12); // red
        cout << "\n  ERROR: No save file found!\n";
        SetConsoleTextAttribute(h, 7);
        return false;
    }

    // Read whose turn
    file >> currentTurn;

    // Read board row by row
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            string cell;
            file >> cell;

            // Clear existing piece at this position
            Piece* existing = board.getPiece(i, j);
            if (existing != nullptr)
            {
                delete existing;
                board.setPiece(i, j, nullptr);
            }

            // Place new piece based on saved data
            if (cell == "--")
            {
                board.setPiece(i, j, nullptr);
            }
            else
            {
                char color = cell[0]; // W or B
                char sym = cell[1]; // K Q R B N P

                Piece* p = nullptr;

                if (sym == 'R') p = new Rook(color, i, j);
                else if (sym == 'N') p = new Knight(color, i, j);
                else if (sym == 'B') p = new Bishop(color, i, j);
                else if (sym == 'Q') p = new Queen(color, i, j);
                else if (sym == 'K') p = new King(color, i, j);
                else if (sym == 'P') p = new Pawn(color, i, j);

                board.setPiece(i, j, p);
            }
        }
    }

    file.close();

    SetConsoleTextAttribute(h, 10); // green
    cout << "\n  Game loaded from '" << SAVE_FILE << "'\n";
    SetConsoleTextAttribute(h, 7);
    return true;
}

// ─────────────────────────────────────────
// Check if save file exists
// ─────────────────────────────────────────
bool FileHandler::saveExists()
{
    ifstream file(SAVE_FILE);
    return file.good();
}

// ─────────────────────────────────────────
// Delete save file
// ─────────────────────────────────────────
void FileHandler::deleteSave()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    if (remove(SAVE_FILE.c_str()) == 0)
    {
        SetConsoleTextAttribute(h, 10);
        cout << "\n  Save file deleted.\n";
        SetConsoleTextAttribute(h, 7);
    }
    else
    {
        SetConsoleTextAttribute(h, 12);
        cout << "\n  No save file to delete.\n";
        SetConsoleTextAttribute(h, 7);
    }
}