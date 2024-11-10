#pragma once
#include "cmRenderComponent.h"

class cmMesh;

class cmMeshRenderer : public cmRenderComponent
{
public:
	cmMeshRenderer() = default;
	virtual ~cmMeshRenderer() = default;

	void SetMesh(cmMesh* inMesh)
	{
		assert(inMesh);
		mPipeData.Mesh = inMesh;
	}
};
