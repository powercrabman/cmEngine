#pragma once

template <typename Ty>
class cmConstantBuffer : public cmConstantBufferBase
{
public:
	cmConstantBuffer() = default;
	virtual ~cmConstantBuffer() = default;

	void Create()
	{
		static_assert(std::is_base_of<cmConstantBufferDataBase, Ty>::value, "Ty must derived of ConstatntBufferBase!");
		auto* device = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Ty);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		HR hr = device->CreateBuffer(&desc, nullptr, mBuffer.GetAddressOf());
		DX_ASSERT(hr, "Constant Buffer Create Fail.");
		if (FAILED(hr))
		{
			LOG_ERROR("Constant Buffer Create Fail.");
			return;
		}
	}

	void UpdateBuffer(const Ty& inData)
	{
		static_assert(std::is_base_of<cmConstantBufferDataBase, Ty>::value, "Ty must derived of ConstatntBufferBase!");

		auto* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		HR hr = context->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);

		DX_ASSERT(hr, "Map open fail.");

		if (FAILED(hr))
		{
			LOG_ERROR("ContantBuffer Update Fail.");
		}
		else
		{
			std::memcpy(subRes.pData, &inData, sizeof(Ty));
		}

		context->Unmap(mBuffer.Get(), 0);
	}
};