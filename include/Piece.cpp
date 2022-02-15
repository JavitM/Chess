#include "Piece.h"
#include "Game.h"

Piece::Piece()
{
	printf("piece constructor\n");
}

Piece::~Piece()
{
	SDL_DestroyTexture(m_texture);
	//delete m_texture;
}

void Piece::SetPossibleMoves(Game* game, struct CheckIfData& kingdata)
{
}

Piece* Piece::GetOwningKing(Piece* Field[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Field[i][j] != nullptr)
			{
				Piece* piece = Field[i][j];
				if (piece->GetPieceType() == PieceType::KING && piece->GetTeam() == m_team)
				{
					return piece;
				}
			}
			
		}
	}
}

void Piece::Render()
{
	SDL_Rect src = { 0, 0, 500, 500 };
	if (m_handler != nullptr)
	{
		SDL_Rect dest = { m_handler->SCREEN_WIDTH / 8 * m_Position.X - 2,
				  m_handler->SCREEN_HEIGHT / 8 * m_Position.Y,
				  m_handler->SCREEN_WIDTH / 8,
				  m_handler->SCREEN_HEIGHT / 8 };
		m_handler->DrawRectangle(src, dest, m_texture);
	}
}

MoveStatement Piece::Move(Position pos, Team check)
{
	MoveStatement statement;
	for (int i = 0; i < PossibleMoves.size(); i++)
	{
 		if (PossibleMoves[i].position.X == pos.X && PossibleMoves[i].position.Y == pos.Y)
		{
			if (firstmove)
			{
				firstmove = false;
			}

			if (m_type == PieceType::PAWN)
			{
				if (pos.Y == 0 || pos.Y == 7)
				{
					Pawn* p = (Pawn*)this;
					p->bCanExchange = true;
				}
			}
			statement.movepos = Position(PossibleMoves[i].position.X, PossibleMoves[i].position.Y);
			statement.movetype = PossibleMoves[i].movetype;
			statement.bCanMove = true;
			return statement;
		}
	}
	statement.bCanMove = false;
	return statement;
}

void Piece::NormalMove(Movement m)
{
}


