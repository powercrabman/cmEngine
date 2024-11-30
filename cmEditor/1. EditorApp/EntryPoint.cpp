#include "0. cmEditor/cmEditor.h"
#include "EditorApp.h"

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	EditorApp game = {};
	ApplicationProp prop = {};
	prop.titleName = L"MyEditor";
	prop.windowPosition = { .X = 100, .Y = 50 };
	prop.windowResolution = { .Width = 1280, .Height = 720 };

	game.Setup(prop);
	return game.Run();
}