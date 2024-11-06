#pragma once

class cmIndexBufferU32
{
public:
	cmIndexBufferU32() = default;
	virtual ~cmIndexBufferU32() = default;

	cmIndexBufferU32(const cmIndexBufferU32& other)
	{
		cmHelper::Graphics::CopyBuffer(mBuffer.Get(), other.GetBuffer());
	}

	cmIndexBufferU32 operator=(const cmIndexBufferU32& other)
	{
		cmHelper::Graphics::CopyBuffer(mBuffer.Get(), other.GetBuffer());
	}

	void Create(const std::vector<UINT>& inIndices)
	{
		mBuffer.Reset();

		auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = static_cast<UINT>(sizeof(UINT) * inIndices.size());
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = inIndices.data();

		HRESULT hr = dv->CreateBuffer(&desc, &initData, mBuffer.GetAddressOf());
		mSize = inIndices.size();

		DX_CHECK(hr, "vertex buffer creating fail.");
	}

	ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }
	size_t GetBufferSize() const { return mSize; }
	constexpr DXGI_FORMAT GetFormat() const { return DXGI_FORMAT_R32_UINT; }

private:
	UComPtr<ID3D11Buffer> mBuffer = nullptr;
	size_t mSize = 0;
};