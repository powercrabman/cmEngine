#pragma once
#include "ResourceBase.h"

namespace cmEngine
{
	struct SpriteData
	{
		Texture*	Texture  = nullptr;
		uint32		Width    = 0;
		uint32		Height   = 0;
		uint32		PivotRow = 0;
		uint32		PivotCol = 0;
	};

	class Sprite : public ResourceBase
	{
	public:
		RESOURCE_BODY(Sprite);

		Sprite() = default;
		virtual ~Sprite() = default;

		void		Create(const SpriteData& inData);

		SpriteData	GetSpriteData() const { return mSpriteData; }
		Geometry*	GetGeometry() const { return mGeometry.get(); }

	private:
		constexpr inline static float ScaleFactor = 1 / 500.f;

		SpriteData					mSpriteData = {};
		std::unique_ptr<Geometry>	mGeometry   = {};
	};
}
