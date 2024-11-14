#pragma once
#include "ResourceBase.h"

namespace cmEngine
{
	struct FlipbookData
	{
		Texture*	Texture = nullptr;
		uint32		Width = 0;
		uint32		Height = 0;
		uint32		PivotRow = 0;
		uint32		PivotCol = 0;
		uint32		FrameCount = 0;
		float		FrameDuration = 0.f;
		bool		Loop = true;
	};

	class Flipbook : public ResourceBase
	{
	public:
		RESOURCE_BODY(Flipbook);

		Flipbook() = default;
		virtual ~Flipbook() = default;

		void Create(const FlipbookData& inData);

		FlipbookData GetFlipbookData() const { return mFlipbookData; }
		Geometry* GetGeometry() const { return mGeometry.get(); }

	private:
		constexpr inline static float ScaleFactor = 1 / 500.f;

		FlipbookData mFlipbookData           = {};
		std::unique_ptr<Geometry>	mGeometry= {};
	};
}