#include "EnginePch.h"
#include "IndexBuffer.h"

namespace cmEngine
{
	void IndexBuffer::Create(const std::vector<UINT>& inIndices)
	{
		mBuffer.Reset();

		D3D11_BUFFER_DESC desc = {};
		desc.Usage             = D3D11_USAGE_DEFAULT;
		desc.ByteWidth         = static_cast<UINT>(sizeof(UINT) * inIndices.size());
		desc.BindFlags         = D3D11_BIND_INDEX_BUFFER;
		desc.CPUAccessFlags    = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem                = inIndices.data();

		HR hr = Renderer::GetDevice()->CreateBuffer(&desc, &initData, mBuffer.GetAddressOf());
		mSize = inIndices.size();

		if (!DX_CHECK(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("vertex buffer creating fail.");
			return;
		}
	}
}