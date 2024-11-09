#include "pch.h"
#include "cmSprite.h"

void cmSprite::Create()
{
	ASSERT(mSpriteData.Texture, "Texture is nullptr");

	auto [width, height] = mSpriteData.Texture->GetSize();
	float normWidth = mSpriteData.Width / width;
	float normHeight = mSpriteData.Height / width;
	float normWidthDiv2 = normWidth * 0.5f;
	float normHeightDiv2 = normHeight * 0.5f;

	// Vertex Buffer
	std::vector<cmVertexPosTex> vb =
	{
		{Vector3{-normWidthDiv2, normHeightDiv2, 0.f},	Vector2{mSpriteData.PivotCol ,mSpriteData.PivotRow}},
		{Vector3{normWidthDiv2, normHeightDiv2, 0.f},	Vector2{mSpriteData.PivotCol + normWidth ,mSpriteData.PivotRow}},
		{Vector3{normWidthDiv2, -normHeightDiv2, 0.f},	Vector2{mSpriteData.PivotCol + normWidth ,mSpriteData.PivotRow + normHeight}},
		{Vector3{-normWidthDiv2, -normHeightDiv2, 0.f}, Vector2{mSpriteData.PivotCol ,mSpriteData.PivotRow + normHeight}}
	};

	// Index Buffer
	std::vector<UINT> ib =
	{
		0,1,2,0,2,3
	};

	mMesh = std::make_unique<cmMesh>();
	mMesh->Create(vb, ib);
}
