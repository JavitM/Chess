#include "Game.h"
#include "Piece.h"
#include <iostream> // X

Game::Game(SDL_Handler* handler)
    :
    pl1(new Pawn(Team::WHITE, Position(0,1), handler,PieceType::PAWN)),
    pl2(new Pawn(Team::WHITE, Position(1, 1), handler, PieceType::PAWN)),
    pl3(new Pawn(Team::WHITE, Position(2, 1), handler, PieceType::PAWN)),
    pl4(new Pawn(Team::WHITE, Position(3, 1), handler, PieceType::PAWN)),
    pl5(new Pawn(Team::WHITE, Position(4, 1), handler, PieceType::PAWN)),
    pl6(new Pawn(Team::WHITE, Position(5, 1), handler, PieceType::PAWN)),
    pl7(new Pawn(Team::WHITE, Position(6, 1), handler, PieceType::PAWN)),
    pl8(new Pawn(Team::WHITE, Position(7, 1), handler, PieceType::PAWN)),
    pb1(new Pawn(Team::BLACK, Position(0, 6), handler, PieceType::PAWN)),
    pb2(new Pawn(Team::BLACK, Position(1, 6), handler, PieceType::PAWN)),
    pb3(new Pawn(Team::BLACK, Position(2, 6), handler, PieceType::PAWN)), 
    pb4(new Pawn(Team::BLACK, Position(3, 6), handler, PieceType::PAWN)),
    pb5(new Pawn(Team::BLACK, Position(4, 6), handler, PieceType::PAWN)), 
    pb6(new Pawn(Team::BLACK, Position(5, 6), handler, PieceType::PAWN)),
    pb7(new Pawn(Team::BLACK, Position(6, 6), handler, PieceType::PAWN)),
    pb8(new Pawn(Team::BLACK, Position(7, 6), handler, PieceType::PAWN)),
    rb1(new Rook(Team::BLACK, Position(0, 7), handler, PieceType::ROOK)),
    rb2(new Rook(Team::BLACK, Position(7, 7), handler, PieceType::ROOK)),
    rl1(new Rook(Team::WHITE, Position(0, 0), handler, PieceType::ROOK)),
    rl2(new Rook(Team::WHITE, Position(7, 0), handler, PieceType::ROOK)),
    nb1(new Knight(Team::BLACK, Position(1, 7), handler, PieceType::KNIGHT)),
    nb2(new Knight(Team::BLACK, Position(6, 7), handler, PieceType::KNIGHT)),
    nl1(new Knight(Team::WHITE, Position(1, 0), handler, PieceType::KNIGHT)),
    nl2(new Knight(Team::WHITE, Position(6, 0), handler, PieceType::KNIGHT)),
    bb1(new Bishop(Team::BLACK, Position(2, 7), handler, PieceType::BISHOP)),
    bb2(new Bishop(Team::BLACK, Position(5, 7), handler, PieceType::BISHOP)),
    bl1(new Bishop(Team::WHITE, Position(2, 0), handler, PieceType::BISHOP)),
    bl2(new Bishop(Team::WHITE, Position(5, 0), handler, PieceType::BISHOP)),
    kb1(new King(Team::BLACK, Position(3, 7), handler, PieceType::KING)), // 4, 7 
    kl1(new King(Team::WHITE, Position(3, 0), handler, PieceType::KING)), // 4, 0
    qb1(new Queen(Team::BLACK, Position(4, 7), handler, PieceType::QUEEN)), // 3, 7
    ql1(new Queen(Team::WHITE, Position(4, 0), handler, PieceType::QUEEN)), // 3, 0
    m_handler(handler),
    m_checkEnPassant(true)
{
    m_field[0][7] = rb1;
    m_field[7][7] = rb2;
    m_field[0][0] = rl1;
    m_field[7][0] = rl2;

    m_field[1][7] = nb1;
    m_field[6][7] = nb2;
    m_field[1][0] = nl1;
    m_field[6][0] = nl2;

    m_field[2][7] = bb1;
    m_field[5][7] = bb2;
    m_field[2][0] = bl1;
    m_field[5][0] = bl2;

    m_field[3][7] = kb1; //
    m_field[3][0] = kl1;

    m_field[4][7] = qb1;
    m_field[4][0] = ql1; //

    m_field[0][1] = pl1;
    m_field[1][1] = pl2;
    m_field[2][1] = pl3;
    m_field[3][1] = pl4;
    m_field[4][1] = pl5;
    m_field[5][1] = pl6;
    m_field[6][1] = pl7;
    m_field[7][1] = pl8;

    m_field[0][6] = pb1;
    m_field[1][6] = pb2;
    m_field[2][6] = pb3; 
    m_field[3][6] = pb4;
    m_field[4][6] = pb5;
    m_field[5][6] = pb6;
    m_field[6][6] = pb7;
    m_field[7][6] = pb8;

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            m_field[j][i] = nullptr;
        }
    }
    m_turn = Team::WHITE;
    CalculatePossibleMoves(true);
}

Game::~Game()
{
}

void Game::move(Piece* piece, Position pos)
{
    if (piece->GetTeam() == m_turn)
    {
        Team check;
        if (m_turn == Team::BLACK) { check = blackkingcheckdata.t; }
        else { check = whitekingcheckdata.t; }

        {
            MoveStatement state = piece->Move(pos, check);
            if (state.bCanMove)
            {
                if (state.movetype == MoveType::NORMAL || state.movetype == MoveType::DOUBLEMOVE)
                {
                    Position oldp = piece->GetPosition();
                    m_handler->undoPieceRender(piece->GetPosition().X, piece->GetPosition().Y);
                    piece->SetPosition(pos.X, pos.Y);
                    m_field[pos.X][pos.Y] = piece;
                    m_field[oldp.X][oldp.Y] = nullptr;
                    piece->Render();
                    if (state.movetype == MoveType::DOUBLEMOVE)
                    {
                        Pawn* p = (Pawn*)piece;
                        p->EnPassant(this);
                    }
                }
                else if (state.movetype == MoveType::INIT)
                {
                    Position oldp = piece->GetPosition();
                    m_handler->undoPieceRender(piece->GetPosition().X, piece->GetPosition().Y);
                    m_handler->undoPieceRender(pos.X, pos.Y);
                    delete m_field[pos.X][pos.Y];
                    piece->SetPosition(pos.X, pos.Y);
                    m_field[pos.X][pos.Y] = piece;
                    m_field[oldp.X][oldp.Y] = nullptr;
                    piece->Render();
                }
                else if (state.movetype == MoveType::LONGCASTLE)
                {
                    if (piece->GetTeam() == Team::BLACK)
                    {
                        m_field[5][7] = m_field[3][7];
                        m_field[4][7] = m_field[7][7];

                        m_field[3][7] = nullptr;
                        m_field[7][7] = nullptr;

                        m_handler->undoPieceRender(3, 7);
                        m_handler->undoPieceRender(7, 7);
                        m_field[5][7]->SetPosition(5, 7);
                        m_field[4][7]->SetPosition(4, 7);
                        m_field[5][7]->Render();
                        m_field[4][7]->Render();
                    }
                    else
                    {
                        m_field[5][0] = m_field[3][0];
                        m_field[4][0] = m_field[7][0];

                        m_field[3][0] = nullptr;
                        m_field[7][0] = nullptr;

                        m_handler->undoPieceRender(3, 0);
                        m_handler->undoPieceRender(7, 0);
                        m_field[5][0]->SetPosition(5, 0);
                        m_field[4][0]->SetPosition(4, 0);
                        m_field[5][0]->Render();
                        m_field[4][0]->Render();
                    }
                }
                else if (state.movetype == MoveType::SHORTCASTLE)
                {
                    if (piece->GetTeam() == Team::BLACK)
                    {
                        m_field[1][7] = m_field[3][7];
                        m_field[2][7] = m_field[0][7];

                        m_field[3][7] = nullptr;
                        m_field[0][7] = nullptr;

                        m_handler->undoPieceRender(3, 7);
                        m_handler->undoPieceRender(0, 7);
                        m_field[1][7]->SetPosition(1, 7);
                        m_field[2][7]->SetPosition(2, 7);
                        m_field[1][7]->Render();
                        m_field[2][7]->Render();
                    }
                    else
                    {
                        m_field[1][0] = m_field[3][0];
                        m_field[2][0] = m_field[0][0];

                        m_field[3][0] = nullptr;
                        m_field[0][0] = nullptr;

                        m_handler->undoPieceRender(3, 0);
                        m_handler->undoPieceRender(0, 0);
                        m_field[1][0]->SetPosition(1, 0);
                        m_field[2][0]->SetPosition(2, 0);
                        m_field[1][0]->Render();
                        m_field[2][0]->Render();
                    }
                }

                if (piece->GetPieceType() == PieceType::PAWN)
                {
                    Pawn* p = (Pawn*)piece;

                    if (state.movetype == MoveType::ENPASSANT)
                    {
                        Position oldp = piece->GetPosition();
                        m_handler->undoPieceRender(piece->GetPosition().X, piece->GetPosition().Y);
                        m_handler->undoPieceRender(p->GetEnpassantPos(1).X, p->GetEnpassantPos(1).Y);
                        delete m_field[p->GetEnpassantPos(1).X][p->GetEnpassantPos(1).Y];
                        piece->SetPosition(p->GetEnpassantPos(0).X, p->GetEnpassantPos(0).Y);
                        m_field[p->GetEnpassantPos(0).X][p->GetEnpassantPos(0).Y] = piece;
                        m_field[oldp.X][oldp.Y] = nullptr;
                        m_field[p->GetEnpassantPos(1).X][p->GetEnpassantPos(1).Y] = nullptr;
                        piece->Render();

                        p->SetEnpassantPossibility(1);
                    }

                    if (p->CanExchange())
                    {
                        SDL_Texture* text_rook = nullptr;
                        SDL_Texture* text_knight = nullptr;
                        SDL_Texture* text_bishop = nullptr;
                        SDL_Texture* text_queen = nullptr;

                        int y_draw = 0;
                        Team team = Team::WHITE;

                        if (p->GetTeam() == Team::BLACK)
                        {
                            text_rook = m_handler->loadImage("icons/black_rook.png");
                            text_knight = m_handler->loadImage("icons/black_knight.png");
                            text_bishop = m_handler->loadImage("icons/black_bishop.png");
                            text_queen = m_handler->loadImage("icons/black_queen.png");
                            y_draw = 3 * m_handler->SCREEN_HEIGHT / 4;
                            team = Team::BLACK;
                        }
                        else
                        {
                            text_rook = m_handler->loadImage("icons/white_rook.png");
                            text_knight = m_handler->loadImage("icons/white_knight.png");
                            text_bishop = m_handler->loadImage("icons/white_bishop.png");
                            text_queen = m_handler->loadImage("icons/white_queen.png");
                        }

                        SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
                        SDL_Rect rectangle = { 0,
                                              y_draw,
                                              m_handler->SCREEN_WIDTH / 4,
                                              m_handler->SCREEN_HEIGHT / 4 };
                        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
                        SDL_Rect src = { 0, 0, 60, 60 };
                        m_handler->DrawRectangle(src, rectangle, text_rook);

                        SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
                        rectangle.x = m_handler->SCREEN_WIDTH / 4;
                        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
                        m_handler->DrawRectangle(src, rectangle, text_knight);

                        SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
                        rectangle.x = 2 * m_handler->SCREEN_WIDTH / 4;
                        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
                        m_handler->DrawRectangle(src, rectangle, text_bishop);

                        SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
                        rectangle.x = 3 * m_handler->SCREEN_WIDTH / 4;
                        SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
                        m_handler->DrawRectangle(src, rectangle, text_queen);

                        bool quit = false;
                        int x = -1;
                        int y = -1;

                        Piece* clickedOn = nullptr;

                        std::cout << m_handler;

                        while (quit == false)
                        {
                            while (SDL_WaitEvent(&m_handler->m_event))
                            {
                                if (m_handler->m_event.type == SDL_QUIT)
                                {
                                    quit = true;
                                }

                                if (m_handler->m_event.type == SDL_MOUSEBUTTONDOWN)
                                {
                                    x = m_handler->m_event.button.x / 160;
                                    y = m_handler->m_event.button.y / 160;

                                    if (y >= y_draw / 160 && y < y_draw / 160 + 1)
                                    {
                                        if (x < m_handler->SCREEN_WIDTH / 640)
                                        {
                                            clickedOn = new Rook(piece->GetTeam(), piece->GetPosition(), m_handler, PieceType::ROOK);
                                        }
                                        else if (x < 2 * m_handler->SCREEN_WIDTH / 640)
                                        {
                                            clickedOn = new Knight(piece->GetTeam(), piece->GetPosition(), m_handler, PieceType::KNIGHT);
                                        }
                                        else if (x < 3 * m_handler->SCREEN_WIDTH / 640)
                                        {
                                            clickedOn = new Bishop(piece->GetTeam(), piece->GetPosition(), m_handler, PieceType::BISHOP);
                                        }
                                        else if (x <= 4 * m_handler->SCREEN_WIDTH / 640)
                                        {
                                            clickedOn = new Queen(piece->GetTeam(), piece->GetPosition(), m_handler, PieceType::QUEEN);
                                        }
                                        quit = true;
                                        break;
                                        std::cout << x << " " << m_handler->SCREEN_WIDTH / 640 << std::endl;
                                    }
                                }

                                if (m_handler->m_event.type == SDL_MOUSEBUTTONUP && clickedOn != nullptr)
                                {
                                    quit = true;
                                }
                            }
                        }
                        delete piece;
                        piece = clickedOn;
                        m_field[piece->GetPosition().X][piece->GetPosition().Y] = piece;
                        m_handler->undoPieceRender(piece->GetPosition().X, piece->GetPosition().Y);
                        m_handler->renderBackground();

                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                if (m_field[i][j] != nullptr)
                                {
                                    m_field[i][j]->Render();
                                }
                            }
                        }

                        SDL_DestroyTexture(text_rook);
                        SDL_DestroyTexture(text_bishop);
                        SDL_DestroyTexture(text_knight);
                        SDL_DestroyTexture(text_queen);
                    }
                }

                if (m_turn == Team::BLACK) { m_turn = Team::WHITE; printf("white turn\n"); }
                else { m_turn = Team::BLACK; printf("black turn\n"); }

                CalculatePossibleMoves(true);
            }
        }
    }
}

Piece* Game::getFieldPos(int row, int col)
{
    return m_field[row][col];
}

CheckIfData Game::CheckIfItsCheck(Piece* King)
{
    CheckIfData data = CheckIfData();
    data.checkside = Side::NOSIDE;
    data.t = Team::NONE;
    Team ENEMY;
    Position Coordinate = King->GetPosition();
    if (King->GetTeam() == Team::BLACK) { ENEMY = Team::WHITE; }
    else { ENEMY = Team::BLACK; }
    int ItsCheckInX = 0; int ItsCheckInTopDiagonal = 0; int ItsCheckInBottomDiagonal = 0;

    if (Coordinate.X - 1 >= 0 && Coordinate.Y - 1 >= 0 && m_field[Coordinate.X - 1][Coordinate.Y - 1])
    {
        if (m_field[Coordinate.X - 1][Coordinate.Y - 1]->GetTeam() == ENEMY)
        {
            if (ENEMY == Team::WHITE)
            {
                if (m_field[Coordinate.X - 1][Coordinate.Y - 1]->GetPieceType() == PieceType::PAWN)
                {
                    std::cout << "Its Check In Left Pawn Coordinate \n";
                    data.checkside = Side::BlackLeftPawn;
                    data.checkcount++;
                    data.t = ENEMY;
                    return data;
                }
            }

            if (m_field[Coordinate.X - 1][Coordinate.Y - 1]->GetPieceType() == PieceType::KING)
            {
                std::cout << "Its Check In K1 Coordinate \n";
                data.checkside = Side::K1;
                data.checkcount++;
                data.t = ENEMY;
                return data;
            }
        }
    }
    if (Coordinate.X + 1 < 8 && Coordinate.Y - 1 >= 0 && m_field[Coordinate.X + 1][Coordinate.Y - 1])
    {
        if (m_field[Coordinate.X + 1][Coordinate.Y - 1]->GetTeam() == ENEMY)
        {
            if (ENEMY == Team::WHITE)
            {
                if (m_field[Coordinate.X + 1][Coordinate.Y - 1]->GetPieceType() == PieceType::PAWN)
                {
                    std::cout << "Its Check In Right Pawn Coordinate \n";
                    data.checkside = Side::BlackRightPawn;
                    data.checkcount++;
                    data.t = ENEMY;
                    return data;
                }
            }

            if (m_field[Coordinate.X + 1][Coordinate.Y - 1]->GetPieceType() == PieceType::KING)
            {
                std::cout << "Its Check In K3 Coordinate \n";
                data.checkside = Side::K3;
                data.checkcount++;
                data.t = ENEMY;
                return data;
            }
        }
    }
    
    if (Coordinate.X - 1 >= 0 && Coordinate.Y + 1 < 8 && m_field[Coordinate.X - 1][Coordinate.Y + 1])
    {
        if (ENEMY == Team::BLACK)
        {
            if (m_field[Coordinate.X - 1][Coordinate.Y + 1]->GetTeam() == ENEMY && m_field[Coordinate.X - 1][Coordinate.Y + 1]->GetPieceType() == PieceType::PAWN)
            {
                std::cout << "Its Check In Left Pawn Coordinate \n";
                data.checkside = Side::WhiteLeftPawn;
                data.checkcount++;
                data.t = ENEMY;
                return data;
            }
        }
        if (m_field[Coordinate.X - 1][Coordinate.Y + 1]->GetTeam() == ENEMY && m_field[Coordinate.X - 1][Coordinate.Y + 1]->GetPieceType() == PieceType::KING)
        {
            std::cout << "Its Check In K6 Coordinate \n";
            data.checkside = Side::K6;
            data.checkcount++;
            data.t = ENEMY;
            return data;
        }
    }
    if (Coordinate.X + 1 < 8 && Coordinate.Y + 1 < 8 && m_field[Coordinate.X + 1][Coordinate.Y + 1])
    {
        if (ENEMY == Team::BLACK)
        {
            if (m_field[Coordinate.X + 1][Coordinate.Y + 1]->GetTeam() == ENEMY && m_field[Coordinate.X + 1][Coordinate.Y + 1]->GetPieceType() == PieceType::PAWN)
            {
                std::cout << "Its Check In Right Pawn Coordinate \n";
                data.checkside = Side::WhiteRightPawn;
                data.checkcount++;
                data.t = ENEMY;
                return data;
            }
        }

        if (m_field[Coordinate.X + 1][Coordinate.Y + 1]->GetTeam() == ENEMY && m_field[Coordinate.X + 1][Coordinate.Y + 1]->GetPieceType() == PieceType::KING)
        {
            std::cout << "Its Check In K8 Coordinate \n";
            data.checkside = Side::K8;
            data.checkcount++;
            data.t = ENEMY;
            return data;
        }
    }

    if (Coordinate.X - 1 >= 0 && Coordinate.Y - 2 >= 0 && m_field[Coordinate.X - 1][Coordinate.Y - 2])
    {
        if (m_field[Coordinate.X - 1][Coordinate.Y - 2]->GetTeam() == ENEMY && m_field[Coordinate.X - 1][Coordinate.Y - 2]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Top Left Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::A;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X + 1 < 8 && Coordinate.Y - 2 >= 0 && m_field[Coordinate.X + 1][Coordinate.Y - 2])
    {
        if (m_field[Coordinate.X + 1][Coordinate.Y - 2]->GetTeam() == ENEMY && m_field[Coordinate.X + 1][Coordinate.Y - 2]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Top Right Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::B;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X - 2 >= 0 && Coordinate.Y - 1 >= 0 && m_field[Coordinate.X - 2][Coordinate.Y - 1])
    {
        if (m_field[Coordinate.X - 2][Coordinate.Y - 1]->GetTeam() == ENEMY && m_field[Coordinate.X - 2][Coordinate.Y - 1]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Left Top Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::C;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X + 2 < 8 && Coordinate.Y - 1 >= 0 && m_field[Coordinate.X + 2][Coordinate.Y - 1])
    {
        if (m_field[Coordinate.X + 2][Coordinate.Y - 1]->GetTeam() == ENEMY && m_field[Coordinate.X + 2][Coordinate.Y - 1]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Right Top Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::D;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X - 2 >= 0 && Coordinate.Y + 1 < 8 && m_field[Coordinate.X - 2][Coordinate.Y + 1])
    {
        if (m_field[Coordinate.X - 2][Coordinate.Y + 1]->GetTeam() == ENEMY && m_field[Coordinate.X - 2][Coordinate.Y + 1]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Left Bottom Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::E;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X + 2 < 8 && Coordinate.Y + 1 < 8 && m_field[Coordinate.X + 2][Coordinate.Y + 1])
    {
        if (m_field[Coordinate.X + 2][Coordinate.Y + 1]->GetTeam() == ENEMY && m_field[Coordinate.X + 2][Coordinate.Y + 1]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Right Bottom Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::F;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X - 1 >= 0 && Coordinate.Y + 2 < 8 && m_field[Coordinate.X - 1][Coordinate.Y + 2])
    {
        if (m_field[Coordinate.X - 1][Coordinate.Y + 2]->GetTeam() == ENEMY && m_field[Coordinate.X - 1][Coordinate.Y + 2]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Bottom Left Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::G;
            data.t = ENEMY;
            //return data;
        }
    }
    if (Coordinate.X + 1 < 8 && Coordinate.Y + 2 < 8 && m_field[Coordinate.X + 1][Coordinate.Y + 2])
    {
        if (m_field[Coordinate.X + 1][Coordinate.Y + 2]->GetTeam() == ENEMY && m_field[Coordinate.X + 1][Coordinate.Y + 2]->GetPieceType() == PieceType::KNIGHT)
        {
            std::cout << "Its Check In Bottom Right Knight Coordinate \n";
            data.checkcount++;
            data.checkside = Side::H;
            data.t = ENEMY;
            //return data;
        }
    }


    for (int YToTop = Coordinate.Y+1; YToTop < 8; YToTop++)
    {
        if (m_field[Coordinate.X][YToTop] != nullptr)
        {
            if (m_field[Coordinate.X][YToTop]->GetTeam() == ENEMY)
            {
                if (YToTop == Coordinate.Y + 1)
                {
                    if (m_field[Coordinate.X][YToTop]->GetPieceType() == PieceType::KING)
                    {
                        std::cout << "Its Check In Y + 1 KING Coordinate \n";
                        //return ENEMY;

                        data.checkcount++;
                        data.t = ENEMY;
                        data.checkside = Side::K7;
                        return data;
                    }
                }

                if (m_field[Coordinate.X][YToTop]->GetPieceType() == PieceType::QUEEN || m_field[Coordinate.X][YToTop]->GetPieceType() == PieceType::ROOK)
                {
                    std::cout << "Its Check In Y Coordinate \n";
                    //return ENEMY;

                    data.checkcount++;
                    data.t = ENEMY;
                    data.checkside = Side::TopY;
                    return data;
                }
                break;
            }
            else
            {
                std::cout << "Its Not Check Y + 1 \n";
                break;
            }
        }
    }
    for (int YToTop = Coordinate.Y-1; YToTop >= 0; YToTop--)
    {
        if (m_field[Coordinate.X][YToTop] != nullptr)
        {
            if (m_field[Coordinate.X][YToTop]->GetTeam() == ENEMY)
            {
                if (YToTop == Coordinate.Y - 1)
                {
                    if (m_field[Coordinate.X][YToTop]->GetPieceType() == PieceType::KING)
                    {
                        std::cout << "Its Check In Y - 1 KING Coordinate \n";
                        //return ENEMY;

                        data.checkcount++;
                        data.t = ENEMY;
                        data.checkside = Side::K2;
                        return data;
                    }
                }

                if (m_field[Coordinate.X][YToTop]->GetPieceType() == PieceType::QUEEN || m_field[Coordinate.X][YToTop]->GetPieceType() == PieceType::ROOK)
                {
                    std::cout << "Its Check In Y Coordinate \n";
                    //return ENEMY;

                    data.checkcount++;
                    data.t = ENEMY;
                    data.checkside = Side::BottomY;
                    return data;
                }
                break;
            }
            else
            {
                std::cout << "Its Not Check \n";
                break;
            }
        }
    }

    for (int XToTop = Coordinate.X + 1; XToTop < 8; XToTop++)
    {
        int DistanceBetweenKing = XToTop - Coordinate.X;

        if (ItsCheckInX == 0)
        {
            if (m_field[XToTop][Coordinate.Y] != nullptr)
            {
                if (m_field[XToTop][Coordinate.Y]->GetTeam() == ENEMY)
                {
                    if (XToTop == Coordinate.X + 1)
                    {
                        if (m_field[XToTop][Coordinate.Y]->GetPieceType() == PieceType::KING)
                        {
                            std::cout << "Its Check In X + 1 KING Coordinate \n";
                            //return ENEMY;

                            data.checkcount++;
                            data.t = ENEMY;
                            data.checkside = Side::K5;
                            return data;
                        }
                    }

                    if (m_field[XToTop][Coordinate.Y]->GetPieceType() == PieceType::QUEEN || m_field[XToTop][Coordinate.Y]->GetPieceType() == PieceType::ROOK)
                    {
                        std::cout << "Its Check In X Coordinate \n";
                        //return ENEMY;

                        data.checkcount++;
                        data.t = ENEMY;
                        data.checkside = Side::TopX;
                        return data;
                    }
                    ItsCheckInX = 1;
                }
                else
                {
                    std::cout << "Its Not Check X + 1 \n";
                    ItsCheckInX = 1;
                }
            }
        }


        if (ItsCheckInBottomDiagonal == 0)
        {
            if (Coordinate.Y + DistanceBetweenKing < 8 && Coordinate.Y + DistanceBetweenKing >= 0)
            {
                if (m_field[XToTop][Coordinate.Y + DistanceBetweenKing] != nullptr)
                {
                    if (m_field[XToTop][Coordinate.Y + DistanceBetweenKing]->GetTeam() == ENEMY)
                    {
                        if (m_field[XToTop][Coordinate.Y + DistanceBetweenKing]->GetPieceType() == PieceType::QUEEN
                            || m_field[XToTop][Coordinate.Y + DistanceBetweenKing]->GetPieceType() == PieceType::BISHOP)
                        {
                            std::cout << "Its Check In Right Bottom Diagonal \n";
                            //return ENEMY;

                            data.checkcount++;
                            data.t = ENEMY;
                            data.checkside = Side::RightBottomDiagonal;
                            return data;
                        }
                    }
                    ItsCheckInBottomDiagonal = 1;
                }
            }
        }

        if (ItsCheckInTopDiagonal == 0)
        {
            if (Coordinate.Y - DistanceBetweenKing < 8 && Coordinate.Y - DistanceBetweenKing >= 0)
            {
                if (m_field[XToTop][Coordinate.Y - DistanceBetweenKing] != nullptr)
                {
                    if (m_field[XToTop][Coordinate.Y - DistanceBetweenKing]->GetTeam() == ENEMY)
                    {
                        if (m_field[XToTop][Coordinate.Y - DistanceBetweenKing]->GetPieceType() == PieceType::QUEEN
                            || m_field[XToTop][Coordinate.Y - DistanceBetweenKing]->GetPieceType() == PieceType::BISHOP)
                        {
                            std::cout << "Its Check In Right Top Diagonal \n";
                            //return ENEMY;

                            data.checkcount++;
                            data.t = ENEMY;
                            data.checkside = Side::RightTopDiagonal;
                            return data;
                        }
                    }
                    ItsCheckInTopDiagonal = 1;
                }
            }
        }
    }

    ItsCheckInX = 0; ItsCheckInTopDiagonal = 0; ItsCheckInBottomDiagonal = 0;

    for (int XToTop = Coordinate.X - 1; XToTop >= 0; XToTop--)
    {
        int DistanceBetweenKing = Coordinate.X - XToTop;

        if (ItsCheckInX == 0)
        {
            if (m_field[XToTop][Coordinate.Y] != nullptr)
            {
                if (m_field[XToTop][Coordinate.Y]->GetTeam() == ENEMY)
                {
                    if (XToTop == Coordinate.X - 1)
                    {
                        if (m_field[XToTop][Coordinate.Y]->GetPieceType() == PieceType::KING)
                        {
                            std::cout << "Its Check In X - 1 KING Coordinate \n";
                            //return ENEMY;

                            data.checkcount++;
                            data.t = ENEMY;
                            data.checkside = Side::K4;
                            return data;
                        }
                    }

                    if (m_field[XToTop][Coordinate.Y]->GetPieceType() == PieceType::QUEEN || m_field[XToTop][Coordinate.Y]->GetPieceType() == PieceType::ROOK)
                    {
                        std::cout << "Its Check In X Coordinate \n";
                        //return ENEMY;

                        data.checkcount++;
                        data.t = ENEMY;
                        data.checkside = Side::BottomX;
                        return data;
                    }
                    ItsCheckInX = 1;
                }
                else
                {
                    std::cout << "Its Not Check X - 1 \n";
                    ItsCheckInX = 1;
                }
            }
        }

        if (ItsCheckInBottomDiagonal == 0)
        {
            if (Coordinate.Y + DistanceBetweenKing < 8 && Coordinate.Y + DistanceBetweenKing >= 0)
            {
                if (m_field[XToTop][Coordinate.Y + DistanceBetweenKing] != nullptr)
                {
                    if (m_field[XToTop][Coordinate.Y + DistanceBetweenKing]->GetTeam() == ENEMY)
                    {
                        if (m_field[XToTop][Coordinate.Y + DistanceBetweenKing]->GetPieceType() == PieceType::QUEEN
                            || m_field[XToTop][Coordinate.Y + DistanceBetweenKing]->GetPieceType() == PieceType::BISHOP)
                        {
                            std::cout << "Its Check In Left Bottom Diagonal \n";
                            //return ENEMY;

                            data.checkcount++;
                            data.t = ENEMY;
                            data.checkside = Side::LeftBotomDiagonal;
                            return data;
                        }
                    }
                    ItsCheckInBottomDiagonal = 1;
                }
            }
        }

        if (ItsCheckInTopDiagonal == 0)
        {
            if (Coordinate.Y - DistanceBetweenKing < 8 && Coordinate.Y - DistanceBetweenKing >= 0)
            {
                if (m_field[XToTop][Coordinate.Y - DistanceBetweenKing] != nullptr)
                {
                    if (m_field[XToTop][Coordinate.Y - DistanceBetweenKing]->GetTeam() == ENEMY)
                    {
                        if (m_field[XToTop][Coordinate.Y - DistanceBetweenKing]->GetPieceType() == PieceType::QUEEN
                            || m_field[XToTop][Coordinate.Y - DistanceBetweenKing]->GetPieceType() == PieceType::BISHOP)
                        {
                            std::cout << "Its Check In Left Top Diagonal \n";
                            //return ENEMY;

                            data.checkcount++;
                            data.t = ENEMY;
                            data.checkside = Side::LeftTopDiagonal;
                            return data;
                        }
                    }
                    ItsCheckInTopDiagonal = 1;
                }
            }
        }
    }
    return data;
}

void Game::CalculatePossibleMoves(bool bByTurn)
{
    int blackpieces = 0;
    int whitepieces = 0;
    int blacknopossiblemove = 0;
    int whitenopossiblemove = 0;
    if (m_turn == Team::BLACK)
    {
       blackkingcheckdata = CheckIfItsCheck(kb1);
    }
    else
    {
        whitekingcheckdata = CheckIfItsCheck(kl1);
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (m_field[i][j] != nullptr)
            {
                if (m_field[i][j]->GetTeam() == m_turn)
                {
                    if (m_field[i][j]->GetTeam() == Team::BLACK)
                    {
                        m_field[i][j]->SetPossibleMoves(this, blackkingcheckdata);
                        blackpieces++;

                        if (m_field[i][j]->GetPossibleMoves().size() == 0)
                        {
                            blacknopossiblemove++;
                        }
                    }
                    else
                    {
                        m_field[i][j]->SetPossibleMoves(this, whitekingcheckdata);
                        whitepieces++;

                        if (m_field[i][j]->GetPossibleMoves().size() == 0)
                        {
                            whitenopossiblemove++;
                        }
                    }
                }
            }
        }
    }

    if (m_turn == Team::BLACK)
    {
        if (blackpieces == blacknopossiblemove)
        {
            if (blackkingcheckdata.checkcount > 0)
            {
                printf("White Wins !\n");
            }
            else
            {
                printf("Its Stalemate!\n");
            }
        }
    }
    else
    {
        if (whitepieces == whitenopossiblemove)
        {
            if (whitekingcheckdata.checkcount > 0)
            {
                printf("Black Wins !\n");
            }
            else
            {
                printf("Its Stalemate!\n");
            }
        }
    }
}

