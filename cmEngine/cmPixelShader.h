#pragma once
#include "cmShader.h"

class cmPixelShader : public cmShader
{
public:
	cmPixelShader() = default;
	virtual ~cmPixelShader() = default;

	void Create();
	ID3D11PixelShader* GetShader() const { return mPS.Get(); }

	bool IsCreated() const { return mPS != nullptr; }

private:
	UComPtr<ID3D11PixelShader> mPS = nullptr;
};

