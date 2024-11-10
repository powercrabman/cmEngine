#include "pch.h"
#include "cmFlipbookRenderer.h"
#include "cmFlipbook.h"
#include "cmGraphicsResourceManager.h"

void cmFlipbookRenderer::SetFlipbook(cmFlipbook* inFlipbook)
{
	mFlipbook = inFlipbook;
	mPipeData.Mesh = inFlipbook->GetMesh();
	mPipeData.Texture = inFlipbook->GetFlipbookData().Texture;

	auto* rm = Engine->GetRenderer()->GetGraphicsResourceManager();
	mPipeData.SamplerState = rm->FindSamplerState(
		eSamplerStateFilter::Point,
		eSamplerStateAddress::Clamp,
		eSamplerStateAddress::Clamp
	);
}

void cmFlipbookRenderer::PreRender()
{
	cmFlipbookData fbData = mFlipbook->GetFlipbookData();
	auto [width, height] = fbData.Texture->GetSize();
	auto* cb = Engine->GetRenderer()->GetGraphicsResourceManager()->FindConstantBuffer<cmCBSprite>();
	cmCBSprite cbData = {};
	cbData.PivotRow = fbData.PivotRow / height;
	cbData.PivotCol = (fbData.PivotCol + fbData.Width * mCurFrame) / static_cast<float>(width);
	cb->UpdateBuffer(cbData);
}

void cmFlipbookRenderer::OnStart()
{
	Super::OnStart();
	mCurFrame = 0;
	mTimeAcc = 0.f;
}

void cmFlipbookRenderer::Update()
{
	if (mFinish) { return; }

	cmFlipbookData data = mFlipbook->GetFlipbookData();
	float duration = data.FrameDuration * mPlaybackSpeedInv;
	
	mTimeAcc += DELTA_TIME;
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
