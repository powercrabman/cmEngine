#pragma once
#include "cmResourceBase.h"
#include "cmFlipbookData.h"

class cmFlipbook : public cmResourceBase
{
public:
	cmFlipbook() = default;
	virtual ~cmFlipbook() = default;

	void Create() override;

	void SetFlipbookData(const cmFlipbookData& inData) { mFlipbookData = inData; }
	cmFlipbookData GetFlipbookData() const { return mFlipbookData; }

private:
	cmFlipbookData mFlipbookData = {};
	std::unique_ptr<cmMesh>	mMesh = {};
};