#include "King.h"
#include "Game.h"
King::King(Team team, Position p, SDL_Handler* handler, PieceType type)
{
	m_team = team;
	m_Position = p;
	m_handler = handler;
	m_type = type;

	std::string filename;
	if (team == BLACK)
	{
		filename = "icons/black_king.png";
	}
	else
	{
		filename = "icons/white_king.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);


	Render();
}

void King::SetPossibleMoves(Game* game, struct CheckIfData& kingdata)
{
	std::vector<Movement> moves;
	Position KingPos = GetPosition();
	
	// Y - 1 Coordinate
	if (KingPos.Y - 1 >= 0)
	{
		if (game->m_field[KingPos.X][KingPos.Y - 1] == nullptr)
		{
			game->m_field[KingPos.X][KingPos.Y - 1] = this;
			this->m_Position.Y = KingPos.Y - 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X, KingPos.Y - 1), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X][KingPos.Y - 1];
			this->m_Position.Y = KingPos.Y;
			game->m_field[KingPos.X][KingPos.Y - 1] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X][KingPos.Y - 1]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X][KingPos.Y - 1];
				game->m_field[KingPos.X][KingPos.Y - 1] = this;
				this->m_Position.Y = KingPos.Y - 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X, KingPos.Y - 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X][KingPos.Y - 1];
				this->m_Position.Y = KingPos.Y;
				game->m_field[KingPos.X][KingPos.Y - 1] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	// Y + 1 Coordinate
	if (KingPos.Y + 1 < 8)
	{
		if (game->m_field[KingPos.X][KingPos.Y + 1] == nullptr)
		{
			game->m_field[KingPos.X][KingPos.Y + 1] = this;
			this->m_Position.Y = KingPos.Y + 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X, KingPos.Y + 1), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X][KingPos.Y + 1];
			this->m_Position.Y = KingPos.Y;
			game->m_field[KingPos.X][KingPos.Y + 1] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X][KingPos.Y + 1]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X][KingPos.Y + 1];
				game->m_field[KingPos.X][KingPos.Y + 1] = this;
				this->m_Position.Y = KingPos.Y + 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X, KingPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X][KingPos.Y + 1];
				this->m_Position.Y = KingPos.Y;
				game->m_field[KingPos.X][KingPos.Y + 1] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
    // X - 1 Coordinate
	if (KingPos.X - 1 >= 0)
	{
		if (game->m_field[KingPos.X - 1][KingPos.Y] == nullptr)
		{
			game->m_field[KingPos.X - 1][KingPos.Y] = this;
			this->m_Position.X = KingPos.X - 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X - 1, KingPos.Y), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X - 1][KingPos.Y];
			this->m_Position.X = KingPos.X;
			game->m_field[KingPos.X - 1][KingPos.Y] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X - 1][KingPos.Y]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X - 1][KingPos.Y];
				game->m_field[KingPos.X - 1][KingPos.Y] = this;
				this->m_Position.X = KingPos.X - 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X - 1, KingPos.Y), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X - 1][KingPos.Y];
				this->m_Position.X = KingPos.X;
				game->m_field[KingPos.X - 1][KingPos.Y] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
    // X + 1 Coordinate
	if (KingPos.X + 1 < 8)
	{
		if (game->m_field[KingPos.X + 1][KingPos.Y] == nullptr)
		{
			game->m_field[KingPos.X + 1][KingPos.Y] = this;
			this->m_Position.X = KingPos.X + 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X + 1, KingPos.Y), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X + 1][KingPos.Y];
			this->m_Position.X = KingPos.X;
			game->m_field[KingPos.X + 1][KingPos.Y] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X + 1][KingPos.Y]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X + 1][KingPos.Y];
				game->m_field[KingPos.X + 1][KingPos.Y] = this;
				this->m_Position.X = KingPos.X + 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X + 1, KingPos.Y), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X + 1][KingPos.Y];
				this->m_Position.X = KingPos.X;
				game->m_field[KingPos.X + 1][KingPos.Y] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
    // X - 1 && Y - 1 Coordinate
	if (KingPos.X - 1 >= 0 && KingPos.Y - 1 >= 0)
	{
		if (game->m_field[KingPos.X - 1][KingPos.Y - 1] == nullptr)
		{
			game->m_field[KingPos.X - 1][KingPos.Y - 1] = this;
			this->m_Position.X = KingPos.X - 1;
			this->m_Position.Y = KingPos.Y - 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X - 1, KingPos.Y - 1), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X - 1][KingPos.Y - 1];
			this->m_Position.X = KingPos.X;
			this->m_Position.Y = KingPos.Y;
			game->m_field[KingPos.X - 1][KingPos.Y - 1] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X - 1][KingPos.Y - 1]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X - 1][KingPos.Y - 1];
				game->m_field[KingPos.X - 1][KingPos.Y - 1] = this;
				this->m_Position.X = KingPos.X - 1;
				this->m_Position.Y = KingPos.Y - 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X - 1, KingPos.Y - 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X - 1][KingPos.Y - 1];
				this->m_Position.X = KingPos.X;
				this->m_Position.Y = KingPos.Y;
				game->m_field[KingPos.X - 1][KingPos.Y - 1] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
    // X + 1 && Y - 1 Coordinate
	if (KingPos.X + 1 < 8 && KingPos.Y - 1 >= 0)
	{
		if (game->m_field[KingPos.X + 1][KingPos.Y - 1] == nullptr)
		{
			game->m_field[KingPos.X + 1][KingPos.Y - 1] = this;
			this->m_Position.X = KingPos.X + 1;
			this->m_Position.Y = KingPos.Y - 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X + 1, KingPos.Y - 1), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X + 1][KingPos.Y - 1];
			this->m_Position.X = KingPos.X;
			this->m_Position.Y = KingPos.Y;
			game->m_field[KingPos.X + 1][KingPos.Y - 1] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X + 1][KingPos.Y - 1]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X + 1][KingPos.Y - 1];
				game->m_field[KingPos.X + 1][KingPos.Y - 1] = this;
				this->m_Position.X = KingPos.X + 1;
				this->m_Position.Y = KingPos.Y - 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X + 1, KingPos.Y - 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X + 1][KingPos.Y - 1];
				this->m_Position.X = KingPos.X;
				this->m_Position.Y = KingPos.Y;
				game->m_field[KingPos.X + 1][KingPos.Y - 1] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
    // X - 1 && Y + 1 Coordinate
	if (KingPos.X - 1 >= 0 && KingPos.Y + 1 < 8)
	{
		if (game->m_field[KingPos.X - 1][KingPos.Y + 1] == nullptr)
		{
			game->m_field[KingPos.X - 1][KingPos.Y + 1] = this;
			this->m_Position.X = KingPos.X - 1;
			this->m_Position.Y = KingPos.Y + 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X - 1, KingPos.Y + 1), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X - 1][KingPos.Y + 1];
			this->m_Position.X = KingPos.X;
			this->m_Position.Y = KingPos.Y;
			game->m_field[KingPos.X - 1][KingPos.Y + 1] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X - 1][KingPos.Y + 1]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X - 1][KingPos.Y + 1];
				game->m_field[KingPos.X - 1][KingPos.Y + 1] = this;
				this->m_Position.X = KingPos.X - 1;
				this->m_Position.Y = KingPos.Y + 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X - 1, KingPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X - 1][KingPos.Y + 1];
				this->m_Position.X = KingPos.X;
				this->m_Position.Y = KingPos.Y;
				game->m_field[KingPos.X - 1][KingPos.Y + 1] = temp;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
    // X + 1 && Y + 1 Coordinate
	if (KingPos.X + 1 < 8 && KingPos.Y + 1 < 8)
	{
		if (game->m_field[KingPos.X + 1][KingPos.Y + 1] == nullptr)
		{
			game->m_field[KingPos.X + 1][KingPos.Y + 1] = this;
			this->m_Position.X = KingPos.X + 1;
			this->m_Position.Y = KingPos.Y + 1;
			game->m_field[KingPos.X][KingPos.Y] = nullptr;
			Team t = game->CheckIfItsCheck(this).t;
			if (t == Team::NONE)
			{
				Movement m = Movement(Position(KingPos.X + 1, KingPos.Y + 1), MoveType::NORMAL);
				moves.push_back(m);
			}

			game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X + 1][KingPos.Y + 1];
			this->m_Position.X = KingPos.X;
			this->m_Position.Y = KingPos.Y;
			game->m_field[KingPos.X + 1][KingPos.Y + 1] = nullptr;
		}
		else
		{
			if (game->m_field[KingPos.X + 1][KingPos.Y + 1]->GetTeam() != m_team)
			{
				Piece* temp = game->m_field[KingPos.X + 1][KingPos.Y + 1];
				game->m_field[KingPos.X + 1][KingPos.Y + 1] = this;
				this->m_Position.X = KingPos.X + 1;
				this->m_Position.Y = KingPos.Y + 1;
				game->m_field[KingPos.X][KingPos.Y] = nullptr;
				Team t = game->CheckIfItsCheck(this).t;
				if (t == Team::NONE)
				{
					Movement m = Movement(Position(KingPos.X + 1, KingPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}

				game->m_field[KingPos.X][KingPos.Y] = game->m_field[KingPos.X + 1][KingPos.Y + 1];
				this->m_Position.X = KingPos.X;
				this->m_Position.Y = KingPos.Y;
				game->m_field[KingPos.X + 1][KingPos.Y + 1] = temp;
			}
		}
	}

	// LONG CASTLE
	if (firstmove)
	{
		if (m_team == Team::BLACK)
		{
			if (!game->m_field[2][7] && !game->m_field[1][7] && game->m_field[0][7])
			{
				if (game->m_field[0][7]->GetPieceType() == PieceType::ROOK && game->m_field[0][7]->GetTeam() == m_team)
				{
					Piece* king = game->m_field[3][7];
					Piece* rook = game->m_field[0][7];
					game->m_field[1][7] = game->m_field[3][7];
					game->m_field[2][7] = game->m_field[0][7];
					game->m_field[1][7]->SetPosition(1, 7);
					game->m_field[3][7] = nullptr;
					game->m_field[0][7] = nullptr;

					Team t = game->CheckIfItsCheck(this).t;
					if (t == Team::NONE)
					{
						Movement m = Movement(Position(KingPos.X - 2, KingPos.Y), MoveType::SHORTCASTLE);
						moves.push_back(m);
					}

					game->m_field[3][7] = king;
					game->m_field[3][7]->SetPosition(3, 7);
					game->m_field[0][7] = rook;
					game->m_field[1][7] = nullptr;
					game->m_field[2][7] = nullptr;
				}
			}

			if (!game->m_field[4][7] && !game->m_field[5][7] && !game->m_field[6][7] && game->m_field[7][7])
			{
				if (game->m_field[7][7]->GetPieceType() == PieceType::ROOK && game->m_field[7][7]->GetTeam() == m_team)
				{
					Piece* king = game->m_field[3][7];
					Piece* rook = game->m_field[7][7];
					game->m_field[5][7] = game->m_field[3][7];
					game->m_field[4][7] = game->m_field[7][7];
					game->m_field[5][7]->SetPosition(5, 7);
					game->m_field[3][7] = nullptr;
					game->m_field[7][7] = nullptr;

					Team t = game->CheckIfItsCheck(this).t;
					if (t == Team::NONE)
					{
						Movement m = Movement(Position(KingPos.X + 2, KingPos.Y), MoveType::LONGCASTLE);
						moves.push_back(m);
					}

					game->m_field[3][7] = king;
					game->m_field[3][7]->SetPosition(3, 7);
					game->m_field[7][7] = rook;
					game->m_field[4][7] = nullptr;
					game->m_field[5][7] = nullptr;
				}
			}
		}
		else
		{
			if (!game->m_field[2][0] && !game->m_field[1][0] && game->m_field[0][0])
			{
				if (game->m_field[0][0]->GetPieceType() == PieceType::ROOK && game->m_field[0][0]->GetTeam() == m_team)
				{
					Piece* king = game->m_field[3][0];
					Piece* rook = game->m_field[0][0];
					game->m_field[1][0] = game->m_field[3][0];
					game->m_field[2][0] = game->m_field[0][0];
					game->m_field[1][0]->SetPosition(1, 0);
					game->m_field[3][0] = nullptr;
					game->m_field[0][0] = nullptr;

					Team t = game->CheckIfItsCheck(this).t;
					if (t == Team::NONE)
					{
						Movement m = Movement(Position(KingPos.X - 2, KingPos.Y), MoveType::SHORTCASTLE);
						moves.push_back(m);
					}

					game->m_field[3][0] = king;
					game->m_field[3][0]->SetPosition(3, 0);
					game->m_field[0][0] = rook;
					game->m_field[1][0] = nullptr;
					game->m_field[2][0] = nullptr;
				}
			}

			if (!game->m_field[4][0] && !game->m_field[5][0] && !game->m_field[6][0] && game->m_field[7][0])
			{
				if (game->m_field[7][0]->GetPieceType() == PieceType::ROOK && game->m_field[7][0]->GetTeam() == m_team)
				{
					Piece* king = game->m_field[3][0];
					Piece* rook = game->m_field[7][0];
					game->m_field[5][0] = game->m_field[3][0];
					game->m_field[4][0] = game->m_field[7][0];
					game->m_field[5][0]->SetPosition(5, 0);
					game->m_field[3][0] = nullptr;
					game->m_field[7][0] = nullptr;

					Team t = game->CheckIfItsCheck(this).t;
					if (t == Team::NONE)
					{
						Movement m = Movement(Position(KingPos.X + 2, KingPos.Y), MoveType::LONGCASTLE);
						moves.push_back(m);
					}

					game->m_field[3][0] = king;
					game->m_field[3][0]->SetPosition(3, 0);
					game->m_field[7][0] = rook;
					game->m_field[4][0] = nullptr;
					game->m_field[5][0] = nullptr;
				}
			}
		}
	}

	PossibleMoves = moves;
}

std::vector<Position> King::GetPosesBetweenCheck(enum Side side, class Game* game)
{
	std::vector<Position> pos;
	Position Coordinate = this->GetPosition();
	if (side == Side::BlackLeftPawn) { pos.push_back(Position(Coordinate.X - 1, Coordinate.Y - 1)); return pos; }
	if (side == Side::BlackRightPawn) { pos.push_back(Position(Coordinate.X + 1, Coordinate.Y - 1)); return pos; }
	if (side == Side::WhiteLeftPawn) { pos.push_back(Position(Coordinate.X - 1, Coordinate.Y + 1)); return pos; }
	if (side == Side::WhiteRightPawn) { pos.push_back(Position(Coordinate.X + 1, Coordinate.Y + 1)); return pos; }
	if (side == Side::A) { pos.push_back(Position(Coordinate.X - 1, Coordinate.Y - 2)); return pos; }
	if (side == Side::B) { pos.push_back(Position(Coordinate.X + 1, Coordinate.Y - 2)); return pos; }
	if (side == Side::C) { pos.push_back(Position(Coordinate.X - 2, Coordinate.Y - 1)); return pos; }
	if (side == Side::D) { pos.push_back(Position(Coordinate.X + 2, Coordinate.Y - 1)); return pos; }
	if (side == Side::E) { pos.push_back(Position(Coordinate.X - 2, Coordinate.Y + 1)); return pos; }
	if (side == Side::F) { pos.push_back(Position(Coordinate.X + 2, Coordinate.Y + 1)); return pos; }
	if (side == Side::G) { pos.push_back(Position(Coordinate.X - 1, Coordinate.Y + 2)); return pos; }
	if (side == Side::H) { pos.push_back(Position(Coordinate.X + 1, Coordinate.Y + 2)); return pos; }

	if (side == Side::TopY)
	{
		for (int Y = Coordinate.Y + 1; Y < 8; Y++)
		{
			Piece* piece = game->getFieldPos(Coordinate.X, Y);
			if (piece != nullptr)
			{
				if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::ROOK)
				{
					pos.push_back(Position(Coordinate.X, Y));
					return pos;
					// the last position in array is eating the piece that made check we will control this in setposition
				}
			}
			pos.push_back(Position(Coordinate.X, Y));
		}
	}
	if (side == Side::BottomY)
	{
		for (int Y = Coordinate.Y - 1; Y >= 0; Y--)
		{
			Piece* piece = game->getFieldPos(Coordinate.X, Y);
			if (piece != nullptr)
			{
				if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::ROOK)
				{
					pos.push_back(Position(Coordinate.X, Y));
					return pos;
					// the last position in array is eating the piece that made check we will control this in setposition
				}
			}
			pos.push_back(Position(Coordinate.X, Y));
		}
	}
	if (side == Side::TopX)
	{
		for (int X = Coordinate.X + 1; X < 8; X++)
		{
			Piece* piece = game->getFieldPos(X, Coordinate.Y);
			if (piece != nullptr)
			{
				if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::ROOK)
				{
					pos.push_back(Position(X, Coordinate.Y));
					return pos;
					// the last position in array is eating the piece that made check we will control this in setposition
				}
			}
			pos.push_back(Position(X, Coordinate.Y));
		}
	}
	if (side == Side::BottomX)
	{
		for (int X = Coordinate.X - 1; X >= 0; X--)
		{
			Piece* piece = game->getFieldPos(X, Coordinate.Y);
			if (piece != nullptr)
			{
				if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::ROOK)
				{
					pos.push_back(Position(X, Coordinate.Y));
					return pos;
					// the last position in array is eating the piece that made check we will control this in setposition
				}
			}
			pos.push_back(Position(X, Coordinate.Y));
		}
	}
	if (side == Side::RightBottomDiagonal)
	{
		for (int X = Coordinate.X + 1; X < 8; X++)
		{
			int DistanceBetweenKing = X - Coordinate.X;

			if (Coordinate.Y + DistanceBetweenKing < 8 && Coordinate.Y + DistanceBetweenKing >= 0)
			{
				Piece* piece = game->getFieldPos(X, Coordinate.Y + DistanceBetweenKing);
				if (piece != nullptr)
				{
					if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::BISHOP)
					{
						pos.push_back(Position(X, Coordinate.Y + DistanceBetweenKing));
						return pos;
						// the last position in array is eating the piece that made check we will control this in setposition
					}
				}
				pos.push_back(Position(X, Coordinate.Y + DistanceBetweenKing));
			}
		}
	}
	if (side == Side::RightTopDiagonal)
	{
		for (int X = Coordinate.X + 1; X < 8; X++)
		{
			int DistanceBetweenKing = X - Coordinate.X;

			if (Coordinate.Y - DistanceBetweenKing < 8 && Coordinate.Y - DistanceBetweenKing >= 0)
			{
				Piece* piece = game->getFieldPos(X, Coordinate.Y - DistanceBetweenKing);
				if (piece != nullptr)
				{
					if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::BISHOP)
					{
						pos.push_back(Position(X, Coordinate.Y - DistanceBetweenKing));
						return pos;
						// the last position in array is eating the piece that made check we will control this in setposition
					}
				}
				pos.push_back(Position(X, Coordinate.Y - DistanceBetweenKing));
			}
		}
	}
	if (side == Side::LeftBotomDiagonal)
	{
		for (int X = Coordinate.X - 1; X >= 0; X--)
		{
			int DistanceBetweenKing = Coordinate.X - X;

			if (Coordinate.Y + DistanceBetweenKing < 8 && Coordinate.Y + DistanceBetweenKing >= 0)
			{
				Piece* piece = game->getFieldPos(X, Coordinate.Y + DistanceBetweenKing);
				if (piece != nullptr)
				{
					if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::BISHOP)
					{
						pos.push_back(Position(X, Coordinate.Y + DistanceBetweenKing));
						return pos;
						// the last position in array is eating the piece that made check we will control this in setposition
					}
				}
				pos.push_back(Position(X, Coordinate.Y + DistanceBetweenKing));
			}
		}
	}
	if (side == Side::LeftTopDiagonal)
	{
		for (int X = Coordinate.X - 1; X >= 0; X--)
		{
			int DistanceBetweenKing = Coordinate.X - X;

			if (Coordinate.Y - DistanceBetweenKing < 8 && Coordinate.Y - DistanceBetweenKing >= 0)
			{
				Piece* piece = game->getFieldPos(X, Coordinate.Y - DistanceBetweenKing);
				if (piece != nullptr)
				{
					if (piece->GetPieceType() == PieceType::QUEEN || piece->GetPieceType() == PieceType::BISHOP)
					{
						pos.push_back(Position(X, Coordinate.Y - DistanceBetweenKing));
						return pos;
						// the last position in array is eating the piece that made check we will control this in setposition
					}
				}
				pos.push_back(Position(X, Coordinate.Y - DistanceBetweenKing));
			}
		}
	}
}
