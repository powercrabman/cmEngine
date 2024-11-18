#include "EnginePch.h"
#include "Pipeline.h"

namespace cmEngine
{
	Pipeline::Pipeline()
	{
		mTransformCB = ConstantBufferPool::FindConstantBuffer<CBTransform>();
		mCameraCB    = ConstantBufferPool::FindConstantBuffer<CBCamera>();
		mSpriteCB    = ConstantBufferPool::FindConstantBuffer<CBSprite>();

		Renderer::GetContext()->VSSetConstantBuffers(0, 1, mTransformCB->GetBuffer().GetAddressOf());
		Renderer::GetContext()->VSSetConstantBuffers(1, 1, mCameraCB->GetBuffer().GetAddressOf());
		Renderer::GetContext()->VSSetConstantBuffers(2, 1, mSpriteCB->GetBuffer().GetAddressOf());
	}

	void Pipeline::SetRenderState(const RenderState& inRenderState)
	{
		if (mRenderState.blendState != inRenderState.blendState)
		{
			mRenderState.blendState = inRenderState.blendState;
			Renderer::GetContext()->OMSetBlendState(RenderStatePool::GetBlendState(mRenderState.blendState).Get(), sBlendFactor, sSampleMask);
		}

		if (mRenderState.depthStencilState != inRenderState.depthStencilState)
		{
			mRenderState.depthStencilState = inRenderState.depthStencilState;

			Renderer::GetContext()->OMSetDepthStencilState(RenderStatePool::GetDepthStencilState(mRenderState.depthStencilState).Get(), 1);
		}

		if (mRenderState.rasterizerState != inRenderState.rasterizerState)
		{
			mRenderState.rasterizerState = inRenderState.rasterizerState;
			Renderer::GetContext()->RSSetState(RenderStatePool::GetRasterizerState(mRenderState.rasterizerState).Get());
		}

		if (mRenderState.samplerState != inRenderState.samplerState)
		{
			mRenderState.samplerState = inRenderState.samplerState;
			Renderer::GetContext()->PSSetSamplers(0, 1, RenderStatePool::GetSamplerState(mRenderState.samplerState).GetAddressOf());
		}
	}

	void Pipeline::Clear()
	{
		mViewProj = Matrix::Identity;

		mTexture = nullptr;

		// RenderState Clear
		mRenderState = RenderState::DefaultState;

		Renderer::GetContext()->OMSetBlendState(RenderStatePool::GetBlendState(mRenderState.blendState).Get(), sBlendFactor, sSampleMask);
		Renderer::GetContext()->OMSetDepthStencilState(RenderStatePool::GetDepthStencilState(mRenderState.depthStencilState).Get(), 1);
		Renderer::GetContext()->RSSetState(RenderStatePool::GetRasterizerState(mRenderState.rasterizerState).Get());
		Renderer::GetContext()->PSSetSamplers(0, 1, RenderStatePool::GetSamplerState(mRenderState.samplerState).GetAddressOf());
	}
}