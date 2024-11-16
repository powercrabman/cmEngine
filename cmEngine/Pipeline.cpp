#include "EnginePch.h"
#include "Pipeline.h"

namespace cmEngine
{
	void Pipeline::SubmitPipeline(const PipelineData& inPipelineDate)
	{
		auto context = Renderer::GetContext();
		if (mPipeData.Geometry != inPipelineDate.Geometry)
		{
			mPipeData.Geometry = inPipelineDate.Geometry;

			VertexBuffer* vertexBuffer = mPipeData.Geometry->GetVertexBuffer();
			IndexBuffer* indexBuffer = mPipeData.Geometry->GetIndexBuffer();
			context->IASetVertexBuffers(0, 1, vertexBuffer->GetBuffer().GetAddressOf(), vertexBuffer->GetStrideAddr(), vertexBuffer->GetOffsetAddr());
			context->IASetIndexBuffer(indexBuffer->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
		}

		if (mPipeData.ShaderSet != inPipelineDate.ShaderSet)
		{
			mPipeData.ShaderSet = inPipelineDate.ShaderSet;
			VertexShader* vs = mPipeData.ShaderSet->GetVertexShader();
			PixelShader* ps = mPipeData.ShaderSet->GetPixelShader();

			context->IASetInputLayout(vs->GetInputLayout().Get());
			context->VSSetShader(vs->GetShader().Get(), nullptr, 0);
			context->PSSetShader(ps->GetShader().Get(), nullptr, 0);
		}

		if (mPipeData.Texture != inPipelineDate.Texture)
		{
			mPipeData.Texture = inPipelineDate.Texture;
			context->PSSetShaderResources(0, 1, mPipeData.Texture->GetShaderResourceView().GetAddressOf());
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

	// TODO - 구조바꾸기 (고정 슬롯 형태)
	void Pipeline::SubmitConstantData()
	{
		VertexShader* vs = mPipeData.ShaderSet->GetVertexShader();
		PixelShader* ps  = mPipeData.ShaderSet->GetPixelShader();

		// VS
		{
			uint32 idx = 0;
			
			for (auto iter = vs->GetConstantBufferListConstBegin(); iter != vs->GetConstantBufferListConstEnd(); ++iter)
			{
				ConstantBufferBase* cb = *iter;
				if (cb != ConstantBufferDatas[idx])
				{
					ConstantBufferDatas[idx] = cb;
					Renderer::GetContext()->VSSetConstantBuffers(idx, 1, cb->GetBuffer().GetAddressOf());
				}
				++idx;
			}
		}

		// PS
		{
			uint32 idx = 0;
			for (auto iter = ps->GetConstantBufferListConstBegin(); iter != ps->GetConstantBufferListConstEnd(); ++iter)
			{
				ConstantBufferBase* cb = *iter;
				if (cb != ConstantBufferDatas[idx])
				{
					ConstantBufferDatas[idx] = cb;
					Renderer::GetContext()->PSSetConstantBuffers(idx, 1, cb->GetBuffer().GetAddressOf());
				}
				++idx;
			}
		}
	}
}