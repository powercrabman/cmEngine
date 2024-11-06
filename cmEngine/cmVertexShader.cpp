#include "pch.h"
#include "cmVertexShader.h"
#include <fstream>

cmVertexShader::~cmVertexShader() {}

void cmVertexShader::Create()
{
	auto* d = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();
	auto* blob = GetBlob();
	ASSERT(blob != nullptr, "VertexShader create fail.");

	if (blob)
	{
		HRESULT hr = d->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, mVS.GetAddressOf());
		DX_CHECK(hr, "VertexShader create fail.");
	}
	else
	{
		LOG_ERROR("VertexShader create fail.");
	}
}
