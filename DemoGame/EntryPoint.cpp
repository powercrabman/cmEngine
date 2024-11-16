#include "pch.h"
#include "Game.h"


int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game = {};
	game.Setup({ 1280, 720 }, { 100, 100 });
	game.Run();

	return 0;
}