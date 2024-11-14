#include "EnginePch.h"
#include "Flipbook.h"

namespace cmEngine
{
	void Flipbook::Create(const FlipbookData& inData)
	{
		mFlipbookData = inData;
		ASSERT(mFlipbookData.Texture, "Texture is nullptr");

		auto [width, height] = mFlipbookData.Texture->GetSize();
		float u              = mFlipbookData.Width / static_cast<float>(width);
		float v              = mFlipbookData.Height / static_cast<float>(height);
		float meshWDiv2      = mFlipbookData.Width * ScaleFactor * 0.5f;
		float meshHDiv2      = mFlipbookData.Height * ScaleFactor * 0.5f;

		// Vertex Buffer
		std::vector<VertexPosTex> vb = {
			{Vector3{-meshWDiv2,  meshHDiv2, 0.f}, Vector2{0.f, 0.f}},
			{Vector3{ meshWDiv2,  meshHDiv2, 0.f}, Vector2{u, 0.f}},
			{Vector3{ meshWDiv2, -meshHDiv2, 0.f}, Vector2{u, v}},
			{Vector3{-meshWDiv2, -meshHDiv2, 0.f}, Vector2{0.f, v}}
		};

		// Index Buffer
		std::vector<UINT> ib =
		{
			0,1,2,0,2,3
		};

		mGeometry = std::make_unique<Geometry>();
		mGeometry->Create(vb, ib);
	}
}
