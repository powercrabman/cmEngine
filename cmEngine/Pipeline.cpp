#include "EnginePch.h"
#include "Pipeline.h"

namespace cmEngine
{
	void Pipeline::SubmitPipeline(const PipelineData& inPipelineDate)
	{
		if (mPipeData.Geometry != inPipelineDate.Geometry)
		{
			mPipeData.Geometry = inPipelineDate.Geometry;

			VertexBuffer* vertexBuffer = mPipeData.Geometry->GetVertexBuffer();
			IndexBuffer* indexBuffer = mPipeData.Geometry->GetIndexBuffer();
			Renderer::GetContext()->IASetVertexBuffers(0, 1, vertexBuffer->GetBuffer().GetAddressOf(), vertexBuffer->GetStrideAddr(), vertexBuffer->GetOffsetAddr());
			Renderer::GetContext()->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		}

		if (mPipeData.VertexShader != inPipelineDate.VertexShader)
		{
			mPipeData.VertexShader = inPipelineDate.VertexShader;
			Renderer::GetContext()->VSSetShader(mPipeData.VertexShader->GetShader().Get(), nullptr, 0);
			Renderer::GetContext()->IASetInputLayout(mPipeData.VertexShader->GetInputLayout().Get());
		}

		if (mPipeData.PixelShader != inPipelineDate.PixelShader)
		{
			mPipeData.PixelShader = inPipelineDate.PixelShader;
			Renderer::GetContext()->PSSetShader(mPipeData.PixelShader->GetShader().Get(), nullptr, 0);
		}

		if (mPipeData.Texture != inPipelineDate.Texture)
		{
			mPipeData.Texture = inPipelineDate.Texture;
			Renderer::GetContext()->PSSetShaderResources(0, 1, mPipeData.Texture->GetShaderResourceView().GetAddressOf());
		}

		// Render State
		if (mPipeData.Blendstate != inPipelineDate.Blendstate)
		{
			mPipeData.Blendstate = inPipelineDate.Blendstate;
			RenderState::BindBlendState(mPipeData.Blendstate);
		}

		if (mPipeData.SamplerState != inPipelineDate.SamplerState)
		{
			//TEMP
			mPipeData.SamplerState = inPipelineDate.SamplerState;
			RenderState::BindSamplerState(mPipeData.SamplerState, PipelineShaderFlags_PixelShader);
		}

		if (mPipeData.DepthStencilState != inPipelineDate.DepthStencilState)
		{
			mPipeData.DepthStencilState = inPipelineDate.DepthStencilState;
			RenderState::BindDepthStencilState(mPipeData.DepthStencilState);
		}

		if (mPipeData.RasterizerState != inPipelineDate.RasterizerState)
		{
			mPipeData.RasterizerState = inPipelineDate.RasterizerState;
			RenderState::BindRasterizerState(mPipeData.RasterizerState);
		}
	}

	void Pipeline::SubmitGraphicsData()
	{
		// Constant Buffer

		// VS
		{
			uint32 idx = 0;
			for (auto iter = mPipeData.VertexShader->GetConstantBufferListConstBegin(); iter != mPipeData.VertexShader->GetConstantBufferListConstEnd(); ++iter)
			{
				ConstantBufferBase* cb = *iter;
				if (cb != ConstantBufferDatas[idx])
				{
					Renderer::GetContext()->VSSetConstantBuffers(idx, 1, cb->GetBuffer().GetAddressOf());
				}
				++idx;
			}
		}

		// PS
		{
			uint32 idx = 0;
			for (auto iter = mPipeData.PixelShader->GetConstantBufferListConstBegin(); iter != mPipeData.PixelShader->GetConstantBufferListConstEnd(); ++iter)
			{
				ConstantBufferBase* cb = *iter;
				if (cb != ConstantBufferDatas[idx])
				{
					Renderer::GetContext()->VSSetConstantBuffers(idx, 1, cb->GetBuffer().GetAddressOf());
				}
				++idx;
			}
		}
	}
}