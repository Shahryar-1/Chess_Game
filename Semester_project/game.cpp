#include "chessboard.h"
#include "game.h"
#include <windows.h>
#include <iostream>
using namespace std;

// Constructor
Game::Game()
{
    currentTurn = 'W';
}

// Switch turns
void Game::switchTurn()
{
    if (currentTurn == 'W')
        currentTurn = 'B';
    else
        currentTurn = 'W';
}

// Check if game is over
bool Game::isGameOver()
{
    // Check checkmate for current player
    if (board.isCheckmate(currentTurn))
        return true;

    // Backup check — if king is directly captured
    if (!board.isKingAlive('W'))
        return true;

    if (!board.isKingAlive('B'))
        return true;

    return false;
}

// Show main menu
void Game::showMenu()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice = 0;

    while (true)
    {
        system("cls");

        SetConsoleTextAttribute(h, 10);
        cout << "\n";
        cout << "  +================================+\n";
        cout << "  |      CHESS  -  C++ Edition     |\n";
        cout << "  +================================+\n\n";
        SetConsoleTextAttribute(h, 7);

        cout << "  ";
        SetConsoleTextAttribute(h, 14);
        cout << " 1: ";
        SetConsoleTextAttribute(h, 7);
        cout << "  New Game\n\n";

        cout << "  ";
        SetConsoleTextAttribute(h, 14);
        cout << " 2: ";
        SetConsoleTextAttribute(h, 7);
        cout << "  Exit\n\n";

        SetConsoleTextAttribute(h, 11);
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

// Main game loop
void Game::start()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string from, to;

    showMenu();

    while (!isGameOver())
    {
        system("cls");
        board.display();

        // Warn if current player is in check
        if (board.isInCheck(currentTurn))
        {
            SetConsoleTextAttribute(h, 12);
            cout << "  *** WARNING: Your king is in CHECK! ***\n";
            SetConsoleTextAttribute(h, 7);
        }

        // Turn indicator
        if (currentTurn == 'W')
        {
            SetConsoleTextAttribute(h, 14);
            cout << "  >>> WHITE's Turn <<<\n";
        }
        else
        {
            SetConsoleTextAttribute(h, 11);
            cout << "  >>> BLACK's Turn <<<\n";
        }
        SetConsoleTextAttribute(h, 7);

        cout << "  (type 'quit' to quit)\n\n";
        cout << "  From: ";
        cin >> from;

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

        if (from.length() != 2 || to.length() != 2 ||
            from[0] < 'a' || from[0] > 'h' ||
            to[0] < 'a' || to[0]   > 'h' ||
            from[1] < '1' || from[1] > '8' ||
            to[1] < '1' || to[1]   > '8')
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  Invalid format! Use letter(a-h) + number(1-8). Example: e2\n";
            SetConsoleTextAttribute(h, 7);
            Sleep(5000);
            continue;
        }

        int fromY = from[0] - 'a';
        int fromX = 8 - (from[1] - '0');
        int toY = to[0] - 'a';
        int toX = 8 - (to[1] - '0');

        if (board.movePiece(fromX, fromY, toX, toY, currentTurn))
        {
            switchTurn();
        }
        else
        {
            SetConsoleTextAttribute(h, 12);
            cout << "\n  Invalid move! Try again.\n";
            SetConsoleTextAttribute(h, 7);
            Sleep(5000);
        }
    }

    // Game over screen
    system("cls");
    board.display();

    // Print correct win message based on who was checkmated
    // currentTurn is the player who got checkmated
    // so the OTHER player wins
    if (!board.isKingAlive('W') || board.isCheckmate('W'))
    {
        SetConsoleTextAttribute(h, 11);
        cout << "\n  *** BLACK WINS! ***\n";
        SetConsoleTextAttribute(h, 7);
    }
    else if (!board.isKingAlive('B') || board.isCheckmate('B'))
    {
        SetConsoleTextAttribute(h, 14);
        cout << "\n  *** WHITE WINS! ***\n";
        SetConsoleTextAttribute(h, 7);
    }

    Sleep(3000);

    SetConsoleTextAttribute(h, 10);
    cout << "\n  +==============================+\n";
    cout << "  |          GAME  OVER          |\n";
    cout << "  +==============================+\n\n";
    SetConsoleTextAttribute(h, 7);
    cout << "  Press Enter to exit...";
    cin.ignore();
    cin.get();
}