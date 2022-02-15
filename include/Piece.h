#pragma once
#include <vector>
#include "SDL_Handler.h"
enum Team { BLACK, WHITE, NONE };

enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, KING, QUEEN, EMPTY };

enum MoveType { NORMAL, LONGCASTLE, SHORTCASTLE, ENPASSANT, NEWPIECE, INIT, DOUBLEMOVE };

struct Position
{
	int X, Y = 0;

	Position()
	{

	}

	Position(int x, int y)
		: X(x), Y(y)
	{

	}
};

struct Movement
{

	Movement(Position p, MoveType t)
		: position(p),movetype(t)
	{

	}
	Position position;
	MoveType movetype;
};

struct MoveStatement
{
	bool bCanMove = false;
	MoveType movetype;
	Position movepos;
};

class Piece
{

public:

	Piece();

	Piece(Team team, Position p, SDL_Handler* handler, PieceType type)
	{
		m_team = team;
		m_Position = p;
		m_handler = handler;
		m_type = type;
	}

	~Piece();

	virtual void SetPossibleMoves(class Game* game, struct CheckIfData& kingdata);

	std::vector<Movement>& GetPossibleMoves() { return PossibleMoves; }

	Team GetTeam() { return m_team; }

	SDL_Texture* GetTexture() { return m_texture; }

	SDL_Handler* GetHandler() { return m_handler; }

	Position GetPosition() { return m_Position; }

	PieceType GetPieceType() { return m_type; }

	Piece* GetOwningKing(Piece* Field[8][8]);

	void SetPosition(int X, int Y) { m_Position.X = X; m_Position.Y = Y; }

	void Render();

	MoveStatement Move(Position pos, Team check);

	virtual void NormalMove(Movement m);

	std::vector<Movement> PossibleMoves;

	bool firstmove = true;
protected:

	// actual position of piece on board
	Position m_Position;

	// texture of this piece
	SDL_Texture* m_texture = nullptr;

	// SDL Handler
	SDL_Handler* m_handler = nullptr;

	// Team this piece plays for
	Team m_team;

	// The Type of Piece
	PieceType m_type;

	// possible move list of piece

};