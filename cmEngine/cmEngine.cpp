#include "pch.h"
#include "cmEngine.h"
#include "cmWindowsManager.h" 
#include "cmRenderer.h" 
#include "cmWindow.h"
#include "cmConsole.h"
#include "cmLogger.h"
#include "cmTimer.h"
#include "cmResourceManager.h"
#include "cmDebugGUI.h"
#include "cmPopupGUI.h"
#include "cmSceneManager.h"
#include "cmGraphicsResourceManager.h"
#include "cmMesh.h"
#include "cmGameObject.h"
#include "cmTransform.h"
#include "cmKeyboard.h"
#include "cmCamera.h"

cmEngine::~cmEngine() = default;
cmEngine::cmEngine()
{
	//엔진 모듈 생성
	mWindowsManager = std::unique_ptr<cmWindowsManager>(new cmWindowsManager);
	mRenderer = std::unique_ptr<cmRenderer>(new cmRenderer);
	mConsole = std::unique_ptr<cmConsole>(new cmConsole);
	mLogger = std::unique_ptr<cmLogger>(new cmLogger);
	mTimer = std::unique_ptr<cmTimer>(new cmTimer);
	mResourceManager = std::unique_ptr<cmResourceManager>(new cmResourceManager);
	mSceneManager = std::unique_ptr<cmSceneManager>(new cmSceneManager);
	mKeyboard = std::unique_ptr<cmKeyboard>(new cmKeyboard);
}

void cmEngine::Initialize() const
{
	LOG_INFO("Engine Start.");

	// 타이머 초기화
	mTimer->Initialize();

	// 윈도우 매니저 초기화
	mWindowsManager->Initialize();

	// Input 초기화
	mKeyboard->Initialize();
}

void cmEngine::FinalInitialize()
{
	// 렌더러 초기화
	cmWindow* mainWin = mWindowsManager->GetMainWindow();
	mRenderer->Initialize(mainWin);

	// 리소스 매니저
	mResourceManager->Initialize();

	// Logger, Debugger, Commander Initialize
	mLogger->Initialize();
	mConsole->Initialize();
	mRenderer->GetGUIRenderer()->RegisterGUI<cmDebugGUI>();

	// 엔진 GUI
	mRenderer->GetGUIRenderer()->RegisterGUI<cmPopupGUI>();

	// 공통 리소스 생성
	LoadCommonResources();

	// 초기화 완료
	mInitalized = true;
	LOG_INFO("Engine Initialize Done.");
}

void cmEngine::LoadCommonResources() const
{
	auto* r = GetResourceManager();
	auto* g = GetRenderer()->GetGraphicsResourceManager();

#pragma region Constant Buffer

	{
		auto* cb = g->CreateConstantBuffer<cmCBTransform>();
		cb->Create();
	}

	{
		auto* cb = g->CreateConstantBuffer<cmCBCamera>();
		cb->Create();
	}

#pragma endregion

	auto* grm = mRenderer->GetGraphicsResourceManager();


	// Vertex Shadepr
	cmVertexShader* vs = r->CreateResource<cmVertexShader>("SimpleVS");
	vs->LoadAndCompileHLSL(
		r->GetCommonResourcePath(L"Shader\\1. SimpleColorShader.hlsli").c_str(),
		"VS",
		"vs_5_0"
	);
	vs->Create();
	vs->SetConstantBuffers({ grm->FindConstantBufferOrNull<cmCBTransform>(), grm->FindConstantBufferOrNull<cmCBCamera>() });

	// Pixel Shader
	cmPixelShader* ps = r->CreateResource<cmPixelShader>("SimplePS");
	ps->LoadAndCompileHLSL(
		r->GetCommonResourcePath(L"Shader\\1. SimpleColorShader.hlsli").c_str(),
		"PS",
		"ps_5_0"
	);
	ps->Create();

	// Geometry
	cmGeometry* geo = g->CreateGeometry("SimpleRect");
	cmHelper::Graphics::Geometry2D::CreateColoredSquare(geo, 0.5f, { cmColors::Cyan,cmColors::Aqua, cmColors::Darkmagenta, cmColors::Palevioletred });

	// InputLayout
	g->CreateInputLayout<cmVertexPosColor>(Engine->GetResourceManager()->FindResourceOrNull<cmVertexShader>("SimpleVS"));

	// Mesh
	cmMesh* m = r->CreateResource<cmMesh>("SimpleMesh");
	cmPipelineData d = {};
	d.Geometry = g->FindGeometryOrNull("SimpleRect");
	d.InputLayout = g->FindInputLayoutOrNull<cmVertexPosColor>();
	d.VertexShader = vs;
	d.PixelShader = ps;

	m->SetPipelineData(d);
}

cmEngine* Engine = nullptr;
