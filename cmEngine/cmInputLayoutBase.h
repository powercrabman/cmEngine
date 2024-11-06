#pragma once

class cmInputLayoutBase
{
public:
	cmInputLayoutBase() = default;
	virtual ~cmInputLayoutBase() = default;

	ID3D11InputLayout* GetInputLayout() const { return mInputLayout.Get(); }

protected:
	UComPtr<ID3D11InputLayout> mInputLayout = nullptr;
};