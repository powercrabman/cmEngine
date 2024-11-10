#pragma once
#include "cmComponent.h"

class cmRenderComponent : public cmComponent
{
public:
	cmRenderComponent() = default;
	virtual ~cmRenderComponent() = default;

	void OnStart() override;
	void OnFinish() override;

	cmPipelineData GetPipelineData() const { return mPipeData; }

	// TODO - 후에 구조 변경
	void SetShaders(cmVertexShader* inVertexShader, cmPixelShader* inPixelShader)
	{
		mPipeData.VertexShader = inVertexShader;
		mPipeData.PixelShader = inPixelShader;
	}

	constexpr inline static eComponentType ComponentType = eComponentType::RenderComponent;

protected:
	cmPipelineData mPipeData = {};
};

