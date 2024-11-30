#include "0. cmEngine/cmEngine.h"
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

	void Flipbook::SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory)
	{
		FlipbookJson js = {};
		js.width = mFlipbookData.width;
		js.flipbookName = GetName();
		js.frameCount = mFlipbookData.frameCount;
		js.frameDuration = mFlipbookData.frameDuration;
		js.height = mFlipbookData.height;
		js.loop = mFlipbookData.loop;
		js.pivotCol = mFlipbookData.pivotCol;
		js.pivotRow = mFlipbookData.pivotRow;
		js.textureName = mFlipbookData.texture->GetName();

		JsonSerializer::Ref().SerializeToFile(js, inFileName, inDirectory);
	}

	bool Flipbook::LoadJsonFromFile(const std::filesystem::path& inFilePath, const std::filesystem::path& inDirectory)
	{
		FlipbookJson js = {};

		if (JsonSerializer::Ref().DeserializerFromFile(js, inFilePath, inDirectory))
		{
			mFlipbookData.width         = js.width;
			mFlipbookData.frameCount    = js.frameCount;
			mFlipbookData.frameDuration = js.frameDuration;
			mFlipbookData.height        = js.height;
			mFlipbookData.loop          = js.loop;
			mFlipbookData.pivotCol      = js.pivotCol;
			mFlipbookData.pivotRow      = js.pivotRow;
			mFlipbookData.texture       = ResourceManager::Ref().TryFindResource<Texture>(js.textureName);
			mName = js.flipbookName;

			if (mFlipbookData.texture == nullptr)
			{
				assert(false);
				ENGINE_LOG_ERROR("Fail Load Json in Flipbook");
				return false;
			}

			return true;
		}

		return false;
	}
}
