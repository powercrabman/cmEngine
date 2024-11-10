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
#include "cmKeyboardPoll.h"
#include "cmCamera.h"
#include "cmTexture.h"
#include "cmFlipbook.h"
#include "cmSprite.h"
#include "cmKeyboardEv.h"

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

#ifdef CM_ENGINE_USE_KEYBOARD_POLL
	mKeyboard = std::unique_ptr<cmKeyboardPoll>(new cmKeyboardPoll);
#else
	mKeyboard = std::unique_ptr<cmKeyboardEv>(new cmKeyboardEv);
#endif // POOLING_KEYBORD

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

#pragma region Texture

	{
		auto* tex = r->CreateResource<cmTexture>("SimpleTexture");
		tex->Load(r->GetCommonResourcePath(L"Texture\\Older_Walk.bmp"));
		tex->Create();
	}


	{
		auto* tex = r->CreateResource<cmTexture>("SimpleTexture2");
		tex->Load(r->GetCommonResourcePath(L"Texture\\tsubaki.png"));
		tex->Create();
	}


#pragma endregion

#pragma region Sprite & Flipbook

	{
		auto* fb = r->CreateResource<cmFlipbook>("SimpleFlipbook");
		cmFlipbookData fbd = {};
		fbd.Loop = true;
		fbd.FrameCount = 12;
		fbd.Width = 75;
		fbd.Height = 85;
		fbd.Texture = r->FindResourceOrNull<cmTexture>("SimpleTexture");
		fbd.PivotCol = 0;
		fbd.PivotRow = 0;
		fbd.FrameDuration = 0.08f;
		fb->Create(fbd);
	}

	{
		auto sp = r->CreateResource<cmSprite>("SimpleSprite");
		cmSpriteData spd = {};
		spd.Width = 0;
		spd.Height = 0;
		spd.PivotCol = 0;
		spd.PivotRow = 0;
		spd.Texture = r->FindResourceOrNull<cmTexture>("SimpleTexture2");
		sp->Create(spd);
	}

#pragma endregion

#pragma region Vertex Shader
	{
		cmVertexShader* vs = r->CreateResource<cmVertexShader>("SimpleVS");
		vs->LoadAndCompileHLSL(
			r->GetCommonResourcePath(L"Shader\\1. SimpleColorShader.hlsli").data(),
			"VS",
			"vs_5_0"
		);
		vs->Create<cmVertexPosColor>();
		vs->SetConstantBuffers({ g->FindConstantBuffer<cmCBTransform>(), g->FindConstantBuffer<cmCBCamera>() });
	}

	{
		cmVertexShader* vs = r->CreateResource<cmVertexShader>("SimpleTexVS");
		vs->LoadAndCompileHLSL(
			r->GetCommonResourcePath(L"Shader\\2. SimpleTexShader.hlsli").data(),
			"VS",
			"vs_5_0"
		);
		vs->Create<cmVertexPosTex>();
		vs->SetConstantBuffers({ g->FindConstantBuffer<cmCBTransform>(), g->FindConstantBuffer<cmCBCamera>() });
	}

	{
		cmVertexShader* vs = r->CreateResource<cmVertexShader>("SimpleTexSpriteVS");
		vs->LoadAndCompileHLSL(
			r->GetCommonResourcePath(L"Shader\\3. SimpleTexSpriteShader.hlsli").data(),
			"VS",
			"vs_5_0"
		);

		vs->Create<cmVertexPosTex>();
		vs->SetConstantBuffers({
			g->FindConstantBuffer<cmCBTransform>(),
			g->FindConstantBuffer<cmCBCamera>(),
			g->FindConstantBuffer<cmCBSprite>()
			});
	}

#pragma endregion

#pragma region Pixel Shader

	{
		cmPixelShader* ps = r->CreateResource<cmPixelShader>("SimplePS");
		ps->LoadAndCompileHLSL(
			r->GetCommonResourcePath(L"Shader\\1. SimpleColorShader.hlsli").data(),
			"PS",
			"ps_5_0"
		);
		ps->Create();
	}

	{
		cmPixelShader* ps = r->CreateResource<cmPixelShader>("SimpleTexPS");
		ps->LoadAndCompileHLSL(
			r->GetCommonResourcePath(L"Shader\\2. SimpleTexShader.hlsli").data(),
			"PS",
			"ps_5_0"
		);
		ps->Create();
	}

	{
		cmPixelShader* ps = r->CreateResource<cmPixelShader>("SimpleTexSpritePS");
		ps->LoadAndCompileHLSL(
			r->GetCommonResourcePath(L"Shader\\3. SimpleTexSpriteShader.hlsli").data(),
			"PS",
			"ps_5_0"
		);
		ps->Create();
	}

#pragma endregion

#pragma region Mesh

	// Mesh
	{
		cmMesh* m = r->CreateResource<cmMesh>("SimpleMesh");
		cmHelper::Graphics::Geometry2D::CreateColoredQuad(m, 0.5f, { cmColors::Gray, cmColors::Cyan, cmColors::Yellow, cmColors::Magenta });
	}

	{
		cmMesh* m = r->CreateResource<cmMesh>("SimpleTexMesh");
		std::array<Vector2, 4> uvs =
		{
			Vector2{1.f,0.f},
			Vector2{1.f,1.f},
			Vector2{0.f,1.f},
			Vector2{0.f,0.f}
		};

		cmHelper::Graphics::Geometry2D::CreateTexQuad(m, 0.5f, uvs);
	}

#pragma endregion

}

cmEngine* Engine = nullptr;
