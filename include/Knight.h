#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
	Knight(Team team, Position p, SDL_Handler* handler, PieceType type);

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata) override;
};

