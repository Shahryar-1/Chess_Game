#pragma once
#include<iostream>
using namespace std;
//Base class of Piece from this every other Piece is drieved
class Piece {
	char color; //Colour of the piece white or black
	int x, y;	//position of the piece at the board
public:
	Piece(char color, int x, int y);	//initializes the colour of the piece and the default position
	char getcolor();					//getter function to get colour
	int getx();							//return current row position
	int gety();							//return current column position
	void setposition();					//updates the position every time a move is made

	//is a pure virtual function and will be implemented in all dereived peice classes like queen rook and kig etc
	virtual bool isvalidmove(int toX, int toY, Piece* board[8][8]) = 0;// return true or false and tells that if the move made made was valid or not

	virtual char getsymbol() = 0;
	virtual ~Piece();	//virtual destructor
};


//simple pawn piece class inherited by Piece class implementing allt he virtual functions
class Pawn :public Piece {
	Pawn(char color, int x, int y);	//pawn class constructor which take values and arguments adn runs the Piece class constructor
	bool isvalidmove(int toX, int toY, Piece* board[8][8]);	//checks if the pawn moved was valid or not
	//like can take 1 or 2 steps at first /after the first step only step forward
	//or if want to capture can move diagonal
	char setsymbol();		//returns teh colour of the moved pawn
};


//Rook class inherited from Base Piece class
class Rook :public Piece {
	Rook(char color, int x, int y); //takes the colour and the default position for the rook
	bool isvalidmove(int toX, int toY, Piece* board[8][8]);	//checks if the move is valid or not 
	//can go updown left or right
	char setsymbol();
};


//Knight class inherited from Base Piece class
class Bishop :public Piece {
	Bishop(char color, int x, int y);	//takes the colour and the default position
	bool isvalidmove(int toX, int toY, Piece* board[8][8]);	//checks if the move is valid or not
	//can move in  shape 2 boxes in one direction and then one in perpendicular direction
	char setsymbol();
};

class Knight :public Piece {
	Knight(char color, int x, int y);	//takes the colour and the default position
	bool isvalidmove(int toX, int toY, Piece* board[8][8]);//can only move in diagonal
	char setsymbol();
};
class Queen :public Piece {
	Queen(char color, int x, int y);	//takes the colour and the default position
	bool isvalidmove(int toX, int toY, Piece* board[8][8]);
	//can move in any direction diagonal straight but cannot copy the movement of knight
	char setsymbol();
};

class King :public Piece {
	King(char color, int x, int y);	//takes the colour and the default position
	bool isvalidmove(int toX, int toY, Piece* board[8][8]);	//can only take one step no more than one step 
	//can take step diagonal and straight
	char setsymbol();
};
//NOTE no piece of different class but same color can the take the piece of that colour


class ChessBoard {
	Piece* grid[8][8];// 8x8 array showing that chess columns and rows of 8 each
	//ie index[0][0] is top left corner the default position for a rook
	ChessBoard();    // allocates the rowns and colums for allt he 32 pieces
	~ChessBoard();   

	//prints 8x8 chess board onto the console
	void display();  



	// returns pointer to piece at position (x, y)
	// returns nullptr if square is empty
	// used by isValidMove to check if path is blocked
	Piece* getPiece(int x, int y);  


	//cals function is valid return true if move is valid or not
	//updates the positions of the pieces and marks null ptr for each empty box||index 
	bool movePiece(int fromX, int fromY, int toX, int toY); 


	//loops through the chess board and finds the king of the given colour
	// used by Game to check if the game is over
	bool isKingAlive(char color);
};


//actual game running classs adn controls the whole game

class Game {
private:
	ChessBoard board;  

	//tells which colour move is going 
	//starts from white and switches afetr every moved
	char currentTurn;  

public:
	Game();            // initializes currentTurn to WHITE


	// main game loop  keeps running until game over function returns true
	// each iteration: displays board, asks player for input, calls movePiece
	void start();      

	//switches the turns after every move and will end when game over function return true
	void switchTurn(); 

	//checks if the game has ended and checks for the conditions of the game over like king captured and 
	bool isGameOver(); 
};