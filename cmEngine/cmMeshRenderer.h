#pragma once
#include "cmComponent.h"

class cmMesh;

class cmMeshRenderer : public cmComponent
{
public:
	cmMeshRenderer() = default;
	virtual ~cmMeshRenderer() = default;

	void OnStart() override;
	void OnFinish() override;
	
	void SetPipelineData(const cmPipelineData& inPipeData) { mPipeData = inPipeData; }
	cmPipelineData GetPipelineData() const { return mPipeData; }

	constexpr inline static eComponentType ComponentType = eComponentType::MeshRenderer;

private:
	cmPipelineData mPipeData = {};
};
