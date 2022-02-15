#include "Rook.h"
#include "Game.h"
#include "King.h"
#include <iostream>

Rook::Rook(Team team, Position p, SDL_Handler* handler, PieceType type)
{
	m_team = team;
	m_Position = p;
	m_handler = handler;
	m_type = type;

	std::string filename;
	if (team == BLACK)
	{
		filename = "icons/black_rook.png";
	}
	else
	{
		filename = "icons/white_rook.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);


	Render();
}

void Rook::SetPossibleMoves(Game* game, CheckIfData& kingdata)
{
	std::vector<Movement> moves;
	Position RookPos = GetPosition();


	if (kingdata.checkcount == 0)
	{
	  yplusone:if (RookPos.Y + 1 < 8)
	  {
		if (game->m_field[RookPos.X][RookPos.Y + 1] != nullptr)
		{
			if (game->m_field[RookPos.X][RookPos.Y + 1]->GetTeam() != m_team)
			{
				Piece* eatenpiece = game->m_field[RookPos.X][RookPos.Y + 1];
				game->m_field[RookPos.X][RookPos.Y + 1] = game->m_field[RookPos.X][RookPos.Y];
				game->m_field[RookPos.X][RookPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(RookPos.X, RookPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}
				game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y + 1];
				game->m_field[RookPos.X][RookPos.Y + 1] = eatenpiece;
				goto yminuesone;
			}
			goto yminuesone;
		}
		else if (game->m_field[RookPos.X][RookPos.Y + 1] == nullptr)
		{
			game->m_field[RookPos.X][RookPos.Y + 1] = game->m_field[RookPos.X][RookPos.Y];
			game->m_field[RookPos.X][RookPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(RookPos.X, RookPos.Y + 1), MoveType::NORMAL);
				moves.push_back(m);

				for (int Y = RookPos.Y + 2; Y < 8; Y++)
				{
					if (game->m_field[RookPos.X][Y] != nullptr)
					{
						if (game->m_field[RookPos.X][Y]->GetTeam() != m_team)
						{
							Movement m = Movement(Position(RookPos.X, Y), MoveType::INIT);
							moves.push_back(m);
							break;
						}
						break;
					}

					Movement m = Movement(Position(RookPos.X, Y), MoveType::NORMAL);
					moves.push_back(m);
				}
			}

			game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y + 1];
			game->m_field[RookPos.X][RookPos.Y + 1] = nullptr;
			goto yminuesone;
		}
	  }

	  // Y - 1
      yminuesone:if (RookPos.Y - 1 >= 0)
      {
		  if (game->m_field[RookPos.X][RookPos.Y - 1] != nullptr)
		  {
			  if (game->m_field[RookPos.X][RookPos.Y - 1]->GetTeam() != m_team)
			  {
				  Piece* eatenpiece = game->m_field[RookPos.X][RookPos.Y - 1];
				  game->m_field[RookPos.X][RookPos.Y - 1] = game->m_field[RookPos.X][RookPos.Y];
				  game->m_field[RookPos.X][RookPos.Y] = nullptr;

				  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				  if (t == Team::NONE)
				  {
					  Movement m = Movement(Position(RookPos.X, RookPos.Y - 1), MoveType::INIT);
					  moves.push_back(m);
				  }
				  game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y - 1];
				  game->m_field[RookPos.X][RookPos.Y - 1] = eatenpiece;
				  goto xplusone;
			  }
			  goto xplusone;
		  }
		  else if (game->m_field[RookPos.X][RookPos.Y - 1] == nullptr)
		  {
			  game->m_field[RookPos.X][RookPos.Y - 1] = game->m_field[RookPos.X][RookPos.Y];
			  game->m_field[RookPos.X][RookPos.Y] = nullptr;

			  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			  if (t == Team::NONE)
			  {
				  Movement m = Movement(Position(RookPos.X, RookPos.Y - 1), MoveType::NORMAL);
				  moves.push_back(m);

				  for (int Y = RookPos.Y - 2; Y >= 0; Y--)
				  {
					  if (game->m_field[RookPos.X][Y] != nullptr)
					  {
						  if (game->m_field[RookPos.X][Y]->GetTeam() != m_team)
						  {
							  Movement m = Movement(Position(RookPos.X, Y), MoveType::INIT);
							  moves.push_back(m);
							  break;
						  }
						  break;
					  }

					  Movement m = Movement(Position(RookPos.X, Y), MoveType::NORMAL);
					  moves.push_back(m);
				  }
			  }

			  game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y - 1];
			  game->m_field[RookPos.X][RookPos.Y - 1] = nullptr;
			  goto xplusone;
		  }
      }


	  // X + 1
      xplusone:if (RookPos.X + 1 < 8)
      {
		  if (game->m_field[RookPos.X + 1][RookPos.Y] != nullptr)
		  {
			  if (game->m_field[RookPos.X + 1][RookPos.Y]->GetTeam() != m_team)
			  {
				  Piece* eatenpiece = game->m_field[RookPos.X + 1][RookPos.Y];
				  game->m_field[RookPos.X + 1][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y];
				  game->m_field[RookPos.X][RookPos.Y] = nullptr;

				  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				  if (t == Team::NONE)
				  {
					  Movement m = Movement(Position(RookPos.X + 1, RookPos.Y), MoveType::INIT);
					  moves.push_back(m);
				  }
				  game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X + 1][RookPos.Y];
				  game->m_field[RookPos.X + 1][RookPos.Y] = eatenpiece;
				  goto xminuesone;
			  }
			  goto xminuesone;
		  }
		  else if (game->m_field[RookPos.X + 1][RookPos.Y] == nullptr)
		  {
			  game->m_field[RookPos.X + 1][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y];
			  game->m_field[RookPos.X][RookPos.Y] = nullptr;

			  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			  if (t == Team::NONE)
			  {
				  Movement m = Movement(Position(RookPos.X + 1, RookPos.Y), MoveType::NORMAL);
				  moves.push_back(m);

				  for (int X = RookPos.X + 2; X < 8; X++)
				  {
					  if (game->m_field[X][RookPos.Y] != nullptr)
					  {
						  if (game->m_field[X][RookPos.Y]->GetTeam() != m_team)
						  {
							  Movement m = Movement(Position(X, RookPos.Y), MoveType::INIT);
							  moves.push_back(m);
							  break;
						  }
						  break;
					  }

					  Movement m = Movement(Position(X, RookPos.Y), MoveType::NORMAL);
					  moves.push_back(m);
				  }
			  }

			  game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X + 1][RookPos.Y];
			  game->m_field[RookPos.X + 1][RookPos.Y] = nullptr;
			  goto xminuesone;
		  }
      }


	  // X - 1
      xminuesone:if (RookPos.X - 1 >= 0)
      {
		  if (game->m_field[RookPos.X - 1][RookPos.Y] != nullptr)
		  {
			  if (game->m_field[RookPos.X - 1][RookPos.Y]->GetTeam() != m_team)
			  {
				  Piece* eatenpiece = game->m_field[RookPos.X - 1][RookPos.Y];
				  game->m_field[RookPos.X - 1][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y];
				  game->m_field[RookPos.X][RookPos.Y] = nullptr;

				  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				  if (t == Team::NONE)
				  {
					  Movement m = Movement(Position(RookPos.X - 1, RookPos.Y), MoveType::INIT);
					  moves.push_back(m);
				  }
				  game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X - 1][RookPos.Y];
				  game->m_field[RookPos.X - 1][RookPos.Y] = eatenpiece;
				  goto end;
			  }
			  goto end;
		  }
		  else if (game->m_field[RookPos.X - 1][RookPos.Y] == nullptr)
		  {
			  game->m_field[RookPos.X - 1][RookPos.Y] = game->m_field[RookPos.X][RookPos.Y];
			  game->m_field[RookPos.X][RookPos.Y] = nullptr;

			  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			  if (t == Team::NONE)
			  {
				  Movement m = Movement(Position(RookPos.X - 1, RookPos.Y), MoveType::NORMAL);
				  moves.push_back(m);

				  for (int X = RookPos.X - 2; X >= 0; X--)
				  {
					  if (game->m_field[X][RookPos.Y] != nullptr)
					  {
						  if (game->m_field[X][RookPos.Y]->GetTeam() != m_team)
						  {
							  Movement m = Movement(Position(X, RookPos.Y), MoveType::INIT);
							  moves.push_back(m);
							  break;
						  }
						  break;
					  }

					  Movement m = Movement(Position(X, RookPos.Y), MoveType::NORMAL);
					  moves.push_back(m);
				  }
			  }

			  game->m_field[RookPos.X][RookPos.Y] = game->m_field[RookPos.X - 1][RookPos.Y];
			  game->m_field[RookPos.X - 1][RookPos.Y] = nullptr;
			  goto end;
		  }
      }

      end:
	  {

	  }
	}

	else if (kingdata.checkcount == 1)
	{
	    King* king = nullptr;
	    king = (King*)GetOwningKing(game->m_field);
	    std::vector<Position> Coordinates = king->GetPosesBetweenCheck(kingdata.checkside, game);
	    bool pieceonline = false;

		for (int YToTop = RookPos.Y + 1; YToTop < 8; YToTop++)
		{
			if (!pieceonline)
			{
				if (game->m_field[RookPos.X][YToTop] != nullptr)
				{
					pieceonline = true;
					if (game->m_field[RookPos.X][YToTop]->GetTeam() == m_team)
					{
						break;
					}
				}
				for (int i = 0; i < Coordinates.size(); i++)
				{
					if (RookPos.X == Coordinates[i].X && YToTop == Coordinates[i].Y)
					{
						if (i == Coordinates.size() - 1)
						{
							moves.push_back(Movement(Coordinates[i], MoveType::INIT));
						}
						else
						{
							moves.push_back(Movement(Coordinates[i], MoveType::NORMAL));
						}
					}
				}
				continue;
			}
			break;
		}
		pieceonline = false;
		for (int YToTop = RookPos.Y - 1; YToTop >= 0; YToTop--)
		{
			if (!pieceonline)
			{
				if (game->m_field[RookPos.X][YToTop] != nullptr)
				{
					pieceonline = true;
					if (game->m_field[RookPos.X][YToTop]->GetTeam() == m_team)
					{
						break;
					}
				}
				for (int i = 0; i < Coordinates.size(); i++)
				{
					if (RookPos.X == Coordinates[i].X && YToTop == Coordinates[i].Y)
					{
						if (i == Coordinates.size() - 1)
						{
							moves.push_back(Movement(Coordinates[i], MoveType::INIT));
						}
						else
						{
							moves.push_back(Movement(Coordinates[i], MoveType::NORMAL));
						}
					}
				}
				continue;
			}
			break;
		}
		pieceonline = false;
		for (int YToTop = RookPos.X + 1; YToTop < 8; YToTop++)
		{
		  int DistanceBetweenKing = YToTop - RookPos.X;
		  one:if (!pieceonline)
		  {
			if (game->m_field[YToTop][RookPos.Y] != nullptr)
			{
				pieceonline = true;
				if (game->m_field[YToTop][RookPos.Y]->GetTeam() == m_team)
				{
					goto one;
				}
			}
			for (int i = 0; i < Coordinates.size(); i++)
			{
				if (YToTop == Coordinates[i].X && RookPos.Y == Coordinates[i].Y)
				{
					if (i == Coordinates.size() - 1)
					{
						moves.push_back(Movement(Coordinates[i], MoveType::INIT));
					}
					else
					{
						moves.push_back(Movement(Coordinates[i], MoveType::NORMAL));
					}
				}
			}
		  }
		}
		pieceonline = false;
		for (int YToTop = RookPos.X - 1; YToTop >= 0; YToTop--)
		{
			int DistanceBetweenKing = RookPos.X - YToTop;
		  onee:if (!pieceonline)
		  {
			if (game->m_field[YToTop][RookPos.Y] != nullptr)
			{
				pieceonline = true;
				if (game->m_field[YToTop][RookPos.Y]->GetTeam() == m_team)
				{
					goto onee;
				}
			}
			for (int i = 0; i < Coordinates.size(); i++)
			{
				if (YToTop == Coordinates[i].X && RookPos.Y == Coordinates[i].Y)
				{
					if (i == Coordinates.size() - 1)
					{
						moves.push_back(Movement(Coordinates[i], MoveType::INIT));
					}
					else
					{
						moves.push_back(Movement(Coordinates[i], MoveType::NORMAL));
					}
				}
			}
		  }
		}
    }

	PossibleMoves = moves;
}
