#include "Queen.h"
#include "Game.h"
#include "King.h"
#include <iostream>
Queen::Queen(Team team, Position p, SDL_Handler* handler, PieceType type)
{
	m_team = team;
	m_Position = p;
	m_handler = handler;
	m_type = type;

	std::string filename;
	if (team == BLACK)
	{
		filename = "icons/black_queen.png";
	}
	else
	{
		filename = "icons/white_queen.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	Render();
}

void Queen::SetPossibleMoves(Game* game, CheckIfData& kingdata)
{
	std::vector<Movement> moves;
	Position QueenPos = GetPosition();

	if (kingdata.checkcount == 0)
	{
		// Y + 1
	    yplusone:if (QueenPos.Y + 1 < 8)
		{
			if (game->m_field[QueenPos.X][QueenPos.Y + 1] != nullptr)
			{
				if (game->m_field[QueenPos.X][QueenPos.Y + 1]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X][QueenPos.Y + 1];
					game->m_field[QueenPos.X][QueenPos.Y + 1] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X, QueenPos.Y + 1), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y + 1];
					game->m_field[QueenPos.X][QueenPos.Y + 1] = eatenpiece;
					goto yminuesone;
				}
				goto yminuesone;
			}
			else if (game->m_field[QueenPos.X][QueenPos.Y + 1] == nullptr)
			{
				game->m_field[QueenPos.X][QueenPos.Y + 1] = game->m_field[QueenPos.X][QueenPos.Y];
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X, QueenPos.Y + 1), MoveType::NORMAL);
					moves.push_back(m);

					for (int Y = QueenPos.Y + 2;Y < 8; Y++)
					{
						if (game->m_field[QueenPos.X][Y] != nullptr)
						{
							if (game->m_field[QueenPos.X][Y]->GetTeam() != m_team)
							{
								Movement m = Movement(Position(QueenPos.X, Y), MoveType::INIT);
								moves.push_back(m);
								break;
							}
							break;
						}

						Movement m = Movement(Position(QueenPos.X, Y), MoveType::NORMAL);
						moves.push_back(m);
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y + 1];
				game->m_field[QueenPos.X][QueenPos.Y + 1] = nullptr;
				goto yminuesone;
			}
		}

		// Y - 1
	    yminuesone:if (QueenPos.Y - 1 >= 0)
		{
			if (game->m_field[QueenPos.X][QueenPos.Y - 1] != nullptr)
			{
				if (game->m_field[QueenPos.X][QueenPos.Y - 1]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X][QueenPos.Y - 1];
					game->m_field[QueenPos.X][QueenPos.Y - 1] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X, QueenPos.Y - 1), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y - 1];
					game->m_field[QueenPos.X][QueenPos.Y - 1] = eatenpiece;
					goto xplusone;
				}
				goto xplusone;
			}
			else if (game->m_field[QueenPos.X][QueenPos.Y - 1] == nullptr)
			{
				game->m_field[QueenPos.X][QueenPos.Y - 1] = game->m_field[QueenPos.X][QueenPos.Y];
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X, QueenPos.Y - 1), MoveType::NORMAL);
					moves.push_back(m);

					for (int Y = QueenPos.Y - 2; Y >= 0; Y--)
					{
						if (game->m_field[QueenPos.X][Y] != nullptr)
						{
							if (game->m_field[QueenPos.X][Y]->GetTeam() != m_team)
							{
								Movement m = Movement(Position(QueenPos.X, Y), MoveType::INIT);
								moves.push_back(m);
								break;
							}
							break;
						}

						Movement m = Movement(Position(QueenPos.X, Y), MoveType::NORMAL);
						moves.push_back(m);
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y - 1];
				game->m_field[QueenPos.X][QueenPos.Y - 1] = nullptr;
				goto xplusone;
			}
		}
	  
		// X + 1
	    xplusone:if (QueenPos.X + 1 < 8)
	    {
			if (game->m_field[QueenPos.X + 1][QueenPos.Y] != nullptr)
			{
				if (game->m_field[QueenPos.X + 1][QueenPos.Y]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X + 1][QueenPos.Y];
					game->m_field[QueenPos.X + 1][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X + 1, QueenPos.Y), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X + 1][QueenPos.Y];
					game->m_field[QueenPos.X + 1][QueenPos.Y] = eatenpiece;
					goto xminuesone;
				}
				goto xminuesone;
			}
			else if (game->m_field[QueenPos.X + 1][QueenPos.Y] == nullptr)
			{
				game->m_field[QueenPos.X + 1][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y];
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X + 1, QueenPos.Y), MoveType::NORMAL);
					moves.push_back(m);

					for (int X = QueenPos.X + 2; X < 8; X++)
					{
						if (game->m_field[X][QueenPos.Y] != nullptr)
						{
							if (game->m_field[X][QueenPos.Y]->GetTeam() != m_team)
							{
								Movement m = Movement(Position(X, QueenPos.Y), MoveType::INIT);
								moves.push_back(m);
								break;
							}
							break;
						}

						Movement m = Movement(Position(X, QueenPos.Y), MoveType::NORMAL);
						moves.push_back(m);
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X + 1][QueenPos.Y];
				game->m_field[QueenPos.X + 1][QueenPos.Y] = nullptr;
				goto xminuesone;
			}
	    }

		// X - 1
	    xminuesone:if (QueenPos.X - 1 >= 0)
	    {
			if (game->m_field[QueenPos.X - 1][QueenPos.Y] != nullptr)
			{
				if (game->m_field[QueenPos.X - 1][QueenPos.Y]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X - 1][QueenPos.Y];
					game->m_field[QueenPos.X - 1][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X - 1, QueenPos.Y), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X - 1][QueenPos.Y];
					game->m_field[QueenPos.X - 1][QueenPos.Y] = eatenpiece;
					goto xminusoneyplusone;
				}
				goto xminusoneyplusone;
			}
			else if (game->m_field[QueenPos.X - 1][QueenPos.Y] == nullptr)
			{
				game->m_field[QueenPos.X - 1][QueenPos.Y] = game->m_field[QueenPos.X][QueenPos.Y];
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X - 1, QueenPos.Y), MoveType::NORMAL);
					moves.push_back(m);

					for (int X = QueenPos.X - 2; X >= 0; X--)
					{
						if (game->m_field[X][QueenPos.Y] != nullptr)
						{
							if (game->m_field[X][QueenPos.Y]->GetTeam() != m_team)
							{
								Movement m = Movement(Position(X, QueenPos.Y), MoveType::INIT);
								moves.push_back(m);
								break;
							}
							break;
						}

						Movement m = Movement(Position(X, QueenPos.Y), MoveType::NORMAL);
						moves.push_back(m);
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X - 1][QueenPos.Y];
				game->m_field[QueenPos.X - 1][QueenPos.Y] = nullptr;
				goto xminusoneyplusone;
			}
	    }

		// X - 1 Y + 1 DIAGONAL
	    xminusoneyplusone:if (QueenPos.X - 1 >= 0 && QueenPos.Y + 1 < 8)
	    {
			if (game->m_field[QueenPos.X - 1][QueenPos.Y + 1] != nullptr)
			{
				if (game->m_field[QueenPos.X - 1][QueenPos.Y + 1]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X - 1][QueenPos.Y + 1];
					game->m_field[QueenPos.X - 1][QueenPos.Y + 1] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X - 1, QueenPos.Y + 1), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X - 1][QueenPos.Y + 1];
					game->m_field[QueenPos.X - 1][QueenPos.Y + 1] = eatenpiece;
					goto xminusoneyminuesone;
				}
				goto xminusoneyminuesone;
			}
			else if (game->m_field[QueenPos.X - 1][QueenPos.Y + 1] == nullptr)
			{
				game->m_field[QueenPos.X - 1][QueenPos.Y + 1] = game->m_field[QueenPos.X][QueenPos.Y];
				//game->m_field[QueenPos.X][QueenPos.Y + 1] = nullptr;
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X - 1, QueenPos.Y + 1), MoveType::NORMAL);
					moves.push_back(m);

					for (int X = QueenPos.X - 2; X >= 0; X--)
					{
						int DistanceBetweenQueen = QueenPos.X - X;

						if (QueenPos.Y + DistanceBetweenQueen < 8 && QueenPos.Y + DistanceBetweenQueen >= 0)
						{
							if (game->m_field[X][QueenPos.Y + DistanceBetweenQueen] != nullptr)
							{
								if (game->m_field[X][QueenPos.Y + DistanceBetweenQueen]->GetTeam() != m_team)
								{
									Movement m = Movement(Position(X, QueenPos.Y + DistanceBetweenQueen), MoveType::INIT);
									moves.push_back(m);
									break;
								}
								break;
							}

							Movement m = Movement(Position(X, QueenPos.Y + DistanceBetweenQueen), MoveType::NORMAL);
							moves.push_back(m);
						}
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X - 1][QueenPos.Y + 1];
				game->m_field[QueenPos.X - 1][QueenPos.Y + 1] = nullptr;
				goto xminusoneyminuesone;
			}
	    }

		// X - 1 Y - 1 DIAGONAL
	    xminusoneyminuesone:if (QueenPos.X - 1 >= 0 && QueenPos.Y - 1 >= 0)
	    {
			if (game->m_field[QueenPos.X - 1][QueenPos.Y - 1] != nullptr)
			{
				if (game->m_field[QueenPos.X - 1][QueenPos.Y - 1]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X - 1][QueenPos.Y - 1];
					game->m_field[QueenPos.X - 1][QueenPos.Y - 1] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X - 1, QueenPos.Y - 1), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X - 1][QueenPos.Y - 1];
					game->m_field[QueenPos.X - 1][QueenPos.Y - 1] = eatenpiece;
					goto xplusoneyplusone;
				}
				goto xplusoneyplusone;
			}
			else if (game->m_field[QueenPos.X - 1][QueenPos.Y - 1] == nullptr)
			{
				game->m_field[QueenPos.X - 1][QueenPos.Y - 1] = game->m_field[QueenPos.X][QueenPos.Y];
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t; //

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X - 1, QueenPos.Y - 1), MoveType::NORMAL);
					moves.push_back(m);

					for (int X = QueenPos.X - 2; X >= 0; X--)
					{
						int DistanceBetweenQueen = QueenPos.X - X;

						if (QueenPos.Y - DistanceBetweenQueen < 8 && QueenPos.Y - DistanceBetweenQueen >= 0)
						{
							if (game->m_field[X][QueenPos.Y - DistanceBetweenQueen] != nullptr)
							{
								if (game->m_field[X][QueenPos.Y - DistanceBetweenQueen]->GetTeam() != m_team)
								{
									Movement m = Movement(Position(X, QueenPos.Y - DistanceBetweenQueen), MoveType::INIT);
									moves.push_back(m);
									break;
								}
								break;
							}

							Movement m = Movement(Position(X, QueenPos.Y - DistanceBetweenQueen), MoveType::NORMAL);
							moves.push_back(m);
						}
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X - 1][QueenPos.Y - 1];
				game->m_field[QueenPos.X - 1][QueenPos.Y - 1] = nullptr;
				goto xplusoneyplusone;
			}
	    }

		// X + 1 Y + 1 DIAGONAL
	    xplusoneyplusone:if (QueenPos.X + 1 < 8 && QueenPos.Y + 1 < 8)
	    {
			if (game->m_field[QueenPos.X + 1][QueenPos.Y + 1] != nullptr)
			{
				if (game->m_field[QueenPos.X + 1][QueenPos.Y + 1]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X + 1][QueenPos.Y + 1];
					game->m_field[QueenPos.X + 1][QueenPos.Y + 1] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X + 1, QueenPos.Y + 1), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X + 1][QueenPos.Y + 1];
					game->m_field[QueenPos.X + 1][QueenPos.Y + 1] = eatenpiece;
					goto xplusoneyminuesone;
				}
				goto xplusoneyminuesone;
			}
			else if (game->m_field[QueenPos.X + 1][QueenPos.Y + 1] == nullptr)
			{
				game->m_field[QueenPos.X + 1][QueenPos.Y + 1] = game->m_field[QueenPos.X][QueenPos.Y];
				//game->m_field[QueenPos.X][QueenPos.Y + 1] = nullptr;
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X + 1, QueenPos.Y + 1), MoveType::NORMAL);
					moves.push_back(m);

					for (int X = QueenPos.X + 2; X < 8; X++)
					{
						int DistanceBetweenQueen = X - QueenPos.X;

						if (QueenPos.Y + DistanceBetweenQueen < 8 && QueenPos.Y + DistanceBetweenQueen >= 0)
						{
							if (game->m_field[X][QueenPos.Y + DistanceBetweenQueen] != nullptr)
							{
								if (game->m_field[X][QueenPos.Y + DistanceBetweenQueen]->GetTeam() != m_team)
								{
									Movement m = Movement(Position(X, QueenPos.Y + DistanceBetweenQueen), MoveType::INIT);
									moves.push_back(m);
									break;
								}
								break;
							}

							Movement m = Movement(Position(X, QueenPos.Y + DistanceBetweenQueen), MoveType::NORMAL);
							moves.push_back(m);
						}
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X + 1][QueenPos.Y + 1];
				game->m_field[QueenPos.X + 1][QueenPos.Y + 1] = nullptr;
				goto xplusoneyminuesone;
			}
	    }

	    xplusoneyminuesone:if (QueenPos.X + 1 < 8 && QueenPos.Y - 1 >= 0)
	    {
			if (game->m_field[QueenPos.X + 1][QueenPos.Y - 1] != nullptr)
			{
				if (game->m_field[QueenPos.X + 1][QueenPos.Y - 1]->GetTeam() != m_team)
				{
					Piece* eatenpiece = game->m_field[QueenPos.X + 1][QueenPos.Y - 1];
					game->m_field[QueenPos.X + 1][QueenPos.Y - 1] = game->m_field[QueenPos.X][QueenPos.Y];
					game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

					Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

					if (t == Team::NONE)
					{
						Movement m = Movement(Position(QueenPos.X + 1, QueenPos.Y - 1), MoveType::INIT);
						moves.push_back(m);
					}
					game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X + 1][QueenPos.Y - 1];
					game->m_field[QueenPos.X + 1][QueenPos.Y - 1] = eatenpiece;
					goto end;
				}
				goto end;
			}
			else if (game->m_field[QueenPos.X + 1][QueenPos.Y - 1] == nullptr)
			{
				game->m_field[QueenPos.X + 1][QueenPos.Y - 1] = game->m_field[QueenPos.X][QueenPos.Y];
				//game->m_field[QueenPos.X][QueenPos.Y - 1] = nullptr;
				game->m_field[QueenPos.X][QueenPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(QueenPos.X + 1, QueenPos.Y - 1), MoveType::NORMAL);
					moves.push_back(m);

					for (int X = QueenPos.X + 2; X < 8; X++)
					{
						int DistanceBetweenQueen = X - QueenPos.X;

						if (QueenPos.Y - DistanceBetweenQueen < 8 && QueenPos.Y - DistanceBetweenQueen >= 0)
						{
							if (game->m_field[X][QueenPos.Y - DistanceBetweenQueen] != nullptr)
							{
								if (game->m_field[X][QueenPos.Y - DistanceBetweenQueen]->GetTeam() != m_team)
								{
									Movement m = Movement(Position(X, QueenPos.Y - DistanceBetweenQueen), MoveType::INIT);
									moves.push_back(m);
									break;
								}
								break;
							}

							Movement m = Movement(Position(X, QueenPos.Y - DistanceBetweenQueen), MoveType::NORMAL);
							moves.push_back(m);
						}
					}
				}

				game->m_field[QueenPos.X][QueenPos.Y] = game->m_field[QueenPos.X + 1][QueenPos.Y - 1];
				game->m_field[QueenPos.X + 1][QueenPos.Y - 1] = nullptr;
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
	  for (int YToTop = QueenPos.Y + 1; YToTop < 8; YToTop++)
	  {
		  if (!pieceonline)
		  {
			  if (game->m_field[QueenPos.X][YToTop] != nullptr)
			  {
				  pieceonline = true;
				  if (game->m_field[QueenPos.X][YToTop]->GetTeam() == m_team)
				  {
					  break;
				  }
			  }
			  for (int i = 0; i < Coordinates.size(); i++)
			  {
				  if (QueenPos.X == Coordinates[i].X && YToTop == Coordinates[i].Y)
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
	  for (int YToTop = QueenPos.Y - 1; YToTop >= 0; YToTop--)
	  {
		  if (!pieceonline)
		  {
			  if (game->m_field[QueenPos.X][YToTop] != nullptr)
			  {
				  pieceonline = true;
				  if (game->m_field[QueenPos.X][YToTop]->GetTeam() == m_team)
				  {
					  break;
				  }
			  }
			  for (int i = 0; i < Coordinates.size(); i++)
			  {
				  if (QueenPos.X == Coordinates[i].X && YToTop == Coordinates[i].Y)
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
	  bool pieceonlineTopD = false;
	  bool pieceonlineBottomD = false;
	  for (int YToTop = QueenPos.X + 1; YToTop < 8; YToTop++)
	  {
		  int DistanceBetweenKing = YToTop - QueenPos.X;
	      one:if (!pieceonline)
		  {
			  if (game->m_field[YToTop][QueenPos.Y] != nullptr)
			  {
				  pieceonline = true;
				  if (game->m_field[YToTop][QueenPos.Y]->GetTeam() == m_team)
				  {
					  goto one;
				  }
			  }
			  for (int i = 0; i < Coordinates.size(); i++)
			  {
				  if (YToTop == Coordinates[i].X && QueenPos.Y == Coordinates[i].Y)
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
		  if (!pieceonlineBottomD)
		  {
			  if (QueenPos.Y + DistanceBetweenKing < 8 && QueenPos.Y + DistanceBetweenKing >= 0)
			  {
				  if (game->m_field[YToTop][QueenPos.Y + DistanceBetweenKing] != nullptr)
				  {
					  pieceonlineBottomD = true;
					  if (game->m_field[YToTop][QueenPos.Y + DistanceBetweenKing]->GetTeam() == m_team)
					  {
						  goto one;
					  }
				  }
				  for (int i = 0; i < Coordinates.size(); i++)
				  {
					  if (YToTop == Coordinates[i].X && QueenPos.Y + DistanceBetweenKing == Coordinates[i].Y)
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
		  if (!pieceonlineTopD)
		  {
			  if (QueenPos.Y - DistanceBetweenKing < 8 && QueenPos.Y - DistanceBetweenKing >= 0)
			  {
				  if (game->m_field[YToTop][QueenPos.Y - DistanceBetweenKing] != nullptr)
				  {
					  pieceonlineTopD = true;
					  if (game->m_field[YToTop][QueenPos.Y - DistanceBetweenKing]->GetTeam() == m_team)
					  {
						  goto one;
					  }
				  }
				  for (int i = 0; i < Coordinates.size(); i++)
				  {
					  if (YToTop == Coordinates[i].X && QueenPos.Y - DistanceBetweenKing == Coordinates[i].Y)
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
	  pieceonline = false;
	  pieceonlineTopD = false;
      pieceonlineBottomD = false;
	  for (int YToTop = QueenPos.X - 1; YToTop >= 0; YToTop--)
	  {
		  int DistanceBetweenKing = QueenPos.X - YToTop;
		  onee:if (!pieceonline)
		  {
			  if (game->m_field[YToTop][QueenPos.Y] != nullptr)
			  {
				  pieceonline = true;
				  if (game->m_field[YToTop][QueenPos.Y]->GetTeam() == m_team)
				  {
					  goto onee;
				  }
			  }
			  for (int i = 0; i < Coordinates.size(); i++)
			  {
				  if (YToTop == Coordinates[i].X && QueenPos.Y == Coordinates[i].Y)
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
		  if (!pieceonlineBottomD)
		  {
			  if (QueenPos.Y + DistanceBetweenKing < 8 && QueenPos.Y + DistanceBetweenKing >= 0)
			  {
				  if (game->m_field[YToTop][QueenPos.Y + DistanceBetweenKing] != nullptr)
				  {
					  pieceonlineBottomD = true;
					  if (game->m_field[YToTop][QueenPos.Y + DistanceBetweenKing]->GetTeam() == m_team)
					  {
						  goto onee;
					  }
				  }
				  for (int i = 0; i < Coordinates.size(); i++)
				  {
					  if (YToTop == Coordinates[i].X && QueenPos.Y + DistanceBetweenKing == Coordinates[i].Y)
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
		  if (!pieceonlineTopD)
		  {
			  if (QueenPos.Y - DistanceBetweenKing < 8 && QueenPos.Y - DistanceBetweenKing >= 0)
			  {
				  if (game->m_field[YToTop][QueenPos.Y - DistanceBetweenKing] != nullptr)
				  {
					  pieceonlineTopD = true;
					  if (game->m_field[YToTop][QueenPos.Y - DistanceBetweenKing]->GetTeam() == m_team)
					  {
						  goto onee;
					  }
				  }
				  for (int i = 0; i < Coordinates.size(); i++)
				  {
					  if (YToTop == Coordinates[i].X && QueenPos.Y - DistanceBetweenKing == Coordinates[i].Y)
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
	}
	PossibleMoves = moves;
}
