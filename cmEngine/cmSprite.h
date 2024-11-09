#pragma once
#include "cmResourceBase.h"
#include "cmSpriteData.h"

class cmSprite : public cmResourceBase
{
public:
	cmSprite() = default;
	virtual ~cmSprite() = default;

	void			Create() override;

	void			SetSpriteData(const cmSpriteData& inData) { mSpriteData = inData; }
	cmSpriteData	GetSpriteData()const { return mSpriteData; }
	cmMesh*			GetMesh() { return mMesh.get(); }

private:
	cmSpriteData				mSpriteData = {};
	std::unique_ptr<cmMesh>		mMesh = nullptr;
};