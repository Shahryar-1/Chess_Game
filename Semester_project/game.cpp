#include "chessboard.h"
#include "game.h"
#include <windows.h>
#include <iostream>
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
        cout << "  Exit\n\n";

        SetConsoleTextAttribute(h, 11); // cyan
        cout << "  Enter your choice: ";
        SetConsoleTextAttribute(h, 7);
        cin >> choice;

        if (choice == 1)
        {
            currentTurn = 'W';
            system("cls");
            break;
        }
        else if (choice == 2)
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
        system("cls");

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

        cout << "  (type 'quit' to quit)\n\n";
        cout << "  From: ";
        cin >> from;

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

        // ── Try block: covers input validation + move execution ────────
        try
        {
            // Throw if format is wrong e.g. "z9" or "abc"
            if (from.length() != 2 || to.length() != 2 ||
                from[0] < 'a' || from[0] > 'h' ||
                to[0] < 'a' || to[0]   > 'h' ||
                from[1] < '1' || from[1] > '8' ||
                to[1] < '1' || to[1]   > '8')
            {
                throw InvalidInputException(from);
            }

            // Parse chess notation
            int fromY = from[0] - 'a';
            int fromX = 8 - (from[1] - '0');
            int toY = to[0] - 'a';
            int toX = 8 - (to[1] - '0');

            // Throw if move is illegal
            if (!board.movePiece(fromX, fromY, toX, toY, currentTurn))
                throw InvalidMoveException();

            // Move succeeded — switch turn
            switchTurn();
        }
        catch (const InvalidInputException& e)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  " << e.what() << "\n";
            SetConsoleTextAttribute(h, 7);
            Sleep(2000);
        }
        catch (const InvalidMoveException& e)
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  " << e.what() << "\n";
            SetConsoleTextAttribute(h, 7);
            Sleep(2000);
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