#include "pch.h"
#include "Game.h"

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Game game = {};
	game.Setup(ApplicationProp{
	.windowResolution = cmEngine::WindowResolution{1600, 900},
	.windowPosition = cmEngine::WindowPosition{100, 50},
	.titleName = L"DemoGame"
	});

	game.Run();

	return 0;
}