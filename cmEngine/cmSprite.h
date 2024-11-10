#pragma once
#include "cmResourceBase.h"
#include "cmSpriteData.h"
#include "cmIPreRenderable.h"

class cmSprite : public cmResourceBase
{
public:
	cmSprite() = default;
	virtual ~cmSprite() = default;

	void			Create(const cmSpriteData& inData);

	cmSpriteData	GetSpriteData()const { return mSpriteData; }
	cmMesh* GetMesh() { return mMesh.get(); }

private:
	constexpr inline static float ScaleFactor = 1 / 500.f;

	cmSpriteData				mSpriteData = {};
	std::unique_ptr<cmMesh>		mMesh = nullptr;
};