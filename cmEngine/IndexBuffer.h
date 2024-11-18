#pragma once

namespace cmEngine
{
	class IndexBuffer
	{
	public:
		IndexBuffer()  = default;
		~IndexBuffer() = default;

		void Create(const std::vector<UINT>& inIndices);

		::ComPtr<ID3D11Buffer>	GetBuffer() const { return mBuffer; }
		UINT					GetBufferSize() const { return mSize; }

		constexpr DXGI_FORMAT	GetFormat() const { return DXGI_FORMAT_R32_UINT; }
		
	private:
		::ComPtr<ID3D11Buffer>	mBuffer;
		UINT					mSize;
	};
}
