#include "pch.h"
#include "Demo.h"

const Vector3 DirectX::SimpleMath::Vector3::Zero = { 0.f,0.f,0.f };
const Vector3 DirectX::SimpleMath::Vector3::One = { 1.f,1.f,1.f };

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Demo app;
	app.Setup({ 1600,900 }, { 100, 50 });
	app.Run();

	return 0;
}