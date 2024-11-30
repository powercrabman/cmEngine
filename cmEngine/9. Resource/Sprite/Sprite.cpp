#include "0. cmEngine/cmEngine.h"
#include "Sprite.h"

namespace cmEngine
{
	void Sprite::Create(const SpriteData& inData)
	{
		mGeometry.reset();

		mSpriteData = inData;
		ASSERT(mSpriteData.texture, "texture is nullptr");

		auto [width, height] = mSpriteData.texture->GetSize();

		if (mSpriteData.width == 0) { mSpriteData.width = width; }
		if (mSpriteData.height == 0) { mSpriteData.height = height; }

		float u              = mSpriteData.width / static_cast<float>(width);
		float v              = mSpriteData.height / static_cast<float>(height);
		float meshWDiv2      = mSpriteData.width;
		float meshHDiv2      = mSpriteData.height;

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
			0, 1, 2, 0, 2, 3
		};

		mGeometry = MakeScope<Geometry>();
		mGeometry->Create(vb, ib);
	}

	void Sprite::SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory)
	{
		SpriteJson js  = {};
		js.width       = mSpriteData.width;
		js.height      = mSpriteData.height;
		js.textureName = mSpriteData.texture->GetName();
		js.pivotCol    = mSpriteData.pivotCol;
		js.pivotRow    = mSpriteData.pivotRow;
		js.spriteName  = GetName();

		JsonSerializer::Ref().SerializeToFile(js, inFileName, inDirectory);
	}

	bool Sprite::LoadJsonFromFile(const std::filesystem::path& inFilePath, const std::filesystem::path& inDirectory)
	{
		SpriteJson js = {};
		if (JsonSerializer::Ref().DeserializerFromFile(js, inFilePath, inDirectory))
		{
			SpriteData spd = {};
			spd.width    = js.width;
			spd.height   = js.height;
			spd.pivotCol = js.pivotCol;
			spd.pivotRow = js.pivotRow;
			spd.texture  = ResourceManager::Ref().TryFindResource<Texture>(js.textureName);
			mName        = js.spriteName;
			Create(spd);
			return true;
		}

		return false;
	}
}
