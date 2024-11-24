#include "EnginePch.h"
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

	bool Sprite::LoadJsonFromFile(std::wstring_view inFilePath)
	{
		SpriteJson js = {};
		if (JsonSerializer::DeserializeFromFile(js, inFilePath))
		{
			return LoadJsonEx(js);
		}

		return false;
	}

	bool Sprite::LoadJsonFromSection(std::wstring_view inFilePath, std::string_view inSectionName)
	{
		SpriteJson js = {};
		if (JsonSerializer::DeserializeFromSection(js, inFilePath, inSectionName))
		{
			return LoadJsonEx(js);
		}

		return false;
	}

	void Sprite::SaveJsonToFile(std::wstring_view inFilePath)
	{
		JsonSerializer::SerializeToFile(SaveJsonEx(), inFilePath);
	}

	void Sprite::SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName)
	{

		JsonSerializer::SerializeToSection(SaveJsonEx(), inFilePath, inSectionName);
	}

	SpriteJson Sprite::SaveJsonEx() const
	{
		SpriteJson js = {};
		js.width = mSpriteData.width;
		js.height = mSpriteData.height;
		js.textureName = mSpriteData.texture->GetName();
		js.pivotCol = mSpriteData.pivotCol;
		js.pivotRow = mSpriteData.pivotRow;
		js.spriteName = GetName();
		return js;
	}

	bool Sprite::LoadJsonEx(const SpriteJson& inJson)
	{
		SpriteData spd = {};
		spd.width      = inJson.width;
		spd.height     = inJson.height;
		spd.pivotCol   = inJson.pivotCol;
		spd.pivotRow   = inJson.pivotRow;
		spd.texture    = ResourceManager::TryFindResource<Texture>(inJson.spriteName);
		mName          = inJson.spriteName;

		// Texture 가 없을 경우
		if (spd.texture == nullptr)
		{
			ENGINE_LOG_ERROR("{} texture isn't exist.", inJson.textureName);
			return false;
		}

		Create(spd);
		return true;
	}
}
