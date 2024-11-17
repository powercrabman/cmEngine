#pragma once
#include "Component.h"

namespace cmEngine
{
	class RenderComponent : public Component
	{
	public:
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		void Awake() override;
		void Sleep() override;

		const PipelineData& GetPipelineData() const { return mPipeData; }
		void				SetShaders(ShaderSet* inShaderSet) { mPipeData.ShaderSet = inShaderSet; }

	protected:
		PipelineData mPipeData = {};
	};
}
