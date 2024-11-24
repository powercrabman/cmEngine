#pragma once
#include "ResourceBase.h"

namespace cmEngine
{
	struct FlipbookJson : public JsonMetaData
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
		friend bool operator==(const FlipbookData& inLhs, const FlipbookData& inRhs)
		{
			return inLhs.texture == inRhs.texture
				&& inLhs.width == inRhs.width
				&& inLhs.height == inRhs.height
				&& inLhs.pivotRow == inRhs.pivotRow
				&& inLhs.pivotCol == inRhs.pivotCol
				&& inLhs.frameCount == inRhs.frameCount
				&& inLhs.frameDuration == inRhs.frameDuration
				&& inLhs.loop == inRhs.loop;
		}

		friend bool operator!=(const FlipbookData& inLhs, const FlipbookData& inRhs)
		{
			return !(inLhs == inRhs);
		}

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

		bool			LoadJsonFromFile(std::wstring_view inFilePath) override;
		bool			LoadJsonFromSection(std::wstring_view inFilePath, std::string_view inSectionName) override;
		bool			LoadJsonEx(const FlipbookJson& inJson);

		void			SaveJsonToFile(std::wstring_view inFilePath) override;
		void			SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName) override;
		FlipbookJson	SaveJsonEx() const;

		constexpr inline static float ScaleFactor = 1 / 500.f;

		FlipbookData		mFlipbookData   = {};
		Scope<Geometry>		mGeometry		= {};
	};
}
