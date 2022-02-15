#include "Knight.h"
#include "Game.h"
#include "King.h"
#include <iostream>

Knight::Knight(Team team, Position p, SDL_Handler* handler, PieceType type)
{
	m_team = team;
	m_Position = p;
	m_handler = handler;
	m_type = type;

	std::string filename;
	if (team == BLACK)
	{
		filename = "icons/black_knight.png";
	}
	else
	{
		filename = "icons/white_knight.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);


	Render();
}

void Knight::SetPossibleMoves(Game* game, CheckIfData& kingdata)
{
	std::vector<Movement> moves;
	Position KnightPos = GetPosition();

	// Top Left Knight Coordinate
	if (KnightPos.X - 1 >= 0 && KnightPos.Y - 2 >= 0)
	{
		if (game->m_field[KnightPos.X - 1][KnightPos.Y - 2] != nullptr)
		{
			if (game->m_field[KnightPos.X - 1][KnightPos.Y - 2]->GetTeam() == m_team)
			{
				goto topright;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X - 1][KnightPos.Y - 2];
				game->m_field[KnightPos.X - 1][KnightPos.Y - 2] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X - 1, KnightPos.Y - 2), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 1][KnightPos.Y - 2];
				game->m_field[KnightPos.X - 1][KnightPos.Y - 2] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X - 1][KnightPos.Y - 2] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X - 1, KnightPos.Y - 2), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 1][KnightPos.Y - 2];
			game->m_field[KnightPos.X - 1][KnightPos.Y - 2] = nullptr;
		}
	}

	// Top Right Knight Coordinate
    topright:if (KnightPos.X + 1 < 8 && KnightPos.Y - 2 >= 0)
    {
		if (game->m_field[KnightPos.X + 1][KnightPos.Y - 2] != nullptr)
		{
			if (game->m_field[KnightPos.X + 1][KnightPos.Y - 2]->GetTeam() == m_team)
			{
				goto lefttop;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X + 1][KnightPos.Y - 2];
				game->m_field[KnightPos.X + 1][KnightPos.Y - 2] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X + 1, KnightPos.Y - 2), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 1][KnightPos.Y - 2];
				game->m_field[KnightPos.X + 1][KnightPos.Y - 2] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X + 1][KnightPos.Y - 2] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X + 1, KnightPos.Y - 2), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 1][KnightPos.Y - 2];
			game->m_field[KnightPos.X + 1][KnightPos.Y - 2] = nullptr;
		}
    }

	// Left Top Knight Coordinate
    lefttop:if (KnightPos.X - 2 >= 0 && KnightPos.Y - 1 >= 0)
	{
		if (game->m_field[KnightPos.X - 2][KnightPos.Y - 1] != nullptr)
		{
			if (game->m_field[KnightPos.X - 2][KnightPos.Y - 1]->GetTeam() == m_team)
			{
				goto righttop;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X - 2][KnightPos.Y - 1];
				game->m_field[KnightPos.X - 2][KnightPos.Y - 1] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X - 2, KnightPos.Y - 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 2][KnightPos.Y - 1];
				game->m_field[KnightPos.X - 2][KnightPos.Y - 1] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X - 2][KnightPos.Y - 1] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X - 2, KnightPos.Y - 1), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 2][KnightPos.Y - 1];
			game->m_field[KnightPos.X - 2][KnightPos.Y - 1] = nullptr;
		}
	}

	// Right Top Knight Coordinate
    righttop:if (KnightPos.X + 2 < 8 && KnightPos.Y - 1 >= 0)
    {
		if (game->m_field[KnightPos.X + 2][KnightPos.Y - 1] != nullptr)
		{
			if (game->m_field[KnightPos.X + 2][KnightPos.Y - 1]->GetTeam() == m_team)
			{
				goto leftbottom;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X + 2][KnightPos.Y - 1];
				game->m_field[KnightPos.X + 2][KnightPos.Y - 1] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X + 2, KnightPos.Y - 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 2][KnightPos.Y - 1];
				game->m_field[KnightPos.X + 2][KnightPos.Y - 1] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X + 2][KnightPos.Y - 1] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X + 2, KnightPos.Y - 1), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 2][KnightPos.Y - 1];
			game->m_field[KnightPos.X + 2][KnightPos.Y - 1] = nullptr;
		}
	}

	// Left Bottom Knight Coordinate
	leftbottom:if (KnightPos.X - 2 >= 0 && KnightPos.Y + 1 < 8)
	{
		if (game->m_field[KnightPos.X - 2][KnightPos.Y + 1] != nullptr)
		{
			if (game->m_field[KnightPos.X - 2][KnightPos.Y + 1]->GetTeam() == m_team)
			{
				goto rightbottom;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X - 2][KnightPos.Y + 1];
				game->m_field[KnightPos.X - 2][KnightPos.Y + 1] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X - 2, KnightPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 2][KnightPos.Y + 1];
				game->m_field[KnightPos.X - 2][KnightPos.Y + 1] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X - 2][KnightPos.Y + 1] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X - 2, KnightPos.Y + 1), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 2][KnightPos.Y + 1];
			game->m_field[KnightPos.X - 2][KnightPos.Y + 1] = nullptr;
		}
	}

	// Right Bottom Knight Coordinate
    rightbottom:if (KnightPos.X + 2 < 8 && KnightPos.Y + 1 < 8)
    {
		if (game->m_field[KnightPos.X + 2][KnightPos.Y + 1] != nullptr)
		{
			if (game->m_field[KnightPos.X + 2][KnightPos.Y + 1]->GetTeam() == m_team)
			{
				goto bottomleft;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X + 2][KnightPos.Y + 1];
				game->m_field[KnightPos.X + 2][KnightPos.Y + 1] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X + 2, KnightPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 2][KnightPos.Y + 1];
				game->m_field[KnightPos.X + 2][KnightPos.Y + 1] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X + 2][KnightPos.Y + 1] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X + 2, KnightPos.Y + 1), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 2][KnightPos.Y + 1];
			game->m_field[KnightPos.X + 2][KnightPos.Y + 1] = nullptr;
		}
    }

	// Bottom Left Knight Coordinate
    bottomleft:if (KnightPos.X - 1 >= 0 && KnightPos.Y + 2 < 8)
	{
		if (game->m_field[KnightPos.X - 1][KnightPos.Y + 2] != nullptr)
		{
			if (game->m_field[KnightPos.X - 1][KnightPos.Y + 2]->GetTeam() == m_team)
			{
				goto bottomright;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X - 1][KnightPos.Y + 2];
				game->m_field[KnightPos.X - 1][KnightPos.Y + 2] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X - 1, KnightPos.Y + 2), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 1][KnightPos.Y + 2];
				game->m_field[KnightPos.X - 1][KnightPos.Y + 2] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X - 1][KnightPos.Y + 2] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X - 1, KnightPos.Y + 2), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X - 1][KnightPos.Y + 2];
			game->m_field[KnightPos.X - 1][KnightPos.Y + 2] = nullptr;
		}
	}

	// Bottom Right Knight Coordinate
	bottomright:if (KnightPos.X + 1 < 8 && KnightPos.Y + 2 < 8)
	{
		if (game->m_field[KnightPos.X + 1][KnightPos.Y + 2] != nullptr)
		{
			if (game->m_field[KnightPos.X + 1][KnightPos.Y + 2]->GetTeam() == m_team)
			{
				goto end;
			}
			else
			{
				Piece* temp = game->m_field[KnightPos.X + 1][KnightPos.Y + 2];
				game->m_field[KnightPos.X + 1][KnightPos.Y + 2] = game->m_field[KnightPos.X][KnightPos.Y];
				game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KnightPos.X + 1, KnightPos.Y + 2), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 1][KnightPos.Y + 2];
				game->m_field[KnightPos.X + 1][KnightPos.Y + 2] = temp;
			}
		}
		else
		{
			game->m_field[KnightPos.X + 1][KnightPos.Y + 2] = game->m_field[KnightPos.X][KnightPos.Y];
			game->m_field[KnightPos.X][KnightPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KnightPos.X + 1, KnightPos.Y + 2), MoveType::INIT);
				moves.push_back(m);
			}

			game->m_field[KnightPos.X][KnightPos.Y] = game->m_field[KnightPos.X + 1][KnightPos.Y + 2];
			game->m_field[KnightPos.X + 1][KnightPos.Y + 2] = nullptr;
		}
	}

	end:{}

	PossibleMoves = moves;
}
