#include "Pawn.h"
#include "Game.h"
Pawn::Pawn(Team team, Position p, SDL_Handler* handler, PieceType type)
{
	m_team = team;
	m_Position = p;
	m_handler = handler;
	m_type = type;

	std::string filename;
	if (team == BLACK)
	{
		filename = "icons/black_pawn.png";
	}
	else
	{
		filename = "icons/chess_white_pawn.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	if (m_texture != nullptr) { printf("pawn png is not null\n"); }
	Render();
}

void Pawn::EnPassant(Game* game)
{
	Position pos = GetPosition();
	if (pos.X - 1 >= 0 && game->m_field[pos.X - 1][pos.Y] != nullptr && game->m_field[pos.X - 1][pos.Y]->GetTeam() != m_team 
		&& game->m_field[pos.X - 1][pos.Y]->GetPieceType() == PieceType::PAWN)
	{
		Pawn* pawn = (Pawn*)game->m_field[pos.X - 1][pos.Y];
		if (pawn->EnpassantPossibility == -1)
		{
			pawn->EnpassantPossibility = 0;
			if (m_team == Team::BLACK)
			{
				pawn->EnpassantPos[0] = Position(pos.X, pos.Y + 1);
				pawn->EnpassantPos[1] = pos;
			}
			else
			{
				pawn->EnpassantPos[0] = Position(pos.X, pos.Y - 1);
				pawn->EnpassantPos[1] = pos;
			}
		}
	}
	if (pos.X + 1 < 8 && game->m_field[pos.X + 1][pos.Y] != nullptr && game->m_field[pos.X + 1][pos.Y]->GetTeam() != m_team
		&& game->m_field[pos.X + 1][pos.Y]->GetPieceType() == PieceType::PAWN)
	{
		Pawn* pawn = (Pawn*)game->m_field[pos.X + 1][pos.Y];
		if (pawn->EnpassantPossibility == -1)
		{
			pawn->EnpassantPossibility = 0;
			if (m_team == Team::BLACK)
			{
				pawn->EnpassantPos[0] = Position(pos.X, pos.Y + 1);
				pawn->EnpassantPos[1] = pos;
			}
			else
			{
				pawn->EnpassantPos[0] = Position(pos.X, pos.Y - 1);
				pawn->EnpassantPos[1] = pos;
			}
		}
	}
}

void Pawn::SetPossibleMoves(Game* game, struct CheckIfData& kingdata)
{
	std::vector<Movement> moves;
   Position PawnPos = GetPosition();
   if (m_team == Team::BLACK)
   {
	   //-------------------- Normal Move Part
	   if (PawnPos.Y - 1 >= 0 && game->getFieldPos(PawnPos.X, PawnPos.Y - 1) == nullptr)
	   {
		   Piece* temp = game->getFieldPos(PawnPos.X, PawnPos.Y);
		   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;
		   game->m_field[PawnPos.X][PawnPos.Y - 1] = temp;

		   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

		   if (t == Team::NONE)
		   {
			   Movement m = Movement(Position(PawnPos.X, PawnPos.Y - 1), MoveType::NORMAL);
			   moves.push_back(m);
		   }

		   if (firstmove)
		   {
			   if (game->getFieldPos(PawnPos.X, PawnPos.Y - 2) == nullptr)
			   {
				   Piece* temp2 = game->m_field[PawnPos.X][PawnPos.Y - 1];
				   game->m_field[PawnPos.X][PawnPos.Y - 1] = nullptr;
				   game->m_field[PawnPos.X][PawnPos.Y - 2] = temp2;

				   t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				   if (t == Team::NONE)
				   {
					   Movement m = Movement(Position(PawnPos.X, PawnPos.Y - 2), MoveType::DOUBLEMOVE);
					   doublemove = m.position;
					   moves.push_back(m);

					   Piece* temp3 = game->getFieldPos(PawnPos.X, PawnPos.Y - 2);
					   game->m_field[PawnPos.X][PawnPos.Y - 2] = nullptr;
					   game->m_field[PawnPos.X][PawnPos.Y - 1] = nullptr;
					   game->m_field[PawnPos.X][PawnPos.Y] = temp3;
					   //PossibleMoves = moves;
					   //return;
					   goto blackeating;
				   }
				   else
				   {
					   Piece* temp2 = game->m_field[PawnPos.X][PawnPos.Y - 2];
					   game->m_field[PawnPos.X][PawnPos.Y - 2] = nullptr;
					   game->m_field[PawnPos.X][PawnPos.Y] = temp2;
					   goto blackeating;
				   }
			   }
		   }

		   Piece* temp1 = game->getFieldPos(PawnPos.X, PawnPos.Y - 1);
		   game->m_field[PawnPos.X][PawnPos.Y - 1] = nullptr;
		   game->m_field[PawnPos.X][PawnPos.Y] = temp1;
	   }

	   //-------------------- Eating Part
	   blackeating:
	   if (PawnPos.X - 1 >= 0 && PawnPos.Y - 1 >= 0 && game->getFieldPos(PawnPos.X - 1, PawnPos.Y - 1) != nullptr)
	   {
		   if (game->m_field[PawnPos.X - 1][PawnPos.Y - 1]->GetTeam() != m_team)
		   {
			   Piece* temp = game->getFieldPos(PawnPos.X, PawnPos.Y);
			   Piece* eatenpiece = game->getFieldPos(PawnPos.X - 1, PawnPos.Y - 1);
			   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;
			   game->m_field[PawnPos.X - 1][PawnPos.Y - 1] = temp;

			   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			   if (t == Team::NONE)
			   {
				   Movement m = Movement(Position(PawnPos.X - 1, PawnPos.Y - 1), MoveType::INIT);
				   moves.push_back(m);
			   }

			   Piece* temp1 = game->getFieldPos(PawnPos.X - 1, PawnPos.Y - 1);
			   game->m_field[PawnPos.X - 1][PawnPos.Y - 1] = eatenpiece;
			   game->m_field[PawnPos.X][PawnPos.Y] = temp1;
		   }
	   }
	   if (PawnPos.X + 1 < 8 && PawnPos.Y - 1 >= 0 && game->getFieldPos(PawnPos.X + 1, PawnPos.Y - 1) != nullptr)
	   {
		   if (game->m_field[PawnPos.X + 1][PawnPos.Y - 1]->GetTeam() != m_team)
		   {
			   Piece* temp = game->getFieldPos(PawnPos.X, PawnPos.Y);
			   Piece* eatenpiece = game->getFieldPos(PawnPos.X + 1, PawnPos.Y - 1);
			   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;
			   game->m_field[PawnPos.X + 1][PawnPos.Y - 1] = temp;

			   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			   if (t == Team::NONE)
			   {
				   Movement m = Movement(Position(PawnPos.X + 1, PawnPos.Y - 1), MoveType::INIT);
				   moves.push_back(m);
			   }

			   Piece* temp1 = game->getFieldPos(PawnPos.X + 1, PawnPos.Y - 1);
			   game->m_field[PawnPos.X + 1][PawnPos.Y - 1] = eatenpiece;
			   game->m_field[PawnPos.X][PawnPos.Y] = temp1;
		   }
	   }
   }

   else
   {
	   //-------------------- Normal Move Part
	   if (PawnPos.Y + 1 < 8 && game->getFieldPos(PawnPos.X, PawnPos.Y + 1) == nullptr)
	   {
		   Piece* temp = game->getFieldPos(PawnPos.X, PawnPos.Y);
		   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;
		   game->m_field[PawnPos.X][PawnPos.Y + 1] = temp;

		   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

		   if (t == Team::NONE)
		   {
			   Movement m = Movement(Position(PawnPos.X, PawnPos.Y + 1), MoveType::NORMAL);
			   moves.push_back(m);
		   }

		   if (firstmove)
		   {
			   if (game->getFieldPos(PawnPos.X, PawnPos.Y + 2) == nullptr)
			   {
				   Piece* temp2 = game->m_field[PawnPos.X][PawnPos.Y + 1];
				   game->m_field[PawnPos.X][PawnPos.Y + 1] = nullptr;
				   game->m_field[PawnPos.X][PawnPos.Y + 2] = temp2;

				   t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

				   if (t == Team::NONE)
				   {
					   Movement m = Movement(Position(PawnPos.X, PawnPos.Y + 2), MoveType::DOUBLEMOVE);
					   doublemove = m.position;
					   moves.push_back(m);

					   Piece* temp3 = game->getFieldPos(PawnPos.X, PawnPos.Y + 2);
					   game->m_field[PawnPos.X][PawnPos.Y + 2] = nullptr;
					   game->m_field[PawnPos.X][PawnPos.Y + 1] = nullptr;
					   game->m_field[PawnPos.X][PawnPos.Y] = temp3;
					   //PossibleMoves = moves;
					   //return;
					   goto whiteeating;
				   }
				   else
				   {
					   Piece* temp2 = game->m_field[PawnPos.X][PawnPos.Y + 2];
					   game->m_field[PawnPos.X][PawnPos.Y + 2] = nullptr;
					   game->m_field[PawnPos.X][PawnPos.Y] = temp2;
					   goto whiteeating;
				   }
			   }
		   }

		   Piece* temp1 = game->getFieldPos(PawnPos.X, PawnPos.Y + 1);
		   game->m_field[PawnPos.X][PawnPos.Y + 1] = nullptr;
		   game->m_field[PawnPos.X][PawnPos.Y] = temp1;
	   }

	   //-------------------- Eating Part
       whiteeating:
	   if (PawnPos.X - 1 >= 0 && PawnPos.Y + 1 < 8 && game->getFieldPos(PawnPos.X - 1, PawnPos.Y + 1) != nullptr)
	   {
		   if (game->m_field[PawnPos.X - 1][PawnPos.Y + 1]->GetTeam() != m_team)
		   {
			   Piece* temp = game->getFieldPos(PawnPos.X, PawnPos.Y);
			   Piece* eatenpiece = game->getFieldPos(PawnPos.X - 1, PawnPos.Y + 1);
			   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;
			   game->m_field[PawnPos.X - 1][PawnPos.Y + 1] = temp;

			   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			   if (t == Team::NONE)
			   {
				   Movement m = Movement(Position(PawnPos.X - 1, PawnPos.Y + 1), MoveType::INIT);
				   moves.push_back(m);
			   }

			   Piece* temp1 = game->getFieldPos(PawnPos.X - 1, PawnPos.Y + 1);
			   game->m_field[PawnPos.X - 1][PawnPos.Y + 1] = eatenpiece;
			   game->m_field[PawnPos.X][PawnPos.Y] = temp1;
		   }
	   }
	   if (PawnPos.X + 1 < 8 && PawnPos.Y + 1 < 8 && game->getFieldPos(PawnPos.X + 1, PawnPos.Y + 1) != nullptr)
	   {
		   if (game->m_field[PawnPos.X + 1][PawnPos.Y + 1]->GetTeam() != m_team)
		   {
			   Piece* temp = game->getFieldPos(PawnPos.X, PawnPos.Y);
			   Piece* eatenpiece = game->getFieldPos(PawnPos.X + 1, PawnPos.Y + 1);
			   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;
			   game->m_field[PawnPos.X + 1][PawnPos.Y + 1] = temp;

			   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

			   if (t == Team::NONE)
			   {
				   Movement m = Movement(Position(PawnPos.X + 1, PawnPos.Y + 1), MoveType::INIT);
				   moves.push_back(m);
			   }

			   Piece* temp1 = game->getFieldPos(PawnPos.X + 1, PawnPos.Y + 1);
			   game->m_field[PawnPos.X + 1][PawnPos.Y + 1] = eatenpiece;
			   game->m_field[PawnPos.X][PawnPos.Y] = temp1;
		   }
	   }
   }

   //-------------------- EnPassant Part
   if (EnpassantPossibility == 0)
   {
	   game->m_field[EnpassantPos[0].X][EnpassantPos[0].Y] = game->m_field[PawnPos.X][PawnPos.Y];
	   game->m_field[PawnPos.X][PawnPos.Y] = nullptr;

	   Team t = game->CheckIfItsCheck(GetOwningKing(game->m_field)).t;

	   if (t == Team::NONE)
	   {
		   Movement m = Movement(EnpassantPos[0], MoveType::ENPASSANT);
		   moves.push_back(m);
	   }

	   game->m_field[PawnPos.X][PawnPos.Y] = game->m_field[EnpassantPos[0].X][EnpassantPos[0].Y];
	   game->m_field[EnpassantPos[0].X][EnpassantPos[0].Y] = nullptr;

	   EnpassantPossibility = -1;
   }

   PossibleMoves = moves;
}

void Pawn::NormalMove(Movement m)
{
}
