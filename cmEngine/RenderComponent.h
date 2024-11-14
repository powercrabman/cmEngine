#pragma once
#include "Component.h"

namespace cmEngine
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		void OnStart() override;
		void OnFinish() override;

		PipelineData GetPipelineData() const { return mPipeData; }

		void SetShaders(VertexShader* inVertexShader, PixelShader* inPixelShader)
		{
			mPipeData.VertexShader = inVertexShader;
			mPipeData.PixelShader = inPixelShader;
		}

	protected:
		PipelineData mPipeData = {};
	};
}
