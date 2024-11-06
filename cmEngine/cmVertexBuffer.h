#pragma once

#include "cmVertexData.h"

class cmVertexBuffer
{
public:
	cmVertexBuffer() = default;
	virtual ~cmVertexBuffer() = default;

	cmVertexBuffer(const cmVertexBuffer& other)
	{
		cmHelper::Graphics::CopyBuffer(mBuffer.Get(), other.GetBuffer());
	}

	cmVertexBuffer operator=(const cmVertexBuffer& other) const
	{
		cmHelper::Graphics::CopyBuffer(mBuffer.Get(), other.GetBuffer());
	}

	template <typename VertexType>
	void Create(const std::vector<VertexType>& inVertices)
	{
		static_assert(std::is_base_of<cmVertexBase, VertexType>::value);
		mBuffer.Reset();

		auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<UINT>(sizeof(VertexType) * inVertices.size());
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = inVertices.data();

		HRESULT hr = dv->CreateBuffer(&desc, &initData, mBuffer.GetAddressOf());

		DX_CHECK(hr, "vertex buffer creating fail.");

		// Set Size
		mBufferSize = static_cast<UINT>(inVertices.size());

		// Set Stride & Offset
		mStride = sizeof(VertexType);
		mOffset = 0;
	}

	ID3D11Buffer* const*	GetBufferRef() { return mBuffer.GetAddressOf(); }
	ID3D11Buffer*			GetBuffer() const { return mBuffer.Get(); }

	UINT GetBufferSize() const { return mBufferSize; }

	const UINT* GetStrideRef() const { return &mStride; }
	const UINT* GetOffsetRef() const { return &mOffset; }

private:
	UComPtr<ID3D11Buffer> mBuffer = nullptr;
	UINT mBufferSize = 0;

	UINT mStride = 0;
	UINT mOffset = 0;
};