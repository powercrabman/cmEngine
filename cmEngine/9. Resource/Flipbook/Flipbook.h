#pragma once

namespace cmEngine
{
	struct FlipbookJson
	{
		std::string		flipbookName  = "";
		eResourceType	resourceType;
		std::string		textureName   = "";
		uint32			width         = 0;
		uint32			height        = 0;
		uint32			pivotRow      = 0;
		uint32			pivotCol      = 0;
		uint32			frameCount    = 0;
		float			frameDuration = 0.f;
		bool			loop          = true;

		JSON_STRUCT_BODY(
			FlipbookJson,
			flipbookName,
			resourceType,
			textureName,
			width,
			height,
			pivotRow,
			pivotCol,
			frameCount,
			frameDuration,
			loop
		);

	};

	struct FlipbookData
	{
		Texture*	texture       = nullptr;
		uint32		width         = 0;
		uint32		height        = 0;
		uint32		pivotRow      = 0;
		uint32		pivotCol      = 0;
		uint32		frameCount    = 0;
		float		frameDuration = 0.f;
		bool		loop          = true;
	};

	class Flipbook : public ResourceBase
	{
	public:
		RESOURCE_BODY(Flipbook);

		virtual ~Flipbook() = default;

		void				Create(const FlipbookData& inData);

		const FlipbookData&	GetFlipbookData() const { return mFlipbookData; }
		Geometry*			GetGeometry() const { return mGeometry.get(); }

	private:
		Flipbook() = default;

	protected:
		void SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory) override;
		bool LoadJsonFromFile(const std::filesystem::path& inFilePath, const std::filesystem::path& inDirectory) override;

	private:
		constexpr inline static float ScaleFactor = 1 / 500.f;

		FlipbookData		mFlipbookData   = {};
		Scope<Geometry>		mGeometry		= {};
	};
}
