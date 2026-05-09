#pragma once
#include "king.h"

King::King(char color, int x, int y) :Piece(color, x, y) {}


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