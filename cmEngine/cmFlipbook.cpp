#include "pch.h"
#include "cmFlipbook.h"

void cmFlipbook::Create()
{
	ASSERT(mFlipbookData.Texture, "Texture is nullptr");

	auto [width, height] = mFlipbookData.Texture->GetSize();
	float normWidth = mFlipbookData.Width / width;
	float normHeight = mFlipbookData.Height / width;
	float normWidthDiv2 = normWidth * 0.5f;
	float normHeightDiv2 = normHeight * 0.5f;

	// Vertex Buffer
	std::vector<cmVertexPosTex> vb =
	{
		{Vector3{-normWidthDiv2, normHeightDiv2, 0.f},	Vector2{mFlipbookData.PivotCol ,mFlipbookData.PivotRow}},
		{Vector3{normWidthDiv2, normHeightDiv2, 0.f},	Vector2{mFlipbookData.PivotCol + normWidth ,mFlipbookData.PivotRow}},
		{Vector3{normWidthDiv2, -normHeightDiv2, 0.f},	Vector2{mFlipbookData.PivotCol + normWidth ,mFlipbookData.PivotRow + normHeight}},
		{Vector3{-normWidthDiv2, -normHeightDiv2, 0.f}, Vector2{mFlipbookData.PivotCol ,mFlipbookData.PivotRow + normHeight}}
	};

	// Index Buffer
	std::vector<UINT> ib =
	{
		0,1,2,0,2,3
	};

	mMesh = std::make_unique<cmMesh>();
	mMesh->Create(vb, ib);
}
