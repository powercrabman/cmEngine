#include "EnginePch.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

namespace cmEngine
{
	void SpriteRenderer::PreRender()
	{
		SpriteData spData    = mSprite->GetSpriteData();
		auto [width, height] = spData.Texture->GetSize();

		CBSprite cbData = {};
		cbData.PivotRow = spData.PivotRow / height;
		cbData.PivotCol = spData.PivotCol / width;
		ConstantBufferPool::FindConstantBuffer<CBSprite>()->UpdateBuffer(cbData);
	}

	void SpriteRenderer::SetSprite(Sprite* inSprite)
	{
		mSprite                = inSprite;
		mPipeData.Geometry     = inSprite->GetGeometry();
		mPipeData.Texture      = inSprite->GetSpriteData().Texture;
		mPipeData.SamplerState = eSamplerState::Point_Clamp;
	}
}
