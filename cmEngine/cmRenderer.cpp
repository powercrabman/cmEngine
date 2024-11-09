#include "pch.h"
#include "cmRenderer.h"
#include "cmGraphicsDevice.h"
#include "cmWindow.h"
#include "cmWindowsManager.h"
#include "cmMesh.h"
#include "cmGUIRenderer.h"
#include "cmWindow.h"
#include "cmViewport.h"
#include "cmRenderTargetView.h"
#include "cmPipeline.h"
#include "cmResourceManager.h"
#include "cmMeshRenderer.h"
#include "cmGraphicsResourceManager.h"
#include "cmGameObject.h"

cmRenderer::cmRenderer()
{
	mGraphicsDevice          = std::unique_ptr<cmGraphicsDevice>(new cmGraphicsDevice);
	mGUIRenderer             = std::unique_ptr<cmGUIRenderer>(new cmGUIRenderer);
	mGraphicsResourceManager = std::unique_ptr<cmGraphicsResourceManager>(new cmGraphicsResourceManager);

	mViewport = std::make_unique<cmViewport>();
	mRTV      = std::make_unique<cmRenderTargetView>();
	mPipeline = std::make_unique<cmPipeline>();

	mRenderList.reserve(1000);
	mRenderRepo.reserve(1000);
}
cmRenderer::~cmRenderer() = default;

void cmRenderer::Initialize(cmWindow* inMainWindow)
{
	//COM interface 
	DX_ASSERT(CoInitializeEx(nullptr, COINIT_MULTITHREADED), "COM Interface Initalize Fail.");

	//그래픽 디바이스 초기화
	mGraphicsDevice->Initailize(inMainWindow->GetHwnd());

	mRTV->CreateFromSwapChain(mGraphicsDevice->GetSwapChain());
	mViewport->SetFrom(inMainWindow);

	//그래픽 리소스
	mGraphicsResourceManager->Initialize();

	//GUI 렌더러 초기화
	mGUIRenderer->Initialize(inMainWindow->GetHwnd(), mGraphicsDevice.get());
	LOG_INFO("Renderer Initialize Done.");
}

void cmRenderer::OnResize(const ScreenSize& inScreenSize)
{
	mGraphicsDevice->ResizeSwapChain(inScreenSize);
	mRTV->CreateFromSwapChain(mGraphicsDevice->GetSwapChain());
	mViewport->SetFrom(inScreenSize);
}

void cmRenderer::RegistGameObject(cmGameObject* inGameObject)
{
	auto iter = mRenderRepo.find(inGameObject->GetObjectID());

	if (iter != mRenderRepo.end())
	{
		ASSERT(false, "already registed mesh renderer.");
		LOG_WARN("already registed mesh renderer.");
		return;
	}

	mRenderList.push_back(inGameObject);

	GameObjectData data = {};
	data.Index = mRenderList.size() - 1;
	data.GameObject = inGameObject;
	mRenderRepo[inGameObject->GetObjectID()] = data;
}

void cmRenderer::UnregistGameObject(cmGameObject* inGameObject)
{
	auto iter = mRenderRepo.find(inGameObject->GetObjectID());

	if (iter == mRenderRepo.end())
	{
		ASSERT(false, "do not exist mesh renderer.");
		LOG_WARN("do not exist mesh renderer.");
		return;
	}

	if (iter->second.Index != mRenderList.size() - 1)
	{
		GameObjectData& replace = mRenderRepo[mRenderList.back()->GetObjectID()];
		replace.Index             = iter->second.Index;

		mRenderList[iter->second.Index] = mRenderList.back();
	}

	mRenderList.pop_back();

	mRenderRepo.erase(iter);
}

void cmRenderer::RenderBegin()
{
	ID3D11DeviceContext* dc = mGraphicsDevice->GetContext();

	// 렌더 타겟 & 뷰포트 설정
	dc->OMSetRenderTargets(1, mRTV->GetRTVPtr(), nullptr);
	dc->ClearRenderTargetView(mRTV->GetRTV(), mClearColor);
	dc->RSSetViewports(1, mViewport->GetViewport());

	dc->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 파이프라인 청소
	mPipeline->Clear();
}


void cmRenderer::Render()
{
	for (cmGameObject* obj : mRenderList)
	{
		obj->PreRender();
		auto* meshRenderer = obj->FindComponentOrNull<cmMeshRenderer>();
		mPipeline->SubmitPipeline(meshRenderer->GetPipelineData());
		mPipeline->SubmitGraphicsData();
		mPipeline->DrawIndices();
	}
}

void cmRenderer::RenderEnd()
{
	//GUI 랜더링
	mGUIRenderer->Render();

	//스왑체인
	mGraphicsDevice->GetSwapChain()->Present(0, 0);
}

void cmRenderer::CleanUp()
{
	CoUninitialize();
	mGUIRenderer->CleanUp();
	mGraphicsDevice->ClearUp();
}