#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "chessboard.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
using namespace std;

const float TILE = 80.f;
const float OFFSET = 40.f;

// ─────────────────────────────────────────
// Constructor
// ─────────────────────────────────────────
Game::Game()
    : window(sf::VideoMode({ 720, 760 }), "Chess - OOP Final Project",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize),
    currentTurn('W'),
    selectedRow(-1),
    selectedCol(-1),
    pieceSelected(false),
    statusMsg("White's turn  —  click a piece to move")
{
    window.setFramerateLimit(60);
}

// ─────────────────────────────────────────
// Switch turns
// ─────────────────────────────────────────
void Game::switchTurn()
{
    currentTurn = (currentTurn == 'W') ? 'B' : 'W';

    string base = (currentTurn == 'W')
        ? "White's turn  —  click a piece to move"
        : "Black's turn  —  click a piece to move";

    if (board.isInCheck(currentTurn))
        base += "   (CHECK!)";

    statusMsg = base;
}

// ─────────────────────────────────────────
// Check if game is over
// ─────────────────────────────────────────
bool Game::isGameOver()
{
    if (!board.isKingAlive('W'))
    {
        statusMsg = "  BLACK WINS!  White king was captured.";
        return true;
    }
    if (!board.isKingAlive('B'))
    {
        statusMsg = "  WHITE WINS!  Black king was captured.";
        return true;
    }

    // currentTurn is the player about to move (after switchTurn)
    if (board.isCheckmate(currentTurn))
    {
        statusMsg = (currentTurn == 'W')
            ? "  CHECKMATE!  BLACK WINS!"
            : "  CHECKMATE!  WHITE WINS!";
        return true;
    }

    return false;
}

// ─────────────────────────────────────────
// Convert mouse pixel position to board row/col
// ─────────────────────────────────────────
bool Game::pixelToBoard(int px, int py, int& row, int& col)
{
    float bx = (px - OFFSET) / TILE;
    float by = (py - OFFSET) / TILE;

    if (bx < 0 || bx >= 8 || by < 0 || by >= 8)
        return false;

    col = (int)bx;
    row = (int)by;
    return true;
}

// ─────────────────────────────────────────
// Draw status bar at the bottom of the window
// ─────────────────────────────────────────
void Game::drawStatus(sf::Font& font)
{
    sf::RectangleShape bar(sf::Vector2f(720.f, 50.f));
    bar.setPosition(sf::Vector2f(0.f, 710.f));
    bar.setFillColor(sf::Color(30, 30, 30));
    window.draw(bar);

    sf::Text msg(font, statusMsg, 16);
    msg.setPosition(sf::Vector2f(12.f, 720.f));
    msg.setFillColor(currentTurn == 'W'
        ? sf::Color(255, 220, 100)   // gold for white's turn
        : sf::Color(100, 200, 255)); // blue for black's turn
    window.draw(msg);
}

// ─────────────────────────────────────────
// Main game loop
// ─────────────────────────────────────────
void Game::start()
{
    sf::Font font;
    bool fontLoaded = font.openFromFile("C:/Windows/Fonts/arial.ttf");

    while (window.isOpen())
    {
        // ── Event loop ───────────────────────────────────
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Keep board centered and undistorted on resize/maximize
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                float windowW = static_cast<float>(resized->size.x);
                float windowH = static_cast<float>(resized->size.y);

                const float boardW = 720.f;
                const float boardH = 760.f;

                float scale = std::min(windowW / boardW, windowH / boardH);
                float viewW = boardW * scale;
                float viewH = boardH * scale;

                sf::View view(sf::FloatRect({ 0.f, 0.f }, { boardW, boardH }));
                view.setViewport(sf::FloatRect(
                    { (1.f - viewW / windowW) / 2.f, (1.f - viewH / windowH) / 2.f },
                    { viewW / windowW, viewH / windowH }
                ));
                window.setView(view);
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button != sf::Mouse::Button::Left)
                    continue;

                sf::Vector2f worldPos = window.mapPixelToCoords(
                    { click->position.x, click->position.y });

                int clickRow, clickCol;
                if (!pixelToBoard((int)worldPos.x, (int)worldPos.y,
                    clickRow, clickCol))
                    continue;   // clicked outside the board

                if (!pieceSelected)
                {
                    // First click: select a piece
                    Piece* p = board.getPiece(clickRow, clickCol);
                    if (p != nullptr && p->getcolor() == currentTurn)
                    {
                        selectedRow = clickRow;
                        selectedCol = clickCol;
                        pieceSelected = true;
                        statusMsg = "Piece selected  —  click destination square";
                    }
                    else
                    {
                        statusMsg = "No valid piece there. Try again.";
                    }
                }
                else
                {
                    // Second click: attempt the move
                    if (clickRow == selectedRow && clickCol == selectedCol)
                    {
                        // Same square clicked again — deselect
                        pieceSelected = false;
                        statusMsg = (currentTurn == 'W')
                            ? "White's turn  —  click a piece to move"
                            : "Black's turn  —  click a piece to move";
                    }
                    else
                    {
                        bool ok = board.movePiece(selectedRow, selectedCol,
                            clickRow, clickCol,
                            currentTurn);
                        pieceSelected = false;

                        if (ok)
                        {
                            switchTurn();

                            if (isGameOver())
                            {
                                // Show final position for 4 seconds then close
                                window.clear(sf::Color(20, 20, 20));
                                board.drawSFML(window, -1, -1, false);
                                if (fontLoaded) drawStatus(font);
                                window.display();
                                sf::sleep(sf::seconds(4));
                                window.close();
                            }
                        }
                        else
                        {
                            statusMsg = "Invalid move!  Try another square.";
                        }
                    }
                }
            }
        }

        // ── Render ───────────────────────────────────────
        window.clear(sf::Color(20, 20, 20));
        board.drawSFML(window, selectedRow, selectedCol, pieceSelected);
        if (fontLoaded) drawStatus(font);
        window.display();
    }
}