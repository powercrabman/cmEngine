#pragma once
#include "cmResourceBase.h"
#include "cmFlipbookData.h"

class cmFlipbook : public cmResourceBase
{
public:
	cmFlipbook() = default;
	virtual ~cmFlipbook() = default;

	void Create(const cmFlipbookData& inData);

	cmFlipbookData GetFlipbookData() const { return mFlipbookData; }
	cmMesh* GetMesh() const { return mMesh.get(); }

private:
	constexpr inline static float ScaleFactor = 1 / 500.f;

	cmFlipbookData mFlipbookData = {};
	std::unique_ptr<cmMesh>	mMesh = {};
};