#pragma once

class cmVertexShader;

class cmInputLayoutBase
{
public:
	cmInputLayoutBase() = default;
	virtual ~cmInputLayoutBase() = default;

	ID3D11InputLayout* GetInputLayout() const { return mInputLayout.Get(); }
	virtual void Create(cmVertexShader* inVertexShader) abstract;

protected:
	UComPtr<ID3D11InputLayout> mInputLayout = nullptr;
};