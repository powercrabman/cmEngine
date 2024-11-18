#pragma once

namespace cmEngine
{
	struct SpriteRender
	{
		Sprite*		sprite        = nullptr;
		ShaderSet*	shaders       = nullptr;
		RenderState rendererState = RenderState::DefaultState;
	};
}