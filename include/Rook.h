#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
public:
	Rook(Team team, Position p, SDL_Handler* handler, PieceType type);

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata) override;
};

