#pragma once

namespace cmEngine
{
	struct FlipbookRender
	{
		Flipbook*	flipbook      = nullptr;
		ShaderSet*	shaders       = nullptr;
		RenderState rendererState = RenderState::DefaultState;

		uint32		curFrame      = 0;
		float		playbackSpeed = 1.f;
		float		timeAcc       = 0.f;
		bool		finish        = false;
	};

}