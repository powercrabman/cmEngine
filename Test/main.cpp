#include <iostream>
#include <d3d11.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include "SimpleMath.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "DirectXTK.lib")

int main()
{
	using namespace DirectX::SimpleMath;
	using namespace std;
	Vector3 v = Vector3::One;

	cout << v.x << endl;
	cout << v.y << endl;
	cout << v.z << endl;
}