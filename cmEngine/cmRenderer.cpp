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

cmRenderer::cmRenderer()
{
	mGraphicsDevice          = std::unique_ptr<cmGraphicsDevice>(new cmGraphicsDevice);
	mGUIRenderer             = std::unique_ptr<cmGUIRenderer>(new cmGUIRenderer);
	mGraphicsResourceManager = std::unique_ptr<cmGraphicsResourceManager>(new cmGraphicsResourceManager);

	mViewport = std::make_unique<cmViewport>();
	mRTV      = std::make_unique<cmRenderTargetView>();
	mPipeline = std::make_unique<cmPipeline>();

	mRenderList.reserve(1000);
	mMeshRendererRepo.reserve(1000);
}
cmRenderer::~cmRenderer() = default;

void cmRenderer::Initialize(cmWindow* inMainWindow)
{
	//그래픽 디바이스 초기화
	mGraphicsDevice->Initailize(inMainWindow->GetHwnd());

	mRTV->CreateFromSwapChain(mGraphicsDevice->GetSwapChain());
	mViewport->SetFrom(inMainWindow);

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


void cmRenderer::RegisterMeshRenderer(cmMeshRenderer* inMeshRenderer)
{
	auto iter = mMeshRendererRepo.find(inMeshRenderer->GetComponentID());

	if (iter != mMeshRendererRepo.end())
	{
		ASSERT(false, "already registed mesh renderer.");
		LOG_WARN("already registed mesh renderer.");
		return;
	}

	mRenderList.push_back(inMeshRenderer);

	MeshRendererData data = {};
	data.Index = mRenderList.size() - 1;
	data.MeshRenderer = inMeshRenderer;
	mMeshRendererRepo[inMeshRenderer->GetComponentID()] = data;
}

void cmRenderer::UnregisterMeshRenderer(cmMeshRenderer* inMeshRenderer)
{
	auto iter = mMeshRendererRepo.find(inMeshRenderer->GetComponentID());

	if (iter == mMeshRendererRepo.end())
	{
		ASSERT(false, "do not exist mesh renderer.");
		LOG_WARN("do not exist mesh renderer.");
		return;
	}

	if (iter->second.Index != mRenderList.size() - 1)
	{
		MeshRendererData& replace = mMeshRendererRepo[mRenderList.back()->GetComponentID()];
		replace.Index             = iter->second.Index;

		mRenderList[iter->second.Index] = mRenderList.back();
	}

	mRenderList.pop_back();

	mMeshRendererRepo.erase(iter);
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
	for (cmMeshRenderer* meshRenderer : mRenderList)
	{
		mPipeline->SetPipeline(meshRenderer->GetMesh()->GetPipelineData());
		mPipeline->SubmitPipeline();
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
	mGUIRenderer->CleanUp();
}