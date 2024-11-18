#pragma once

namespace cmEngine
{
	struct GeometryRender
	{
		Geometry geometry;
		ShaderSet* shaders = nullptr;
		RenderState renderState = RenderState::DefaultState;
	};
}
