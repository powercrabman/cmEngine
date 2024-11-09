#include "pch.h"
#include "cmRenderState.h"
#include "cmGraphicsDevice.h"


void cmRenderState::Initialize()
{
	// Sampler State
	for (int i = 0; i < SAMPLER_STATE_FILTER_MAX; ++i)
	{
		for (int j = 0; j < SAMPLER_STATE_ADDRESS_MAX; ++j)
		{
			for (int k = 0; k < SAMPLER_STATE_ADDRESS_MAX; ++k)
			{
				CreateSamplerState((eSamplerStateFilter)i, (eSamplerStateAddress)j, (eSamplerStateAddress)k);
			}
		}
	}
}

void cmRenderState::CreateSamplerState(eSamplerStateFilter inFilter, eSamplerStateAddress inModeU, eSamplerStateAddress inModeV)
{
	static const D3D11_FILTER filterMapper[SAMPLER_STATE_FILTER_MAX] =
	{
		D3D11_FILTER_MIN_MAG_MIP_POINT,
		D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT,
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_FILTER_ANISOTROPIC
	};

	static const D3D11_TEXTURE_ADDRESS_MODE addressMapper[SAMPLER_STATE_FILTER_MAX] =
	{
		 D3D11_TEXTURE_ADDRESS_WRAP,
		 D3D11_TEXTURE_ADDRESS_MIRROR,
		 D3D11_TEXTURE_ADDRESS_CLAMP,
		 D3D11_TEXTURE_ADDRESS_BORDER
	};

	auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

	UComPtr<ID3D11SamplerState> samplerState = nullptr;

	D3D11_SAMPLER_DESC desc = {};
	desc.Filter             = filterMapper[(uint32)inFilter];
	desc.AddressU           = addressMapper[(uint32)inModeU];
	desc.AddressV           = addressMapper[(uint32)inModeV];
	desc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc     = D3D11_COMPARISON_ALWAYS;
	desc.MinLOD             = 0;
	desc.MaxLOD             = D3D11_FLOAT32_MAX;

	HR hr = dv->CreateSamplerState(&desc, samplerState.GetAddressOf());

	if (FAILED(hr))
	{
		DX_ASSERT(hr, "CreateSamplerState Fail.");
		LOG_ERROR("CreateSamplerState Fail.");
		return;
	}

	mSamplerState[(uint32)inFilter][(uint32)inModeU][(uint32)inModeV] = std::move(samplerState);
}




