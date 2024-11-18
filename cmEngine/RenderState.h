#pragma once

namespace cmEngine
{
	struct RenderState
	{
		static RenderState DefaultState;

		eSamplerState		samplerState;
		eDepthStencilState	depthStencilState;
		eRasterizerState	rasterizerState;
		eBlendState			blendState;
	};
}


