#pragma once
#include "cmRenderComponent.h"
#include "cmIUpdateable.h"
#include "cmIPreRenderable.h"
class cmFlipbook;

class cmFlipbookRenderer
	: public		cmRenderComponent
	, IMPLEMENTS	cmIUpdateable
	, IMPLEMENTS	cmIPreRenderable
{
	using Super = cmRenderComponent;
public:
	cmFlipbookRenderer() = default;
	virtual ~cmFlipbookRenderer() = default;

	void Update() override;
	void PreRender() override;

	void OnStart() override;

	void SetFlipbook(cmFlipbook* inFlipbook);
	cmFlipbook* GetFlipbook() const { return mFlipbook; }

	void SetPlaybackSpeed(float inPlaybackSpeed)
	{
		if (inPlaybackSpeed <= cmMath::SMALL_NUM) { inPlaybackSpeed = cmMath::SMALL_NUM; }
		mPlaybackSpeedInv = 1.f / inPlaybackSpeed; 
	}

private:
	cmFlipbook* mFlipbook         = nullptr;
	uint32		mCurFrame            = 0;
	float		mPlaybackSpeedInv = 1.f;
	float		mTimeAcc          = 0.f;
	bool		mFinish           = false;
};
