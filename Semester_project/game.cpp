#include "chessboard.h"
#include "game.h"
#include "piece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include "filehandler.h"
using namespace std;

// ─────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────
Game::Game()
{
    currentTurn = 'W';
}

// ─────────────────────────────────────────
// Switch turns
// ─────────────────────────────────────────
void Game::switchTurn()
{
    if (currentTurn == 'W')
        currentTurn = 'B';
    else
        currentTurn = 'W';
}

// ─────────────────────────────────────────
// Check if game is over
// ─────────────────────────────────────────
bool Game::isGameOver()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!board.isKingAlive('W'))
    {
        SetConsoleTextAttribute(h, 11);
        cout << "\n  *** BLACK WINS! White king captured. ***\n";
        SetConsoleTextAttribute(h, 7);
        return true;
    }
    if (!board.isKingAlive('B'))
    {
        SetConsoleTextAttribute(h, 14);
        cout << "\n  *** WHITE WINS! Black king captured. ***\n";
        SetConsoleTextAttribute(h, 7);
        return true;
    }
    return false;
}

// ─────────────────────────────────────────
// Save game to file
// ─────────────────────────────────────────
void Game::saveGame()
{
    ofstream file("savegame.txt");
    if (!file.is_open())
    {
        cout << "  Could not save game.\n";
        return;
    }

    // Save whose turn it is
    file << currentTurn << "\n";

    // Save board state row by row
    // Format: color symbol (e.g. WK, BP) or -- for empty
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

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "  Game saved successfully!\n";
    SetConsoleTextAttribute(h, 7);
}

// ─────────────────────────────────────────
// Load game from file
// ─────────────────────────────────────────
bool Game::loadGame()
{
    ifstream file("savegame.txt");
    if (!file.is_open())
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 12);
        cout << "  No saved game found!\n";
        SetConsoleTextAttribute(h, 7);
        return false;
    }

    // Read whose turn
    file >> currentTurn;

    // Read board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            string cell;
            file >> cell;

            // Delete existing piece
            Piece* existing = board.getPiece(i, j);
            if (existing != nullptr)
            {
                delete existing;
            }

            if (cell == "--")
            {
                board.setPiece(i, j, nullptr);
            }
            else
            {
                char color = cell[0];
                char sym = cell[1];
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

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 10);
    cout << "  Game loaded successfully!\n";
    SetConsoleTextAttribute(h, 7);
    return true;
}

// ─────────────────────────────────────────
// Show main menu
// ─────────────────────────────────────────
void Game::showMenu()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice = 0;

    while (true)
    {
        system("cls");

        SetConsoleTextAttribute(h, 10); // green
        cout << "\n";
        cout << "  +================================+\n";
        cout << "  |      CHESS  -  C++ Edition     |\n";
        cout << "  +================================+\n\n";
        SetConsoleTextAttribute(h, 7);

        cout << "  ";
        SetConsoleTextAttribute(h, 14); // yellow
        cout << " 1: ";
        SetConsoleTextAttribute(h, 7);
        cout << "  New Game\n\n";

        cout << "  ";
        SetConsoleTextAttribute(h, 14);
        cout << " 2: ";
        SetConsoleTextAttribute(h, 7);
        cout << "  Load Saved Game\n\n";

        cout << "  ";
        SetConsoleTextAttribute(h, 14);
        cout << " 3: ";
        SetConsoleTextAttribute(h, 7);
        cout << "  Exit\n\n";

        SetConsoleTextAttribute(h, 11); // cyan
        cout << "  Enter your choice: ";
        SetConsoleTextAttribute(h, 7);
        cin >> choice;

        if (choice == 1)
        {
            // New game — reset board and turn
            currentTurn = 'W';
            system("cls");
            break;
        }
        else if (choice == 2)
        {
            system("cls");
            if (loadGame())
            {
                Sleep(1000); // show "loaded" message for 1 second
                system("cls");
                break;
            }
            else
            {
                Sleep(1500); // show "not found" message
            }
        }
        else if (choice == 3)
        {
            system("cls");
            SetConsoleTextAttribute(h, 10);
            cout << "\n  Thanks for playing! Goodbye.\n\n";
            SetConsoleTextAttribute(h, 7);
            exit(0);
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  Invalid choice. Press Enter to try again...";
            SetConsoleTextAttribute(h, 7);
            cin.ignore();
            cin.get();
        }
    }
}

// ─────────────────────────────────────────
// Main game loop
// ─────────────────────────────────────────
void Game::start()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string from, to;

    // Show menu first
    showMenu();

    while (!isGameOver())
    {
        // Clear screen before every board redraw
        system("cls");

        // Draw board
        board.display();

        // Turn indicator
        if (currentTurn == 'W')
        {
            SetConsoleTextAttribute(h, 14); // yellow
            cout << "  >>> WHITE's Turn <<<\n";
        }
        else
        {
            SetConsoleTextAttribute(h, 11); // cyan
            cout << "  >>> BLACK's Turn <<<\n";
        }
        SetConsoleTextAttribute(h, 7);

        cout << "  (type 'save' to save, 'quit' to quit)\n\n";
        cout << "  From: ";
        cin >> from;

        // Save command
        if (from == "save")
        {
            saveGame();
            Sleep(1000);
            continue;
        }

        // Quit command
        if (from == "quit")
        {
            system("cls");
            SetConsoleTextAttribute(h, 10);
            cout << "\n  Thanks for playing! Goodbye.\n\n";
            SetConsoleTextAttribute(h, 7);
            break;
        }

        cout << "  To:   ";
        cin >> to;

        // Validate format
        if (from.length() != 2 || to.length() != 2 ||
            from[0] < 'a' || from[0] > 'h' ||
            to[0] < 'a' || to[0]   > 'h' ||
            from[1] < '1' || from[1] > '8' ||
            to[1] < '1' || to[1]   > '8')
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  Invalid format! Use letter(a-h) + number(1-8). Example: e2\n";
            SetConsoleTextAttribute(h, 7);
            Sleep(1500);
            continue;
        }

        // Parse chess notation
        int fromY = from[0] - 'a';
        int fromX = 8 - (from[1] - '0');
        int toY = to[0] - 'a';
        int toX = 8 - (to[1] - '0');

        if (board.movePiece(fromX, fromY, toX, toY, currentTurn))
        {
            // Auto save after every move
            saveGame();
            switchTurn();
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  Invalid move! Try again.\n";
            SetConsoleTextAttribute(h, 7);
            Sleep(1500);
        }
    }

    // Game over screen
    system("cls");
    board.display();
    SetConsoleTextAttribute(h, 10);
    cout << "\n  +==============================+\n";
    cout << "  |          GAME  OVER          |\n";
    cout << "  +==============================+\n\n";
    SetConsoleTextAttribute(h, 7);
    cout << "  Press Enter to exit...";
    cin.ignore();
    cin.get();
}