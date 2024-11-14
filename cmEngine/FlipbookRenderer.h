#pragma once
#include "RenderComponent.h"
#include "IUpdateable.h"
#include "IPreRenderable.h"

class Flipbook;

namespace cmEngine
{
	class FlipbookRenderer
		: public		RenderComponent
		, IMPLEMENTS	IUpdateable
		, IMPLEMENTS	IPreRenderable
	{
		using Super = RenderComponent;
	public:
		COMPONENT_BODY(FlipbookRenderer);

		FlipbookRenderer() = default;
		virtual ~FlipbookRenderer() = default;

		void Update() override;
		void PreRender() override;

		void OnStart() override;

		void		SetFlipbook(Flipbook* inFlipbook);
		Flipbook*	GetFlipbook() const { return mFlipbook; }

		void SetPlaybackSpeed(float inPlaybackSpeed)
		{
			if (Math::Tolerance(inPlaybackSpeed)) { inPlaybackSpeed = Math::SMALL_NUM; }
			mPlaybackSpeedInv = 1.f / inPlaybackSpeed;
		}

	private:
		Flipbook*	mFlipbook = nullptr;
		uint32		mCurFrame = 0;
		float		mPlaybackSpeedInv = 1.f;
		float		mTimeAcc = 0.f;
		bool		mFinish = false;
	};
}
