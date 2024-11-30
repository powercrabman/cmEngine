#pragma once

namespace cmEngine
{
	//===================================================
	//			           Base
	//===================================================

	class ConstantBufferBase
	{
	public:
		ConstantBufferBase() {}
		virtual ~ConstantBufferBase() {}

		::ComPtr<ID3D11Buffer> GetBuffer() const { return mBuffer; }

	protected:
		::ComPtr<ID3D11Buffer> mBuffer;
	};

	//===================================================
	//			          Concrete
	//===================================================

	class ConstantBufferDataBase;

	template <typename ConstantBufferDataType>
	class ConstantBuffer : public ConstantBufferBase
	{
		static_assert(std::is_base_of<ConstantBufferDataBase, ConstantBufferDataType>::value);
	public:
				ConstantBuffer() {}
		virtual ~ConstantBuffer() {}

		void Create();
		void UpdateBuffer(const ConstantBufferDataType& inData);
	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename ConstantBufferDataType>
	inline void ConstantBuffer<ConstantBufferDataType>::Create()
	{
		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(ConstantBufferDataType);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HR hr = Renderer::Ref().GetDevice()->CreateBuffer(&desc, nullptr, mBuffer.GetAddressOf());

		if (!DX_CHECK(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("Constant Buffer Create Fail.");
			return;
		}

		ENGINE_LOG_INFO("Constant buffer create done.");
	}

	template<typename ConstantBufferDataType>
	inline void ConstantBuffer<ConstantBufferDataType>::UpdateBuffer(const ConstantBufferDataType& inData)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		HR hr = Renderer::Ref().GetContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);

		if (!DX_CHECK(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("Map open fail.");
			return;
		}
		else
		{
			std::memcpy(subRes.pData, &inData, sizeof(ConstantBufferDataType));
		}

		Renderer::Ref().GetContext()->Unmap(mBuffer.Get(), 0);
	}
}