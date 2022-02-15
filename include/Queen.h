#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
	Queen(Team team, Position p, SDL_Handler* handler, PieceType type);

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata) override;
};

