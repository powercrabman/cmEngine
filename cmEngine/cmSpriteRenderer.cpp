#include "pch.h"
#include "cmSpriteRenderer.h"
#include "cmSprite.h"
#include "cmGraphicsResourceManager.h"

void cmSpriteRenderer::SetSprite(cmSprite* inSprite)
{
	mSprite = inSprite;
	mPipeData.Mesh = inSprite->GetMesh();
	mPipeData.Texture = inSprite->GetSpriteData().Texture;

	auto* rm = Engine->GetRenderer()->GetGraphicsResourceManager();
	mPipeData.SamplerState = rm->FindSamplerState(
		eSamplerStateFilter::Point,
		eSamplerStateAddress::Clamp,
		eSamplerStateAddress::Clamp
	);
}

void cmSpriteRenderer::PreRender()
{
	cmSpriteData spData = mSprite->GetSpriteData();
	auto [width, height] = spData.Texture->GetSize();
	auto* cb = Engine->GetRenderer()->GetGraphicsResourceManager()->FindConstantBuffer<cmCBSprite>();
	cmCBSprite cbData = {};
	cbData.PivotRow = spData.PivotRow / height;
	cbData.PivotCol = spData.PivotCol / width;
	cb->UpdateBuffer(cbData);
}