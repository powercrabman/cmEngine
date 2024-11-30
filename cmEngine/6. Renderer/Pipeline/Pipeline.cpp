#include "0. cmEngine/cmEngine.h"
#include "Pipeline.h"

namespace cmEngine
{
	Pipeline::Pipeline()
	{
		mTransformCB = ConstantBufferPool::FindConstantBuffer<CBTransform>();
		mCameraCB    = ConstantBufferPool::FindConstantBuffer<CBCamera>();
		mSpriteCB    = ConstantBufferPool::FindConstantBuffer<CBSprite>();

		Renderer::Ref().GetContext()->VSSetConstantBuffers(0, 1, mTransformCB->GetBuffer().GetAddressOf());
		Renderer::Ref().GetContext()->VSSetConstantBuffers(1, 1, mCameraCB->GetBuffer().GetAddressOf());
		Renderer::Ref().GetContext()->VSSetConstantBuffers(2, 1, mSpriteCB->GetBuffer().GetAddressOf());
	}

	void Pipeline::SetRenderState(const RenderState& inRenderState)
	{
		if (mRenderState.blendState != inRenderState.blendState)
		{
			mRenderState.blendState = inRenderState.blendState;
			Renderer::Ref().GetContext()->OMSetBlendState(RenderStatePool::GetBlendState(mRenderState.blendState).Get(), sBlendFactor, sSampleMask);
		}

		if (mRenderState.depthStencilState != inRenderState.depthStencilState)
		{
			mRenderState.depthStencilState = inRenderState.depthStencilState;

			Renderer::Ref().GetContext()->OMSetDepthStencilState(RenderStatePool::GetDepthStencilState(mRenderState.depthStencilState).Get(), 1);
		}

		if (mRenderState.rasterizerState != inRenderState.rasterizerState)
		{
			mRenderState.rasterizerState = inRenderState.rasterizerState;
			Renderer::Ref().GetContext()->RSSetState(RenderStatePool::GetRasterizerState(mRenderState.rasterizerState).Get());
		}

		if (mRenderState.samplerState != inRenderState.samplerState)
		{
			mRenderState.samplerState = inRenderState.samplerState;
			Renderer::Ref().GetContext()->PSSetSamplers(0, 1, RenderStatePool::GetSamplerState(mRenderState.samplerState).GetAddressOf());
		}
	}

	void Pipeline::Clear()
	{
		mViewProj = Matrix::Identity;

		mTexture = nullptr;

		// RenderState ClearBuffer
		mRenderState = RenderState::DefaultState;


		auto c = Renderer::Ref().GetContext();
		c->OMSetBlendState(RenderStatePool::GetBlendState(mRenderState.blendState).Get(), sBlendFactor, sSampleMask);
		c->OMSetDepthStencilState(RenderStatePool::GetDepthStencilState(mRenderState.depthStencilState).Get(), 1);
		c->RSSetState(RenderStatePool::GetRasterizerState(mRenderState.rasterizerState).Get());
		c->PSSetSamplers(0, 1, RenderStatePool::GetSamplerState(mRenderState.samplerState).GetAddressOf());
	}
}