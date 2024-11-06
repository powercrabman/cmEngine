#pragma once
#include "cmShader.h"

class cmPixelShader : public cmShader
{
	RESOURCE_BODY();
public:
	virtual ~cmPixelShader() = default;

	void Create() override;
	ID3D11PixelShader* GetShader() const { return mPS.Get(); }

	bool IsCreated() const { return mPS != nullptr; }

private:
	cmPixelShader() = default;

	UComPtr<ID3D11PixelShader> mPS = nullptr;
};

