#pragma once

namespace cmEngine
{
	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer() = default;

		template <typename VertexType>
		void Create(const std::vector<VertexType>& inVertices);

		::ComPtr<ID3D11Buffer>	GetBuffer() { return mBuffer; }

		UINT					GetBufferSize() const { return mBufferSize; }
		const UINT*				GetStrideAddr() const { return &mStride; }
		const UINT*				GetOffsetAddr() const { return &mOffset; }

	private:
		::ComPtr<ID3D11Buffer>	mBuffer;
		UINT					mBufferSize;
		UINT					mStride;
		UINT					mOffset;
	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename VertexType>
	inline void VertexBuffer::Create(const std::vector<VertexType>& inVertices)
	{
		mBuffer.Reset();

		D3D11_BUFFER_DESC desc = {};
		desc.Usage             = D3D11_USAGE_DEFAULT;
		desc.ByteWidth         = static_cast<UINT>(sizeof(VertexType) * inVertices.size());
		desc.BindFlags         = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags    = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = inVertices.data();

		HR hr = Renderer::Ref().GetDevice()->CreateBuffer(&desc, &initData, mBuffer.GetAddressOf());

		if (!DX_CHECK(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("Cannot create Vertex Buffer");
			return;
		}

		// Set Size
		mBufferSize = static_cast<UINT>(inVertices.size());

		// Set Stride & Offset
		mStride = sizeof(VertexType);
		mOffset = 0;
	}
}

