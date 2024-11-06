#pragma once
#include "cmShader.h"

class cmVertexShader : public cmShader
{
	RESOURCE_BODY();
public:
	virtual ~cmVertexShader();

	void Create() override;
	ID3D11VertexShader* GetShader() const { return mVS.Get(); }

	bool IsCreated() const { return mVS != nullptr; }

private:
	cmVertexShader() = default;

	UComPtr<ID3D11VertexShader> mVS = nullptr;
};