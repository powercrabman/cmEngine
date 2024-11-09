#include "pch.h"
#include "cmGraphicsHelper.h"

namespace cmHelper::Graphics
{
	void CopyBuffer(ID3D11Buffer* dst, ID3D11Buffer* src)
	{
		auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();
		auto* dc = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();
		

		D3D11_BUFFER_DESC desc = {};
		src->GetDesc(&desc);

		HR hr = dv->CreateBuffer(&desc, nullptr, &dst);
		DX_ASSERT(hr, "index buffer creating fail during copy.");

		dc->CopyResource(dst, src);
	}

}
