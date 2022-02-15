#pragma once
#include "Piece.h"
class King :
	public Piece
{
public:
	King(Team team, Position p, SDL_Handler* handler, PieceType type);

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata);

	std::vector<Position> GetPosesBetweenCheck(enum Side side,class Game* game);
};

