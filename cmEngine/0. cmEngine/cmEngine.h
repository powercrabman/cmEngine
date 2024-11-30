#pragma once

//============================
// 엔진 및 클라이언트에서 전역적으로 사용
//============================

#define _WIN32_WINNT 0x0601


//Windows
#include <Windows.h>

//STD & STL
#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <fstream>
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

#include "json/json.hpp"
using json = nlohmann::json;

//entt
#include "../Libraries/entt/entt.hpp"

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
#include "../Libraries/ImGui/imgui.h"
#include "../Libraries/ImGui/imgui_impl_dx11.h"
#include "../Libraries/ImGui/imgui_impl_win32.h"
#include "../Libraries/ImGui/imgui_internal.h"
#include "7. Gui/Helper/GuiHelper.h"

#pragma comment(lib, "Imgui/imgui.lib")

//Inc
#include "99. Base/Pointer.h"
#include "99. Base/TypeID.h"
#include "99. Base/Types.h"
#include "99. Base/Colors.h"
#include "99. Base/EngineMacro.h"
#include "99. Base/Hasher.h"
#include "3. Event/GameEvent.h"
#include "3. event/EventDispatcher.h"

//Common
#include "99. Base/EngineAssertion.h"
#include "5. Timer/Timer.h"
#include "98. Log/Log.h"
#include "99. Base/EngineAlgorithm.h"

#include "96. JsonSerializer/JsonHelper.h"
#include "99. Base/EngineMath.h"
#include "9. Resource/EngineResource.h"
//Engine Module
#include "96. JsonSerializer/JsonSerializer.h"

#include "3. Window/GameWindow.h"
#include "3. Window/GameWindow.h"
#include "4. Input/Input.h"
#include "1. Application/Application.h"
#include "2. Engine/EngineCore.h"

// Rendering & Resource
#include "6. Renderer/RenderTarget/Viewport.h"
#include "6. Renderer/Core/Renderer.h"
#include "6. Renderer/RenderTarget/RenderTarget.h"
#include "6. Renderer/RenderTarget/MasterRenderTarget.h"
#include "6. Renderer/RenderTarget/SubRenderTarget.h"
#include "6. Renderer/ContantBuffer/ConstantBuffer.h"
#include "6. Renderer/ContantBuffer/ConstantBufferData.h"
#include "6. Renderer/ContantBuffer/ConstantBufferPool.h"
#include "6. Renderer/Vertex/VertexData.h"
#include "6. Renderer/Shader/Shader.h"
#include "6. Renderer/Shader/ShaderAnalyzer.h"
#include "6. Renderer/Shader/PixelShader.h"
#include "6. Renderer/Shader/VertexShader.h"
#include "6. Renderer/RenderState/RenderStatePool.h"
#include "6. Renderer/RenderState/RenderState.h"
#include "6. Renderer/Geometry/IndexBuffer.h"
#include "6. Renderer/Geometry/VertexBuffer.h"
#include "6. Renderer/Geometry/Geometry.h"
#include "6. Renderer/Geometry/PrimitiveGeometry.h"
#include "9. Resource/Core/ResourceBase.h"
#include "9. Resource/Core/ResourceManager.h"
#include "9. Resource/Texture/Texture.h"
#include "9. Resource/ShaderSet/ShaderSet.h"
#include "9. Resource/Sprite/Sprite.h"
#include "9. Resource/Flipbook/Flipbook.h"
#include "6. Renderer/Pipeline/Pipeline.h"
#include "7. Gui/Gui.h"
#include "7. Gui/GuiRenderer.h"

// GameEntity
#include "12. Component/Factory/ComponentSerializer.h"
#include "12. Component/Name.h"
#include "11. GameEntity/GameEntity.h"

// Scene

#include "10. Scene/Scene.h"
#include "10. Scene/SceneManager.h"

// Compoenent System

#include "12. Component/Transform.h"
#include "12. Component/Camera.h"
#include "12. Component/RenderComponent.h"
#include "12. Component/Behavior.h"
#include "12. Component/InputController.h"
#include "12. Component/Factory/ComponentSerializer.h"
