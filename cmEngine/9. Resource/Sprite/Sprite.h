#pragma once


namespace cmEngine
{
	struct SpriteJson
	{
		std::string		spriteName;
		eResourceType	resourceType;
		std::string		textureName;
		uint32			width;
		uint32			height;
		uint32			pivotRow;
		uint32			pivotCol;

		JSON_STRUCT_BODY(
			SpriteJson,
			spriteName,
			resourceType,
			textureName,
			width,
			height,
			pivotRow,
			pivotCol
		);
	};

	struct SpriteData
	{
		Texture*	texture     = 0;
		uint32		width       = 0;
		uint32		height      = 0;
		uint32		pivotRow    = 0;
		uint32		pivotCol    = 0;
	};

	class Sprite : public ResourceBase
	{
	public:
		RESOURCE_BODY(Sprite);
		~Sprite() override = default;

		void				Create(const SpriteData& inData);

		const SpriteData&	GetSpriteData() const { return mSpriteData; }

		Geometry*			GetGeometry() const { return mGeometry.get(); }

	private:
		Sprite() = default;

		void SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory) override;
		bool LoadJsonFromFile(const std::filesystem::path& inFilePath,const std::filesystem::path& inDirectory) override;

	private:
		constexpr inline static float ScaleFactor = 1 / 500.f;

		SpriteData			mSpriteData = {};
		Scope<Geometry>		mGeometry   = {};
	};
}
