#include "Bishop.h"
#include "Game.h"
#include "King.h"
#include <iostream>

Bishop::Bishop(Team team, Position p, SDL_Handler* handler, PieceType type)
{
		m_team = team;
		m_Position = p;
		m_handler = handler;
		m_type = type;

		std::string filename;
		if (team == BLACK)
		{
			filename = "icons/black_bishop.png";
		}
		else
		{
			filename = "icons/white_bishop.png";
		}
		m_handler = handler;
		m_texture = handler->loadImage(filename);


		Render();
}

void Bishop::SetPossibleMoves(Game* game, CheckIfData& kingdata)
{
	std::vector<Movement> moves;
	Position BishopPos = GetPosition();

	if (kingdata.checkcount == 0)
	{
	  // X - 1 Y + 1 DIAGONAL
	  xminusoneyplusone:if (BishopPos.X - 1 >= 0 && BishopPos.Y + 1 < 8)
	  {
		if (game->m_field[BishopPos.X - 1][BishopPos.Y + 1] != nullptr)
		{
			if (game->m_field[BishopPos.X - 1][BishopPos.Y + 1]->GetTeam() != m_team)
			{
				Piece* eatenpiece = game->m_field[BishopPos.X - 1][BishopPos.Y + 1];
				game->m_field[BishopPos.X - 1][BishopPos.Y + 1] = game->m_field[BishopPos.X][BishopPos.Y];
				game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

				Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				if (t == Team::NONE)
				{
					Movement m = Movement(Position(BishopPos.X - 1, BishopPos.Y + 1), MoveType::INIT);
					moves.push_back(m);
				}
				game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X - 1][BishopPos.Y + 1];
				game->m_field[BishopPos.X - 1][BishopPos.Y + 1] = eatenpiece;
				goto xminusoneyminuesone;
			}
			goto xminusoneyminuesone;
		}
		else if (game->m_field[BishopPos.X - 1][BishopPos.Y + 1] == nullptr)
		{
			game->m_field[BishopPos.X - 1][BishopPos.Y + 1] = game->m_field[BishopPos.X][BishopPos.Y];
			//game->m_field[BishopPos.X][BishopPos.Y + 1] = nullptr;
			game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

			Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			if (t == Team::NONE)
			{
				Movement m = Movement(Position(BishopPos.X - 1, BishopPos.Y + 1), MoveType::NORMAL);
				moves.push_back(m);

				for (int X = BishopPos.X - 2; X >= 0; X--)
				{
					int DistanceBetweenQueen = BishopPos.X - X;

					if (BishopPos.Y + DistanceBetweenQueen < 8 && BishopPos.Y + DistanceBetweenQueen >= 0)
					{
						if (game->m_field[X][BishopPos.Y + DistanceBetweenQueen] != nullptr)
						{
							if (game->m_field[X][BishopPos.Y + DistanceBetweenQueen]->GetTeam() != m_team)
							{
								Movement m = Movement(Position(X, BishopPos.Y + DistanceBetweenQueen), MoveType::INIT);
								moves.push_back(m);
								break;
							}
							break;
						}

						Movement m = Movement(Position(X, BishopPos.Y + DistanceBetweenQueen), MoveType::NORMAL);
						moves.push_back(m);
					}
				}
			}

			game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X - 1][BishopPos.Y + 1];
			game->m_field[BishopPos.X - 1][BishopPos.Y + 1] = nullptr;
			goto xminusoneyminuesone;
		}
	  }

	  // X - 1 Y - 1 DIAGONAL
      xminusoneyminuesone:if (BishopPos.X - 1 >= 0 && BishopPos.Y - 1 >= 0)
      {
		  if (game->m_field[BishopPos.X - 1][BishopPos.Y - 1] != nullptr)
		  {
			  if (game->m_field[BishopPos.X - 1][BishopPos.Y - 1]->GetTeam() != m_team)
			  {
				  Piece* eatenpiece = game->m_field[BishopPos.X - 1][BishopPos.Y - 1];
				  game->m_field[BishopPos.X - 1][BishopPos.Y - 1] = game->m_field[BishopPos.X][BishopPos.Y];
				  game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

				  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				  if (t == Team::NONE)
				  {
					  Movement m = Movement(Position(BishopPos.X - 1, BishopPos.Y - 1), MoveType::INIT);
					  moves.push_back(m);
				  }
				  game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X - 1][BishopPos.Y - 1];
				  game->m_field[BishopPos.X - 1][BishopPos.Y - 1] = eatenpiece;
				  goto xplusoneyplusone;
			  }
			  goto xplusoneyplusone;
		  }
		  else if (game->m_field[BishopPos.X - 1][BishopPos.Y - 1] == nullptr)
		  {
			  game->m_field[BishopPos.X - 1][BishopPos.Y - 1] = game->m_field[BishopPos.X][BishopPos.Y];
			  game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

			  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t; //

			  if (t == Team::NONE)
			  {
				  Movement m = Movement(Position(BishopPos.X - 1, BishopPos.Y - 1), MoveType::NORMAL);
				  moves.push_back(m);

				  for (int X = BishopPos.X - 2; X >= 0; X--)
				  {
					  int DistanceBetweenQueen = BishopPos.X - X;

					  if (BishopPos.Y - DistanceBetweenQueen < 8 && BishopPos.Y - DistanceBetweenQueen >= 0)
					  {
						  if (game->m_field[X][BishopPos.Y - DistanceBetweenQueen] != nullptr)
						  {
							  if (game->m_field[X][BishopPos.Y - DistanceBetweenQueen]->GetTeam() != m_team)
							  {
								  Movement m = Movement(Position(X, BishopPos.Y - DistanceBetweenQueen), MoveType::INIT);
								  moves.push_back(m);
								  break;
							  }
							  break;
						  }

						  Movement m = Movement(Position(X, BishopPos.Y - DistanceBetweenQueen), MoveType::NORMAL);
						  moves.push_back(m);
					  }
				  }
			  }

			  game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X - 1][BishopPos.Y - 1];
			  game->m_field[BishopPos.X - 1][BishopPos.Y - 1] = nullptr;
			  goto xplusoneyplusone;
		  }
      }

	  // X + 1 Y + 1 DIAGONAL
      xplusoneyplusone:if (BishopPos.X + 1 < 8 && BishopPos.Y + 1 < 8)
      {
		  if (game->m_field[BishopPos.X + 1][BishopPos.Y + 1] != nullptr)
		  {
			  if (game->m_field[BishopPos.X + 1][BishopPos.Y + 1]->GetTeam() != m_team)
			  {
				  Piece* eatenpiece = game->m_field[BishopPos.X + 1][BishopPos.Y + 1];
				  game->m_field[BishopPos.X + 1][BishopPos.Y + 1] = game->m_field[BishopPos.X][BishopPos.Y];
				  game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

				  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				  if (t == Team::NONE)
				  {
					  Movement m = Movement(Position(BishopPos.X + 1, BishopPos.Y + 1), MoveType::INIT);
					  moves.push_back(m);
				  }
				  game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X + 1][BishopPos.Y + 1];
				  game->m_field[BishopPos.X + 1][BishopPos.Y + 1] = eatenpiece;
				  goto xplusoneyminuesone;
			  }
			  goto xplusoneyminuesone;
		  }
		  else if (game->m_field[BishopPos.X + 1][BishopPos.Y + 1] == nullptr)
		  {
			  game->m_field[BishopPos.X + 1][BishopPos.Y + 1] = game->m_field[BishopPos.X][BishopPos.Y];
			  //game->m_field[BishopPos.X][BishopPos.Y + 1] = nullptr;
			  game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

			  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			  if (t == Team::NONE)
			  {
				  Movement m = Movement(Position(BishopPos.X + 1, BishopPos.Y + 1), MoveType::NORMAL);
				  moves.push_back(m);

				  for (int X = BishopPos.X + 2; X < 8; X++)
				  {
					  int DistanceBetweenQueen = X - BishopPos.X;

					  if (BishopPos.Y + DistanceBetweenQueen < 8 && BishopPos.Y + DistanceBetweenQueen >= 0)
					  {
						  if (game->m_field[X][BishopPos.Y + DistanceBetweenQueen] != nullptr)
						  {
							  if (game->m_field[X][BishopPos.Y + DistanceBetweenQueen]->GetTeam() != m_team)
							  {
								  Movement m = Movement(Position(X, BishopPos.Y + DistanceBetweenQueen), MoveType::INIT);
								  moves.push_back(m);
								  break;
							  }
							  break;
						  }

						  Movement m = Movement(Position(X, BishopPos.Y + DistanceBetweenQueen), MoveType::NORMAL);
						  moves.push_back(m);
					  }
				  }
			  }

			  game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X + 1][BishopPos.Y + 1];
			  game->m_field[BishopPos.X + 1][BishopPos.Y + 1] = nullptr;
			  goto xplusoneyminuesone;
		  }
      }

      xplusoneyminuesone:if (BishopPos.X + 1 < 8 && BishopPos.Y - 1 >= 0)
      {
		  if (game->m_field[BishopPos.X + 1][BishopPos.Y - 1] != nullptr)
		  {
			  if (game->m_field[BishopPos.X + 1][BishopPos.Y - 1]->GetTeam() != m_team)
			  {
				  Piece* eatenpiece = game->m_field[BishopPos.X + 1][BishopPos.Y - 1];
				  game->m_field[BishopPos.X + 1][BishopPos.Y - 1] = game->m_field[BishopPos.X][BishopPos.Y];
				  game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

				  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				  if (t == Team::NONE)
				  {
					  Movement m = Movement(Position(BishopPos.X + 1, BishopPos.Y - 1), MoveType::INIT);
					  moves.push_back(m);
				  }
				  game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X + 1][BishopPos.Y - 1];
				  game->m_field[BishopPos.X + 1][BishopPos.Y - 1] = eatenpiece;
				  goto end;
			  }
			  goto end;
		  }
		  else if (game->m_field[BishopPos.X + 1][BishopPos.Y - 1] == nullptr)
		  {
			  game->m_field[BishopPos.X + 1][BishopPos.Y - 1] = game->m_field[BishopPos.X][BishopPos.Y];
			  //game->m_field[BishopPos.X][BishopPos.Y - 1] = nullptr;
			  game->m_field[BishopPos.X][BishopPos.Y] = nullptr;

			  Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			  if (t == Team::NONE)
			  {
				  Movement m = Movement(Position(BishopPos.X + 1, BishopPos.Y - 1), MoveType::NORMAL);
				  moves.push_back(m);

				  for (int X = BishopPos.X + 2; X < 8; X++)
				  {
					  int DistanceBetweenQueen = X - BishopPos.X;

					  if (BishopPos.Y - DistanceBetweenQueen < 8 && BishopPos.Y - DistanceBetweenQueen >= 0)
					  {
						  if (game->m_field[X][BishopPos.Y - DistanceBetweenQueen] != nullptr)
						  {
							  if (game->m_field[X][BishopPos.Y - DistanceBetweenQueen]->GetTeam() != m_team)
							  {
								  Movement m = Movement(Position(X, BishopPos.Y - DistanceBetweenQueen), MoveType::INIT);
								  moves.push_back(m);
								  break;
							  }
							  break;
						  }

						  Movement m = Movement(Position(X, BishopPos.Y - DistanceBetweenQueen), MoveType::NORMAL);
						  moves.push_back(m);
					  }
				  }
			  }

			  game->m_field[BishopPos.X][BishopPos.Y] = game->m_field[BishopPos.X + 1][BishopPos.Y - 1];
			  game->m_field[BishopPos.X + 1][BishopPos.Y - 1] = nullptr;
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
	   bool pieceonlineTopD = false;
	   bool pieceonlineBottomD = false;

	   for (int YToTop = BishopPos.X + 1; YToTop < 8; YToTop++)
	   {
		   int DistanceBetweenKing = YToTop - BishopPos.X;

           one:if (!pieceonlineBottomD)
		   {
			   if (BishopPos.Y + DistanceBetweenKing < 8 && BishopPos.Y + DistanceBetweenKing >= 0)
			   {
				   if (game->m_field[YToTop][BishopPos.Y + DistanceBetweenKing] != nullptr)
				   {
					   pieceonlineBottomD = true;
					   if (game->m_field[YToTop][BishopPos.Y + DistanceBetweenKing]->GetTeam() == m_team)
					   {
						   goto one;
					   }
				   }
				   for (int i = 0; i < Coordinates.size(); i++)
				   {
					   if (YToTop == Coordinates[i].X && BishopPos.Y + DistanceBetweenKing == Coordinates[i].Y)
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
			   if (BishopPos.Y - DistanceBetweenKing < 8 && BishopPos.Y - DistanceBetweenKing >= 0)
			   {
				   if (game->m_field[YToTop][BishopPos.Y - DistanceBetweenKing] != nullptr)
				   {
					   pieceonlineTopD = true;
					   if (game->m_field[YToTop][BishopPos.Y - DistanceBetweenKing]->GetTeam() == m_team)
					   {
						   goto one;
					   }
				   }
				   for (int i = 0; i < Coordinates.size(); i++)
				   {
					   if (YToTop == Coordinates[i].X && BishopPos.Y - DistanceBetweenKing == Coordinates[i].Y)
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

	   pieceonlineTopD = false;
	   pieceonlineBottomD = false;

	   for (int YToTop = BishopPos.X - 1; YToTop >= 0; YToTop--)
	   {
		   int DistanceBetweenKing = BishopPos.X - YToTop;
	   onee:if (!pieceonlineBottomD)
		   {
		     if (BishopPos.Y + DistanceBetweenKing < 8 && BishopPos.Y + DistanceBetweenKing >= 0)
		     {
			   if (game->m_field[YToTop][BishopPos.Y + DistanceBetweenKing] != nullptr)
			   {
				   pieceonlineBottomD = true;
				   if (game->m_field[YToTop][BishopPos.Y + DistanceBetweenKing]->GetTeam() == m_team)
				   {
					   goto onee;
				   }
			   }
			   for (int i = 0; i < Coordinates.size(); i++)
			   {
				   if (YToTop == Coordinates[i].X && BishopPos.Y + DistanceBetweenKing == Coordinates[i].Y)
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
			 if (BishopPos.Y - DistanceBetweenKing < 8 && BishopPos.Y - DistanceBetweenKing >= 0)
			 {
				 if (game->m_field[YToTop][BishopPos.Y - DistanceBetweenKing] != nullptr)
				 {
					 pieceonlineTopD = true;
					 if (game->m_field[YToTop][BishopPos.Y - DistanceBetweenKing]->GetTeam() == m_team)
					 {
						 goto onee;
					 }
				 }
				 for (int i = 0; i < Coordinates.size(); i++)
				 {
					 if (YToTop == Coordinates[i].X && BishopPos.Y - DistanceBetweenKing == Coordinates[i].Y)
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
