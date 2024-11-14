#pragma once

//============================
// 엔진 및 클라이언트에서 전역적으로 사용
//============================

#define _WIN32_WINNT 0x0601
#define _CRTDBG_MAP_ALLOC
//#define CM_ENGINE_USE_KEYBOARD_POLL

#include <crtdbg.h>

//Windows
#include <Windows.h>

//STD & STL
#include <algorithm>
#include <array>
#include <cassert>
#include <codecvt>
#include <deque>
#include <filesystem>
#include <format>
#include <functional>
#include <locale>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <stdarg.h>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//DirectX
#include <d3d11.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <winrt/base.h>

#include "DirectXTK/SimpleMath.h"
#include "DirectXTK/SimpleMath.inl"
#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/DirectXTex.inl"
#include <wrl/client.h>
using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxcompiler.lib")
#pragma comment(lib, "DirectXTK/DirectXTK_debug.lib")
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#pragma comment(lib, "windowsapp.lib")
#pragma comment(lib, "runtimeobject.lib")

//Imgui
#include "imguiInc.h"
#include "Log.h"

//Common
#include "Types.h"
#include "EngineAssertion.h"
#include "EngineAlgorithm.h"
#include "TypeID.h"
#include "EngineMath.h"
#include "EngineMacro.h"
#include "BatchSystem.h"

//Inc
#include "Colors.h"
#include "Enums.h"

//Engine Module
#include "GameWindow.h"
#include "EngineCore.h"
#include "Timer.h"
#include "Input.h"

// Resource
#include "ResourceManager.h"

// Rendering
#include "Viewport.h"
#include "Renderer.h"
#include "ConstantBufferData.h"
#include "ConstantBuffer.h"
#include "ConstantBufferPool.h"
#include "VertexData.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Geometry.h"
#include "RenderState.h"
#include "Texture.h"
#include "Pipeline.h"
#include "Gui.h"
#include "GuiRenderer.h"

// Scene
#include "Scene.h"
#include "SceneManager.h"