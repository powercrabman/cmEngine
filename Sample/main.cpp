#include "pch.h"
#include "App.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	App app;
	app.Setup({ 1600, 900 });
	app.Run();

	return 0;
}