#pragma once

//============================
// 엔진 및 클라이언트에서 전역적으로 사용
//============================

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

//Windows
#include <Windows.h>

//STD & STL
#include <array>
#include <algorithm>
#include <cassert>
#include <functional>
#include <format>
#include <typeinfo>
#include <string>
#include <sstream>
#include <stdarg.h>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <memory>
#include <random>
#include <filesystem>

//DirectX (TMP)
#include "UComPtr.h"
#include <d3d11.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include "../Lib/DirectXTK/Inc/SimpleMath.h"
#include "../Lib/DirectXTK/Inc/Mouse.h"
#include "../Lib/DirectXTK/Inc/Keyboard.h"

#if defined(DEBUG) || defined(_DEBUG)
#pragma comment(lib, "../Lib/DirectXTK/Debug/DirectXTK.lib")
#else
#pragma comment(lib, "../Lib/DirectXTK/Release/DirectXTK.lib")
#endif // 

using namespace DirectX;
using namespace DirectX::SimpleMath;

//Imgui
#include "imguiInc.h"
	
//Common
#include "cmAssert.h"
#include "Types.h"
#include "cmAlgorithm.h"
#include "cmStaticTextBuffer.h"
#include "cmType.h"

//Inc
#include "cmColors.h"
#include "Enums.h"
#include "WindowsStruct.h"
#include "Macro.h"
#include "ini/INIReader.h"

//Engine Module
#include "cmEngine.h"
#include "cmTimer.h"
#include "cmLogger.h"
#include "cmRenderer.h"
#include "cmGUIRenderer.h"
#include "cmResourceManager.h"

//Helper
#include "ImGuiHelper.h"
#include "cmGraphicsHelper.h"
#include "cmHelper.h"

//Graphics
#include "cmGraphicsDevice.h"
#include "cmConstantBufferData.h"
#include "cmConstantBufferBase.h"
#include "cmConstantBuffer.h"
#include "cmVertexShader.h"
#include "cmInputLayout.h"
#include "cmVertexBuffer.h"
#include "cmPixelShader.h"
#include "cmIndexBuffer.h"
#include "cmGeometry.h"
#include "cmGeometryHelper.h"
#include "cmPipelineData.h"
