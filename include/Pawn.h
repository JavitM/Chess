#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Team team, Position p, SDL_Handler* handler, PieceType type);

	bool CanExchange() { return bCanExchange; }
	Position GetEnpassantPos(int i) { return EnpassantPos[i]; }

	void SetCanExchange(bool b) { bCanExchange = b; }
	void SetEnpassantPossibility(int i) { EnpassantPossibility = i; }
		 
	void EnPassant(class Game* game);

private:

	Position doublemove;

	bool bCanExchange = false;

	int EnpassantPossibility = -1;
	Position EnpassantPos[2];

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata) override;

	virtual void NormalMove(Movement m) override;

	friend class Piece;
};

