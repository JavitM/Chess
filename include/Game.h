#pragma once
#include "SDL_Handler.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

enum Side {
    NOSIDE, BlackLeftPawn, BlackRightPawn, WhiteLeftPawn, WhiteRightPawn, TopX, BottomX, TopY, BottomY,
    LeftTopDiagonal, LeftBotomDiagonal, RightTopDiagonal, RightBottomDiagonal, A, B, C, D, E, F, G, H, K1, K2, K3, K4, K5, K6, K7, K8
};

struct CheckIfData
{
    int checkcount;
    Team t;
    bool DoubleCheck;
    Side checkside;
};

class Game
{
public:
	// Constructor
	Game(SDL_Handler* handler);

	// Destructor
	~Game();

	//Moves a piece
	void move(Piece* piece, Position pos);

    // return position of piece on board
    Piece* getFieldPos(int row, int col);

    CheckIfData CheckIfItsCheck(Piece* King);

    void CalculatePossibleMoves(bool bByTurn);

	// handler
	SDL_Handler* m_handler;

	// 2D Field array, every Position has got a PIece::Team and a piece
    Piece* m_field[8][8];

    // turn
    Team m_turn;

    // returns m_turn
    Team getTurn() { return m_turn; };

    bool m_checkEnPassant;

    CheckIfData blackkingcheckdata;
    CheckIfData whitekingcheckdata;
        
    // every single piece
    Pawn* pl1;
    Pawn* pl2;
    Pawn* pl3;
    Pawn* pl4;
    Pawn* pl5;
    Pawn* pl6;
    Pawn* pl7;
    Pawn* pl8;
    Pawn* pb1;
    Pawn* pb2;
    Pawn* pb3;
    Pawn* pb4;
    Pawn* pb5;
    Pawn* pb6;
    Pawn* pb7;
    Pawn* pb8;
    Rook* rb1;
    Rook* rb2;
    Rook* rl1;
    Rook* rl2;
    Knight* nb1;
    Knight* nb2;
    Knight* nl1;
    Knight* nl2;
    Bishop* bb1;
    Bishop* bb2;
    Bishop* bl1;
    Bishop* bl2;
    King* kb1;
    King* kl1;
    Queen* qb1;
    Queen* ql1;
};