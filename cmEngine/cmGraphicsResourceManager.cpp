#include "pch.h"
#include "cmGraphicsResourceManager.h"
#include "cmRenderState.h"

cmGraphicsResourceManager::cmGraphicsResourceManager()
{
	mRenderState = std::make_unique<cmRenderState>();
}
cmGraphicsResourceManager::~cmGraphicsResourceManager() {}

void cmGraphicsResourceManager::Initialize()
{
	mRenderState->Initialize();
}

ID3D11SamplerState* cmGraphicsResourceManager::FindSamplerState(eSamplerStateFilter inFilter, eSamplerStateAddress inModeU, eSamplerStateAddress inModeV)
{
	return mRenderState->GetSamplerState(inFilter, inModeU, inModeV);
}