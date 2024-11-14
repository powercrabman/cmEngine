#include "EnginePch.h"
#include "Sprite.h"

namespace cmEngine
{
	void Sprite::Create(const SpriteData& inData)
	{
		mSpriteData = inData;
		ASSERT(mSpriteData.Texture, "Texture is nullptr");

		auto [width, height] = mSpriteData.Texture->GetSize();
		float u              = mSpriteData.Width == 0 ? 1.f : mSpriteData.Width / static_cast<float>(width);
		float v              = mSpriteData.Height == 0 ? 1.f : mSpriteData.Height / static_cast<float>(height);
		float meshWDiv2      = mSpriteData.Width == 0 ? width : mSpriteData.Width;
		float meshHDiv2      = mSpriteData.Height == 0 ? height : mSpriteData.Height;

		meshWDiv2 *= ScaleFactor * 0.5f;
		meshHDiv2 *= ScaleFactor * 0.5f;

		// Vertex Buffer
		std::vector<VertexPosTex> vb = {
			{Vector3{-meshWDiv2, meshHDiv2, 0.f}, Vector2{0.f, 0.f}},
			{Vector3{meshWDiv2, meshHDiv2, 0.f}, Vector2{u, 0.f}},
			{Vector3{meshWDiv2, -meshHDiv2, 0.f}, Vector2{u, v}},
			{Vector3{-meshWDiv2, -meshHDiv2, 0.f}, Vector2{0.f, v}},
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


