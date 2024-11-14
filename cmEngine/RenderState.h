#pragma once

namespace cmEngine
{
	enum class eBlendState
	{
		Opaque = 0, /* Default */
		Alpha,
		StraightAlpha,
		Additive,
		Multiplicative,
		Substractive,
		AlphaToCoverage,
		Screen,

		Count,

		Defaul = Opaque
	};

	enum class eSamplerState
	{
		Point_Wrap = 0, /* Default */
		Point_Clamp,

		Linear_Wrap,
		Linear_Clamp,

		Anisotropic_Wrap,
		Anisotropic_Clamp,

		Comparison,

		Count,

		Default = Point_Wrap
	};

	enum class eDepthStencilState
	{
		Depth = 0, /* Default */
		Depth_ReadOnly,
		No_Depth,

		Depth_Stencil,
		Depth_ReadOnly_Stencil,
		No_Depth_Stencil,

		Count,

		Default   = Depth
	}; 

	enum class eRasterizerState
	{
		Solid_CCWCull = 0, /* Default */
		Solid_CWCull,
		Solid_NoCull,

		Wireframe_CCWCull,
		Wireframe_CWCull,
		Wireframe_NoCull,

		Solid_CCWCull_Antialias,
		Solid_CWCull_Antialias,
		Solid_NoCull_Antialias,

		Wireframe_CCWCull_Antialias,
		Wireframe_CWCull_Antialias,
		Wireframe_NoCull_Antialias,

		Count,

		Default = Solid_CCWCull
	};

	using PipelineShaderFlags = uint32;
	enum PipelineShaderFlags_
	{
		PipelineShaderFlags_VertexShader   = 0,
		PipelineShaderFlags_GeometryShader = BIT(1),
		PipelineShaderFlags_HullShader     = BIT(2),
		PipelineShaderFlags_DomainShader   = BIT(3),
		PipelineShaderFlags_PixelShader    = BIT(4),
		PipelineShaderFlags_ComputeShader  = BIT(5)
	};

	class RenderState
	{
	public:
		void Initialize();

		static void	BindBlendState(eBlendState inState);
		static void	BindSamplerState(eSamplerState inState, PipelineShaderFlags inFlags);
		static void	BindDepthStencilState(eDepthStencilState inState);
		static void BindRasterizerState(eRasterizerState inState);

	private:
		inline static std::array<::ComPtr<ID3D11BlendState>, (uint32)eBlendState::Count>					mBlendState = {};
		inline static std::array<::ComPtr<ID3D11SamplerState>, (uint32)eSamplerState::Count>				mSamplerState = {};
		inline static std::array<::ComPtr<ID3D11DepthStencilState>, (uint32)eDepthStencilState::Count>		mDepthStencilState = {};
		inline static std::array<::ComPtr<ID3D11RasterizerState>, (uint32)eRasterizerState::Count>			mRasterizeState = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void RenderState::BindSamplerState(eSamplerState inState, PipelineShaderFlags inFlags)
	{
		ID3D11SamplerState* const* state = mSamplerState[(uint32)inState].GetAddressOf();
		if (inFlags & PipelineShaderFlags_VertexShader)	Renderer::GetContext()->VSSetSamplers(0, 1, state);
		if (inFlags & PipelineShaderFlags_PixelShader)	Renderer::GetContext()->PSSetSamplers(0, 1, state);
	}

	inline void RenderState::BindDepthStencilState(eDepthStencilState inState)
	{
		Renderer::GetContext()->OMSetDepthStencilState(mDepthStencilState[(uint32)inState].Get(), 1);
	}

	inline void RenderState::BindRasterizerState(eRasterizerState inState)
	{
		Renderer::GetContext()->RSSetState(mRasterizeState[(uint32)inState].Get());
	}

	inline void RenderState::BindBlendState(eBlendState inState)
	{
		static FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		static UINT sampleMask = 0xFFFFFFFF;
		Renderer::GetContext()->OMSetBlendState(mBlendState[(uint32)inState].Get(), blendFactor, sampleMask);
	}

	//===================================================
	//                    ToString
	//===================================================

	inline constexpr const char* ToString(eBlendState inState)
	{
		switch (inState)
		{
		case eBlendState::Opaque:				return "Opaque";
		case eBlendState::Alpha:				return "Alpha";
		case eBlendState::StraightAlpha:		return "StraightAlpha";
		case eBlendState::Additive:				return "Additive";
		case eBlendState::Multiplicative:		return "Multiplicative";
		case eBlendState::Substractive:			return "Substractive";
		case eBlendState::AlphaToCoverage:		return "AlphaToCoverage";
		case eBlendState::Screen:				return "Screen";
		default: assert(false); return "Unkownd";
		}
	}

	inline constexpr const char* ToString(eSamplerState inState)
	{
		switch (inState)
		{
		case cmEngine::eSamplerState::Point_Wrap:			  return "Point_Wrap";
		case cmEngine::eSamplerState::Point_Clamp:			  return "Point_Clamp";
		case cmEngine::eSamplerState::Linear_Wrap:			  return "Linear_Wrap";
		case cmEngine::eSamplerState::Linear_Clamp:			  return "Linear_Clamp";
		case cmEngine::eSamplerState::Anisotropic_Wrap:		  return "Anisotropic_Wrap";
		case cmEngine::eSamplerState::Anisotropic_Clamp:	  return "Anisotropic_Clamp";
		case cmEngine::eSamplerState::Comparison:			  return "Comparison";
		default: assert(false);								  return "Undefined";
		}
	}

	inline constexpr const char* ToString(eDepthStencilState inState)
	{
		switch (inState)
		{
		case cmEngine::eDepthStencilState::Depth:					 return "Depth";
		case cmEngine::eDepthStencilState::Depth_ReadOnly:			 return "Depth_ReadOnly";
		case cmEngine::eDepthStencilState::No_Depth:				 return "No_Depth";
		case cmEngine::eDepthStencilState::Depth_Stencil:			 return "Depth_Stencil";
		case cmEngine::eDepthStencilState::Depth_ReadOnly_Stencil:	 return "Depth_ReadOnly_Stencil";
		case cmEngine::eDepthStencilState::No_Depth_Stencil:		 return "No_Depth_Stencil";
		default: assert(false);										 return "Undefined";
		}
	}

	inline constexpr const char* ToString(eRasterizerState inState)
	{
		switch (inState)
		{
		case cmEngine::eRasterizerState::Solid_CCWCull:					return "Solid_CCWCull";
		case cmEngine::eRasterizerState::Solid_CWCull:					return "Solid_CWCull";
		case cmEngine::eRasterizerState::Solid_NoCull:					return "Solid_NoCull";
		case cmEngine::eRasterizerState::Wireframe_CCWCull:				return "Wireframe_CCWCull";
		case cmEngine::eRasterizerState::Wireframe_CWCull:				return "Wireframe_CWCull";
		case cmEngine::eRasterizerState::Wireframe_NoCull:				return "Wireframe_NoCull";
		case cmEngine::eRasterizerState::Solid_CCWCull_Antialias:		return "Solid_CCWCull_Antialias";
		case cmEngine::eRasterizerState::Solid_CWCull_Antialias:		return "Solid_CWCull_Antialias";
		case cmEngine::eRasterizerState::Solid_NoCull_Antialias:		return "Solid_NoCull_Antialias";
		case cmEngine::eRasterizerState::Wireframe_CCWCull_Antialias:	return "Wireframe_CCWCull_Antialias";
		case cmEngine::eRasterizerState::Wireframe_CWCull_Antialias:	return "Wireframe_CWCull_Antialias";
		case cmEngine::eRasterizerState::Wireframe_NoCull_Antialias:	return "Wireframe_NoCull_Antialias";
		default: assert(false);											return "Undefined";
		}
	}
}

