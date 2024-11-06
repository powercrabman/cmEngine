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
	
	cmMesh* GetMesh() const { return mMesh; }
	void SetMesh(cmMesh* inMesh) { mMesh = inMesh; }

private:
	cmMesh* mMesh = nullptr;
};
