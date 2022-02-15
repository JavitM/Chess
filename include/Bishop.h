#pragma once
#include "Piece.h"
class Bishop :
	public Piece
{
public:
	Bishop(Team team, Position p, SDL_Handler* handler, PieceType type);

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata) override;
};

