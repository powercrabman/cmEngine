#include "EnginePch.h"
#include "RenderStatePool.h"

namespace cmEngine
{
	void RenderStatePool::Initialize()
	{
		HR hr = {};

		// Blend State
		{
			D3D11_BLEND_DESC desc = {};

			for (uint32 idx = 0; idx < (uint32)eBlendState::Count; ++idx)
			{
				FILL_ZERO(desc, D3D11_BLEND_DESC);
				auto state = static_cast<eBlendState>(idx);

				switch (state)
				{
				case eBlendState::Opaque:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = FALSE;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::Alpha:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
					desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
					desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::StraightAlpha:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::Additive:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::Multiplicative:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_DEST_COLOR;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::Substractive:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::AlphaToCoverage:
					desc.AlphaToCoverageEnable = TRUE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;

				case eBlendState::Screen:
					desc.AlphaToCoverageEnable = FALSE;
					desc.IndependentBlendEnable = FALSE;
					desc.RenderTarget[0].BlendEnable = TRUE;
					desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
					desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
					desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
					desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
					break;
				}

				hr = Renderer::GetDevice()->CreateBlendState(&desc, mBlendState[idx].GetAddressOf());
				DX_ASSERT(hr, std::format("{} create Fail", ToString(state)));
			}
		}

		// Sampler State
		{
			D3D11_SAMPLER_DESC desc = {};

			for (uint32 idx = 0; idx < (uint32)eSamplerState::Count; ++idx)
			{
				FILL_ZERO(desc, D3D11_SAMPLER_DESC);
				auto state = static_cast<eSamplerState>(idx);

				switch (state)
				{
				case eSamplerState::Point_Wrap:
					desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
					break;

				case eSamplerState::Point_Clamp:
					desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
					break;

				case eSamplerState::Linear_Wrap:
					desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
					break;

				case eSamplerState::Linear_Clamp:
					desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
					break;

				case eSamplerState::Anisotropic_Wrap:
					desc.Filter = D3D11_FILTER_ANISOTROPIC;
					desc.MaxAnisotropy = 16;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
					break;

				case eSamplerState::Anisotropic_Clamp:
					desc.Filter = D3D11_FILTER_ANISOTROPIC;
					desc.MaxAnisotropy = 16;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
					break;

				case eSamplerState::Comparison:
					desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
					desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
					desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
					desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
					desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
					desc.BorderColor[0] = 1.0f;
					desc.BorderColor[1] = 1.0f;
					desc.BorderColor[2] = 1.0f;
					desc.BorderColor[3] = 1.0f;
					break;
				}

				hr = Renderer::GetDevice()->CreateSamplerState(&desc, mSamplerState[idx].GetAddressOf());
				DX_ASSERT(hr, std::format("{} create Fail", ToString(state)));
			}
		}

		// Depth Stencil State
		{
			D3D11_DEPTH_STENCIL_DESC desc = {};

			for (uint32 idx = 0; idx < (uint32)eDepthStencilState::Count; ++idx)
			{
				FILL_ZERO(desc, D3D11_DEPTH_STENCIL_DESC);
				auto state = static_cast<eDepthStencilState>(idx);

				switch (state)
				{
				case eDepthStencilState::Depth:
					desc.DepthEnable = TRUE;
					desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
					desc.DepthFunc = D3D11_COMPARISON_LESS;
					desc.StencilEnable = FALSE;
					break;

				case eDepthStencilState::Depth_ReadOnly:
					desc.DepthEnable = TRUE;
					desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
					desc.DepthFunc = D3D11_COMPARISON_LESS;
					desc.StencilEnable = FALSE;
					break;

				case eDepthStencilState::No_Depth:
					desc.DepthEnable = FALSE;
					desc.StencilEnable = FALSE;
					break;

				case eDepthStencilState::Depth_Stencil:
					desc.DepthEnable = TRUE;
					desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
					desc.DepthFunc = D3D11_COMPARISON_LESS;
					desc.StencilEnable = TRUE;
					desc.StencilReadMask = 0xFF;
					desc.StencilWriteMask = 0xFF;

					desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
					desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

					desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
					desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
					break;

				case eDepthStencilState::Depth_ReadOnly_Stencil:
					desc.DepthEnable = TRUE;
					desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
					desc.DepthFunc = D3D11_COMPARISON_LESS;
					desc.StencilEnable = TRUE;
					desc.StencilReadMask = 0xFF;
					desc.StencilWriteMask = 0xFF;

					desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
					desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

					desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
					desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
					desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
					break;

				}

				hr = Renderer::GetDevice()->CreateDepthStencilState(&desc, mDepthStencilState[idx].GetAddressOf());
				DX_ASSERT(hr, std::format("{} create Fail", ToString(state)));
			}
		}

		// ReasterizerState
		{
			D3D11_RASTERIZER_DESC desc = {};

			for (uint32 idx = 0; idx < (uint32)eRasterizerState::Count; ++idx)
			{
				FILL_ZERO(desc, D3D11_RASTERIZER_DESC);

				switch (static_cast<eRasterizerState>(idx))
				{
				case eRasterizerState::Solid_CCWCull:
					desc.FillMode = D3D11_FILL_SOLID;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Solid_CWCull:
					desc.FillMode = D3D11_FILL_SOLID;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = FALSE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Solid_NoCull:
					desc.FillMode = D3D11_FILL_SOLID;
					desc.CullMode = D3D11_CULL_NONE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Wireframe_CCWCull:
					desc.FillMode = D3D11_FILL_WIREFRAME;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Wireframe_CWCull:
					desc.FillMode = D3D11_FILL_WIREFRAME;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = FALSE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Wireframe_NoCull:
					desc.FillMode = D3D11_FILL_WIREFRAME;
					desc.CullMode = D3D11_CULL_NONE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Solid_CCWCull_Antialias:
					desc.FillMode = D3D11_FILL_SOLID;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = TRUE;
					desc.AntialiasedLineEnable = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Solid_CWCull_Antialias:
					desc.FillMode = D3D11_FILL_SOLID;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = FALSE;
					desc.AntialiasedLineEnable = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Solid_NoCull_Antialias:
					desc.FillMode = D3D11_FILL_SOLID;
					desc.CullMode = D3D11_CULL_NONE;
					desc.AntialiasedLineEnable = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Wireframe_CCWCull_Antialias:
					desc.FillMode = D3D11_FILL_WIREFRAME;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = TRUE;
					desc.AntialiasedLineEnable = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Wireframe_CWCull_Antialias:
					desc.FillMode = D3D11_FILL_WIREFRAME;
					desc.CullMode = D3D11_CULL_BACK;
					desc.FrontCounterClockwise = FALSE;
					desc.AntialiasedLineEnable = TRUE;
					desc.DepthClipEnable = TRUE;
					break;

				case eRasterizerState::Wireframe_NoCull_Antialias:
					desc.FillMode = D3D11_FILL_WIREFRAME;
					desc.CullMode = D3D11_CULL_NONE;
					desc.AntialiasedLineEnable = TRUE;
					desc.DepthClipEnable = TRUE;
					break;
				}

				hr = Renderer::GetDevice()->CreateRasterizerState(&desc, mRasterizeState[idx].GetAddressOf());
				DX_ASSERT(hr, std::format("{} create Fail", ToString(static_cast<eRasterizerState>(idx))));
			}
		}
	}
}