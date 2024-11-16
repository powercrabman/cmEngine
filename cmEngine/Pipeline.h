#pragma once

namespace cmEngine
{
	struct PipelineData
	{
		void Clear()
		{
			Geometry  = nullptr;
			ShaderSet = nullptr;
			Texture   = nullptr;

			Blendstate        = eBlendState::Defaul;
			SamplerState      = eSamplerState::Default;
			DepthStencilState = eDepthStencilState::Default;
			RasterizerState   = eRasterizerState::Default;

			RenderState::BindBlendState(Blendstate);
			RenderState::BindSamplerState(SamplerState, PipelineShaderFlags_PixelShader);
			RenderState::BindDepthStencilState(DepthStencilState);
			RenderState::BindRasterizerState(RasterizerState);
		}

		Geometry*			Geometry           = nullptr;
		ShaderSet*			ShaderSet          = nullptr;
		Texture*			Texture            = nullptr;

		eBlendState			Blendstate         = eBlendState::Defaul;
		eSamplerState		SamplerState       = eSamplerState::Default;
		eDepthStencilState	DepthStencilState  = eDepthStencilState::Default;
		eRasterizerState	RasterizerState    = eRasterizerState::Default;
	};

	class Pipeline
	{
	public:
		Pipeline() = default;
		virtual ~Pipeline() = default;

		void DrawIndices()
		{
			Renderer::GetContext()->DrawIndexed(mPipeData.Geometry->GetIndexBuffer()->GetBufferSize(), 0, 0);
		}

		void Draw()
		{
			Renderer::GetContext()->Draw(mPipeData.Geometry->GetVertexBuffer()->GetBufferSize(), 0);
		}

		void SubmitPipeline(const PipelineData& inPipelineDate);
		void SubmitConstantData();

		void Clear()
		{
			mPipeData.Clear();
			ConstantBufferDatas.fill(nullptr);
		}

	private:
		PipelineData	mPipeData = {};

		enum { CONSTANTBUFFER_SLOT_MAX = 10 };
		std::array<ConstantBufferBase*, CONSTANTBUFFER_SLOT_MAX> ConstantBufferDatas = {}; 
	};
};
