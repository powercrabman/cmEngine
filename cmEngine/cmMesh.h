#pragma once
#include "cmResourceBase.h"

class cmMesh : public cmResourceBase
{
public:
	cmMesh() = default;
	virtual ~cmMesh() = default;

	void Load(std::wstring_view inFilePath) override { /* TODO */ }
	void Save(std::wstring_view inFilePath) override { /* TODO */ }

	void SetPipelineData(const cmPipelineData& inPipeData) { mPipelineData = inPipeData; }
	cmPipelineData GetPipelineData() const { return mPipelineData; }

private:
	cmPipelineData mPipelineData = {};
};