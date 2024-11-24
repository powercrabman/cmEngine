#pragma once
#include "ResourceBase.h"

namespace cmEngine
{
	struct SpriteJson : JsonMetaData
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
		friend bool operator==(const SpriteData& inLhs, const SpriteData& inRhs)
		{
			return inLhs.texture == inRhs.texture
				&& inLhs.width == inRhs.width
				&& inLhs.height == inRhs.height
				&& inLhs.pivotRow == inRhs.pivotRow
				&& inLhs.pivotCol == inRhs.pivotCol;
		}

		friend bool operator!=(const SpriteData& inLhs, const SpriteData& inRhs)
		{
			return !(inLhs == inRhs);
		}

		Texture* texture = nullptr;
		uint32		width    = 0;
		uint32		height   = 0;
		uint32		pivotRow = 0;
		uint32		pivotCol = 0;
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

		bool LoadJsonFromFile(std::wstring_view inFilePath) override;
		bool LoadJsonFromSection(std::wstring_view inFilePath, std::string_view inSectionName) override;
		bool LoadJsonEx(const SpriteJson& inJson);

		void		SaveJsonToFile(std::wstring_view inFilePath) override;
		void		SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName) override;
		SpriteJson	SaveJsonEx() const;

		constexpr inline static float ScaleFactor = 1 / 500.f;

		SpriteData			mSpriteData = {};
		Scope<Geometry>		mGeometry   = {};
	};
}
