#pragma once

class cmGameObject;

class cmConstantBufferBase
{
public:
	cmConstantBufferBase() = default;
	virtual ~cmConstantBufferBase() = default;

	bool GetDirtyBit() const { return mDirtyBit; }

	ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }
	ID3D11Buffer* const* GetBufferPtr() { return mBuffer.GetAddressOf(); }

protected:
	UComPtr<ID3D11Buffer> mBuffer = nullptr;

	bool mDirtyBit = false;
};