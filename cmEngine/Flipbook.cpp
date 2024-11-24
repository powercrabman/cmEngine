#include "EnginePch.h"
#include "Flipbook.h"

namespace cmEngine
{

	void Flipbook::Create(const FlipbookData& inData)
	{
		mGeometry.reset();

		mFlipbookData = inData;
		ASSERT(mFlipbookData.texture, "texture is nullptr");

		auto [width, height] = mFlipbookData.texture->GetSize();
		float u = mFlipbookData.width / static_cast<float>(width);
		float v = mFlipbookData.height / static_cast<float>(height);
		float meshWDiv2 = mFlipbookData.width * ScaleFactor * 0.5f;
		float meshHDiv2 = mFlipbookData.height * ScaleFactor * 0.5f;

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

		mGeometry = MakeScope<Geometry>();
		mGeometry->Create(vb, ib);
	}

	bool Flipbook::LoadJsonFromFile(std::wstring_view inFilePath)
	{
		FlipbookJson js = {};

		if (JsonSerializer::DeserializeFromFile(js, inFilePath))
		{
			return LoadJsonEx(js);
		}

		ENGINE_LOG_INFO("{} texture load fails", js.flipbookName);
		return false;
	}


	bool Flipbook::LoadJsonFromSection(std::wstring_view inFilePath,std::string_view inSectionName)
	{
		FlipbookJson js = {};

		if (JsonSerializer::DeserializeFromSection(js, inFilePath, inSectionName))
		{
			return LoadJsonEx(js);
		}

		ENGINE_LOG_INFO("{} texture load fails", js.flipbookName);
		return false;
	}

	bool Flipbook::LoadJsonEx(const FlipbookJson& inJson)
	{
		mFlipbookData.width         = inJson.width;
		mFlipbookData.frameCount    = inJson.frameCount;
		mFlipbookData.frameDuration = inJson.frameDuration;
		mFlipbookData.height        = inJson.height;
		mFlipbookData.loop          = inJson.loop;
		mFlipbookData.pivotCol      = inJson.pivotCol;
		mFlipbookData.pivotRow      = inJson.pivotRow;
		mFlipbookData.texture       = ResourceManager::TryFindResource<Texture>(inJson.textureName);
		mName                       = inJson.flipbookName;

		if (mFlipbookData.texture == nullptr)
		{
			assert(false);
			ENGINE_LOG_ERROR("Fail Load Json in Flipbook");
			return false;
		}

		return true;
	}

	void Flipbook::SaveJsonToFile(std::wstring_view inFilePath)
	{
		JsonSerializer::SerializeToFile(SaveJsonEx(), inFilePath);
	}

	void Flipbook::SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName)
	{
		JsonSerializer::SerializeToSection(SaveJsonEx(), inFilePath, inSectionName);
	}

	FlipbookJson Flipbook::SaveJsonEx() const
	{
		FlipbookJson js  = {};
		js.width         = mFlipbookData.width;
		js.flipbookName  = GetName();
		js.frameCount    = mFlipbookData.frameCount;
		js.frameDuration = mFlipbookData.frameDuration;
		js.height        = mFlipbookData.height;
		js.loop          = mFlipbookData.loop;
		js.pivotCol      = mFlipbookData.pivotCol;
		js.pivotRow      = mFlipbookData.pivotRow;
		js.textureName   = mFlipbookData.texture->GetName();

		return js; 
	}
}
