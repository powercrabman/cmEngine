#include "pch.h"
#include "cmShader.h"
#include <fstream>

void cmShader::LoadAndCompileHLSL(std::wstring_view inFilePath, std::string_view inEntryPoint, std::string_view inShaderModel)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG) | defined(DEBUG)
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	UComPtr<ID3DBlob> pErrorBlob = nullptr;
	hr = D3DCompileFromFile(
		inFilePath.data(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		inEntryPoint.data(),
		inShaderModel.data(),
		dwShaderFlags,
		0,
		mBlob.GetAddressOf(),
		pErrorBlob.GetAddressOf());

	if (FAILED(hr))
	{
		if (pErrorBlob != nullptr)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		ASSERT(false, "Shader Compile fail!");
	}

	DX_CHECK(hr, "Shader compile fail!");
	LOG_INFO("Shader compile done.");
}

void cmShader::Save(std::wstring_view inFilePath)
{
	ID3DBlob* blob = GetBlob();
	ASSERT(blob != nullptr, "VertexShader create fail.");

	if (blob)
	{
		std::ofstream file(inFilePath.data(), std::ios::binary);
		file.write(static_cast<const char*>(blob->GetBufferPointer()), blob->GetBufferSize());
	}
	else
	{
		LOG_ERROR("VertexShader create fail.");
	}
}
