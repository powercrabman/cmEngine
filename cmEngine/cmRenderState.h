#pragma once

class cmRenderState
{
public:
	cmRenderState() = default;
	virtual ~cmRenderState() = default;

	void Initialize();
	void CreateSamplerState(eSamplerStateFilter inFilter, eSamplerStateAddress inModeU, eSamplerStateAddress inModeV);

	ID3D11SamplerState* GetSamplerState(eSamplerStateFilter inFilter, eSamplerStateAddress inModeU, eSamplerStateAddress inModeV) const
	{
		return mSamplerState[(uint32)inFilter][(uint32)inModeU][(uint32)inModeV].Get();
	}

private:
	enum
	{
		SAMPLER_STATE_FILTER_MAX = (uint32)eSamplerStateFilter::Count,
		SAMPLER_STATE_ADDRESS_MAX = (uint32)eSamplerStateAddress::Count,
	};
	UComPtr<ID3D11SamplerState> mSamplerState[SAMPLER_STATE_FILTER_MAX][SAMPLER_STATE_ADDRESS_MAX][SAMPLER_STATE_ADDRESS_MAX] = {};

};