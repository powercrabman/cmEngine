#include "EnginePch.h"
#include "FlipbookRenderer.h"
#include "Flipbook.h"

namespace cmEngine
{
	void FlipbookRenderer::SetFlipbook(Flipbook* inFlipbook)
	{
		mFlipbook              = inFlipbook;
		mPipeData.Geometry     = inFlipbook->GetGeometry();
		mPipeData.Texture      = inFlipbook->GetFlipbookData().Texture;
		mPipeData.SamplerState = eSamplerState::Point_Wrap;
	}

	void FlipbookRenderer::PreRender()
	{
		const FlipbookData& fbData  = mFlipbook->GetFlipbookData();
		auto [width, height]        = fbData.Texture->GetSize();
		CBSprite cbData             = {};
		cbData.PivotRow             = fbData.PivotRow / height;
		cbData.PivotCol             = (fbData.PivotCol + fbData.Width * mCurFrame) / static_cast<float>(width);
		ConstantBufferPool::FindConstantBuffer<CBSprite>()->UpdateBuffer(cbData);
	}

	void FlipbookRenderer::Awake()
	{
		Super::Awake();
		mCurFrame = 0;
		mTimeAcc = 0.f;
	}

	void FlipbookRenderer::Update()
	{
		if (mFinish) { return; }

		FlipbookData data = mFlipbook->GetFlipbookData();
		float duration = data.FrameDuration * mPlaybackSpeedInv;

		mTimeAcc += Timer::GetDeltaTime();
		if (mTimeAcc >= duration)
		{
			mTimeAcc -= duration;

			if (mCurFrame < data.FrameCount - 1)
			{
				++mCurFrame;
			}
			else
			{
				if (data.Loop)
				{
					mCurFrame = 0;
				}
				else
				{
					mFinish = true;
				}
			}
		}
	}
}
