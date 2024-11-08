#include "pch.h"
#include "Demo.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
 {
	Demo app;
	app.Setup({ 1600,900 }, { 100, 50 });
	app.Run();

	return 0;
}