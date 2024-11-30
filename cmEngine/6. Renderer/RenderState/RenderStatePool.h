#pragma once

namespace cmEngine
{
	enum class eBlendState
	{
		Opaque = 0, /* Default */
		Alpha,

		Count,

		Default = Alpha
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

		Default = Depth
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
		PipelineShaderFlags_VertexShader = 0,
		PipelineShaderFlags_GeometryShader = BIT(1),
		PipelineShaderFlags_HullShader = BIT(2),
		PipelineShaderFlags_DomainShader = BIT(3),
		PipelineShaderFlags_PixelShader = BIT(4),
		PipelineShaderFlags_ComputeShader = BIT(5)
	};

	class RenderStatePool
	{
	public:
		static void Initialize();

		static ::ComPtr<ID3D11BlendState> GetBlendState(eBlendState inState)
		{
			return mBlendState[static_cast<uint32>(inState)];

		}
		static ::ComPtr<ID3D11SamplerState> GetSamplerState(eSamplerState inState)
		{
			return mSamplerState[static_cast<uint32>(inState)];
		}
		static ::ComPtr<ID3D11DepthStencilState> GetDepthStencilState(eDepthStencilState inState)
		{
			return mDepthStencilState[static_cast<uint32>(inState)];
		}
		static ::ComPtr<ID3D11RasterizerState> GetRasterizerState(eRasterizerState inState)
		{
			return mRasterizeState[static_cast<uint32>(inState)];
		}

		static void CleanUp()
		{
			mBlendState.fill(nullptr);
			mDepthStencilState.fill(nullptr);
			mRasterizeState.fill(nullptr);
			mSamplerState.fill(nullptr);
		}

		inline static constexpr std::array<const char*, static_cast<uint32>(eBlendState::Count)> sBlendStateString =
		{
			"Opaque",
			"Alpha"
		};

		inline static constexpr std::array<const char*, static_cast<uint32>(eSamplerState::Count)> sSamplerStateString =
		{
			"Point_Wrap",
			"Point_Clamp",
			"Linear_Wrap",
			"Linear_Clamp",
			"Anisotropic_Wrap",
			"Anisotropic_Clamp",
			"Comparison",
		};

		inline static constexpr std::array<const char*, static_cast<uint32>(eDepthStencilState::Count)> sDepthStencilStateString =
		{
			"Depth",
			"Depth_ReadOnly",
			"No_Depth",
			"Depth_Stencil",
			"Depth_ReadOnly_Stencil",
			"No_Depth_Stencil"
		};

		inline static constexpr std::array<const char*, static_cast<uint32>(eRasterizerState::Count)> sRasterizerStateString =
		{
			"Solid_CCWCull",
			"Solid_CWCull",
			"Solid_NoCull",
			"Wireframe_CCWCull",
			"Wireframe_CWCull",
			"Wireframe_NoCull",
			"Solid_CCWCull_Antialias",
			"Solid_CWCull_Antialias",
			"Solid_NoCull_Antialias",
			"Wireframe_CCWCull_Antialias",
			"Wireframe_CWCull_Antialias",
			"Wireframe_NoCull_Antialias",
		};

	private:
		inline static std::array<::ComPtr<ID3D11BlendState>, static_cast<uint32>(eBlendState::Count)>					mBlendState = {};
		inline static std::array<::ComPtr<ID3D11SamplerState>, static_cast<uint32>(eSamplerState::Count)>				mSamplerState = {};
		inline static std::array<::ComPtr<ID3D11DepthStencilState>, static_cast<uint32>(eDepthStencilState::Count)>		mDepthStencilState = {};
		inline static std::array<::ComPtr<ID3D11RasterizerState>, static_cast<uint32>(eRasterizerState::Count)>			mRasterizeState = {};
	};

	//===================================================
	//                    ToString
	//===================================================

	inline constexpr const char* ToString(eBlendState inState)
	{
		return RenderStatePool::sBlendStateString[static_cast<uint32>(inState)];
	}

	inline constexpr const char* ToString(eSamplerState inState)
	{
		return RenderStatePool::sSamplerStateString[static_cast<uint32>(inState)];
	}

	inline constexpr const char* ToString(eDepthStencilState inState)
	{
		return RenderStatePool::sDepthStencilStateString[static_cast<uint32>(inState)];
	}

	inline constexpr const char* ToString(eRasterizerState inState)
	{
		return RenderStatePool::sRasterizerStateString[static_cast<uint32>(inState)];
	}

	//===================================================
	//			            JSON
	//===================================================

	JSON_SERIALIZE_ENUM
	(
		eBlendState,
		ENUM_ENTRY(eBlendState::Opaque, "Opaque"),
		ENUM_ENTRY(eBlendState::Alpha, "Alpha")
	);

	JSON_SERIALIZE_ENUM
	(
		eSamplerState,
		ENUM_ENTRY(eSamplerState::Point_Wrap, "Point_Wrap"),
		ENUM_ENTRY(eSamplerState::Point_Clamp, "Point_Clamp"),
		ENUM_ENTRY(eSamplerState::Linear_Wrap, "Linear_Wrap"),
		ENUM_ENTRY(eSamplerState::Linear_Clamp, "Linear_Clamp"),
		ENUM_ENTRY(eSamplerState::Anisotropic_Wrap, "Anisotropic_Wrap"),
		ENUM_ENTRY(eSamplerState::Anisotropic_Clamp, "Anisotropic_Clamp"),
		ENUM_ENTRY(eSamplerState::Comparison, "Comparison")
	);

	JSON_SERIALIZE_ENUM
	(
		eDepthStencilState,
		ENUM_ENTRY(eDepthStencilState::Depth, "Depth"),
		ENUM_ENTRY(eDepthStencilState::Depth_ReadOnly, "Depth_ReadOnly"),
		ENUM_ENTRY(eDepthStencilState::No_Depth, "No_Depth"),
		ENUM_ENTRY(eDepthStencilState::Depth_Stencil, "Depth_Stencil"),
		ENUM_ENTRY(eDepthStencilState::Depth_ReadOnly_Stencil, "Depth_ReadOnly_Stencil"),
		ENUM_ENTRY(eDepthStencilState::No_Depth_Stencil, "No_Depth_Stencil")
	);

	JSON_SERIALIZE_ENUM
	(
		eRasterizerState,
		ENUM_ENTRY(eRasterizerState::Solid_CCWCull, "Solid_CCWCull"),
		ENUM_ENTRY(eRasterizerState::Solid_CWCull, "Solid_CWCull"),
		ENUM_ENTRY(eRasterizerState::Solid_NoCull, "Solid_NoCull"),
		ENUM_ENTRY(eRasterizerState::Wireframe_CCWCull, "Wireframe_CCWCull"),
		ENUM_ENTRY(eRasterizerState::Wireframe_CWCull, "Wireframe_CWCull"),
		ENUM_ENTRY(eRasterizerState::Wireframe_NoCull, "Wireframe_NoCull"),
		ENUM_ENTRY(eRasterizerState::Solid_CCWCull_Antialias, "Solid_CCWCull_Antialias"),
		ENUM_ENTRY(eRasterizerState::Solid_CWCull_Antialias, "Solid_CWCull_Antialias"),
		ENUM_ENTRY(eRasterizerState::Solid_NoCull_Antialias, "Solid_NoCull_Antialias"),
		ENUM_ENTRY(eRasterizerState::Wireframe_CCWCull_Antialias, "Wireframe_CCWCull_Antialias"),
		ENUM_ENTRY(eRasterizerState::Wireframe_CWCull_Antialias, "Wireframe_CWCull_Antialias"),
		ENUM_ENTRY(eRasterizerState::Wireframe_NoCull_Antialias, "Wireframe_NoCull_Antialias")
	);
}

