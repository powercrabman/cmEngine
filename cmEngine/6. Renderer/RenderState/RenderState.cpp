#include "0. cmEngine/cmEngine.h"
#include "RenderState.h"

namespace cmEngine
{
	RenderState RenderState::DefaultState = {
		.samplerState = eSamplerState::Default,
		.depthStencilState = eDepthStencilState::Default,
		.rasterizerState = eRasterizerState::Default,
		.blendState = eBlendState::Default
	};
}