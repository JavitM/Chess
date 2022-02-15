#include <iostream>
#include "MainLoop.h"
#include "SDL_Handler.h"
#include "Piece.h"
#include "Game.h"
void Chess::Run()
{
	SDL_Handler handler;

	bool quit = false;

	handler.init();
	handler.renderBackground();

	int imgflag = IMG_INIT_PNG;

	int initted = IMG_Init(imgflag);
	if ((initted & imgflag) != imgflag) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		return;
	}

	int xStart = 0;
	int yStart = 0;

	Game* MainGame = new Game(&handler);

	Piece* selectedpiece = nullptr;
	while (!quit)
	{
		while (SDL_WaitEvent(&handler.m_event))
		{
			if (handler.m_event.type == SDL_QUIT)
			{
				quit = true;
				printf("quit\n");
			}
			else if (handler.m_event.type == SDL_MOUSEBUTTONDOWN)
			{
				xStart = handler.m_event.button.x / 80;
				yStart = handler.m_event.button.y / 80;
				selectedpiece = MainGame->getFieldPos(xStart, yStart);
				if (selectedpiece != nullptr)
				{
					//if (selectedpiece->getTeam() == selectedpiece->getTurn())
					//{
					//	game->renderPossibleMoves(selectedpiece);
					//}
					std::cout << "Selected Piece Is At " << xStart << " " << yStart << "\n";
					if (selectedpiece->GetTeam() == MainGame->getTurn())
					{
						std::cout << "This Piece Can Move\n";
					}
				}

			}
			// Test For Piece Movement
			else if (handler.m_event.type == SDL_MOUSEBUTTONUP)
			{
				xStart = handler.m_event.button.x / 80;
				yStart = handler.m_event.button.y / 80;

				if (selectedpiece != nullptr)
				{
					if (xStart == selectedpiece->GetPosition().X && yStart == selectedpiece->GetPosition().Y)
					{
						continue;
					}
					MainGame->move(selectedpiece, Position(xStart, yStart));
				}
			}

			else
			{
				break;
			}
		}
	}
}