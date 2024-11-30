#include "EnginePch.h"
#include "PixelShader.h"

namespace cmEngine
{
	void cmEngine::PixelShader::Create()
	{
		HR hr = Renderer::GetDevice()->CreatePixelShader(
			GetBlob()->GetBufferPointer(),
			GetBlob()->GetBufferSize(),
			nullptr,
			mShader.GetAddressOf()
		);

		if (!DX_CHECK(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("pixel shader create error.");
			return;
		}

		ENGINE_LOG_INFO("pixel shader create done.");
	}
}

